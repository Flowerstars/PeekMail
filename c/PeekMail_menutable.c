#define MENUTABLE_C

#ifdef WIN32
#include "std_header.h"
#endif
#include "window_parse.h"
//#include "sci_types.h"
#include "mmi_module.h"
#include "guimenu.h"

#include "mmi_menutable.h"
#include "mmi_text.h"

#include "mmi_id.h"
#include "mmi_common.h"

#include "PeekMail_menutable.h"
#include "PeekMail_text.h"
#include "PeekMail_image.h"



#define TIP_NULL 0

//Inbox left softkey menu table
const GUIMENU_ITEM_T menu_Peek_Mail_Inbox_table[] =
{
    {ID_PEEKMAIL_OPEN_MESSAGE,		TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_OPEN_MESSAGE_ITEM,		0,0,0,0},
    {ID_PEEKMAIL_COMPOSE,			TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_COMPOSE_ITEM,			0,0,0,0},
    {ID_PEEKMAIL_REPLY,				TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_REPLY_ITEM,				0,0,0,0},
	{ID_PEEKMAIL_REPLY_ALL,			TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_REPLY_ALL_ITEM,			0,0,0,0},
	{ID_PEEKMAIL_FORWARD,			TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_FORWARD_ITEM,			0,0,0,0},
	{ID_PEEKMAIL_MARK_READ_UNREAD,	TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_MARK_READ_UNREAD_ITEM,  0,0,0,0},
	{ID_PEEKMAIL_SAVE_MESSAGE, 		TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_SAVE_MESSAGE_ITEM,		0,0,0,0},
	{ID_PEEKMAIL_DELETE_MESSAGE,	TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_DELETE_MESSAGE_ITEM,	0,0,0,0},
	{ID_PEEKMAIL_DELETE_ALL,		TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_DELETE_ALL_ITEM,		0,0,0,0},
	{ID_PEEKMAIL_SENT_FOLDER,		TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_SENT_FOLDER_ITEM,		0,0,0,0},
	{ID_PEEKMAIL_DRAFTS_FOLDER,		TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_DRAFTS_FOLDER_ITEM,		0,0,0,0},
	{ID_PEEKMAIL_SAVED_FOLDER,		TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_SAVED_FOLDER_ITEM,		0,0,0,0},
	{ID_PEEKMAIL_TRASH_FOLDER,		TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_TRASH_FOLDER_ITEM,		0,0,0,0},	
	{ID_PEEKMAIL_SEARCH_THIS_FOLDER,TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_SEARCH_THIS_FOLDER_ITEM,0,0,0,0},
	{ID_PEEKMAIL_CONTACTS,			TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_CONTACTS_ITEM,			0,0,0,0},
	{ID_PEEKMAIL_PEEKMAIL_MANAGER,	TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_PEEK_MAIL_MANAGER_ITEM, 0,0,0,0},
	{ID_PEEKMAIL_EXIT,				TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_EXIT_ITEM,				0,0,0,0},
};


//Sent left softkey menu table
const GUIMENU_ITEM_T menu_Peek_Mail_Sent_table[] =
{
    {ID_PEEKMAIL_OPEN_MESSAGE,		TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_OPEN_MESSAGE_ITEM,		0,0,0,0},
    {ID_PEEKMAIL_COMPOSE,			TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_COMPOSE_ITEM,			0,0,0,0},
    {ID_PEEKMAIL_REPLY,				TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_REPLY_ITEM,				0,0,0,0},
	{ID_PEEKMAIL_REPLY_ALL,			TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_REPLY_ALL_ITEM,			0,0,0,0},
	{ID_PEEKMAIL_FORWARD,			TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_FORWARD_ITEM,			0,0,0,0},
	{ID_PEEKMAIL_MARK_READ_UNREAD,	TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_MARK_READ_UNREAD_ITEM,  0,0,0,0},
	{ID_PEEKMAIL_SAVE_MESSAGE, 		TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_SAVE_MESSAGE_ITEM,		0,0,0,0},
	{ID_PEEKMAIL_DELETE_MESSAGE,	TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_DELETE_MESSAGE_ITEM,	0,0,0,0},
	{ID_PEEKMAIL_DELETE_ALL,		TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_DELETE_ALL_ITEM,		0,0,0,0},
	{ID_PEEKMAIL_INBOX_FOLDER,		TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_SENT_MENU_INBOX_FOLDER_ITEM,		0,0,0,0},
	{ID_PEEKMAIL_MOVE_TO_INBOX_FOLDER, TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_SENT_MENU_MOVE_TO_INBOX_FOLDER_ITEM,		0,0,0,0},
	{ID_PEEKMAIL_DRAFTS_FOLDER,		TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_DRAFTS_FOLDER_ITEM,		0,0,0,0},
	{ID_PEEKMAIL_SAVED_FOLDER,		TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_SAVED_FOLDER_ITEM,		0,0,0,0},
	{ID_PEEKMAIL_TRASH_FOLDER,		TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_TRASH_FOLDER_ITEM,		0,0,0,0},	
	{ID_PEEKMAIL_SEARCH_THIS_FOLDER,TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_SEARCH_THIS_FOLDER_ITEM,0,0,0,0},
	{ID_PEEKMAIL_CONTACTS,			TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_CONTACTS_ITEM,			0,0,0,0},
	{ID_PEEKMAIL_PEEKMAIL_MANAGER,	TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_PEEK_MAIL_MANAGER_ITEM, 0,0,0,0},
	{ID_PEEKMAIL_EXIT,				TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_EXIT_ITEM,				0,0,0,0},
};


