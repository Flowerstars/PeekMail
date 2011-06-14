/*****************************************************************************
** File Name:      HelloPeek_mmi_image.h                                            *
** Author:         Song,Han                                                          *
** Date:           05/22/2011                                                   *
** Copyright:      2011 Peek Inc. All Rights Reserved.        *
** Description:    This file is used to describe call log                    *
******************************************************************************
**                         Important Edit History                            *
** --------------------------------------------------------------------------*
** 05/22/2011 Create                                *
******************************************************************************/


#ifndef PEEKMAIL_MMI_IMAGE_H_
#define PEEKMAIL_MMI_IMAGE_H_

#include "sci_types.h"
#include "mmi_imagefun.h"
#include "mmi_module.h"

#ifdef __cplusplus
extern   "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
// Image Resource ID
///////////////////////////////////////////////////////////////////////////////

#define MACRO_MDU_TYPE  MACRO_MDU_IMAGE
#include "macro_mdu_def.h"

typedef enum PEEKMAIL_MMI_IMAGE_ID_E
{
	PEEKMAIL_IMAGE_NULL = ( MMI_MODULE_PEEKMAIL << 16 ) | MMI_SYS_RES_FLAG,
	#include "PeekMail_mdu_def.h"
	PEEKMAIL_IMAGE_MAX_ID
} PEEKMAIL_MMI_IMAGE_ID_E;

#undef MACRO_MDU_TYPE

#ifdef __cplusplus
}
#endif

#endif //PEEKMAIL_MMI_IMAGE_H_

