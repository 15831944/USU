// CheckOutDlg1.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "CheckOutDlg1.h"
#include "LadaStrings.h"
#include "Lstring.h"
#include "LADA Control ModuleDoc.h"
#include "Checkout.h"
#include "inputlocations.h"
#include "SystemDiagDlg.h"
#include "verify.h"
#include "LadaTest.h"
#include "display.h"
#include "HistoryClass.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define	CHECK_OUT_FAILED	-1
#define	STEP_FAILED			0
#define	STEP_SUCCESSFUL		1

extern LString Strings;				// The strings for both languages
extern CFont RussianArial;			// The font used
extern CString IntToString(int number);
extern UINT MyMessageBox(UINT MessageID, UINT MessageTitleID = NO_TITLE, DWORD mFlags = MB_OK);
#undef MessageBox
#define MessageBox MyMessageBox
extern UINT NotificationBox(UINT MessageID, UINT MessageTitleID = NO_TITLE, DWORD mFlags = MB_OK, BOOL IsModal = FALSE, DWORD Duration = INFINITE);
extern BOOL LoadBMPImage(LPCTSTR sBMPFile, CBitmap &bitmap, CPalette *pPal);
/////////////////////////////////////////////////////////////////////////////
// Step Functions

CString					CCheckOutDlg::CompletedFileName;
CheckOutType			CCheckOutDlg::m_DlgType;
CCheckout *				CCheckOutDlg::print = NULL;
CLADAControlModuleDoc * CCheckOutDlg::pDoc = NULL;
BOOL					CCheckOutDlg::m_IsAutomatic = FALSE;


int CCheckOutDlg::Step1() 
{
	switch(m_DlgType)
	{
	case CheckOut:
		{
			// Turn CM-IDC POWER switch on
			return STEP_SUCCESSFUL;
		}
	case Tensiometer:
		{


		}
	}
}

int CCheckOutDlg::Step2()
{
	switch(m_DlgType)
	{
	case CheckOut:
		{
			// CM-IDC POWER LEDs are lit
			return STEP_SUCCESSFUL;
		}
	case Tensiometer:
		{


		}
	}
	
}

int CCheckOutDlg::Step3()
{
	switch(m_DlgType)
	{
	case CheckOut:
		{
			pDoc->m_ControlMode = ManualControlMode;
			if (pDoc->Connect(FALSE, Regular, FALSE))
			{// don't start data retrieval mode, make sure regular program is running on CR10, don't do initialization
				BOOL Success;
				
				Success = pDoc->commObject->UpdateCR10Time();
								
				if (!m_IsAutomatic && !Success)
					NotificationBox(IDS_M_TIME_NOT_UPDATED,IDS_PROGRAM_NAME,MB_OK,FALSE,1000);

				return Success;
			}
			else
				return CHECK_OUT_FAILED;
		}
	case Tensiometer:
		{


		}
	}
}

int CCheckOutDlg::Step4()
{
	switch(m_DlgType)
	{
	case CheckOut:
		{
			int listSize = 10;
			int InputList[] = { VOLTAGE_1, CURRENT_1, VOLTAGE_2, CURRENT_2,
								VOLTAGE_3, CURRENT_3, VOLTAGE_4, CURRENT_4,
								VOLTAGE_5, CURRENT_5 };
			
			double * returnData = new double[listSize];
			CSystemDiagDlg dlg(pDoc, -1, FALSE, InputList, listSize, returnData, m_IsAutomatic, FALSE);
			dlg.DoModal();
			delete [] returnData;
			// to do: why are we collecting these values and not saving them?

			return STEP_SUCCESSFUL;
		}
	case Tensiometer:
		{


		}
	}
}

int CCheckOutDlg::Step5()
{
	switch(m_DlgType)
	{
	case CheckOut:
		{
			Verify dlga(pDoc,m_IsAutomatic,print);
			dlga.DoModal();
			return STEP_SUCCESSFUL;
		}
	case Tensiometer:
		{


		}
	}
}

int CCheckOutDlg::Step6()
{
	switch(m_DlgType)
	{
	case CheckOut:
		{
			LadaTest dlgc(pDoc, print, m_IsAutomatic);
			dlgc.DoModal();
			return STEP_SUCCESSFUL;
		}
	case Tensiometer:
		{


		}
	}
}

