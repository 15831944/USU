// This is Version 1.0 PLEASE DOCUMENT CHANGES
// StartDialog.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "StartDialog.h"

#include "windows.h"
#include "LString.h"
#include "LadaStrings.h"
#include "LanguageChanger.h"
#include "htmlhelp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CFont LargeRussianArial;
extern CFont RussianArial;
extern CFont HugeRussianArial;
extern int   curLanguage;
extern int GetCurrentLanguage();
extern LString Strings;

extern BOOL LoadBMPImage(LPCTSTR sBMPFile, CBitmap &bitmap, CPalette *pPal);
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
	DlgTemplate.style = DS_CENTER | DS_MODALFRAME;// | DS_SETFONT; 
	DlgTemplate.cDlgItems = 0; 
	DlgTemplate.x = 0; 
	DlgTemplate.y = 0; 
	DlgTemplate.cx = GetSystemMetrics(SM_CXFULLSCREEN);
	DlgTemplate.cy = GetSystemMetrics(SM_CYFULLSCREEN);
	DlgTemplate.menu[0] = NULL; 
	DlgTemplate.windowClass[0] = NULL; //"CStartDialog";
	DlgTemplate.title[0] = NULL;
	/*
	MultiByteToWideChar(
		CP_ACP,         // code page
		NULL,         // character-type options
		LPCSTR("Lada Operating System"), // string to map
		37,       // number of bytes in string
		DlgTemplate.title,  // wide-character buffer
		40        // size of buffer
	);
	*/
	//DlgTemplate.title = "Lada Operating System";//[0]= NULL; 
	// The following members exist only if the style member is 
	// set to DS_SETFONT or DS_SHELLFONT.
	DlgTemplate.pointsize = 12; 
	DlgTemplate.weight = FW_NORMAL; 
	DlgTemplate.italic = 0;
	DlgTemplate.charset = 205;
	

	InitModalIndirect(&DlgTemplate);
	
	ProgramIcon = new CBitmap;

	//ProgramIcon->LoadBitmap(IDB_PROGRAMBMP);
	
	CPalette Palette;
		
	CString filePath = workingDirectory + "\\LadaPics\\ProgramIcon.bmp";
	LoadBMPImage((LPCTSTR) filePath, *ProgramIcon, &Palette);

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
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(ID_SETUP,ID_EXIT,OnButton)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStartDialog message handlers

