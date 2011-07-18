/***************************************************************************
** File Name:      PeekMail_get_mail_info.h                                             *
** Author:                                                                 *
** Date:           5/20/2011                                               *
** Copyright:      2011 Peek Inc. All Rights Reserved.       *
** Description:    This file is used to describe the data struct of        *
**                      system, application, window and control                 *
****************************************************************************
**                         Important Edit History                          *
** ------------------------------------------------------------------------*
**   DATE           NAME             DESCRIPTION                               *
** 5.20/2011    Song,Han               Create                                    *
**																		   *
****************************************************************************/
#ifndef _PEEKMAIL_GET_MAIL_INFO_H_
#define _PEEKMAIL_GET_MAIL_INFO_H_

/*----------------------------------------------------------------------------*/
/*                          Include Files                                     */
/*----------------------------------------------------------------------------*/ 

#include "std_header.h"
#include "mmk_type.h"
#include "mmi_filemgr.h"

/*----------------------------------------------------------------------------*/
/*                         Compiler Flag                                      */
/*----------------------------------------------------------------------------*/ 

#ifdef _cplusplus
	extern   "C"
    {
#endif
/*----------------------------------------------------------------------------*/
/*                         MACRO DEFINITION                                   */
/*----------------------------------------------------------------------------*/

#define INBOX_INFO 			"D:\\PeekMail\\Inbox\\dir.info"
#define SENT_INFO 			"D:\\PeekMail\\Sent\\dir.info"
#define SAVED_INFO 			"D:\\PeekMail\\Saved\\dir.info"
#define DRAFTS_INFO 		"D:\\PeekMail\\Drafts\\dir.info"
#define TRASH_INFO 			"D:\\PeekMail\\Trash\\dir.info"

#define INBOX_PATH 			"D:\\PeekMail\\Inbox\\"
#define SENT_PATH			"D:\\PeekMail\\Sent\\"
#define SAVED_PATH 			"D:\\PeekMail\\Saved\\"
#define DRAFTS_PATH 		"D:\\PeekMail\\Drafts\\"
#define TRASH_PATH 			"D:\\PeekMail\\Trash\\"

#define MAX_MAIL_ITEM_SIZE 	2048
#define MAX_MAIL_SIZE 		2048
#define MAX_INDEX_LEN 		6

#define READ_STR			"read:"
#define DATE_STR			"date:"
#define TIME_STR			"time:"
#define FROM_STR			"from:"
#define TO_STR				"to:"
#define CC_STR				"cc:"
#define SUBJECT_STR			"subject:"
#define TEXT_STR			"text:"

/*----------------------------------------------------------------------------*/
/*                          TYPE AND STRUCT                                   */
/*----------------------------------------------------------------------------*/

typedef enum
{
	ALL_INFO = 1,			//for viewing mail: filename, read, date_time, from, to, cc, sub, text
	GEN_LIST_INFO,			// for generating mail list: read, from, time, sub
	RE_FWD_INFO,			// for reply/reply all/forward: date_time, from, to, cc, sub, text
	MAIL_INFO_MAX
}PEEKMAIL_MAIL_INFO_TYPE_E;

typedef struct
{
	uint16   		 read_flag;
	uint8		   * file_name;
	MMI_STRING_T   * date;
	MMI_STRING_T   * time;
	MMI_STRING_T   * from;
	MMI_STRING_T   * to;
	MMI_STRING_T   * cc;
	MMI_STRING_T   * subject;
	MMI_STRING_T   * text;
}PEEKMAIL_MAIL_STRUCT;

/*----------------------------------------------------------------------------*/
/*                         Function Declare                                   */
/*----------------------------------------------------------------------------*/
/*****************************************************************************/
//  Description : open hello peek windows
//  Global resource dependence : 
//  Author: xiaoqing.lu
//  Note: 
/*****************************************************************************/

PUBLIC uint16 PeekMail_GetMailNum(char * info_file);



LOCAL uint16 PeekMail_GetMailContent(char * file_name, char **content);


LOCAL uint16 PeekMail_GetMailDetail(char * mail_content, uint16 * content_index, MMI_STRING_T ** detail_item, char end_char);



PUBLIC void PeekMail_GetMailStructure(char * file_name, PEEKMAIL_MAIL_STRUCT *mail_detail, PEEKMAIL_MAIL_INFO_TYPE_E info_type);

LOCAL void DestroyString(MMI_STRING_T **string);

PUBLIC void PeekMail_DestroyMailStruct(PEEKMAIL_MAIL_STRUCT *mail_detail, BOOLEAN flag);

/*----------------------------------------------------------------------------*/
/*                         Compiler Flag                                      */
/*----------------------------------------------------------------------------*/
#ifdef _cplusplus
	}
#endif

#endif