int CCheckOutDlg::Step7()
{
	switch(m_DlgType)
	{
	case CheckOut:
		{
			Display ddlg(print);
			ddlg.DoModal();
			CString fName = pDoc->dataFolder + "\\" + CompletedFileName;
			ofstream fout (fName);	
			fout << "Parameter Designation\tIndication" << endl;
			print->output(fout);
			return STEP_SUCCESSFUL;
		}
	case Tensiometer:
		{


		}
	}
	
}

int CCheckOutDlg::Step8()
{
	switch(m_DlgType)
	{
	case CheckOut:
		{
			return STEP_SUCCESSFUL;
		}
	case Tensiometer:
		{
			return STEP_SUCCESSFUL;
		}
	}
	
}

int CCheckOutDlg::Step9()
{

	switch(m_DlgType)
	{
	case CheckOut:
		{
			// Turn CM-IDC POWER switch on
			return STEP_SUCCESSFUL;
		}
	case Tensiometer:
		{
			return STEP_SUCCESSFUL;
		}
	}
}

int CCheckOutDlg::Step10()
{

	switch(m_DlgType)
	{
	case CheckOut:
		{
			// Turn CM-IDC POWER switch on
			return STEP_SUCCESSFUL;
		}
	case Tensiometer:
		{
			return STEP_SUCCESSFUL;

		}
	}
}

int CCheckOutDlg::Step11()
{

	switch(m_DlgType)
	{
	case CheckOut:
		{
			// Turn CM-IDC POWER switch on
			return STEP_SUCCESSFUL;
		}
	case Tensiometer:
		{
			return STEP_SUCCESSFUL;

		}
	}
}

int CCheckOutDlg::Step12()
{

	switch(m_DlgType)
	{
	case CheckOut:
		{
			// Turn CM-IDC POWER switch on
			return STEP_SUCCESSFUL;
		}
	case Tensiometer:
		{
			return STEP_SUCCESSFUL;

		}
	}
}

int CCheckOutDlg::Step13()
{

	switch(m_DlgType)
	{
	case CheckOut:
		{
			// Turn CM-IDC POWER switch on
			return STEP_SUCCESSFUL;
		}
	case Tensiometer:
		{
			return STEP_SUCCESSFUL;

		}
	}
}

int CCheckOutDlg::Step14()
{

	switch(m_DlgType)
	{
	case CheckOut:
		{
			// Turn CM-IDC POWER switch on
			return STEP_SUCCESSFUL;
		}
	case Tensiometer:
		{
			return STEP_SUCCESSFUL;

		}
	}
}

int CCheckOutDlg::Step15()
{

	switch(m_DlgType)
	{
	case CheckOut:
		{
			// Turn CM-IDC POWER switch on
			return STEP_SUCCESSFUL;
		}
	case Tensiometer:
		{
			return STEP_SUCCESSFUL;

		}
	}
}

int CCheckOutDlg::Step16()
{

	switch(m_DlgType)
	{
	case CheckOut:
		{
			// Turn CM-IDC POWER switch on
			return STEP_SUCCESSFUL;
		}
	case Tensiometer:
		{
			return STEP_SUCCESSFUL;

		}
	}
}

int CCheckOutDlg::Step17()
{

	switch(m_DlgType)
	{
	case CheckOut:
		{
			// Turn CM-IDC POWER switch on
			return STEP_SUCCESSFUL;
		}
	case Tensiometer:
		{
			return STEP_SUCCESSFUL;

		}
	}
}

int CCheckOutDlg::Step18()
{

	switch(m_DlgType)
	{
	case CheckOut:
		{
			// Turn CM-IDC POWER switch on
			return STEP_SUCCESSFUL;
		}
	case Tensiometer:
		{
			return STEP_SUCCESSFUL;

		}
	}
}


/////////////////////////////////////////////////////////////////////////////
// CCheckOutDlg dialog

CCheckOutDlg::CCheckOutDlg(CheckOutType whatType, CLADAControlModuleDoc * doc, CWnd* pParent /*=NULL*/)
	: CDialog(CCheckOutDlg::IDD, pParent)
{
	m_DlgType = whatType;
	//{{AFX_DATA_INIT(CCheckOutDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	pDoc = doc;
	m_Bitmap = NULL;
	m_Palette = NULL;

	m_Function[0] = &Step1;
	m_Function[1] = &Step2;
	m_Function[2] = &Step3;
	m_Function[3] = &Step4;
	m_Function[4] = &Step5;
	m_Function[5] = &Step6;
	m_Function[6] = &Step7;
	m_Function[7] = &Step8;
	m_Function[8] = &Step9;
	m_Function[9] = &Step10;
	m_Function[10] = &Step11;
	m_Function[11] = &Step12;
	m_Function[12] = &Step13;
	m_Function[13] = &Step14;
	m_Function[14] = &Step15;
	m_Function[15] = &Step16;
	m_Function[16] = &Step17;
	m_Function[17] = &Step18;

	m_wPage = 0;
	m_curStep = 0;

	for (int i = 0; i < MAX_STEPS; i++)
		PictureName[i] = "No Picture";
	

	switch (m_DlgType)
	{
	case CheckOut:
		{
			print = new CCheckout();
			m_TotalSteps = 7;
		} break;
	case Tensiometer:
		{
			m_TotalSteps = 18;
		} break;
	}
}

