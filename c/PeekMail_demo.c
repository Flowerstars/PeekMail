/*****************************************************************************
** File Name:      peekmail_main.c                                               *
** Author:                                                                   *
** Date:             5/20/2011                                                 *
** Copyright:      2011 Peek Inc. All Rights Reserved.       *
** Description:    This file is used to describe call log                    *
******************************************************************************
**                         Important Edit History                            *
** --------------------------------------------------------------------------*
**   DATE           NAME             DESCRIPTION                               *
** 5.20/2011    Song,Han               Create                                   *
******************************************************************************/

/**--------------------------------------------------------------------------*/
/**                         Include Files                                    */
/**--------------------------------------------------------------------------*/
#include "PeekMail_demo.h"


/**--------------------------------------------------------------------------*/
/**                         MACRO DEFINITION                                 */
/**--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                          TYPE AND STRUCT                                   */
/*----------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                          CONSTANT ARRAY                                   */
/*---------------------------------------------------------------------------*/

/**--------------------------------------------------------------------------*/
/**                         EXTERNAL DECLARE                                 */
/**--------------------------------------------------------------------------*/

/**--------------------------------------------------------------------------*/
/**                         STATIC DEFINITION                                */
/**--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                          LOCAL FUNCTION DECLARE                           */
/*---------------------------------------------------------------------------*/

/**--------------------------------------------------------------------------*/
/**                         GLOBAL DEFINITION                                */
/**--------------------------------------------------------------------------*/

/**--------------------------------------------------------------------------*
 **                         FUNCTION DEFINITION                              *
 **--------------------------------------------------------------------------*/
PUBLIC void PeekMailDemoGenerate(uint8 *infoPath)
{
	wchar				info_file_name[256];
	MMIFILE_HANDLE		hFile;

	MMIAPICOM_StrToWstr(infoPath,info_file_name);
	hFile = MMIFILE_CreateFile(
				info_file_name,
				SFS_MODE_READ | SFS_MODE_OPEN_EXISTING,
				PNULL,
				PNULL);

	if(SFS_INVALID_HANDLE == hFile)
	{
		GenerateMails();
		GenerateAccounts();
		GenerateContacts();
	}
	MMIFILE_CloseFile(hFile);
}

