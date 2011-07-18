/*****************************************************************************
** File Name:      peekmail_contact_operation.c                                               *
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

#include "PeekMail_contact_operation.h"


PUBLIC uint16 PeekMail_GetContactNum(char * info_file)
{
	char			   *buffer 	= PNULL;
	uint32				bufsize = 0;
	uint32				length 	= 0;
	uint32 				buf_len = 0;
	uint16				mail_num = 0;
	wchar				unicode_file_name[256];
	MMIFILE_HANDLE 		hFile = PNULL;

	MMIAPICOM_StrToWstr(info_file, unicode_file_name);
	hFile = MMIFILE_CreateFile(
				unicode_file_name,
				SFS_MODE_READ | SFS_MODE_OPEN_EXISTING,
				PNULL,
				PNULL);

	if (SFS_INVALID_HANDLE == hFile)
	{
		return -1;
	}
	
	length = MMIFILE_GetFileSize(hFile);
	bufsize = length + 1;
	buffer = (char *)malloc(bufsize * sizeof(char));
	*(buffer + length) = 0;
	MMIFILE_ReadFile(hFile, buffer, length, &buf_len, PNULL);
	MMIFILE_CloseFile(hFile);

	mail_num = (uint16)atoi(buffer);

	free(buffer);

	return mail_num;
}


LOCAL uint16 PeekMail_GetContactContent(char * file_name, char ** content)
{
	char				*buffer = PNULL;
	uint32				bufsize = 0;
	uint32 				length = 0;
	uint32 				buf_len = 0;
	uint16				mail_num = 0;
	wchar				unicode_file_name[256];
	MMIFILE_HANDLE		hFile = PNULL;

	MMIAPICOM_StrToWstr(file_name, unicode_file_name);
	hFile = MMIFILE_CreateFile(
				unicode_file_name,
				SFS_MODE_READ | SFS_MODE_OPEN_EXISTING,
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


LOCAL uint16 PeekMail_GetContactDetail(char * contact_content, uint16 * content_index, MMI_STRING_T ** detail_item, char end_char)
{
	uint16 index = *content_index;
	uint16 temp_index = 0;
	char   temp[MAX_CONTACT_ITEM_SIZE];
	
	memset(temp, 0, sizeof(temp));
	while (end_char != contact_content[index])
	{
		temp[temp_index++] = contact_content[index++];
	}
	*content_index = index + 1;

	*detail_item = (MMI_STRING_T *)malloc(sizeof(MMI_STRING_T));
	(*detail_item)->wstr_ptr = (wchar *)malloc((temp_index+1) * sizeof(wchar));
	MMIAPICOM_StrToWstr(temp, (*detail_item)->wstr_ptr);
	(*detail_item)->wstr_len = MMIAPICOM_Wstrlen((*detail_item)->wstr_ptr);
}


LOCAL void PeekMail_GetContactNextItemIndex(char * contact_content, uint16 * content_index)
{
	uint16 index = *content_index;
	
	while ('\r' != contact_content[index])
	{
		index++;
	}
	*content_index = index + 1;
}


PUBLIC void PeekMail_GetContactStructure(char * file_name, PEEKMAIL_CONTACT_STRUCT *contact_detail, PEEKMAIL_CONTACT_INFO_TYPE_E info_type)
{
	uint16 content_index = 0;
	uint16 temp_index = 0;
	uint16 index = 0;
	uint16 content_size = 0;
	char*  contact_content = PNULL;
	char   temp[MAX_CONTACT_ITEM_SIZE];


	PeekMail_GetContactContent(file_name, &contact_content);
	content_size = strlen(contact_content);

	memset(temp, 0, sizeof(temp));

	if (ALL_INFO == info_type)
	{
		contact_detail->file_name = (uint8 *)malloc((strlen(file_name)+1)*sizeof(uint8));
		strcpy(contact_detail->file_name, file_name);
	}

	for (content_index=0; content_index<content_size; content_index++)
	{
		temp[temp_index] = contact_content[content_index];

		if (!strcmp(temp, NAME_STR))
		{
			content_index++;
			PeekMail_GetContactDetail(contact_content, &content_index, &contact_detail->name, '\r');
			memset(temp, 0, sizeof(temp));
			temp_index = 0;
		}
		else if (!strcmp(temp, PHONE_STR))
		{	
			content_index++;
			PeekMail_GetContactDetail(contact_content, &content_index, &contact_detail->phone, '\r');
			memset(temp, 0, sizeof(temp));
			temp_index = 0;
		}
		else if (!strcmp(temp, MAIL_STR))
		{
			content_index++;
			PeekMail_GetContactDetail(contact_content, &content_index, &contact_detail->mail, '\0');
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
	if (*string != NULL) 
	{
		free((*string)->wstr_ptr);
		free(*string);
	}
}

//flag == TRUE means contact_detail was generated using malloc(), thus it need to be freed, otherwise ignore it
PUBLIC void PeekMail_DestroyContactStruct(PEEKMAIL_CONTACT_STRUCT *contact_detail, BOOLEAN flag)
{
	if(contact_detail->file_name != PNULL) 
	{
		free(contact_detail->file_name);
	}
	DestroyString(&contact_detail->name);
	DestroyString(&contact_detail->phone);
	DestroyString(&contact_detail->mail);

	if (flag) 
	{
		free(contact_detail);
	}
}