CCheckOutDlg::~CCheckOutDlg()
{
	switch (m_DlgType)
	{
	case CheckOut:
		{
			delete print;
			print = NULL;
		} break;
	case Tensiometer:
		{
			m_TotalSteps = 14;
		} break;
	}

	delete m_Palette;
	delete m_Bitmap;
}

void CCheckOutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCheckOutDlg)
	DDX_Control(pDX, IDC_PICTURE, m_CPicture);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCheckOutDlg, CDialog)
	//{{AFX_MSG_MAP(CCheckOutDlg)
	ON_BN_CLICKED(ID_NEXT, OnNext)
	ON_BN_CLICKED(ID_BACK, OnBack)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(IDC_CHECK1,IDC_CHECK9,OnCheckBox)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCheckOutDlg message handlers

void CCheckOutDlg::OnNext() 
{
	// TODO: Add your control notification handler code here
	if (m_curStep == m_TotalSteps && (m_wPage == (m_TotalSteps - 1) / 9))
	{
		RestoreStrings(); // restore any temporary strings
		EndDialog(IDOK);
	}
	else
	{
		m_wPage++;
		PreparePage();
	}
}

void CCheckOutDlg::OnBack() 
{
	// TODO: Add your control notification handler code here
	m_wPage--;
	//m_curStep = m_wPage * 9 + 9;
	PreparePage();
}

