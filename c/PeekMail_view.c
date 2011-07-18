/*****************************************************************************
** File Name:      PeekMail_view.c                                               *
** Author:                                                                   *
** Date:             6/13/2011                                                 *
** Copyright:      2011 Peek Inc. All Rights Reserved.       *
** Description:    This file is used to describe call log                    *
******************************************************************************
**                         Important Edit History                            *
** --------------------------------------------------------------------------*
**   DATE           NAME             DESCRIPTION                               *
** 6/13/2011    Liu, Zhengbo            Create                                   *
******************************************************************************/
#include "PeekMail_view.h"
#include "PeekMail_id.h"
#include "PeekMail_image.h"

/**--------------------------------------------------------------------------*/
/**						 GLOBAL DEFINITION								  		  */
/**--------------------------------------------------------------------------*/
WINDOW_TABLE(MMI_PEEK_MAIL_VIEW_WIN_TAB) =
{
	WIN_ID(MMI_PEEK_MAIL_VIEW_WIN_ID),
	WIN_FUNC((uint32)HandlePeekMailViewWinMsg),
	WIN_STATUSBAR,
	CREATE_RICHTEXT_CTRL(MMI_PEEK_MAIL_VIEW_RICHTEXT_CTRL_ID),
	WIN_SOFTKEY(TXT_PEEKMAIL_MENU, TXT_NULL, TXT_PEEKMAIL_BACK),
	END_WIN
};

WINDOW_TABLE(MMI_PEEK_MAIL_VIEW_PARSE_WIN_TAB) =
{
	WIN_ID(MMI_PEEK_MAIL_VIEW_PARSE_WIN_ID),
	WIN_FUNC((uint32)HandlePeekMailViewParseWinMsg),
	WIN_STYLE(WS_HAS_PROMPT_WIN),
	WIN_SOFTKEY(TXT_NULL, TXT_NULL, TXT_PEEKMAIL_BACK),
	END_WIN
};

int8 *filePath = PNULL;
MMI_CTRL_ID_T ctrl_id;
PEEKMAIL_MAIL_STRUCT mailStructure;
wchar *parseString = PNULL;

