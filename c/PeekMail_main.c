/*****************************************************************************
** File Name:      peekmail_main.c                                               *
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

/**--------------------------------------------------------------------------*/
/**                         Include Files                                    */
/**--------------------------------------------------------------------------*/
#include <stdio.h>

#include "std_header.h"
#include "window_parse.h"
#include "mmidisplay_data.h"
#include "mmi_textfun.h"

#include "guifont.h"
#include "guilcd.h"
#include "guilistbox.h"
#include "guititle.h"


#include "PeekMail_main.h"
#include "PeekMail_text.h"
#include "PeekMail_image.h"
#include "PeekMail_id.h"
#include "PeekMail_menutable.h"
#include "PeekMail_sent.h"
#include "PeekMail_draft.h"
#include "PeekMail_view.h"

#include "HelloPeek_text.h"
#include "HelloPeek_image.h"




/**--------------------------------------------------------------------------*/
/**                         MACRO DEFINITION                                 */
/**--------------------------------------------------------------------------*/
#define INBOX_INFO 			"PeekMail\\Inbox\\dir.info"
#define INBOX_PATH 			"PeekMail\\Inbox\\"
#define MAX_PATH_LEN 		24
#define MAX_MAIL_SIZE 		2048
#define MAX_MAIL_ITEM_SIZE	2048
#define READ_STR			"read:"
#define DATE_STR			"date:"
#define TIME_STR			"time:"
#define FROM_STR			"from:"
#define TO_STR				"to:"
#define CC_STR				"cc:"
#define SUBJECT_STR			"subject:"
#define TEXT_STR			"text:"




/*----------------------------------------------------------------------------*/
/*                          TYPE AND STRUCT                                   */
/*----------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                          CONSTANT ARRAY                                   */
/*---------------------------------------------------------------------------*/

/**--------------------------------------------------------------------------*/
/**                         EXTERNAL DECLARE                                 */
/**--------------------------------------------------------------------------*/

/**--------------------------------------------------------------------------*/
/**                         STATIC DEFINITION                                */
/**--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                          LOCAL FUNCTION DECLARE                           */
/*---------------------------------------------------------------------------*/

/**--------------------------------------------------------------------------*/
/**                         GLOBAL DEFINITION                                */
/**--------------------------------------------------------------------------*/

//Inbox
WINDOW_TABLE(MMI_PEEK_MAIL_INBOX_WIN_TAB) =
{
	WIN_ID(MMI_PEEK_MAIL_INBOX_WIN_ID),
	WIN_FUNC((uint32)HandlePeekMailInboxWinMsg),
	WIN_TITLE(TXT_PEEKMAIL_INBOX_TITLE),
	//CREATE_MENU_CTRL(MENU_PEEKMAIL_INBOX_MENU, MMI_PEEK_MAIL_INBOX_MENU_CTRL_ID),
	CREATE_LISTBOX_CTRL(GUILIST_TEXTLIST_E, MMI_PEEK_MAIL_INBOX_CTRL_ID),
	WIN_SOFTKEY(TXT_PEEKMAIL_MENU, TXT_PEEKMAIL_VIEW, TXT_PEEKMAIL_BACK),
	END_WIN
};

// Inbox Menu (left softkey)
WINDOW_TABLE( MMI_PEEK_MAIL_INBOX_MENU_TAB ) = 
{
	WIN_ID(MMI_PEEK_MAIL_INBOX_MENU_WIN_ID),
    WIN_FUNC((uint32)HandlePeekMailInboxMenuWinMsg),
    WIN_STYLE( WS_HAS_TRANSPARENT),
    CREATE_POPMENU_CTRL(MENU_PEEKMAIL_INBOX_MENU,MMI_PEEK_MAIL_INBOX_MENU_CTRL_ID),
    WIN_SOFTKEY(STXT_OK,TXT_NULL,STXT_RETURN),
    END_WIN
};

MMI_HANDLE_T g_win_inbox;




/**--------------------------------------------------------------------------*
 **                         FUNCTION DEFINITION                              *
 **--------------------------------------------------------------------------*/
/*****************************************************************************/
//  Description : open hello peek windows
//  Global resource dependence : 
//  Author: Song,Han
//  Note: 
/*****************************************************************************/

