/*****************************************************************************
** File Name:      peekmail_contact.c                                               *
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
#include "mmipub.h"

#include "guifont.h"
#include "guilcd.h"
#include "guilistbox.h"
#include "guititle.h"
#include "guilabel.h"
#include "guiform.h"



#include "PeekMail_contact.h"
#include "PeekMail_contact_operation.h"
//#include "PeekMail_get_mail_info.h"
#include "PeekMail_main.h"
#include "PeekMail_text.h"
#include "PeekMail_image.h"
#include "PeekMail_id.h"
#include "PeekMail_menutable.h"
//#include "PeekMail_sent.h"
//#include "PeekMail_draft.h"
//#include "PeekMail_view.h"




/**--------------------------------------------------------------------------*/
/**                         MACRO DEFINITION                                 */
/**--------------------------------------------------------------------------*/

#define MAX_PATH_LEN 		24

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

//Contact list
WINDOW_TABLE(MMI_PEEK_MAIL_CONTACT_WIN_TAB) =
{
	WIN_ID(MMI_PEEK_MAIL_CONTACT_WIN_ID),
	WIN_FUNC((uint32)HandlePeekMailContactWinMsg),
	WIN_TITLE(TXT_PEEKMAIL_CONTACT_TITLE),
	CREATE_LISTBOX_CTRL(GUILIST_TEXTLIST_E, MMI_PEEK_MAIL_CONTACT_CTRL_ID),
	WIN_SOFTKEY(TXT_PEEKMAIL_MENU, TXT_PEEKMAIL_VIEW, TXT_PEEKMAIL_BACK),
	END_WIN
};

// Contact Menu (left softkey)
WINDOW_TABLE( MMI_PEEK_MAIL_CONTACT_MENU_WIN_TAB ) = 
{
	WIN_ID(MMI_PEEK_MAIL_CONTACT_MENU_WIN_ID),
    WIN_FUNC((uint32)HandlePeekMailContactMenuWinMsg),
    WIN_STYLE(WS_HAS_TRANSPARENT),
    CREATE_POPMENU_CTRL(MENU_PEEKMAIL_CONTACT_MENU,MMI_PEEK_MAIL_CONTACT_MENU_CTRL_ID),
    WIN_SOFTKEY(STXT_OK,TXT_NULL,STXT_RETURN),
    END_WIN
};

