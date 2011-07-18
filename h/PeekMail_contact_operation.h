/***************************************************************************
** File Name:      PeekMail_contact_operation.h                                             *
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
#ifndef _PEEKMAIL_CONTACT_OPERATION_H_
#define _PEEKMAIL_CONTACT_OPERATION_H_

/*----------------------------------------------------------------------------*/
/*                          Include Files                                     */
/*----------------------------------------------------------------------------*/ 

#include "os_api.h"
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

#define CONTACT_INFO 			"D:\\PeekMail\\Contacts\\dir.info"
#define CONTACT_PATH 			"D:\\PeekMail\\Contacts\\"

#define MAX_CONTACT_ITEM_SIZE 	256
#define MAX_INDEX_LEN 			8

#define NAME_STR			"name:"
#define PHONE_STR			"phone:"
#define MAIL_STR			"mail:"




/*----------------------------------------------------------------------------*/
/*                          TYPE AND STRUCT                                   */
/*----------------------------------------------------------------------------*/

typedef enum
{
	ALL_INFO = 1,			//for viewing mail: filename, read, date_time, from, to, cc, sub, text
	//GEN_LIST_INFO,			// for generating mail list: read, from, time, sub
	//RE_FWD_INFO,			// for reply/reply all/forward: date_time, from, to, cc, sub, text
	//MAIL_INFO_MAX
}PEEKMAIL_CONTACT_INFO_TYPE_E;

typedef struct
{
	uint8		   * file_name;
	MMI_STRING_T   * name;
	MMI_STRING_T   * phone;
	MMI_STRING_T   * mail;
}PEEKMAIL_CONTACT_STRUCT;


/*----------------------------------------------------------------------------*/
/*                         Function Declare                                   */
/*----------------------------------------------------------------------------*/
/*****************************************************************************/
//  Description : open hello peek windows
//  Global resource dependence : 
//  Author: xiaoqing.lu
//  Note: 
/*****************************************************************************/

PUBLIC uint16 PeekMail_GetContactNum(char * info_file);



LOCAL uint16 PeekMail_GetContactContent(char * file_name, char ** content);


LOCAL uint16 PeekMail_GetContactDetail(char * contact_content, uint16 * content_index, MMI_STRING_T ** detail_item, char end_char);



PUBLIC void PeekMail_GetContactStructure(char * file_name, PEEKMAIL_CONTACT_STRUCT *contact_detail, PEEKMAIL_CONTACT_INFO_TYPE_E info_type);

LOCAL void DestroyString(MMI_STRING_T **string);

PUBLIC void PeekMail_DestroyContactStruct(PEEKMAIL_CONTACT_STRUCT *contact_detail, BOOLEAN flag);

/*----------------------------------------------------------------------------*/
/*                         Compiler Flag                                      */
/*----------------------------------------------------------------------------*/
#ifdef _cplusplus
	}
#endif

#endif






