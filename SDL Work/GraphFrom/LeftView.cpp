// LeftView.cpp : implementation of the CLeftView class
//

#include "stdafx.h"
#include "GraphForm.h"

#include "GraphFormDoc.h"
#include "LeftView.h"
#include "stdlib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CView)

BEGIN_MESSAGE_MAP(CLeftView, CView)
	//{{AFX_MSG_MAP(CLeftView)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	//ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	//ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	//ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLeftView construction/destruction

CLeftView::CLeftView() 
: backgroundBrush(RGB(200, 200, 255))

{
	// TODO: add construction code here
	penThickBlack.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	penThinBlack.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	penThinGray.CreatePen(PS_SOLID, 1, RGB(128, 128, 128));
	PixelLabelDistance = 40.0;
}

CLeftView::~CLeftView()
{
}

BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView drawing

CString ValueToString(double value, int dPlaces = 2){
	CString prefix = "";
	if (value < 0){
		prefix = "-";
		value *= -1;
	}
	for (int i = 0; i < dPlaces; i++) value *= 10;
	int nCopy = value;
	
	CString StringValue;
	int dPlace = 0;
	do {
		StringValue.Insert(0,char(nCopy % 10 + '0'));
		nCopy /= 10;
		dPlace++;
		if (dPlace == dPlaces)
			StringValue.Insert(0,'.');
		if (nCopy == 0 && dPlace <= dPlaces)
				StringValue.Insert(0,'0');
	} while (nCopy > 0);
	return prefix + StringValue;
}

void CLeftView::OnDraw(CDC* pDC)
{
	// TODO: add draw code for native data here
	// create and select a solid blue brush   
	CPen* pOldPen = pDC->SelectObject(&penThickBlack); 
	CBrush* pOldBrush = pDC->SelectObject(&backgroundBrush);
	
	CRect rect;   
	GetClientRect(rect);
      	
	bool IsDefinedMinMax = false;
	double minValue;
	double maxValue;

	// find min and max values
	for (int whichData = 0; whichData < nData; whichData++){
		if (pDoc->IsItemChecked[whichData]){
			if (!IsDefinedMinMax){
				minValue = maxValue = gData[whichData][*sPoint];
				IsDefinedMinMax = true;
			}
			for (int location = *sPoint; location < *sPoint + *nPoints; location++){
				if (gData[whichData][location] > maxValue)
					maxValue = gData[whichData][location];
				if (gData[whichData][location] < minValue)
					minValue = gData[whichData][location];
			}
		}
	}
	if (!IsDefinedMinMax){
		CString label = "No Data Items Are Selected";
		CSize labelSize = pDC->GetTextExtent(label);
		int labelLength = labelSize.cx;
		int labelHeigth = labelSize.cy;
		pDC->TextOut((rect.right - labelLength) / 2, (rect.bottom - labelHeigth) / 2, label);
		return;
	}

	rect.DeflateRect(60, 0, 0, 20);
	// draw a thick black rectangle filled with blue   
	pDC->Rectangle(rect);
	CSize rectSize = rect.Size();
	
	double Units = 5 * (maxValue - minValue) / 4;
	double UnitsPerPixel = Units / rect.Height();
	int BottomValue = minValue - Units / 10;
	int TopValue = maxValue + Units / 10;
	
	// start the labeling
	pDC->SelectObject(penThinGray);
	double PixelsPerPoint = double(rect.Width()) / *nPoints;
	if (PixelsPerPoint <= 0.0) 
		return; // it's too condensed to display anything
	int PixelLeftPos = rect.left;
	int PixelBottomPos = rect.bottom - 3;
	int PixelLabelPos = PixelBottomPos;
	double PixelLabelValue = BottomValue;
	do {
		pDC->MoveTo(rect.left, PixelLabelPos);
		pDC->LineTo(rect.right, PixelLabelPos);
		CString label = ValueToString(PixelLabelValue);
		CSize labelSize = pDC->GetTextExtent(label);
		int labelLength = labelSize.cx;
		int labelHeigth = labelSize.cy;
		pDC->TextOut(rect.left - 5 - labelLength, PixelLabelPos - labelHeigth / 2, label);
		PixelLabelPos -= PixelLabelDistance;
		PixelLabelValue = (PixelBottomPos - PixelLabelPos) * UnitsPerPixel + BottomValue;
	} while (PixelLabelValue < TopValue);

	PixelLabelPos = PixelLeftPos;
	double TimePerPoint = double(*EndTime - *StartTime) / *nPoints;

	PixelLabelValue = *StartTime; // this should be associated with time
	
	do {
		pDC->MoveTo(PixelLabelPos, rect.bottom);
		pDC->LineTo(PixelLabelPos, rect.top);
		CString label = ValueToString(PixelLabelValue);
		pDC->TextOut(PixelLabelPos, rect.bottom, label);
		PixelLabelPos += PixelLabelDistance * 3 / 2;
		PixelLabelValue = (PixelLabelPos - PixelLeftPos) * (TimePerPoint / PixelsPerPoint) + 35 /*StartTime*/;
	} while (PixelLabelValue < *EndTime);

	// plot the data
	for (int i = 0; i < nData; i++){
		if (pDoc->IsItemChecked[i]){
			pDC->SelectObject(pens[i]);
			int p = *sPoint;
			int ypos = PixelBottomPos - (gData[i][p] - BottomValue) / UnitsPerPixel;
			int xpos = (p - *sPoint) * PixelsPerPoint + PixelLeftPos;
			pDC->MoveTo(xpos,ypos);
			for (p = *sPoint + 1 ; p < *nPoints; p++){
				ypos = PixelBottomPos - (gData[i][p] - BottomValue) / UnitsPerPixel;
				xpos = (p - *sPoint) * PixelsPerPoint + PixelLeftPos;
				pDC->LineTo(xpos, ypos);
			}
		}
	}

   // put back the old objects   
   pDC->SelectObject(pOldBrush);
   pDC->SelectObject(pOldPen);

}


