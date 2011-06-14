/*****************************************************************************
** File Name:      peekmail_composer.c                                               *
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
#include "guilabel.h"
#include "guiform.h"

//#include "C:\peek\SPRD\MOCOR_10A.W11.09_P2_Source\MS_MMI\source\mmi_gui\source\form\h\guiform_internal.h"

#include "PeekMail_main.h"
#include "PeekMail_text.h"
#include "PeekMail_image.h"
#include "PeekMail_id.h"
#include "PeekMail_menutable.h"
#include "PeekMail_sent.h"
#include "PeekMail_saved.h"
#include "PeekMail_composer.h"



/**--------------------------------------------------------------------------*/
/**                         MACRO DEFINITION                                 */
/**--------------------------------------------------------------------------*/

#define MAX_LEN_COMPOSER_FROM 		128
#define MAX_LEN_COMPOSER_TO 		128
#define MAX_LEN_COMPOSER_SUBJECT 	128
#define MAX_LEN_COMPOSER_TEXT 		4096

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

// Composer
WINDOW_TABLE(MMI_PEEK_MAIL_COMPOSER_WIN_TAB) =
{
	WIN_ID(MMI_PEEK_MAIL_COMPOSER_WIN_ID),
	WIN_FUNC((uint32)HandlePeekMailComposerWinMsg),
	WIN_TITLE(TXT_PEEKMAIL_COMPOSER_TITLE),


/*
	CREATE_LABEL_CTRL(GUILABEL_ALIGN_LEFT,MMI_PEEK_MAIL_COMPOSER_LABEL_FROM_CTRL_ID),
	CREATE_EDIT_TEXT_CTRL(MAX_LEN_COMPOSER_FROM,MMI_PEEK_MAIL_COMPOSER_EDITBOX_FROM_CTRL_ID),

	CREATE_LABEL_CTRL(GUILABEL_ALIGN_LEFT,MMI_PEEK_MAIL_COMPOSER_LABEL_TO_CTRL_ID),
	CREATE_EDIT_TEXT_CTRL(MAX_LEN_COMPOSER_TO,MMI_PEEK_MAIL_COMPOSER_EDITBOX_TO_CTRL_ID),

	CREATE_LABEL_CTRL(GUILABEL_ALIGN_LEFT,MMI_PEEK_MAIL_COMPOSER_LABEL_SUBJECT_CTRL_ID),
	CREATE_EDIT_TEXT_CTRL(MAX_LEN_COMPOSER_SUBJECT,MMI_PEEK_MAIL_COMPOSER_EDITBOX_SUBJECT_CTRL_ID),

	CREATE_EDIT_TEXT_CTRL(MAX_LEN_COMPOSER_TEXT,MMI_PEEK_MAIL_COMPOSER_EDITBOX_TEXT_CTRL_ID),
*/
	

	CREATE_FORM_CTRL(GUIFORM_LAYOUT_ORDER, MMI_PEEK_MAIL_COMPOSER_FORM_CTRL_ID),

	CHILD_FORM_CTRL(TRUE,GUIFORM_LAYOUT_SBS,MMI_PEEK_MAIL_COMPOSER_FROM_FORM_CTRL_ID,MMI_PEEK_MAIL_COMPOSER_FORM_CTRL_ID),
		CHILD_LABEL_CTRL(GUILABEL_ALIGN_LEFT,FALSE,MMI_PEEK_MAIL_COMPOSER_LABEL_FROM_CTRL_ID,MMI_PEEK_MAIL_COMPOSER_FROM_FORM_CTRL_ID),
		CHILD_EDIT_TEXT_CTRL(TRUE,MAX_LEN_COMPOSER_FROM,MMI_PEEK_MAIL_COMPOSER_EDITBOX_FROM_CTRL_ID,MMI_PEEK_MAIL_COMPOSER_FROM_FORM_CTRL_ID),

	CHILD_FORM_CTRL(TRUE,GUIFORM_LAYOUT_SBS,MMI_PEEK_MAIL_COMPOSER_TO_FORM_CTRL_ID,MMI_PEEK_MAIL_COMPOSER_FORM_CTRL_ID),
		CHILD_LABEL_CTRL(GUILABEL_ALIGN_LEFT,FALSE,MMI_PEEK_MAIL_COMPOSER_LABEL_TO_CTRL_ID,MMI_PEEK_MAIL_COMPOSER_TO_FORM_CTRL_ID),
		CHILD_EDIT_TEXT_CTRL(TRUE,MAX_LEN_COMPOSER_TO,MMI_PEEK_MAIL_COMPOSER_EDITBOX_TO_CTRL_ID,MMI_PEEK_MAIL_COMPOSER_TO_FORM_CTRL_ID),


	CHILD_FORM_CTRL(TRUE,GUIFORM_LAYOUT_SBS,MMI_PEEK_MAIL_COMPOSER_SUBJECT_FORM_CTRL_ID,MMI_PEEK_MAIL_COMPOSER_FORM_CTRL_ID),
		CHILD_LABEL_CTRL(GUILABEL_ALIGN_LEFT,FALSE,MMI_PEEK_MAIL_COMPOSER_LABEL_SUBJECT_CTRL_ID,MMI_PEEK_MAIL_COMPOSER_SUBJECT_FORM_CTRL_ID),
		CHILD_EDIT_TEXT_CTRL(TRUE,MAX_LEN_COMPOSER_SUBJECT,MMI_PEEK_MAIL_COMPOSER_EDITBOX_SUBJECT_CTRL_ID,MMI_PEEK_MAIL_COMPOSER_SUBJECT_FORM_CTRL_ID),

	CHILD_FORM_CTRL(TRUE,GUIFORM_LAYOUT_SBS,MMI_PEEK_MAIL_COMPOSER_TEXT_FORM_CTRL_ID,MMI_PEEK_MAIL_COMPOSER_FORM_CTRL_ID),
		//CHILD_LABEL_CTRL(GUILABEL_ALIGN_LEFT,FALSE,MMI_PEEK_MAIL_COMPOSER_LABEL_TEXT_CTRL_ID,MMI_PEEK_MAIL_COMPOSER_TEXT_FORM_CTRL_ID),
		CHILD_EDIT_TEXT_CTRL(TRUE,MAX_LEN_COMPOSER_TEXT,MMI_PEEK_MAIL_COMPOSER_EDITBOX_TEXT_CTRL_ID,MMI_PEEK_MAIL_COMPOSER_TEXT_FORM_CTRL_ID),

	WIN_SOFTKEY(TXT_PEEKMAIL_MENU, TXT_NULL, TXT_PEEKMAIL_BACK),
	END_WIN
};

