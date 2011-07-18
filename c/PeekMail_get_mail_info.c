/*****************************************************************************
** File Name:      peekmail_get_mail_info.c                                               *
** Author:                                                                   *
** Date:             5/20/2011                                                 *
** Copyright:      2011 Peek Inc. All Rights Reserved.       *
** Description:    This file is used to describe call log                    *
******************************************************************************
**                         Important Edit History                            *
** --------------------------------------------------------------------------*
**   DATE           NAME             DESCRIPTION                               *
** 5.20/2011    Song,Han               Create                                   *
******************************************************************************/

#include "PeekMail_get_mail_info.h"


PUBLIC uint16 PeekMail_GetMailNum(char * info_file)
{
	int8			   *buffer 	= PNULL;
	uint32				bufsize = 0;
	uint32 				length 	= 0;
	uint32 				buf_len = 0;
	uint16				mail_num = 0;
	wchar				info_file_name[256];
	MMIFILE_HANDLE		hFile;	

	MMIAPICOM_StrToWstr(info_file,info_file_name);
	hFile = MMIFILE_CreateFile(
				info_file_name,
				SFS_MODE_READ | SFS_MODE_OPEN_EXISTING,
				PNULL,
				PNULL);

	if(SFS_INVALID_HANDLE == hFile)
	{
		return -1;
	}

	length = MMIFILE_GetFileSize(hFile);
	//SFS_GetFileSize(hFile, &length);

	bufsize = length + 1;
	buffer = (int8 *)malloc(bufsize * sizeof(int8));
	//*(buffer + length) = 0;

	
	if(SFS_ERROR_NONE == MMIFILE_ReadFile(
                hFile, 
                buffer, 
                length, 
                &buf_len, 
                NULL
                ))
	//SFS_ReadFile(hFile, buffer, length, &buf_len, PNULL);
	//SFS_CloseFile(hFile);

	MMIFILE_CloseFile(hFile);

	mail_num = (uint16)atoi(buffer);

	free(buffer);

	return mail_num;
}


LOCAL uint16 PeekMail_GetMailContent(char * file_name, char ** content)
{
	char				*buffer = PNULL;
	uint32				bufsize = 0;
	uint32 				length = 0;
	uint32 				buf_len = 0;
	uint16				mail_num = 0;
	MMIFILE_HANDLE		hFile = PNULL;
	wchar				unicode_file_name[256];
	
	MMIAPICOM_StrToWstr(file_name, unicode_file_name);
	hFile = MMIFILE_CreateFile(
				unicode_file_name,
				SFS_MODE_SHARE_READ | SFS_MODE_OPEN_EXISTING,
				PNULL,
				PNULL);

	if (SFS_INVALID_HANDLE == hFile)
	{
		return -1;
	}
	
	length = MMIFILE_GetFileSize(hFile);
	bufsize = length + 1;
	*content = (char *)malloc(bufsize * sizeof(char));
	buffer = (char *)malloc(bufsize * sizeof(char));
	*(buffer + length) = 0;
	MMIFILE_ReadFile(hFile, buffer, length, &buf_len, PNULL);
	MMIFILE_CloseFile(hFile);

	strcpy(*content, buffer);

	free(buffer);

	return 1;
}


LOCAL uint16 PeekMail_GetMailDetail(char * mail_content, uint16 * content_index, MMI_STRING_T ** detail_item, char end_char)
{
	uint16 index = *content_index;
	uint16 temp_index = 0;
	char   temp[MAX_MAIL_ITEM_SIZE];
	
	memset(temp, 0, sizeof(temp));
	while (end_char != mail_content[index])
	{
		temp[temp_index++] = mail_content[index++];
	}
	*content_index = index + 1;

	*detail_item = (MMI_STRING_T *)malloc(sizeof(MMI_STRING_T));
	(*detail_item)->wstr_ptr = (wchar *)malloc((temp_index+1) * sizeof(wchar));
	MMIAPICOM_StrToWstr(temp, (*detail_item)->wstr_ptr);
	(*detail_item)->wstr_len = MMIAPICOM_Wstrlen((*detail_item)->wstr_ptr);
	return 0;
}


LOCAL void PeekMail_GetMailNextItemIndex(char * mail_content, uint16 * content_index)
{
	uint16 index = *content_index;
	
	while ('\r' != mail_content[index])
	{
		index++;
	}
	*content_index = index + 1;
}


