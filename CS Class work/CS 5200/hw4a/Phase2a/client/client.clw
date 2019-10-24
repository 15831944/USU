; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CClientDlg
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
LastObject=IDC_ADD_EVENT
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
ControlCount=16
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_ID,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_NAME,edit,1350631552
Control6=IDC_DESC,edit,1350631492
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_NOTE,edit,1350631492
Control10=IDC_STATIC,static,1342308352
Control11=IDC_DATE,edit,1350631552
Control12=IDC_STATIC,static,1342308352
Control13=IDC_DURATION,edit,1350631552
Control14=IDC_STATIC,static,1342308352
Control15=IDC_LOCATION,edit,1350631552
Control16=IDC_STATIC,static,1342308352

[CLS:CAddEventDlg]
Type=0
HeaderFile=AddEventDlg.h
ImplementationFile=AddEventDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CAddEventDlg
VirtualFilter=dWC

[DLG:IDD_EVENT_LIST]
Type=1
Class=CEventListDlg
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDC_START,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_END,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_QUERY,button,1342242816
Control7=IDC_LIST,edit,1350631552
Control8=IDC_STATIC,static,1342308352

[CLS:CEventListDlg]
Type=0
HeaderFile=EventListDlg.h
ImplementationFile=EventListDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_QUERY

[DLG:IDD_CONFIG_DLG]
Type=1
Class=?
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_FILENAME,edit,1350631552

