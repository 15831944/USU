// This is Version 1.0 PLEASE DOCUMENT CHANGES
// MessageBox.cpp : implementation file
//

#include "stdafx.h"
#include "LADA Control Module.h"
#include "MessageBox.h"
#include <math.h>
#include "resource.h"
#include "LString.h"
#include "LadaStrings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern LString Strings;

/*
#define MB_DEFBUTTON1               0x00000000L
#define MB_DEFBUTTON2               0x00000100L
#define MB_DEFBUTTON3               0x00000200L
#if(WINVER >= 0x0400)
#define MB_DEFBUTTON4               0x00000300L
*/

//#define MB_OK                       0x00000000L
//#define MB_OKCANCEL                 0x00000001L
//#define MB_ABORTRETRYIGNORE         0x00000002L
//#define MB_YESNOCANCEL              0x00000003L
//#define MB_YESNO                    0x00000004L
//#define MB_RETRYCANCEL              0x00000005L
#define MB_CANCELTRYAGAINCONTINUE		0x00000006L

// IDOK			= 1
// IDCANCEL		= 2
// IDABORT		= 3
// IDRETRY		= 4
// IDIGNORE		= 5
// IDYES		= 6
// IDNO			= 7
// IDCONTINUE	= 8
// IDTRYAGAIN	= 9

#define ICON_WIDTH			40
#define ICON_HEIGHT			28
#define MARGIN_WIDTH_SIDE	12
#define MARGIN_WIDTH_TOP	15
#define BUTTON_SEPARATOR	15
#define BUTTON_HEIGHT		23
#define BUTTON_MARGIN		5
#define N_BUTTONS			10
/////////////////////////////////////////////////////////////////////////////
// CMessageBox dialog

extern int curLanguage;

// static variables
bool CMessageBox::InfoInitialized = false;
int	 CMessageBox::charWidth[256];
int	 CMessageBox::screenWidth;
int  CMessageBox::charHeight;
CFont * CMessageBox::ptrFont = NULL;
int CMessageBox::buttonWidths[10][2];
char * ButtonTexts[] = { "","&OK","&Cancel","&Abort","&Retry","&Ignore","&Yes","&No","&Continue","&Try Again",
						 "","&ОК","&Отмена","&Прервать","&Повторить","&Пропустить","&Да","&Нет","&Продолжить","&Повторить попытку"};

int B1[] = {IDOK};
int B2[] = {IDOK,IDCANCEL};
int B3[] = {IDABORT,IDRETRY,IDIGNORE};
int B4[] = {IDYES,IDNO,IDCANCEL};
int B5[] = {IDYES,IDNO};
int B6[] = {IDRETRY,IDCANCEL};
int B7[] = {IDCANCEL,IDTRYAGAIN,IDCONTINUE};
int * BUTTONS[] = { B1, B2, B3, B4, B5, B6, B7 };
int nButtons[] = { 1, 2, 3, 3, 2, 2, 3 };

UINT MessageIDD[] = {IDD_OK, 
					 IDD_OKCANCEL,
					 IDD_ABORTRETRYIGNORE,
					 IDD_YESNOCANCEL,
					 IDD_YESNO,
					 IDD_RETRYCANCEL,
					 IDD_CANCELTRYCONTINUE};

UINT MyMessageBox(const char *text, const char *title = NULL, DWORD mFlags = MB_OK)
{
	CMessageBox mb(text, (title == NULL ? CString(""):CString(title)), MessageIDD[mFlags & 0xF], mFlags & 0x70, mFlags & 0xF00, INFINITE);
	return mb.DoModal();
}

UINT MyMessageBox(CString text, CString title = "", DWORD mFlags = MB_OK)
{
	CMessageBox mb(text, title, MessageIDD[mFlags & 0xF], mFlags & 0x70, mFlags & 0xF00, INFINITE);
	return mb.DoModal();

}

UINT MyMessageBox(UINT MessageID, UINT MessageTitleID = NO_TITLE, DWORD mFlags = MB_OK)
{
	CMessageBox mb(MessageID, MessageTitleID, MessageIDD[mFlags & 0xF], mFlags & 0x70, mFlags & 0xF00, INFINITE);
	return mb.DoModal();
}

UINT NotificationBox(const char *text, const char *title = NULL, DWORD mFlags = MB_OK, BOOL IsModal = FALSE, DWORD Duration = INFINITE)
{
	if (IsModal)
	{
		CMessageBox mb(text, title, MessageIDD[mFlags & 0xF], mFlags & 0x70, mFlags & 0xF00, Duration, IsModal);
		return mb.DoModal();
	}
	else
	{
		CMessageBox * ptrMB;
		ptrMB = new CMessageBox(text, title, MessageIDD[mFlags & 0xF], mFlags & 0x70, mFlags & 0xF00, Duration, IsModal);
		ptrMB->Create(MessageIDD[mFlags & 0xF]);
		return 0;
	}
	return 0;
}

