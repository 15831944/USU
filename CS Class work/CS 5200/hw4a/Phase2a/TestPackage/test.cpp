// test.cpp : implementation file
//

#include "stdafx.h"
#include "TestPackage.h"
#include "test.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// test

IMPLEMENT_DYNAMIC(test, CDaoRecordset)

test::test(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(test)
	m_hitrack_id = 0;
	m_med_id = _T("");
	m_birthdate = (DATE)0;
	m_lastname = _T("");
	m_firstname = _T("");
	m_initial = _T("");
	m_hospital = _T("");
	m_facility = _T("");
	m_sex = _T("");
	m_nursery_type = _T("");
	m_birthtime = _T("");
	m_birth_order = _T("");
	m_birthwgt_grams = 0;
	m_icu_days = 0;
	m_delivery_type = _T("");
	m_discharge_date = (DATE)0;
	m_ped_code = _T("");
	m_insurance = _T("");
	m_old_hitrackid = 0;
	m_UniqueID = _T("");
	m_changed = _T("");
	m_change2 = _T("");
	m_change3 = _T("");
	m_notes = _T("");
	m_finished = 0;
	m_race = _T("");
	m_gestation_period = _T("");
	m_tracking_assistance = _T("");
	m_tracking_flag = _T("");
	m_tracking_flag1 = _T("");
	m_tracking_flag2 = _T("");
	m_aux_string = _T("");
	m_aux_number = 0;
	m_aux_date = (DATE)0;
	m_hearing_status = _T("");
	m_diag_recommendation = _T("");
	m_l_mostconc_inpatient = 0;
	m_r_mostconc_inpatient = 0;
	m_l_mostconc_outpatient = 0;
	m_r_mostconc_outpatient = 0;
	m_override_mc = FALSE;
	m_inpatient_date = (DATE)0;
	m_outpatient_date = (DATE)0;
	m_inpatient_head_result = _T("");
	m_outpatient_head_result = _T("");
	m_ChangeDate = (DATE)0;
	m_ei_reffered = FALSE;
	m_Birth_ID = _T("");
	m_stage = _T("");
	m_nFields = 49;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}


CString test::GetDefaultDBName()
{
	return _T("D:\\swc\\Infant Hearing\\TestData\\HTStateData\\HiTrack.mdb");
}

CString test::GetDefaultSQL()
{
	return _T("[baby]");
}

void test::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(test)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Long(pFX, _T("[hitrack_id]"), m_hitrack_id);
	DFX_Text(pFX, _T("[med_id]"), m_med_id);
	DFX_DateTime(pFX, _T("[birthdate]"), m_birthdate);
	DFX_Text(pFX, _T("[lastname]"), m_lastname);
	DFX_Text(pFX, _T("[firstname]"), m_firstname);
	DFX_Text(pFX, _T("[initial]"), m_initial);
	DFX_Text(pFX, _T("[hospital]"), m_hospital);
	DFX_Text(pFX, _T("[facility]"), m_facility);
	DFX_Text(pFX, _T("[sex]"), m_sex);
	DFX_Text(pFX, _T("[nursery_type]"), m_nursery_type);
	DFX_Text(pFX, _T("[birthtime]"), m_birthtime);
	DFX_Text(pFX, _T("[birth_order]"), m_birth_order);
	DFX_Long(pFX, _T("[birthwgt_grams]"), m_birthwgt_grams);
	DFX_Long(pFX, _T("[icu_days]"), m_icu_days);
	DFX_Text(pFX, _T("[delivery_type]"), m_delivery_type);
	DFX_DateTime(pFX, _T("[discharge_date]"), m_discharge_date);
	DFX_Text(pFX, _T("[ped_code]"), m_ped_code);
	DFX_Text(pFX, _T("[insurance]"), m_insurance);
	DFX_Long(pFX, _T("[old_hitrackid]"), m_old_hitrackid);
	DFX_Text(pFX, _T("[UniqueID]"), m_UniqueID);
	DFX_Text(pFX, _T("[changed]"), m_changed);
	DFX_Text(pFX, _T("[change2]"), m_change2);
	DFX_Text(pFX, _T("[change3]"), m_change3);
	DFX_Text(pFX, _T("[notes]"), m_notes);
	DFX_Long(pFX, _T("[finished]"), m_finished);
	DFX_Text(pFX, _T("[race]"), m_race);
	DFX_Text(pFX, _T("[gestation_period]"), m_gestation_period);
	DFX_Text(pFX, _T("[tracking_assistance]"), m_tracking_assistance);
	DFX_Text(pFX, _T("[tracking_flag]"), m_tracking_flag);
	DFX_Text(pFX, _T("[tracking_flag1]"), m_tracking_flag1);
	DFX_Text(pFX, _T("[tracking_flag2]"), m_tracking_flag2);
	DFX_Text(pFX, _T("[aux_string]"), m_aux_string);
	DFX_Long(pFX, _T("[aux_number]"), m_aux_number);
	DFX_DateTime(pFX, _T("[aux_date]"), m_aux_date);
	DFX_Text(pFX, _T("[hearing_status]"), m_hearing_status);
	DFX_Text(pFX, _T("[diag_recommendation]"), m_diag_recommendation);
	DFX_Long(pFX, _T("[l_mostconc_inpatient]"), m_l_mostconc_inpatient);
	DFX_Long(pFX, _T("[r_mostconc_inpatient]"), m_r_mostconc_inpatient);
	DFX_Long(pFX, _T("[l_mostconc_outpatient]"), m_l_mostconc_outpatient);
	DFX_Long(pFX, _T("[r_mostconc_outpatient]"), m_r_mostconc_outpatient);
	DFX_Bool(pFX, _T("[override_mc]"), m_override_mc);
	DFX_DateTime(pFX, _T("[inpatient_date]"), m_inpatient_date);
	DFX_DateTime(pFX, _T("[outpatient_date]"), m_outpatient_date);
	DFX_Text(pFX, _T("[inpatient_head_result]"), m_inpatient_head_result);
	DFX_Text(pFX, _T("[outpatient_head_result]"), m_outpatient_head_result);
	DFX_DateTime(pFX, _T("[ChangeDate]"), m_ChangeDate);
	DFX_Bool(pFX, _T("[ei_reffered]"), m_ei_reffered);
	DFX_Text(pFX, _T("[Birth_ID]"), m_Birth_ID);
	DFX_Text(pFX, _T("[stage]"), m_stage);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// test diagnostics

#ifdef _DEBUG
void test::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void test::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