// Contact Editor 
WINDOW_TABLE(MMI_PEEK_MAIL_CONTACT_EDITOR_WIN_TAB) =
{
	WIN_ID(MMI_PEEK_MAIL_CONTACT_EDITOR_WIN_ID),
	WIN_FUNC((uint32)HandlePeekMailContactEditorWinMsg),
	WIN_TITLE(TXT_PEEKMAIL_CONTACT_NEW_CONTACT),

	CREATE_FORM_CTRL(GUIFORM_LAYOUT_ORDER, MMI_PEEK_MAIL_CONTACT_EDITOR_FORM_CTRL_ID),

	CHILD_FORM_CTRL(TRUE,GUIFORM_LAYOUT_SBS,MMI_PEEK_MAIL_CONTACT_EDITOR_NAME_FORM_CTRL_ID,MMI_PEEK_MAIL_CONTACT_EDITOR_FORM_CTRL_ID),
		CHILD_LABEL_CTRL(GUILABEL_ALIGN_LEFT,FALSE,MMI_PEEK_MAIL_CONTACT_EDITOR_LABEL_NAME_CTRL_ID,MMI_PEEK_MAIL_CONTACT_EDITOR_NAME_FORM_CTRL_ID),
		CHILD_EDIT_TEXT_CTRL(TRUE,MAX_LEN_CONTACT_EDITOR_NAME,MMI_PEEK_MAIL_CONTACT_EDITOR_EDITBOX_NAME_CTRL_ID,MMI_PEEK_MAIL_CONTACT_EDITOR_NAME_FORM_CTRL_ID),

	CHILD_FORM_CTRL(TRUE,GUIFORM_LAYOUT_SBS,MMI_PEEK_MAIL_CONTACT_EDITOR_PHONE_FORM_CTRL_ID,MMI_PEEK_MAIL_CONTACT_EDITOR_FORM_CTRL_ID),
		CHILD_LABEL_CTRL(GUILABEL_ALIGN_LEFT,FALSE,MMI_PEEK_MAIL_CONTACT_EDITOR_LABEL_PHONE_CTRL_ID,MMI_PEEK_MAIL_CONTACT_EDITOR_PHONE_FORM_CTRL_ID),
		CHILD_EDIT_PHONENUM_CTRL(TRUE,MAX_LEN_CONTACT_EDITOR_PHONE,MMI_PEEK_MAIL_CONTACT_EDITOR_EDITBOX_PHONE_CTRL_ID,MMI_PEEK_MAIL_CONTACT_EDITOR_PHONE_FORM_CTRL_ID),

	CHILD_FORM_CTRL(TRUE,GUIFORM_LAYOUT_SBS,MMI_PEEK_MAIL_CONTACT_EDITOR_ADDRESS_FORM_CTRL_ID,MMI_PEEK_MAIL_CONTACT_EDITOR_FORM_CTRL_ID),
		CHILD_LABEL_CTRL(GUILABEL_ALIGN_LEFT,FALSE,MMI_PEEK_MAIL_CONTACT_EDITOR_LABEL_ADDRESS_CTRL_ID,MMI_PEEK_MAIL_CONTACT_EDITOR_ADDRESS_FORM_CTRL_ID),
		CHILD_EDIT_TEXT_CTRL(TRUE,MAX_LEN_CONTACT_EDITOR_EMAIL_ADDRESS,MMI_PEEK_MAIL_CONTACT_EDITOR_EDITBOX_ADDRESS_CTRL_ID,MMI_PEEK_MAIL_CONTACT_EDITOR_ADDRESS_FORM_CTRL_ID),

	WIN_SOFTKEY(TXT_PEEKMAIL_MENU, TXT_NULL, TXT_PEEKMAIL_BACK),
	END_WIN
};


WINDOW_TABLE(MMI_PEEK_MAIL_CONTACT_EDIT_MENU_WIN_TAB) =
{
	WIN_ID(MMI_PEEK_MAIL_CONTACT_EDIT_MENU_WIN_ID),
	WIN_FUNC((uint32)HandlePeekMailContactEditMenuWinMsg),
	WIN_STYLE(WS_HAS_TRANSPARENT),
	CREATE_POPMENU_CTRL(MENU_PEEKMAIL_CONTACT_EDIT_MENU, MMI_PEEK_MAIL_CONTACT_EDIT_MENU_CTRL_ID),
	WIN_SOFTKEY(STXT_OK, TXT_NULL, STXT_RETURN),
	END_WIN
};


PEEKMAIL_CONTACT_EDITOR_TYPE_E 	g_contact_editor_type = NEW;
MMI_HANDLE_T			 		g_edit_contact_win_h;


/**--------------------------------------------------------------------------*
 **                         FUNCTION DEFINITION                              *
 **--------------------------------------------------------------------------*/
/*****************************************************************************/
//  Description : open hello peek windows
//  Global resource dependence : 
//  Author: Song,Han
//  Note: 
/*****************************************************************************/

