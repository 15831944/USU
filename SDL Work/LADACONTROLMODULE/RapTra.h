
/*****************************************************************
------------------------------------------------------------------
    
	RapTra.h

    This header file declares the functions of the 
	RapidTranslation DLL

	To use RapidTranslation, please include this file
	
------------------------------------------------------------------
*****************************************************************/


/*****************************************************************

    Some useful defines

    These defines are used for importing the DLL functions

*****************************************************************/

/* Dont allow multiple includes of this file*/
#if !defined(RAPTRA_DLL_INCLUDED)
#define RAPTRA_DLL_INCLUDED


/* Make sure c-linkage is used */
#ifdef __cplusplus
extern "C" {
#endif


/* This define is used for exported / imported functions */
//*
#ifdef RAPTRADLL_EXPORTS
#define RAPTRADLL_API         __declspec(dllexport) 
#define RAPTRADLL_API_BOOL    __declspec(dllexport) BOOL
#define RAPTRADLL_API_INT     __declspec(dllexport) int
#define RAPTRADLL_API_HBITMAP __declspec(dllexport) HBITMAP
#else
#define RAPTRADLL_API         __declspec(dllimport) 
#define RAPTRADLL_API_BOOL    __declspec(dllimport) BOOL
#define RAPTRADLL_API_INT     __declspec(dllimport) int
#define RAPTRADLL_API_HBITMAP __declspec(dllimport) HBITMAP
#endif
/**/

/*  In one of the next releases the following #defines will be used */
/*  The only difference is "__stdcall" to allow VisualBasic compatibility */
/*  To use these you need a special version of RapTra30.dll */ 
/*
#ifdef RAPTRADLL_EXPORTS
#define RAPTRADLL_API         __declspec(dllexport) 
#define RAPTRADLL_API_BOOL    __declspec(dllexport) BOOL    __stdcall
#define RAPTRADLL_API_INT     __declspec(dllexport) int     __stdcall
#define RAPTRADLL_API_HBITMAP __declspec(dllexport) HBITMAP __stdcall
#else
#define RAPTRADLL_API         __declspec(dllimport) 
#define RAPTRADLL_API_BOOL    __declspec(dllimport) BOOL    __stdcall
#define RAPTRADLL_API_INT     __declspec(dllimport) int     __stdcall
#define RAPTRADLL_API_HBITMAP __declspec(dllimport) HBITMAP __stdcall
#endif

/****************************************************************/

/*****************************************************************
------------------------------------------------------------------

    struct's
	--------

    This section declares the struct's used in the RapidTranslation
    system.

------------------------------------------------------------------
*****************************************************************/

/*****************************************************************

    RT_LANGUAGEPARAMS

    This struct describes the parameters of 
    RapidTranslation file (.tra)

*****************************************************************/

typedef struct
{
	/* Size of this struct */
	DWORD dwSize;

	/* Name of program */
	TCHAR szPrg[256];

	/* Version of program */
	TCHAR szVer[256];

	/* Name of language */
	TCHAR szName[256];
	
	/* Language ID (since 3.0) */
	WORD nLanguageID;
	
	/* Name of translator (since 3.0) */
	TCHAR szAuthor[256];

	/* Date of Translation JJJJ-MM-DD (since 3.0) */
	TCHAR szDate[256];

	/* Comment for language */
	TCHAR szComment[1024];
	
	/* Path to this .tra file */
	TCHAR szFilePath[_MAX_PATH];
	
	/* Flags */
	DWORD dwFlags;

	/* Extended flags */
	DWORD dwExFlags;
}
RT_LANGUAGEPARAMS;


/*****************************************************************

    RT_STARTPARAMS

    This struct describes the parameters of the start of
    the RapidTranslation system

*****************************************************************/

typedef struct
{
	/* Size of this struct */
	DWORD dwSize;
	
	/* File and Path info */
	/* ------------------ */

	/* Path to initial language file (.tra) */
	TCHAR szStdFile[_MAX_PATH];

	/* Relative path to language files used for runtime switching */
	TCHAR szTraPath[_MAX_PATH];

	/* Automatic registry / ini - support */
	/* ---------------------------------- */
	
	/* hRegKey == NULL and szIniFilePath == NULL means:*/
	/*     No automatic ini / registry support */

	/* hRegKey != NULL means */
	/*     Automatic save last language in registry */

	/* szIniFilePath != NULL means */
	/*     Automatic save last language in ini file */
	
	/* Automatical write to this registry section */
	HKEY hRegKey;

	/* Automatical write to this ini file */
	TCHAR szIniFilePath[_MAX_PATH];
	
	/* Switch dialog configuration */
	/* --------------------------- */

	/* Allow older language versions in switch dialog */
	BOOL bSwitchDlgAllowOld;

	/* Help ID that the switch dialog throws (0 = no help button */
	UINT nSwitchDlgHelpID;

	/* Switch command menu extension */
	/* ----------------------------- */

	/* Do add automatically a "switch language" menu */
	BOOL bAutoSwitchCommand;
	
	/* Command ID of the "switch language" automatic menu item */
	UINT nSwitchCommandID;

	/* Position of main and sub menu that contains switch command */
	UINT nSwitchMainMenuPos;
	UINT nSwitchSubMenuPos;

	/* Windows Message to be broadcasted after a runtime language switch */
	/* NULL means: Don't broadcast message */
	UINT nSwitchBroadcastMsg;
}
RT_STARTPARAMS;



/*****************************************************************
------------------------------------------------------------------

    Start / cleanup functions
	-------------------------

    these functions have to be called at the start and the end
	of the application

------------------------------------------------------------------
*****************************************************************/


/*****************************************************************

    RTStart(RT_STARTPARAMS* pParams)

    This function starts the RapidTranslation system
	The return value is TRUE unless any error occured

*****************************************************************/

RAPTRADLL_API_BOOL RTStart(RT_STARTPARAMS* pParams);


/*****************************************************************

    RTAddThread(DWORD dwThreadID)

    This function adds a user interface thread to the RapidTranslation System
	The return value is TRUE unless any error occured

*****************************************************************/

RAPTRADLL_API_BOOL RTAddThread(DWORD dwThreadID);



/*****************************************************************

    RTEnd

    This function ends the RapidTranslation System
	The return value is TRUE unless any error occured

*****************************************************************/

RAPTRADLL_API_BOOL RTEnd();


/*****************************************************************
------------------------------------------------------------------

    Language file info functions
	----------------------------

    these functions provide information about the current active
	.TRA file and about other .TRA files

------------------------------------------------------------------
*****************************************************************/


/*****************************************************************

    RTGetLanguageParams

    This function retrieves Information about the current active
	language. It fills pParams. If any error occurs, the
	return value is FALSE.

*****************************************************************/

RAPTRADLL_API_BOOL RTGetLanguageParams(RT_LANGUAGEPARAMS* pParams);


/*****************************************************************

    RTGetLanguageBitmap

    This function retrieves a bitmap of the flag that symbolizes
	the current language. The device context is used for a proper construction
	of the bitmap.
	The return value is NULL if any error occurs

*****************************************************************/

RAPTRADLL_API_HBITMAP RTGetLanguageBitmap(HDC hDC);


/*****************************************************************

    RTGetLanguageFileParams

    This function retrieves Information about the language in the
	.TRA - file szFile.. It fills pParams. If any error occurs, the
	return value is FALSE.

*****************************************************************/

RAPTRADLL_API_BOOL RTGetLanguageFileParams(const TCHAR* szFile, RT_LANGUAGEPARAMS* pParams);


/*****************************************************************

    RTGetLanguageFileBitmap

    This function retrieves a bitmap of the flag that symbolizes
	the language described by the .TRA file szFile.
	The device context is used for a proper construction
	of the bitmap.
	The return value is NULL if any error occurs

*****************************************************************/

RAPTRADLL_API_HBITMAP RTGetLanguageFileBitmap(const TCHAR* szFile, HDC hDC);


/*****************************************************************
------------------------------------------------------------------

    Language switch functions
	-------------------------

    Use these functions to switch manually the language to another
	.TRA file or to call the RapidTranslation language switch dialog

------------------------------------------------------------------
*****************************************************************/

/*****************************************************************

    RTSwitchLanguage

    This function switches to a new language, specified in the
	.TRA - file szFile.
	All texts that are visible are translated.
	If specified in RT_STARTPARAMS, a windows message is
	broadcasted to all windows.
	The return value is FALSE if any error occured.

*****************************************************************/

RAPTRADLL_API_BOOL RTSwitchLanguage(const TCHAR* szFile);


/*****************************************************************

    RTSwitchDialog

    This function shows the RapidTranslation language switch dialog.
	In this Dialog the user can select one of the available languages.
	If a new language is chosen, all texts are switched to the new
	language.
	This dialog can be configured in the RT_STARTPARAMS struct.
	The return value is TRUE, if a new language was chosen,
	otherwise FALSE.
	
*****************************************************************/

RAPTRADLL_API_BOOL RTSwitchDialog();



/*****************************************************************
------------------------------------------------------------------

    Translation functions

    The function to translate strings has to be called every time
	a string is loaded from the stringtable.

	The other translation functions normally need not to be called.
	Only in very few cases it can be useful to call them.

------------------------------------------------------------------
*****************************************************************/


/*****************************************************************

    RTTranslateString()

    This function translates the text szSource to the proper language.
	szSource should have been loaded from the stringtable.
	The return value is the number of characters translated.

*****************************************************************/

RAPTRADLL_API_INT RTTranslateString(TCHAR* szDest, const TCHAR* szSource, int nMaxBuffer);


/*****************************************************************

    RTTranslateFirstLineString()

	This function translates the string szSource, if szSource is
	the first line of a stringtable entry
	The return value is the number of characters translated.

*****************************************************************/

RAPTRADLL_API_INT RTTranslateFirstLineString(TCHAR* szDest, const TCHAR* szSource, int nMaxBuffer);


/*****************************************************************

    RTTranslateLastLineString()

	This function translates the string szSource, if szSource is
	the last line of a stringtable entry
	The return value is the number of characters translated.

*****************************************************************/

RAPTRADLL_API_INT RTTranslateLastLineString(TCHAR* szDest, const TCHAR* szSource, int nMaxBuffer);


/*****************************************************************

    RTTranslateDialog()

	This function translates a dialog.
	The return value is TRUE is successful.
	This function is needed only in special cases

*****************************************************************/

RAPTRADLL_API_BOOL RTTranslateDialog(HWND hDialog);


/*****************************************************************

    RTTranslateMenu()

	This function translates a Menu of a window.
	The return value is TRUE is successful.
	This function is needed only in special cases

*****************************************************************/

RAPTRADLL_API_BOOL RTTranslateMenu(HWND hWnd);


/*****************************************************************

    RTTranslateContextMenu()

	This function translates a context menu. ("Right mouse menu")
	The return value is TRUE is successful.
	This function is needed only in special cases

*****************************************************************/

RAPTRADLL_API_BOOL RTTranslateContextMenu(HMENU hMenu);



/* End make sure c-linkage is used */
#ifdef __cplusplus
}
#endif

/* !defined(RAPTRA_DLL_INCLUDED) */
#endif 
