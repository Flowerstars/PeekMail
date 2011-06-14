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

/**--------------------------------------------------------------------------*/
/**						 GLOBAL DEFINITION								  		  */
/**--------------------------------------------------------------------------*/
WINDOW_TABLE(MMI_PEEK_MAIL_VIEW_WIN_TAB) =
{
	WIN_ID(MMI_PEEK_MAIL_VIEW_WIN_ID),
	WIN_FUNC((uint32)HandlePeekMailViewWinMsg),
	WIN_STATUSBAR,
	CREATE_RICHTEXT_CTRL(MMI_PEEK_MAIL_VIEW_RICHTEXT_CTRL_ID),
	WIN_SOFTKEY(STXT_OPTION, TXT_NULL, STXT_RETURN),
	END_WIN
};

LOCAL MMI_RESULT_E HandlePeekMailViewWinMsg(
													MMI_WIN_ID_T     	win_id, 
													MMI_MESSAGE_ID_E    msg_id, 
													DPARAM              param
													)
{
	MMI_RESULT_E		recode = MMI_RESULT_TRUE;
	GUI_LCD_DEV_INFO	lcd_dev_info = {GUI_MAIN_LCD_ID, GUI_BLOCK_MAIN};
	GUI_RECT_T			rect = {0, 0, 239, 319};
	uint16				index = 0;
	DWORD 				bufsize = 0;
	char				*buffer = PNULL;
	wchar 				*w_buffer = PNULL;
	MMI_STRING_T		str = {0};
	char 				filename[] = "PeekMail\\Inbox\\test_email.txt";
	char 				output_filename[] = "PeekMail\\Inbox\\out_email.txt";
	char				copy_filename[] = "PeekMail\\Inbox\\copy_email.txt";


	switch(msg_id)
	{
		case MSG_OPEN_WINDOW:
		{
			GUIRICHTEXT_ITEM_T item_data = {0};
			HANDLE hFile = CreateFile(
										filename,
										GENERIC_READ,
										FILE_SHARE_READ,
										0,
										OPEN_EXISTING,
										0,
										0);
			HANDLE hOutFile = CreateFile(
										output_filename,
										GENERIC_ALL,
										FILE_SHARE_READ,
										0,
										OPEN_ALWAYS,
										0,
										0);

			DWORD len = 0;
			DWORD buf_len = 0;
			GUI_FONT_T font = SONG_FONT_14;
			
			if (hFile == INVALID_HANDLE_VALUE)
				return -1;
			if (hOutFile == INVALID_HANDLE_VALUE)
				return -1;

			len = GetFileSize(hFile, 0);
			bufsize = len + 1;
			buffer = (char *)malloc(bufsize * sizeof(char));
			w_buffer = (wchar *)malloc(bufsize * sizeof(wchar));

			*(buffer + len) = 0;
			ReadFile(hFile, buffer, len, &buf_len, 0);
			CloseHandle(hFile);
			WriteFile(hOutFile, buffer, len, &buf_len, 0);
			CloseHandle(hOutFile);

			MMIAPICOM_StrToWstr(buffer, w_buffer);
			str.wstr_ptr = w_buffer;
			str.wstr_len = MMIAPICOM_Wstrlen(w_buffer);

			MMK_SetAtvCtrl(MMI_PEEK_MAIL_VIEW_WIN_ID, MMI_PEEK_MAIL_VIEW_RICHTEXT_CTRL_ID);
			GUIRICHTEXT_SetFocusMode(MMI_PEEK_MAIL_VIEW_RICHTEXT_CTRL_ID, GUIRICHTEXT_FOCUS_SHIFT_BASIC);
			GUIRICHTEXT_SetFont(MMI_PEEK_MAIL_VIEW_RICHTEXT_CTRL_ID, font);

			item_data.text_type = GUIRICHTEXT_TEXT_BUF;
			item_data.text_data.buf.str_ptr = str.wstr_ptr;
			item_data.text_data.buf.len = str.wstr_len;
//			item_data.setting_font = SONG_FONT_14;
			item_data.align_type = GUIRICHTEXT_ALIGN_LEFT;
			item_data.tag_type = GUIRICHTEXT_TAG_PARSE;
			item_data.frame_type = GUIRICHTEXT_FRAME_NORMAL;
			CopyFile(output_filename, copy_filename, 1);
			DeleteFile(output_filename);
			GUIRICHTEXT_AddItem(MMI_PEEK_MAIL_VIEW_RICHTEXT_CTRL_ID, &item_data, &index);
		}
			break;
		case MSG_GET_FOCUS:
			break;
		case MSG_LOSE_FOCUS:
			break;
		case MSG_FULL_PAINT:
//			GUI_FillRect(&lcd_dev_info, rect, MMI_BACKGROUND_COLOR);
			break;

		case MSG_CLOSE_WINDOW:
		case MSG_APP_CANCEL:
		case MSG_CTL_CANCEL:
			MMK_CloseWin(win_id);
			break;
		case MSG_APP_OK:
		case MSG_CTL_OK:
		case MSG_APP_WEB:
			break;
		default:
			recode = MMI_RESULT_FALSE;
			break;
	}
	return recode;
}

PUBLIC void MMI_CreatePeekMailViewWin(void)
{
	MMK_CreateWin((uint32*)MMI_PEEK_MAIL_VIEW_WIN_TAB, PNULL);
}

