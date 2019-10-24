/*****************************************************************
------------------------------------------------------------------
 
    RapTraMFC.h
  
    This header adapt's the MFC so that it automatically
    uses the RapidTranslation DLL to translate strings

    To use RapidTranslation with MFC, please include this file

------------------------------------------------------------------
*****************************************************************/

/*****************************************************************

    Don't allow multiple inclusion of this file

*****************************************************************/

#ifndef INC_RAPTRA_MFC_HEADER
#define INC_RAPTRA_MFC_HEADER


/*****************************************************************

    This uses 
	- the RapidTranslation DLL 
	- the win32 SDK #define's
	- the Macros against virtual functions

*****************************************************************/

#include "RapTra.h"
#include "RapTraSDK.h"
#include "RapTraMFCFix.h"

/*****************************************************************
------------------------------------------------------------------

    Adapt the MFC class CString

------------------------------------------------------------------
*****************************************************************/

/* Be sure CString is not #define'd */
#undef CString

/*****************************************************************

    The maximum length of stringtable entry's
	Adapt this #define if you need larger strings

*****************************************************************/

#define _RAPTRA_MFC_MAX_STRINGTABLE_ENTRY 2048


/*****************************************************************

    This function translates a CString

*****************************************************************/

class __X_CString;

/* Translate the string */
static BOOL __X_TranslateString(CString& szText)
{
	/* Use this buffer */
	TCHAR szBuffer[_RAPTRA_MFC_MAX_STRINGTABLE_ENTRY];

	/* Translate the string */
	int nLen = RTTranslateString(szBuffer, szText,
		_RAPTRA_MFC_MAX_STRINGTABLE_ENTRY);

	/* Copy back if something has been translated */
	if(nLen > 0)
		szText = CString(szBuffer);

	/* TRUE if something was translated */
	return (nLen > 0);
}

/*****************************************************************

    This class does adapt the MFC class CString so that it uses
	RapidTranslation

*****************************************************************/

/* Declare the string load function */
BOOL __X_TranslateLoadString(CString& szText, UINT nID);

/* The adapted class */
class __X_CString : public CString
{
public:
	/* The constructors have to be overloaded to make castings work */
	__X_CString() : CString() {};
	__X_CString(const CString& stringSrc) : CString(stringSrc) {};
	__X_CString(TCHAR ch, int nRepeat = 1) : CString(ch, nRepeat) {};
	__X_CString(LPCTSTR lpch, int nLength) : CString(lpch, nLength) {};
	__X_CString(const unsigned char* psz) : CString(psz) {};

	/* These are conversion constructors */
	#ifdef _UNICODE
		__X_CString(LPCSTR lpsz) : CString(lpsz) {}; /* conversion a => w */
	#else
		__X_CString(LPCWSTR lpsz) : CString(lpsz) {}; /* conversion w => a */
	#endif

	/* And this is a constructor for stringtable entrys */
	__X_CString(LPCTSTR lpsz) : CString(lpsz) 
	{
		/* It is a stringtable constructor */
		if (lpsz != NULL && HIWORD(lpsz) == NULL)
		{
			/* Now translate this string */
			__X_TranslateString(*this);
		}
	}

	/* This overrides the LoadString function in normal chars ... */
	BOOL __X_LoadStringA(UINT nID)
	{
		return __X_TranslateLoadString(*this, nID);
	};

	/* ... and in UNICODE */
	BOOL __X_LoadStringW(UINT nID)
	{
		return __X_TranslateLoadString(*this, nID);
	};

	/* to access original stringtable */
	BOOL __X_GetTheString(UINT nID)
	{
		/* we have to switch off and on the SDK stuff */
		#undef LoadStringA
		#undef LoadStringW
			BOOL bRes = ((CString*)this)->LoadString(nID);
			return bRes;
		#ifdef _UNICODE
			#define LoadStringW __X_LoadStringW			
		#else
			#define LoadStringA __X_LoadStringA
		#endif
	};

	/* Format sring member functions */
	void AFX_CDECL Format(LPCTSTR lpszFormat, ...)
	{
		/* do it like mfc does it */
		ASSERT(AfxIsValidString(lpszFormat, FALSE));
		va_list argList;
		va_start(argList, lpszFormat);
		FormatV(lpszFormat, argList);
		va_end(argList);
	}
;
	/* This formats from stringtable string, so translate it */
	void AFX_CDECL Format(UINT nFormatID, ...)
	{
		/* translate ist */
		__X_CString strFormat;
		#ifdef _UNICODE
			VERIFY(strFormat.__X_LoadStringW(nFormatID) != 0);
		#else
			VERIFY(strFormat.__X_LoadStringA(nFormatID) != 0);
		#endif

		/* mfc formats */
		va_list argList;
		va_start(argList, nFormatID);
		FormatV(strFormat, argList);
		va_end(argList);
	}
};

/* Load and translate the string from stringtable */
static BOOL __X_TranslateLoadString(CString& szText, UINT nID)
{
	/* Load the original stringtable string */
	BOOL bRes = ((__X_CString*)&szText)->__X_GetTheString(nID);

	/* And translate it */
	BOOL bTrans = __X_TranslateString(szText);

	/* return TRUE even if not translated to prevent assert's */
	return bRes;
}

/* Now activate the new class */
#define CString __X_CString


/*****************************************************************
------------------------------------------------------------------

    Adapt the Message boxes

------------------------------------------------------------------
*****************************************************************/

/* Be sure AfxMessageBox is not #define'd */
#undef AfxMessageBox

/*****************************************************************

    The new AfxMessageBox - version

*****************************************************************/

/* AfxMessageBox from stringtable: translate ! */
static int __X_AfxMessageBox(UINT nIDPrompt, UINT nType = MB_OK,
	UINT nIDHelp = (UINT)-1)
{
	/* Get the translated text */
	__X_CString szText;
	__X_TranslateLoadString(szText, nIDPrompt);

	/* The rest is MFC*/
	return AfxMessageBox(szText, nType, nIDHelp);
}

/* Normal string - AfxMessageBox */
static int __X_AfxMessageBox(LPCTSTR lpszText, UINT nType = MB_OK,
	UINT nIDHelp = 0)
{
	return AfxMessageBox(lpszText, nType, nIDHelp);
}

/* Now activate the new message box */

#define AfxMessageBox __X_AfxMessageBox

/*****************************************************************

    End of multiple inclusion prevention

*****************************************************************/

#endif


