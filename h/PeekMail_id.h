
// Window ID
typedef enum
{
	MMIPEEKMAIL_WIN_ID_START = (MMI_MODULE_PEEKMAIL << 16),
		
	MMI_PEEK_MAIL_WIN_ID,
	MMI_PEEK_MAIL_INBOX_WIN_ID,
	MMI_PEEK_MAIL_INBOX_MENU_WIN_ID,
	MMI_PEEK_MAIL_SENT_WIN_ID,
	MMI_PEEK_MAIL_SENT_MENU_WIN_ID,
	MMI_PEEK_MAIL_SAVED_WIN_ID,
	MMI_PEEK_MAIL_SAVED_MENU_WIN_ID,
	MMI_PEEK_MAIL_COMPOSER_WIN_ID,
	MMI_PEEK_MAIL_COMPOSER_MENU_WIN_ID,
	MMI_PEEK_MAIL_DRAFT_WIN_ID,
	MMI_PEEK_MAIL_DRAFT_MENU_WIN_ID,
	MMI_PEEK_MAIL_TRASH_WIN_ID,
	MMI_PEEK_MAIL_TRASH_MENU_WIN_ID,
	MMI_PEEK_MAIL_VIEW_WIN_ID,
	MMI_PEEK_MAIL_VIEW_PARSE_WIN_ID,
	MMI_PEEK_MAIL_MANAGER_WIN_ID,
	MMI_PEEK_MAIL_MANAGER_ACCOUNT_MENU_WIN_ID,
	MMI_PEEK_MAIL_MANAGER_ACCOUNT_WIN_ID,
	MMI_PEEK_MAIL_ACCOUNT_EDITOR_WIN_ID,
	MMI_PEEK_MAIL_MANAGER_STORAGE_WIN_ID,
	MMI_PEEK_MAIL_CONTACT_WIN_ID,
	MMI_PEEK_MAIL_CONTACT_MENU_WIN_ID,
	MMI_PEEK_MAIL_CONTACT_EDITOR_WIN_ID,
	MMI_PEEK_MAIL_CONTACT_EDIT_MENU_WIN_ID,


	MMIPEEKMAIL_MAX_WIN_ID
}MMIPEEKMAIL_WINDOW_ID_E;


