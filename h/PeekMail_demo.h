/***************************************************************************
** File Name:      PeekMail_demo.h                                             *
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
#ifndef _PEEKMAIL_DEMO_H_
#define _PEEKMAIL_DEMO_H_

/*----------------------------------------------------------------------------*/
/*                          Include Files                                     */
/*----------------------------------------------------------------------------*/ 
#include "PeekMail_get_mail_info.h"

#include "mmi_filemgr.h"
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
#define ACCOUNT_INFO 			"D:\\PeekMail\\Accounts\\dir.info"
#define ACCOUNT_PATH 			"D:\\PeekMail\\Accounts\\"
#define CONTACT_INFO 			"D:\\PeekMail\\Contacts\\dir.info"
#define CONTACT_PATH 			"D:\\PeekMail\\Contacts\\"


/*----------------------------------------------------------------------------*/
/*                          TYPE AND STRUCT                                   */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/*                         Function Declare                                   */
/*----------------------------------------------------------------------------*/
PUBLIC void PeekMailDemoGenerate(uint8 *infoPath);

LOCAL void GenerateMails(void);

LOCAL void GenerateAccounts(void);

LOCAL void GenerateContacts(void);


#ifdef _cplusplus
}
#endif

#endif

