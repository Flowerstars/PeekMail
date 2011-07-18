
#ifndef PEEKMAIL_MENUTABLE_H
#define PEEKMAIL_MENUTABLE_H

#include "mmi_module.h"
#include "mmicc_handfree.h"


/**---------------------------------------------------------------------------*
 **                         Compiler Flag                                     *
 **---------------------------------------------------------------------------*/
#ifdef __cplusplus
    extern   "C"
    {
#endif

/*-------------------------------------------------------------------------*/
/*                         TYPES/CONSTANTS                                 */
/*-------------------------------------------------------------------------*/

typedef enum
{
    ID_PEEKMAIL_MENU_START = (MMI_MODULE_PEEKMAIL << 16),
		
    ID_PEEKMAIL_OPEN_MESSAGE,
    ID_PEEKMAIL_COMPOSE,
    ID_PEEKMAIL_REPLY,
    ID_PEEKMAIL_REPLY_ALL,
    ID_PEEKMAIL_FORWARD,
    ID_PEEKMAIL_MARK_READ_UNREAD,
    ID_PEEKMAIL_SAVE_MESSAGE,
    ID_PEEKMAIL_DELETE_MESSAGE,
    ID_PEEKMAIL_DELETE_ALL,
    ID_PEEKMAIL_SENT_FOLDER,
    ID_PEEKMAIL_DRAFTS_FOLDER,
    ID_PEEKMAIL_SAVED_FOLDER,
    ID_PEEKMAIL_TRASH_FOLDER,
    ID_PEEKMAIL_SEARCH_THIS_FOLDER,
    ID_PEEKMAIL_CONTACTS,
    ID_PEEKMAIL_PEEKMAIL_MANAGER,
    ID_PEEKMAIL_EXIT,
    
	ID_PEEKMAIL_INBOX_FOLDER,
	ID_PEEKMAIL_MOVE_TO_INBOX_FOLDER,
	
	ID_PEEKMAIL_SEND_MESSAGE,
	ID_PEEKMAIL_SAVE_AS_DRAFT,
	ID_PEEKMAIL_ADD_CC,
	ID_PEEKMAIL_ADD_BCC,

	ID_PEEKMAIL_EMAIL_ACCOUNTS,
	ID_PEEKMAIL_EMAIL_STORAGE,
	ID_PEEKMAIL_ABOUT,
	ID_PEEKMAIL_RESET_PMAIL,

	ID_PEEKMAIL_MANAGER_EDIT_ACCOUNT,
	ID_PEEKMAIL_MANAGER_NEW_ACCOUNT,
	ID_PEEKMAIL_MANAGER_DEL_ACCOUNT,
	ID_PEEKMAIL_MANAGER_SET_AS_PRIMARY,
	ID_PEEKMAIL_MANAGER_DOWNLOAD_CONTACTS,

	ID_PEEKMAIL_CONTACT_NEW,
	ID_PEEKMAIL_CONTACT_DOWNLOAD,
	ID_PEEKMAIL_CONTACT_EDIT_SAVE_DETAILS,
	

	ID_PEEKMAIL_MENU_MAX
}MMIPEEKMAIL_ID_MENU_E;

#define MENU_DEF(_TABLEID, _ITEMPTR, _STYLE, _TITLESTR, _TITLE_ICON, _TITLE_NUMICON, _TITLE_BACKGROUND, \
	_ITEMCOUNT) \
     _TABLEID,

typedef enum
{
	MMIPEEKMAIL_MENU_LABEL_START = (MMI_MODULE_PEEKMAIL << 16),
    #include "PeekMail_menutable.def"
	MMIPEEKMAIL_MENUTABLE_MAX
} MMIPEEKMAIL_MENU_LABEL_E;

#undef MENU_DEF

/*-------------------------------------------------------------------------*/
/*                         FUNCTIONS                                       */
/*-------------------------------------------------------------------------*/

PUBLIC void MMIPEEKMAIL_RegMenuGroup(void);


/*-------------------------------------------------------------------------*/
/*                         VARIABLES                                       */
/*-------------------------------------------------------------------------*/

/**---------------------------------------------------------------------------*
 **                         Compiler Flag                                     *
 **---------------------------------------------------------------------------*/
#ifdef   __cplusplus
    }
#endif
/*-------------------------------------------------------------------------*/

#endif /* PEEKMAIL_MENUTABLE_H */

