// GraphFormView.cpp : implementation of the CGraphFormView class
//

#include "stdafx.h"
#include "GraphForm.h"

#include "GraphFormDoc.h"
#include "GraphFormView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphFormView

IMPLEMENT_DYNCREATE(CGraphFormView, CFormView)

BEGIN_MESSAGE_MAP(CGraphFormView, CFormView)
	//{{AFX_MSG_MAP(CGraphFormView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
	ON_COMMAND_RANGE(IDC_FIRST_CHECKBOX,IDC_LAST_CHECKBOX, OnClickCheckBox)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphFormView construction/destruction

CGraphFormView::CGraphFormView()
	: CFormView(CGraphFormView::IDD)
{
	//{{AFX_DATA_INIT(CGraphFormView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CGraphFormView::~CGraphFormView()
{
}

void CGraphFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGraphFormView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BOOL CGraphFormView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CGraphFormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	
	CButton *bCtrl;
	for (int i = 0; i < 10; i++){
		bCtrl = new CButton;
		bCtrl->Create("Button Control",BS_AUTOCHECKBOX | WS_VISIBLE, CRect(10,10+i * 20,100,20+i*20),this,IDC_FIRST_CHECKBOX+i);
	}
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}

/////////////////////////////////////////////////////////////////////////////
// CGraphFormView message-handling routines

void CGraphFormView::OnClickCheckBox(UINT nID){

	int whichButton = nID - IDC_FIRST_CHECKBOX;
	CGraphFormDoc* pDoc = (CGraphFormDoc*)GetDocument();
	pDoc->IsItemChecked[whichButton] = pDoc->IsItemChecked[whichButton] ? FALSE : TRUE;
	pDoc->UpdateAllViews(this);
}

/////////////////////////////////////////////////////////////////////////////
// CGraphFormView printing

BOOL CGraphFormView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGraphFormView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGraphFormView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CGraphFormView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CGraphFormView diagnostics

#ifdef _DEBUG
void CGraphFormView::AssertValid() const
{
	CFormView::AssertValid();
}

void CGraphFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CGraphFormDoc* CGraphFormView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphFormDoc)));
	return (CGraphFormDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGraphFormView message handlers
