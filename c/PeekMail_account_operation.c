/*****************************************************************************
** File Name:      peekmail_account_operation.c                                               *
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

#include "PeekMail_account_operation.h"


PUBLIC uint16 PeekMail_GetAccountNum(char * info_file)
{
	char			   *buffer 	= PNULL;
	uint32				bufsize = 0;
	uint32 				length 	= 0;
	uint32 				buf_len = 0;
	uint16				mail_num = 0;
	wchar				unicode_file_name[256];
	MMIFILE_HANDLE		hFile = PNULL;
	
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


LOCAL uint16 PeekMail_GetAccountContent(char * file_name, char ** content)
{
	char				*buffer = PNULL;
	uint32				bufsize = 0;
	uint32 				length = 0;
	uint32 				buf_len = 0;
	uint16				mail_num = 0;
	wchar				unicode_file_name[256];
	MMIFILE_HANDLE		hFile;	

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


LOCAL uint16 PeekMail_GetAccountDetail(char * mail_content, uint16 * content_index, MMI_STRING_T ** detail_item, char end_char)
{
	uint16 index = *content_index;
	uint16 temp_index = 0;
	char   temp[MAX_ACCOUNT_ITEM_SIZE];
	
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
}


LOCAL void PeekMail_GetAccountNextItemIndex(char * mail_content, uint16 * content_index)
{
	uint16 index = *content_index;
	
	while ('\r' != mail_content[index])
	{
		index++;
	}
	*content_index = index + 1;
}


PUBLIC void PeekMail_GetAccountStructure(char * file_name, PEEKMAIL_ACCOUNT_STRUCT *account_detail, PEEKMAIL_ACCOUNT_INFO_TYPE_E info_type)
{
	uint16 content_index = 0;
	uint16 temp_index = 0;
	uint16 index = 0;
	uint16 content_size = 0;
	char*  account_content = PNULL;
	char   temp[MAX_ACCOUNT_ITEM_SIZE];
	char   active_flag = '0';
	char   primary_flag = '0';

	PeekMail_GetAccountContent(file_name, &account_content);
	content_size = strlen(account_content);

	memset(temp, 0, sizeof(temp));

	if (ALL_INFO == info_type)
	{
		account_detail->file_name = (uint8 *)malloc((strlen(file_name)+1)*sizeof(uint8));
		strcpy(account_detail->file_name, file_name);
	}

	for (content_index=0; content_index<content_size; content_index++)
	{
		temp[temp_index] = account_content[content_index];

		if (!strcmp(temp, ACTIVE_STR))
		{
			if (ALL_INFO == info_type)
			{
				account_detail->active_flag = account_content[++content_index] - 48;
			}
			else
			{
				content_index++;
			}
			memset(temp, 0, sizeof(temp));
			content_index += 2;
			temp_index = 0;
		}
		else if (!strcmp(temp, PRIMARY_STR))
		{
			if (ALL_INFO == info_type)
			{
				account_detail->primary_flag = account_content[++content_index] - 48;
			}
			else
			{
				content_index++;
			}
			memset(temp, 0, sizeof(temp));
			content_index += 2;
			temp_index = 0;
		}
		else if (!strcmp(temp, ACCOUNT_NAME_STR))
		{
			if (ALL_INFO == info_type)
			{				
				content_index++;
				PeekMail_GetAccountDetail(account_content, &content_index, &account_detail->account_name, '\r');
			}
			else
			{
				PeekMail_GetAccountNextItemIndex(account_content, &content_index);
			}
			memset(temp, 0, sizeof(temp));
			temp_index = 0;
		}
		else if (!strcmp(temp, FIRST_NAME_STR))
		{	
			content_index++;
			PeekMail_GetAccountDetail(account_content, &content_index, &account_detail->first_name, '\r');
			memset(temp, 0, sizeof(temp));
			temp_index = 0;
		}
		else if (!strcmp(temp, LAST_NAME_STR))
		{
			content_index++;
			PeekMail_GetAccountDetail(account_content, &content_index, &account_detail->last_name, '\r');
			memset(temp, 0, sizeof(temp));
			temp_index = 0;
		}
		else if (!strcmp(temp, PSW_STR))
		{
			if (ALL_INFO == info_type)
			{
				content_index++;
				PeekMail_GetAccountDetail(account_content, &content_index, &account_detail->password, '\r');
			}
			else
			{
				PeekMail_GetAccountNextItemIndex(account_content, &content_index);
			}
			memset(temp, 0, sizeof(temp));
			temp_index = 0;
		}
		else if (!strcmp(temp, ADDRESS_STR))
		{
			if (ALL_INFO == info_type)
			{
				content_index++;
				PeekMail_GetAccountDetail(account_content, &content_index, &account_detail->address, '\r');
			}
			else
			{
				PeekMail_GetAccountNextItemIndex(account_content, &content_index);
			}
			memset(temp, 0, sizeof(temp));
			temp_index = 0;
		}
		else if (!strcmp(temp, SIGNATURE_STR))
		{
			content_index += 3;
			PeekMail_GetAccountDetail(account_content, &content_index, &account_detail->signature, '\0');
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

//flag == TRUE means account_detail was generated using malloc(), thus it need to be freed, otherwise ignore it
PUBLIC void PeekMail_DestroyAccountStruct(PEEKMAIL_ACCOUNT_STRUCT *account_detail, BOOLEAN flag)
{
	if(account_detail->file_name != PNULL) 
	{
		free(account_detail->file_name);
	}
	DestroyString(&account_detail->account_name);
	DestroyString(&account_detail->first_name);
	DestroyString(&account_detail->last_name);
	DestroyString(&account_detail->password);
	DestroyString(&account_detail->address);
	DestroyString(&account_detail->signature);
	
	if (flag) 
	{
		free(account_detail);
	}
}

