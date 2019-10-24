// This is Version 1.0 PLEASE DOCUMENT CHANGES
// GraphButtonForm.cpp : implementation file
//

#include "stdafx.h"
#include "LADA Control Module.h"
#include "GraphButtonForm.h"

#include "LADA Control ModuleDoc.h"
#include "ColorCheckButton.h"
#include "GraphCollection.h"
#include "ReplaceGraphDlg.h"
#include "ChangeLocationDlg.h"
#include "GraphProperties.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CString ValueToString(double value, int dPlaces = 2, BOOL applyLanguage = FALSE);
extern int curLanguage;
extern CFont RussianArial;
extern COLORREF DefaultColor[15];

#define NUMBER_BOX_WIDTH	60
#define BOX_Y_OFFSET		30
/////////////////////////////////////////////////////////////////////////////
// CGraphButtonForm

IMPLEMENT_DYNCREATE(CGraphButtonForm, CFormView)

CGraphButtonForm::CGraphButtonForm()
	: CFormView(CGraphButtonForm::IDD)
{
	//{{AFX_DATA_INIT(CGraphButtonForm)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	bCtrl = NULL;
	numberBoxes = NULL;
	//formFont = NULL;
	numControls = 0;
	Initialized = FALSE;
}

CGraphButtonForm::~CGraphButtonForm()
{
	for (int i = 0; i < numControls; i++){
		delete bCtrl[i];
		delete numberBoxes[i];
	}
	delete [] bCtrl;
	delete [] numberBoxes;
	//delete formFont;
}


void CGraphButtonForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGraphButtonForm)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

#define LAST_NUMBER_BOX		IDC_FIRSTNUMBERBOX + 3 * 15
BEGIN_MESSAGE_MAP(CGraphButtonForm, CFormView)
	//{{AFX_MSG_MAP(CGraphButtonForm)
	ON_BN_CLICKED(IDC_GRAPH_NAME, OnGraphName)
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(IDC_FIRSTNUMBERBOX, LAST_NUMBER_BOX, OnClickNumberBox)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphButtonForm diagnostics

#ifdef _DEBUG
void CGraphButtonForm::AssertValid() const
{
	CFormView::AssertValid();
}

void CGraphButtonForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGraphButtonForm message handlers

void CGraphButtonForm::OnInitialUpdate() 
{

	// TODO: Add your specialized code here and/or call the base class
	if (Initialized){
		for (int i = 0; i < numControls; i++){
			delete bCtrl[i];
			delete numberBoxes[i];
		}
		delete [] bCtrl;
		delete [] numberBoxes;
	}
	
	//formFont = new CFont;
	//formFont->CreateFont(16,0,0,0,FW_NORMAL,0,0,0,RUSSIAN_CHARSET,
	//	                     0,0,0,0,"Times New Roman");
	Initialized = TRUE;
	pDoc = (CLADAControlModuleDoc *) GetDocument();	
	pDoc->curWindow++;
	whichWindow = pDoc->curWindow;
	pDoc->pGraphButtonView[whichWindow] = this;

	numControls = pDoc->maxGraphItems;
	bCtrl = new CColorCheckButton *[numControls];
	numberBoxes = new CStatic *[numControls];
	BOOL vis = (pDoc->PaneToCollectionIndex[whichWindow] != -1);
	
	CString title = (vis ? pDoc->GraphCollection[pDoc->PaneToCollectionIndex[whichWindow]].name : "");
	GetDlgItem(IDC_GRAPH_NAME)->SetWindowText(title);

	for (int i = 0; i < numControls ; i++){
		
		if (vis)
			vis &= (i < pDoc->GraphCollection[pDoc->PaneToCollectionIndex[whichWindow]].nItems);
		
		numberBoxes[i] = new CStatic;

		numberBoxes[i]->Create("0.00",(vis?WS_VISIBLE:0)|WS_CHILD|WS_BORDER|SS_NOTIFY|SS_CENTER|SS_CENTERIMAGE, 
			// using center image causes the text to be centered vertically
			CRect(10,BOX_Y_OFFSET+i * 25,10 + NUMBER_BOX_WIDTH,BOX_Y_OFFSET+17+i*25),this,IDC_FIRSTNUMBERBOX+i+whichWindow * 15);
		
		numberBoxes[i]->SetFont(&RussianArial);
		bCtrl[i] = new CColorCheckButton;
		if (pDoc->PaneToCollectionIndex[whichWindow] != -1 && vis)
		{
			bCtrl[i]->CreateButton(WS_VISIBLE,pDoc->GetDataName(whichWindow,i),
				CRect(15 + NUMBER_BOX_WIDTH,BOX_Y_OFFSET-4+i * 25,265 + NUMBER_BOX_WIDTH,BOX_Y_OFFSET+21+i*25),this,
				IDC_FIRST_CHECKBOX+i+whichWindow * 15,DefaultColor[i],
				pDoc->GraphCollection[pDoc->PaneToCollectionIndex[whichWindow]].isItemChecked[i],&RussianArial);
		}
		else
		{
			bCtrl[i]->CreateButton(0,"??",
				CRect(15 + NUMBER_BOX_WIDTH,BOX_Y_OFFSET-4+i * 25,265 + NUMBER_BOX_WIDTH,BOX_Y_OFFSET+21+i*25),this,
				IDC_FIRST_CHECKBOX+i+whichWindow * 15,DefaultColor[i],FALSE,&RussianArial);
		}
	}

	CFormView::OnInitialUpdate();
}