LOCAL MMI_RESULT_E HandlePeekMailViewWinMsg(
														MMI_WIN_ID_T     	win_id, 
														MMI_MESSAGE_ID_E    msg_id, 
														DPARAM              param)
{
	MMI_RESULT_E		recode = MMI_RESULT_TRUE;
	GUI_LCD_DEV_INFO	lcd_dev_info = {GUI_MAIN_LCD_ID, GUI_BLOCK_MAIN};
//	GUI_RECT_T			rect = {0, 0, 239, 319};
	wchar				*item_to_str = PNULL;
	wchar				*item_from_str = PNULL;
	wchar				unicode_file_name[256];

	wchar				phone_txt[] = L"This is a phone number.";
	wchar				email_txt[] = L"This is an email address.";
	wchar				url_txt[] = L"This is a URL.";

	switch(msg_id)
	{
		case MSG_OPEN_WINDOW:
		{
			GUIRICHTEXT_ITEM_T item_to = {0};
			GUIRICHTEXT_ITEM_T item_from = {0};
			GUIRICHTEXT_ITEM_T item_text = {0};
			int32 buf_len = 0;
			MMIFILE_HANDLE hFile;
			uint16 index = GUILIST_GetCurItemIndex(ctrl_id);
			GUILIST_ITEM_T *curItem = GUILIST_GetItemPtrByIndex(ctrl_id, index);

			PeekMail_GetMailStructure(filePath, &mailStructure, ALL_INFO);
			MMIAPICOM_StrToWstr(filePath, unicode_file_name);
			hFile = MMIFILE_CreateFile(
						unicode_file_name,
						SFS_MODE_WRITE | SFS_MODE_OPEN_EXISTING,
						PNULL,
						PNULL);
			if (!mailStructure.read_flag) {
				curItem->item_data_ptr->item_content[0].item_data.image_id = IMG_PEEKMAIL_READ_ICON;
				MMIFILE_WriteFile(hFile, READ_FLAG, READ_FLAG_LEN, &buf_len, PNULL);
			}
			MMIFILE_CloseFile(hFile);
/*
			HANDLE hOutFile = CreateFile(
										output_filename,
										GENERIC_ALL,
										FILE_SHARE_READ,
										0,
										OPEN_ALWAYS,
										0,
										0);

			DWORD len = 0;
			GUI_FONT_T font = SONG_FONT_14;
			
			
			if (hFile == INVALID_HANDLE_VALUE)
				return -1;
			if (hOutFile == INVALID_HANDLE_VALUE)
				return -1;

			len = GetFileSize(hFile, 0) - READ_FLAG_LEN;
			bufsize = len + 1;
			buffer = (char *)malloc(bufsize * sizeof(char));
			w_buffer = (wchar *)malloc(bufsize * sizeof(wchar));

			*(buffer + len) = 0;
			ReadFile(hFile, read_buffer, READ_FLAG_LEN, &buf_len, 0);
			ReadFile(hFile, buffer, MAX_MAIL_LEN, &buf_len, 0);
			CloseHandle(hFile);
			if (read_buffer[READ_FLAG_POS] == '0') {
				read_buffer[READ_FLAG_POS] = '1';
				curItem->item_data_ptr->item_content[0].item_data.image_id = IMG_HELLOPEEK_MAIL_READ_ICON;
				hFile = CreateFile(
								filePath,
								GENERIC_ALL,
								FILE_SHARE_READ,
								0,
								OPEN_EXISTING,
								0,
								0);
				WriteFile(hFile, read_buffer, READ_FLAG_LEN, &buf_len, 0);
				CloseHandle(hFile);
			}

			MMIAPICOM_StrToWstr(buffer, w_buffer);
			str.wstr_ptr = w_buffer;
			str.wstr_len = MMIAPICOM_Wstrlen(w_buffer);
*/

			MMK_SetAtvCtrl(MMI_PEEK_MAIL_VIEW_WIN_ID, MMI_PEEK_MAIL_VIEW_RICHTEXT_CTRL_ID);
			GUIRICHTEXT_SetFocusMode(MMI_PEEK_MAIL_VIEW_RICHTEXT_CTRL_ID, GUIRICHTEXT_FOCUS_SHIFT_BASIC);
//			GUIRICHTEXT_SetFont(MMI_PEEK_MAIL_VIEW_RICHTEXT_CTRL_ID, font);
			PeekMailViewParse(&mailStructure, &item_to_str, &item_from_str);
			item_to.text_type = GUIRICHTEXT_TEXT_BUF;
			item_to.text_data.buf.str_ptr = item_to_str;
			item_to.text_data.buf.len = MMIAPICOM_Wstrlen(item_to.text_data.buf.str_ptr);
			item_to.text_set_font = TRUE;
			item_to.setting_font = SONG_FONT_12;
			item_to.align_type = GUIRICHTEXT_ALIGN_LEFT;
			item_to.tag_type = GUIRICHTEXT_TAG_PARSE;
			item_to.frame_type = GUIRICHTEXT_FRAME_NORMAL;
			GUIRICHTEXT_AddItem(MMI_PEEK_MAIL_VIEW_RICHTEXT_CTRL_ID, &item_to, &index);

			item_from.text_type = GUIRICHTEXT_TEXT_BUF;
			item_from.text_data.buf.str_ptr = item_from_str;
			item_from.text_data.buf.len = MMIAPICOM_Wstrlen(item_from.text_data.buf.str_ptr);
			item_from.text_set_font = TRUE;
			item_from.setting_font = SONG_FONT_14;
			item_from.align_type = GUIRICHTEXT_ALIGN_LEFT;
			item_from.tag_type = GUIRICHTEXT_TAG_PARSE;
			item_from.frame_type = GUIRICHTEXT_FRAME_NORMAL;
			GUIRICHTEXT_AddItem(MMI_PEEK_MAIL_VIEW_RICHTEXT_CTRL_ID, &item_from, &index);

			item_text.text_type = GUIRICHTEXT_TEXT_BUF;
			item_text.text_data.buf.str_ptr = mailStructure.text->wstr_ptr;
			item_text.text_data.buf.len = mailStructure.text->wstr_len;
			item_text.text_set_font = TRUE;
			item_text.setting_font = SONG_FONT_14;
			item_text.align_type = GUIRICHTEXT_ALIGN_LEFT;
			item_text.tag_type = GUIRICHTEXT_TAG_PARSE;
			item_text.frame_type = GUIRICHTEXT_FRAME_NORMAL;
			GUIRICHTEXT_AddItem(MMI_PEEK_MAIL_VIEW_RICHTEXT_CTRL_ID, &item_text, &index);
			GUIRICHTEXT_Update(MMI_PEEK_MAIL_VIEW_RICHTEXT_CTRL_ID);
			GUIRICHTEXT_ScrollToItem(MMI_PEEK_MAIL_VIEW_RICHTEXT_CTRL_ID, 1);
		}
			break;
		case MSG_GET_FOCUS:
			break;
		case MSG_LOSE_FOCUS:
			break;
		case MSG_FULL_PAINT:
			break;
		case MSG_CTL_CANCEL:
		case MSG_APP_CANCEL:
			MMK_CloseWin(win_id);
			break;
		case MSG_APP_OK:
		case MSG_CTL_OK:
			break;
		case MSG_APP_WEB:
		case MSG_CTL_PENOK:
		{
			GUIRICHTEXT_FOCUS_ELEM_T element;
			GUIRICHTEXT_GetFocusElement(MMI_PEEK_MAIL_VIEW_RICHTEXT_CTRL_ID, &element);
			switch(element.type)
			{
				case GUIRICHTEXT_FOCUS_PHONENUM:
					parseString = (wchar *)malloc(sizeof(phone_txt));
					MMIAPICOM_Wstrcpy(parseString, phone_txt);
					MMK_CreateWin((uint32*)MMI_PEEK_MAIL_VIEW_PARSE_WIN_TAB, PNULL);
					break;
				case GUIRICHTEXT_FOCUS_EMAIL:
					parseString = (wchar *)malloc(sizeof(email_txt));
					MMIAPICOM_Wstrcpy(parseString, email_txt);
					MMK_CreateWin((uint32*)MMI_PEEK_MAIL_VIEW_PARSE_WIN_TAB, PNULL);
					break;
				case GUIRICHTEXT_FOCUS_URL:
					parseString = (wchar *)malloc(sizeof(url_txt));
					MMIAPICOM_Wstrcpy(parseString, url_txt);
					MMK_CreateWin((uint32*)MMI_PEEK_MAIL_VIEW_PARSE_WIN_TAB, PNULL);
					break;
				default:
					break;
			}
		}
			break;
		case MSG_CLOSE_WINDOW:
			PeekMail_DestroyMailStruct(&mailStructure, FALSE);
			break;
		default:
			recode = MMI_RESULT_FALSE;
			break;
	}
	return recode;
}