UINT NotificationBox(CString text, CString title = "", DWORD mFlags = MB_OK, BOOL IsModal = FALSE, DWORD Duration = INFINITE)
{
	return NotificationBox(text.GetBuffer(0), (title == "" ? NULL : title.GetBuffer(0)), mFlags, IsModal, Duration);
}

UINT NotificationBox(UINT MessageID, UINT MessageTitleID = NO_TITLE, DWORD mFlags = MB_OK, BOOL IsModal = FALSE, DWORD Duration = INFINITE)
{
	if (IsModal)
	{
		CMessageBox mb(MessageID, MessageTitleID, MessageIDD[mFlags & 0xF], mFlags & 0x70, mFlags & 0xF00, Duration, IsModal);
		return mb.DoModal();
	}
	else
	{
		CMessageBox *ptrMB;
		ptrMB = new CMessageBox(MessageID, MessageTitleID, MessageIDD[mFlags & 0xF], mFlags & 0x70, mFlags & 0xF00, Duration, IsModal);
		ptrMB->Create(MessageIDD[mFlags & 0xF]);
		return 0;
	}
	return 0;
}

CMessageBox::CMessageBox(UINT MessageID, UINT MessageTitleID, DWORD DialogID, UINT iconID, UINT defaultButton, DWORD Duration /*= INFINITE*/, BOOL IsModal, CWnd *pParent)
	: CDialog(DialogID, pParent)
{
	m_IsModal = IsModal;
	m_Duration = Duration;
	m_MessageID = MessageID;
	m_MessageTitleID = MessageTitleID;
	m_Text = Strings.get(MessageID);
	m_Title = (MessageTitleID != NO_TITLE) ? Strings.get(MessageTitleID) : CString("");
	m_DlgID = DialogID;
	
	defButtonNum = defaultButton >> 8;
	
	switch (m_DlgID){
	case IDD_ABORTRETRYIGNORE:	m_MBType = MB_ABORTRETRYIGNORE; break;
	case IDD_CANCELTRYCONTINUE: m_MBType = MB_CANCELTRYAGAINCONTINUE; break;
	case IDD_OK:				m_MBType = MB_OK; break;
	case IDD_OKCANCEL:			m_MBType = MB_OKCANCEL; break;
	case IDD_RETRYCANCEL:		m_MBType = MB_RETRYCANCEL; break;
	case IDD_YESNO:				m_MBType = MB_YESNO; break;
	case IDD_YESNOCANCEL:		m_MBType = MB_YESNOCANCEL; break;
	}

	if (iconID)
	{
		IsIcon = true;
		switch (iconID)
		{
		case MB_ICONEXCLAMATION: //case MB_ICONWARNING:
			m_IconID = IDI_EXCLAMATION;
			break;
		case MB_ICONINFORMATION: //case MB_ICONASTERISK:
			m_IconID = IDI_INFORMATION;
			break;
		case MB_ICONQUESTION:
			m_IconID = IDI_QUESTION;
			break;
		case MB_ICONSTOP: //case MB_ICONERROR: case MB_ICONHAND:
			m_IconID = IDI_ERROR;
			break;
		default:
			IsIcon = false;
		}	
	}
	else 
		IsIcon = false;
}