LOCAL void AppendMailListItem(
							  MMI_CTRL_ID_T    ctrl_id,
							  MMI_IMAGE_ID_T   image_id,
							  /*MMI_STRING_T    text_from_id,
							  MMI_STRING_T    text_time_id,
							  MMI_STRING_T    text_subject_id 							  */
							  MMI_TEXT_ID_T    text_from_id,
							  MMI_TEXT_ID_T    text_time_id,
							  MMI_TEXT_ID_T    text_subject_id 							  
							  )
{
	GUILIST_ITEM_T			item_t	   = {0};
	GUILIST_ITEM_DATA_T 	item_data  = {0};
	uint32					item_index = 0;
	
	//item_t.item_style 	 = GUIITEM_STYLE_ONE_LINE_ICON_TEXT;
	item_t.item_style	 =GUIITEM_STYLE_TWO_LINE_ICON_TWO_TEXT_AND_TEXT;

	item_t.item_data_ptr = &item_data;
/*
	item_data.item_content[0].item_data_type = GUIITEM_DATA_IMAGE_ID;
	item_data.item_content[0].item_data.image_id = image_id;

	item_data.item_content[1].item_data_type = GUIITEM_DATA_TEXT_BUFFER;
	item_data.item_content[1].item_data.text_buffer = text_from_id;

	item_data.item_content[2].item_data_type = GUIITEM_DATA_TEXT_BUFFER;
	item_data.item_content[2].item_data.text_buffer = text_time_id;

	item_data.item_content[3].item_data_type = GUIITEM_DATA_TEXT_BUFFER;
	item_data.item_content[3].item_data.text_buffer = text_subject_id;
*/	

	item_data.item_content[0].item_data_type = GUIITEM_DATA_IMAGE_ID;
	item_data.item_content[0].item_data.image_id = image_id;

	item_data.item_content[1].item_data_type = GUIITEM_DATA_TEXT_ID;
	item_data.item_content[1].item_data.text_id= text_from_id;

	item_data.item_content[2].item_data_type = GUIITEM_DATA_TEXT_ID;
	item_data.item_content[2].item_data.text_id = text_time_id;

	item_data.item_content[3].item_data_type = GUIITEM_DATA_TEXT_ID;
	item_data.item_content[3].item_data.text_id = text_subject_id;


	GUILIST_AppendItem(ctrl_id, &item_t);

	return;
}


LOCAL uint16 PeekMail_GetMailNum()
{
	char				*buffer = PNULL;
	char 				filename[] = INBOX_INFO;
	DWORD				bufsize = 0;
	DWORD 				length = 0;
	DWORD 				buf_len = 0;
	uint16				mail_num = 0;

	HANDLE hFile = CreateFile(filename,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,0,0);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		return -1;
	}
	
	length = GetFileSize(hFile, 0);

	bufsize = length + 1;
	buffer = (char *)malloc(bufsize * sizeof(char));
	*(buffer + length) = 0;
	ReadFile(hFile, buffer, length, &buf_len, 0);
	CloseHandle(hFile);

	mail_num = (uint16)atoi(buffer);

	free(buffer);

	return mail_num;
}


LOCAL uint16 PeekMail_GetMailContent(char * file_name, uint16 file_name_len, char * content)
{
	char				*buffer = PNULL;
	char 				*filename = PNULL;
	DWORD				bufsize = 0;
	DWORD 				length = 0;
	DWORD 				buf_len = 0;
	uint16				mail_num = 0;
	HANDLE hFile = CreateFile(filename,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,0,0);

	filename = (char *)malloc(file_name_len * sizeof(char));
	memset(filename, 0, sizeof(filename));
	strcpy(filename, file_name);

	
	if (INVALID_HANDLE_VALUE == hFile)
	{
		free(filename);
		return -1;
	}
	
	length = GetFileSize(hFile, 0);

	bufsize = length + 1;
	buffer = (char *)malloc(bufsize * sizeof(char));
	*(buffer + length) = 0;
	ReadFile(hFile, buffer, length, &buf_len, 0);
	CloseHandle(hFile);

	strcpy(content, buffer);

	free(buffer);
	free(filename);

	return 1;
}


