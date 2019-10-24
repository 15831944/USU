// StartDialog.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "StartDialog.h"

#include "windows.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CFont RussianArial;
extern CFont smallRussianArial;
extern CFont largeRussianArial;
extern int   curLanguage;
extern int GetCurrentLanguage();
/////////////////////////////////////////////////////////////////////////////
// CStartDialog dialog
#define MAX_CHAR_PER_LINE		50

CStartDialog::CStartDialog(UINT *r, CWnd* pParent /*=NULL*/)
	//: CDialog(CStartDialog::IDD, pParent)
{
	result = r;
	/*
	DLGTEMPLATE DlgTemplate;
	DlgTemplate.style = DS_CENTER | DS_MODALFRAME | DS_SETFONT;
	DlgTemplate.dwExtendedStyle; 
	DlgTemplate.cdit; 
	DlgTemplate.x = 0; 
	DlgTemplate.y = 0; 
	DlgTemplate.cx; 
	DlgTemplate.cy;*/ 
	
	
	DlgTemplate.dlgVer = 1; 
	DlgTemplate.signature = 0xFFFF; 
	DlgTemplate.helpID = NULL; 
	DlgTemplate.exStyle = NULL; 
	DlgTemplate.style = DS_CENTER | DS_MODALFRAME | DS_SETFONT; 
	DlgTemplate.cDlgItems = 0; 
	DlgTemplate.x = 0; 
	DlgTemplate.y = 0; 
	DlgTemplate.cx = GetSystemMetrics(SM_CXFULLSCREEN);
	DlgTemplate.cy = GetSystemMetrics(SM_CYFULLSCREEN);
	DlgTemplate.menu[0] = NULL; 
	DlgTemplate.windowClass[0] = NULL; 
	DlgTemplate.title[0] = NULL; //title[titleLen]; 
	// The following members exist only if the style member is 
	// set to DS_SETFONT or DS_SHELLFONT.
	DlgTemplate.pointsize = 12; 
	DlgTemplate.weight = FW_NORMAL; 
	DlgTemplate.italic = 0;
	DlgTemplate.charset = 205;
	MultiByteToWideChar(
		CP_ACP,         // code page
		NULL,         // character-type options
		LPCSTR("Times New Roman"), // string to map
		16,       // number of bytes in string
		DlgTemplate.typeface,  // wide-character buffer
		40        // size of buffer
	);

	InitModalIndirect(&DlgTemplate);
	ProgramIcon = new CBitmap;
	ProgramIcon->LoadBitmap(IDB_PROGRAMBMP);
	
	  //{{AFX_DATA_INIT(CStartDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CStartDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStartDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStartDialog, CDialog)
	//{{AFX_MSG_MAP(CStartDialog)
	ON_WM_DRAWITEM()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(ID_SETUP,ID_EXIT,OnButton)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStartDialog message handlers

BOOL CStartDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	ShowWindow(SW_MAXIMIZE);
	CRect rect;
	GetClientRect(rect);
	CString s;

	BitmapBorder.Create( NULL,WS_CHILD|WS_VISIBLE|SS_BITMAP|SS_CENTERIMAGE, rect, this, IDC_BFRAME );
	BitmapBorder.SetBitmap((HBITMAP)ProgramIcon->m_hObject);
	int bWidth;
	int bHeigth;
	CRect ScreenRect(rect);
	rect.right = bWidth = rect.right / 6;
	rect.bottom = bHeigth = rect.bottom / 17;
	int bSpace = bHeigth * 4 / 3;

	CRect WelcomeRect(ScreenRect.left,bHeigth * 1,ScreenRect.right,bHeigth * 2);
	ScreenRect.DeflateRect(bWidth / 2, bHeigth * 2);
	rect.OffsetRect(bWidth * 2 / 3, bHeigth * 4);
	CRect HelpRect = CRect(rect.left + bWidth + 10, rect.top, rect.right + bWidth * 2, rect.bottom + 15);

	s.LoadString(IDS_SBUTTON1);
	Button1.Create( s, WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, rect, this, ID_SETUP );
	Button1.SetFont(&RussianArial);
	Button1Help.Create(NULL,WS_CHILD|WS_VISIBLE|SS_OWNERDRAW, HelpRect, this, IDC_HELPTEXT1);
	rect.OffsetRect(0, bSpace);
	HelpRect.OffsetRect(0, bSpace);
	
	s.LoadString(IDS_SBUTTON2);
	Button2.Create( s, WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, rect, this, ID_CHECK_OUT );
	Button2.SetFont(&RussianArial);
	Button2Help.Create(NULL,WS_CHILD|WS_VISIBLE|SS_OWNERDRAW, HelpRect, this, IDC_HELPTEXT2);
	rect.OffsetRect(0, bSpace);
	HelpRect.OffsetRect(0, bSpace);
	
	s.LoadString(IDS_SBUTTON3);
	Button3.Create( s, WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, rect, this, ID_WET_UP );
	Button3.SetFont(&RussianArial);
	Button3Help.Create(NULL,WS_CHILD|WS_VISIBLE|SS_OWNERDRAW, HelpRect, this, IDC_HELPTEXT3);
	rect.OffsetRect(0, bSpace);
	HelpRect.OffsetRect(0, bSpace);
	
	s.LoadString(IDS_SBUTTON4);
	Button4.Create( s, WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, rect, this, ID_NORMAL );
	Button4.SetFont(&RussianArial);
	Button4Help.Create(NULL,WS_CHILD|WS_VISIBLE|SS_OWNERDRAW, HelpRect, this, IDC_HELPTEXT4);
	rect.OffsetRect(0, bSpace);
	HelpRect.OffsetRect(0, bSpace);
	
	s.LoadString(IDS_SBUTTON5);
	Button5.Create( s, WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, rect, this, ID_DIAGNOSTICS );
	Button5.SetFont(&RussianArial);
	Button5Help.Create(NULL,WS_CHILD|WS_VISIBLE|SS_OWNERDRAW, HelpRect, this, IDC_HELPTEXT5);
	rect.OffsetRect(0, bSpace);
	HelpRect.OffsetRect(0, bSpace);

	s.LoadString(IDS_SBUTTON6);
	Button6.Create( s, WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, rect, this, ID_CHANGE_LANGUAGE );
	Button6.SetFont(&RussianArial);
	Button6Help.Create(NULL,WS_CHILD|WS_VISIBLE|SS_OWNERDRAW, HelpRect, this, IDC_HELPTEXT6);
	rect.OffsetRect(0, bSpace);
	HelpRect.OffsetRect(0, bSpace);
	
	s.LoadString(IDS_SBUTTON7);
	Button7.Create( s, WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, rect, this, ID_EXIT );
	Button7.SetFont(&RussianArial);
	Button7Help.Create(NULL,WS_CHILD|WS_VISIBLE|SS_OWNERDRAW, HelpRect, this, IDC_HELPTEXT7);

	Welcome.Create(NULL,WS_CHILD|WS_VISIBLE|SS_OWNERDRAW, WelcomeRect,this, IDC_WELCOMETEXT);
	Border.Create(NULL, WS_CHILD|WS_VISIBLE|SS_BLACKFRAME, ScreenRect, this);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStartDialog::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CString ItemString[4];
	CSize ItemSize;
	int TextLines = 0;
	int x1 = 0;
	int y1 = 0;

	switch (nIDCtl) {
	case IDC_WELCOMETEXT: {
		ItemString[0].LoadString(IDS_WELCOMESTRING);
		HFONT hFont = HFONT(largeRussianArial);
		SelectObject(lpDrawItemStruct->hDC, hFont);
		//SetBkColor(lpDrawItemStruct->hDC,RGB(255,255,255));          // handle to DC
		GetTextExtentPoint32(lpDrawItemStruct->hDC, ItemString[0], ItemString[0].GetLength(),&ItemSize);//dc.GetTextExtent(welcomeString));
		x1 = (lpDrawItemStruct->rcItem.right - lpDrawItemStruct->rcItem.left - ItemSize.cx)/2;
		y1 = 0;
		TextLines = 1;
		break;}
	case IDC_HELPTEXT1:
	case IDC_HELPTEXT2:
	case IDC_HELPTEXT3:
	case IDC_HELPTEXT4:
	case IDC_HELPTEXT5:
	case IDC_HELPTEXT6:
	case IDC_HELPTEXT7:{
		int whichButton = nIDCtl - IDC_HELPTEXT1;
		CString s;
		s.LoadString(IDS_STEXT1 + whichButton);
		int sLength = s.GetLength();
		int pos = 0;
		int c;
		while (sLength > 0 && TextLines < 4){
			c = MAX_CHAR_PER_LINE;
			if (sLength <= MAX_CHAR_PER_LINE)
				c = sLength;
			else {
				while (c > 0 && s.GetAt(pos + c) != ' ' && s.GetAt(pos + c - 1) != ' ') 
					c--;
			}
			if (c == 0)
				break;
			ItemString[TextLines++] = s.Mid(pos,c);
			pos += c;
			sLength -= c;
		}

		HFONT hFont = HFONT(smallRussianArial);
		SelectObject(lpDrawItemStruct->hDC, hFont);
		GetTextExtentPoint32(lpDrawItemStruct->hDC, ItemString[0], ItemString[0].GetLength(),&ItemSize);//dc.GetTextExtent(welcomeString));
		break;}
	}

	SetBkMode(lpDrawItemStruct->hDC, TRANSPARENT);
  	
	
	for (int i = 0; i < TextLines; i++){
		TextOut(lpDrawItemStruct->hDC,x1,y1,ItemString[i],ItemString[i].GetLength());
		y1 += ItemSize.cy * 4 / 3;
	}

}

