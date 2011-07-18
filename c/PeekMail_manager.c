/*****************************************************************************
** File Name:      peekmail_manager.c                                               *
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
#include "mmi_common.h"
#include "mmi_theme.h"
#include "mmipub.h"

#include "guifont.h"
#include "guilcd.h"
#include "guilistbox.h"
#include "guiform.h"
#include "guilabel.h"

#include "PeekMail_main.h"
#include "PeekMail_text.h"
#include "PeekMail_image.h"
#include "PeekMail_id.h"
#include "PeekMail_menutable.h"
#include "PeekMail_manager.h"
#include "PeekMail_account_operation.h"


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

PEEKMAIL_ACCOUNT_EDITOR_TYPE_E 	g_editor_type = NEW;
MMI_HANDLE_T					g_account_edit_win_h;
MMI_HANDLE_T					g_account_new_win_h;
uint16							g_deactive_items[32];
uint16							g_deactive_num = 0;


// Manager Main Menu
WINDOW_TABLE(MMI_PEEK_MAIL_MANAGER_WIN_TAB) =
{
	WIN_ID(MMI_PEEK_MAIL_MANAGER_WIN_ID),
	WIN_FUNC((uint32)HandlePeekMailManagerWinMsg),
	WIN_TITLE(TXT_PEEKMAIL_MANAGER_TITLE),
	CREATE_MENU_CTRL(MENU_PEEKMAIL_MANAGER_MAIN_MENU, MMI_PEEK_MAIL_MANAGER_MENU_CTRL_ID),
	WIN_SOFTKEY(STXT_OK, TXT_NULL, TXT_PEEKMAIL_BACK),
	END_WIN
};

// Account List
WINDOW_TABLE(MMI_PEEK_MAIL_MANAGER_ACCOUNT_WIN_TAB) =
{
	WIN_ID(MMI_PEEK_MAIL_MANAGER_ACCOUNT_WIN_ID),
	WIN_FUNC((uint32)HandlePeekMailManagerAccountWinMsg),
	WIN_TITLE(TXT_PEEKMAIL_MANAGER_ACCOUNT_TITLE),
	CREATE_LISTBOX_CTRL(GUILIST_TEXTLIST_E, MMI_PEEK_MAIL_MANAGER_ACCOUNT_CTRL_ID),
	WIN_SOFTKEY(TXT_PEEKMAIL_MENU, TXT_NULL, TXT_PEEKMAIL_BACK),
	END_WIN
};

// Account Menu (left softkey)
WINDOW_TABLE( MMI_PEEK_MAIL_MANAGER_ACCOUNT_MENU_WIN_TAB ) = 
{
	WIN_ID(MMI_PEEK_MAIL_MANAGER_ACCOUNT_MENU_WIN_ID),
    WIN_FUNC((uint32)HandlePeekMailManagerAccountMenuWinMsg),
    WIN_STYLE(WS_HAS_TRANSPARENT),
    CREATE_POPMENU_CTRL(MENU_PEEKMAIL_MANAGER_ACCOUNT_MENU, MMI_PEEK_MAIL_MANAGER_ACCOUNT_MENU_CTRL_ID),
    WIN_SOFTKEY(STXT_OK,TXT_NULL,STXT_RETURN),
    END_WIN
};

// Account Editor 
WINDOW_TABLE(MMI_PEEK_MAIL_ACCOUNT_EDITOR_WIN_TAB) =
{
	WIN_ID(MMI_PEEK_MAIL_ACCOUNT_EDITOR_WIN_ID),
	WIN_FUNC((uint32)HandlePeekMailAccountEditorWinMsg),
	WIN_TITLE(TXT_PEEKMAIL_MANAGER_ACCOUNT_EDITOR_TITLE),

	CREATE_FORM_CTRL(GUIFORM_LAYOUT_ORDER, MMI_PEEK_MAIL_ACCOUNT_EDITOR_FORM_CTRL_ID),

	CHILD_FORM_CTRL(TRUE,GUIFORM_LAYOUT_SBS,MMI_PEEK_MAIL_ACCOUNT_EDITOR_FIRST_NAME_FORM_CTRL_ID,MMI_PEEK_MAIL_ACCOUNT_EDITOR_FORM_CTRL_ID),
		CHILD_LABEL_CTRL(GUILABEL_ALIGN_LEFT,FALSE,MMI_PEEK_MAIL_ACCOUNT_EDITOR_LABEL_FIRST_NAME_CTRL_ID,MMI_PEEK_MAIL_ACCOUNT_EDITOR_FIRST_NAME_FORM_CTRL_ID),
		CHILD_EDIT_TEXT_CTRL(TRUE,MAX_LEN_ACCOUNT_EDITOR_NAME,MMI_PEEK_MAIL_ACCOUNT_EDITOR_EDITBOX_FIRST_NAME_CTRL_ID,MMI_PEEK_MAIL_ACCOUNT_EDITOR_FIRST_NAME_FORM_CTRL_ID),

	CHILD_FORM_CTRL(TRUE,GUIFORM_LAYOUT_SBS,MMI_PEEK_MAIL_ACCOUNT_EDITOR_LAST_NAME_FORM_CTRL_ID,MMI_PEEK_MAIL_ACCOUNT_EDITOR_FORM_CTRL_ID),
		CHILD_LABEL_CTRL(GUILABEL_ALIGN_LEFT,FALSE,MMI_PEEK_MAIL_ACCOUNT_EDITOR_LABEL_LAST_NAME_CTRL_ID,MMI_PEEK_MAIL_ACCOUNT_EDITOR_LAST_NAME_FORM_CTRL_ID),
		CHILD_EDIT_TEXT_CTRL(TRUE,MAX_LEN_ACCOUNT_EDITOR_NAME,MMI_PEEK_MAIL_ACCOUNT_EDITOR_EDITBOX_LAST_NAME_CTRL_ID,MMI_PEEK_MAIL_ACCOUNT_EDITOR_LAST_NAME_FORM_CTRL_ID),

	CHILD_FORM_CTRL(TRUE,GUIFORM_LAYOUT_SBS,MMI_PEEK_MAIL_ACCOUNT_EDITOR_PASSWORD_FORM_CTRL_ID,MMI_PEEK_MAIL_ACCOUNT_EDITOR_FORM_CTRL_ID),
		CHILD_LABEL_CTRL(GUILABEL_ALIGN_LEFT,FALSE,MMI_PEEK_MAIL_ACCOUNT_EDITOR_LABEL_PASSWORD_CTRL_ID,MMI_PEEK_MAIL_ACCOUNT_EDITOR_PASSWORD_FORM_CTRL_ID),
		CHILD_EDIT_PASSWORD_CTRL(TRUE,MAX_LEN_ACCOUNT_EDITOR_PASSWORD,MMI_PEEK_MAIL_ACCOUNT_EDITOR_EDITBOX_PASSWORD_CTRL_ID,MMI_PEEK_MAIL_ACCOUNT_EDITOR_PASSWORD_FORM_CTRL_ID),

	CHILD_FORM_CTRL(TRUE,GUIFORM_LAYOUT_SBS,MMI_PEEK_MAIL_ACCOUNT_EDITOR_ADDRESS_FORM_CTRL_ID,MMI_PEEK_MAIL_ACCOUNT_EDITOR_FORM_CTRL_ID),
		CHILD_LABEL_CTRL(GUILABEL_ALIGN_LEFT,FALSE,MMI_PEEK_MAIL_ACCOUNT_EDITOR_LABEL_ADDRESS_CTRL_ID,MMI_PEEK_MAIL_ACCOUNT_EDITOR_ADDRESS_FORM_CTRL_ID),
		CHILD_EDIT_TEXT_CTRL(TRUE,MAX_LEN_ACCOUNT_EDITOR_ADDRESS,MMI_PEEK_MAIL_ACCOUNT_EDITOR_EDITBOX_ADDRESS_CTRL_ID,MMI_PEEK_MAIL_ACCOUNT_EDITOR_ADDRESS_FORM_CTRL_ID),

	CHILD_FORM_CTRL(TRUE,GUIFORM_LAYOUT_ORDER,MMI_PEEK_MAIL_ACCOUNT_EDITOR_SIGNATURE_FORM_CTRL_ID,MMI_PEEK_MAIL_ACCOUNT_EDITOR_FORM_CTRL_ID),
		CHILD_LABEL_CTRL(GUILABEL_ALIGN_LEFT,FALSE,MMI_PEEK_MAIL_ACCOUNT_EDITOR_LABEL_SIGNATURE_CTRL_ID,MMI_PEEK_MAIL_ACCOUNT_EDITOR_SIGNATURE_FORM_CTRL_ID),
		CHILD_EDIT_TEXT_CTRL(TRUE,MAX_LEN_ACCOUNT_EDITOR_SIGNATURE,MMI_PEEK_MAIL_ACCOUNT_EDITOR_EDITBOX_SIGNATURE_CTRL_ID,MMI_PEEK_MAIL_ACCOUNT_EDITOR_SIGNATURE_FORM_CTRL_ID),

	WIN_SOFTKEY(TXT_PEEKMAIL_MENU, TXT_NULL, TXT_PEEKMAIL_BACK),
	END_WIN
};


// storage win
WINDOW_TABLE(MMI_PEEK_MAIL_MANAGER_STORAGE_WIN_TAB) =
{
	WIN_ID(MMI_PEEK_MAIL_MANAGER_STORAGE_WIN_ID),
	WIN_FUNC((uint32)HandlePeekMailManagerStorageWinMsg),
	WIN_TITLE(TXT_PEEKMAIL_MANAGER_STORAGE_TITLE),
	CREATE_LISTBOX_CTRL(GUILIST_RADIOLIST_E, MMI_PEEK_MAIL_MANAGER_STORAGE_CTRL_ID),
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

LOCAL MMI_RESULT_E HandlePeekMailManagerWinMsg(
                                         MMI_WIN_ID_T     win_id, 
                                         MMI_MESSAGE_ID_E msg_id, 
                                         DPARAM           param
                                         )
{
    MMI_RESULT_E        recode	 	 = MMI_RESULT_TRUE;
    GUI_LCD_DEV_INFO	lcd_dev_info = {GUI_LCD_0, GUI_BLOCK_0};
	MMI_CTRL_ID_T	  	ctrl_id		 = MMI_PEEK_MAIL_MANAGER_MENU_CTRL_ID;
	MMI_MENU_GROUP_ID_T group_id = 0;
	MMI_MENU_ID_T		menu_id  = 0;

	MMIPUB_TEXT_PARAM_T prompt_about 	= {0};
		
	MMI_STRING_T		about_text 		= {0};
	MMI_STRING_T		reset_text		= {0};
	
	wchar  				text[]			= L"PeekMail V 1.00.00\nPowered by Peek Inc;\nwww.peek9.com, Peek's genius clould makes devices smarter.";
	wchar  				reset_alert[]	= L"Are you sure to reset your account?";

	uint32 				time_period = 1000;

    lcd_dev_info.lcd_id		= GUI_MAIN_LCD_ID;
    lcd_dev_info.block_id	= GUI_BLOCK_MAIN;

	about_text.wstr_ptr = text;
	about_text.wstr_len = MMIAPICOM_Wstrlen(text);

	reset_text.wstr_ptr = reset_alert;
	reset_text.wstr_len = MMIAPICOM_Wstrlen(reset_alert);

	prompt_about.title_id = TXT_PEEKMAIL_MANAGER_ABOUT_PEEKMAIL;
	prompt_about.is_user_rect = FALSE;
	prompt_about.is_user_skb = FALSE;
	prompt_about.string = about_text;

    switch(msg_id)
    {
    case MSG_OPEN_WINDOW:	
		MMK_SetAtvCtrl(win_id, ctrl_id);
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

	case MSG_CTL_PENOK:
	case MSG_CTL_MIDSK:
	case MSG_CTL_OK:
	case MSG_APP_WEB:
		GUIMENU_GetId(ctrl_id, &group_id, &menu_id);
		switch (menu_id)
		{
			case ID_PEEKMAIL_EMAIL_ACCOUNTS:
				MMI_CreatePeekMailManagerAccountWin();
				break;
			case ID_PEEKMAIL_EMAIL_STORAGE:
				MMI_CreatePeekMailManagerStorageWin();
				break;
			case ID_PEEKMAIL_ABOUT:
				//MMIPUB_OpenQueryWinByTextPtr(PNULL,&about_text,PNULL, PNULL, PNULL);
				MMIPUB_OpenTextWin(&prompt_about);
				break;
			case ID_PEEKMAIL_RESET_PMAIL:			
				MMIPUB_OpenQueryWinByTextPtr(&reset_text,PNULL,IMAGE_PUBWIN_QUERY, PNULL, PNULL);
				break;
			default:
				break;
		}
		
    case MSG_APP_OK:
        break;
		
    case MSG_CLOSE_WINDOW:
        break;

	case MSG_PROMPTWIN_OK:
		MMIPUB_CloseQuerytWin(PNULL);
		// to Reset
		MMIPUB_OpenAlertWinByTextId(&time_period,TXT_PEEKMAIL_MANAGER_RESET_SUCCESSFULLY,TXT_NULL,IMAGE_PUBWIN_SUCCESS,PNULL,PNULL,MMIPUB_SOFTKEY_ONE,PNULL);
	break;
	
	case MSG_PROMPTWIN_CANCEL: 
		MMIPUB_CloseQuerytWin(PNULL);
		break;

    default:
        break;
    }

    return recode;
}


PUBLIC void AppendAccountListItem(
							  MMI_CTRL_ID_T    ctrl_id,
							  MMI_STRING_T  *  text_account_name,
							  MMI_STRING_T  *  text_first_name,
							  MMI_STRING_T  *  text_last_name,
							  MMI_STRING_T  *  text_address,
							  uint16		   is_active,
							  uint16		   is_primary
							  )
{
	GUILIST_ITEM_T			item_t	   = {0};
	GUILIST_ITEM_DATA_T 	item_data  = {0};
	uint32					item_index = 0;
	uint8				    first_name[64];
	uint8				    last_name[64];
	uint8				    address[128];
	
	MMI_IMAGE_ID_T			img_active 		= IMG_PEEKMAIL_ACTIVE_ICON;
	MMI_IMAGE_ID_T			img_de_active	= IMG_PEEKMAIL_DEACTIVE_ICON;
	MMI_IMAGE_ID_T			img_primary 	= IMG_PEEKMAIL_PRIMARY_ICON;

	uint8					name_and_address[128];
	wchar					wch_name_and_address[128];	
	MMI_STRING_T			str_name_and_address;

	memset(first_name, 0, strlen(first_name));
	memset(last_name, 0, strlen(last_name));
	MMIAPICOM_WstrToStr(text_first_name->wstr_ptr, first_name);
	MMIAPICOM_WstrToStr(text_last_name->wstr_ptr, last_name);	


	memset(address, 0, strlen(address));
	MMIAPICOM_WstrToStr(text_address->wstr_ptr, address);

	memset(name_and_address, 0, strlen(name_and_address));
	memset(wch_name_and_address, 0, strlen(wch_name_and_address));
	sprintf(name_and_address,	"%s %s, %s", first_name, last_name, address);
	MMIAPICOM_StrToWstr(name_and_address, wch_name_and_address);


	
	str_name_and_address.wstr_ptr 	= wch_name_and_address;
	str_name_and_address.wstr_len 	= MMIAPICOM_Wstrlen(wch_name_and_address);
	
 	item_t.item_style	 = GUIITEM_STYLE_ONE_TWO_LINE_TWO_ICON_TEXT_AND_TEXT;


	item_t.item_data_ptr = &item_data;

	item_data.item_content[0].item_data_type		= GUIITEM_DATA_IMAGE_ID;
	if (TRUE == is_primary)
	{
		item_data.item_content[0].item_data.image_id 	= img_primary;
	}
	else
	{
		item_data.item_content[0].item_data.image_id 	= IMAGE_NULL;	
	}

	item_data.item_content[1].item_data_type		= GUIITEM_DATA_IMAGE_ID;
	if (TRUE == is_active)
	{
		item_data.item_content[1].item_data.image_id 	= img_active;
	}
	else
	{
		item_data.item_content[1].item_data.image_id 	= img_de_active;		
	}
	
	item_data.item_content[2].item_data_type = GUIITEM_DATA_TEXT_BUFFER;
	item_data.item_content[2].item_data.text_buffer = *text_account_name;
	
	item_data.item_content[3].item_data_type = GUIITEM_DATA_TEXT_BUFFER;
	item_data.item_content[3].item_data.text_buffer = str_name_and_address;


	GUILIST_AppendItem(ctrl_id, &item_t);

	return;
}



LOCAL BOOLEAN is_deactive(uint16 account_index)
{
	uint16 index;

	for (index = 0; index<g_deactive_num; index++)
	{
		if (account_index == g_deactive_items[index])
		{
			return TRUE;
		}
	}

	return FALSE;
}


LOCAL MMI_RESULT_E HandlePeekMailManagerAccountWinMsg(
													 MMI_WIN_ID_T		win_id, 
													 MMI_MESSAGE_ID_E	 msg_id, 
													 DPARAM 			 param
													 )
{
    MMI_RESULT_E        recode	 	 = MMI_RESULT_TRUE;
    GUI_LCD_DEV_INFO	lcd_dev_info = {GUI_LCD_0, GUI_BLOCK_0};
	MMI_CTRL_ID_T	  	ctrl_id		 = MMI_PEEK_MAIL_MANAGER_ACCOUNT_CTRL_ID;

	uint16					account_num 		= 0;
	uint16					account_index 		= 0;
	char 					*account_file_name	= PNULL;
	uint16					file_name_len 		= 0;
	PEEKMAIL_ACCOUNT_STRUCT account_detail		= {0};


    lcd_dev_info.lcd_id		= GUI_MAIN_LCD_ID;
    lcd_dev_info.block_id	= GUI_BLOCK_MAIN;

    switch(msg_id)
    {
    case MSG_OPEN_WINDOW:
		memset(g_deactive_items, 0, strlen(g_deactive_items)*sizeof(uint16));
		account_num = PeekMail_GetAccountNum(ACCOUNT_INFO);
		MMK_SetAtvCtrl(win_id, ctrl_id);
		GUILIST_SetMaxItem(ctrl_id, 10, FALSE);
		GUILIST_SetNeedPrgbar(ctrl_id,TRUE);
		GUILIST_SetTitleIndexType(ctrl_id, GUILIST_TITLE_INDEX_DEFAULT);
		GUILIST_SetTextFont(ctrl_id, SONG_FONT_16, MMI_WHITE_COLOR);
		for (account_index = 1; account_index<=account_num; account_index++)
		{
			account_file_name = (char *)malloc(32 * sizeof(char));	
			memset(account_file_name, 0, sizeof(account_file_name));
			sprintf(account_file_name,  "%s%d", ACCOUNT_PATH, account_index);
			memset(&account_detail, 0, sizeof(account_detail));
			PeekMail_GetAccountStructure(account_file_name, &account_detail, ALL_INFO);

			AppendAccountListItem(ctrl_id,
								  account_detail.account_name, 
								  account_detail.first_name, 
								  account_detail.last_name, 
								  account_detail.address, 
								  account_detail.active_flag, 
								  account_detail.primary_flag
							  	 );
			if (0 == account_detail.active_flag)
			{
				g_deactive_items[g_deactive_num] = account_index;
				g_deactive_num++;
				
				GUILIST_SetItemGray(ctrl_id, account_index-1, TRUE);
			}
		}
		break;

    case MSG_GET_FOCUS:
        break;

    case MSG_LOSE_FOCUS:
        break;

    case MSG_FULL_PAINT:
        break;

    case MSG_CTL_CANCEL:
        MMK_CloseWin(win_id);
        break;

	/********************************
	* MSG_CTL_OK: is the left softkey      **
	* MSG_CTL_MIDSK: is the middle one **
	*********************************/

	case MSG_CTL_OK:
		MMI_CreatePeekMailManagerAccountMenuWin();
		break;

	case MSG_CTL_MIDSK:
	case MSG_CTL_PENOK:
		
		//MMIPUB_OpenQueryWinByTextId(TXT_MMS_EDIT_EXIT_WITHOUT_SAVE,IMAGE_PUBWIN_QUERY,PNULL,PNULL);
	/*	account_index = GUILIST_GetCurItemIndex(MMI_PEEK_MAIL_MANAGER_ACCOUNT_CTRL_ID);
		if (is_deactive(account_index))
		{
			// this item is gray
		
			MMIPUB_OpenQueryWinByTextId(TXT_MMS_EDIT_EXIT_WITHOUT_SAVE,IMAGE_PUBWIN_QUERY,PNULL,PNULL);
		}*/
		MMI_CreatePeekMailManagerAccountEditWin();
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