void CGraphButtonForm::ClickCheckBox(UINT nID){

	int whichButton = (nID - IDC_FIRST_CHECKBOX) % 15;
	
	//CLADAControlModuleDoc * pDoc = (CLADAControlModuleDoc*)GetDocument();
	if (pDoc->PaneToCollectionIndex[whichWindow] != -1)
	{
		pDoc->ToggleData(pDoc->PaneToCollectionIndex[whichWindow], whichButton);
		pDoc->UpdateAllViews(this);
	}
}


void CGraphButtonForm::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	//CLADAControlModuleDoc * pDoc = (CLADAControlModuleDoc*)GetDocument();
	
	if (pDoc->paneModified[whichWindow] && pDoc->PaneToCollectionIndex[whichWindow] != -1) // is there as is modified
	{
		
		CGraphCollection * ptrGraph = &pDoc->GraphCollection[pDoc->PaneToCollectionIndex[whichWindow]];
		GetDlgItem(IDC_GRAPH_NAME)->SetWindowText(ptrGraph->name);
		
		for (int i = 0; i < numControls; i++){
			if (i < ptrGraph->nItems){	
				numberBoxes[i]->ShowWindow(SW_SHOW);
				numberBoxes[i]->SetWindowText(ValueToString(pDoc->newData[ptrGraph->DataIndex[i]])); //pDoc->DataIndex[whichWindow][i]
				bCtrl[i]->ShowWindow(SW_SHOW);	
				bCtrl[i]->SetWindowText(pDoc->InputLocationNameList[ptrGraph->DataIndex[i]][curLanguage]);
				bCtrl[i]->SetCheck(ptrGraph->isItemChecked[i]);
			}
			else
			{
				numberBoxes[i]->ShowWindow(SW_HIDE);
				bCtrl[i]->ShowWindow(SW_HIDE);
			}
		}
		pDoc->paneModified[whichWindow] = FALSE;
		Invalidate();
	}
	else if (pDoc->PaneToCollectionIndex[whichWindow] != -1) // is there and not modified
	{
		for (int i = 0; i < numControls; i++)
		{
			if (i < pDoc->GraphCollection[whichWindow].nItems)	
				numberBoxes[i]->SetWindowText(ValueToString(pDoc->newData[pDoc->GraphCollection[pDoc->PaneToCollectionIndex[whichWindow]].DataIndex[i]]));
		}
	}
	else if (pDoc->paneModified[whichWindow]) // modified and is not there
	{
		GetDlgItem(IDC_GRAPH_NAME)->SetWindowText("");
		for (int i = 0; i < numControls; i++)
		{
			numberBoxes[i]->ShowWindow(SW_HIDE);
			bCtrl[i]->ShowWindow(SW_HIDE);
			
		}
	}
	
}

/*
HBRUSH CGraphButtonForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	//HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	
	// TODO: Return a different brush if the default is not desired
	CLADAControlModuleDoc * pDoc = (CLADAControlModuleDoc*)GetDocument();
	int whichButton = (nCtlColor - IDC_FIRST_CHECKBOX) % 15;
	LOGPEN penStruct;
	pDoc->pens[whichButton].GetLogPen(&penStruct);
	brush.CreateSolidBrush(penStruct.lopnColor);
	return (HBRUSH)brush.Detach();
	//return hbr;
}
*/

void CGraphButtonForm::OnGraphName() 
{
	// TODO: Add your control notification handler code here
	if (pDoc->nGraphCollections == 0)
	{
		CGraphProperties gDialog(pDoc);
		gDialog.DoModal();
		pDoc->UpdateAllViews(NULL);
		return;
	}

	CReplaceGraphDlg gDlg(pDoc);
	if (gDlg.DoModal() == IDOK)
	{
		if (pDoc->GraphCollection[gDlg.m_wGraph].whichPane != -1)
		{
			pDoc->PaneToCollectionIndex[pDoc->GraphCollection[gDlg.m_wGraph].whichPane] = -1;
			pDoc->paneModified[pDoc->GraphCollection[gDlg.m_wGraph].whichPane] = TRUE;	
			pDoc->GraphCollection[gDlg.m_wGraph].whichPane = -1;
		}

		int gInWindow = pDoc->PaneToCollectionIndex[whichWindow];
		if (gInWindow != -1)
		{
			pDoc->GraphCollection[gInWindow].whichPane = -1;
			for (int i = 0; i < pDoc->nPanes; i++)
			{
				if (i != whichWindow && pDoc->PaneToCollectionIndex[i] == -1)
				{
					pDoc->GraphCollection[gInWindow].whichPane = i;
					pDoc->PaneToCollectionIndex[i] = gInWindow;
					pDoc->paneModified[i] = TRUE;	
					break;
				}
			}
		}
		
		pDoc->GraphCollection[gDlg.m_wGraph].whichPane = whichWindow;
		pDoc->PaneToCollectionIndex[whichWindow] = gDlg.m_wGraph;
		pDoc->paneModified[whichWindow] = TRUE;	
		pDoc->UpdateGraphViews();
	}
}

void CGraphButtonForm::OnClickNumberBox(UINT nID)
{
	int whichButton = (nID - IDC_FIRSTNUMBERBOX) % 15;

	if (pDoc->GraphCollection[whichWindow].whichPane != -1)
	{
		CChangeLocationDlg cDlg(pDoc, pDoc->GraphCollection[pDoc->PaneToCollectionIndex[whichWindow]].DataIndex[whichButton]+1);
		cDlg.DoModal();	 
	}
}
