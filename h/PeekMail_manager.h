/***************************************************************************
** File Name:      PeekMail_manager.h                                             *
** Author:                                                                 *
** Date:             5/20/2011                                               *
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
#ifndef _PEEKMAIL_MANAGER_H_
#define _PEEKMAIL_MANAGER_H_

/*----------------------------------------------------------------------------*/
/*                          Include Files                                     */
/*----------------------------------------------------------------------------*/ 

#include "sci_types.h"
#include "mmk_type.h"
#include "guistring.h"
#include "guires.h"

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

#define FROM_NAME_STR 		"from name: "
#define EMAIL_ADDRESS_STR 	"address: "
#define M_ACTIVE_STR		"Active"
#define M_PRIMARY_STR		"(Primary)"

#define MAX_LEN_ACCOUNT_EDITOR_NAME 		32
#define MAX_LEN_ACCOUNT_EDITOR_PASSWORD 	32
#define MAX_LEN_ACCOUNT_EDITOR_ADDRESS 		128
#define MAX_LEN_ACCOUNT_EDITOR_SIGNATURE 	256



/*----------------------------------------------------------------------------*/
/*                          TYPE AND STRUCT                                   */
/*----------------------------------------------------------------------------*/

typedef enum
{
	NEW = 1,
	EDIT,
	COMPOSE_TYPE_MAX
}PEEKMAIL_ACCOUNT_EDITOR_TYPE_E;

/*----------------------------------------------------------------------------*/
/*                         Function Declare                                   */
/*----------------------------------------------------------------------------*/
/*****************************************************************************/
//  Description : open hello peek windows
//  Global resource dependence : 
//  Author: xiaoqing.lu
//  Note: 
/*****************************************************************************/




LOCAL MMI_RESULT_E HandlePeekMailManagerWinMsg(
                                         MMI_WIN_ID_T     	win_id, 
                                         MMI_MESSAGE_ID_E    msg_id, 
                                         DPARAM              param
                                         );

LOCAL MMI_RESULT_E HandlePeekMailManagerAccountWinMsg(
											 MMI_WIN_ID_T		win_id, 
											 MMI_MESSAGE_ID_E	 msg_id, 
											 DPARAM 			 param
											 );

LOCAL MMI_RESULT_E HandlePeekMailManagerAccountMenuWinMsg(
                                         MMI_WIN_ID_T     	win_id, 
                                         MMI_MESSAGE_ID_E    msg_id, 
                                         DPARAM              param
                                         );


LOCAL MMI_RESULT_E HandlePeekMailAccountEditorWinMsg(
											 MMI_WIN_ID_T		win_id, 
											 MMI_MESSAGE_ID_E	 msg_id, 
											 DPARAM 			 param
											 );


LOCAL MMI_RESULT_E HandlePeekMailManagerStorageWinMsg(
											 MMI_WIN_ID_T		win_id, 
											 MMI_MESSAGE_ID_E	 msg_id, 
											 DPARAM 			 param
											 );

PUBLIC void AppendAccountListItem(
							  MMI_CTRL_ID_T    ctrl_id,
							  MMI_STRING_T  *  text_account_name,
							  MMI_STRING_T  *  text_first_name,
							  MMI_STRING_T  *  text_last_name,
							  MMI_STRING_T  *  text_address,
							  uint16		   is_active,
							  uint16		   is_primary
							  );
							  

LOCAL void AppendStorageListItem(
							  MMI_CTRL_ID_T    ctrl_id,
							  MMI_TEXT_ID_T    text_storage_type_id
							  );



PUBLIC void MMI_CreatePeekMailManagerWin(void);

PUBLIC void MMI_CreatePeekMailManagerAccountWin(void);

PUBLIC void MMI_CreatePeekMailManagerAccountMenuWin(void);

PUBLIC void MMI_CreatePeekMailManagerAccountEditWin(void);

PUBLIC void MMI_CreatePeekMailManagerAccountNewWin(void);

PUBLIC void MMI_CreatePeekMailManagerStorageWin(void);



/*----------------------------------------------------------------------------*/
/*                         Compiler Flag                                      */
/*----------------------------------------------------------------------------*/
#ifdef _cplusplus
	}
#endif

#endif





