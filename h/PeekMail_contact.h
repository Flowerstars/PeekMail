/***************************************************************************
** File Name:      PeekMail_contact.h                                             *
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
#ifndef _PEEKMAIL_CONTACT_H_
#define _PEEKMAIL_CONTACT_H_

/*----------------------------------------------------------------------------*/
/*                          Include Files                                     */
/*----------------------------------------------------------------------------*/ 

#include "sci_types.h"
#include "mmk_type.h"
#include "guistring.h"
#include "guires.h"
#include "os_api.h"

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
#define MAX_LEN_CONTACT_EDITOR_NAME 128
#define MAX_LEN_CONTACT_EDITOR_PHONE 32
#define MAX_LEN_CONTACT_EDITOR_EMAIL_ADDRESS 128


/*----------------------------------------------------------------------------*/
/*                          TYPE AND STRUCT                                   */
/*----------------------------------------------------------------------------*/

typedef enum
{
	NEW = 1,
	EDIT,
	COMPOSE_TYPE_MAX
}PEEKMAIL_CONTACT_EDITOR_TYPE_E;


/*----------------------------------------------------------------------------*/
/*                         Function Declare                                   */
/*----------------------------------------------------------------------------*/
/*****************************************************************************/
//  Description : open hello peek windows
//  Global resource dependence : 
//  Author: xiaoqing.lu
//  Note: 
/*****************************************************************************/

PUBLIC void AppendContactListItem(
							  MMI_CTRL_ID_T    ctrl_id,
							  MMI_STRING_T *   text_name,
							  MMI_STRING_T *   text_phone,
							  MMI_STRING_T *   text_mail
							  );


LOCAL MMI_RESULT_E HandlePeekMailContactWinMsg(
                                         MMI_WIN_ID_T     	win_id, 
                                         MMI_MESSAGE_ID_E    msg_id, 
                                         DPARAM              param
                                         );

LOCAL MMI_RESULT_E HandlePeekMailContactMenuWinMsg(
                                         MMI_WIN_ID_T     	win_id, 
                                         MMI_MESSAGE_ID_E    msg_id, 
                                         DPARAM              param
                                         );


LOCAL MMI_RESULT_E HandlePeekMailContactEditorWinMsg(
											 MMI_WIN_ID_T		win_id, 
											 MMI_MESSAGE_ID_E	 msg_id, 
											 DPARAM 			 param
											 );

LOCAL MMI_RESULT_E HandlePeekMailContactEditMenuWinMsg(
											 MMI_WIN_ID_T		win_id, 
											 MMI_MESSAGE_ID_E	 msg_id, 
											 DPARAM 			 param
											 );


PUBLIC void MMI_CreatePeekContactWin(void);

PUBLIC void MMI_CreatePeekContactMenuWin(void);

PUBLIC void MMI_CreatePeekMailContactEditWin(void);

PUBLIC void MMI_CreatePeekMailContactNewWin(void);

PUBLIC void MMI_CreatePeekMailContactEditMenuWin(void);

/*----------------------------------------------------------------------------*/
/*                         Compiler Flag                                      */
/*----------------------------------------------------------------------------*/
#ifdef _cplusplus
	}
#endif

#endif