LOCAL MMI_RESULT_E HandlePeekMailManagerAccountMenuWinMsg(
                                         MMI_WIN_ID_T     	win_id, 
                                         MMI_MESSAGE_ID_E    msg_id, 
                                         DPARAM              param
                                         )
{
	MMI_RESULT_E		recode		= MMI_RESULT_TRUE;
	MMI_MENU_GROUP_ID_T group_id	= 0;
	MMI_MENU_ID_T		menu_id 	= 0;
	MMI_CTRL_ID_T		ctrl_id 	= MMI_PEEK_MAIL_MANAGER_ACCOUNT_MENU_CTRL_ID;
	

	switch(msg_id)
	{
	case MSG_OPEN_WINDOW:
		MMK_SetAtvCtrl(win_id, ctrl_id);
		break;
		
	case MSG_CTL_PENOK:
	case MSG_CTL_MIDSK:		
	case MSG_CTL_OK:
	case MSG_APP_OK:
	case MSG_APP_WEB:
		GUIMENU_GetId(ctrl_id,&group_id,&menu_id);
		switch (menu_id)
		{
			case ID_PEEKMAIL_MANAGER_EDIT_ACCOUNT:
				 MMI_CreatePeekMailManagerAccountEditWin();
				break;

			case ID_PEEKMAIL_MANAGER_NEW_ACCOUNT:
				 MMI_CreatePeekMailManagerAccountNewWin();
				break;
			
			case ID_PEEKMAIL_MANAGER_DEL_ACCOUNT:
				break;
			case ID_PEEKMAIL_MANAGER_SET_AS_PRIMARY:
				break;
			case ID_PEEKMAIL_MANAGER_DOWNLOAD_CONTACTS:
				break;
			case ID_PEEKMAIL_INBOX_FOLDER:
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


LOCAL MMI_RESULT_E HandlePeekMailAccountEditorWinMsg(
                                         MMI_WIN_ID_T     win_id, 
                                         MMI_MESSAGE_ID_E msg_id, 
                                         DPARAM           param
                                         )
{
    MMI_RESULT_E        recode 					= MMI_RESULT_TRUE;
    GUI_LCD_DEV_INFO	lcd_dev_info 			= {GUI_LCD_0, GUI_BLOCK_0};

	uint16 				account_index 			= 0;	
	uint8			   *account_file_name		= PNULL;
	
	MMI_CTRL_ID_T	  	ctrl_id_label_last_name 	= MMI_PEEK_MAIL_ACCOUNT_EDITOR_LABEL_FIRST_NAME_CTRL_ID;
	MMI_CTRL_ID_T	  	ctrl_id_label_first_name 	= MMI_PEEK_MAIL_ACCOUNT_EDITOR_LABEL_LAST_NAME_CTRL_ID;
	MMI_CTRL_ID_T	  	ctrl_id_label_password 		= MMI_PEEK_MAIL_ACCOUNT_EDITOR_LABEL_PASSWORD_CTRL_ID;
	MMI_CTRL_ID_T	  	ctrl_id_label_address 		= MMI_PEEK_MAIL_ACCOUNT_EDITOR_LABEL_ADDRESS_CTRL_ID;
	MMI_CTRL_ID_T	  	ctrl_id_label_signature 	= MMI_PEEK_MAIL_ACCOUNT_EDITOR_LABEL_SIGNATURE_CTRL_ID;

	MMI_CTRL_ID_T	  	ctrl_id_edit_last_name		= MMI_PEEK_MAIL_ACCOUNT_EDITOR_EDITBOX_FIRST_NAME_CTRL_ID;
	MMI_CTRL_ID_T	  	ctrl_id_edit_first_name 	= MMI_PEEK_MAIL_ACCOUNT_EDITOR_EDITBOX_LAST_NAME_CTRL_ID;
	MMI_CTRL_ID_T	  	ctrl_id_edit_password 		= MMI_PEEK_MAIL_ACCOUNT_EDITOR_EDITBOX_PASSWORD_CTRL_ID;
	MMI_CTRL_ID_T	  	ctrl_id_edit_address 		= MMI_PEEK_MAIL_ACCOUNT_EDITOR_EDITBOX_ADDRESS_CTRL_ID;
	MMI_CTRL_ID_T	  	ctrl_id_edit_signature 		= MMI_PEEK_MAIL_ACCOUNT_EDITOR_EDITBOX_SIGNATURE_CTRL_ID;

	
	LOCAL const wchar 	wch_last_name[] 		= L"Last Name:";
	LOCAL const wchar 	wch_first_name[] 		= L"First Name:";
	LOCAL const wchar 	wch_password[] 			= L"Password:";
	LOCAL const wchar 	wch_address[] 			= L"Address:";
	LOCAL const wchar 	wch_signature[] 		= L"Signature:";

	MMI_STRING_T		str_last_name 			= {0};
	MMI_STRING_T		str_first_name 			= {0};
	MMI_STRING_T		str_password 			= {0};
	MMI_STRING_T		str_address 			= {0};
	MMI_STRING_T		str_signature 			= {0};

	GUI_BG_T			bg						= {GUI_BG_COLOR, GUI_SHAPE_ROUNDED_RECT,0, MMI_WHITE_COLOR};

	GUIFORM_CHILD_WIDTH_T width_edit_last_name 	= {0};
	GUIFORM_CHILD_WIDTH_T width_edit_first_name	= {0};
	GUIFORM_CHILD_WIDTH_T width_edit_password	= {0};
	GUIFORM_CHILD_WIDTH_T width_edit_address	= {0};
	GUIFORM_CHILD_WIDTH_T width_edit_signature	= {0};

	GUIFORM_CHILD_HEIGHT_T height_edit_last_name 	= {0};
	GUIFORM_CHILD_HEIGHT_T height_edit_first_name 	= {0};
	GUIFORM_CHILD_HEIGHT_T height_edit_password		= {0};
	GUIFORM_CHILD_HEIGHT_T height_edit_address 		= {0};
	GUIFORM_CHILD_HEIGHT_T height_edit_signature 	= {0};

	uint16				   ver_space				= 10;

	PEEKMAIL_ACCOUNT_STRUCT   account_detail;

	BOOLEAN					is_disp = FALSE;
	

	width_edit_last_name.add_data				= 145;
	width_edit_last_name.type					= GUIFORM_CHLID_WIDTH_FIXED;
	width_edit_first_name.add_data				= 145;
	width_edit_first_name.type					= GUIFORM_CHLID_WIDTH_FIXED;
	width_edit_password.add_data				= 145;
	width_edit_password.type					= GUIFORM_CHLID_WIDTH_FIXED;
	width_edit_address.add_data					= 145;
	width_edit_address.type						= GUIFORM_CHLID_WIDTH_FIXED;
	width_edit_signature.add_data				= 240;
	width_edit_signature.type					= GUIFORM_CHLID_WIDTH_FIXED;

	height_edit_last_name.add_data				= 15;
	height_edit_last_name.type					= GUIFORM_CHLID_HEIGHT_FIXED;
	height_edit_first_name.add_data				= 15;
	height_edit_first_name.type					= GUIFORM_CHLID_HEIGHT_FIXED;
	height_edit_password.add_data				= 15;
	height_edit_password.type					= GUIFORM_CHLID_HEIGHT_FIXED;
	height_edit_address.add_data				= 15;
	height_edit_address.type					= GUIFORM_CHLID_HEIGHT_FIXED;
	height_edit_signature.add_data				= 30;
	height_edit_signature.type					= GUIFORM_CHLID_HEIGHT_FIXED;

    lcd_dev_info.lcd_id							= GUI_MAIN_LCD_ID;
    lcd_dev_info.block_id						= GUI_BLOCK_MAIN;

	str_last_name.wstr_ptr 						= wch_last_name;
	str_last_name.wstr_len 						= MMIAPICOM_Wstrlen(wch_last_name);
	str_first_name.wstr_ptr 					= wch_first_name;
	str_first_name.wstr_len 					= MMIAPICOM_Wstrlen(wch_first_name);
	str_password.wstr_ptr 						= wch_password;
	str_password.wstr_len 						= MMIAPICOM_Wstrlen(wch_password);
	str_address.wstr_ptr 						= wch_address;
	str_address.wstr_len 						= MMIAPICOM_Wstrlen(wch_address);
	str_signature.wstr_ptr 						= wch_signature;
	str_signature.wstr_len 						= MMIAPICOM_Wstrlen(wch_signature);

    switch(msg_id)
    {
    case MSG_OPEN_WINDOW:

		GUIFORM_SetStyle(MMI_PEEK_MAIL_ACCOUNT_EDITOR_FIRST_NAME_FORM_CTRL_ID, GUIFORM_STYLE_NORMAL);	
		GUILABEL_SetText(ctrl_id_label_last_name, &str_last_name, FALSE);
		GUILABEL_SetFont(ctrl_id_label_last_name, SONG_FONT_14, MMI_BACKGROUND_COLOR);
		GUIFORM_SetChildWidth(MMI_PEEK_MAIL_ACCOUNT_EDITOR_FIRST_NAME_FORM_CTRL_ID,ctrl_id_edit_last_name, &width_edit_last_name);
		MMK_SetAtvCtrl(win_id, ctrl_id_edit_last_name);

		GUIFORM_SetStyle(MMI_PEEK_MAIL_ACCOUNT_EDITOR_LAST_NAME_FORM_CTRL_ID, GUIFORM_STYLE_NORMAL);	
		GUILABEL_SetText(ctrl_id_label_first_name, &str_first_name, FALSE);
		GUILABEL_SetFont(ctrl_id_label_first_name, SONG_FONT_14, MMI_BACKGROUND_COLOR);
		GUIFORM_SetChildWidth(MMI_PEEK_MAIL_ACCOUNT_EDITOR_LAST_NAME_FORM_CTRL_ID,ctrl_id_edit_first_name, &width_edit_first_name);
		//GUIFORM_SetSpace(MMI_PEEK_MAIL_COMPOSER_TO_FORM_CTRL_ID, PNULL, &ver_space);
		MMK_SetAtvCtrl(win_id, ctrl_id_edit_first_name);

		GUIFORM_SetStyle(MMI_PEEK_MAIL_ACCOUNT_EDITOR_PASSWORD_FORM_CTRL_ID, GUIFORM_STYLE_NORMAL);	
		GUILABEL_SetText(ctrl_id_label_password, &str_password, FALSE);
		GUILABEL_SetFont(ctrl_id_label_password, SONG_FONT_14, MMI_BACKGROUND_COLOR);		
		GUIFORM_SetChildWidth(MMI_PEEK_MAIL_ACCOUNT_EDITOR_PASSWORD_FORM_CTRL_ID,ctrl_id_edit_password, &width_edit_password);
		//GUIFORM_SetChildHeight(MMI_PEEK_MAIL_COMPOSER_SUBJECT_FORM_CTRL_ID,ctrl_id_edit_subject, &height_edit_subject);
		GUIFORM_SetSpace(MMI_PEEK_MAIL_ACCOUNT_EDITOR_PASSWORD_FORM_CTRL_ID, PNULL, &ver_space);

		GUIFORM_SetStyle(MMI_PEEK_MAIL_ACCOUNT_EDITOR_ADDRESS_FORM_CTRL_ID, GUIFORM_STYLE_NORMAL);	
		GUILABEL_SetText(ctrl_id_label_address, &str_address, FALSE);
		GUILABEL_SetFont(ctrl_id_label_address, SONG_FONT_14, MMI_BACKGROUND_COLOR);		
		GUIFORM_SetChildWidth(MMI_PEEK_MAIL_ACCOUNT_EDITOR_ADDRESS_FORM_CTRL_ID,ctrl_id_edit_address, &width_edit_address);
		//GUIFORM_SetChildHeight(MMI_PEEK_MAIL_COMPOSER_SUBJECT_FORM_CTRL_ID,ctrl_id_edit_subject, &height_edit_subject);
		GUIFORM_SetSpace(MMI_PEEK_MAIL_ACCOUNT_EDITOR_ADDRESS_FORM_CTRL_ID, PNULL, &ver_space);

		GUIFORM_SetStyle(MMI_PEEK_MAIL_ACCOUNT_EDITOR_SIGNATURE_FORM_CTRL_ID, GUIFORM_STYLE_NORMAL);	
		GUILABEL_SetText(ctrl_id_label_signature, &str_signature, FALSE);
		GUILABEL_SetFont(ctrl_id_label_signature, SONG_FONT_14, MMI_BACKGROUND_COLOR);		
		GUIFORM_SetChildWidth(MMI_PEEK_MAIL_ACCOUNT_EDITOR_SIGNATURE_FORM_CTRL_ID,ctrl_id_edit_signature, &width_edit_signature);
		//GUIFORM_SetChildHeight(MMI_PEEK_MAIL_COMPOSER_SUBJECT_FORM_CTRL_ID,ctrl_id_edit_subject, &height_edit_subject);
		GUIFORM_SetSpace(MMI_PEEK_MAIL_ACCOUNT_EDITOR_SIGNATURE_FORM_CTRL_ID, PNULL, &ver_space);
		
		if (NEW != g_editor_type)
		{			
			account_index = GUILIST_GetCurItemIndex(MMI_PEEK_MAIL_MANAGER_ACCOUNT_CTRL_ID);
			account_file_name = (char *)malloc(32 * sizeof(char));	
			memset(account_file_name, 0, sizeof(account_file_name));
			sprintf(account_file_name,	"%s%d", ACCOUNT_PATH, account_index+1);
			memset(&account_detail, 0, sizeof(account_detail));
			PeekMail_GetAccountStructure(account_file_name, &account_detail, ALL_INFO);

			GUIEDIT_SetString(ctrl_id_edit_last_name, account_detail.last_name->wstr_ptr, account_detail.last_name->wstr_len);
			GUIEDIT_SetFont(ctrl_id_edit_last_name,SONG_FONT_14);
			GUIEDIT_SetString(ctrl_id_edit_first_name, account_detail.first_name->wstr_ptr, account_detail.first_name->wstr_len);
			GUIEDIT_SetFont(ctrl_id_edit_first_name,SONG_FONT_14);
			GUIEDIT_SetString(ctrl_id_edit_address, account_detail.address->wstr_ptr, account_detail.address->wstr_len);
			GUIEDIT_SetFont(ctrl_id_edit_address,SONG_FONT_14);
			GUIEDIT_SetString(ctrl_id_edit_signature, account_detail.signature->wstr_ptr, account_detail.signature->wstr_len);
			GUIEDIT_SetFont(ctrl_id_edit_signature,SONG_FONT_14);
			//GUIEDIT_SetDispImIcon(ctrl_id_edit_signature, &is_disp, &is_disp);
			//GUIEDIT_SetIm(ctrl_id_edit_signature,GUIIM_TYPE_NONE,GUIIM_TYPE_NONE);
			//GUIEDIT_SetListStyle(ctrl_id_edit_signature,GUIEDIT_LIST_STYLE_ALL);
			//GUIEDIT_SetStyle(ctrl_id_edit_signature,GUIEDIT_STYLE_MULTI);
		}	
			
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
        //MMK_CreateWin((uint32 *)MMI_PEEK_MAIL_COMPOSER_MENU_TAB, PNULL);
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


LOCAL void AppendStorageListItem(
							  MMI_CTRL_ID_T    ctrl_id,
							  MMI_TEXT_ID_T    text_storage_type_id
							  )
{
	GUILIST_ITEM_T			item_t	   = {0};
	GUILIST_ITEM_DATA_T 	item_data  = {0};
	uint32					item_index = 0;

	item_t.item_style	 = GUIITEM_STYLE_ONE_LINE_RADIO;

	item_t.item_data_ptr = &item_data;

	item_data.item_content[0].item_data_type = GUIITEM_DATA_TEXT_ID;
	item_data.item_content[0].item_data.text_id = text_storage_type_id;
	
	GUILIST_AppendItem(ctrl_id, &item_t);

	return;
}


LOCAL MMI_RESULT_E HandlePeekMailManagerStorageWinMsg(
                                         MMI_WIN_ID_T     	win_id, 
                                         MMI_MESSAGE_ID_E    msg_id, 
                                         DPARAM              param
                                         )
{
	MMI_RESULT_E		recode		= MMI_RESULT_TRUE;
	MMI_MENU_GROUP_ID_T group_id	= 0;
	MMI_MENU_ID_T		menu_id 	= 0;
	MMI_CTRL_ID_T		ctrl_id 	= MMI_PEEK_MAIL_MANAGER_STORAGE_CTRL_ID;
	

	switch(msg_id)
    {
    case MSG_OPEN_WINDOW:
		MMK_SetAtvCtrl(win_id, ctrl_id);
		GUILIST_SetMaxItem(ctrl_id, 2, FALSE);
		GUILIST_SetTitleIndexType(ctrl_id, GUILIST_TITLE_INDEX_DEFAULT);
		GUILIST_SetTextFont(ctrl_id, SONG_FONT_22, MMI_WHITE_COLOR);
		GUILIST_SetSelectedItem(ctrl_id,0,TRUE);
		AppendStorageListItem(ctrl_id, TXT_PEEKMAIL_MANAGER_STORAGE_TYPE_PHONE);
		AppendStorageListItem(ctrl_id, TXT_PEEKMAIL_MANAGER_STORAGE_TYPE_SDCARD);	
		break;

    case MSG_GET_FOCUS:
        break;

    case MSG_LOSE_FOCUS:
        break;

    case MSG_FULL_PAINT:
        break;

    case MSG_CTL_CANCEL:
        MMK_CloseWin(win_id);
        break;

	/********************************
	* MSG_CTL_OK: is the left softkey      **
	* MSG_CTL_MIDSK: is the middle one **
	*********************************/

	case MSG_CTL_OK:
	case MSG_CTL_MIDSK:
	case MSG_CTL_PENOK:
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
PUBLIC void MMI_CreatePeekMailManagerWin(void)
{
   MMK_CreateWin((uint32*)MMI_PEEK_MAIL_MANAGER_WIN_TAB, PNULL);
}

PUBLIC void MMI_CreatePeekMailManagerAccountWin(void)
{
   MMK_CreateWin((uint32*)MMI_PEEK_MAIL_MANAGER_ACCOUNT_WIN_TAB, PNULL);
}

PUBLIC void MMI_CreatePeekMailManagerAccountMenuWin(void)
{
   MMK_CreateWin((uint32*)MMI_PEEK_MAIL_MANAGER_ACCOUNT_MENU_WIN_TAB, PNULL);
}

PUBLIC void MMI_CreatePeekMailManagerAccountEditWin(void)
{
	g_editor_type = EDIT;
	MMK_CreateWin((uint32*)MMI_PEEK_MAIL_ACCOUNT_EDITOR_WIN_TAB, PNULL);
}

PUBLIC void MMI_CreatePeekMailManagerAccountNewWin(void)
{
	g_editor_type = NEW;
	MMK_CreateWin((uint32*)MMI_PEEK_MAIL_ACCOUNT_EDITOR_WIN_TAB, PNULL);
}

PUBLIC void MMI_CreatePeekMailManagerStorageWin(void)
{
	MMK_CreateWin((uint32*)MMI_PEEK_MAIL_MANAGER_STORAGE_WIN_TAB, PNULL);
}

