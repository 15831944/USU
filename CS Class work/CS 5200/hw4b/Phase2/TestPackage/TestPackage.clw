; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTestPackageDlg
LastTemplate=CDaoRecordset
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "TestPackage.h"

ClassCount=4
Class1=CTestPackageApp
Class2=CTestPackageDlg
Class3=CAboutDlg

ResourceCount=2
Resource1=IDR_MAINFRAME
Class4=test
Resource2=IDD_TESTPACKAGE_DIALOG

[CLS:CTestPackageApp]
Type=0
HeaderFile=TestPackage.h
ImplementationFile=TestPackage.cpp
Filter=N

[CLS:CTestPackageDlg]
Type=0
HeaderFile=TestPackageDlg.h
ImplementationFile=TestPackageDlg.cpp
Filter=D
LastObject=CTestPackageDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=TestPackageDlg.h
ImplementationFile=TestPackageDlg.cpp
Filter=D

[DLG:IDD_TESTPACKAGE_DIALOG]
Type=1
Class=CTestPackageDlg
ControlCount=27
Control1=IDC_TEST_STRDUP,button,1342242819
Control2=IDC_TEST_DSTRING,button,1342242819
Control3=IDC_TEST_TIMEOFDAY,button,1342242819
Control4=IDC_TEST_CALENDARDATE,button,1342242819
Control5=IDC_TEST_TIMEBLOCK,button,1342242819
Control6=IDC_TEST_RESERVEDTIME,button,1342242819
Control7=IDC_TEST_CALENDAR,button,1342242819
Control8=IDC_TEST_BUILDING,button,1342242819
Control9=IDC_TEST_EVENT,button,1342242819
Control10=IDC_TEST_LOCATION,button,1342242819
Control11=IDC_TEST_USER,button,1342242819
Control12=IDC_TEST_PERSISTENTOBJECTSET,button,1342242819
Control13=IDC_TEST_SOCKADDR,button,1342242819
Control14=IDC_TEST_COMCHANNEL,button,1342242819
Control15=IDC_TEST_SERVER_COM_CHANNEL,button,1342242819
Control16=IDC_TEST_CLIENT_COM_CHANNEL,button,1342242819
Control17=IDC_TEST_CONFIGURATION,button,1342242819
Control18=IDC_TEST_LOGICALCLOCK,button,1342242819
Control19=IDC_TEST_BUTTON,button,1342242816
Control20=IDOK,button,1342242817
Control21=IDC_MESSAGE_LOG,edit,1352728708
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_TEST_MESSAGE,button,1342242819
Control25=IDC_TEST_MEETINGPREFERENCE,button,1342242819
Control26=IDC_TEST_REQUEST,button,1342242819
Control27=IDC_TEST_REPLY,button,1342242819

[CLS:test]
Type=0
HeaderFile=test.h
ImplementationFile=test.cpp
BaseClass=CDaoRecordset
Filter=N
VirtualFilter=x

[DB:test]
DB=1
DBType=DAO
ColumnCount=49
Column1=[hitrack_id], 4, 4
Column2=[med_id], 12, 15
Column3=[birthdate], 11, 8
Column4=[lastname], 12, 20
Column5=[firstname], 12, 10
Column6=[initial], 12, 1
Column7=[hospital], 12, 5
Column8=[facility], 12, 5
Column9=[sex], 12, 1
Column10=[nursery_type], 12, 1
Column11=[birthtime], 12, 8
Column12=[birth_order], 12, 1
Column13=[birthwgt_grams], 4, 4
Column14=[icu_days], 4, 4
Column15=[delivery_type], 12, 1
Column16=[discharge_date], 11, 8
Column17=[ped_code], 12, 4
Column18=[insurance], 12, 2
Column19=[old_hitrackid], 4, 4
Column20=[UniqueID], 12, 20
Column21=[changed], 12, 1
Column22=[change2], 12, 1
Column23=[change3], 12, 1
Column24=[notes], -1, 0
Column25=[finished], 4, 4
Column26=[race], 12, 2
Column27=[gestation_period], 12, 2
Column28=[tracking_assistance], 12, 1
Column29=[tracking_flag], 12, 1
Column30=[tracking_flag1], 12, 1
Column31=[tracking_flag2], 12, 1
Column32=[aux_string], 12, 50
Column33=[aux_number], 4, 4
Column34=[aux_date], 11, 8
Column35=[hearing_status], 12, 50
Column36=[diag_recommendation], 12, 50
Column37=[l_mostconc_inpatient], 4, 4
Column38=[r_mostconc_inpatient], 4, 4
Column39=[l_mostconc_outpatient], 4, 4
Column40=[r_mostconc_outpatient], 4, 4
Column41=[override_mc], -7, 1
Column42=[inpatient_date], 11, 8
Column43=[outpatient_date], 11, 8
Column44=[inpatient_head_result], 12, 1
Column45=[outpatient_head_result], 12, 1
Column46=[ChangeDate], 11, 8
Column47=[ei_reffered], -7, 1
Column48=[Birth_ID], 12, 15
Column49=[stage], 12, 1