/////////////////////////////////////////////////////////////////////////////
// CLeftView printing
/*
BOOL CLeftView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLeftView::OnBeginPrinting(CDC*, CPrintInfo* )//pDC pInfo
{
	// TODO: add extra initialization before printing
}

void CLeftView::OnEndPrinting(CDC*, CPrintInfo* )//pDC pInfo
{
	// TODO: add cleanup after printing
}
*/
void CLeftView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	pDoc = (CGraphFormDoc*)GetDocument();
	ASSERT_VALID(pDoc);

	nData = pDoc->nDataItems;
	gData = pDoc->graphData;

	pens = new CPen[nData];
	colors = new COLORREF[15];
	colors[0] = RGB(255,0,0);
	colors[1] = RGB(0,255,0);
	colors[2] = RGB(0,0,255);
	colors[3] = RGB(255,255,0);
	colors[4] = RGB(255,0,255);
	colors[5] = RGB(0,255,255);
	colors[6] = RGB(128,0,0);
	colors[1] = RGB(0,128,0);
	colors[7] = RGB(0,0,128);
	colors[9] = RGB(128,255,0);
	colors[10] = RGB(128,0,255);
	colors[11] = RGB(0,128,255);
	colors[12] = RGB(255,128,0);
	colors[13] = RGB(255,0,128);
	colors[14] = RGB(0,255,128);

	for (int whichPen = 0; whichPen < nData; whichPen++)
		pens[whichPen].CreatePen(PS_SOLID, 1, colors[whichPen]);

	nPoints = new int(100);
	sPoint = new int(0);
	
	StartTime = new int(35);
	EndTime = new int(450);
	
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView diagnostics

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

/*
CGraphFormDoc* CLeftView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphFormDoc)));
	return (CGraphFormDoc*)m_pDocument;
}
*/
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLeftView message handlers

void CLeftView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CView::OnMouseMove(nFlags, point);
}
