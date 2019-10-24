// GraphDisplayView.cpp : implementation file
//

#include "stdafx.h"
#include "LADA Control Module.h"
#include "GraphDisplayView.h"

#include "LADA Control ModuleDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CFont RussianArial;
extern int curLanguage;
extern void  SetFontText(UINT controlID, UINT stringID, CWnd *window);

/////////////////////////////////////////////////////////////////////////////
// CGraphDisplayView

IMPLEMENT_DYNCREATE(CGraphDisplayView, CView)

CGraphDisplayView::CGraphDisplayView()
{
	PixelLabelDistanceY = 40;
	PixelLabelDistanceX	= PixelLabelDistanceY * 3 / 2;
}

CGraphDisplayView::~CGraphDisplayView()
{
	
}


BEGIN_MESSAGE_MAP(CGraphDisplayView, CView)
	//{{AFX_MSG_MAP(CGraphDisplayView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphDisplayView drawing


CString ValueToString(double value, int dPlaces = 2){
	CString prefix = "";
	if (value < 0){
		prefix = "-";
		value *= -1;
	}
	for (int i = 0; i < dPlaces; i++) value *= 10;
	int nCopy = (int)value;
	if (nCopy == 0)
		prefix = "";

	CString StringValue;
	int dPlace = 0;
	do 
	{
		StringValue.Insert(0,char(nCopy % 10 + '0'));
		nCopy /= 10;
		dPlace++;
		if (dPlace == dPlaces){
			if (curLanguage == ENGLISH)
				StringValue.Insert(0,'.');
			else
				StringValue.Insert(0,',');
			if (nCopy == 0)
				StringValue.Insert(0,'0');
		}
	} 
	while (nCopy > 0 || dPlace < dPlaces);//while (nCopy > 0);
	
	return prefix + StringValue;
}


void CGraphDisplayView::OnDraw(CDC* ptrDC)
{
	// TODO: add draw code here
	
	pDoc = (CLADAControlModuleDoc*) GetDocument();
	pDC = ptrDC;
	pDC->SelectObject(&RussianArial);

	GetClientRect(rect);
	if (pDoc->nFilledPoints < 2){
		CString label;
		label.LoadString(IDS_NOT_ENOUGH_DATA);
		CSize labelSize = pDC->GetTextExtent(label);
		int labelLength = labelSize.cx;
		int labelHeigth = labelSize.cy;
		pDC->TextOut((rect.right - labelLength) / 2, (rect.bottom - labelHeigth) / 2, label);
		//MessageBox("Click to continue");
		
		labelSize = pDC->GetTextExtent("88:88:88");
		PixelLabelDistanceX = labelSize.cx + 5;
		return;
	}

	if (!pDoc->DoAutoWrap || pDoc->nFilledPoints < nBackPoints){
		firstPoint = 0;
		lastPoint = pDoc->GraphDataPos - 1;
		if (pDoc->GraphDataPos == 1)
			Hint = 0;
	}
	else
	{
		firstPoint = pDoc->GraphDataPos;
		lastPoint = (pDoc->GraphDataPos + pDoc->nFilledPoints - 1) % pDoc->nFilledPoints;
	}


	// create and select a solid blue brush   
	CPen* pOldPen = pDC->SelectObject(&pDoc->penThickBlack); 
	CBrush* pOldBrush = pDC->SelectObject(&pDoc->backgroundBrush);
	
	GetMinMax();
	
	if (!IsDefinedMinMax){
		CString label;
		label.LoadString(IDS_NO_ITEMS_SELECTED);
		CSize labelSize = pDC->GetTextExtent(label);
		int labelLength = labelSize.cx;
		int labelHeigth = labelSize.cy;
		pDC->TextOut((rect.right - labelLength) / 2, (rect.bottom - labelHeigth) / 2, label);
		//MessageBox("Click to continue");
		return;
	}

	if (Hint != 1 || pDoc->DoAutoWrap )
		DrawGraphForm();
	
	PlotDataPoints();

	//MessageBox("Click to continue");
   // put back the old objects   
   pDC->SelectObject(pOldBrush);
   pDC->SelectObject(pOldPen);
   Hint = 0;
}

void CGraphDisplayView::GetMinMax(){
	IsDefinedMinMax = false;
	// find min and max values
	nDataPoints = (lastPoint - firstPoint + nBackPoints) % nBackPoints;
	int pos = 0;
	double value = 0.0;
	for (int whichData = 0; whichData < pDoc->maxGraphItems; whichData++){
		if (pDoc->IsItemChecked(whichWindow,whichData)){
			if (!IsDefinedMinMax){
				minValue = maxValue = pDoc->GetDataValue(whichWindow, whichData,firstPoint);
				IsDefinedMinMax = true;
			}
			for (int location = firstPoint; location <= nDataPoints; location++){
				pos = location % nBackPoints;
				value = pDoc->GetDataValue(whichWindow, whichData,pos);
				if (value > maxValue)
					maxValue = value;
				else if (value < minValue)
					minValue = value;
			}
		}
	}
	if (maxValue - minValue < 0.1 && pDoc->nFilledPoints < 10 ||
		maxValue - minValue == 0.0)
		maxValue += 1.0;
}