// Composer Menu (left softkey)
WINDOW_TABLE( MMI_PEEK_MAIL_COMPOSER_MENU_TAB ) = 
{
	WIN_ID(MMI_PEEK_MAIL_COMPOSER_MENU_WIN_ID),
    WIN_FUNC((uint32)HandlePeekMailComposerMenuWinMsg),
    WIN_STYLE( WS_HAS_TRANSPARENT),
    CREATE_POPMENU_CTRL(MENU_PEEKMAIL_COMPOSER_MENU, MMI_PEEK_MAIL_COMPOSER_MENU_CTRL_ID),
    WIN_SOFTKEY(STXT_OK,TXT_NULL,STXT_RETURN),
    END_WIN
};



/**--------------------------------------------------------------------------*
 **                         FUNCTION DEFINITION                              *
 **--------------------------------------------------------------------------*/
/*****************************************************************************/
//  Description : open hello peek windows
//  Global resource dependence : 
//  Author: Song,Han
//  Note: 
/*****************************************************************************/



LOCAL MMI_RESULT_E HandlePeekMailComposerWinMsg(
                                         MMI_WIN_ID_T     win_id, 
                                         MMI_MESSAGE_ID_E msg_id, 
                                         DPARAM           param
                                         )
{
    MMI_RESULT_E        recode 					= MMI_RESULT_TRUE;
    GUI_LCD_DEV_INFO	lcd_dev_info 			= {GUI_LCD_0, GUI_BLOCK_0};
	
	MMI_CTRL_ID_T	  	ctrl_id_label_from 		= MMI_PEEK_MAIL_COMPOSER_LABEL_FROM_CTRL_ID;
	MMI_CTRL_ID_T	  	ctrl_id_label_to 		= MMI_PEEK_MAIL_COMPOSER_LABEL_TO_CTRL_ID;
	MMI_CTRL_ID_T	  	ctrl_id_label_subject 	= MMI_PEEK_MAIL_COMPOSER_LABEL_SUBJECT_CTRL_ID;
	//MMI_CTRL_ID_T	  	ctrl_id_label_text 		= MMI_PEEK_MAIL_COMPOSER_LABEL_TEXT_CTRL_ID;
	MMI_CTRL_ID_T	  	ctrl_id_edit_from 		= MMI_PEEK_MAIL_COMPOSER_EDITBOX_FROM_CTRL_ID;
	MMI_CTRL_ID_T	  	ctrl_id_edit_to 		= MMI_PEEK_MAIL_COMPOSER_EDITBOX_TO_CTRL_ID;
	MMI_CTRL_ID_T	  	ctrl_id_edit_subject 	= MMI_PEEK_MAIL_COMPOSER_EDITBOX_SUBJECT_CTRL_ID;
	MMI_CTRL_ID_T	  	ctrl_id_edit_text 		= MMI_PEEK_MAIL_COMPOSER_EDITBOX_TEXT_CTRL_ID;

	GUI_RECT_T			label_from_rect 		= {2, 45, 60, 65};
	GUI_RECT_T			label_to_rect 			= {2, 67, 60, 87};
	GUI_RECT_T			label_subject_rect		= {2, 89, 60,109};
	GUI_RECT_T			edit_from_rect 			= {61,45,237, 65};
	GUI_RECT_T			edit_to_rect 			= {61,67,237, 87};
	GUI_RECT_T			edit_subject_rect		= {61,89,237,109};
	GUI_RECT_T			edit_text_rect 			= {0,112,239,319};
	
	LOCAL const wchar 	wch_from[] 				= L"From:";
	LOCAL const wchar 	wch_to[] 				= L"To:";
	LOCAL const wchar 	wch_subject[] 			= L"Subject:";

	MMI_STRING_T		str_from 				= {0};
	MMI_STRING_T		str_to 					= {0};
	MMI_STRING_T		str_subject 			= {0};

	GUI_BG_T			bg						= {GUI_BG_COLOR, GUI_SHAPE_ROUNDED_RECT,0, MMI_WHITE_COLOR};

	GUIFORM_CHILD_WIDTH_T width_edit_from 		= {0};
	GUIFORM_CHILD_WIDTH_T width_edit_to 		= {0};
	GUIFORM_CHILD_WIDTH_T width_edit_subject	= {0};

	GUIFORM_CHILD_HEIGHT_T height_edit_from 	= {0};
	GUIFORM_CHILD_HEIGHT_T height_edit_to 		= {0};
	GUIFORM_CHILD_HEIGHT_T height_edit_subject	= {0};
	GUIFORM_CHILD_HEIGHT_T height_edit_text 	= {0};

	uint16				   ver_space			= 10;
	
	width_edit_from.add_data					= 182;
	width_edit_from.type						= GUIFORM_CHLID_WIDTH_FIXED;
	width_edit_to.add_data						= 182;
	width_edit_to.type							= GUIFORM_CHLID_WIDTH_FIXED;
	width_edit_subject.add_data					= 182;
	width_edit_subject.type						= GUIFORM_CHLID_WIDTH_FIXED;
	
	height_edit_from.add_data					= 15;
	height_edit_from.type						= GUIFORM_CHLID_HEIGHT_FIXED;
	height_edit_to.add_data						= 15;
	height_edit_to.type							= GUIFORM_CHLID_HEIGHT_FIXED;
	height_edit_subject.add_data				= 15;
	height_edit_subject.type					= GUIFORM_CHLID_HEIGHT_FIXED;
	height_edit_text.add_data					= 45;
	height_edit_text.type						= GUIFORM_CHLID_HEIGHT_FIXED;

	
    lcd_dev_info.lcd_id							= GUI_MAIN_LCD_ID;
    lcd_dev_info.block_id						= GUI_BLOCK_MAIN;

	str_from.wstr_ptr 							= wch_from;
	str_from.wstr_len 							= MMIAPICOM_Wstrlen(wch_from);
	str_to.wstr_ptr 							= wch_to;
	str_to.wstr_len 							= MMIAPICOM_Wstrlen(wch_to);
	str_subject.wstr_ptr 						= wch_subject;
	str_subject.wstr_len 						= MMIAPICOM_Wstrlen(wch_subject);

    switch(msg_id)
    {
    case MSG_OPEN_WINDOW:
		
		GUIFORM_SetStyle(MMI_PEEK_MAIL_COMPOSER_FROM_FORM_CTRL_ID, GUIFORM_STYLE_NORMAL);	
		GUILABEL_SetText(ctrl_id_label_from, &str_from, FALSE);
		GUILABEL_SetFont(ctrl_id_label_from, SONG_FONT_14, MMI_BACKGROUND_COLOR);
		GUIFORM_SetChildWidth(MMI_PEEK_MAIL_COMPOSER_FROM_FORM_CTRL_ID,ctrl_id_edit_from, &width_edit_from);
		//GUIFORM_SetChildHeight(MMI_PEEK_MAIL_COMPOSER_FROM_FORM_CTRL_ID,ctrl_id_edit_from, &height_edit_from);
		MMK_SetAtvCtrl(win_id, ctrl_id_edit_from);


		GUIFORM_SetStyle(MMI_PEEK_MAIL_COMPOSER_TO_FORM_CTRL_ID, GUIFORM_STYLE_NORMAL);	
		GUILABEL_SetText(ctrl_id_label_to, &str_to, FALSE);
		GUILABEL_SetFont(ctrl_id_label_to, SONG_FONT_14, MMI_BACKGROUND_COLOR);
		GUIFORM_SetChildWidth(MMI_PEEK_MAIL_COMPOSER_TO_FORM_CTRL_ID,ctrl_id_edit_to, &width_edit_to);
		//GUIFORM_SetChildHeight(MMI_PEEK_MAIL_COMPOSER_TO_FORM_CTRL_ID,ctrl_id_edit_to, &height_edit_to);
		GUIFORM_SetSpace(MMI_PEEK_MAIL_COMPOSER_TO_FORM_CTRL_ID, PNULL, &ver_space);


		GUIFORM_SetStyle(MMI_PEEK_MAIL_COMPOSER_SUBJECT_FORM_CTRL_ID, GUIFORM_STYLE_NORMAL);	
		GUILABEL_SetText(ctrl_id_label_subject, &str_subject, FALSE);
		GUILABEL_SetFont(ctrl_id_label_subject, SONG_FONT_14, MMI_BACKGROUND_COLOR);		
		GUIFORM_SetChildWidth(MMI_PEEK_MAIL_COMPOSER_SUBJECT_FORM_CTRL_ID,ctrl_id_edit_subject, &width_edit_subject);
		//GUIFORM_SetChildHeight(MMI_PEEK_MAIL_COMPOSER_SUBJECT_FORM_CTRL_ID,ctrl_id_edit_subject, &height_edit_subject);
		GUIFORM_SetSpace(MMI_PEEK_MAIL_COMPOSER_SUBJECT_FORM_CTRL_ID, PNULL, &ver_space);

		
		GUIFORM_SetStyle(MMI_PEEK_MAIL_COMPOSER_TEXT_FORM_CTRL_ID, GUIFORM_STYLE_NORMAL);	
		//GUIFORM_SetChildDisplay(MMI_PEEK_MAIL_COMPOSER_TEXT_FORM_CTRL_ID,ctrl_id_label_text,GUIFORM_CHILD_DISP_HIDE);
		//GUIEDIT_SetRect(ctrl_id_edit_text, &edit_text_rect);
		//GUIFORM_SetChildHeight(MMI_PEEK_MAIL_COMPOSER_TEXT_FORM_CTRL_ID,ctrl_id_edit_text, &height_edit_text);
		//GUIFORM_SetSpace(MMI_PEEK_MAIL_COMPOSER_TEXT_FORM_CTRL_ID, PNULL, &ver_space);

		break;

    case MSG_GET_FOCUS:
        break;

    case MSG_LOSE_FOCUS:
        break;

    case MSG_FULL_PAINT:
		{			
			GUI_RECT_T 				rect = {0,0, 239, 319};
			GUI_FillRect(&lcd_dev_info,rect,MMI_WHITE_COLOR);
		}
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
        MMK_CreateWin((uint32 *)MMI_PEEK_MAIL_COMPOSER_MENU_TAB, PNULL);
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


LOCAL MMI_RESULT_E HandlePeekMailComposerMenuWinMsg(
                                         MMI_WIN_ID_T     	win_id, 
                                         MMI_MESSAGE_ID_E    msg_id, 
                                         DPARAM              param
                                         )
{
	MMI_RESULT_E 		recode 		= MMI_RESULT_TRUE;
	MMI_MENU_GROUP_ID_T group_id 	= 0;
	MMI_MENU_ID_T 		menu_id 	= 0;
	MMI_CTRL_ID_T	  	ctrl_id		= MMI_PEEK_MAIL_COMPOSER_MENU_CTRL_ID;
	

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
			case ID_PEEKMAIL_SEND_MESSAGE:
				break;

			case ID_PEEKMAIL_SAVE_AS_DRAFT:
				break;
			
			case ID_PEEKMAIL_ADD_CC:
				break;
			case ID_PEEKMAIL_ADD_BCC:
				break;
			case ID_PEEKMAIL_INBOX_FOLDER:
				MMI_CreatePeekMailWin();
				break;
			case ID_PEEKMAIL_CONTACTS:
				break;
			case ID_PEEKMAIL_PEEKMAIL_MANAGER:
				break;
			case ID_PEEKMAIL_REPLY:
				break;
			case ID_PEEKMAIL_REPLY_ALL: // other than inbox
				break;
			case ID_PEEKMAIL_FORWARD:  // other than inbox
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
//  Description : open hello peek windows
//  Global resource dependence : 
//  Author: Song,Han
//  Note: 
/*****************************************************************************/
PUBLIC void MMI_CreatePeekMailComposerWin(void)
{
    MMK_CreateWin((uint32*)MMI_PEEK_MAIL_COMPOSER_WIN_TAB, PNULL);
}