PUBLIC void AppendContactListItem(
							  MMI_CTRL_ID_T    ctrl_id,
							  MMI_STRING_T 	*  text_name,
							  MMI_STRING_T  *  text_phone_num,
							  MMI_STRING_T  *  text_mail_address					  
							  )
{
	GUILIST_ITEM_T			item_t	   = {0};
	GUILIST_ITEM_DATA_T 	item_data  = {0};
	uint32					item_index = 0;
/*
	wchar					name[] = L"Name: ";
	wchar					phone[] = L"Phone: ";
	wchar					address[] = L"eMail: ";
*/
/*
	MMI_STRING_T			name_str = {0};
	MMI_STRING_T			phone_str = {0};
	MMI_STRING_T			address_str = {0};


	wchar 					*wch_name;
	wchar 					*wch_phone;
	wchar 					*wch_address;

	uint8 *					ch_name;
	uint8 *					ch_phone;
	uint8 *					ch_address;

	
	uint8 					name[128];
	uint8 					phone[128];
	uint8 					address[128];

	wch_name = (wchar *)malloc((text_name->wstr_len+8)*sizeof(wchar));
	wch_phone = (wchar *)malloc((text_phone_num->wstr_len+8)*sizeof(wchar));
	wch_address = (wchar *)malloc((text_mail_address->wstr_len+8)*sizeof(wchar));
	memset(wch_name, 0, strlen(wch_name));
	memset(wch_phone, 0, strlen(wch_phone));
	memset(wch_address, 0, strlen(wch_address));

	
	ch_name = (uint8 *)malloc((text_name->wstr_len+8)*sizeof(uint8));
	ch_phone = (uint8 *)malloc((text_phone_num->wstr_len+8)*sizeof(uint8));
	ch_address = (uint8 *)malloc((text_mail_address->wstr_len+8)*sizeof(uint8));
	memset(ch_name, 0, strlen(ch_name));
	memset(ch_phone, 0, strlen(ch_phone));
	memset(ch_address, 0, strlen(ch_address));

	
	MMIAPICOM_WstrToStr(text_name->wstr_ptr,ch_name);
	MMIAPICOM_WstrToStr(text_phone_num->wstr_ptr,ch_phone);
	MMIAPICOM_WstrToStr(text_mail_address->wstr_ptr,ch_address);
	
	sprintf(name, "Name: %s", ch_name);
	sprintf(phone, "Phone: %s", ch_phone);
	sprintf(address, "eMail: %s", ch_address);

	MMIAPICOM_StrToWstr(name, wch_name);	
	MMIAPICOM_StrToWstr(phone, wch_phone);
	MMIAPICOM_StrToWstr(address, wch_address);

	name_str.wstr_ptr = wch_name;
	name_str.wstr_len = MMIAPICOM_Wstrlen(wch_name);

	phone_str.wstr_ptr = wch_phone;
	phone_str.wstr_len = MMIAPICOM_Wstrlen(wch_phone);
	
	address_str.wstr_ptr = wch_address;
	address_str.wstr_len = MMIAPICOM_Wstrlen(wch_address);
*/

	
/*
	MMIAPICOM_Wstrcat(wch_name, name);
	MMIAPICOM_Wstrcat(wch_name, text_name->wstr_ptr);
	name_str.wstr_ptr = name;
	name_str.wstr_len = MMIAPICOM_Wstrlen(name);
/*	
	MMIAPICOM_Wstrcat(phone, text_phone_num->wstr_ptr);	
	phone_str.wstr_ptr = phone;
	phone_str.wstr_len = MMIAPICOM_Wstrlen(phone);
	
	MMIAPICOM_Wstrcat(address, text_mail_address->wstr_ptr);
	address_str.wstr_ptr = address;
	address_str.wstr_len = MMIAPICOM_Wstrlen(address);*/

/*
	MMIAPICOM_Wstrcpy(wch_name, name);
	MMIAPICOM_Wstrcat(wch_name, text_name->wstr_ptr);
	MMIAPICOM_Wstrcpy(wch_phone,phone);
	MMIAPICOM_Wstrcat(wch_phone, text_phone_num->wstr_ptr);
	MMIAPICOM_Wstrcpy(wch_address, address);
	MMIAPICOM_Wstrcat(wch_address, text_mail_address->wstr_ptr);

	text_name->wstr_ptr = wch_name;
	text_name->wstr_len = MMIAPICOM_Wstrlen(wch_name);
	text_phone_num->wstr_ptr = wch_phone;
	text_phone_num->wstr_len = MMIAPICOM_Wstrlen(wch_phone);
	text_mail_address->wstr_ptr = wch_address;
	text_mail_address->wstr_len = MMIAPICOM_Wstrlen(wch_address);
*/

	
	item_t.item_style	 = GUIITEM_STYLE_THREE_LINE_TEXT;

	item_t.item_data_ptr = &item_data;

	item_data.item_content[0].item_data_type = GUIITEM_DATA_TEXT_BUFFER;
	item_data.item_content[0].item_data.text_buffer = *text_name;//name_str;

	item_data.item_content[1].item_data_type = GUIITEM_DATA_TEXT_BUFFER;
	item_data.item_content[1].item_data.text_buffer = *text_phone_num;//phone_str;

	item_data.item_content[2].item_data_type = GUIITEM_DATA_TEXT_BUFFER;
	item_data.item_content[2].item_data.text_buffer = *text_mail_address;//address_str;

	GUILIST_AppendItem(ctrl_id, &item_t);

	return;
}


