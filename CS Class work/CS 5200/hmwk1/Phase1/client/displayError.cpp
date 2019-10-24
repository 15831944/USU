#include "stdafx.h"

void DisplayErrorMessage(DWORD ErrorNum, char *AdditionalMessage = NULL)
{
	if (ErrorNum)
	{
	
		LPVOID lpMsgBuf = NULL;
		FormatMessage( 
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM | 
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			ErrorNum,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf,
			0,
			NULL 
		);
		// Process any inserts in lpMsgBuf.
		// ...
		// Display the string.
		char messageString[100];
		messageString[0] = '\0';

		if (lpMsgBuf)
		{
			strcat(messageString,(LPCTSTR)lpMsgBuf);
		}
		else
		{
			strcat(messageString,"Unknown error occured.");
		}
		//wsprintf(messageString,"%s%s",messageString,(LPCTSTR)lpMsgBuf);
		if (AdditionalMessage)
			strcat(messageString,AdditionalMessage);
		//wsprintf(messageString,"%s%s",messageString,AdditionalMessage);

		MessageBox( NULL, messageString, NULL, MB_OK | MB_ICONINFORMATION );
		// Free the buffer.
		LocalFree( lpMsgBuf );
	}
}