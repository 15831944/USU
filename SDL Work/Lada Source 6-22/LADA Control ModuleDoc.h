// LADA Control ModuleDoc.h : interface of the CLADAControlModuleDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LADACONTROLMODULEDOC_H__B5A7CF9F_72B9_11D4_98D9_00A076801ACD__INCLUDED_)
#define AFX_LADACONTROLMODULEDOC_H__B5A7CF9F_72B9_11D4_98D9_00A076801ACD__INCLUDED_

#include "InputLocFileInfo.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef char InputListType[2][30];

class CGraphDoc;
class CCommOperations;
class CInputLocFileInfo;
class CFSInfo;
class CLADAControlModuleView;
class CHistoryClass;
class CViewHistoryDialog;
class CMainFrame;
class CCameraData;
class CManualControl;

//class CInputRequest;
//class List;
//#include "List.h"
#include "WetupInfo.h"	// Added by ClassView
#include "ControlParameters.h"	// Added by ClassView
#include "LADA Control ModuleView.h"	// Added by ClassView

//template< class NODETYPE > class List; 
//enum RequestType {GraphData,CollectData,WriteData};

class CLADAControlModuleDoc : public CDocument
{
	friend class CGraphDoc;
	friend class CLADAControlModuleView;

	
// Implementation
// Operations
protected: // create from serialization only
	CLADAControlModuleDoc();
	DECLARE_DYNCREATE(CLADAControlModuleDoc)
public:
	virtual ~CLADAControlModuleDoc();

	BOOL StartDataRetrievalMode(BOOL StartTimers);
	void EndDataRetrievalMode();
	BOOL GetInputLocations(int *ptrFirstLocation, int nLocations, double *ptrReturnData, int wCall = 0, BOOL useDocIndex = FALSE);

	BOOL Connect( BOOL StartTimers, 
		ControlStateType desiredState, 
		BOOL DoInitialization = TRUE,
		BOOL FailOnWrongProgram = TRUE);
	BOOL EnsureCorrectCR10Program( ControlStateType desiredState );
	BOOL GetNewProjectSettings();
	BOOL IsItemChecked(int whichIndex, int whichButton);
	BOOL IsPositionLabel(int pos);
	BOOL LoadCameras();
	BOOL PerformInitialization(CString &notice);
	BOOL SetControlParameters(int whichChamber, double MoistLevel, int MaxDosage, BOOL In24Hour, int LightOn, int LightOff, int SMPFreq );	
	BOOL StopComm();
	BOOL UnloadCameras();
	BOOL WaitForNewData();
	const char * GetDataName(int whichGraph, int whichData);
	CString GetPositionLabel(int Position);
	double GetDataValue(int whichGraph, int whichData, int Position);
	void AddData(double data[], CTime dataTime, BOOL UpdateViews = TRUE);
	void AddGraphData(CTime dataTime);
	void AddRequest(RequestType r, int whichGroup = 0);
	void CleanUp();
	void ClearGraphData();
	void CompleteRequests();
	
	void ExecuteInitialCommand();
	void FillWithRandomData();
	void LoadDataStoragePointer();
	void LoadWetupGraphParameters();
	void OnStartNewDocument();
	void PauseAutomaticCommunication();
	void RequestLocations(int *locList, int nLoc);//uses lada IL index zero based location list, not cr10 actual IL values
	void ResetGetLocList();
	void ResumeAutomaticCommunication();
	void SaveDataStoragePointer();
	void SaveWetupGraphParameters();
	void SetLastFile(CString fileName);
	
	void ToggleData(int whichIndex, int whichButton);
	void UpdateGraphViews();
	void WriteInputLocations(CInputLocFileInfo * ptrInfo);


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
	
// Attributes
public:
	CMainFrame * m_ptrMainFrame;
	CTime GetCR10Time(BOOL ForceUpdate = FALSE, int UpdateInterval = 10);
	int GotData;
	void FlushAllRequests();
	int m_nTimeRequests;
	int nInGetInputLocations;
	BOOL DataError;
	HANDLE hDataRetrievalThread;
	CRITICAL_SECTION CommCriticalSection;
	HANDLE CommWakeUpEvent;
	int sleepingRequests;
	//int ThreadsServicing;
	//int ThreadsToBeServiced;