void CGraphDisplayView::PlaceVertLabel(int PixelLabelPos)
{
	pDC->MoveTo(rect.left, PixelLabelPos);
	pDC->LineTo(rect.right, PixelLabelPos);
	double PixelLabelValue = (PixelBottomPos - PixelLabelPos) * UnitsPerPixel + BottomValue;
	CString label = ValueToString(PixelLabelValue);
	CSize labelSize = pDC->GetTextExtent(label);
	int labelLength = labelSize.cx;
	int labelHeigth = labelSize.cy;
	pDC->TextOut(rect.left - 5 - labelLength, PixelLabelPos - labelHeigth / 2, label);
}

void CGraphDisplayView::PlaceHoroLabel(int PixelLabelPos)
{
	pDC->MoveTo(PixelLabelPos, rect.bottom);
	pDC->LineTo(PixelLabelPos, rect.top);
	int PixelLabelValue = int((PixelLabelPos - PixelLeftPos) / PixelsPerPoint + firstPoint) % nBackPoints;
	if (PixelLabelValue < lastPoint ){
		CString label = pDoc->GetPositionLabel(PixelLabelValue);
		if (label[0] == '0')
			label = label.Mid(1);
		pDC->TextOut(PixelLabelPos, rect.bottom, label);
	}
}

void CGraphDisplayView::DrawGraphForm(){
	rect.DeflateRect(60, 0, 0, 20);
	// draw a thick black rectangle filled with blue   
	pDC->Rectangle(rect);
	// start the labeling
	pDC->SelectObject(pDoc->penThinGray);

	CSize rectSize = rect.Size();
	
	double Units = 5 * (maxValue - minValue) / 4;
	UnitsPerPixel = Units / rect.Height();
	BottomValue = minValue - Units / 10;
	double TopValue = maxValue + Units / 10;
	PixelsPerPoint = double(rect.Width()) / nBackPoints;
	if (PixelsPerPoint <= 0.0) 
		return; // it's too condensed to display anything
	PixelLeftPos = rect.left;
	PixelBottomPos = rect.bottom - 3;
	
	int PixelLabelPos = PixelBottomPos - int((Units / 10) / UnitsPerPixel); 
	
	if (PixelBottomPos - PixelLabelPos > 20){
		PlaceVertLabel(PixelLabelPos);
		PlaceVertLabel(PixelBottomPos);
	}
	else
		PlaceVertLabel(PixelLabelPos);

	int PDistance = rect.Height() / int(rect.Height() / PixelLabelDistanceY);

	int MaxLabelPos = rect.top - 3 + int((Units / 10) / UnitsPerPixel); 

	PixelLabelPos -= PDistance;
	while (PixelLabelPos - MaxLabelPos > 20){
		PlaceVertLabel(PixelLabelPos);	
		PixelLabelPos -= PDistance;
	}
	PlaceVertLabel(MaxLabelPos);


	PixelLabelPos = PixelLeftPos;
	
	do {
		PlaceHoroLabel(PixelLabelPos);
		PixelLabelPos += PixelLabelDistanceX;
	} while (PixelLabelPos < rect.right);
}

void CGraphDisplayView::PlotDataPoints(){

// plot the data
	for (int i = 0; i < pDoc->maxGraphItems; i++){
		if (pDoc->IsItemChecked(whichWindow,i)){
			pDC->SelectObject(pDoc->pens[i]);
			int p = firstPoint; 
			int ypos = PixelBottomPos - int((pDoc->GetDataValue(whichWindow, i,p) - BottomValue) / UnitsPerPixel);
			int xpos = PixelLeftPos;
			pDC->MoveTo(xpos,ypos);
			p++;
			for (int c = 0; c < nDataPoints; c++){
				if (p >= nBackPoints) 
					p -= nBackPoints;
				ypos = PixelBottomPos - int((pDoc->GetDataValue(whichWindow, i,p) - BottomValue) / UnitsPerPixel);
				xpos = int((c+1) * PixelsPerPoint) + PixelLeftPos;
				pDC->LineTo(xpos, ypos);
				p++;
			}
		}
	}


}

/////////////////////////////////////////////////////////////////////////////
// CGraphDisplayView diagnostics

#ifdef _DEBUG
void CGraphDisplayView::AssertValid() const
{
	CView::AssertValid();
}

void CGraphDisplayView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGraphDisplayView message handlers

void CGraphDisplayView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	// TODO: Add your specialized code here and/or call the base class
	pDoc = (CLADAControlModuleDoc *) GetDocument();
	nData = pDoc->nData;
	whichWindow = pDoc->curWindow;
	nBackPoints = pDoc->nBackPoints;
	pDoc->pGraphView[whichWindow] = this;
}



void CGraphDisplayView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	Hint = lHint;
	if (lHint == 1)
	{
		
		//Invalidate(FALSE);
		Hint = 0;
		Invalidate();
	}
	else
	{
		Invalidate();
	}
}
