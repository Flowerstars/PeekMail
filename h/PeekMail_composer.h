/***************************************************************************
** File Name:      PeekMail_composer.h                                             *
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
#ifndef _PEEKMAIL_COMPOSER_H_
#define _PEEKMAIL_COMPOSER_H_

/*----------------------------------------------------------------------------*/
/*                          Include Files                                     */
/*----------------------------------------------------------------------------*/ 
#include "mmi_filemgr.h"
#include "os_api.h"

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
#define MAX_LEN_COMPOSER_FROM 		128
#define MAX_LEN_COMPOSER_TO 		128
#define MAX_LEN_COMPOSER_SUBJECT 	128
#define MAX_LEN_COMPOSER_TEXT 		4096


/*----------------------------------------------------------------------------*/
/*                          TYPE AND STRUCT                                   */
/*----------------------------------------------------------------------------*/

typedef enum
{
	NEW = 1,
	REPLY,
	REPLY_ALL,
	FORWARD,
	COMPOSE_TYPE_MAX
}PEEKMAIL_COMPOSER_TYPE_E;


/*----------------------------------------------------------------------------*/
/*                         Function Declare                                   */
/*----------------------------------------------------------------------------*/
/*****************************************************************************/
//  Description : open hello peek windows
//  Global resource dependence : 
//  Author: xiaoqing.lu
//  Note: 
/*****************************************************************************/

LOCAL MMI_RESULT_E HandlePeekMailComposerWinMsg(
                                         MMI_WIN_ID_T     	win_id, 
                                         MMI_MESSAGE_ID_E    msg_id, 
                                         DPARAM              param
                                         );

LOCAL MMI_RESULT_E HandlePeekMailComposerMenuWinMsg(
                                         MMI_WIN_ID_T     	win_id, 
                                         MMI_MESSAGE_ID_E    msg_id, 
                                         DPARAM              param
                                         );




PUBLIC void MMI_CreatePeekMailComposerWin(void);


/*----------------------------------------------------------------------------*/
/*                         Compiler Flag                                      */
/*----------------------------------------------------------------------------*/
#ifdef _cplusplus
	}
#endif

#endif