LOCAL uint16 PeekMail_GetMailDetail(char * mail_content, uint16 * content_index, MMI_STRING_T * detail_item)
{
	uint16 index = *content_index;
	uint16 temp_index = 0;
	char   temp[MAX_MAIL_ITEM_SIZE];
	
	memset(temp, 0, sizeof(temp));
	while ('\n' != mail_content[index])
	{
		temp[temp_index++] = mail_content[index++];
	}
	*content_index = index + 1;

	detail_item = (MMI_STRING_T *)malloc(sizeof(MMI_STRING_T));
	detail_item->wstr_ptr = (wchar *)malloc((temp_index+1) * sizeof(wchar));
	MMIAPICOM_StrToWstr(temp, detail_item->wstr_ptr);
	detail_item->wstr_len = MMIAPICOM_Wstrlen(detail_item->wstr_ptr);
}

LOCAL void PeekMail_GetMailStructure(char * mail_content, PEEKMAIL_MAIL_STRUCT *mail_detail)
{
	uint16 content_index = 0;
	uint16 temp_index = 0;
	uint16 index = 0;
	uint16 content_size = sizeof(mail_content);
	char   temp[MAX_MAIL_ITEM_SIZE];
	char   read_flag = '0';

	memset(temp, 0, sizeof(temp));

	for (content_index=0; content_index<content_size; content_index++)
	{
		temp[temp_index] = mail_content[content_index];

		if (!strcmp(temp, READ_STR))
		{
			mail_detail->read_flag = atoi(mail_content[++content_index]);
			memset(temp, 0, sizeof(temp));
			mail_content++;
			temp_index = 0;
		}
		else if (!strcmp(temp, DATE_STR))
		{
			content_index++;
			PeekMail_GetMailDetail(mail_content, &content_index, mail_detail->date);
			memset(temp, 0, sizeof(temp));
			temp_index = 0;
		}
		else if (!strcmp(temp, TIME_STR))
		{
			content_index++;
			PeekMail_GetMailDetail(mail_content, &content_index, mail_detail->time);
			memset(temp, 0, sizeof(temp));
			temp_index = 0;
		}
		else if (!strcmp(temp, FROM_STR))
		{
			content_index++;
			PeekMail_GetMailDetail(mail_content, &content_index, mail_detail->from);
			memset(temp, 0, sizeof(temp));
			temp_index = 0;
		}
		else if (!strcmp(temp, TO_STR))
		{
			content_index++;
			PeekMail_GetMailDetail(mail_content, &content_index, mail_detail->to);
			memset(temp, 0, sizeof(temp));
			temp_index = 0;
		}
		else if (!strcmp(temp, CC_STR))
		{
			content_index++;
			PeekMail_GetMailDetail(mail_content, &content_index, mail_detail->cc);
			memset(temp, 0, sizeof(temp));
			temp_index = 0;
		}
		else if (!strcmp(temp, SUBJECT_STR))
		{
			content_index++;
			PeekMail_GetMailDetail(mail_content, &content_index, mail_detail->subject);
			memset(temp, 0, sizeof(temp));
			temp_index = 0;
		}
		else if (!strcmp(temp, TEXT_STR))
		{
			content_index++;
			PeekMail_GetMailDetail(mail_content, &content_index, mail_detail->text);
			memset(temp, 0, sizeof(temp));
			temp_index = 0;
		}

	}
	
}