LOCAL MMI_RESULT_E HandlePeekMailContactWinMsg(
                                         MMI_WIN_ID_T     win_id, 
                                         MMI_MESSAGE_ID_E msg_id, 
                                         DPARAM           param
                                         )
{
    MMI_RESULT_E        recode	 	 = MMI_RESULT_TRUE;
    GUI_LCD_DEV_INFO	lcd_dev_info = {GUI_LCD_0, GUI_BLOCK_0};
	MMI_CTRL_ID_T	  	ctrl_id		 = MMI_PEEK_MAIL_CONTACT_CTRL_ID;

	uint16				contact_num = 0;
	uint16				contact_index = 0;
	char 				*contact_file_name;
	
	PEEKMAIL_CONTACT_STRUCT contact_detail;


    lcd_dev_info.lcd_id		= GUI_MAIN_LCD_ID;
    lcd_dev_info.block_id	= GUI_BLOCK_MAIN;

    switch(msg_id)
    {
    case MSG_OPEN_WINDOW:
		contact_num = PeekMail_GetContactNum(CONTACT_INFO);
		MMK_SetAtvCtrl(win_id, ctrl_id);
		GUILIST_SetMaxItem(ctrl_id, 10, FALSE);
		GUILIST_SetNeedPrgbar(ctrl_id,TRUE);
		GUILIST_SetTitleIndexType(ctrl_id, GUILIST_TITLE_INDEX_DEFAULT);
		GUILIST_SetTextFont(ctrl_id, SONG_FONT_14, MMI_WHITE_COLOR);
		for (contact_index = 1; contact_index<=contact_num; contact_index++)
		{	
			contact_file_name = (char *)malloc(32 * sizeof(char));	
			memset(contact_file_name, 0, sizeof(contact_file_name));
			sprintf(contact_file_name,  "%s%d", CONTACT_PATH, contact_index);
			memset(&contact_detail, 0, sizeof(contact_detail));
			PeekMail_GetContactStructure(contact_file_name, &contact_detail, ALL_INFO);

			AppendContactListItem(ctrl_id, contact_detail.name, contact_detail.phone, contact_detail.mail);
		}
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
        MMI_CreatePeekContactMenuWin();
        break;

	case MSG_CTL_MIDSK:
	case MSG_CTL_PENOK:
		MMI_CreatePeekMailContactEditWin();
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


LOCAL MMI_RESULT_E HandlePeekMailContactMenuWinMsg(
                                         MMI_WIN_ID_T     	win_id, 
                                         MMI_MESSAGE_ID_E    msg_id, 
                                         DPARAM              param
                                         )
{
	MMI_RESULT_E 		recode 		= MMI_RESULT_TRUE;
	MMI_MENU_GROUP_ID_T group_id 	= 0;
	MMI_MENU_ID_T 		menu_id 	= 0;
	MMI_CTRL_ID_T	  	ctrl_id		= MMI_PEEK_MAIL_CONTACT_MENU_CTRL_ID;

	uint16				time_period = 1000;

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
			case ID_PEEKMAIL_CONTACT_NEW:
				MMI_CreatePeekMailContactNewWin();
				break;

			case ID_PEEKMAIL_CONTACT_DOWNLOAD:
				// do download
				MMIPUB_OpenAlertWinByTextId(&time_period,TXT_PEEKMAIL_CONTACT_DOWNLOAD_SUCCESSFULLY,TXT_NULL,IMAGE_PUBWIN_SUCCESS,PNULL,PNULL,MMIPUB_SOFTKEY_ONE,PNULL);
				break;
			
			case ID_PEEKMAIL_INBOX_FOLDER:
				MMK_CloseWin(win_id);
				MMK_CloseWin(MMI_PEEK_MAIL_CONTACT_WIN_ID);
				MMI_CreatePeekMailWin();
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


LOCAL MMI_RESULT_E HandlePeekMailContactEditorWinMsg(
											 MMI_WIN_ID_T		win_id, 
											 MMI_MESSAGE_ID_E	 msg_id, 
											 DPARAM 			 param
											 )
{
	MMI_RESULT_E		recode					= MMI_RESULT_TRUE;
	GUI_LCD_DEV_INFO	lcd_dev_info			= {GUI_LCD_0, GUI_BLOCK_0};

	uint16				contact_index			= 0;	
	uint8			   *contact_file_name		= PNULL;
	
	MMI_CTRL_ID_T		ctrl_id_label_name 		= MMI_PEEK_MAIL_CONTACT_EDITOR_LABEL_NAME_CTRL_ID;
	MMI_CTRL_ID_T		ctrl_id_label_phone		= MMI_PEEK_MAIL_CONTACT_EDITOR_LABEL_PHONE_CTRL_ID;
	MMI_CTRL_ID_T		ctrl_id_label_address	= MMI_PEEK_MAIL_CONTACT_EDITOR_LABEL_ADDRESS_CTRL_ID;

	MMI_CTRL_ID_T		ctrl_id_edit_name		= MMI_PEEK_MAIL_CONTACT_EDITOR_EDITBOX_NAME_CTRL_ID;
	MMI_CTRL_ID_T		ctrl_id_edit_phone 		= MMI_PEEK_MAIL_CONTACT_EDITOR_EDITBOX_PHONE_CTRL_ID;
	MMI_CTRL_ID_T		ctrl_id_edit_address	= MMI_PEEK_MAIL_CONTACT_EDITOR_EDITBOX_ADDRESS_CTRL_ID;

	
	LOCAL const wchar	wch_name[] 		= L"Name:";
	LOCAL const wchar	wch_phone[]		= L"Phone:";
	LOCAL const wchar	wch_address[]	= L"Address:";

	const wchar  text_edit_title[] 	= L"Edit Contact";

	MMI_STRING_T		str_name			= {0};
	MMI_STRING_T		str_phone			= {0};
	MMI_STRING_T		str_address			= {0};


	GUI_BG_T			bg						= {GUI_BG_COLOR, GUI_SHAPE_ROUNDED_RECT,0, MMI_WHITE_COLOR};

	GUIFORM_CHILD_WIDTH_T width_edit_name		= {0};
	GUIFORM_CHILD_WIDTH_T width_edit_phone 		= {0};
	GUIFORM_CHILD_WIDTH_T width_edit_address	= {0};

	GUIFORM_CHILD_HEIGHT_T height_edit_name		= {0};
	GUIFORM_CHILD_HEIGHT_T height_edit_phone	= {0};
	GUIFORM_CHILD_HEIGHT_T height_edit_address	= {0};

	uint16				   		ver_space		= 10;

	PEEKMAIL_CONTACT_STRUCT   	contact_detail;

	BOOLEAN 					is_disp = FALSE;
	
	uint16  text_edit_title_len 		= MMIAPICOM_Wstrlen(text_edit_title);
	

	width_edit_name.add_data			= 170;
	width_edit_name.type				= GUIFORM_CHLID_WIDTH_FIXED;
	width_edit_phone.add_data			= 170;
	width_edit_phone.type				= GUIFORM_CHLID_WIDTH_FIXED;
	width_edit_address.add_data			= 170;
	width_edit_address.type				= GUIFORM_CHLID_WIDTH_FIXED;


	height_edit_name.add_data			= 15;
	height_edit_name.type				= GUIFORM_CHLID_HEIGHT_FIXED;
	height_edit_phone.add_data 			= 15;
	height_edit_phone.type 				= GUIFORM_CHLID_HEIGHT_FIXED;
	height_edit_address.add_data		= 15;
	height_edit_address.type			= GUIFORM_CHLID_HEIGHT_FIXED;


	lcd_dev_info.lcd_id 				= GUI_MAIN_LCD_ID;
	lcd_dev_info.block_id				= GUI_BLOCK_MAIN;

	str_name.wstr_ptr					= wch_name;
	str_name.wstr_len					= MMIAPICOM_Wstrlen(wch_name);
	str_phone.wstr_ptr 					= wch_phone;
	str_phone.wstr_len 					= MMIAPICOM_Wstrlen(wch_phone);
	str_address.wstr_ptr				= wch_address;
	str_address.wstr_len				= MMIAPICOM_Wstrlen(wch_address);

	switch(msg_id)
	{
	case MSG_OPEN_WINDOW:
		GUIFORM_SetStyle(MMI_PEEK_MAIL_CONTACT_EDITOR_NAME_FORM_CTRL_ID, GUIFORM_STYLE_NORMAL);	
		GUILABEL_SetText(ctrl_id_label_name, &str_name, FALSE);
		GUILABEL_SetFont(ctrl_id_label_name, SONG_FONT_14, MMI_BACKGROUND_COLOR);
		GUIFORM_SetChildWidth(MMI_PEEK_MAIL_CONTACT_EDITOR_NAME_FORM_CTRL_ID,ctrl_id_edit_name, &width_edit_name);
		MMK_SetAtvCtrl(win_id, ctrl_id_edit_name);

		GUIFORM_SetStyle(MMI_PEEK_MAIL_CONTACT_EDITOR_PHONE_FORM_CTRL_ID, GUIFORM_STYLE_NORMAL);	
		GUILABEL_SetText(ctrl_id_label_phone, &str_phone, FALSE);
		GUILABEL_SetFont(ctrl_id_label_phone, SONG_FONT_14, MMI_BACKGROUND_COLOR);
		GUIFORM_SetChildWidth(MMI_PEEK_MAIL_CONTACT_EDITOR_PHONE_FORM_CTRL_ID,ctrl_id_edit_phone, &width_edit_phone);
		//GUIFORM_SetSpace(MMI_PEEK_MAIL_COMPOSER_TO_FORM_CTRL_ID, PNULL, &ver_space);
		//MMK_SetAtvCtrl(win_id, ctrl_id_edit_phone);

		GUIFORM_SetStyle(MMI_PEEK_MAIL_CONTACT_EDITOR_ADDRESS_FORM_CTRL_ID, GUIFORM_STYLE_NORMAL); 
		GUILABEL_SetText(ctrl_id_label_address, &str_address, FALSE);
		GUILABEL_SetFont(ctrl_id_label_address, SONG_FONT_14, MMI_BACKGROUND_COLOR);		
		GUIFORM_SetChildWidth(MMI_PEEK_MAIL_CONTACT_EDITOR_ADDRESS_FORM_CTRL_ID,ctrl_id_edit_address, &width_edit_address);
		//GUIFORM_SetChildHeight(MMI_PEEK_MAIL_COMPOSER_SUBJECT_FORM_CTRL_ID,ctrl_id_edit_subject, &height_edit_subject);
		//GUIFORM_SetSpace(MMI_PEEK_MAIL_CONTACT_EDITOR_ADDRESS_FORM_CTRL_ID, PNULL, &ver_space);
		
		if (NEW != g_contact_editor_type)
		{
		
			GUIWIN_SetTitleText(g_edit_contact_win_h, text_edit_title, text_edit_title_len, FALSE);
			contact_index = GUILIST_GetCurItemIndex(MMI_PEEK_MAIL_CONTACT_CTRL_ID);
			contact_file_name = (char *)malloc(32 * sizeof(char));	
			memset(contact_file_name, 0, sizeof(contact_file_name));
			sprintf(contact_file_name,	"%s%d", CONTACT_PATH, contact_index+1);
			memset(&contact_detail, 0, sizeof(contact_detail));
			PeekMail_GetContactStructure(contact_file_name, &contact_detail, ALL_INFO);

			GUIEDIT_SetString(ctrl_id_edit_name, contact_detail.name->wstr_ptr, contact_detail.name->wstr_len);
			GUIEDIT_SetFont(ctrl_id_edit_name,SONG_FONT_14);
			GUIEDIT_SetString(ctrl_id_edit_phone, contact_detail.phone->wstr_ptr, contact_detail.phone->wstr_len);
			GUIEDIT_SetFont(ctrl_id_edit_phone,SONG_FONT_14);
			GUIEDIT_SetString(ctrl_id_edit_address, contact_detail.mail->wstr_ptr, contact_detail.mail->wstr_len);
			GUIEDIT_SetFont(ctrl_id_edit_address,SONG_FONT_14);
		}	
			
		break;

	case MSG_GET_FOCUS:
		break;

	case MSG_LOSE_FOCUS:
		break;

	case MSG_FULL_PAINT:
		{			
			GUI_RECT_T				rect = {0,0, 239, 319};
			GUI_FillRect(&lcd_dev_info,rect,MMI_WHITE_COLOR);
		}
		break;

	//case MSG_KEYDOWN_CANCEL:
	case MSG_CTL_CANCEL:
		MMK_CloseWin(win_id);
		break;

	/********************************
	* MSG_CTL_OK: is the left softkey	   **
	* MSG_CTL_MIDSK: is the middle one **
	*********************************/

	case MSG_CTL_OK:
		MMI_CreatePeekMailContactEditMenuWin();
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



LOCAL MMI_RESULT_E HandlePeekMailContactEditMenuWinMsg(
										 MMI_WIN_ID_T		win_id, 
										 MMI_MESSAGE_ID_E	 msg_id, 
										 DPARAM 			 param
										 )
{
	MMI_RESULT_E		recode		= MMI_RESULT_TRUE;
	MMI_MENU_GROUP_ID_T group_id	= 0;
	MMI_MENU_ID_T		menu_id 	= 0;
	MMI_CTRL_ID_T		ctrl_id 	= MMI_PEEK_MAIL_CONTACT_EDIT_MENU_CTRL_ID;

	uint16				time_period = 1000;

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
			case ID_PEEKMAIL_CONTACT_EDIT_SAVE_DETAILS:
				MMIPUB_OpenAlertWinByTextId(&time_period,TXT_PEEKMAIL_CONTACT_EDIT_SAVE_CONTACT_SUCCESSFULLY,TXT_NULL,IMAGE_PUBWIN_SUCCESS,PNULL,PNULL,MMIPUB_SOFTKEY_ONE,PNULL);	
				break;

			case ID_PEEKMAIL_INBOX_FOLDER:
				MMK_CloseWin(win_id);
				MMK_CloseWin(MMI_PEEK_MAIL_CONTACT_EDITOR_WIN_ID);
				MMK_CloseWin(MMI_PEEK_MAIL_CONTACT_WIN_ID);
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

PUBLIC void MMI_CreatePeekContactWin()
{
   MMK_CreateWin((uint32*)MMI_PEEK_MAIL_CONTACT_WIN_TAB, PNULL);
}


PUBLIC void MMI_CreatePeekContactMenuWin()
{
   MMK_CreateWin((uint32*)MMI_PEEK_MAIL_CONTACT_MENU_WIN_TAB, PNULL);
}

PUBLIC void MMI_CreatePeekMailContactEditWin(void)
{
	g_contact_editor_type = EDIT;	
	g_edit_contact_win_h = MMK_CreateWin((uint32*)MMI_PEEK_MAIL_CONTACT_EDITOR_WIN_TAB, PNULL);
}

PUBLIC void MMI_CreatePeekMailContactNewWin(void)
{
	g_contact_editor_type = NEW;
	MMK_CreateWin((uint32*)MMI_PEEK_MAIL_CONTACT_EDITOR_WIN_TAB, PNULL);
}

PUBLIC void MMI_CreatePeekMailContactEditMenuWin(void)
{
	MMK_CreateWin((uint32*)MMI_PEEK_MAIL_CONTACT_EDIT_MENU_WIN_TAB, PNULL);
}

