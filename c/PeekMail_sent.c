/*****************************************************************************
** File Name:      peekmail_sent.c                                               *
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

#include "mmk_type.h"
//#include "mmi_window.h"

#include "guifont.h"
#include "guilcd.h"
#include "guilistbox.h"

#include "PeekMail_text.h"
#include "PeekMail_image.h"
#include "PeekMail_id.h"
#include "PeekMail_menutable.h"
#include "PeekMail_sent.h"
#include "PeekMail_draft.h"
#include "PeekMail_get_mail_info.h"
#include "PeekMail_main.h"



/**--------------------------------------------------------------------------*/
/**                         MACRO DEFINITION                                 */
/**--------------------------------------------------------------------------*/

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

// Sent Box
WINDOW_TABLE(MMI_PEEK_MAIL_SENT_WIN_TAB) =
{
	WIN_ID(MMI_PEEK_MAIL_SENT_WIN_ID),
	WIN_FUNC((uint32)HandlePeekMailSentWinMsg),
	WIN_TITLE(TXT_PEEKMAIL_SENT_TITLE),
	CREATE_LISTBOX_CTRL(GUILIST_TEXTLIST_E, MMI_PEEK_MAIL_SENT_CTRL_ID),
	WIN_SOFTKEY(TXT_PEEKMAIL_MENU, TXT_PEEKMAIL_VIEW, TXT_PEEKMAIL_BACK),
	END_WIN
};

// Sent Menu (left softkey)
WINDOW_TABLE( MMI_PEEK_MAIL_SENT_MENU_TAB ) = 
{
	WIN_ID(MMI_PEEK_MAIL_SENT_MENU_WIN_ID),
    WIN_FUNC((uint32)HandlePeekMailSentMenuWinMsg),
    WIN_STYLE( WS_HAS_TRANSPARENT),
    CREATE_POPMENU_CTRL(MENU_PEEKMAIL_SENT_MENU, MMI_PEEK_MAIL_SENT_MENU_CTRL_ID),
    WIN_SOFTKEY(STXT_OK,TXT_NULL,STXT_RETURN),
    END_WIN
};

MMIPEEKMAIL_WINDOW_ID_E g_win_id_sent = MMI_PEEK_MAIL_SENT_WIN_ID;

/**--------------------------------------------------------------------------*
 **                         FUNCTION DEFINITION                              *
 **--------------------------------------------------------------------------*/
/*****************************************************************************/
//  Description : open hello peek windows
//  Global resource dependence : 
//  Author: Song,Han
//  Note: 
/*****************************************************************************/

LOCAL void AppendMailListItem_sent(
							  MMI_CTRL_ID_T    ctrl_id,
							  MMI_IMAGE_ID_T   image_id,
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

	item_data.item_content[0].item_data_type = GUIITEM_DATA_IMAGE_ID;
	item_data.item_content[0].item_data.image_id = image_id;

	item_data.item_content[1].item_data_type = GUIITEM_DATA_TEXT_ID;
	item_data.item_content[1].item_data.text_id = text_from_id;

	item_data.item_content[2].item_data_type = GUIITEM_DATA_TEXT_ID;
	item_data.item_content[2].item_data.text_id = text_time_id;

	item_data.item_content[3].item_data_type = GUIITEM_DATA_TEXT_ID;
	item_data.item_content[3].item_data.text_id = text_subject_id;

	//item_data.softkey_id[0] = left_softkey_id;
	//item_data.softkey_id[1] = middle_softkey_id;
	//item_data.softkey_id[2] = right_softkey_id;
	
	GUILIST_AppendItem(ctrl_id, &item_t);

	return;
}


