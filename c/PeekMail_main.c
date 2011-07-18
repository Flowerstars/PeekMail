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
#include "std_header.h"
#include "window_parse.h"
#include "mmidisplay_data.h"
#include "mmi_textfun.h"
#include "mmipub.h"

#include "guifont.h"
#include "guilcd.h"
#include "guilistbox.h"
#include "guititle.h"


#include "PeekMail_get_mail_info.h"
#include "PeekMail_main.h"
#include "PeekMail_text.h"
#include "PeekMail_image.h"
#include "PeekMail_id.h"
#include "PeekMail_menutable.h"
#include "PeekMail_sent.h"
#include "PeekMail_draft.h"
#include "PeekMail_view.h"
#include "PeekMail_search.h"
#include "PeekMail_demo.h"



/**--------------------------------------------------------------------------*/
/**                         MACRO DEFINITION                                 */
/**--------------------------------------------------------------------------*/
#define MAX_PATH_LEN 			24
#define REFRESH_TIMMER			60000
#define QUERY_WIN_DELETE_ONE 	1
#define QUERY_WIN_DELETE_ALL 	2

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
uint8		 g_query_win_id = 0;
uint16 		 g_inbox_info[] = L"PeekMail\\Inbox\\dir.info";



/**--------------------------------------------------------------------------*
 **                         FUNCTION DEFINITION                              *
 **--------------------------------------------------------------------------*/
/*****************************************************************************/
//  Description : open hello peek windows
//  Global resource dependence : 
//  Author: Song,Han
//  Note: 
/*****************************************************************************/

PUBLIC void AppendMailListItem(
							  MMI_CTRL_ID_T    ctrl_id,
							  MMI_IMAGE_ID_T   image_id,
							  MMI_STRING_T *   text_from_id,
							  MMI_STRING_T  *  text_time_id,
							  MMI_STRING_T  *  text_subject_id
							  /*MMI_TEXT_ID_T    text_from_id,
							  MMI_TEXT_ID_T    text_time_id,
							  MMI_TEXT_ID_T    text_subject_id*/						  
							  )
{
	GUILIST_ITEM_T			item_t	   = {0};
	GUILIST_ITEM_DATA_T 	item_data  = {0};
	uint32					item_index = 0;
	
	//item_t.item_style 	 = GUIITEM_STYLE_ONE_LINE_ICON_TEXT;
	item_t.item_style	 =GUIITEM_STYLE_TWO_LINE_ICON_TWO_TEXT_AND_TEXT;

	item_t.item_data_ptr = &item_data;

	item_data.item_content[0].item_data_type = GUIITEM_DATA_IMAGE_ID;
	item_data.item_content[0].item_data.image_id = image_id;

	item_data.item_content[1].item_data_type = GUIITEM_DATA_TEXT_BUFFER;
	item_data.item_content[1].item_data.text_buffer = *text_from_id;

	item_data.item_content[2].item_data_type = GUIITEM_DATA_TEXT_BUFFER;
	item_data.item_content[2].item_data.text_buffer = *text_time_id;

	item_data.item_content[3].item_data_type = GUIITEM_DATA_TEXT_BUFFER;
	item_data.item_content[3].item_data.text_buffer = *text_subject_id;


	GUILIST_AppendItem(ctrl_id, &item_t);

	return;
}