void CStartDialog::SetStrings()
{
	CString s;
	s.LoadString(IDS_SBUTTON1);
	Button1.SetWindowText(s);
	s.LoadString(IDS_SBUTTON2);
	Button2.SetWindowText(s);
	s.LoadString(IDS_SBUTTON3);
	Button3.SetWindowText(s);
	s.LoadString(IDS_SBUTTON4);
	Button4.SetWindowText(s);
	s.LoadString(IDS_SBUTTON5);
	Button5.SetWindowText(s);
	s.LoadString(IDS_SBUTTON6);
	Button6.SetWindowText(s);
	s.LoadString(IDS_SBUTTON7);
	Button7.SetWindowText(s);
}

void CStartDialog::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	delete ProgramIcon;
}

void CStartDialog::OnButton(UINT nID)
{
	if (nID == ID_CHANGE_LANGUAGE)
	{
#ifdef _RAPID_TRANSLATION
		curLanguage = -1;
		RTSwitchDialog();
		GetCurrentLanguage();
		SetStrings();
		Invalidate();      // Update Window to cause View to redraw.   
		UpdateWindow();
		/*
		if (curLanguage != lastLanguage){
			m_wText.LoadString(IDS_STRING1);
			lastLanguage = curLanguage;
			UpdateData(FALSE);
		}
		*/
#endif
		return;
	}

	*result = nID;
	CDialog::OnOK();
}