PUBLIC void MMI_CreatePeekMailViewWin(const int8 *folder, MMI_CTRL_ID_T id)
{
	int16 index = GUILIST_GetTotalItemNum(id) - GUILIST_GetCurItemIndex(id);
	int8 filename[MAX_INDEX_LEN];
	MMIAPICOM_Int2Str(index, filename, MAX_INDEX_LEN);
	filePath = (int8 *)malloc((strlen(folder) + strlen(filename) + 1) * sizeof(int8));
	if (filePath == PNULL) {
		return;
	}
	strcpy(filePath, folder);
	strcat(filePath, filename);
	ctrl_id = id;

	MMK_CreateWin((uint32*)MMI_PEEK_MAIL_VIEW_WIN_TAB, PNULL);
}

LOCAL void PeekMailViewParse(
									PEEKMAIL_MAIL_STRUCT *mailStructure,
									wchar **item_to_str,
									wchar **item_from_str)
{
	MMI_STRING_T to_s = {L"To: ", 4};
	wchar to[] = L"To: ";
	wchar cc[] = L"Cc: ";
	wchar from[] = L"From: ";
	wchar endline[] = L"\r\n";

	*item_to_str = (wchar *)malloc((MMIAPICOM_Wstrlen(to) + mailStructure->to->wstr_len + 1)
				* sizeof(wchar));
	MMIAPICOM_Wstrcpy(*item_to_str, to);
	MMIAPICOM_Wstrcat(*item_to_str, mailStructure->to->wstr_ptr);

	
	*item_from_str = (wchar *)malloc((MMIAPICOM_Wstrlen(to) + mailStructure->from->wstr_len
					+ MMIAPICOM_Wstrlen(endline) + mailStructure->subject->wstr_len
					+ MMIAPICOM_Wstrlen(endline) + mailStructure->date->wstr_len
					+ 2 + mailStructure->time->wstr_len + 1)
					* sizeof(wchar));
	MMIAPICOM_Wstrcpy(*item_from_str, from);
	MMIAPICOM_Wstrcat(*item_from_str, mailStructure->from->wstr_ptr);
	MMIAPICOM_Wstrcat(*item_from_str, endline);
	MMIAPICOM_Wstrcat(*item_from_str, mailStructure->subject->wstr_ptr);
	MMIAPICOM_Wstrcat(*item_from_str, endline);
	MMIAPICOM_Wstrcat(*item_from_str, mailStructure->date->wstr_ptr);
	MMIAPICOM_Wstrcat(*item_from_str, L", ");
	MMIAPICOM_Wstrcat(*item_from_str, mailStructure->time->wstr_ptr);
}