	int * InputLocationToIndex;
	//HANDLE ServicingData;
	//HANDLE ToBeServicedData;
	HANDLE DataCompletion;
	HANDLE DataRequest;
	BOOL m_AreCamerasLoaded;
	BOOL openDocumentFailed;
	void DeleteLastFile();
	CTime m_LastGraphUpdate;

	BOOL						DocInitialized;
	BOOL *						paneModified;
	BOOL *						m_DoValidation;
	BOOL *						m_HasMinMax;
	BOOL *						BackM_DoValidation;
	BOOL						ApplicationIsOpen;
	BOOL						D_CatchEndCommBlock;
	BOOL						DoAutoWrap;
	BOOL						InCommMode;
	BOOL						LoadBackGraphParameters;
	BOOL						m_DoWetup;
	BOOL						m_IsCommPaused;
	BOOL						m_IsCR10Initialized;
	BOOL						m_WetupInProgress;
	BOOL						m_LastCameraLoadFailed;
	BOOL						m_UseMilitaryTime;
	
	CBitmap *					AutomaticBMP;
	CBitmap *					ManualBMP;
	
	CBrush						backgroundBrush;
	
	CCameraData *				m_CameraData;
	
	CCommOperations *			commObject;
	
	CControlParameters *		m_ControlParameters;
	
	CFSInfo *					m_FSOutputTable;
	
	CGraphCollection *			BackGraphCollection;
	CGraphCollection *			GraphCollection;
	
	CHistoryClass *				m_ErrorFiles;
	CHistoryClass *				m_History;
	
	CInputLocFileInfo *			m_ILData;
	CInputLocFileInfo			m_FSCollectionParam;
	
	CLADAControlModuleView *	m_pMainView;
	
	CMainFrame *				m_FrameWnd;
	
	CManualControl	*			m_ptrManualDlg;
	
	COLORREF					backgroundBrushColor;
	
	ControlModeType				m_ControlMode;
	
	ControlStateType			m_ControlState;
	
	CPen						penThickBlack;
	CPen						penThinBlack;
	CPen						penThinGray;
	
	CR10ConnectionStatusType	ConnectionStatus;
	
	CString *					InputLocationUnits;
	CString *					m_ErrorNames;
	CString *					m_HistoryNames;
	CString						dataFolder;
	CString						LastCopyFolder;
	CString						m_FloppyDefault;
	CString						m_PcmciaDefault;
	CString						projectName;
	CString						projectOptionsFile;
	
	CTime *						PositionTime;
	CTime						CR10Time;
	CTime						CR10TimeUpdated;
	CTimeSpan					dataPlotFreq;
	
	CView *						pGraphButtonView[4];
	CView *						pGraphView[4];
	
	CViewHistoryDialog *		m_ptrErrorDlg;
	CViewHistoryDialog *		m_ptrHistoryDlg;
	
	CWetupInfo					m_WetupInfo;
	
	double *					GraphData;
	double *					newData; // uses zero based CR10 locations
	double *					tempArray;
	double *					m_maxValues;
	double *					m_minValues;
	
	InputListType *				BackInputLocationNameList;
	InputListType *				InputLocationNameList;
	
	int *						BackInputLocationList;
	int *						BackPaneToCollectionIndex;
	int *						m_GetLocationList;
	int *						m_GetLocationListIndex;
	int *						PaneToCollectionIndex;
	int *						InputLocationList;
	int							BackGraphCollections;
	int 						BacknInputLocations;
	int 						curWindow;
	int 						GraphDataBlockSize;
	int 						GraphDataPos;
	int 						m_CamerasEnabled;
	int 						m_Errors;
	int 						m_LastGroup;
	int 						m_nActiveRequests;
	int 						m_nGetLocList;
	int 						m_Reads;
	int 						maxGraphItems;
	int 						nBackPoints;
	int 						nCameras;
	int 						nFilledPoints;
	int 						nFSFiles;
	int 						nGraphCollections;
	int 						nGrowthChambers;
	int 						nHistoryFiles;
	int 						nILFiles;
	int 						nInputLocations;
	int 						nPanes;
	int 						ThreadsInCommBlock;
	int 						UpdateTimeRequests;

	List<CInputRequest>			GetLocationRequests;
	List<CInputRequest>			WriteLocationRequests;
	List<MSG>					TimerMessageQueue;
	
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
