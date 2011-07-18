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


#include "PeekMail_main.h"
#include "PeekMail_text.h"
#include "PeekMail_image.h"
#include "PeekMail_id.h"
#include "PeekMail_menutable.h"
#include "PeekMail_sent.h"
#include "PeekMail_saved.h"
#include "PeekMail_composer.h"
#include "PeekMail_get_mail_info.h"

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

// Composer
WINDOW_TABLE(MMI_PEEK_MAIL_COMPOSER_WIN_TAB) =
{
	WIN_ID(MMI_PEEK_MAIL_COMPOSER_WIN_ID),
	WIN_FUNC((uint32)HandlePeekMailComposerWinMsg),
	WIN_TITLE(TXT_PEEKMAIL_COMPOSER_TITLE),
	

	CREATE_FORM_CTRL(GUIFORM_LAYOUT_ORDER, MMI_PEEK_MAIL_COMPOSER_FORM_CTRL_ID),


	CHILD_FORM_CTRL(TRUE,GUIFORM_LAYOUT_SBS,MMI_PEEK_MAIL_COMPOSER_FROM_FORM_CTRL_ID,MMI_PEEK_MAIL_COMPOSER_FORM_CTRL_ID),
		CHILD_LABEL_CTRL(GUILABEL_ALIGN_LEFT,FALSE,MMI_PEEK_MAIL_COMPOSER_LABEL_FROM_CTRL_ID,MMI_PEEK_MAIL_COMPOSER_FROM_FORM_CTRL_ID),
		CHILD_EDIT_TEXT_CTRL(TRUE,MAX_LEN_COMPOSER_FROM,MMI_PEEK_MAIL_COMPOSER_EDITBOX_FROM_CTRL_ID,MMI_PEEK_MAIL_COMPOSER_FROM_FORM_CTRL_ID),


	CHILD_FORM_CTRL(TRUE,GUIFORM_LAYOUT_SBS,MMI_PEEK_MAIL_COMPOSER_TO_FORM_CTRL_ID,MMI_PEEK_MAIL_COMPOSER_FORM_CTRL_ID),
		CHILD_LABEL_CTRL(GUILABEL_ALIGN_LEFT,FALSE,MMI_PEEK_MAIL_COMPOSER_LABEL_TO_CTRL_ID,MMI_PEEK_MAIL_COMPOSER_TO_FORM_CTRL_ID),
		CHILD_EDIT_TEXT_CTRL(TRUE,MAX_LEN_COMPOSER_TO,MMI_PEEK_MAIL_COMPOSER_EDITBOX_TO_CTRL_ID,MMI_PEEK_MAIL_COMPOSER_TO_FORM_CTRL_ID),

	CHILD_FORM_CTRL(TRUE,GUIFORM_LAYOUT_SBS,MMI_PEEK_MAIL_COMPOSER_CC_FORM_CTRL_ID,MMI_PEEK_MAIL_COMPOSER_FORM_CTRL_ID),
		CHILD_LABEL_CTRL(GUILABEL_ALIGN_LEFT,FALSE,MMI_PEEK_MAIL_COMPOSER_LABEL_CC_CTRL_ID,MMI_PEEK_MAIL_COMPOSER_CC_FORM_CTRL_ID),
		CHILD_EDIT_TEXT_CTRL(TRUE,MAX_LEN_COMPOSER_TO,MMI_PEEK_MAIL_COMPOSER_EDITBOX_CC_CTRL_ID,MMI_PEEK_MAIL_COMPOSER_CC_FORM_CTRL_ID),

	CHILD_FORM_CTRL(TRUE,GUIFORM_LAYOUT_SBS,MMI_PEEK_MAIL_COMPOSER_BCC_FORM_CTRL_ID,MMI_PEEK_MAIL_COMPOSER_FORM_CTRL_ID),
		CHILD_LABEL_CTRL(GUILABEL_ALIGN_LEFT,FALSE,MMI_PEEK_MAIL_COMPOSER_LABEL_BCC_CTRL_ID,MMI_PEEK_MAIL_COMPOSER_BCC_FORM_CTRL_ID),
		CHILD_EDIT_TEXT_CTRL(TRUE,MAX_LEN_COMPOSER_TO,MMI_PEEK_MAIL_COMPOSER_EDITBOX_BCC_CTRL_ID,MMI_PEEK_MAIL_COMPOSER_BCC_FORM_CTRL_ID),


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


PEEKMAIL_COMPOSER_TYPE_E g_composer_type = NEW;
char *					 g_filename = PNULL;
MMI_HANDLE_T			 g_reply_win_h;
MMI_HANDLE_T			 g_reply_all_win_h;
MMI_HANDLE_T			 g_forward_win_h;


/**--------------------------------------------------------------------------*
 **                         FUNCTION DEFINITION                              *
 **--------------------------------------------------------------------------*/
/*****************************************************************************/
//  Description : open hello peek windows
//  Global resource dependence : 
//  Author: Song,Han
//  Note: 
/*****************************************************************************/
LOCAL void PeekMailComposerSaveEmail(const int8 *folder, const int8 *folderInfo)
{
	uint16 			index = PeekMail_GetMailNum(folderInfo);
	int8 			filename[MAX_INDEX_LEN];
	int8 			*filePath = PNULL;
	int8 			*temp = PNULL;
	int8 			*output = PNULL;
	MMI_STRING_T 	string;
	int16 			buf_len = 0;
	wchar			unicode_file_name[256];
	MMIFILE_HANDLE	hFile;	

	int8 endline[] = "\r\n";
	int8 read[] = "read:1\r\n";
	int8 date[] = "date:7.17.2011\r\n";
	int8 time[] = "time:12:31:23\r\n";
	int8 from[] = "from:aaa@peek9.com\r\n";

	int8 test[] = "read:1\r\ndate:7.17.2011\r\ntime:12:31:23\r\nfrom:aaa@peek9.com\r\n";
	
	index++;
	MMIAPICOM_Int2Str(index, filename, MAX_INDEX_LEN);
	filePath = (int8 *)malloc((strlen(folder) + strlen(filename) + 1) * sizeof(int8));
	strcpy(filePath, folder);
	strcat(filePath, filename);

	MMIAPICOM_StrToWstr(filePath, unicode_file_name);
	hFile = MMIFILE_CreateFile(
				unicode_file_name,
				SFS_MODE_WRITE | SFS_MODE_CREATE_NEW,
				PNULL,
				PNULL);
	MMIFILE_WriteFile(hFile, test, strlen(test), &buf_len, PNULL);

	GUIEDIT_GetString(MMI_PEEK_MAIL_COMPOSER_EDITBOX_TO_CTRL_ID, &string);
	temp = (int8 *)malloc((string.wstr_len + 1) * sizeof(int8));
	output = (int8 *)malloc((strlen(TO_STR) + string.wstr_len + strlen(endline) + 1) * sizeof(int8));
	MMIAPICOM_WstrToStr(string.wstr_ptr, temp);
	strcpy(output, TO_STR);
	strcat(output, temp);
	strcat(output, endline);
	free(temp);
	MMIFILE_WriteFile(hFile, output, strlen(output), &buf_len, PNULL);
	free(output);

	GUIEDIT_GetString(MMI_PEEK_MAIL_COMPOSER_EDITBOX_SUBJECT_CTRL_ID, &string);
	temp = (int8 *)malloc((string.wstr_len + 1) * sizeof(int8));
	output = (int8 *)malloc((strlen(SUBJECT_STR) + string.wstr_len + strlen(endline) + 1) * sizeof(int8));
	MMIAPICOM_WstrToStr(string.wstr_ptr, temp);
	strcpy(output, SUBJECT_STR);
	strcat(output, temp);
	strcat(output, endline);
	free(temp);
	MMIFILE_WriteFile(hFile, output, strlen(output), &buf_len, PNULL);
	free(output);

	GUIEDIT_GetString(MMI_PEEK_MAIL_COMPOSER_EDITBOX_TEXT_CTRL_ID, &string);
	temp = (int8 *)malloc((string.wstr_len + 1) * sizeof(int8));
	output = (int8 *)malloc((strlen(TEXT_STR) + string.wstr_len + strlen(endline) + 1) * sizeof(int8));
	MMIAPICOM_WstrToStr(string.wstr_ptr, temp);
	strcpy(output, TEXT_STR);
	strcat(output, endline);
	strcat(output, temp);
	free(temp);
	MMIFILE_WriteFile(hFile, output, strlen(output), &buf_len, PNULL);
	free(output);
	MMIFILE_CloseFile(hFile);

	MMIAPICOM_StrToWstr(folderInfo, unicode_file_name);
	hFile = MMIFILE_CreateFile(
				unicode_file_name,
				SFS_MODE_WRITE | SFS_MODE_CREATE_ALWAYS,
				PNULL,
				PNULL);
	MMIFILE_WriteFile(hFile, filename, strlen(filename), &buf_len, PNULL);
	MMIFILE_CloseFile(hFile);
}

LOCAL MMI_RESULT_E HandlePeekMailComposerWinMsg(
                                         MMI_WIN_ID_T     win_id, 
                                         MMI_MESSAGE_ID_E msg_id, 
                                         DPARAM           param
                                         )
{
    MMI_RESULT_E        recode 					= MMI_RESULT_TRUE;
	
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
	MMI_STRING_T		str_sent_by				= {0};

	GUI_BG_T			bg						= {GUI_BG_COLOR, GUI_SHAPE_ROUNDED_RECT,0, MMI_WHITE_COLOR};

	GUIFORM_CHILD_WIDTH_T width_edit_from 		= {0};
	GUIFORM_CHILD_WIDTH_T width_edit_to 		= {0};
	GUIFORM_CHILD_WIDTH_T width_edit_subject	= {0};

	GUIFORM_CHILD_HEIGHT_T height_edit_from 	= {0};
	GUIFORM_CHILD_HEIGHT_T height_edit_to 		= {0};
	GUIFORM_CHILD_HEIGHT_T height_edit_subject	= {0};
	GUIFORM_CHILD_HEIGHT_T height_edit_text 	= {0};

	uint16				   ver_space			= 10;

	PEEKMAIL_MAIL_STRUCT   mail_detail;
	
	wchar  text_reply[] 		= L"Reply";
	wchar  text_reply_all[] 	= L"Reply All";
	wchar  text_forward[] 		= L"Forward";

	wchar  text_Re[]			= L"Re: ";
	wchar  text_Fwd[]			= L"Fwd: ";
	wchar  text_sent_by[]		= L"\n\n--\nsent by Peek Mail\n";

	uint8* ch_date				= PNULL;
	uint8* ch_time				= PNULL;
	uint8* ch_from				= PNULL;
	uint8* ch_text 				= PNULL;
	uint8* ch_subject			= PNULL;
	uint8* ch_to				= PNULL;

	wchar* wch_reform_text 		= PNULL;
	uint8* ch_reform_text		= PNULL;

	uint16  text_reply_len		= MMIAPICOM_Wstrlen(text_reply);
	uint16  text_reply_all_len 	= MMIAPICOM_Wstrlen(text_reply_all);
	uint16  text_forward_len 	= MMIAPICOM_Wstrlen(text_forward);
	uint16  text_Re_sub_len		= 0;
	uint16  text_Fwd_sub_len    = 0;
	uint16  text_reform_len		= 0;

	
	width_edit_from.add_data					= 175;
	width_edit_from.type						= GUIFORM_CHLID_WIDTH_FIXED;
	width_edit_to.add_data						= 175;
	width_edit_to.type							= GUIFORM_CHLID_WIDTH_FIXED;
	width_edit_subject.add_data					= 175;
	width_edit_subject.type						= GUIFORM_CHLID_WIDTH_FIXED;
	
	height_edit_from.add_data					= 15;
	height_edit_from.type						= GUIFORM_CHLID_HEIGHT_FIXED;
	height_edit_to.add_data						= 15;
	height_edit_to.type							= GUIFORM_CHLID_HEIGHT_FIXED;
	height_edit_subject.add_data				= 15;
	height_edit_subject.type					= GUIFORM_CHLID_HEIGHT_FIXED;
	height_edit_text.add_data					= 45;
	height_edit_text.type						= GUIFORM_CHLID_HEIGHT_FIXED;

	str_from.wstr_ptr 							= wch_from;
	str_from.wstr_len 							= MMIAPICOM_Wstrlen(wch_from);
	str_to.wstr_ptr 							= wch_to;
	str_to.wstr_len 							= MMIAPICOM_Wstrlen(wch_to);
	str_subject.wstr_ptr 						= wch_subject;
	str_subject.wstr_len 						= MMIAPICOM_Wstrlen(wch_subject);

	str_sent_by.wstr_ptr						= text_sent_by;
	str_sent_by.wstr_len						= MMIAPICOM_Wstrlen(text_sent_by);

    switch(msg_id)
    {
    case MSG_OPEN_WINDOW:

		GUIFORM_SetStyle(MMI_PEEK_MAIL_COMPOSER_FROM_FORM_CTRL_ID, GUIFORM_STYLE_NORMAL);	
		GUILABEL_SetText(ctrl_id_label_from, &str_from, FALSE);
		GUILABEL_SetFont(ctrl_id_label_from, SONG_FONT_14, MMI_BACKGROUND_COLOR);
		GUIFORM_SetChildWidth(MMI_PEEK_MAIL_COMPOSER_FROM_FORM_CTRL_ID,ctrl_id_edit_from, &width_edit_from);
		MMK_SetAtvCtrl(win_id, ctrl_id_edit_from);

		GUIFORM_SetChildDisplay(MMI_PEEK_MAIL_COMPOSER_FORM_CTRL_ID, MMI_PEEK_MAIL_COMPOSER_CC_FORM_CTRL_ID, GUIFORM_CHILD_DISP_HIDE);
		GUIFORM_SetChildDisplay(MMI_PEEK_MAIL_COMPOSER_FORM_CTRL_ID, MMI_PEEK_MAIL_COMPOSER_BCC_FORM_CTRL_ID, GUIFORM_CHILD_DISP_HIDE);

		GUIFORM_SetStyle(MMI_PEEK_MAIL_COMPOSER_TO_FORM_CTRL_ID, GUIFORM_STYLE_NORMAL);	
		GUILABEL_SetText(ctrl_id_label_to, &str_to, FALSE);
		GUILABEL_SetFont(ctrl_id_label_to, SONG_FONT_14, MMI_BACKGROUND_COLOR);
		GUIFORM_SetChildWidth(MMI_PEEK_MAIL_COMPOSER_TO_FORM_CTRL_ID,ctrl_id_edit_to, &width_edit_to);
		//MMK_SetAtvCtrl(win_id, ctrl_id_edit_to);

		GUIFORM_SetStyle(MMI_PEEK_MAIL_COMPOSER_SUBJECT_FORM_CTRL_ID, GUIFORM_STYLE_NORMAL);	
		GUILABEL_SetText(ctrl_id_label_subject, &str_subject, FALSE);
		GUILABEL_SetFont(ctrl_id_label_subject, SONG_FONT_14, MMI_BACKGROUND_COLOR);		
		GUIFORM_SetChildWidth(MMI_PEEK_MAIL_COMPOSER_SUBJECT_FORM_CTRL_ID,ctrl_id_edit_subject, &width_edit_subject);
		GUIFORM_SetSpace(MMI_PEEK_MAIL_COMPOSER_SUBJECT_FORM_CTRL_ID, PNULL, &ver_space);

		GUIEDIT_SetString(MMI_PEEK_MAIL_COMPOSER_EDITBOX_TEXT_CTRL_ID, str_sent_by.wstr_ptr, str_sent_by.wstr_len);
		GUIEDIT_SetFont(MMI_PEEK_MAIL_COMPOSER_EDITBOX_TEXT_CTRL_ID,SONG_FONT_14);

		GUIFORM_SetStyle(MMI_PEEK_MAIL_COMPOSER_TEXT_FORM_CTRL_ID, GUIFORM_STYLE_NORMAL);	

		if (NEW != g_composer_type)
		{
			memset(&mail_detail, 0, sizeof(mail_detail));
			PeekMail_GetMailStructure(g_filename, &mail_detail, RE_FWD_INFO);

			ch_date 	= (uint8 *)malloc((mail_detail.date->wstr_len+1)*sizeof(uint8));
			ch_time 	= (uint8 *)malloc((mail_detail.time->wstr_len+1)*sizeof(uint8));
			ch_from 	= (uint8 *)malloc((mail_detail.from->wstr_len+1)*sizeof(uint8));
			ch_text 	= (uint8 *)malloc((mail_detail.text->wstr_len+1)*sizeof(uint8));
			ch_subject 	= (uint8 *)malloc((mail_detail.subject->wstr_len+1)*sizeof(uint8));
			ch_to 		= (uint8 *)malloc((mail_detail.to->wstr_len+1)*sizeof(uint8));

			MMIAPICOM_WstrToStr(mail_detail.date->wstr_ptr, ch_date);
			MMIAPICOM_WstrToStr(mail_detail.time->wstr_ptr, ch_time);
			MMIAPICOM_WstrToStr(mail_detail.from->wstr_ptr, ch_from);
			MMIAPICOM_WstrToStr(mail_detail.text->wstr_ptr, ch_text);
			MMIAPICOM_WstrToStr(mail_detail.subject->wstr_ptr, ch_subject);
			MMIAPICOM_WstrToStr(mail_detail.to->wstr_ptr, ch_to);

			switch (g_composer_type)
			{
				case REPLY:
				{
					uint8*	ch_subject_cpy;
					uint8*	ch_Re_subject;
					wchar*  wch_Re_subject;
					uint32	ch_reform_text_len;

					GUIWIN_SetTitleText(g_reply_win_h, text_reply, text_reply_len, FALSE);
					GUIEDIT_SetString(MMI_PEEK_MAIL_COMPOSER_EDITBOX_TO_CTRL_ID, mail_detail.from->wstr_ptr, mail_detail.from->wstr_len);
					GUIEDIT_SetFont(MMI_PEEK_MAIL_COMPOSER_EDITBOX_TO_CTRL_ID,SONG_FONT_14);

					ch_subject_cpy = (uint8 *)malloc((mail_detail.subject->wstr_len+1) * sizeof(uint8));
					MMIAPICOM_WstrToStr(mail_detail.subject->wstr_ptr, ch_subject_cpy);
					ch_Re_subject = (uint8 *)malloc((mail_detail.subject->wstr_len+5) * sizeof(uint8));
 					sprintf(ch_Re_subject,  "Re: %s", ch_subject_cpy);
					wch_Re_subject = (wchar *)malloc((strlen(ch_Re_subject)+1)*sizeof(wchar));
					MMIAPICOM_StrToWstr(ch_Re_subject, wch_Re_subject);
					text_Re_sub_len = MMIAPICOM_Wstrlen(wch_Re_subject);
					GUIEDIT_SetString(MMI_PEEK_MAIL_COMPOSER_EDITBOX_SUBJECT_CTRL_ID, wch_Re_subject, text_Re_sub_len);
					GUIEDIT_SetFont(MMI_PEEK_MAIL_COMPOSER_EDITBOX_SUBJECT_CTRL_ID,SONG_FONT_14);

					ch_reform_text = (uint8 *)malloc((strlen(ch_date)+strlen(ch_time)+strlen(ch_from)+strlen(ch_text)+256) * sizeof(uint8)); 
					//memset(ch_reform_text, 0, strlen(ch_reform_text));
					sprintf(ch_reform_text,  "\n\nOn %s at %s, <%s> wrote:\n%s\n\n--\nsent by Peek Mail\n", 
												  ch_date, ch_time, ch_from, ch_text);
					wch_reform_text = (wchar *)malloc((strlen(ch_reform_text)+1) * sizeof(wchar));
					//memset(wch_reform_text, 0, text_reform_len);
					MMIAPICOM_StrToWstr(ch_reform_text, wch_reform_text);
					text_reform_len = MMIAPICOM_Wstrlen(wch_reform_text);
					GUIEDIT_SetString(MMI_PEEK_MAIL_COMPOSER_EDITBOX_TEXT_CTRL_ID, wch_reform_text, text_reform_len);
					GUIEDIT_SetFont(MMI_PEEK_MAIL_COMPOSER_EDITBOX_TEXT_CTRL_ID,SONG_FONT_14);

					free(ch_subject_cpy);
					free(ch_Re_subject);
					free(wch_Re_subject);
					free(wch_reform_text);
					free(ch_reform_text);
					break;
				}
				case REPLY_ALL:
				{
					uint8*	ch_subject_cpy;
					uint8*	ch_Re_subject;
					wchar*  wch_Re_subject;
					uint32	ch_reform_text_len;
					
					GUIWIN_SetTitleText(g_reply_all_win_h, text_reply_all, text_reply_all_len, FALSE);
					GUIEDIT_SetString(MMI_PEEK_MAIL_COMPOSER_EDITBOX_TO_CTRL_ID, mail_detail.from->wstr_ptr, mail_detail.from->wstr_len);
					GUIEDIT_SetFont(MMI_PEEK_MAIL_COMPOSER_EDITBOX_TO_CTRL_ID,SONG_FONT_14);

					ch_subject_cpy = (uint8 *)malloc((mail_detail.subject->wstr_len+1) * sizeof(uint8));
					MMIAPICOM_WstrToStr(mail_detail.subject->wstr_ptr, ch_subject_cpy);
					ch_Re_subject = (uint8 *)malloc((mail_detail.subject->wstr_len+5) * sizeof(uint8));
 					sprintf(ch_Re_subject,  "Re: %s", ch_subject_cpy);
					wch_Re_subject = (wchar *)malloc((strlen(ch_Re_subject)+1)*sizeof(wchar));
					MMIAPICOM_StrToWstr(ch_Re_subject, wch_Re_subject);
					text_Re_sub_len = MMIAPICOM_Wstrlen(wch_Re_subject);
					GUIEDIT_SetString(MMI_PEEK_MAIL_COMPOSER_EDITBOX_SUBJECT_CTRL_ID, wch_Re_subject, text_Re_sub_len);
					GUIEDIT_SetFont(MMI_PEEK_MAIL_COMPOSER_EDITBOX_SUBJECT_CTRL_ID,SONG_FONT_14);

					ch_reform_text = (uint8 *)malloc((strlen(ch_date)+strlen(ch_time)+strlen(ch_from)+strlen(ch_text)+256) * sizeof(uint8)); 
					//memset(ch_reform_text, 0, strlen(ch_reform_text));
					sprintf(ch_reform_text,  "\n\nOn %s at %s, <%s> wrote:\n%s\n\n--\nsent by Peek Mail\n", 
												  ch_date, ch_time, ch_from, ch_text);
					wch_reform_text = (wchar *)malloc((strlen(ch_reform_text)+1) * sizeof(wchar));
					//memset(wch_reform_text, 0, text_reform_len);
					MMIAPICOM_StrToWstr(ch_reform_text, wch_reform_text);					
					text_reform_len = MMIAPICOM_Wstrlen(wch_reform_text);
					GUIEDIT_SetString(MMI_PEEK_MAIL_COMPOSER_EDITBOX_TEXT_CTRL_ID, wch_reform_text, text_reform_len);
					GUIEDIT_SetFont(MMI_PEEK_MAIL_COMPOSER_EDITBOX_TEXT_CTRL_ID,SONG_FONT_14);

					free(ch_subject_cpy);
					free(ch_Re_subject);
					free(wch_Re_subject);
					free(wch_reform_text);
					free(ch_reform_text);
					break;
				}
				case FORWARD:
				{
					uint8*	ch_subject_cpy;
					uint8*	ch_Fwd_subject;
					wchar*  wch_Fwd_subject;
		
					GUIWIN_SetTitleText(g_forward_win_h, text_forward, text_forward_len, FALSE);
					GUIEDIT_SetString(MMI_PEEK_MAIL_COMPOSER_EDITBOX_TO_CTRL_ID, mail_detail.from->wstr_ptr, mail_detail.from->wstr_len);
					GUIEDIT_SetFont(MMI_PEEK_MAIL_COMPOSER_EDITBOX_TO_CTRL_ID,SONG_FONT_14);

					ch_subject_cpy = (uint8 *)malloc((mail_detail.subject->wstr_len+1) * sizeof(uint8));
					MMIAPICOM_WstrToStr(mail_detail.subject->wstr_ptr, ch_subject_cpy);
					ch_Fwd_subject = (uint8 *)malloc((mail_detail.subject->wstr_len+6) * sizeof(uint8));
 					sprintf(ch_Fwd_subject,  "Fwd: %s", ch_subject_cpy);
					wch_Fwd_subject = (wchar *)malloc((strlen(ch_Fwd_subject)+1)*sizeof(wchar));
					MMIAPICOM_StrToWstr(ch_Fwd_subject, wch_Fwd_subject);
					text_Fwd_sub_len = MMIAPICOM_Wstrlen(wch_Fwd_subject);
					GUIEDIT_SetString(MMI_PEEK_MAIL_COMPOSER_EDITBOX_SUBJECT_CTRL_ID, wch_Fwd_subject, text_Fwd_sub_len);
					GUIEDIT_SetFont(MMI_PEEK_MAIL_COMPOSER_EDITBOX_SUBJECT_CTRL_ID,SONG_FONT_14);

					ch_reform_text = (uint8 *)malloc((strlen(ch_from)+strlen(ch_date)+strlen(ch_time)+strlen(ch_subject)+strlen(ch_to)+strlen(ch_text)+256) * sizeof(uint8)); 
					//memset(ch_reform_text, 0, strlen(ch_reform_text));
					sprintf(ch_reform_text,  "\n\n--Forwarded message--\nFrom: <%s>\nDate: %s at %s\nSubject: %s\nTo: %s\n\n\n%s\n\n--\nsent by Peek Mail\n", 
												  ch_from, ch_date, ch_time, ch_subject, ch_to, ch_text);
					wch_reform_text = (wchar *)malloc((strlen(ch_reform_text)+1) * sizeof(wchar));
					//memset(wch_reform_text, 0, text_reform_len);
					MMIAPICOM_StrToWstr(ch_reform_text, wch_reform_text);
					text_reform_len = MMIAPICOM_Wstrlen(wch_reform_text);
					GUIEDIT_SetString(MMI_PEEK_MAIL_COMPOSER_EDITBOX_TEXT_CTRL_ID, wch_reform_text, text_reform_len);
					GUIEDIT_SetFont(MMI_PEEK_MAIL_COMPOSER_EDITBOX_TEXT_CTRL_ID,SONG_FONT_14);
					
					free(ch_subject_cpy);
					free(ch_Fwd_subject);
					free(wch_Fwd_subject);
					free(wch_reform_text);
					free(ch_reform_text);
					break;
				}
				default:
					break;
			}

			g_composer_type = NEW;
			free(ch_date);
			free(ch_time);
			free(ch_from);
			free(ch_text);
			free(ch_subject);
			free(ch_to);
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
        MMK_CreateWin((uint32 *)MMI_PEEK_MAIL_COMPOSER_MENU_TAB, PNULL);
        break;

	case MSG_CTL_MIDSK:
		//MMK_CloseWin(win_id);
		break;
		
    case MSG_APP_OK:
        break;
		
    case MSG_CLOSE_WINDOW:
        break;

	case MSG_PROMPTWIN_OK:
		MMIPUB_CloseQuerytWin(PNULL);
		MMK_CloseWin(win_id);
	break;

	case MSG_PROMPTWIN_CANCEL: 
		MMIPUB_CloseQuerytWin(PNULL);
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
	MMI_CTRL_ID_T	  	ctrl_id			= MMI_PEEK_MAIL_COMPOSER_MENU_CTRL_ID;
	MMI_CTRL_ID_T 		subject_ctrl_id = MMI_PEEK_MAIL_COMPOSER_EDITBOX_SUBJECT_CTRL_ID;
	MMI_CTRL_ID_T		text_ctrl_id 	= MMI_PEEK_MAIL_COMPOSER_EDITBOX_TEXT_CTRL_ID;
	MMI_STRING_T		text_string 	= {0};
	MMI_STRING_T 		subject_string	= {0};
	
	uint32  prompt_last_period = 1000;

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
				PeekMailComposerSaveEmail(SENT_PATH,SENT_INFO);
				MMIPUB_OpenAlertWinByTextId(&prompt_last_period,TXT_PEEKMAIL_COMPOSER_PROMPT_TEXT_SAVED_SENT,TXT_NULL,IMAGE_PUBWIN_SUCCESS,PNULL,PNULL,MMIPUB_SOFTKEY_ONE,PNULL);
				break;

			case ID_PEEKMAIL_SAVE_AS_DRAFT:
				PeekMailComposerSaveEmail(DRAFTS_PATH,DRAFTS_INFO);
				MMIPUB_OpenAlertWinByTextId(&prompt_last_period,TXT_PEEKMAIL_COMPOSER_PROMPT_TEXT_SAVED_DRAFT,TXT_NULL,IMAGE_PUBWIN_SUCCESS,PNULL,PNULL,MMIPUB_SOFTKEY_ONE,PNULL);
				break;
			
			case ID_PEEKMAIL_ADD_CC:
			{
				MMI_STRING_T 			str_cc = {0};
				wchar 					wch_cc[] = L"Cc:";
				GUIFORM_CHILD_WIDTH_T 	width_edit_cc = {0};
				
				str_cc.wstr_ptr 		= &wch_cc;
				str_cc.wstr_len 		= MMIAPICOM_Wstrlen(&wch_cc);
				width_edit_cc.add_data 	= 175;
				width_edit_cc.type 		= GUIFORM_CHLID_WIDTH_FIXED;
				
				GUIFORM_SetStyle(MMI_PEEK_MAIL_COMPOSER_CC_FORM_CTRL_ID, GUIFORM_STYLE_NORMAL);	
				GUILABEL_SetText(MMI_PEEK_MAIL_COMPOSER_LABEL_CC_CTRL_ID, &str_cc, FALSE);
				GUILABEL_SetFont(MMI_PEEK_MAIL_COMPOSER_LABEL_CC_CTRL_ID, SONG_FONT_14, MMI_BACKGROUND_COLOR);
				GUIFORM_SetChildWidth(MMI_PEEK_MAIL_COMPOSER_CC_FORM_CTRL_ID,MMI_PEEK_MAIL_COMPOSER_EDITBOX_CC_CTRL_ID, &width_edit_cc);
				MMK_SetAtvCtrl(MMI_PEEK_MAIL_COMPOSER_WIN_ID, MMI_PEEK_MAIL_COMPOSER_EDITBOX_CC_CTRL_ID);
				
				GUIFORM_SetChildDisplay(MMI_PEEK_MAIL_COMPOSER_FORM_CTRL_ID, MMI_PEEK_MAIL_COMPOSER_CC_FORM_CTRL_ID, GUIFORM_CHILD_DISP_NORMAL);
				MMK_SetAtvCtrl(MMI_PEEK_MAIL_COMPOSER_WIN_ID, MMI_PEEK_MAIL_COMPOSER_CC_FORM_CTRL_ID);
				break;
			}
			case ID_PEEKMAIL_ADD_BCC:
			{	
				MMI_STRING_T 			str_bcc = {0};
				wchar 					wch_bcc[] = L"Bcc:";
				GUIFORM_CHILD_WIDTH_T 	width_edit_bcc = {0};
				
				str_bcc.wstr_ptr 			= &wch_bcc;
				str_bcc.wstr_len 			= MMIAPICOM_Wstrlen(&wch_bcc);
				width_edit_bcc.add_data 	= 175;
				width_edit_bcc.type 		= GUIFORM_CHLID_WIDTH_FIXED;
				
				GUIFORM_SetStyle(MMI_PEEK_MAIL_COMPOSER_BCC_FORM_CTRL_ID, GUIFORM_STYLE_NORMAL);	
				GUILABEL_SetText(MMI_PEEK_MAIL_COMPOSER_LABEL_BCC_CTRL_ID, &str_bcc, FALSE);
				GUILABEL_SetFont(MMI_PEEK_MAIL_COMPOSER_LABEL_BCC_CTRL_ID, SONG_FONT_14, MMI_BACKGROUND_COLOR);
				GUIFORM_SetChildWidth(MMI_PEEK_MAIL_COMPOSER_BCC_FORM_CTRL_ID,MMI_PEEK_MAIL_COMPOSER_EDITBOX_BCC_CTRL_ID, &width_edit_bcc);
				MMK_SetAtvCtrl(MMI_PEEK_MAIL_COMPOSER_WIN_ID, MMI_PEEK_MAIL_COMPOSER_EDITBOX_BCC_CTRL_ID);

				GUIFORM_SetChildDisplay(MMI_PEEK_MAIL_COMPOSER_FORM_CTRL_ID, MMI_PEEK_MAIL_COMPOSER_BCC_FORM_CTRL_ID, GUIFORM_CHILD_DISP_NORMAL);
				MMK_SetAtvCtrl(MMI_PEEK_MAIL_COMPOSER_WIN_ID, MMI_PEEK_MAIL_COMPOSER_BCC_FORM_CTRL_ID);
				break;
			}
			case ID_PEEKMAIL_INBOX_FOLDER:
				MMI_CreatePeekMailWin();
				break;
			case ID_PEEKMAIL_CONTACTS:
				break;
			case ID_PEEKMAIL_PEEKMAIL_MANAGER:
				MMI_CreatePeekMailManagerWin();
				break;
			case ID_PEEKMAIL_EXIT:
				SCI_MEMSET( &subject_string, 0, sizeof( MMI_STRING_T ) );
				GUIEDIT_GetString(subject_ctrl_id, &subject_string);
				SCI_MEMSET( &text_string, 0, sizeof( MMI_STRING_T ) );
				GUIEDIT_GetString(text_ctrl_id, &text_string);
				
				if (0 == subject_string.wstr_len && 0 == text_string.wstr_len)	
				{
					// close the edit window
					MMK_CloseWin(MMI_PEEK_MAIL_COMPOSER_WIN_ID);			
				}
				else
				{
					MMIPUB_OpenQueryWinByTextId(TXT_MMS_EDIT_EXIT_WITHOUT_SAVE,IMAGE_PUBWIN_QUERY,PNULL,PNULL);
					//GUISOFTKEY_SetTextId(MMI_HANDLE_T win_handle,MMI_CTRL_ID_T ctrl_id,MMI_TEXT_ID_T leftsoft_id,MMI_TEXT_ID_T middlesoft_id,MMI_TEXT_ID_T rightsoft_id,BOOLEAN is_need_update)
					MMK_CloseWin(win_id);
				}
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
	g_composer_type = NEW;
    MMK_CreateWin((uint32*)MMI_PEEK_MAIL_COMPOSER_WIN_TAB, PNULL);
}


PUBLIC void MMI_CreatePeekMailReplyWin(char * filename)
{
	g_composer_type = REPLY;
	g_filename = (char *)malloc((strlen(filename)+1)*sizeof(char));
	strcpy(g_filename, filename);
    g_reply_win_h = MMK_CreateWin((uint32*)MMI_PEEK_MAIL_COMPOSER_WIN_TAB, PNULL);
}


PUBLIC void MMI_CreatePeekMailReplyAllWin(char * filename)
{
	g_composer_type = REPLY_ALL;
	g_filename = (char *)malloc((strlen(filename)+1)*sizeof(char));
	strcpy(g_filename, filename);
    g_reply_all_win_h = MMK_CreateWin((uint32*)MMI_PEEK_MAIL_COMPOSER_WIN_TAB, PNULL);
}


PUBLIC void MMI_CreatePeekMailForwardWin(char * filename)
{
	g_composer_type = FORWARD;
	g_filename = (char *)malloc((strlen(filename)+1)*sizeof(char));
	strcpy(g_filename, filename);
    g_forward_win_h = MMK_CreateWin((uint32*)MMI_PEEK_MAIL_COMPOSER_WIN_TAB, PNULL);
}