LOCAL void GenerateMails(void)
{
	uint32			buf_len;
	uint32			index;
	int8			inboxFileStr[] = "7";
	int32			inboxFileNum = 7;
	int8			folderFileStr[] = "0";
	wchar			file_name[256];
	int8			*mail_file_path[] = {
		"D:\\PeekMail\\Inbox\\1",
		"D:\\PeekMail\\Inbox\\2",
		"D:\\PeekMail\\Inbox\\3",
		"D:\\PeekMail\\Inbox\\4",
		"D:\\PeekMail\\Inbox\\5",
		"D:\\PeekMail\\Inbox\\6",
		"D:\\PeekMail\\Inbox\\7"
	};
	int8			*mail_file_contents[] = {
		"read:0\r\ndate:06.10.2011\r\ntime:11:22 PM\r\nfrom:john@gmail.com\r\nto:micheal@hotmail.com\r\nsubject:Great Meetting\r\ntext:\r\nhi, Micheal,\r\nI have sent you the address and date of the coming meetting. There must be lots of people come in here and discuss about the issue we had talked in the last meetting. See you there.\r\n\r\nGood luck.\r\n\r\nJohn\r\n",
		"read:1\r\ndate:06.10.2011\r\ntime:3:53 PM\r\nfrom:amol@peek9.com\r\nto:micheal@hotmail.com\r\nsubject:Demos\r\ntext:\r\nHey guys! Got almost all your demos... but if you did not use Jing it does not work on screencast! Please use Jing... or upload to youtube.\r\n",
		"read:1\r\ndate:06.10.2011\r\ntime:11:33 AM\r\nfrom:amol@peek9.com\r\nto:Matthieu Labour <matthieu@getpeek.com>\r\nsubject:Wifi on 7th floor\r\ntext:\r\nAll - there is a wifi service provided by our hosts on the 7th floor:\r\n\r\nSSID= THG-PEEK\r\nWPA2 pass = peeky007\r\n\r\n\r\nIf we set up another one, then that will be 2.\r\n",
		"read:0\r\ndate:06.10.2011\r\ntime:5:52 PM\r\nfrom:amol@peek9.com\r\nto:interns11@peek9.com\r\nsubject:Payment details\r\ntext:\r\nHello everyone!\r\nI am trying to run payroll.\r\nI need name, address to mail check to, social security number (you need to have one to get paid).\r\nI need the SSNs from everyone - even if you have gotten a payment already from me.\r\n",
		"read:1\r\ndate:06.10.2011\r\ntime:2:44 PM\r\nfrom:amol@peek9.com\r\nto:genius@getpeek.com\r\nsubject:Welcome new interns and next month\r\ntext:\r\nHello everyone!\r\nYou survived 1 month so far. Good job.\r\nSo far I talked to everyone and gave you some feedback. Some of you will be switching to part time or taking some time off during July -- but most of you are going to continue. Great work. I have payment details from everyone and you will get some checks in the mail next week.\r\n\r\nAmol",
		"read:1\r\ndate:Jun 9, 2011\r\ntime:11:13 AM\r\nfrom:amol@peek9.com\r\nto:interns11@peek9.com\r\nsubject:How to do research for a startup\r\ntext:\r\nHey guys,\r\n\r\nI gave a presentation today to a startup class at NYU Stern. Attached is the presentation.\r\n\r\nSkype me to asarva and I will tell you more about it. If you guys are interested I can tell you more about it or repeat the lecture.\r\n\r\nAmol\r\n",
		"read:1\r\ndate:Jul 6, 2011\r\ntime:10:13 AM\r\nfrom:amol@peek9.com\r\nto:han@getpeek.com\r\nsubject: Re: SPRD Peekmail demo\r\ntext:\r\nHey Han,\r\n\r\nUnless you add some nice music :)\r\n\r\nAmol\r\n"
	};
	MMIFILE_HANDLE	hFile;

	MMIAPICOM_StrToWstr(INBOX_INFO, file_name);
	hFile = MMIFILE_CreateFile(
				file_name, 
				SFS_MODE_WRITE | SFS_MODE_CREATE_NEW,
				PNULL,
				PNULL);
	if (SFS_INVALID_HANDLE == hFile) {
		return;
	}
	MMIFILE_WriteFile(hFile, inboxFileStr, strlen(inboxFileStr), &buf_len, PNULL);
	MMIFILE_CloseFile(hFile);

	for (index = 0; index < inboxFileNum; index++) {
		MMIAPICOM_StrToWstr(mail_file_path[index], file_name);
		hFile = MMIFILE_CreateFile(
					file_name,
					SFS_MODE_WRITE | SFS_MODE_CREATE_NEW,
					PNULL,
					PNULL);
		if (SFS_INVALID_HANDLE == hFile) {
			continue;
		}
		MMIFILE_WriteFile(
			hFile,
			mail_file_contents[index],
			strlen(mail_file_contents[index]),
			&buf_len,
			PNULL);
		MMIFILE_CloseFile(hFile);
	}
	
	//set dir.info for Sent folder
	MMIAPICOM_StrToWstr(SENT_INFO, file_name);
	hFile = MMIFILE_CreateFile(
				file_name, 
				SFS_MODE_WRITE | SFS_MODE_CREATE_NEW,
				PNULL,
				PNULL);
	if (SFS_INVALID_HANDLE == hFile) {
		return;
	}
	MMIFILE_WriteFile(hFile, folderFileStr, strlen(folderFileStr), &buf_len, PNULL);
	MMIFILE_CloseFile(hFile);

	//set dir.info for Saved folder
	MMIAPICOM_StrToWstr(SAVED_INFO, file_name);
	hFile = MMIFILE_CreateFile(
				file_name, 
				SFS_MODE_WRITE | SFS_MODE_CREATE_NEW,
				PNULL,
				PNULL);
	if (SFS_INVALID_HANDLE == hFile) {
		return;
	}
	MMIFILE_WriteFile(hFile, folderFileStr, strlen(folderFileStr), &buf_len, PNULL);
	MMIFILE_CloseFile(hFile);

	//set dir.info for Drafts folder
	MMIAPICOM_StrToWstr(DRAFTS_INFO, file_name);
	hFile = MMIFILE_CreateFile(
				file_name, 
				SFS_MODE_WRITE | SFS_MODE_CREATE_NEW,
				PNULL,
				PNULL);
	if (SFS_INVALID_HANDLE == hFile) {
		return;
	}
	MMIFILE_WriteFile(hFile, folderFileStr, strlen(folderFileStr), &buf_len, PNULL);
	MMIFILE_CloseFile(hFile);

	//set dir.info for Trash folder
	MMIAPICOM_StrToWstr(TRASH_INFO, file_name);
	hFile = MMIFILE_CreateFile(
				file_name, 
				SFS_MODE_WRITE | SFS_MODE_CREATE_NEW,
				PNULL,
				PNULL);
	if (SFS_INVALID_HANDLE == hFile) {
		return;
	}
	MMIFILE_WriteFile(hFile, folderFileStr, strlen(folderFileStr), &buf_len, PNULL);
	MMIFILE_CloseFile(hFile);	
}