LOCAL MMI_RESULT_E HandlePeekMailSentWinMsg(
                                         MMI_WIN_ID_T     win_id, 
                                         MMI_MESSAGE_ID_E msg_id, 
                                         DPARAM           param
                                         )
{
    MMI_RESULT_E        recode	 	 = MMI_RESULT_TRUE;
    GUI_LCD_DEV_INFO	lcd_dev_info = {GUI_LCD_0, GUI_BLOCK_0};
	MMI_CTRL_ID_T	  	ctrl_id		 = MMI_PEEK_MAIL_SENT_CTRL_ID;

	uint16				mail_num = 0;
	uint16				mail_index = 0;
	char 				*mail_file_name;
	uint16				file_name_len = 0;
	PEEKMAIL_MAIL_STRUCT mail_detail;

    lcd_dev_info.lcd_id		= GUI_MAIN_LCD_ID;
    lcd_dev_info.block_id	= GUI_BLOCK_MAIN;

    switch(msg_id)
    {
    case MSG_OPEN_WINDOW:	
		//mail_num = PeekMail_GetMailNum(SENT_INFO);
		MMK_SetAtvCtrl(win_id, ctrl_id);
		GUILIST_SetMaxItem(ctrl_id, 3, FALSE);
		GUILIST_SetNeedPrgbar(ctrl_id,TRUE);
		GUILIST_SetTitleIndexType(ctrl_id, GUILIST_TITLE_INDEX_DEFAULT);
		GUILIST_SetTextFont(ctrl_id, SONG_FONT_14, MMI_WHITE_COLOR);

		/*for (mail_index = mail_num; mail_index>0; mail_index--)
		{	
			mail_file_name = (char *)malloc(32 * sizeof(char)); 
			memset(mail_file_name, 0, sizeof(mail_file_name));
			sprintf(mail_file_name,  "%s%d", SENT_PATH, mail_index);
			memset(&mail_detail, 0, sizeof(mail_detail));
			PeekMail_GetMailStructure(mail_file_name, &mail_detail, GEN_LIST_INFO);

			if (0 == mail_detail.read_flag)
			{
				AppendMailListItem(ctrl_id, IMG_HELLOPEEK_MAIL_UNREAD_ICON, mail_detail.from, mail_detail.time, mail_detail.subject);
			}
			else
			{
				AppendMailListItem(ctrl_id, IMG_HELLOPEEK_MAIL_READ_ICON, mail_detail.from, mail_detail.time, mail_detail.subject);
			}
		}*/

		AppendMailListItem_sent(ctrl_id, IMG_PEEKMAIL_UNREAD_ICON, TXT_PEEKMAIL_EXAMPLE_FROM_1, TXT_PEEKMAIL_EXAMPLE_TIME_1, TXT_PEEKMAIL_EXAMPLE_SUBJ_1);
		AppendMailListItem_sent(ctrl_id, IMG_PEEKMAIL_STAR_ICON, TXT_PEEKMAIL_EXAMPLE_FROM_2, TXT_PEEKMAIL_EXAMPLE_TIME_2, TXT_PEEKMAIL_EXAMPLE_SUBJ_2);
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
        MMK_CreateWin((uint32 *)MMI_PEEK_MAIL_SENT_MENU_TAB, PNULL);
        break;

	case MSG_CTL_MIDSK:
	case MSG_CTL_PENOK:
		//MMI_CreatePeekMailViewWin(INBOX_PATH, MMI_PEEK_MAIL_SENT_CTRL_ID);
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


LOCAL MMI_RESULT_E HandlePeekMailSentMenuWinMsg(
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
		MMK_SetAtvCtrl(win_id, MMI_PEEK_MAIL_SENT_MENU_CTRL_ID);
		break;
		
	case MSG_CTL_PENOK:
	case MSG_CTL_OK:
	case MSG_APP_OK:
	case MSG_APP_WEB:
	case MSG_CTL_MIDSK:
		GUIMENU_GetId(MMI_PEEK_MAIL_SENT_MENU_CTRL_ID,&group_id,&menu_id);
		switch (menu_id)
		{
			case ID_PEEKMAIL_OPEN_MESSAGE:	
				//MMI_CreatePeekMailViewWin(INBOX_PATH, MMI_PEEK_MAIL_SENT_CTRL_ID);
				break;
			case ID_PEEKMAIL_COMPOSE:
				MMK_CloseWin(win_id);
				MMK_CloseWin(g_win_id_sent);
				MMI_CreatePeekMailComposerWin();
				break;	
			case ID_PEEKMAIL_REPLY:
				break;
			case ID_PEEKMAIL_REPLY_ALL:
				break;
			case ID_PEEKMAIL_FORWARD:
				break;
			case ID_PEEKMAIL_MARK_READ_UNREAD:
				break;
			case ID_PEEKMAIL_SAVE_MESSAGE:
				break;
			case ID_PEEKMAIL_DELETE_MESSAGE:
				break;
			case ID_PEEKMAIL_DELETE_ALL:
				break;
			case ID_PEEKMAIL_INBOX_FOLDER: // other than inbox
				MMK_CloseWin(win_id);
				MMK_CloseWin(g_win_id_sent);
				break;
			case ID_PEEKMAIL_MOVE_TO_INBOX_FOLDER:  // other than inbox
				break;
			case ID_PEEKMAIL_DRAFTS_FOLDER:
				MMK_CloseWin(win_id);
				MMK_CloseWin(g_win_id_sent);
				MMI_CreatePeekMailDraftWin();
				break;
			case ID_PEEKMAIL_SAVED_FOLDER:
				MMK_CloseWin(win_id);
				MMK_CloseWin(g_win_id_sent);
				MMI_CreatePeekMailSavedWin();
				break;
			case ID_PEEKMAIL_TRASH_FOLDER:
				MMK_CloseWin(win_id);
				MMK_CloseWin(g_win_id_sent);
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
		
		//MMK_CloseWin(win_id);
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
//  Description : open hello peek windows
//  Global resource dependence : 
//  Author: Song,Han
//  Note: 
/*****************************************************************************/
PUBLIC void MMI_CreatePeekMailSentWin(void)
{
	MMK_CreateWin((uint32*)MMI_PEEK_MAIL_SENT_WIN_TAB, PNULL);
}


