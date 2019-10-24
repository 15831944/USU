/*****************************************************************
------------------------------------------------------------------
 
    RapTraSDK.h

    This header adapt's some win32 SDK functions so that they
    use the RapidTranslation DLL to translate strings
  
    To use RapidTranslation with "direct" win32 SDK programming,
    please include this file

------------------------------------------------------------------
*****************************************************************/

/*****************************************************************

    Don't allow multiple inclusion of this file

*****************************************************************/

#ifndef INC_RAPTRA_SDK_HEADER
#define INC_RAPTRA_SDK_HEADER


/*****************************************************************

    This uses the RapidTranslation DLL 

*****************************************************************/

#include "RapTra.h"


/*****************************************************************
------------------------------------------------------------------

    Adapt the  Win32 - Function LoadString

------------------------------------------------------------------
*****************************************************************/


/*****************************************************************

    Adapt the 8-bit-character version

*****************************************************************/

#ifndef _UNICODE

/* Be sure it isn't #define'd yet */
#undef LoadStringA

/* The #define'd function has to use the RapTra DLL */
static int __X_LoadStringA(HINSTANCE hInstance, UINT uID, 
	LPSTR lpBuffer, int nBufferMax)
{
	/* Local vars */
	char* szBuffer;
	int nRes, nRTRes;

	/* We have to use a temporary buffer */
	szBuffer = (char*) malloc((nBufferMax + 1) * sizeof(char));
	
	/* First use LoadString */
	nRes = LoadStringA(hInstance, uID, szBuffer, nBufferMax);
	
	/* If not found, return 0 */
	if(nRes == 0)
	{
		free(szBuffer);
		return 0;
	}

	/* Now translate the string */
	nRTRes = RTTranslateString(lpBuffer, szBuffer, nBufferMax);
	
	/* If RapidTranslation cannot translate, use orig string */
	if(nRTRes == 0)
	{
		/* truncate Buffer if necessary */
		szBuffer[nBufferMax-1] = 0;

		/* copy original string */
		_tcscpy(lpBuffer, szBuffer);

		/* return original string length */
		free(szBuffer);
		return nRes;
	}

	/* return translated string length */
	free(szBuffer);
	return nRTRes;
}

/* Now #define it ! */
#define LoadStringA __X_LoadStringA

/* #ifndef _UNICODE*/
#endif

/*****************************************************************

    Adapt the UNICODE version

*****************************************************************/

#ifdef _UNICODE

/* Be sure it isn't #define'd yet */
#undef LoadStringW

/* The #define'd function has to use the RapTra DLL */
static int __X_LoadStringW(HINSTANCE hInstance, UINT uID, 
	LPWSTR lpBuffer, int nBufferMax)
{
	/* Some local vars */
	WCHAR* szBuffer;
	int nRes, nRTRes;
	
	/* We have to use a temporary buffer */
	szBuffer = (WCHAR*) malloc((nBufferMax + 1) * sizeof(WCHAR));
	
	/* First use LoadString */
	nRes = LoadStringW(hInstance, uID, szBuffer, nBufferMax);
	
	/* If not found, return 0 */
	if(nRes == 0)
	{
		free(szBuffer);
		return 0;
	}

	/* Now translate the string */
	nRTRes = RTTranslateString(lpBuffer, szBuffer, nBufferMax);
	
	/* If RapidTranslation cannot translate, use orig string */
	if(nRTRes == 0)
	{
		/* truncate Buffer if necessary */
		szBuffer[nBufferMax-1] = NULL;

		/* copy original string */
		_tcscpy(lpBuffer, szBuffer);

		/* return original string length */
		free(szBuffer);
		return nRes;
	}

	/* return translated string length */
	free(szBuffer);
	return nRTRes;
}

/* Now #define it ! */
#define LoadStringW __X_LoadStringW

/* #ifdef _UNICODE */
#endif

/*****************************************************************

    end of c linkage and
	multiple inclusion prevention of this file

*****************************************************************/

/* multiple inclusion */
#endif


