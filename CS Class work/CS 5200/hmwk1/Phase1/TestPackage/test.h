#if !defined(AFX_TEST_H__6A49F862_F2FC_11D4_B4BB_000086204AC6__INCLUDED_)
#define AFX_TEST_H__6A49F862_F2FC_11D4_B4BB_000086204AC6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// test.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// test DAO recordset

class test : public CDaoRecordset
{
public:
	test(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(test)

// Field/Param Data
	//{{AFX_FIELD(test, CDaoRecordset)
	long	m_hitrack_id;
	CString	m_med_id;
	COleDateTime	m_birthdate;
	CString	m_lastname;
	CString	m_firstname;
	CString	m_initial;
	CString	m_hospital;
	CString	m_facility;
	CString	m_sex;
	CString	m_nursery_type;
	CString	m_birthtime;
	CString	m_birth_order;
	long	m_birthwgt_grams;
	long	m_icu_days;
	CString	m_delivery_type;
	COleDateTime	m_discharge_date;
	CString	m_ped_code;
	CString	m_insurance;
	long	m_old_hitrackid;
	CString	m_UniqueID;
	CString	m_changed;
	CString	m_change2;
	CString	m_change3;
	CString	m_notes;
	long	m_finished;
	CString	m_race;
	CString	m_gestation_period;
	CString	m_tracking_assistance;
	CString	m_tracking_flag;
	CString	m_tracking_flag1;
	CString	m_tracking_flag2;
	CString	m_aux_string;
	long	m_aux_number;
	COleDateTime	m_aux_date;
	CString	m_hearing_status;
	CString	m_diag_recommendation;
	long	m_l_mostconc_inpatient;
	long	m_r_mostconc_inpatient;
	long	m_l_mostconc_outpatient;
	long	m_r_mostconc_outpatient;
	BOOL	m_override_mc;
	COleDateTime	m_inpatient_date;
	COleDateTime	m_outpatient_date;
	CString	m_inpatient_head_result;
	CString	m_outpatient_head_result;
	COleDateTime	m_ChangeDate;
	BOOL	m_ei_reffered;
	CString	m_Birth_ID;
	CString	m_stage;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(test)
	public:
	virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(CDaoFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEST_H__6A49F862_F2FC_11D4_B4BB_000086204AC6__INCLUDED_)