LOCAL void GenerateInboxMailList(MMI_WIN_ID_T win_id, MMI_CTRL_ID_T ctrl_id)
{
	uint16					mail_num 		= 0;
	uint16					mail_index 		= 0;
	char* 					mail_file_name	= PNULL;
	uint16					file_name_len 	= 0;
	PEEKMAIL_MAIL_STRUCT 	mail_detail		= {0};

	
	mail_num = PeekMail_GetMailNum(INBOX_INFO);
	MMK_SetAtvCtrl(win_id, ctrl_id);
	GUILIST_SetMaxItem(ctrl_id, 50, FALSE);
	GUILIST_SetNeedPrgbar(ctrl_id,TRUE);
	GUILIST_SetTitleIndexType(ctrl_id, GUILIST_TITLE_INDEX_DEFAULT);
	GUILIST_SetTextFont(ctrl_id, SONG_FONT_14, MMI_WHITE_COLOR);
	for (mail_index = mail_num; mail_index>0; mail_index--)
	{	
		mail_file_name = (char *)malloc(32 * sizeof(char)); 
		memset(mail_file_name, 0, sizeof(mail_file_name));
		sprintf(mail_file_name,  "%s%d", INBOX_PATH, mail_index);
		memset(&mail_detail, 0, sizeof(mail_detail));
		PeekMail_GetMailStructure(mail_file_name, &mail_detail, GEN_LIST_INFO);

		if (0 == mail_detail.read_flag)
		{
			AppendMailListItem(ctrl_id, IMG_PEEKMAIL_UNREAD_ICON, mail_detail.from, mail_detail.time, mail_detail.subject);
		}
		else
		{
			AppendMailListItem(ctrl_id, IMG_PEEKMAIL_READ_ICON, mail_detail.from, mail_detail.time, mail_detail.subject);
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

	uint8 				refresh_timer_id = 0;

	uint16 				mail_index = 0;


    lcd_dev_info.lcd_id		= GUI_MAIN_LCD_ID;
    lcd_dev_info.block_id	= GUI_BLOCK_MAIN;

    switch(msg_id)
    {
    case MSG_OPEN_WINDOW:
		PeekMailDemoGenerate(INBOX_INFO);
		GenerateInboxMailList(win_id, ctrl_id);
		//refresh_timer_id = MMK_CreateWinTimer(g_win_inbox, REFRESH_TIMMER, TRUE);
		break;
/*
	case MSG_TIMER:
		mail_index = GUILIST_GetCurItemIndex(ctrl_id);
		GUILIST_RemoveAllItems(ctrl_id);
		GenerateInboxMailList(win_id, ctrl_id);
		GUILIST_SetSelectedItem(ctrl_id, mail_index, TRUE);
		MMK_UpdateScreen();
		break;
*/
    case MSG_GET_FOCUS:
        break;

    case MSG_LOSE_FOCUS:
        break;

    case MSG_FULL_PAINT:
        break;

    case MSG_KEYDOWN_RIGHT:
		break;

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
		MMI_CreatePeekMailViewWin(INBOX_PATH, MMI_PEEK_MAIL_INBOX_CTRL_ID);
		break;
		
    case MSG_APP_OK:
        break;

	case MSG_PROMPTWIN_OK:
	{
		uint16 		 time_period 		= 1000;
		wchar		 wch_delete_one[]  	= L"Delete Successfully!";
		wchar		 wch_delete_all[]  	= L"Delete All Successfully!";
		MMI_STRING_T str_delete 		= {0};
		
		MMIPUB_CloseQuerytWin(PNULL);
		
		switch (g_query_win_id)
		{
			case QUERY_WIN_DELETE_ONE:
				str_delete.wstr_ptr = &wch_delete_one;
				str_delete.wstr_len = MMIAPICOM_Wstrlen(wch_delete_one);
				break;
			case QUERY_WIN_DELETE_ALL:
				str_delete.wstr_ptr = &wch_delete_all;
				str_delete.wstr_len = MMIAPICOM_Wstrlen(wch_delete_all);
				break;
			default:
				break;
		}
		
		MMIPUB_OpenAlertWinByTextPtr(&time_period,&str_delete,PNULL,IMAGE_PUBWIN_SUCCESS,PNULL,PNULL,MMIPUB_SOFTKEY_ONE,PNULL);
		break;
	}
	
	case MSG_PROMPTWIN_CANCEL: 
		MMIPUB_CloseQuerytWin(PNULL);
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
	MMIFILE_HANDLE hFile = PNULL; 
	MMIFILE_HANDLE hOutFile = PNULL;
	wchar unicode_file_name[256];

	int8 buffer[6] = {0};
	int16 read_len = 6;
	int16 buf_len = 0;
	int16 index = GUILIST_GetCurItemIndex(MMI_PEEK_MAIL_INBOX_CTRL_ID);
	GUILIST_ITEM_T *curItem = GUILIST_GetItemPtrByIndex(MMI_PEEK_MAIL_INBOX_CTRL_ID, index);

	MMIAPICOM_StrToWstr(filename, unicode_file_name);
	hFile = MMIFILE_CreateFile(
				unicode_file_name,
				SFS_MODE_READ | SFS_MODE_OPEN_EXISTING,
				PNULL,
				PNULL);
	if (hFile == SFS_INVALID_HANDLE) {
		return -1;
	}
	MMIFILE_ReadFile(hFile, buffer, read_len, &buf_len, PNULL);
	MMIFILE_CloseFile(hFile);
	hOutFile = MMIFILE_CreateFile(
				unicode_file_name,
				SFS_MODE_WRITE | SFS_MODE_OPEN_EXISTING,
				PNULL,
				PNULL);
	if (hOutFile == SFS_INVALID_HANDLE) {
		return;
	}
	if (buffer[5] == '0') {
		buffer[5] = '1';
		curItem->item_data_ptr->item_content[0].item_data.image_id = IMG_PEEKMAIL_READ_ICON;		
	} else if (buffer[5] == '1') {
		buffer[5] = '0';
		curItem->item_data_ptr->item_content[0].item_data.image_id = IMG_PEEKMAIL_UNREAD_ICON;
	}
	MMIFILE_WriteFile(hOutFile, buffer, read_len, &buf_len, PNULL);
	MMIFILE_CloseFile(hOutFile);
	return 1;
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
				MMI_CreatePeekMailViewWin(INBOX_PATH, MMI_PEEK_MAIL_INBOX_CTRL_ID);
				break;

			case ID_PEEKMAIL_COMPOSE:
				MMI_CreatePeekMailComposerWin();
				break;
			
			case ID_PEEKMAIL_REPLY:
				{					
					int8 *filename;
					int8 fileIndexBuffer[8] = {0};
					uint16 fileIndex = GUILIST_GetTotalItemNum(MMI_PEEK_MAIL_INBOX_CTRL_ID)
									- GUILIST_GetCurItemIndex(MMI_PEEK_MAIL_INBOX_CTRL_ID);
					MMIAPICOM_Int2Str(fileIndex, fileIndexBuffer, 8);
					filename = (int8 *)malloc((strlen(INBOX_PATH) + strlen(fileIndexBuffer)+1) * sizeof(int8));
					sprintf(filename,  "%s%d", INBOX_PATH, fileIndex);
					MMI_CreatePeekMailReplyWin(filename);					
					free(filename);
				}
				break;
			case ID_PEEKMAIL_REPLY_ALL:
				{					
					int8 *filename;
					int8 fileIndexBuffer[8] = {0};
					uint16 fileIndex = GUILIST_GetTotalItemNum(MMI_PEEK_MAIL_INBOX_CTRL_ID)
									- GUILIST_GetCurItemIndex(MMI_PEEK_MAIL_INBOX_CTRL_ID);
					MMIAPICOM_Int2Str(fileIndex, fileIndexBuffer, 8);
					filename = (int8 *)malloc((strlen(INBOX_PATH) + strlen(fileIndexBuffer)+1) * sizeof(int8));
					sprintf(filename,  "%s%d", INBOX_PATH, fileIndex);
					MMI_CreatePeekMailReplyAllWin(filename);
					free(filename);
				}
				break;
			case ID_PEEKMAIL_FORWARD:
				{					
					int8 *filename;
					int8 fileIndexBuffer[8] = {0};
					uint32 fileIndex = GUILIST_GetTotalItemNum(MMI_PEEK_MAIL_INBOX_CTRL_ID)
									- GUILIST_GetCurItemIndex(MMI_PEEK_MAIL_INBOX_CTRL_ID);
					
					MMIAPICOM_Int2Str(fileIndex, fileIndexBuffer, 8);
					filename = (uint8 *)malloc((strlen(INBOX_PATH)+strlen(fileIndexBuffer)+1) * sizeof(uint8)); 
					//memset(filename, 0, strlen(filename));
					sprintf(filename,  "%s%d", INBOX_PATH, fileIndex);
					MMI_CreatePeekMailForwardWin(filename);
					free(filename);
				}
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
			//	GUILIST_RemoveAllItems(MMI_PEEK_MAIL_INBOX_CTRL_ID);				
			//	GenerateInboxMailList(MMI_PEEK_MAIL_INBOX_WIN_ID, MMI_PEEK_MAIL_INBOX_CTRL_ID);
			{
				uint16 		 time_period 		= 1000;
				wchar		 wch_save_mail[]  	= L"The mail has been saved.";
				MMI_STRING_T str_save_mail 	= {0};

				str_save_mail.wstr_ptr = &wch_save_mail;
				str_save_mail.wstr_len = MMIAPICOM_Wstrlen(wch_save_mail);

				MMIPUB_OpenAlertWinByTextPtr(&time_period,&str_save_mail,PNULL,IMAGE_PUBWIN_SUCCESS,PNULL,PNULL,MMIPUB_SOFTKEY_ONE,PNULL);
				break;
			}
			case ID_PEEKMAIL_DELETE_MESSAGE:
			{
				uint32		 time_period = 1000;
				wchar		 wch_delete[]  = L"Are you sure to delete the mail?";
				MMI_STRING_T str_delete = {0};

				str_delete.wstr_ptr = &wch_delete;
				str_delete.wstr_len = MMIAPICOM_Wstrlen(wch_delete);
				
				MMIPUB_OpenQueryWinByTextPtr(&str_delete, PNULL,IMAGE_PUBWIN_QUERY, PNULL, PNULL);
				g_query_win_id = QUERY_WIN_DELETE_ONE;
				break;
			}
			case ID_PEEKMAIL_DELETE_ALL:
			{
				uint16 		 time_period = 1000;
				wchar		 wch_delete_all[]  = L"Are you sure to delete all mails?";
				MMI_STRING_T str_delete_all = {0};

				str_delete_all.wstr_ptr = &wch_delete_all;
				str_delete_all.wstr_len = MMIAPICOM_Wstrlen(wch_delete_all);

				MMIPUB_OpenQueryWinByTextPtr(&str_delete_all, PNULL,IMAGE_PUBWIN_QUERY, PNULL, PNULL);
				g_query_win_id = QUERY_WIN_DELETE_ALL;
				break;
			}
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
				MMI_CreatePeekMailSearchWin();
				break;
			case ID_PEEKMAIL_CONTACTS:
				MMI_CreatePeekContactWin();
				break;
			case ID_PEEKMAIL_PEEKMAIL_MANAGER:
				MMI_CreatePeekMailManagerWin();
				break;
			case ID_PEEKMAIL_EXIT:
				MMK_CloseWin(win_id);
				MMK_CloseWin(MMI_PEEK_MAIL_INBOX_WIN_ID);
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