//Saved left softkey menu table
const GUIMENU_ITEM_T menu_Peek_Mail_Saved_table[] =
{
    {ID_PEEKMAIL_OPEN_MESSAGE,		TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_OPEN_MESSAGE_ITEM,		0,0,0,0},
    {ID_PEEKMAIL_COMPOSE,			TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_COMPOSE_ITEM,			0,0,0,0},
    {ID_PEEKMAIL_REPLY,				TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_REPLY_ITEM,				0,0,0,0},
	{ID_PEEKMAIL_REPLY_ALL,			TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_REPLY_ALL_ITEM,			0,0,0,0},
	{ID_PEEKMAIL_FORWARD,			TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_FORWARD_ITEM,			0,0,0,0},
	{ID_PEEKMAIL_MARK_READ_UNREAD,	TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_MARK_READ_UNREAD_ITEM,  0,0,0,0},
	{ID_PEEKMAIL_DELETE_MESSAGE,	TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_DELETE_MESSAGE_ITEM,	0,0,0,0},
	{ID_PEEKMAIL_DELETE_ALL,		TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_DELETE_ALL_ITEM,		0,0,0,0},
	{ID_PEEKMAIL_INBOX_FOLDER,		TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_SENT_MENU_INBOX_FOLDER_ITEM,		0,0,0,0},
	{ID_PEEKMAIL_MOVE_TO_INBOX_FOLDER, TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_SENT_MENU_MOVE_TO_INBOX_FOLDER_ITEM,		0,0,0,0},
	{ID_PEEKMAIL_DRAFTS_FOLDER,		TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_DRAFTS_FOLDER_ITEM,		0,0,0,0},
	{ID_PEEKMAIL_SENT_FOLDER,		TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_SENT_FOLDER_ITEM,		0,0,0,0},
	{ID_PEEKMAIL_TRASH_FOLDER,		TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_TRASH_FOLDER_ITEM,		0,0,0,0},	
	{ID_PEEKMAIL_SEARCH_THIS_FOLDER,TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_SEARCH_THIS_FOLDER_ITEM,0,0,0,0},
	{ID_PEEKMAIL_CONTACTS,			TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_CONTACTS_ITEM,			0,0,0,0},
	{ID_PEEKMAIL_PEEKMAIL_MANAGER,	TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_PEEK_MAIL_MANAGER_ITEM, 0,0,0,0},
	{ID_PEEKMAIL_EXIT,				TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_EXIT_ITEM,				0,0,0,0},
};


//Composer left softkey menu table
const GUIMENU_ITEM_T menu_Peek_Mail_Composer_table[] =
{
    {ID_PEEKMAIL_SEND_MESSAGE,			TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_COMPOSER_MENU_SEND_MESSAGE_ITEM,	0,0,0,0},
    {ID_PEEKMAIL_SAVE_AS_DRAFT,			TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_COMPOSER_MENU_SAVE_AS_DRAFT_ITEM,	0,0,0,0},
    {ID_PEEKMAIL_ADD_CC,				TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_COMPOSER_MENU_ADD_CC_ITEM,			0,0,0,0},
	{ID_PEEKMAIL_ADD_BCC,				TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_COMPOSER_MENU_ADD_BCC_ITEM,		0,0,0,0},
	{ID_PEEKMAIL_INBOX_FOLDER,			TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_SENT_MENU_INBOX_FOLDER_ITEM,		0,0,0,0},
	{ID_PEEKMAIL_CONTACTS,				TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_CONTACTS_ITEM,  		0,0,0,0},
	{ID_PEEKMAIL_PEEKMAIL_MANAGER,		TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_PEEK_MAIL_MANAGER_ITEM,	0,0,0,0},
	{ID_PEEKMAIL_EXIT,					TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_EXIT_ITEM,				0,0,0,0},
};


