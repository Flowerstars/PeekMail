/*****************************************************************************
** File Name:      peekmail_trash.c                                               *
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

#include "guifont.h"
#include "guilcd.h"
#include "guilistbox.h"

#include "PeekMail_main.h"
#include "PeekMail_text.h"
#include "PeekMail_image.h"
#include "PeekMail_id.h"
#include "PeekMail_menutable.h"
#include "PeekMail_sent.h"
#include "PeekMail_saved.h"
#include "PeekMail_draft.h"
#include "PeekMail_Trash.h"

#include "HelloPeek_text.h"
#include "HelloPeek_image.h"

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

// Trash Box
WINDOW_TABLE(MMI_PEEK_MAIL_TRASH_WIN_TAB) =
{
	WIN_ID(MMI_PEEK_MAIL_TRASH_WIN_ID),
	WIN_FUNC((uint32)HandlePeekMailTrashWinMsg),
	WIN_TITLE(TXT_PEEKMAIL_TRASH_TITLE),
	CREATE_LISTBOX_CTRL(GUILIST_TEXTLIST_E, MMI_PEEK_MAIL_TRASH_CTRL_ID),
	WIN_SOFTKEY(TXT_PEEKMAIL_MENU, TXT_PEEKMAIL_VIEW, TXT_PEEKMAIL_BACK),
	END_WIN
};

// Trash Menu (left softkey)
WINDOW_TABLE( MMI_PEEK_MAIL_TRASH_MENU_TAB ) = 
{
	WIN_ID(MMI_PEEK_MAIL_TRASH_MENU_WIN_ID),
    WIN_FUNC((uint32)HandlePeekMailTrashMenuWinMsg),
    WIN_STYLE(WS_HAS_TRANSPARENT),
    CREATE_POPMENU_CTRL(MENU_PEEKMAIL_TRASH_MENU, MMI_PEEK_MAIL_TRASH_MENU_CTRL_ID),
    WIN_SOFTKEY(STXT_OK,TXT_NULL,STXT_RETURN),
    END_WIN
};

MMIPEEKMAIL_WINDOW_ID_E g_win_id_trash = MMI_PEEK_MAIL_TRASH_WIN_ID;


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
							  MMI_TEXT_ID_T    text_from_id,
							  MMI_TEXT_ID_T    text_time_id,
							  MMI_TEXT_ID_T    text_subject_id
							  //MMI_TEXT_ID_T    left_softkey_id,
							  //MMI_TEXT_ID_T    middle_softkey_id,
							  //MMI_TEXT_ID_T    right_softkey_id
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


LOCAL MMI_RESULT_E HandlePeekMailTrashWinMsg(
                                         MMI_WIN_ID_T     win_id, 
                                         MMI_MESSAGE_ID_E msg_id, 
                                         DPARAM           param
                                         )
{
    MMI_RESULT_E        recode	 	 = MMI_RESULT_TRUE;
    GUI_LCD_DEV_INFO	lcd_dev_info = {GUI_LCD_0, GUI_BLOCK_0};
	MMI_CTRL_ID_T	  	ctrl_id		 = MMI_PEEK_MAIL_TRASH_CTRL_ID;

    lcd_dev_info.lcd_id		= GUI_MAIN_LCD_ID;
    lcd_dev_info.block_id	= GUI_BLOCK_MAIN;

    switch(msg_id)
    {
    case MSG_OPEN_WINDOW:	
		MMK_SetAtvCtrl(win_id, ctrl_id);
		GUILIST_SetMaxItem(ctrl_id, 3, FALSE);
		GUILIST_SetNeedPrgbar(ctrl_id,TRUE);
		GUILIST_SetTitleIndexType(ctrl_id, GUILIST_TITLE_INDEX_DEFAULT);
		GUILIST_SetTextFont(ctrl_id, SONG_FONT_14, MMI_WHITE_COLOR);
		AppendMailListItem(ctrl_id, IMG_HELLOPEEK_MAIL_UNREAD_ICON, TXT_HELLOPEEK_DEMO_LIST_BOX_MAIL_EXAMPLE_FROM_1, TXT_HELLOPEEK_DEMO_LIST_BOX_MAIL_EXAMPLE_TIME_1, TXT_HELLOPEEK_DEMO_LIST_BOX_MAIL_EXAMPLE_SUBJ_1/*,STXT_OK, TXT_HELLOPEEK_DEMO_LIST_BOX_MAIL_VIEW, STXT_RETURN*/);
		AppendMailListItem(ctrl_id, IMG_HELLOPEEK_MAIL_READ_ICON, TXT_HELLOPEEK_DEMO_LIST_BOX_MAIL_EXAMPLE_FROM_2, TXT_HELLOPEEK_DEMO_LIST_BOX_MAIL_EXAMPLE_TIME_2, TXT_HELLOPEEK_DEMO_LIST_BOX_MAIL_EXAMPLE_SUBJ_2/*, STXT_SELECT, TXT_HELLOPEEK_DEMO_LIST_BOX_MAIL_VIEW, STXT_RETURN*/);
		AppendMailListItem(ctrl_id, IMG_HELLOPEEK_MAIL_STARRED_ICON, TXT_HELLOPEEK_DEMO_LIST_BOX_MAIL_EXAMPLE_FROM_3, TXT_HELLOPEEK_DEMO_LIST_BOX_MAIL_EXAMPLE_TIME_3, TXT_HELLOPEEK_DEMO_LIST_BOX_MAIL_EXAMPLE_SUBJ_3/*, STXT_ANSWER, TXT_HELLOPEEK_DEMO_LIST_BOX_MAIL_VIEW, STXT_RETURN*/);
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
        MMK_CreateWin((uint32 *)MMI_PEEK_MAIL_TRASH_MENU_TAB, PNULL);
        break;

	case MSG_CTL_MIDSK:
		//MMK_CloseWin(win_id);
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