LOCAL MMI_RESULT_E HandlePeekMailInboxWinMsg(
                                         MMI_WIN_ID_T     win_id, 
                                         MMI_MESSAGE_ID_E msg_id, 
                                         DPARAM           param
                                         )
{
    MMI_RESULT_E        recode	 	 = MMI_RESULT_TRUE;
    GUI_LCD_DEV_INFO	lcd_dev_info = {GUI_LCD_0, GUI_BLOCK_0};
	MMI_CTRL_ID_T	  	ctrl_id		 = MMI_PEEK_MAIL_INBOX_CTRL_ID;

	LOCAL const wchar 	wch_sub[]	= L"Peek";

	GUI_RECT_T			sub_text_rect = {200,10,239,30};
	GUI_FONT_T			sub_text_font = CAF_FONT_14;

	uint16				mail_num = 0;
	uint16				mail_index = 0;
	char 				*mail_file_name;
	char				*mail_content;
	uint16				file_name_len = 0;
	PEEKMAIL_MAIL_STRUCT mail_detail;


    lcd_dev_info.lcd_id		= GUI_MAIN_LCD_ID;
    lcd_dev_info.block_id	= GUI_BLOCK_MAIN;


    switch(msg_id)
    {
    case MSG_OPEN_WINDOW:
		mail_num = PeekMail_GetMailNum();
		MMK_SetAtvCtrl(win_id, ctrl_id);
		GUILIST_SetMaxItem(ctrl_id, 10, FALSE);
		GUILIST_SetNeedPrgbar(ctrl_id,TRUE);
		GUILIST_SetTitleIndexType(ctrl_id, GUILIST_TITLE_INDEX_DEFAULT);
		GUILIST_SetTextFont(ctrl_id, SONG_FONT_14, MMI_WHITE_COLOR);
		/*for (mail_index=mail_num; mail_index>0; mail_index--)
		{
			file_name_len = sprintf(NULL,  "%s%d", INBOX_PATH, mail_index);
			mail_file_name = (char *)malloc((file_name_len+1) * sizeof(char));
			memset(mail_file_name, 0, sizeof(mail_file_name));
			sprintf(mail_file_name, "%s%d",INBOX_PATH,mail_index);
			mail_content = (char *)malloc(MAX_MAIL_SIZE * sizeof(char));
			memset(mail_content, 0, sizeof(mail_content));
			PeekMail_GetMailContent(mail_file_name, file_name_len+1, mail_content);
			memset(&mail_detail, 0, sizeof(mail_detail));
			PeekMail_GetMailStructure(mail_content, &mail_detail);

			if (0 == mail_detail.read_flag)
			{
				AppendMailListItem(ctrl_id, IMG_HELLOPEEK_MAIL_UNREAD_ICON, mail_detail.from, mail_detail.time, mail_detail.subject);
			}
			else
			{
				AppendMailListItem(ctrl_id, IMG_HELLOPEEK_MAIL_READ_ICON, mail_detail.from, mail_detail.time, mail_detail.subject);
			}
		}*/

		AppendMailListItem(ctrl_id, IMG_HELLOPEEK_MAIL_UNREAD_ICON, TXT_HELLOPEEK_DEMO_LIST_BOX_MAIL_EXAMPLE_FROM_1, TXT_HELLOPEEK_DEMO_LIST_BOX_MAIL_EXAMPLE_TIME_1, TXT_HELLOPEEK_DEMO_LIST_BOX_MAIL_EXAMPLE_SUBJ_1);
		AppendMailListItem(ctrl_id, IMG_HELLOPEEK_MAIL_READ_ICON, TXT_HELLOPEEK_DEMO_LIST_BOX_MAIL_EXAMPLE_FROM_2, TXT_HELLOPEEK_DEMO_LIST_BOX_MAIL_EXAMPLE_TIME_2, TXT_HELLOPEEK_DEMO_LIST_BOX_MAIL_EXAMPLE_SUBJ_2);
		AppendMailListItem(ctrl_id, IMG_HELLOPEEK_MAIL_STARRED_ICON, TXT_HELLOPEEK_DEMO_LIST_BOX_MAIL_EXAMPLE_FROM_3, TXT_HELLOPEEK_DEMO_LIST_BOX_MAIL_EXAMPLE_TIME_3, TXT_HELLOPEEK_DEMO_LIST_BOX_MAIL_EXAMPLE_SUBJ_3);
		AppendMailListItem(ctrl_id, IMG_HELLOPEEK_MAIL_UNREAD_ICON, TXT_HELLOPEEK_DEMO_LIST_BOX_MAIL_EXAMPLE_FROM_1, TXT_HELLOPEEK_DEMO_LIST_BOX_MAIL_EXAMPLE_TIME_1, TXT_HELLOPEEK_DEMO_LIST_BOX_MAIL_EXAMPLE_SUBJ_1);
		AppendMailListItem(ctrl_id, IMG_HELLOPEEK_MAIL_READ_ICON, TXT_HELLOPEEK_DEMO_LIST_BOX_MAIL_EXAMPLE_FROM_2, TXT_HELLOPEEK_DEMO_LIST_BOX_MAIL_EXAMPLE_TIME_2, TXT_HELLOPEEK_DEMO_LIST_BOX_MAIL_EXAMPLE_SUBJ_2);
		AppendMailListItem(ctrl_id, IMG_HELLOPEEK_MAIL_STARRED_ICON, TXT_HELLOPEEK_DEMO_LIST_BOX_MAIL_EXAMPLE_FROM_3, TXT_HELLOPEEK_DEMO_LIST_BOX_MAIL_EXAMPLE_TIME_3, TXT_HELLOPEEK_DEMO_LIST_BOX_MAIL_EXAMPLE_SUBJ_3);
		AppendMailListItem(ctrl_id, IMG_HELLOPEEK_MAIL_READ_ICON, TXT_HELLOPEEK_DEMO_LIST_BOX_MAIL_EXAMPLE_FROM_2, TXT_HELLOPEEK_DEMO_LIST_BOX_MAIL_EXAMPLE_TIME_2, TXT_HELLOPEEK_DEMO_LIST_BOX_MAIL_EXAMPLE_SUBJ_2);
		AppendMailListItem(ctrl_id, IMG_HELLOPEEK_MAIL_STARRED_ICON, TXT_HELLOPEEK_DEMO_LIST_BOX_MAIL_EXAMPLE_FROM_3, TXT_HELLOPEEK_DEMO_LIST_BOX_MAIL_EXAMPLE_TIME_3, TXT_HELLOPEEK_DEMO_LIST_BOX_MAIL_EXAMPLE_SUBJ_3);

		GUITITLE_SetSubText(g_win_inbox,MMI_PEEK_MAIL_INBOX_MENU_CTRL_ID,TRUE, wch_sub,MMIAPICOM_Wstrlen(wch_sub),FALSE);
		GUITITLE_SetSubTextParam(g_win_inbox, MMI_PEEK_MAIL_INBOX_MENU_CTRL_ID, &sub_text_rect, &sub_text_font, ALIGN_RIGHT);
		break;

    case MSG_GET_FOCUS:
        break;

    case MSG_LOSE_FOCUS:
        break;

    case MSG_FULL_PAINT:
        break;

    //case MSG_KEYDOWN_CANCEL:
    case MSG_CTL_CANCEL:
        MMK_CloseWin(win_id);
        break;

	/********************************
	* MSG_CTL_OK: is the left softkey      **
	* MSG_CTL_MIDSK: is the middle one **
	*********************************/

	case MSG_CTL_OK:
        MMK_CreateWin((uint32 *)MMI_PEEK_MAIL_INBOX_MENU_TAB, PNULL);
        break;

	case MSG_CTL_MIDSK:
	case MSG_CTL_PENOK:
		MMI_CreatePeekMailViewWin();
		break;
		
    case MSG_APP_OK:
        break;
		
    case MSG_CLOSE_WINDOW:
        break;

    default:
        break;
    }

    return recode;
}


