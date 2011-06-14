/***************************************************************************
** File Name:      PeekMail_main.h                                             *
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
#ifndef _PEEKMAIL_MAIN_H_
#define _PEEKMAIL_MAIN_H_

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


/*----------------------------------------------------------------------------*/
/*                          TYPE AND STRUCT                                   */
/*----------------------------------------------------------------------------*/
typedef struct
{
	uint16   		 read_flag;
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

LOCAL void AppendMailListItem(
							  MMI_CTRL_ID_T    ctrl_id,
							  MMI_IMAGE_ID_T   image_id,
							  MMI_TEXT_ID_T    text_from_id,
							  MMI_TEXT_ID_T    text_time_id,
							  MMI_TEXT_ID_T    text_subject_id
							  //MMI_TEXT_ID_T    left_softkey_id,
							 // MMI_TEXT_ID_T    middle_softkey_id,
							  //MMI_TEXT_ID_T    right_softkey_id
							  );


LOCAL MMI_RESULT_E HandlePeekMailInboxWinMsg(
                                         MMI_WIN_ID_T     	win_id, 
                                         MMI_MESSAGE_ID_E    msg_id, 
                                         DPARAM              param
                                         );

LOCAL MMI_RESULT_E HandlePeekMailInboxMenuWinMsg(
                                         MMI_WIN_ID_T     	win_id, 
                                         MMI_MESSAGE_ID_E    msg_id, 
                                         DPARAM              param
                                         );




PUBLIC void MMI_CreatePeekMailWin(void);


/*----------------------------------------------------------------------------*/
/*                         Compiler Flag                                      */
/*----------------------------------------------------------------------------*/
#ifdef _cplusplus
	}
#endif

#endif
