/*****************************************************************
------------------------------------------------------------------
 
    RapTraMFCFix.h
  
    This header #define's macros that make virtual functions,
	that have parameters of type CString, work correctly.

    Every time such a function is used, the correspondending macro
	has to be used in the same public / protected / private section

------------------------------------------------------------------
*****************************************************************/


/*****************************************************************
------------------------------------------------------------------

    #define macros for every mfc class that has a virtual function
	with parameter CString

------------------------------------------------------------------
*****************************************************************/


/*****************************************************************

    class CDaoRecordset

*****************************************************************/

// CString CDaoRecordset::GetDefaultDBName()
#define RTFIX_CDAORECORDSET_GETDEFAULTDBNAME() \
	virtual __Y_CString GetDefaultDBName() \
	{ return GetDefaultDBName(); } \

// CString CDaoRecordset::GetDefaultSQL()
#define RTFIX_CDAORECORDSET_GETDEFAULTSQL() \
	virtual __Y_CString GetDefaultSQL() \
	{ return GetDefaultSQL(); } \


/*****************************************************************

    class CDocManager

*****************************************************************/

// BOOL CDocManager::DoPromptFileName(CString&, UINT, DWORD, BOOL, CDocTemplate*);
#define RTFIX_CDOCMANAGER_DOPROMPTFILENAME() \
	virtual BOOL DoPromptFileName(__Y_CString& fileName, UINT nIDSTitle, \
		DWORD lFlags, BOOL bOpenFileDialog, CDocTemplate* pTemplate) \
	{ return DoPromptFileName((__X_CString&)fileName, nIDSTitle, lFlags, bOpenFileDialog, pTemplate); } \


/*****************************************************************

    class CDocTemplate

*****************************************************************/

// BOOL CDocTemplate::GetDocString(CString&, enum DocStringIndex);
#define RTFIX_CDOCTEMPLATE_GETDOCSTRING() \
	virtual BOOL GetDocString(__Y_CString& rString,	enum DocStringIndex index) const  \
	{ return GetDocString((__X_CString&)rString, index); } \


/*****************************************************************

    class COleServerDoc

*****************************************************************/

// BOOL COleServerDoc::GetFileTypeString(CString& rString);
#define RTFIX_COLESERVERDOC_GETFILETYPESTRING() \
	virtual BOOL GetFileTypeString(__Y_CString& rString) \
	{ return GetFileTypeString((__X_CString &)rString); } \


/*****************************************************************

    class CFile

*****************************************************************/

// CString CFile::GetFileName() const
#define RTFIX_CFILE_GETFILENAME() \
	virtual __Y_CString GetFileName() const \
	{ return (__Y_CString) GetFileName(); } \

// CString CFile::GetFileTitle() const
#define RTFIX_CFILE_GETFILETITLE() \
	virtual __Y_CString GetFileTitle() const \
	{ return (__Y_CString) GetFileTitle(); } \

// CString CFile::GetFilePath() const
#define RTFIX_CFILE_GETFILEPATH() \
	virtual __Y_CString GetFilePath() const \
	{ return (__Y_CString) GetFilePath(); } \


/*****************************************************************

    class COleStreamFile

*****************************************************************/

// const CString COleStreamFile::GetStorageName() const;
#define RTFIX_COLESTREAMFILE_GETSTORAGENAME() \
	virtual const __Y_CString GetStorageName() const \
	{ return (__Y_CString) GetStorageName(); } \


/*****************************************************************

    class CStdioFile

*****************************************************************/

// BOOL CStdioFile::ReadString(CString&)
#define RTFIX_CSTDIOFILE_READSTRING() \
	virtual BOOL ReadString(__Y_CString& rString) \
	{ return ReadString((__X_CString&)rString); } \

		
/*****************************************************************

    class CHttpFile

*****************************************************************/

// CString CHttpFile::GetFileURL() const;
#define RTFIX_CHTTPFILE_GETFILEURL() \
	virtual __Y_CString GetFileURL() const \
	{ return (__Y_CString) GetFileURL(); } \


/*****************************************************************

    class CFileFind

*****************************************************************/

// CString CFileFind::GetFileName() const;
#define RTFIX_CFILEFIND_GETFILENAME() \
	virtual __Y_CString GetFileName() const \
	{ return (__Y_CString) GetFileName(); } \

// CString CFileFind::GetFilePath() const;
#define RTFIX_CFILEFIND_GETFILEPATH() \
	virtual __Y_CString GetFilePath() const \
	{ return (__Y_CString) GetFilePath(); } \

// CString CFileFind::GetFileTitle() const;
#define RTFIX_CFILEFIND_GETFILETITLE() \
	virtual __Y_CString GetFileTitle() const \
	{ return (__Y_CString) GetFileTitle(); } \

// CString CFileFind::GetFileURL() const;
#define RTFIX_CFILEFIND_GETFILEURL() \
	virtual __Y_CString GetFileURL() const \
	{ return (__Y_CString) GetFileURL(); } \

// CString CFileFind::GetRoot() const;
#define RTFIX_CFILEFIND_GETROOT() \
	virtual __Y_CString GetRoot() const \
	{ return (__Y_CString) GetRoot(); } \


/*****************************************************************

    class COleControl

*****************************************************************/

// void COleControl::GetMessageString(UINT, CString&)
#define RTFIX_COLECONTROL_GETMESSAGESTRING() \
	virtual void GetMessageString(UINT nID, __Y_CString& rString) \
	{ GetMessageString(nID, (__X_CString&)rString); } \

// BOOL COleControl::OnGetDisplayString(DISPID, CString&);
#define RTFIX_COLECONTROL_ONGETDISPLAYSTRING() \
	virtual BOOL OnGetDisplayString(DISPID id, __Y_CString& rString) \
	{ return OnGetDisplayString(id, (__X_CString&)rString); } \


/*****************************************************************

    class CRecordset

*****************************************************************/

// CString CRecordset::GetDefaultConnect();
#define RTFIX_CRECORDSET_GETDEFAULTCONNECT() \
	virtual __Y_CString GetDefaultConnect() \
	{ return (__Y_CString) GetDefaultConnect(); } \
	
// CString CRecordset::GetDefaultSQL();
#define RTFIX_CRECORDSET_GETDEFAULTSQL() \
	virtual __Y_CString GetDefaultSQL() \
	{ return (__Y_CString) GetDefaultSQL(); } \


/*****************************************************************

    class CFrameWnd

*****************************************************************/

// CFrameWnd::GetMessageString(UINT, CString&) const;
#define RTFIX_CFRAMEWND_GETMESSAGESTRING() \
	virtual void GetMessageString(UINT nID, __Y_CString& rMessage) const \
	{ GetMessageString(nID, (__X_CString&)rMessage); } \


/*****************************************************************
------------------------------------------------------------------

    Now make some typedef's
	without them it would not be possible to fix the whole problem
	of virtual functions only in the headers

	This typedef gives acces to original CString as __Y_CString

------------------------------------------------------------------
*****************************************************************/

#undef CString
typedef CString __Y_CString;
#define CString __X_CString