LOCAL MMI_RESULT_E HandlePeekMailTrashMenuWinMsg(
                                         MMI_WIN_ID_T     	win_id, 
                                         MMI_MESSAGE_ID_E    msg_id, 
                                         DPARAM              param
                                         )
{
	MMI_RESULT_E 		recode 		= MMI_RESULT_TRUE;
	MMI_MENU_GROUP_ID_T group_id 	= 0;
	MMI_MENU_ID_T 		menu_id 	= 0;
	MMI_CTRL_ID_T	  	ctrl_id		= MMI_PEEK_MAIL_TRASH_MENU_CTRL_ID;
	

	switch(msg_id)
	{
	case MSG_OPEN_WINDOW:
		MMK_SetAtvCtrl(win_id, ctrl_id);
		break;
		
	case MSG_CTL_PENOK:
	case MSG_CTL_OK:
	case MSG_APP_OK:
	case MSG_APP_WEB:
	case MSG_CTL_MIDSK:
		GUIMENU_GetId(ctrl_id,&group_id,&menu_id);
		switch (menu_id)
		{
			case ID_PEEKMAIL_OPEN_MESSAGE:
				break;

			case ID_PEEKMAIL_COMPOSE:
				MMK_CloseWin(win_id);
				MMK_CloseWin(g_win_id_trash);
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
			case ID_PEEKMAIL_DELETE_MESSAGE:
				break;
			case ID_PEEKMAIL_DELETE_ALL:
				break;
			case ID_PEEKMAIL_INBOX_FOLDER: // other than inbox
				MMK_CloseWin(win_id);
				MMK_CloseWin(g_win_id_trash);				
				break;
			case ID_PEEKMAIL_MOVE_TO_INBOX_FOLDER:  // other than inbox
				break;
			case ID_PEEKMAIL_SAVED_FOLDER:
				MMK_CloseWin(win_id);
				MMK_CloseWin(g_win_id_trash);
				MMI_CreatePeekMailSavedWin();
				break;
			case ID_PEEKMAIL_SENT_FOLDER:
				MMK_CloseWin(win_id);
				MMK_CloseWin(g_win_id_trash);
				MMI_CreatePeekMailSentWin();
				break;
			case ID_PEEKMAIL_DRAFTS_FOLDER:
				MMK_CloseWin(win_id);
				MMK_CloseWin(g_win_id_trash);
				MMI_CreatePeekMailDraftWin();
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
PUBLIC void MMI_CreatePeekMailTrashWin(void)
{
   MMK_CreateWin((uint32*)MMI_PEEK_MAIL_TRASH_WIN_TAB, PNULL);
}