BOOL CCheckOutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	for (int i = 0; i < 9; i++)
	{
		GetDlgItem(IDC_CHECK1 + i)->SetFont(&RussianArial);
	}
	SetFont(&RussianArial);
	GetDlgItem(IDC_STEP)->SetFont(&RussianArial);
	GetDlgItem(IDC_STEP_NUM)->SetFont(&RussianArial);
	GetDlgItem(IDC_TEXT)->SetFont(&RussianArial);
	GetDlgItem(IDC_TEXT1)->SetFont(&RussianArial);
	GetDlgItem(ID_BACK)->SetFont(&RussianArial);
	GetDlgItem(ID_NEXT)->SetFont(&RussianArial);
	GetDlgItem(ID_HELP)->SetFont(&RussianArial);
	
	switch (m_DlgType)
	{
	case CheckOut:
		{
			m_BaseAddressStepTitle = IDS_CO11;
			m_BaseAddressStepDescription = IDS_AB0;
			m_BaseAddressStepString = IDS_CO11;
			m_HasStepTitle = TRUE;
			fillerEnglish = Strings.get(IDS_AB8,ENGLISH);
			fillerRussian = Strings.get(IDS_AB8,RUSSIAN);
			if (MessageBox(IDS_M_AUTOMATIC_CHECK_OUT,IDS_PROGRAM_NAME,MB_YESNO|MB_ICONQUESTION)==IDYES)
				m_IsAutomatic = TRUE;
			else
				m_IsAutomatic = FALSE;

			StartTime=CTime::GetCurrentTime();
			CString temp;
			temp = StartTime.Format("%d.%m.%y");
			print->data[0][1] = temp;
			temp = StartTime.Format(" %H:%M");
			print->data[1][1] = temp;

			fillerEnglish = Strings.get(IDS_AB8,ENGLISH);
			fillerRussian = Strings.get(IDS_AB8,RUSSIAN);

			CompletedFileName = "CheckOut Results " + StartTime.Format("%m-%d-%y %H;%M.txt");
			CString temp1;
			CString temp2;
			wsprintf(temp1.GetBuffer(200), Strings.get(IDS_AB8,ENGLISH).GetBuffer(0), CompletedFileName);
			wsprintf(temp2.GetBuffer(200), Strings.get(IDS_AB8,RUSSIAN).GetBuffer(0), CompletedFileName);
			temp1.ReleaseBuffer();
			temp2.ReleaseBuffer();
			Strings.set(temp1,temp2,IDS_AB8);
			PictureDirectory = "C:\\Windows\\";
			PictureName[0] = "Clouds.bmp";
			PictureName[1] = "Setup.bmp";
			PictureName[2] = "Forest.bmp";
			PictureName[3] = "Gold Weave.bmp";
			PictureName[4] = "Clouds.bmp";
			PictureName[5] = "Forest.bmp";
		} break;
	case Tensiometer:
		{
			m_BaseAddressStepDescription = IDS_TENS_STEP_EXPLANATION_1;
			m_BaseAddressStepString = IDS_TENSIOMETER_STEP_1;
			m_HasStepTitle = FALSE;
			//m_BaseAddressStepTitle = IDS_NO_STRING;
			PictureDirectory = workingDirectory + "\\TensiometerPictures\\";
		}
	}
	
	PreparePage();	
	LoadPicture();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CCheckOutDlg::OnCheckBox(UINT nID)
{
	static int nSuccessiveFailures = 0;
	// determine if check was placed or removed...
	int checkNumber = nID - IDC_CHECK1;

	if (((CButton*)GetDlgItem(nID))->GetCheck())
	{   // check placed
		int prevStep = m_curStep;
		m_curStep = m_wPage * 9 + checkNumber;
		int returnValue;
		
		returnValue = ((*m_Function[m_curStep]))();
				
		if (returnValue == STEP_SUCCESSFUL)
			nSuccessiveFailures = 0;
		else
		{
			nSuccessiveFailures++;
			pDoc->m_ErrorFiles->WriteHistory(IDS_C_CHECK_OUT_STEP_FAILED, m_BaseAddressStepString +m_curStep);
		}

		if (returnValue == STEP_SUCCESSFUL)
		{
			m_curStep++;
			// if m_curStep = last step, enable next or finish

			if (m_curStep == m_TotalSteps) // last step overall
			{
				GetDlgItem(IDC_STEP_NUM)->SetWindowText("-");
				GetDlgItem(IDC_TEXT)->SetWindowText("");
				GetDlgItem(IDC_TEXT1)->SetWindowText(Strings.get(IDS_ALL_STEPS_COMPLETE));
				GetDlgItem(ID_NEXT)->EnableWindow(TRUE);	
			}
			else if (m_curStep % 9 == 0) // last step on current page
			{
				GetDlgItem(IDC_STEP_NUM)->SetWindowText("-");
				GetDlgItem(IDC_TEXT)->SetWindowText("");
				GetDlgItem(IDC_TEXT1)->SetWindowText(Strings.get(IDS_STEPS_COMPLETE));		
				GetDlgItem(ID_NEXT)->EnableWindow(TRUE);
			}
			else
			{
			// enable next check mark
				GetDlgItem(nID+1)->EnableWindow(TRUE);
				LoadPicture();
				SetStepText();
			}
			if (m_curStep < prevStep)
				m_curStep = prevStep;
		}
		else if (returnValue == STEP_FAILED)
		{
			((CButton*)GetDlgItem(nID))->SetCheck(0);
			// else, remove check mark
		}
		else //(returnValue == CHECK_OUT_FAILED )
		{
			((CButton*)GetDlgItem(nID))->SetCheck(0);
		}

		if (m_IsAutomatic && nSuccessiveFailures < 2 && returnValue != CHECK_OUT_FAILED)
		{
			
			if (m_curStep == m_TotalSteps)
				OnNext();
			else if (m_curStep % 9 == 0 && m_wPage < (m_curStep / 9))
				OnNext();
			
			if (m_curStep > 1)
			SetTimer(1,1000,NULL);

			
		}
		else if (m_IsAutomatic)  // nSuccessiveFailures == 2
		{
			m_IsAutomatic = FALSE;
			pDoc->m_ErrorFiles->WriteHistory(IDS_C_CHECK_OUT_FAILED, m_BaseAddressStepString + m_curStep);
			MessageBox(IDS_C_CHECK_OUT_FAILED,IDS_PROGRAM_NAME,MB_ICONSTOP);
			RestoreStrings();
			EndDialog(IDABORT);
		}

	}
	else
	{
	// check removed
		// removed all checks inbetween curstep and new step
		// curStep = step which was removed
		int prevStep = m_curStep;
		m_curStep = m_wPage * 9 + checkNumber;
		SetStepText();
		if (m_curStep < prevStep)
			m_curStep = prevStep;
	}

}

