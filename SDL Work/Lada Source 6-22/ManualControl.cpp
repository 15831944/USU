// ManualControl.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "ManualControl.h"

#include "LadaStrings.h"
#include "LString.h"
#include "inputlocations.h"

extern LString Strings;

extern UINT MyMessageBox(UINT MessageID, UINT MessageTitleID = NO_TITLE, DWORD mFlags = MB_OK);
#undef MessageBox
#define MessageBox MyMessageBox

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern int round(double &value);
/////////////////////////////////////////////////////////////////////////////
// CManualControl dialog


CManualControl::CManualControl(CLADAControlModuleDoc * doc, CWnd* pParent /*=NULL*/)
	: CDialog(CManualControl::IDD, pParent)
{
	pDoc = doc;
	//{{AFX_DATA_INIT(CManualControl)
	//}}AFX_DATA_INIT
	curChamber = 0;
}	

CManualControl::~CManualControl()
{
	pDoc->m_ptrManualDlg = NULL;
}

void CManualControl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CManualControl)
	DDX_Control(pDX, IDC_FANS, m_CFans);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CManualControl, CDialog)
	//{{AFX_MSG_MAP(CManualControl)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_CHAMBER_A, OnChamberA)
	ON_BN_CLICKED(IDC_CHAMBER_B, OnChamberB)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(IDC_FANS,IDC_APUMP,OnCR10Control)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CManualControl message handlers

void CManualControl::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	EndDialog(IDOK);
	delete pDoc->m_ptrManualDlg;
	//CDialog::OnClose();
}

void CManualControl::OnCR10Control(UINT nID)
{
	CR10ControlType state;
	if (((CButton*)GetDlgItem(nID))->GetCheck()==TRUE)
		state = On;
	else
		state = Off;

	if (!pDoc->commObject)
	{
		((CButton*)GetDlgItem(nID))->SetCheck(state==On?0:1);
		MessageBox(IDS_M_CANT_CONTROL_CR10, IDS_ERROR, MB_OK);
		return;
	}
	
	switch (nID)
	{
	case IDC_FANS:		ControlCR10(NoChange,state);break;
	case IDC_LIGHTS:	ControlCR10(state);
		GetDlgItem(IDC_FANS)->EnableWindow(state);
		if (state==On)
		{
			m_CFans.SetCheck(TRUE);
			//(CButton*)(GetDlgItem(IDC_FANS))->SetCheck(TRUE);
		}
		break;
	case IDC_WATERF:
		{
						GetDlgItem(IDC_WATERB)->EnableWindow( state == On ? FALSE : TRUE);
						ControlCR10(NoChange,NoChange, state == On ? Forward : Off);
		} break;
	case IDC_WATERB:
		{
			
						GetDlgItem(IDC_WATERF)->EnableWindow( state == On ? FALSE : TRUE);
						ControlCR10(NoChange,NoChange, state == On ? Reverse : Off);
		} break;
	case IDC_APUMP:		ControlCR10(NoChange,NoChange,NoChange, state);		break;
	}

	GetDlgItem(nID)->EnableWindow(FALSE);
	if ( nID == IDC_WATERF )
	{
		GetDlgItem(IDC_WATERF)->EnableWindow(FALSE);
		GetDlgItem(IDC_WATERB)->EnableWindow(FALSE);
		if (state == Off)
			SetTimer(IDC_WATERB,5000,NULL);
		SetTimer(IDC_WATERF,5000,NULL);
	}
	if ( nID == IDC_WATERB )
	{
		GetDlgItem(IDC_WATERF)->EnableWindow(FALSE);
		GetDlgItem(IDC_WATERB)->EnableWindow(FALSE);
		if (state == Off)
			SetTimer(IDC_WATERF,5000,NULL);
		SetTimer(IDC_WATERB,5000,NULL);
	}

	SetTimer(nID,5000,NULL);
}

BOOL CManualControl::ControlCR10( CR10ControlType Lights, // = NoChange 
								CR10ControlType Fans,   // = NoChange
								CR10ControlType Pump1,  // = NoChange
								CR10ControlType Pump2)  // = NoChange
{
	BOOL status = pDoc->commObject->ControlCR10(Lights,Fans,Pump1,Pump2,curChamber);
	return status;
}

