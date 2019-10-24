// GraphButtonForm.cpp : implementation file
//

#include "stdafx.h"
#include "LADA Control Module.h"
#include "GraphButtonForm.h"

#include "LADA Control ModuleDoc.h"
#include "ColorCheckButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CString ValueToString(double value, int dPlaces = 2);
extern int curLanguage;
extern CFont smallRussianArial;
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


BEGIN_MESSAGE_MAP(CGraphButtonForm, CFormView)
	//{{AFX_MSG_MAP(CGraphButtonForm)
	//}}AFX_MSG_MAP
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
	CLADAControlModuleDoc * pDoc = (CLADAControlModuleDoc *) GetDocument();	
	pDoc->curWindow++;
	whichWindow = pDoc->curWindow;
	
	numControls = pDoc->maxGraphItems;
	bCtrl = new CColorCheckButton *[numControls];
	numberBoxes = new CStatic *[numControls];
	
	for (int i = 0; i < numControls ; i++){
		numberBoxes[i] = new CStatic;
		numberBoxes[i]->Create("0.00",WS_CHILD|WS_BORDER|SS_CENTER,
			CRect(10,14+i * 22,48,31+i*22),this,IDC_FIRSTNUMBERBOX+i+whichWindow * 15);
		numberBoxes[i]->SetFont(&smallRussianArial);
		bCtrl[i] = new CColorCheckButton;
		bCtrl[i]->CreateButton(pDoc->GetDataName(whichWindow,i),
			CRect(50,10+i * 22,300,35+i*22),this,
			IDC_FIRST_CHECKBOX+i+whichWindow * 15,pDoc->colors[i],
			pDoc->ItemChecked[whichWindow][i],&smallRussianArial);
		//bCtrl[i]->SetFont(formFont);
	}

	CFormView::OnInitialUpdate();
}


void CGraphButtonForm::ClickCheckBox(UINT nID){

	int whichButton = (nID - IDC_FIRST_CHECKBOX) % 15;
	
	CLADAControlModuleDoc * pDoc = (CLADAControlModuleDoc*)GetDocument();
	pDoc->ToggleData(whichWindow, whichButton);
	pDoc->UpdateAllViews(this);
}

void CGraphButtonForm::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	CLADAControlModuleDoc * pDoc = (CLADAControlModuleDoc*)GetDocument();
	
	if (pDoc->graphListModified[whichWindow]){
		for (int i = 0; i < numControls; i++){
			if (i < pDoc->nDataGraph[whichWindow]){	
				numberBoxes[i]->ShowWindow(SW_SHOW);
				numberBoxes[i]->SetWindowText(ValueToString(pDoc->newData[pDoc->DataIndex[whichWindow][i]]));
				bCtrl[i]->ShowWindow(SW_SHOW);
				bCtrl[i]->SetWindowText(pDoc->InputLocationNameList[pDoc->DataIndex[whichWindow][i]][curLanguage]);
				bCtrl[i]->SetCheck(pDoc->ItemChecked[whichWindow][i]);
			}
			else
			{
				numberBoxes[i]->ShowWindow(SW_HIDE);
				bCtrl[i]->ShowWindow(SW_HIDE);
			}
		}
		pDoc->graphListModified[whichWindow] = FALSE;
	}
	else
	{
		for (int i = 0; i < numControls; i++){
			if (i < pDoc->nDataGraph[whichWindow])	
				numberBoxes[i]->SetWindowText(ValueToString(pDoc->newData[pDoc->DataIndex[whichWindow][i]]));
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