LOCAL int16 PeekMail_MarkRead(int8 *filename)
{
	HANDLE hFile = CreateFile(filename,
							GENERIC_ALL,
							FILE_SHARE_READ,
							0,
							OPEN_EXISTING,
							0,
							0);
	HANDLE hOutFile;

	int8 buffer[6] = {0};
	int16 read_len = 6;
	int16 buf_len = 0;
	int16 index = GUILIST_GetCurItemIndex(MMI_PEEK_MAIL_INBOX_CTRL_ID);
	GUILIST_ITEM_T *curItem = GUILIST_GetItemPtrByIndex(MMI_PEEK_MAIL_INBOX_CTRL_ID, index);

	if (hFile == INVALID_HANDLE_VALUE)
		return -1;
	ReadFile(hFile, buffer, read_len, &buf_len, 0);
	CloseHandle(hFile);
	hOutFile = CreateFile(filename,
						GENERIC_ALL,
						FILE_SHARE_READ,
						0,
						OPEN_EXISTING,
						0,
						0);
	if (buffer[5] == '0') {
		buffer[5] = '1';
		curItem->item_data_ptr->item_content[0].item_data.image_id = IMG_HELLOPEEK_MAIL_READ_ICON;		
	} else if (buffer[5] == '1') {
		buffer[5] = '0';
		curItem->item_data_ptr->item_content[0].item_data.image_id = IMG_HELLOPEEK_MAIL_UNREAD_ICON;
	}
	WriteFile(hOutFile, buffer, buf_len, &buf_len, 0);
	CloseHandle(hOutFile);
}