//Draft left softkey menu table
const GUIMENU_ITEM_T menu_Peek_Mail_Draft_table[] =
{
	{ID_PEEKMAIL_OPEN_MESSAGE,		TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_OPEN_MESSAGE_ITEM,		0,0,0,0},
	{ID_PEEKMAIL_COMPOSE,			TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_COMPOSE_ITEM,			0,0,0,0},
	{ID_PEEKMAIL_REPLY, 			TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_REPLY_ITEM, 			0,0,0,0},
	{ID_PEEKMAIL_REPLY_ALL, 		TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_REPLY_ALL_ITEM, 		0,0,0,0},
	{ID_PEEKMAIL_FORWARD,			TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_FORWARD_ITEM,			0,0,0,0},
	{ID_PEEKMAIL_MARK_READ_UNREAD,	TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_MARK_READ_UNREAD_ITEM,	0,0,0,0},
	{ID_PEEKMAIL_DELETE_MESSAGE,	TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_DELETE_MESSAGE_ITEM,	0,0,0,0},
	{ID_PEEKMAIL_DELETE_ALL,		TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_DELETE_ALL_ITEM,		0,0,0,0},
	{ID_PEEKMAIL_INBOX_FOLDER,		TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_SENT_MENU_INBOX_FOLDER_ITEM,		0,0,0,0},
	{ID_PEEKMAIL_MOVE_TO_INBOX_FOLDER, TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_SENT_MENU_MOVE_TO_INBOX_FOLDER_ITEM,		0,0,0,0},
	{ID_PEEKMAIL_SAVED_FOLDER, 	TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_SAVED_FOLDER_ITEM, 	0,0,0,0},
	{ID_PEEKMAIL_SENT_FOLDER,		TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_SENT_FOLDER_ITEM,		0,0,0,0},
	{ID_PEEKMAIL_TRASH_FOLDER,		TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_TRASH_FOLDER_ITEM,		0,0,0,0},	
	{ID_PEEKMAIL_SEARCH_THIS_FOLDER,TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_SEARCH_THIS_FOLDER_ITEM,0,0,0,0},
	{ID_PEEKMAIL_CONTACTS,			TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_CONTACTS_ITEM,			0,0,0,0},
	{ID_PEEKMAIL_PEEKMAIL_MANAGER,	TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_PEEK_MAIL_MANAGER_ITEM, 0,0,0,0},
	{ID_PEEKMAIL_EXIT,				TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_EXIT_ITEM,				0,0,0,0},
};

//Trash left softkey menu table
const GUIMENU_ITEM_T menu_Peek_Mail_Trash_table[] =
{
	{ID_PEEKMAIL_OPEN_MESSAGE,		TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_OPEN_MESSAGE_ITEM,		0,0,0,0},
	{ID_PEEKMAIL_COMPOSE,			TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_COMPOSE_ITEM,			0,0,0,0},
	{ID_PEEKMAIL_REPLY, 			TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_REPLY_ITEM, 			0,0,0,0},
	{ID_PEEKMAIL_REPLY_ALL, 		TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_REPLY_ALL_ITEM, 		0,0,0,0},
	{ID_PEEKMAIL_FORWARD,			TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_FORWARD_ITEM,			0,0,0,0},
	{ID_PEEKMAIL_MARK_READ_UNREAD,	TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_MARK_READ_UNREAD_ITEM,	0,0,0,0},
	{ID_PEEKMAIL_DELETE_MESSAGE,	TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_DELETE_MESSAGE_ITEM,	0,0,0,0},
	{ID_PEEKMAIL_DELETE_ALL,		TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_DELETE_ALL_ITEM,		0,0,0,0},
	{ID_PEEKMAIL_INBOX_FOLDER,		TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_SENT_MENU_INBOX_FOLDER_ITEM,		0,0,0,0},
	{ID_PEEKMAIL_MOVE_TO_INBOX_FOLDER, TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_SENT_MENU_MOVE_TO_INBOX_FOLDER_ITEM,		0,0,0,0},
	{ID_PEEKMAIL_SAVED_FOLDER, 	TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_SAVED_FOLDER_ITEM, 	0,0,0,0},
	{ID_PEEKMAIL_SENT_FOLDER,		TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_SENT_FOLDER_ITEM,		0,0,0,0},
	{ID_PEEKMAIL_DRAFTS_FOLDER,		TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_DRAFTS_FOLDER_ITEM,		0,0,0,0},	
	{ID_PEEKMAIL_SEARCH_THIS_FOLDER,TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_SEARCH_THIS_FOLDER_ITEM,0,0,0,0},
	{ID_PEEKMAIL_CONTACTS,			TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_CONTACTS_ITEM,			0,0,0,0},
	{ID_PEEKMAIL_PEEKMAIL_MANAGER,	TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_PEEK_MAIL_MANAGER_ITEM, 0,0,0,0},
	{ID_PEEKMAIL_EXIT,				TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_INBOX_MENU_EXIT_ITEM,				0,0,0,0},
};


