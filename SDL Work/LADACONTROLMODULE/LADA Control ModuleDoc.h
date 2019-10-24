// LADA Control ModuleDoc.h : interface of the CLADAControlModuleDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LADACONTROLMODULEDOC_H__B5A7CF9F_72B9_11D4_98D9_00A076801ACD__INCLUDED_)
#define AFX_LADACONTROLMODULEDOC_H__B5A7CF9F_72B9_11D4_98D9_00A076801ACD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_INPUT_LOCATIONS		256

typedef char InputListType[2][30];

class CGraphDoc;

class CLADAControlModuleDoc : public CDocument
{
	friend class CGraphDoc;
	friend class CProjectSettingsDlg;
protected: // create from serialization only
	CLADAControlModuleDoc();
	DECLARE_DYNCREATE(CLADAControlModuleDoc)

	BOOL  DocInitialized;
	BOOL InCommMode;
	DWORD RTime;
	DWORD DelayTime;
	int ThreadsInFunction;
	int ThreadsInCommunication;
	int ThreadsInStartBlock;

	HANDLE CommSyncObject;
	HANDLE DataTimer;
	CView * pGraphView[4];
	BOOL NewDataExists;
	HANDLE ILFileOut;
	CTime lastFileCreationTime;
	CTime lastSaveTime;
	BOOL *graphListModified;
	int numGraphs;
	int curWindow;
	BOOL DoAutoWrap;
// Attributes which were in CGraphDoc
	int *nDataGraph;
	BOOL (*ItemChecked)[15];
	int (*DataIndex)[15];
	
// Attributes which were in CGraphDisplay
	CPen *pens;
	COLORREF *colors;
	CBrush backgroundBrush;
	CPen penThickBlack;
	CPen penThinBlack;
	CPen penThinGray;

// Attributes	
	double * GraphData;
	double * tempArray;
	double * tempSaveData;
	double * newData;
	int nItemsInTempArray;
	int GraphDataBlockSize;
	int nData;
	int nFilledPoints;
	int nFilledSaveData;
	int nBackPoints;
	int maxGraphItems;
	int GraphDataPos;
	CTime * PositionTime;
	CTimeSpan dataPlotFreq;
	CTimeSpan dataRetrievalFreq;
	CTimeSpan dataWriteFreq;
	BOOL saveFinalStorage;
	BOOL saveLocations;
	BOOL saveByAverage;
	BOOL saveByTime;
	int newFileSize;
	CTimeSpan newFileFreq;
	CString dataFolder;
	CString projectOptionsFile;

	InputListType *InputLocationNameList;
	int *InputLocationSaveList;
	
	
// Operations
public:
	void OnStartNewDocument();
	BOOL StopComm();
	void InitCommSynchronization();
	void StartCommBlock();
	void EndCommBlock();
	void WriteInputLocations();
	void AddData(double data[], CTime dataTime, BOOL UpdateViews = TRUE);
	double GetDataValue(int whichGraph, int whichData, int Position);
	const char * GetDataName(int whichGraph, int whichData);
	CString GetPositionLabel(int Position);
	void FillWithRandomData();
	void SetLastFile(CString fileName);
	void ToggleData(int whichWindow, int whichButton);
	BOOL IsItemChecked(int whichWindow, int whichButton);

	CCommOperations *commObject;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLADAControlModuleDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void OnCloseDocument();
	virtual void DeleteContents();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	CString m_PcmciaDefault;
	CString m_FloppyDefault;
	void UpdateGraphViews();
	virtual ~CLADAControlModuleDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLADAControlModuleDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LADACONTROLMODULEDOC_H__B5A7CF9F_72B9_11D4_98D9_00A076801ACD__INCLUDED_)
