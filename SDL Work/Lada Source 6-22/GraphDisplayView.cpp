// This is Version 1.0 PLEASE DOCUMENT CHANGES
// 1-11-01 1:00pm added bounds to ValueToString
// GraphDisplayView.cpp : implementation file
//


#include "stdafx.h"
#include "LADA Control Module.h"
#include "GraphDisplayView.h"

#include "LADA Control ModuleDoc.h"
#include "LString.h"
#include "Ladastrings.h"
#include <math.h>
#include "GraphCollection.h"
#include "Historyclass.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern LString Strings;
extern CFont LargeRussianArial;
extern int curLanguage;
extern CPen Pen[15];

extern int round(double &value);

bool IsValid(double value)
{
	return (value >= -100000.0 && value <= 100000.0 && round(value) != -99999 && round(value) != 99999);
}

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
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipNotify)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphDisplayView drawing
double StringToValue(const char *ptrString)
{
	double returnValue = 0.0;

	int l = strlen(ptrString);

	for (int bPos = 0; bPos < l && 
		ptrString[bPos] != '+' && 
		ptrString[bPos] != '-' && 
		(ptrString[bPos] < '0' || ptrString[bPos] > '9'); bPos++);
				
	double sign;
	if (ptrString[bPos] == '-')
		sign = -1;
	else
		sign = 1;

	int iPart = 0;
	bool period = false;
	double DecValue = 1.0;

	for (;bPos < l && ((ptrString[bPos] >= '0' && ptrString[bPos] <= '9') || ptrString[bPos] == '.' || ptrString[bPos] == '+' || ptrString[bPos] == '-'); bPos++)
	{
		if (ptrString[bPos] == '.')
		{
			period = true;
		}
		else if (ptrString[bPos] >= '0' && ptrString[bPos] <= '9')
		{
			if (!period){
				iPart *= 10;
				iPart += (ptrString[bPos] - '0');
			}
			else
			{
				DecValue /= 10;
				returnValue += (double(ptrString[bPos] - '0') * DecValue);
			}
		}
	}
	returnValue += double(iPart);
	returnValue *= sign;	
	return returnValue;
}