LOCAL void GenerateAccounts(void)
{
	uint32			buf_len;
	uint32			index;
	int8			accountFileStr[] = "3";
	int32			accountFileNum = 3;
	wchar			file_name[256];
	int8			*account_file_path[] = {
		"D:\\PeekMail\\Accounts\\1",
		"D:\\PeekMail\\Accounts\\2",
		"D:\\PeekMail\\Accounts\\3"
	};
	int8			*account_file_contents[] = {
		"active:1\r\nprimary:1\r\naccount_name:Peek.Gmail\r\nfirst_name:Han\r\nlast_name:Song\r\npassword:peek\r\naddress:han@getpeek.com\r\nsignature:\r\nHan SONG\r\n+1 917 868 5196\r\nwww.getpeek.com\r\n",
		"active:1\r\nprimary:0\r\naccount_name:BOBO.Hotmail\r\nfirst_name:Zhengbo\r\nlast_name:Liu\r\npassword:peek\r\naddress:liuzhengbo111@hotmail.com\r\nsignature:\r\nZhengbo Liu\r\nCS Dep. @Corant, NYU\r\n",
		"active:0\r\nprimary:0\r\naccount_name:NYU.Gmail\r\nfirst_name:Han\r\nlast_name:Song\r\npassword:peek\r\naddress:hs1359@nyu.edu\r\nsignature:\r\nHan Song\r\nCS Dep. @Corant, NYU\r\n"
	};
	MMIFILE_HANDLE	hFile;

	MMIAPICOM_StrToWstr(ACCOUNT_INFO, file_name);
	hFile = MMIFILE_CreateFile(
				file_name, 
				SFS_MODE_WRITE | SFS_MODE_CREATE_NEW,
				PNULL,
				PNULL);
	if (SFS_INVALID_HANDLE == hFile) {
		return;
	}
	MMIFILE_WriteFile(hFile, accountFileStr, strlen(accountFileStr), &buf_len, PNULL);
	MMIFILE_CloseFile(hFile);

	for (index = 0; index < accountFileNum; index++) {
		MMIAPICOM_StrToWstr(account_file_path[index], file_name);
		hFile = MMIFILE_CreateFile(
					file_name,
					SFS_MODE_WRITE | SFS_MODE_CREATE_NEW,
					PNULL,
					PNULL);
		if (SFS_INVALID_HANDLE == hFile) {
			return;
		}
		MMIFILE_WriteFile(
			hFile,
			account_file_contents[index],
			strlen(account_file_contents[index]),
			&buf_len,
			PNULL);
		MMIFILE_CloseFile(hFile);
	}
}

LOCAL void GenerateContacts(void)
{
	uint32			buf_len;
	uint32			index;
	int8			contactFileStr[] = "3";
	int32			contactFileNum = 3;
	wchar			file_name[256];
	int8			*contact_file_path[] = {
		"D:\\PeekMail\\Contacts\\1",
		"D:\\PeekMail\\Contacts\\2",
		"D:\\PeekMail\\Contacts\\3"
	};
	int8			*contact_file_contents[] = {
		"name:Santa C.\r\nphone:8561139876\r\nmail:santa.c@christmas.net\r\n",
		"name:peek service\r\nphone:8776777335\r\nmail:custom_service@peek9.com\r\n",
		"name:coco\r\nphone:9871234560\r\nmail:coco@ococ.com\r\n"
	};
	MMIFILE_HANDLE	hFile;

	MMIAPICOM_StrToWstr(CONTACT_INFO, file_name);
	hFile = MMIFILE_CreateFile(
				file_name, 
				SFS_MODE_WRITE | SFS_MODE_CREATE_NEW,
				PNULL,
				PNULL);
	if (SFS_INVALID_HANDLE == hFile) {
		return;
	}
	MMIFILE_WriteFile(hFile, contactFileStr, strlen(contactFileStr), &buf_len, PNULL);
	MMIFILE_CloseFile(hFile);

	for (index = 0; index < contactFileNum; index++) {
		MMIAPICOM_StrToWstr(contact_file_path[index], file_name);
		hFile = MMIFILE_CreateFile(
					file_name,
					SFS_MODE_WRITE | SFS_MODE_CREATE_NEW,
					PNULL,
					PNULL);
		if (SFS_INVALID_HANDLE == hFile) {
			return;
		}
		MMIFILE_WriteFile(
			hFile,
			contact_file_contents[index],
			strlen(contact_file_contents[index]),
			&buf_len,
			PNULL);
		MMIFILE_CloseFile(hFile);
	}
}

