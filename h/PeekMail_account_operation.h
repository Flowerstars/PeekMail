/***************************************************************************
** File Name:      PeekMail_account_operation.h                                             *
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
#ifndef _PEEKMAIL_ACCOUNT_OPERATION_H_
#define _PEEKMAIL_ACCOUNT_OPERATION_H_

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

#define ACCOUNT_INFO 			"D:\\PeekMail\\Accounts\\dir.info"

#define ACCOUNT_PATH 			"D:\\PeekMail\\Accounts\\"

#define MAX_ACCOUNT_ITEM_SIZE 	2048
#define MAX_MAIL_SIZE 		2048
#define MAX_INDEX_LEN 		6

#define ACTIVE_STR			"active:"
#define PRIMARY_STR			"primary:"
#define ACCOUNT_NAME_STR	"account_name:"
#define FIRST_NAME_STR		"first_name:"
#define LAST_NAME_STR		"last_name:"
#define PSW_STR				"password:"
#define ADDRESS_STR			"address:"
#define SIGNATURE_STR		"signature:"



/*----------------------------------------------------------------------------*/
/*                          TYPE AND STRUCT                                   */
/*----------------------------------------------------------------------------*/

typedef enum
{
	ALL_INFO = 1,			//for viewing mail: filename, read, date_time, from, to, cc, sub, text
	//GEN_LIST_INFO,			// for generating mail list: read, from, time, sub
	//RE_FWD_INFO,			// for reply/reply all/forward: date_time, from, to, cc, sub, text
	//MAIL_INFO_MAX
}PEEKMAIL_ACCOUNT_INFO_TYPE_E;

typedef struct
{
	uint16   		 active_flag;
	uint16   		 primary_flag;
	uint8		   * file_name;
	MMI_STRING_T   * account_name;
	MMI_STRING_T   * first_name;
	MMI_STRING_T   * last_name;
	MMI_STRING_T   * password;
	MMI_STRING_T   * address;
	MMI_STRING_T   * signature;
}PEEKMAIL_ACCOUNT_STRUCT;

/*----------------------------------------------------------------------------*/
/*                         Function Declare                                   */
/*----------------------------------------------------------------------------*/
/*****************************************************************************/
//  Description : open hello peek windows
//  Global resource dependence : 
//  Author: xiaoqing.lu
//  Note: 
/*****************************************************************************/

PUBLIC uint16 PeekMail_GetAccountNum(char * info_file);



LOCAL uint16 PeekMail_GetAccountContent(char * file_name, char ** content);


LOCAL uint16 PeekMail_GetAccountDetail(char * mail_content, uint16 * content_index, MMI_STRING_T ** detail_item, char end_char);



PUBLIC void PeekMail_GetAccountStructure(char * file_name, PEEKMAIL_ACCOUNT_STRUCT *account_detail, PEEKMAIL_ACCOUNT_INFO_TYPE_E info_type);

LOCAL void DestroyString(MMI_STRING_T **string);

PUBLIC void PeekMail_DestroyAccountStruct(PEEKMAIL_ACCOUNT_STRUCT *account_detail, BOOLEAN flag);

/*----------------------------------------------------------------------------*/
/*                         Compiler Flag                                      */
/*----------------------------------------------------------------------------*/
#ifdef _cplusplus
	}
#endif

#endif