void CCheckOutDlg::PreparePage()
{
	int wBox = 0;
	int curStepAtTop = m_wPage * 9;
	// display text in all boxes
	for (int i = curStepAtTop; i < curStepAtTop + 9 && i < m_TotalSteps; i++)
	{
		GetDlgItem(IDC_CHECK1 + wBox)->EnableWindow(i <= m_curStep);
		GetDlgItem(IDC_CHECK1 + wBox)->ShowWindow(SW_SHOW);
		((CButton*)GetDlgItem(IDC_CHECK1 + wBox))->SetCheck(m_curStep > i);
		wBox++;
	}
	
	// back should be enabled if the top step is greater than 0...
	GetDlgItem(ID_BACK)->EnableWindow(curStepAtTop > 0);
	
	for (; i < curStepAtTop + 9; i++)
	{
		GetDlgItem(IDC_CHECK1 + wBox)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK1 + wBox)->ShowWindow(SW_HIDE);
		wBox++;
	}
	GetDlgItem(ID_NEXT)->EnableWindow(m_curStep >= curStepAtTop + 9);
	SetStrings();
	
	// place text in first instruction

	// set first picture


}

void CCheckOutDlg::SetStrings()
{
	int curStepAtTop = m_wPage * 9;
	GetDlgItem(ID_BACK)->SetWindowText(Strings.get(IDS_BACK));
	
	if (m_TotalSteps - curStepAtTop < 10) // means finish should be set
		GetDlgItem(ID_NEXT)->SetWindowText(Strings.get(IDS_FINISH));
	else // means next should be set
		GetDlgItem(ID_NEXT)->SetWindowText(Strings.get(IDS_NEXT));

	int wBox = 0;
	for (int i = curStepAtTop; i < curStepAtTop + 9 && i < m_TotalSteps; i++)
	{
		GetDlgItem(IDC_CHECK1 + wBox)->SetWindowText(Strings.get(m_BaseAddressStepString + i));
		wBox++;
	}
	
	if (m_curStep == m_TotalSteps)
	{
		GetDlgItem(IDC_STEP_NUM)->SetWindowText("-");
		GetDlgItem(IDC_TEXT)->SetWindowText("");
		GetDlgItem(IDC_TEXT1)->SetWindowText(Strings.get(IDS_ALL_STEPS_COMPLETE));
		GetDlgItem(ID_NEXT)->EnableWindow(TRUE);	
	}
	else if (m_curStep >= curStepAtTop + 9)
	{
		GetDlgItem(IDC_STEP_NUM)->SetWindowText("-");
		GetDlgItem(IDC_TEXT)->SetWindowText("");
		GetDlgItem(IDC_TEXT1)->SetWindowText(Strings.get(IDS_STEPS_COMPLETE));		
	}	
	else
		SetStepText();	
	
}

void CCheckOutDlg::SetStepText()
{
	//int lastStepThisPage = 
	GetDlgItem(IDC_STEP)->SetWindowText(Strings.get(IDS_CHECK_OUT_STEP));
	GetDlgItem(IDC_STEP_NUM)->SetWindowText(IntToString(m_curStep+1));
	if (m_HasStepTitle)
		GetDlgItem(IDC_TEXT)->SetWindowText(Strings.get(m_BaseAddressStepTitle + m_curStep));
	GetDlgItem(IDC_TEXT1)->SetWindowText(Strings.get(m_BaseAddressStepDescription + m_curStep));
}

BOOL CCheckOutDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_F2)
	{
		Strings.ToggleLanguage();
		SetStrings();
		return TRUE;
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == 13)
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}

void CCheckOutDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 1)
	{
		// go to next step
		KillTimer(1);
		int CheckID = m_curStep - m_wPage * 9 + IDC_CHECK1;
		((CButton*)GetDlgItem(CheckID))->SetCheck(1);
		OnCheckBox( CheckID );

	}
	//CDialog::OnTimer(nIDEvent);
}


void CCheckOutDlg::RestoreStrings()
{
	if (m_DlgType == CheckOut)
		Strings.set(fillerEnglish,fillerRussian,IDS_AB8);
}

void CCheckOutDlg::LoadPicture()
{
	if (PictureName[m_curStep] != "No Picture")
	{
		delete m_Palette;
		m_Palette = new CPalette;
		delete m_Bitmap;
		m_Bitmap = new CBitmap;
		LoadBMPImage(PictureDirectory + PictureName[m_curStep],*m_Bitmap,m_Palette);
		m_CPicture.SetBitmap((HBITMAP)*m_Bitmap);
	}
}
