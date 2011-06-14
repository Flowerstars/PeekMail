/***************************************************************************
** File Name:      PeekMail_view.h                                             *
** Author:                                                                 *
** Date:           6/13/2011                                               *
** Copyright:      2011 Peek Inc. All Rights Reserved.       *
** Description:    This file is used to describe the data struct of        *
**                      system, application, window and control                 *
****************************************************************************
**                         Important Edit History                          *
** ------------------------------------------------------------------------*
**   DATE           NAME             DESCRIPTION                               *
** 6/13/2011    Liu, Zhengbo               Create                                    *
**																		   *
****************************************************************************/
#ifndef _PEEKMAIL_VIEW_H_
#define _PEEKMAIL_VIEW_H_

/*----------------------------------------------------------------------------*/
/*                          Include Files                                     */
/*----------------------------------------------------------------------------*/ 

#include "stdio.h"
#include "sci_types.h"
#include "mmk_type.h"
#include "guistring.h"
#include "guires.h"
#include "guilcd.h"
#include "guifont.h"
#include "guirichtext.h"
#include "std_header.h"
#include "window_parse.h"
#include "mmidisplay_data.h"
#include "mmi_textfun.h"
#include "PeekMail_text.h"
#include "PeekMail_image.h"
#include "PeekMail_menutable.h"


/*----------------------------------------------------------------------------*/
/*                         Compiler Flag                                      */
/*----------------------------------------------------------------------------*/ 

#ifdef _cplusplus
extern "C"
{
#endif
/*----------------------------------------------------------------------------*/
/*                         MACRO DEFINITION                                   */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/*                          TYPE AND STRUCT                                   */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/*                         Function Declare                                   */
/*----------------------------------------------------------------------------*/
/*****************************************************************************/
//  Description : create PeekMail view window
//  Global resource dependence : 
//  Author: Liu, Zhengbo
//  Note: 
/*****************************************************************************/
PUBLIC void MMI_CreatePeekMailViewWin(void);

/*****************************************************************************/
//  Description : PeekMail view window msg handler
//  Global resource dependence : 
//  Author: Liu, Zhengbo
//  Note: 
/*****************************************************************************/
LOCAL MMI_RESULT_E HandlePeekMailViewWinMsg(
			                                         MMI_WIN_ID_T     	win_id, 
			                                         MMI_MESSAGE_ID_E    msg_id, 
			                                         DPARAM              param
			                                         );

/*----------------------------------------------------------------------------*/
/*                         Compiler Flag                                      */
/*----------------------------------------------------------------------------*/
#ifdef _cplusplus
}
#endif

#endif