LOCAL MMI_RESULT_E HandlePeekMailInboxMenuWinMsg(
                                         MMI_WIN_ID_T     	win_id, 
                                         MMI_MESSAGE_ID_E    msg_id, 
                                         DPARAM              param
                                         )
{
	MMI_RESULT_E recode = MMI_RESULT_TRUE;
	MMI_MENU_GROUP_ID_T group_id = 0;
	MMI_MENU_ID_T menu_id = 0;


	switch(msg_id)
	{
	case MSG_OPEN_WINDOW:
		MMK_SetAtvCtrl(win_id, MMI_PEEK_MAIL_INBOX_MENU_CTRL_ID);
		break;
		
	case MSG_CTL_PENOK:
	case MSG_CTL_OK:
	case MSG_APP_OK:
	case MSG_APP_WEB:
	case MSG_CTL_MIDSK:
		GUIMENU_GetId(MMI_PEEK_MAIL_INBOX_MENU_CTRL_ID,&group_id,&menu_id);
		switch (menu_id)
		{
			case ID_PEEKMAIL_OPEN_MESSAGE:
				MMI_CreatePeekMailViewWin();
				break;

			case ID_PEEKMAIL_COMPOSE:
				MMI_CreatePeekMailComposerWin();
				break;
			
			case ID_PEEKMAIL_REPLY:
				break;
			case ID_PEEKMAIL_REPLY_ALL:
				break;
			case ID_PEEKMAIL_FORWARD:
				break;
			case ID_PEEKMAIL_MARK_READ_UNREAD:
				{
					int8 *filename;
					int8 fileIndexBuffer[6] = {0};
					uint16 fileIndex = GUILIST_GetTotalItemNum(MMI_PEEK_MAIL_INBOX_CTRL_ID)
									- GUILIST_GetCurItemIndex(MMI_PEEK_MAIL_INBOX_CTRL_ID);
					MMIAPICOM_Int2Str(fileIndex, fileIndexBuffer, 6);
					filename = (int8 *)malloc(sizeof(INBOX_PATH) + strlen(fileIndexBuffer) * sizeof(int8));
					strcpy(filename, INBOX_PATH);
					strcat(filename, fileIndexBuffer);
					PeekMail_MarkRead(filename);
				}
				break;
			case ID_PEEKMAIL_SAVE_MESSAGE:
				break;
			case ID_PEEKMAIL_DELETE_MESSAGE:
				break;
			case ID_PEEKMAIL_DELETE_ALL:
				break;
			case ID_PEEKMAIL_SENT_FOLDER:
				MMI_CreatePeekMailSentWin();
				break;
			case ID_PEEKMAIL_DRAFTS_FOLDER:
				MMI_CreatePeekMailDraftWin();
				break;
			case ID_PEEKMAIL_SAVED_FOLDER:
				MMI_CreatePeekMailSavedWin();
				break;
			case ID_PEEKMAIL_TRASH_FOLDER:
				MMI_CreatePeekMailTrashWin();
				break;
			case ID_PEEKMAIL_SEARCH_THIS_FOLDER:
				break;
			case ID_PEEKMAIL_CONTACTS:
				break;
			case ID_PEEKMAIL_PEEKMAIL_MANAGER:
				break;
			case ID_PEEKMAIL_EXIT:
				break;		
			default:
				break;
		}
		
		MMK_CloseWin(win_id);
		break;
		
	case MSG_CTL_CANCEL:
	case MSG_APP_CANCEL:
		MMK_CloseWin(win_id);
		break;
		
	default:
		recode = MMI_RESULT_FALSE;
		break;
	}
	return recode;
}



/*****************************************************************************/
// 	Description : Register hello menu group
//	Global resource dependence : none
//  Author: Song,Han
//	Note:
/*****************************************************************************/
PUBLIC void MMIAPIPEEKMAIL_InitModule(void)
{
    MMIPEEKMAIL_RegMenuGroup();
}


/*****************************************************************************/
//  Description : open hello peek windows
//  Global resource dependence : 
//  Author: Song,Han
//  Note: 
/*****************************************************************************/
PUBLIC void MMI_CreatePeekMailWin(void)
{
   g_win_inbox = MMK_CreateWin((uint32*)MMI_PEEK_MAIL_INBOX_WIN_TAB, PNULL);
}