CMessageBox::CMessageBox(CString mText, CString mTitle, DWORD DialogID, UINT iconID, UINT defaultButton, DWORD Duration /*= INFINITE*/, BOOL IsModal, CWnd* pParent /*=NULL*/)
	: CDialog(DialogID, pParent)
{
	m_IsModal = IsModal;
	m_Duration = Duration;
	m_MessageID = 0xFFFFFFAA;
	m_MessageTitleID = 0xFFFFFFAA;
	m_Text = mText;
	m_Title = mTitle;
	m_DlgID = DialogID;
	
	defButtonNum = defaultButton >> 8;

	switch (m_DlgID){
	case IDD_ABORTRETRYIGNORE:	m_MBType = MB_ABORTRETRYIGNORE; break;
	case IDD_CANCELTRYCONTINUE: m_MBType = MB_CANCELTRYAGAINCONTINUE; break;
	case IDD_OK:				m_MBType = MB_OK; break;
	case IDD_OKCANCEL:			m_MBType = MB_OKCANCEL; break;
	case IDD_RETRYCANCEL:		m_MBType = MB_RETRYCANCEL; break;
	case IDD_YESNO:				m_MBType = MB_YESNO; break;
	case IDD_YESNOCANCEL:		m_MBType = MB_YESNOCANCEL; break;
	}

	if (iconID)
	{
		IsIcon = true;
		switch (iconID)
		{
		case MB_ICONEXCLAMATION: //case MB_ICONWARNING:
			m_IconID = IDI_EXCLAMATION;
			break;
		case MB_ICONINFORMATION: //case MB_ICONASTERISK:
			m_IconID = IDI_INFORMATION;
			break;
		case MB_ICONQUESTION:
			m_IconID = IDI_QUESTION;
			break;
		case MB_ICONSTOP: //case MB_ICONERROR: case MB_ICONHAND:
			m_IconID = IDI_ERROR;
			break;
		default:
			IsIcon = false;
		}	
	}
	else 
		IsIcon = false;

	//{{AFX_DATA_INIT(CMessageBox)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMessageBox::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMessageBox)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMessageBox, CDialog)
	//{{AFX_MSG_MAP(CMessageBox)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(IDOK,IDTRYAGAIN,OnButton)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMessageBox message handlers

void CMessageBox::OnButton(UINT nID) 
{
	// TODO: Add extra validation here
	if (m_Duration != INFINITE)
	{
		KillTimer(1);
	}
	
	if (m_IsModal)
		EndDialog(nID);
	else
	{
		DestroyWindow();		
	}

}

BOOL CMessageBox::OnInitDialog() 
{
	m_DefaultButton = IDOK;

	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if (!InfoInitialized)
	{
		InitializeFontInfo();
	}
	if (ptrFont == NULL)
	{
		MessageBox("ptrFont == NULL.  Message box intialization failed.");
		EndDialog(IDABORT);
	}

	// display the icon (if there is one)
	if (IsIcon)
	{
		GetDlgItem(IDC_MICON)->ShowWindow(SW_SHOW);
		((CStatic*)GetDlgItem(IDC_MICON))->SetIcon( ::LoadIcon(NULL, m_IconID) );
	}
	
	SetFont(ptrFont);

	textBox.Create("",WS_CHILD|WS_VISIBLE,CRect(0,0,0,0), this);
	textBox.SetFont(ptrFont);

	DrawMessageBox();

	if (m_Duration != INFINITE)
	{
		SetTimer(1, m_Duration, NULL);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMessageBox::InitializeFontInfo()
{
	CPaintDC dc(this); // device context for painting
	dc.SelectObject(ptrFont);
	dc.GetOutputCharWidth(0,255,charWidth);
	
	TEXTMETRIC Metrics;
	dc.GetOutputTextMetrics(&Metrics);
	charHeight = Metrics.tmHeight;
	InfoInitialized = true;
	screenWidth = GetSystemMetrics(SM_CXSCREEN);

	for (int l = 0; l < 2; l++)
	{
		for (int b = 1; b < 10; b++)
		{
			int Length = 0;
			int nChar = strlen(ButtonTexts[l * N_BUTTONS + b]);
			for (int i = 0; i < nChar; i++)
				Length += charWidth[(unsigned char)(ButtonTexts[l * N_BUTTONS + b][i])];
			Length += BUTTON_MARGIN * 3; // |<-margin[ButtonText]margin->|
			buttonWidths[b][l] = Length;
		}
	}
}

void CMessageBox::SetMessageFont(CFont *pFont)
{
	ptrFont = pFont;
	InfoInitialized = false;
}

void CMessageBox::DrawMessageBox()
{
	
	SetWindowText(m_Title);

	// get the length of the text to be displayed in the message box
	// max box width
	int textBoxWidth = 0;
	int textBoxHeight = 0;
	bool MakeTextCentered = false;

	if (m_Text.GetLength())
	{
		int maxBoxWidth = screenWidth / 2;
		int maxTextWidth = maxBoxWidth - IsIcon * ICON_WIDTH - 2 * MARGIN_WIDTH_SIDE;

		//int Length = 0;
		int LongestString = 0;
		int currentString = 0;
		for (int i = 0; i < m_Text.GetLength(); i++)
		{
			if (m_Text[i] == '\n' || m_Text == '\r')
			{
				if (currentString > LongestString)
					LongestString = currentString;
				currentString = 0;
			}
			else
			{
				unsigned char whichChar = (unsigned char)m_Text[i];
				currentString += charWidth[whichChar];
			}
		}
		if (currentString > LongestString)
			LongestString = currentString;
		// Length += charWidth[m_Text[i]];

		int nl = (int)ceil((double)LongestString / (double)maxTextWidth);
		textBoxWidth = LongestString / nl + 50;

		currentString = 0;
		int nLinesText = 1;
		for ( i = 0; i < m_Text.GetLength(); i++)
		{
			if (m_Text[i] == '\n')
			{
				nLinesText++;
				currentString = 0;
			}
			else
			{
				unsigned char whichChar = (unsigned char)m_Text[i];
				currentString += charWidth[whichChar];
			}
			
			if (currentString > textBoxWidth)
			{
				nLinesText++;
				currentString = 0;
			}
		}

		textBoxHeight = nLinesText * charHeight;

		if (nLinesText == 1)
			MakeTextCentered = true;
	}

	if (IsIcon && textBoxHeight < ICON_HEIGHT)
		textBoxHeight = ICON_HEIGHT;

	int totalButtonWidth = 0;
	for ( int i = 0; i < nButtons[m_MBType]; i++)
		totalButtonWidth += buttonWidths[BUTTONS[m_MBType][i]][curLanguage];
	totalButtonWidth += BUTTON_MARGIN * 2 * nButtons[m_MBType];

	int minBoxWidth = 2 * MARGIN_WIDTH_SIDE + totalButtonWidth;
	
	int BoxWidth = IsIcon * ICON_WIDTH + 2 * MARGIN_WIDTH_SIDE + textBoxWidth + 10; //;
	if (BoxWidth < minBoxWidth)
		BoxWidth = minBoxWidth;

	int ButtonPosY = MARGIN_WIDTH_TOP + textBoxHeight + BUTTON_SEPARATOR;
	int BoxHeight = 20 + ButtonPosY + MARGIN_WIDTH_TOP +  BUTTON_HEIGHT; // + title bar height?
	SetWindowPos(NULL,0,0,BoxWidth,BoxHeight,SWP_NOMOVE|SWP_NOZORDER);
	
	if (m_Text.GetLength())
	{
		int x = MARGIN_WIDTH_SIDE + IsIcon * ICON_WIDTH;
		int y = MARGIN_WIDTH_TOP;
		int cx = textBoxWidth;
		int cy = textBoxHeight;
		//textBox.Create(m_Text,WS_CHILD|WS_VISIBLE| (MakeTextCentered ? SS_CENTER : 0) ,CRect(x1,y1,x2,y2), this);
		//textBox.SetFont(ptrFont);
		textBox.ModifyStyle( (MakeTextCentered ? 0: SS_CENTER), (MakeTextCentered ? SS_CENTER: 0) ); 
		textBox.SetWindowPos(NULL, x, y, cx, cy, SWP_NOZORDER );
		textBox.SetWindowText(m_Text);
	}
	
	int ButtonPosX = (BoxWidth - MARGIN_WIDTH_SIDE * 2 - totalButtonWidth) / 2 + MARGIN_WIDTH_SIDE;
	for ( i = 0; i < nButtons[m_MBType]; i++)
	{
		CWnd * ptrButton = GetDlgItem(BUTTONS[m_MBType][i]);
		if (i == defButtonNum)
			((CButton*)ptrButton)->SetButtonStyle(BS_DEFPUSHBUTTON);
		ptrButton->SetWindowText(ButtonTexts[curLanguage * N_BUTTONS + BUTTONS[m_MBType][i]]);
		ptrButton->SetFont(ptrFont);
		ptrButton->SetWindowPos(NULL,ButtonPosX + BUTTON_MARGIN - 3,ButtonPosY, buttonWidths[BUTTONS[m_MBType][i]][curLanguage], BUTTON_HEIGHT, SWP_NOZORDER);
		ButtonPosX += buttonWidths[BUTTONS[m_MBType][i]][curLanguage] + 2 * BUTTON_MARGIN;
	}
}

BOOL CMessageBox::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_F2)
	{
		if (m_MessageID != 0xFFFFFFAA &&
			m_MessageTitleID != 0xFFFFFFAA)
		{
			curLanguage = !curLanguage;
			m_Text = Strings.get(m_MessageID);
			m_Title = (m_MessageTitleID != NO_TITLE) ? Strings.get(m_MessageTitleID) : CString("");
			DrawMessageBox();
			return TRUE;
		}
	}
	if (pMsg->message == WM_TIMER)
	{
		int a = 0;
		OnTimer(pMsg->wParam);
		return TRUE;
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == 13)
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}

void CMessageBox::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_Duration != INFINITE)
	{
		OnButton(m_DefaultButton);
	}
	else
	{
		// write to error log...  this should have happened
		// (OnTimer called when m_Duration == INFINITE
	}
}

void CMessageBox::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	//KillTimer(1);	
	//EndDialog(IDABORT);
	//DestroyWindow();
}

void CMessageBox::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	if (!m_IsModal)
		delete this;
}