PUBLIC void PeekMail_GetMailStructure(char * file_name, PEEKMAIL_MAIL_STRUCT *mail_detail, PEEKMAIL_MAIL_INFO_TYPE_E info_type)
{
	uint16 content_index = 0;
	uint16 temp_index = 0;
	uint16 index = 0;
	uint16 content_size = 0;
	char*   mail_content = PNULL;
	char   temp[MAX_MAIL_ITEM_SIZE];
	char   read_flag = '0';

	PeekMail_GetMailContent(file_name, &mail_content);
	content_size = strlen(mail_content);

	memset(temp, 0, sizeof(temp));

	if (ALL_INFO == info_type)
	{
		mail_detail->file_name = (uint8 *)malloc((strlen(file_name)+1)*sizeof(uint8));
		strcpy(mail_detail->file_name, file_name);
	}

	for (content_index=0; content_index<content_size; content_index++)
	{
		temp[temp_index] = mail_content[content_index];

		if (!strcmp(temp, READ_STR))
		{
			if (RE_FWD_INFO != info_type)
			{
				mail_detail->read_flag = mail_content[++content_index] - 48;
			}
			else
			{
				content_index++;
			}
			memset(temp, 0, sizeof(temp));
			content_index += 2;
			temp_index = 0;
		}
		else if (!strcmp(temp, DATE_STR))
		{
			if (GEN_LIST_INFO != info_type)
			{				
				content_index++;
				PeekMail_GetMailDetail(mail_content, &content_index, &mail_detail->date, '\r');
			}
			else
			{
				PeekMail_GetMailNextItemIndex(mail_content, &content_index);
			}
			memset(temp, 0, sizeof(temp));
			temp_index = 0;
		}
		else if (!strcmp(temp, TIME_STR))
		{	
	
			content_index++;
			PeekMail_GetMailDetail(mail_content, &content_index, &mail_detail->time, '\r');
			memset(temp, 0, sizeof(temp));
			temp_index = 0;
		}
		else if (!strcmp(temp, FROM_STR))
		{
			content_index++;
			PeekMail_GetMailDetail(mail_content, &content_index, &mail_detail->from, '\r');
			memset(temp, 0, sizeof(temp));
			temp_index = 0;
		}
		else if (!strcmp(temp, TO_STR))
		{
			if (GEN_LIST_INFO != info_type)
			{
				content_index++;
				PeekMail_GetMailDetail(mail_content, &content_index, &mail_detail->to, '\r');
			}
			else
			{
				PeekMail_GetMailNextItemIndex(mail_content, &content_index);
			}
			memset(temp, 0, sizeof(temp));
			temp_index = 0;
		}
		else if (!strcmp(temp, CC_STR))
		{
			if (GEN_LIST_INFO != info_type)
			{
				content_index++;
				PeekMail_GetMailDetail(mail_content, &content_index, &mail_detail->cc, '\r');
			}
			else
			{
				PeekMail_GetMailNextItemIndex(mail_content, &content_index);
			}
			memset(temp, 0, sizeof(temp));
			temp_index = 0;
		}
		else if (!strcmp(temp, SUBJECT_STR))
		{
			content_index++;
			PeekMail_GetMailDetail(mail_content, &content_index, &mail_detail->subject, '\r');
			memset(temp, 0, sizeof(temp));
			temp_index = 0;
		}
		else if (!strcmp(temp, TEXT_STR))
		{
			if (GEN_LIST_INFO != info_type)
			{
				content_index += 3;
				PeekMail_GetMailDetail(mail_content, &content_index, &mail_detail->text, '\0');
			}
			else
			{
				return;
			}
			memset(temp, 0, sizeof(temp));
			temp_index = 0;
		}
		else
		{
			temp_index++;
		}
	}
	
}

LOCAL void DestroyString(MMI_STRING_T **string)
{
	if (*string != NULL) {
		free((*string)->wstr_ptr);
		free(*string);
	}
}

//flag == TRUE means mail_detail was generated using malloc(), thus it need to be freed, otherwise ignore it
PUBLIC void PeekMail_DestroyMailStruct(PEEKMAIL_MAIL_STRUCT *mail_detail, BOOLEAN flag)
{
	if(mail_detail->file_name != PNULL) {
		free(mail_detail->file_name);
	}
	DestroyString(&mail_detail->date);
	DestroyString(&mail_detail->time);
	DestroyString(&mail_detail->from);
	DestroyString(&mail_detail->to);
	DestroyString(&mail_detail->cc);
	DestroyString(&mail_detail->subject);
	DestroyString(&mail_detail->text);
	if (flag) {
		free(mail_detail);
	}
}