// Control ID
typedef enum
{
	MMIPEEKMAIL_CTRL_ID_ID_START = MMIPEEKMAIL_MAX_WIN_ID,
		
	MMI_PEEK_MAIL_INBOX_CTRL_ID,
	MMI_PEEK_MAIL_INBOX_MENU_CTRL_ID,
	MMI_PEEK_MAIL_SENT_CTRL_ID,
	MMI_PEEK_MAIL_SENT_MENU_CTRL_ID,
	MMI_PEEK_MAIL_SAVED_CTRL_ID,
	MMI_PEEK_MAIL_SAVED_MENU_CTRL_ID,
	MMI_PEEK_MAIL_DRAFT_CTRL_ID,
	MMI_PEEK_MAIL_DRAFT_MENU_CTRL_ID,
	MMI_PEEK_MAIL_TRASH_CTRL_ID,
	MMI_PEEK_MAIL_TRASH_MENU_CTRL_ID,
	MMI_PEEK_MAIL_VIEW_RICHTEXT_CTRL_ID,

	MMI_PEEK_MAIL_COMPOSER_MENU_CTRL_ID,
	
	MMI_PEEK_MAIL_COMPOSER_FORM_CTRL_ID,
		MMI_PEEK_MAIL_COMPOSER_FROM_FORM_CTRL_ID,
			MMI_PEEK_MAIL_COMPOSER_LABEL_FROM_CTRL_ID,
			MMI_PEEK_MAIL_COMPOSER_EDITBOX_FROM_CTRL_ID,
		MMI_PEEK_MAIL_COMPOSER_TO_FORM_CTRL_ID,
			MMI_PEEK_MAIL_COMPOSER_LABEL_TO_CTRL_ID,
			MMI_PEEK_MAIL_COMPOSER_EDITBOX_TO_CTRL_ID,
		MMI_PEEK_MAIL_COMPOSER_CC_FORM_CTRL_ID,
			MMI_PEEK_MAIL_COMPOSER_LABEL_CC_CTRL_ID,
			MMI_PEEK_MAIL_COMPOSER_EDITBOX_CC_CTRL_ID,
		MMI_PEEK_MAIL_COMPOSER_BCC_FORM_CTRL_ID,
			MMI_PEEK_MAIL_COMPOSER_LABEL_BCC_CTRL_ID,
			MMI_PEEK_MAIL_COMPOSER_EDITBOX_BCC_CTRL_ID,
		MMI_PEEK_MAIL_COMPOSER_SUBJECT_FORM_CTRL_ID,
			MMI_PEEK_MAIL_COMPOSER_LABEL_SUBJECT_CTRL_ID,
			MMI_PEEK_MAIL_COMPOSER_EDITBOX_SUBJECT_CTRL_ID,
		MMI_PEEK_MAIL_COMPOSER_TEXT_FORM_CTRL_ID,
			MMI_PEEK_MAIL_COMPOSER_EDITBOX_TEXT_CTRL_ID,

	MMI_PEEK_MAIL_MANAGER_MENU_CTRL_ID,
	MMI_PEEK_MAIL_MANAGER_ACCOUNT_CTRL_ID,
	MMI_PEEK_MAIL_MANAGER_ACCOUNT_MENU_CTRL_ID,

	MMI_PEEK_MAIL_ACCOUNT_EDITOR_FORM_CTRL_ID,
		MMI_PEEK_MAIL_ACCOUNT_EDITOR_FIRST_NAME_FORM_CTRL_ID,
			MMI_PEEK_MAIL_ACCOUNT_EDITOR_LABEL_FIRST_NAME_CTRL_ID,
			MMI_PEEK_MAIL_ACCOUNT_EDITOR_EDITBOX_FIRST_NAME_CTRL_ID,
		MMI_PEEK_MAIL_ACCOUNT_EDITOR_LAST_NAME_FORM_CTRL_ID,
			MMI_PEEK_MAIL_ACCOUNT_EDITOR_LABEL_LAST_NAME_CTRL_ID,
			MMI_PEEK_MAIL_ACCOUNT_EDITOR_EDITBOX_LAST_NAME_CTRL_ID,
		MMI_PEEK_MAIL_ACCOUNT_EDITOR_PASSWORD_FORM_CTRL_ID,
			MMI_PEEK_MAIL_ACCOUNT_EDITOR_LABEL_PASSWORD_CTRL_ID,
			MMI_PEEK_MAIL_ACCOUNT_EDITOR_EDITBOX_PASSWORD_CTRL_ID,
		MMI_PEEK_MAIL_ACCOUNT_EDITOR_ADDRESS_FORM_CTRL_ID,
			MMI_PEEK_MAIL_ACCOUNT_EDITOR_LABEL_ADDRESS_CTRL_ID,
			MMI_PEEK_MAIL_ACCOUNT_EDITOR_EDITBOX_ADDRESS_CTRL_ID,
		MMI_PEEK_MAIL_ACCOUNT_EDITOR_SIGNATURE_FORM_CTRL_ID,
			MMI_PEEK_MAIL_ACCOUNT_EDITOR_LABEL_SIGNATURE_CTRL_ID,
			MMI_PEEK_MAIL_ACCOUNT_EDITOR_EDITBOX_SIGNATURE_CTRL_ID,

	MMI_PEEK_MAIL_MANAGER_STORAGE_CTRL_ID,

	MMI_PEEK_MAIL_CONTACT_CTRL_ID,
	MMI_PEEK_MAIL_CONTACT_MENU_CTRL_ID,
	MMI_PEEK_MAIL_CONTACT_EDIT_MENU_CTRL_ID,

	MMI_PEEK_MAIL_CONTACT_EDITOR_FORM_CTRL_ID,
		MMI_PEEK_MAIL_CONTACT_EDITOR_NAME_FORM_CTRL_ID,
			MMI_PEEK_MAIL_CONTACT_EDITOR_LABEL_NAME_CTRL_ID,
			MMI_PEEK_MAIL_CONTACT_EDITOR_EDITBOX_NAME_CTRL_ID,
		MMI_PEEK_MAIL_CONTACT_EDITOR_PHONE_FORM_CTRL_ID,
			MMI_PEEK_MAIL_CONTACT_EDITOR_LABEL_PHONE_CTRL_ID,
			MMI_PEEK_MAIL_CONTACT_EDITOR_EDITBOX_PHONE_CTRL_ID,
		MMI_PEEK_MAIL_CONTACT_EDITOR_ADDRESS_FORM_CTRL_ID,
			MMI_PEEK_MAIL_CONTACT_EDITOR_LABEL_ADDRESS_CTRL_ID,
			MMI_PEEK_MAIL_CONTACT_EDITOR_EDITBOX_ADDRESS_CTRL_ID,		
			
	MMI_PEEK_MAIL_SEARCH_FORM_CTRL_ID,
		MMI_PEEK_MAIL_SEARCH_LOOKING_FOR_CTRL_ID,
			MMI_PEEK_MAIL_SEARCH_LABEL_LOOKING_FOR_STH_CTRL_ID,
		MMI_PEEK_MAIL_SEARCH_DATE_FORM_CTRL_ID,
			MMI_PEEK_MAIL_SEARCH_LABEL_DATE_CTRL_ID,
			MMI_PEEK_MAIL_SEARCH_EDITBOX_DATE_CTRL_ID,
		MMI_PEEK_MAIL_SEARCH_ATTACHMENTS_FORM_CTRL_ID,
			MMI_PEEK_MAIL_SEARCH_LABEL_ATTACHMENTS_CTRL_ID,
			MMI_PEEK_MAIL_SEARCH_EDITBOX_ATTACHMENTS_CTRL_ID,
		MMI_PEEK_MAIL_SEARCH_SUBJECT_FORM_CTRL_ID,
			MMI_PEEK_MAIL_SEARCH_LABEL_SUBJECT_CTRL_ID,
			MMI_PEEK_MAIL_SEARCH_EDITBOX_SUBJECT_CTRL_ID,
		MMI_PEEK_MAIL_SEARCH_FROM_FORM_CTRL_ID,
			MMI_PEEK_MAIL_SEARCH_LABEL_FROM_CTRL_ID,
			MMI_PEEK_MAIL_SEARCH_EDITBOX_FROM_CTRL_ID,

	
	MMIPEEKMAIL_MAX_CTRL_ID
}MMIPEEKMAIL_CONTROL_ID_E;

