/*****************************************************************************
** File Name:      peekmail_search.c                                               *
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


#include "PeekMail_main.h"
#include "PeekMail_text.h"
#include "PeekMail_image.h"
#include "PeekMail_id.h"
#include "PeekMail_menutable.h"
#include "PeekMail_sent.h"
#include "PeekMail_saved.h"
#include "PeekMail_composer.h"
#include "PeekMail_get_mail_info.h"
#include "PeekMail_search.h"

#include "mmisms_text.h"
#include "mmisms_image.h"
#include "mmipub.h"




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

// Searcher
WINDOW_TABLE(MMI_PEEK_MAIL_SEARCH_WIN_TAB) =
{
	WIN_ID(MMI_PEEK_MAIL_COMPOSER_WIN_ID),
	WIN_FUNC((uint32)HandlePeekMailSearchWinMsg),
	WIN_TITLE(TXT_PEEKMAIL_SEARCH_TITLE),
	

	CREATE_FORM_CTRL(GUIFORM_LAYOUT_ORDER, MMI_PEEK_MAIL_SEARCH_FORM_CTRL_ID),


	CHILD_FORM_CTRL(TRUE,GUIFORM_LAYOUT_SBS,MMI_PEEK_MAIL_SEARCH_LOOKING_FOR_CTRL_ID,MMI_PEEK_MAIL_SEARCH_FORM_CTRL_ID),
		CHILD_LABEL_CTRL(GUILABEL_ALIGN_LEFT,FALSE,MMI_PEEK_MAIL_SEARCH_LABEL_LOOKING_FOR_STH_CTRL_ID,MMI_PEEK_MAIL_SEARCH_LOOKING_FOR_CTRL_ID),


	CHILD_FORM_CTRL(TRUE,GUIFORM_LAYOUT_SBS,MMI_PEEK_MAIL_SEARCH_DATE_FORM_CTRL_ID,MMI_PEEK_MAIL_SEARCH_FORM_CTRL_ID),
		CHILD_LABEL_CTRL(GUILABEL_ALIGN_LEFT,FALSE,MMI_PEEK_MAIL_SEARCH_LABEL_DATE_CTRL_ID,MMI_PEEK_MAIL_SEARCH_DATE_FORM_CTRL_ID),
		CHILD_EDIT_TEXT_CTRL(TRUE,MAX_LEN_SEARCH_DATE,MMI_PEEK_MAIL_SEARCH_EDITBOX_DATE_CTRL_ID,MMI_PEEK_MAIL_SEARCH_DATE_FORM_CTRL_ID),

	CHILD_FORM_CTRL(TRUE,GUIFORM_LAYOUT_SBS,MMI_PEEK_MAIL_SEARCH_ATTACHMENTS_FORM_CTRL_ID,MMI_PEEK_MAIL_SEARCH_FORM_CTRL_ID),
		CHILD_LABEL_CTRL(GUILABEL_ALIGN_LEFT,FALSE,MMI_PEEK_MAIL_SEARCH_LABEL_ATTACHMENTS_CTRL_ID,MMI_PEEK_MAIL_SEARCH_ATTACHMENTS_FORM_CTRL_ID),
		CHILD_EDIT_TEXT_CTRL(TRUE,MAX_LEN_SEARCH_ATTACHMENTS,MMI_PEEK_MAIL_SEARCH_EDITBOX_ATTACHMENTS_CTRL_ID,MMI_PEEK_MAIL_SEARCH_ATTACHMENTS_FORM_CTRL_ID),

	CHILD_FORM_CTRL(TRUE,GUIFORM_LAYOUT_SBS,MMI_PEEK_MAIL_SEARCH_SUBJECT_FORM_CTRL_ID,MMI_PEEK_MAIL_SEARCH_FORM_CTRL_ID),
		CHILD_LABEL_CTRL(GUILABEL_ALIGN_LEFT,FALSE,MMI_PEEK_MAIL_SEARCH_LABEL_SUBJECT_CTRL_ID,MMI_PEEK_MAIL_SEARCH_SUBJECT_FORM_CTRL_ID),
		CHILD_EDIT_TEXT_CTRL(TRUE,MAX_LEN_SEARCH_SUBJECT,MMI_PEEK_MAIL_SEARCH_EDITBOX_SUBJECT_CTRL_ID,MMI_PEEK_MAIL_SEARCH_SUBJECT_FORM_CTRL_ID),


	CHILD_FORM_CTRL(TRUE,GUIFORM_LAYOUT_SBS,MMI_PEEK_MAIL_SEARCH_FROM_FORM_CTRL_ID,MMI_PEEK_MAIL_SEARCH_FORM_CTRL_ID),
		CHILD_LABEL_CTRL(GUILABEL_ALIGN_LEFT,FALSE,MMI_PEEK_MAIL_SEARCH_LABEL_FROM_CTRL_ID,MMI_PEEK_MAIL_SEARCH_FROM_FORM_CTRL_ID),
		CHILD_EDIT_TEXT_CTRL(TRUE,MAX_LEN_SEARCH_FROM,MMI_PEEK_MAIL_SEARCH_EDITBOX_FROM_CTRL_ID,MMI_PEEK_MAIL_SEARCH_FROM_FORM_CTRL_ID),

	WIN_SOFTKEY(STXT_OK, TXT_NULL, TXT_PEEKMAIL_BACK),
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


LOCAL MMI_RESULT_E HandlePeekMailSearchWinMsg(
                                         MMI_WIN_ID_T     win_id, 
                                         MMI_MESSAGE_ID_E msg_id, 
                                         DPARAM           param
                                         )
{
    MMI_RESULT_E        recode 						= MMI_RESULT_TRUE;
    GUI_LCD_DEV_INFO	lcd_dev_info 				= {GUI_LCD_0, GUI_BLOCK_0};
	
	MMI_CTRL_ID_T	  	ctrl_id_label_lookoing_for 	= MMI_PEEK_MAIL_SEARCH_LABEL_LOOKING_FOR_STH_CTRL_ID;
	MMI_CTRL_ID_T	  	ctrl_id_label_date 			= MMI_PEEK_MAIL_SEARCH_LABEL_DATE_CTRL_ID;
	MMI_CTRL_ID_T	  	ctrl_id_label_attachment 	= MMI_PEEK_MAIL_SEARCH_LABEL_ATTACHMENTS_CTRL_ID;
	MMI_CTRL_ID_T	  	ctrl_id_label_subject 		= MMI_PEEK_MAIL_SEARCH_LABEL_SUBJECT_CTRL_ID;
	MMI_CTRL_ID_T	  	ctrl_id_label_from 			= MMI_PEEK_MAIL_SEARCH_LABEL_FROM_CTRL_ID;
	MMI_CTRL_ID_T	  	ctrl_id_edit_date 			= MMI_PEEK_MAIL_SEARCH_EDITBOX_DATE_CTRL_ID;
	MMI_CTRL_ID_T	  	ctrl_id_edit_attachment 	= MMI_PEEK_MAIL_SEARCH_EDITBOX_ATTACHMENTS_CTRL_ID;
	MMI_CTRL_ID_T	  	ctrl_id_edit_subject 		= MMI_PEEK_MAIL_SEARCH_EDITBOX_SUBJECT_CTRL_ID;
	MMI_CTRL_ID_T	  	ctrl_id_edit_from 			= MMI_PEEK_MAIL_SEARCH_EDITBOX_FROM_CTRL_ID;

	LOCAL const wchar 	wch_looking_for[] 			= L"Looking for something?";
	LOCAL const wchar 	wch_date[] 					= L"Date: ";
	LOCAL const wchar 	wch_attachments[] 			= L"Attachment: ";
	LOCAL const wchar 	wch_subject[] 				= L"Subject:";
	LOCAL const wchar 	wch_from[] 					= L"From: ";

	MMI_STRING_T		str_looking_for 			= {0};
	MMI_STRING_T		str_date 					= {0};
	MMI_STRING_T		str_attachments 			= {0};
	MMI_STRING_T		str_subject					= {0};	
	MMI_STRING_T		str_from					= {0};

	GUI_BG_T			bg							= {GUI_BG_COLOR, GUI_SHAPE_ROUNDED_RECT,0, MMI_WHITE_COLOR};

	GUIFORM_CHILD_WIDTH_T width_edit_date 			= {0};
	GUIFORM_CHILD_WIDTH_T width_edit_attachments 	= {0};
	GUIFORM_CHILD_WIDTH_T width_edit_subject		= {0};
	GUIFORM_CHILD_WIDTH_T width_edit_from 			= {0};

	GUIFORM_CHILD_HEIGHT_T height_edit_date 		= {0};
	GUIFORM_CHILD_HEIGHT_T height_edit_attachments 	= {0};
	GUIFORM_CHILD_HEIGHT_T height_edit_subject		= {0};
	GUIFORM_CHILD_HEIGHT_T height_edit_from 		= {0};

	uint16				   ver_space			= 10;


	width_edit_date.add_data					= 145;
	width_edit_date.type						= GUIFORM_CHLID_WIDTH_FIXED;
	width_edit_attachments.add_data				= 145;
	width_edit_attachments.type					= GUIFORM_CHLID_WIDTH_FIXED;
	width_edit_subject.add_data					= 145;
	width_edit_subject.type						= GUIFORM_CHLID_WIDTH_FIXED;
	width_edit_from.add_data					= 145;
	width_edit_from.type						= GUIFORM_CHLID_WIDTH_FIXED;
	
	height_edit_date.add_data					= 15;
	height_edit_date.type						= GUIFORM_CHLID_HEIGHT_FIXED;
	height_edit_attachments.add_data			= 15;
	height_edit_attachments.type				= GUIFORM_CHLID_HEIGHT_FIXED;
	height_edit_subject.add_data				= 15;
	height_edit_subject.type					= GUIFORM_CHLID_HEIGHT_FIXED;
	height_edit_from.add_data					= 15;
	height_edit_from.type						= GUIFORM_CHLID_HEIGHT_FIXED;
	
    lcd_dev_info.lcd_id							= GUI_MAIN_LCD_ID;
    lcd_dev_info.block_id						= GUI_BLOCK_MAIN;


	str_looking_for.wstr_ptr					= wch_looking_for;
	str_looking_for.wstr_len					= MMIAPICOM_Wstrlen(wch_looking_for);
	str_date.wstr_ptr 							= wch_date;
	str_date.wstr_len 							= MMIAPICOM_Wstrlen(wch_date);
	str_attachments.wstr_ptr					= wch_attachments;
	str_attachments.wstr_len					= MMIAPICOM_Wstrlen(wch_attachments);
	str_subject.wstr_ptr 						= wch_subject;
	str_subject.wstr_len 						= MMIAPICOM_Wstrlen(wch_subject);
	str_from.wstr_ptr 							= wch_from;
	str_from.wstr_len 							= MMIAPICOM_Wstrlen(wch_from);


    switch(msg_id)
    {
    case MSG_OPEN_WINDOW:

		GUIFORM_SetStyle(MMI_PEEK_MAIL_SEARCH_LOOKING_FOR_CTRL_ID, GUIFORM_STYLE_NORMAL);	
		GUILABEL_SetText(ctrl_id_label_lookoing_for, &str_looking_for, FALSE);
		GUILABEL_SetFont(ctrl_id_label_lookoing_for, SONG_FONT_18, MMI_BACKGROUND_COLOR);


		GUIFORM_SetStyle(MMI_PEEK_MAIL_SEARCH_DATE_FORM_CTRL_ID, GUIFORM_STYLE_NORMAL);	
		GUILABEL_SetText(ctrl_id_label_date, &str_date, FALSE);
		GUILABEL_SetFont(ctrl_id_label_date, SONG_FONT_14, MMI_BACKGROUND_COLOR);
		GUIFORM_SetChildWidth(MMI_PEEK_MAIL_SEARCH_DATE_FORM_CTRL_ID,ctrl_id_edit_date, &width_edit_date);
		MMK_SetAtvCtrl(win_id, ctrl_id_edit_date);

		GUIFORM_SetStyle(MMI_PEEK_MAIL_SEARCH_ATTACHMENTS_FORM_CTRL_ID, GUIFORM_STYLE_NORMAL);	
		GUILABEL_SetText(ctrl_id_label_attachment, &str_attachments, FALSE);
		GUILABEL_SetFont(ctrl_id_label_attachment, SONG_FONT_14, MMI_BACKGROUND_COLOR);		
		GUIFORM_SetChildWidth(MMI_PEEK_MAIL_SEARCH_ATTACHMENTS_FORM_CTRL_ID,ctrl_id_edit_attachment, &width_edit_attachments);
		GUIFORM_SetSpace(MMI_PEEK_MAIL_SEARCH_ATTACHMENTS_FORM_CTRL_ID, PNULL, &ver_space);

		GUIFORM_SetStyle(MMI_PEEK_MAIL_SEARCH_SUBJECT_FORM_CTRL_ID, GUIFORM_STYLE_NORMAL);	
		GUILABEL_SetText(ctrl_id_label_subject, &str_subject, FALSE);
		GUILABEL_SetFont(ctrl_id_label_subject, SONG_FONT_14, MMI_BACKGROUND_COLOR);		
		GUIFORM_SetChildWidth(MMI_PEEK_MAIL_SEARCH_SUBJECT_FORM_CTRL_ID,ctrl_id_edit_subject, &width_edit_subject);
		GUIFORM_SetSpace(MMI_PEEK_MAIL_SEARCH_SUBJECT_FORM_CTRL_ID, PNULL, &ver_space);

		GUIFORM_SetStyle(MMI_PEEK_MAIL_SEARCH_FROM_FORM_CTRL_ID, GUIFORM_STYLE_NORMAL);	
		GUILABEL_SetText(ctrl_id_label_from, &str_from, FALSE);
		GUILABEL_SetFont(ctrl_id_label_from, SONG_FONT_14, MMI_BACKGROUND_COLOR);		
		GUIFORM_SetChildWidth(MMI_PEEK_MAIL_SEARCH_FROM_FORM_CTRL_ID,ctrl_id_edit_from, &width_edit_from);
		GUIFORM_SetSpace(MMI_PEEK_MAIL_SEARCH_FROM_FORM_CTRL_ID, PNULL, &ver_space);		

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





/*****************************************************************************/
//  Description : open hello peek windows
//  Global resource dependence : 
//  Author: Song,Han
//  Note: 
/*****************************************************************************/
PUBLIC void MMI_CreatePeekMailSearchWin(void)
{
    MMK_CreateWin((uint32*)MMI_PEEK_MAIL_SEARCH_WIN_TAB, PNULL);
}