LOCAL MMI_RESULT_E HandlePeekMailViewParseWinMsg(
                                         						MMI_WIN_ID_T     win_id, 
                                         						MMI_MESSAGE_ID_E msg_id, 
                                         						DPARAM           param)
{
    MMI_RESULT_E        recode	 	 = MMI_RESULT_TRUE;
    GUI_LCD_DEV_INFO	lcd_dev_info = {GUI_LCD_0, GUI_BLOCK_0};
	GUI_RECT_T			rect = {50, 90, 190, 230};

	lcd_dev_info.lcd_id 	= GUI_MAIN_LCD_ID;
	lcd_dev_info.block_id	= GUI_BLOCK_MAIN;

    switch(msg_id)
    {
    case MSG_OPEN_WINDOW:
	{
		GUISTR_STYLE_T text_style = {0};
		GUISTR_STATE_T text_state = GUISTR_STATE_ALIGN;
		MMI_STRING_T text_str = {0};

		text_str.wstr_ptr = parseString;
		text_str.wstr_len= MMIAPICOM_Wstrlen(parseString);
		text_style.align = ALIGN_HVMIDDLE;
		text_style.font = SONG_FONT_16;
		text_style.font_color = MMI_BACKGROUND_COLOR;
		GUI_FillRect(&lcd_dev_info,rect, MMI_WHITE_COLOR);
		GUISTR_DrawTextToLCDInRect(&lcd_dev_info, &rect, &rect, &text_str, &text_style, text_state, 0);
    }
		break;

    case MSG_GET_FOCUS:
        break;

    case MSG_LOSE_FOCUS:
        break;

    case MSG_FULL_PAINT:
        break;

    //case MSG_KEYDOWN_CANCEL:
    case MSG_APP_CANCEL:
    case MSG_CTL_CANCEL:
		free(parseString);
        MMK_CloseWin(win_id);
        break;

	/********************************
	* MSG_CTL_OK: is the left softkey      **
	* MSG_CTL_MIDSK: is the middle one **
	*********************************/

	case MSG_CTL_OK:
        break;

	case MSG_CTL_MIDSK:
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