//PMail Manager main menu table
const GUIMENU_ITEM_T menu_Peek_Mail_Manager_table[] =
{
	{ID_PEEKMAIL_EMAIL_ACCOUNTS,	TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_MANAGER_MAIN_MENU_EMAIL_ACCOUNTS,	0,0,0,0},
	{ID_PEEKMAIL_EMAIL_STORAGE,		TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_MANAGER_MAIN_MENU_EMAIL_STORAGE,	0,0,0,0},
	{ID_PEEKMAIL_ABOUT, 			TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_MANAGER_MAIN_MENU_ABOUT, 			0,0,0,0},
	{ID_PEEKMAIL_RESET_PMAIL, 		TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_MANAGER_MAIN_MENU_RESET_PMAIL, 	0,0,0,0},
};

//PMail Manager menu table
const GUIMENU_ITEM_T menu_Peek_Mail_Manager_Account_table[] =
{
	{ID_PEEKMAIL_MANAGER_EDIT_ACCOUNT,		TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_MANAGER_ACCOUNT_MENU_EDIT_ACCOUNTS,	0,0,0,0},
	{ID_PEEKMAIL_MANAGER_NEW_ACCOUNT,		TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_MANAGER_ACCOUNT_MENU_NEW_ACCOUNTS,		0,0,0,0},
	{ID_PEEKMAIL_MANAGER_DEL_ACCOUNT, 		TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_MANAGER_ACCOUNT_MENU_DEL_ACCOUNTS, 	0,0,0,0},
	{ID_PEEKMAIL_MANAGER_SET_AS_PRIMARY, 	TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_MANAGER_ACCOUNT_MENU_SET_AS_PRIMARY, 	0,0,0,0},
	{ID_PEEKMAIL_MANAGER_DOWNLOAD_CONTACTS, TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_MANAGER_ACCOUNT_MENU_DOWNLOAD_CONTACTS,0,0,0,0},
	{ID_PEEKMAIL_INBOX_FOLDER,				TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_SENT_MENU_INBOX_FOLDER_ITEM, 			0,0,0,0},
};

//Contact menu table
const GUIMENU_ITEM_T menu_Peek_Mail_Contact_table[] =
{
	{ID_PEEKMAIL_CONTACT_NEW,		TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_CONTACT_NEW_CONTACT,			0,0,0,0},
	{ID_PEEKMAIL_CONTACT_DOWNLOAD,	TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_CONTACT_DOWNLOAD_CONTACTS,		0,0,0,0},
	{ID_PEEKMAIL_INBOX_FOLDER, 		TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_SENT_MENU_INBOX_FOLDER_ITEM, 	0,0,0,0},
};

//Contact Edit menu table
const GUIMENU_ITEM_T menu_Peek_Mail_Contact_Edit_table[] =
{
	{ID_PEEKMAIL_CONTACT_EDIT_SAVE_DETAILS,	TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_CONTACT_EDIT_SAVE_DETAILS,		0,0,0,0},
	{ID_PEEKMAIL_INBOX_FOLDER, 				TIP_NULL,{STXT_OK,TXT_NULL,STXT_RETURN},TXT_PEEKMAIL_SENT_MENU_INBOX_FOLDER_ITEM, 	0,0,0,0},
};







#define MENU_DEF(_TABLEID, _ITEMPTR, _STYLE, _TITLESTR, _TITLE_ICON, _TITLE_NUMICON, _TITLE_BACKGROUND, \
    _ITEMCOUNT) \
     _ITEMPTR, _STYLE, _TITLESTR, _TITLE_ICON, _TITLE_NUMICON, _TITLE_BACKGROUND, _ITEMCOUNT, 

const GUIMENU_GROUP_T mmipeekmail_menu_table[] = 
{
    {NULL},
    #include "PeekMail_menutable.def"
};

#undef MENU_DEF

/*****************************************************************************/
// 	Description : Register hello menu group
//	Global resource dependence : none
//  Author: xiaoqing.lu
//	Note:
/*****************************************************************************/
PUBLIC void MMIPEEKMAIL_RegMenuGroup(void)
{
    MMI_RegMenuGroup(MMI_MODULE_PEEKMAIL, mmipeekmail_menu_table);
}