BOOL CStartDialog::OnInitDialog() 
{
//	static BOOL DirectlyToCheckout=TRUE;
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	ShowWindow(SW_MAXIMIZE);
	CRect rect;
	GetClientRect(rect);

	BitmapBorder.Create( NULL,WS_CHILD|WS_VISIBLE|SS_BITMAP|SS_CENTERIMAGE, rect, this, IDC_BFRAME );
	BitmapBorder.SetBitmap((HBITMAP)ProgramIcon->m_hObject);
	//	m_picture.SetBitmap((HBITMAP)*ptrBitmap);
	int bWidth;
	int bHeigth;
	CRect ScreenRect(rect);
	rect.right = bWidth = rect.right / 5;
	rect.bottom = bHeigth = rect.bottom / 17;
	int bSpace = bHeigth * 4 / 3;

	CRect WelcomeRect(ScreenRect.left,bHeigth * 1,ScreenRect.right,bHeigth * 2);
	ScreenRect.DeflateRect(bWidth / 2, bHeigth * 2);
	rect.OffsetRect(bWidth * 2 / 3, bHeigth * 4);
	//CRect HelpRect = CRect(rect.left + bWidth + 10, rect.top, rect.right + bWidth * 2, rect.bottom + 15);

	Button1.Create( Strings.get(IDS_A1), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, rect, this, ID_SETUP );
	Button1.SetFont(&LargeRussianArial);
	//Button1Help.Create(NULL,WS_CHILD|WS_VISIBLE|SS_OWNERDRAW, HelpRect, this, IDC_HELPTEXT1);
	rect.OffsetRect(0, bSpace);
	//HelpRect.OffsetRect(0, bSpace);
	
	Button2.Create( Strings.get(IDS_A2), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, rect, this, ID_CHECK_OUT );
	Button2.SetFont(&LargeRussianArial);
	//Button2Help.Create(NULL,WS_CHILD|WS_VISIBLE|SS_OWNERDRAW, HelpRect, this, IDC_HELPTEXT2);
	rect.OffsetRect(0, bSpace);
	//HelpRect.OffsetRect(0, bSpace);
	
	Button3.Create( Strings.get(IDS_A3), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, rect, this, ID_WET_UP );
	Button3.SetFont(&LargeRussianArial);
	//Button3Help.Create(NULL,WS_CHILD|WS_VISIBLE|SS_OWNERDRAW, HelpRect, this, IDC_HELPTEXT3);
	rect.OffsetRect(0, bSpace);
	//HelpRect.OffsetRect(0, bSpace);
	
	Button4.Create( Strings.get(IDS_A4), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, rect, this, ID_NORMAL );
	Button4.SetFont(&LargeRussianArial);
	//Button4Help.Create(NULL,WS_CHILD|WS_VISIBLE|SS_OWNERDRAW, HelpRect, this, IDC_HELPTEXT4);
	rect.OffsetRect(0, bSpace);
	//HelpRect.OffsetRect(0, bSpace);
	
	Button5.Create( Strings.get(IDS_A5), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, rect, this, ID_DIAGNOSTICS );
	Button5.SetFont(&LargeRussianArial);
	//Button5Help.Create(NULL,WS_CHILD|WS_VISIBLE|SS_OWNERDRAW, HelpRect, this, IDC_HELPTEXT5);
	rect.OffsetRect(0, bSpace);
	//HelpRect.OffsetRect(0, bSpace);

	Button6.Create( Strings.get(IDS_A6), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, rect, this, ID_CHANGE_LANGUAGE );
	Button6.SetFont(&LargeRussianArial);
	//Button6Help.Create(NULL,WS_CHILD|WS_VISIBLE|SS_OWNERDRAW, HelpRect, this, IDC_HELPTEXT6);
	rect.OffsetRect(0, bSpace);
	//HelpRect.OffsetRect(0, bSpace);
	
	Button7.Create( Strings.get(IDS_A7), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, rect, this, ID_EXIT );
	Button7.SetFont(&LargeRussianArial);
	//Button7Help.Create(NULL,WS_CHILD|WS_VISIBLE|SS_OWNERDRAW, HelpRect, this, IDC_HELPTEXT7);

	Welcome.Create(NULL,WS_CHILD|WS_VISIBLE|SS_OWNERDRAW, WelcomeRect,this, IDC_WELCOMETEXT);
	Border.Create(NULL, WS_CHILD|WS_VISIBLE|SS_BLACKFRAME, ScreenRect, this);
/*	if (DirectlyToCheckout)
	{
		DirectlyToCheckout=FALSE;
		*result=(ID_CHECK_OUT);
		CDialog::OnOK();
	}
	*/

	//SetStrings();
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
		ItemString[0] = Strings.get(IDS_WELCOMESTRING);
		HFONT hFont = HFONT(HugeRussianArial);
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
		CString s = Strings.get(IDS_A1H + whichButton);
		
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

		HFONT hFont = HFONT(RussianArial);
		SelectObject(lpDrawItemStruct->hDC, hFont);
		GetTextExtentPoint32(lpDrawItemStruct->hDC, ItemString[0], ItemString[0].GetLength(),&ItemSize);//dc.GetTextExtent(welcomeString));
		break;}
	}

	SetBkMode(lpDrawItemStruct->hDC, TRANSPARENT);//OPAQUE);
  	
	
	for (int i = 0; i < TextLines; i++){
		TextOut(lpDrawItemStruct->hDC,x1,y1,ItemString[i],ItemString[i].GetLength());
		y1 += ItemSize.cy * 4 / 3;
	}

}

void CStartDialog::SetStrings()
{
	Button1.SetWindowText(Strings.get(IDS_A1));
	//GetDlgItem(IDC_HELPTEXT1)->SetWindowText(Strings.get(IDS_A1H));
	Button2.SetWindowText(Strings.get(IDS_A2));
	//GetDlgItem(IDC_HELPTEXT2)->SetWindowText(Strings.get(IDS_A2H));
	Button3.SetWindowText(Strings.get(IDS_A3));
	//GetDlgItem(IDC_HELPTEXT3)->SetWindowText(Strings.get(IDS_A3H));
	Button4.SetWindowText(Strings.get(IDS_A4));
	//GetDlgItem(IDC_HELPTEXT4)->SetWindowText(Strings.get(IDS_A4H));
	Button5.SetWindowText(Strings.get(IDS_A5));
	//GetDlgItem(IDC_HELPTEXT5)->SetWindowText(Strings.get(IDS_A5H));
	Button6.SetWindowText(Strings.get(IDS_A6));
	//GetDlgItem(IDC_HELPTEXT6)->SetWindowText(Strings.get(IDS_A6H));
	Button7.SetWindowText(Strings.get(IDS_A7));
	//GetDlgItem(IDC_HELPTEXT7)->SetWindowText(Strings.get(IDS_A7H));
	GetDlgItem(IDC_WELCOMETEXT)->SetWindowText(Strings.get(IDS_WELCOMESTRING));
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
		LanguageChanger lDlg;
		lDlg.DoModal();
		SetStrings();
		Invalidate();  
		return;
	}
	if (nID == ID_DIAGNOSTICS)
	{
		if (curLanguage == ENGLISH)
		{
			HtmlHelp(NULL, workingDirectory + "\\LADA Help.chm", HH_DISPLAY_TOPIC, NULL);
		}
		else
		{
			HtmlHelp(NULL, workingDirectory + "\\LADA Help Ru.chm", HH_DISPLAY_TOPIC, NULL);
		}
		return;
	}
	
	*result = nID;
	CDialog::OnOK();
}

BOOL CStartDialog::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_F2)
	{
		curLanguage = !curLanguage;
		SetStrings();
		Invalidate();
		return TRUE;
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == 13)
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}

void CStartDialog::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// simply having this function here makes it so the background will
	// be erased (temporarily) when the language is changed.

	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
}
