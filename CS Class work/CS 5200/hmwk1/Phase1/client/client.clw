; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CEventListDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "client.h"

ClassCount=4
Class1=CClientApp
Class2=CClientDlg

ResourceCount=5
Resource2=IDD_ADD_EVENT_DLG
Resource1=IDR_MAINFRAME
Class3=CAddEventDlg
Resource3=IDD_CONFIG_DLG
Class4=CEventListDlg
Resource4=IDD_CLIENT_DIALOG
Resource5=IDD_EVENT_LIST

[CLS:CClientApp]
Type=0
HeaderFile=client.h
ImplementationFile=client.cpp
Filter=N

[CLS:CClientDlg]
Type=0
HeaderFile=clientDlg.h
ImplementationFile=clientDlg.cpp
Filter=D
LastObject=CClientDlg
BaseClass=CDialog
VirtualFilter=dWC



[DLG:IDD_CLIENT_DIALOG]
Type=1
Class=CClientDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDC_LIST_EVENTS,button,1342242816
Control3=IDC_ADD_EVENT,button,1342242816
Control4=IDC_STATIC,static,1342308352

[DLG:IDD_ADD_EVENT_DLG]
Type=1
Class=CAddEventDlg
ControlCount=15
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_NAME,edit,1350631552
Control4=IDC_DESC,edit,1350631492
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_NOTE,edit,1350631492
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_DURATION,edit,1350631552
Control11=IDC_STATIC,static,1342308352
Control12=IDC_LOCATION,edit,1350631552
Control13=IDC_STATIC,static,1342308352
Control14=IDC_DATE_PICKER,SysDateTimePick32,1342242848
Control15=IDC_TIME_PICKER,SysDateTimePick32,1342242857

[CLS:CAddEventDlg]
Type=0
HeaderFile=AddEventDlg.h
ImplementationFile=AddEventDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDOK
VirtualFilter=dWC

[DLG:IDD_EVENT_LIST]
Type=1
Class=CEventListDlg
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_QUERY,button,1342242816
Control5=IDC_STATIC,static,1342308352
Control6=IDC_START_DATE,SysDateTimePick32,1342242848
Control7=IDC_END_DATE,SysDateTimePick32,1342242848
Control8=IDC_LIST_VIEW,SysListView32,1350631425

[CLS:CEventListDlg]
Type=0
HeaderFile=EventListDlg.h
ImplementationFile=EventListDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CEventListDlg

[DLG:IDD_CONFIG_DLG]
Type=1
Class=?
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_FILENAME,edit,1350631552