void CManualControl::SetStrings()
{
	GetDlgItem(IDC_FANS)->SetWindowText(Strings.get(IDS_FANS));//Strings.get(IDS_F4));
	GetDlgItem(IDC_LIGHTS)->SetWindowText(Strings.get(IDS_LIGHTS));//Strings.get(IDS_F5));
	GetDlgItem(IDC_WATERF)->SetWindowText(Strings.get(IDS_WATER_PUMP_F));//Strings.get(IDS_F6));
	GetDlgItem(IDC_WATERB)->SetWindowText(Strings.get(IDS_WATER_PUMP_B));
	GetDlgItem(IDC_APUMP)->SetWindowText(Strings.get(IDS_AIR_PUMP));//Strings.get(IDS_F6));
	GetDlgItem(IDC_CHAMBER_A)->SetWindowText(Strings.get(IDS_CHAMBER_A));
	GetDlgItem(IDC_CHAMBER_B)->SetWindowText(Strings.get(IDS_CHAMBER_B));
}

BOOL CManualControl::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetStrings();
	SetChamberRadio();

	if (pDoc->nGrowthChambers == 2)
		GetDlgItem(IDC_CHAMBER_B)->ShowWindow(SW_SHOW);

	RefreshControls();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CManualControl::OnChamberA() 
{
	curChamber = 0;
	SetChamberRadio();
}

void CManualControl::OnChamberB() 
{
	curChamber = 1;
	SetChamberRadio();
}

void CManualControl::SetChamberRadio()
{
	((CButton *)GetDlgItem(IDC_CHAMBER_A))->SetCheck(curChamber == 0);
	((CButton *)GetDlgItem(IDC_CHAMBER_B))->SetCheck(curChamber == 1);
}

void CManualControl::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	GetDlgItem(nIDEvent)->EnableWindow(TRUE);
	KillTimer(nIDEvent);
}

void CManualControl::RefreshControls()
{
	BOOL Success = FALSE;
	//double oldValue;
	//int location = CHAMBER_1_STATUS;
	
	int statusLocations[4] = { LIGHT_A_STATUS, FAN_A_STATUS, PUMP1_A_STATUS, PUMP2_A_STATUS };
	double returnData[4];
	pDoc->GetInputLocations( statusLocations, 4, returnData, 28 );

	//pDoc->GetInputLocations(&location,1,&oldValue,12);	

	//int ctrlBits = round(oldValue);
			
	//((CButton*)GetDlgItem(IDC_LIGHTS))->SetCheck(ctrlBits & (1<<0));
	//((CButton*)GetDlgItem(IDC_FANS))->SetCheck(ctrlBits & (1<<1));
	((CButton*)GetDlgItem(IDC_LIGHTS))->SetCheck(round(returnData[0]));
	((CButton*)GetDlgItem(IDC_FANS))->SetCheck(round(returnData[1]));
	
	((CButton*)GetDlgItem(IDC_WATERF))->SetCheck(round(returnData[2])==1);
	((CButton*)GetDlgItem(IDC_WATERB))->SetCheck(round(returnData[2])==2);
	((CButton*)GetDlgItem(IDC_APUMP))->SetCheck(round(returnData[3]));

	//if (ctrlBits & (1<<2))
	//{
		// means pump 1 is on, pumping forward or backwards...
		// because only 4 bits are used by the CR10 to represent all states,
		// we do not know which.
		// we will not set the check on this one, unless neither forwards
		// nor backwards is checked.
		// If a check is already in place, we will assume that
		// pump 1 is going forwards.
	//	if ( (((CButton*)GetDlgItem(IDC_WATERF))->GetCheck()==FALSE) &&
	//		 (((CButton*)GetDlgItem(IDC_WATERB))->GetCheck()==FALSE))
	//	{
	//		((CButton*)GetDlgItem(IDC_WATERF))->SetCheck(1);
	//	}
	//}
	//else
	//{
	//	((CButton*)GetDlgItem(IDC_WATERF))->SetCheck(0);
	//	((CButton*)GetDlgItem(IDC_WATERB))->SetCheck(0);
	//}
	//((CButton*)GetDlgItem(IDC_APUMP))->SetCheck(ctrlBits & (1<<3));


}
