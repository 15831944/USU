; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CServerDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "server.h"

ClassCount=3
Class1=CServerApp
Class2=CServerDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDR_MAINFRAME
Resource2=IDD_SERVER_DIALOG
Resource3=IDD_CONFIG_DLG

[CLS:CServerApp]
Type=0
HeaderFile=server.h
ImplementationFile=server.cpp
Filter=N

[CLS:CServerDlg]
Type=0
HeaderFile=serverDlg.h
ImplementationFile=serverDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_LOG

[CLS:CAboutDlg]
Type=0
HeaderFile=serverDlg.h
ImplementationFile=serverDlg.cpp
Filter=D

[DLG:IDD_SERVER_DIALOG]
Type=1
Class=CServerDlg
ControlCount=5
Control1=IDCANCEL,button,1342242816
Control2=IDC_STOP,button,1342242816
Control3=IDC_START,button,1342242816
Control4=IDC_LOG,edit,1352665092
Control5=IDC_STATIC,static,1342308352

[DLG:IDD_CONFIG_DLG]
Type=1
Class=?
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_FILENAME,edit,1350631552