CString ValueToString(double value, int dPlaces = 2, BOOL applyLanguage = FALSE)
{
	if (fabs(value + 99999.00) < 0.001)
		return "Error";
	if 	(value> 100000 || value < -100000)
		return "Invalid";
	CString prefix = "";
	if (value < 0){
		prefix = "-";
		value *= -1;
	}
	for (int i = 0; i < dPlaces; i++) value *= 10;
	if ((value-(int)value)>=.5)
		value+=1;
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
			
			if (curLanguage == ENGLISH || !applyLanguage)
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

int StringToInt(CString String, int Length = 0)
{
	int value = 0;
	if (Length == 0)
		Length = String.GetLength();
	for (int i = 0; i < Length && String[i] != '.'; i++)
	{
		value *= 10;
		value += String[i] - '0';
	}
	return value;
}

int StringToInt(const char * String, int Length = 0)
{
	int value = 0;
	if (Length == 0)
		Length = strlen(String);
	for (unsigned int i = 0; i < (unsigned int)Length && String[i] != '.'; i++)
	{
		value *= 10;
		value += String[i] - '0';
	}
	return value;	
}

CString IntToString(int number)
{
	char text[25];
	wsprintf(text,"%i",number);
	return CString(text);
}


void CGraphDisplayView::OnDraw(CDC* ptrDC)
{
	// TODO: add draw code here
	IsDefinedMinMax = false;
	if ((whichGraph = pDoc->PaneToCollectionIndex[whichWindow]) == -1)
	{
		// this means that OnDraw has been called for a window which has 
		// no CGraphCollection associated.
		// this is not bad... if we have just taken a graph out of this window
		// it will cause the window to be blanked out.
		return;
	}
	
	pDC = ptrDC;
	CFont *ptrOldFont = pDC->SelectObject(&LargeRussianArial);

	GetClientRect(rect);
	if (pDoc->nFilledPoints < 1)
	{
		pDC->ExtTextOut(10,10,0,&rect,Strings.get(IDS_NOT_ENOUGH_DATA),NULL);
		CSize labelSize = pDC->GetTextExtent("88:88:88");
		PixelLabelDistanceX = labelSize.cx + 5;
		return;
	}

	// determine start and end data points to graph
	if (!pDoc->DoAutoWrap || pDoc->nFilledPoints < nBackPoints)
	{
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

	GetMinMax();
		
	if (!IsDefinedMinMax)
	{
		if (m_IsDataSelected)
		{
			// all the data selected is invalid
			pDC->ExtTextOut(10,10,0,&rect,Strings.get(IDS_NO_VALID_DATA),NULL);
			pDC->SelectObject(ptrOldFont);
			return;
		}
		else
		{
			pDC->ExtTextOut(10,10,0,&rect,Strings.get(IDS_NO_ITEMS_SELECTED),NULL);
			pDC->SelectObject(ptrOldFont);
			return;
		}
	}

	//CPen* pOldPen = pDC->SelectObject(&pDoc->penThickBlack); 
	CBrush* pOldBrush = pDC->SelectObject(&pDoc->backgroundBrush);	
	
	if (DrawGraphForm())
		PlotDataPoints();

	//const MSG * curMessage = this->GetCurrentMessage();
	
	//OnMouseMove(NULL, curMessage->pt);
	//MessageBox("Click to continue");
	// put back the old objects   
	
	pDC->SelectObject(pOldBrush);
	//pDC->SelectObject(pOldPen);
	pDC->SelectObject(ptrOldFont);
	Hint = 0;
}

void CGraphDisplayView::GetMinMax(){
	
	// find min and max values
	nDataPoints = (lastPoint - firstPoint + nBackPoints) % nBackPoints;
	int pos = 0;
	double value = 0.0;
	m_IsDataSelected = false;
	for (int whichData = 0; whichData < pDoc->GraphCollection[whichGraph].nItems; whichData++)
	{
		if (pDoc->IsItemChecked(whichGraph,whichData))
		{
			m_IsDataSelected = true;
			if (!IsDefinedMinMax)
			{
				minValue = 10000.0;
				maxValue = -10000.0;
			}
			
			int location = firstPoint; 
			for (int c = 0; c <= nDataPoints; c++)
			{
				if (location >= nBackPoints) 
					location -= nBackPoints;
				value = pDoc->GetDataValue(whichGraph, whichData, location);
				if (IsValid(value))
				{
					IsDefinedMinMax = true;
					if (value > maxValue)
						maxValue = value;
					if (value < minValue)
						minValue = value;
				}
				location++;
			}
		}
	}
	if (maxValue - minValue < 0.1 && pDoc->nFilledPoints < 10 ||
		maxValue - minValue == 0.0)
		maxValue += 1.0;
}

void CGraphDisplayView::PlaceVertLabel(int PixelLabelPos, BOOL draw, int &maxLength)
{
	double PixelLabelValue = (PixelBottomPos - PixelLabelPos) * UnitsPerPixel + BottomValue;
	CString label = ValueToString(PixelLabelValue);
	CSize labelSize = pDC->GetTextExtent(label);
	
	if (labelSize.cx > maxLength)
		maxLength = labelSize.cx;
	if (!draw)
		return;

	pDC->MoveTo(rect.left, PixelLabelPos);
	pDC->LineTo(rect.right, PixelLabelPos);
	pDC->TextOut(rect.left - labelSize.cx - 5, PixelLabelPos - labelSize.cy / 2, label);
	return;
}

void CGraphDisplayView::PlaceHoroLabel(int PixelLabelPos)
{
	pDC->MoveTo(PixelLabelPos, rect.bottom);
	pDC->LineTo(PixelLabelPos, rect.top);
	int PixelLabelValue = int((PixelLabelPos - PixelLeftPos) / PixelsPerPoint + firstPoint) % nBackPoints;
	//if (pDoc->IsPositionLabel(PixelLabelValue)){
	if (PixelLabelValue < nDataPoints)
	{
		CString label = pDoc->GetPositionLabel(PixelLabelValue);
		if (label[0] == '0')
			label = label.Mid(1);
		pDC->TextOut(PixelLabelPos, rect.bottom, label);
	}
}

int CGraphDisplayView::CreateValueLabels(BOOL drawLabels)
{
	double Units = 5 * (maxValue - minValue) / 4;
	// rect, minvalue, maxvalue, CDC
	int maxlength = 0;

	// pixel label pos refers to the position of the first label, vertically
	int PixelLabelPos = PixelBottomPos - int((Units / 10) / UnitsPerPixel); 
	
	// place the bottom two labels, if there is enough room place both
	if (PixelBottomPos - PixelLabelPos > 20){
		PlaceVertLabel(PixelLabelPos, drawLabels, maxlength);
		PlaceVertLabel(PixelBottomPos, drawLabels, maxlength);
	}
	else
	{
		PlaceVertLabel(PixelLabelPos, drawLabels, maxlength);
	}

	double d = 0;
	int PDistance = 0;
	if (PixelLabelDistanceY > 0)
		d = double(rect.Height()) / double(PixelLabelDistanceY);
	if (d > 0)
		PDistance = int(rect.Height() / d);

	int MaxLabelPos = rect.top - 3 + int((Units / 10) / UnitsPerPixel); 
	
	if (PDistance > 10)
	{
		PixelLabelPos -= PDistance;
		while (PixelLabelPos - MaxLabelPos > 20){
			PlaceVertLabel(PixelLabelPos, drawLabels, maxlength);	
			PixelLabelPos -= PDistance;
		}
	}
	PlaceVertLabel(MaxLabelPos, drawLabels, maxlength);

	return maxlength;
}

BOOL CGraphDisplayView::DrawGraphForm()
{
	double Units = 5 * (maxValue - minValue) / 4;
	UnitsPerPixel = Units / (rect.Height() - 20);
	BottomValue = minValue - Units / 10;
	double TopValue = maxValue + Units / 10;

	// place value labels, vertically
	// start the labeling
	void * ptrOldPen = pDC->SelectObject(pDoc->penThinGray);

	rect.DeflateRect(0, 0, 0, 20); // pull the bottom up
	PixelBottomPos = rect.bottom - 3;
	
	int labelLength = CreateValueLabels(FALSE) + 10;
	rect.DeflateRect(labelLength, 0, 0, 0); // push the left side over
	
	CSize rectSize = rect.Size();
	
	PixelsPerPoint = double(rect.Width()) / nBackPoints;
	if (PixelsPerPoint <= 0.0) 
		return FALSE; // it's too condensed to display anything

	PixelLeftPos = rect.left;
	// draw a thick rectangle filled with graph color   
	pDC->Rectangle(rect);
	CreateValueLabels(TRUE);
	
	int PixelLabelPos = PixelLeftPos;
	
	do 
	{
		PlaceHoroLabel(PixelLabelPos);
		PixelLabelPos += PixelLabelDistanceX;
	} 
	while (PixelLabelPos < rect.right);

	pDC->SelectObject(ptrOldPen);
	return TRUE;
}

void CGraphDisplayView::PlotData(int whichGraphItem)
{
	double dataValue;
	int ypos;
	int xpos;
	bool wasLastPointValid;

	void * ptrOldPen = pDC->SelectObject(Pen[whichGraphItem]);
	int p = firstPoint;
			
	dataValue = pDoc->GetDataValue(whichGraph, whichGraphItem, p);
	if (IsValid(dataValue))
	{
		wasLastPointValid = true;
		ypos = PixelBottomPos - int((dataValue - BottomValue) / UnitsPerPixel);
		xpos = PixelLeftPos;
		pDC->MoveTo(xpos,ypos);
		if (pDoc->nFilledPoints == 1)
			pDC->LineTo(xpos+1,ypos);
	}
	else
		wasLastPointValid = false;
	p++;

	for (int c = 0; c < nDataPoints; c++){
		if (p >= nBackPoints) 
			p -= nBackPoints;
		dataValue = pDoc->GetDataValue(whichGraph, whichGraphItem, p);
		if (IsValid(dataValue))
		{
			ypos = PixelBottomPos - int((dataValue - BottomValue) / UnitsPerPixel);
			xpos = int((c+1) * PixelsPerPoint) + PixelLeftPos;
			if (!wasLastPointValid)
				pDC->MoveTo(xpos-1,ypos);
			pDC->LineTo(xpos, ypos); // this is where we scribble
			wasLastPointValid = true;
		}
		else
			wasLastPointValid = false;
		p++;
	}
	pDC->SelectObject(ptrOldPen);
}

void CGraphDisplayView::PlotDataPoints()
{
	// plot the data
	for (int i = 0; i < pDoc->GraphCollection[whichGraph].nItems; i++)
	{
		if (pDoc->IsItemChecked(whichGraph,i))
			PlotData(i);
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
	
	whichWindow = pDoc->curWindow;
	nBackPoints = pDoc->nBackPoints;
	pDoc->pGraphView[whichWindow] = this;

	m_ToolTip.Create(this);
	CRect Rect;
	GetClientRect(&Rect);
	m_ToolTip.AddTool( this, LPSTR_TEXTCALLBACK, &Rect,1);//, LPCRECT lpRectTool = NULL, UINT nIDTool = 0 );
	//TOOLINFO
	//m_ToolTip.SetToolInfo();
	//EnableToolTips(TRUE);   // enable tool tips for view
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

void CGraphDisplayView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	int PixelLabelValue = int((point.x - PixelLeftPos) / PixelsPerPoint + firstPoint) % nBackPoints;
	CString timeLabel = "";
	CString valueLabel = "";
	if (IsDefinedMinMax && rect.PtInRect(point) && PixelLabelValue < nDataPoints)
	{
		// value component
		double value = double(PixelBottomPos - point.y) * UnitsPerPixel + BottomValue;
		
		// time component
		timeLabel = pDoc->GetPositionLabel(PixelLabelValue);
		if (timeLabel[0] == '0')
			timeLabel = timeLabel.Mid(1);
		valueLabel = ValueToString(value);
	}
	
	pDoc->m_pMainView->GetDlgItem(IDC_G_VALUE)->SetWindowText(valueLabel.GetBuffer(0));
	pDoc->m_pMainView->GetDlgItem(IDC_G_TIME)->SetWindowText(timeLabel.GetBuffer(0));
	
	if (pDoc->dataPlotFreq.GetTotalSeconds() > 10 && (CTime::GetCurrentTime() - pDoc->m_LastGraphUpdate).GetTotalSeconds() > 2)
	{
		//pDoc->m_pMainView->SendMessage(WM_TIMER,UPDATE_GRAPH_TIMER,0);
		pDoc->m_pMainView->OnTimer(UPDATE_GRAPH_TIMER);

	}

}

void CGraphDisplayView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	OnMouseMove(nFlags,point);
	//CView::OnLButtonDown(nFlags, point);
}


BOOL CGraphDisplayView::OnToolTipNotify(UINT id, NMHDR *pNMHDR, LRESULT *pResult)
{
   // need to handle both ANSI and UNICODE versions of the message
   TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
   //TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;   
   CString strTipText;
   UINT nID = pNMHDR->idFrom;
   if (pNMHDR->code == TTN_NEEDTEXTA && (pTTTA->uFlags & TTF_IDISHWND))// ||
      //pNMHDR->code == TTN_NEEDTEXTW && (pTTTW->uFlags & TTF_IDISHWND))   
   {
      // idFrom is actually the HWND of the tool
      nID = ::GetDlgCtrlID((HWND)nID);   
   }
   if (nID != 0) // will be zero on a separator
      strTipText.Format("Control ID = %d", nID);
   if (pNMHDR->code == TTN_NEEDTEXTA)
      lstrcpyn(pTTTA->szText, strTipText, sizeof(pTTTA->szText));   
   //else
    //  _mbstowcsz(pTTTW->szText, strTipText, sizeof(pTTTW->szText));
   *pResult = 0;   
   return TRUE;    // message was handled
}
