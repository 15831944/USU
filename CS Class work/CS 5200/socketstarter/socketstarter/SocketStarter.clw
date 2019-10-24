; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDatagramDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SocketStarter.h"

ClassCount=6
Class1=CSocketStarterApp
Class2=CSocketStarterDlg

ResourceCount=6
Resource2=IDD_DIALOG_ACTIVE
Resource3=IDD_DIALOG_PASSIVE
Resource4=IDD_SOCKETSTARTER_DIALOG
Resource5=IDD_DIALOG_DATAGRAM
Resource1=IDR_MAINFRAME
Class3=CActiveStreamDlg
Class4=CPassiveStreamDlg
Class5=CDatagramDlg
Class6=CWatchDlg
Resource6=IDD_DIALOG_WATCH

[CLS:CSocketStarterApp]
Type=0
HeaderFile=SocketStarter.h
ImplementationFile=SocketStarter.cpp
Filter=N
LastObject=CSocketStarterApp

[CLS:CSocketStarterDlg]
Type=0
HeaderFile=SocketStarterDlg.h
ImplementationFile=SocketStarterDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CSocketStarterDlg


[DLG:IDD_SOCKETSTARTER_DIALOG]
Type=1
Class=CSocketStarterDlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_RADIO_ACTIVE,button,1342308361
Control4=IDC_RADIO_PASSIVE,button,1342177289
Control5=IDC_RADIO_DATAGRAM,button,1342177289

[DLG:IDD_DIALOG_ACTIVE]
Type=1
Class=CActiveStreamDlg
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT_ACTIVEIP,edit,1350631552
Control6=IDC_EDIT_ACTIVEPORT,edit,1350631552
Control7=IDC_EDIT1,edit,1350633600
Control8=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOG_PASSIVE]
Type=1
Class=CPassiveStreamDlg
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_PASSIVEPORT,edit,1350631552
Control5=IDC_ACCEPT_STATUS,edit,1350633600
Control6=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOG_DATAGRAM]
Type=1
Class=CDatagramDlg
ControlCount=11
Control1=IDC_EDIT_DG_LOCALPORT,edit,1350631552
Control2=IDC_EDIT_DG_REMOTEIP,edit,1350631552
Control3=IDC_EDIT_DG_REMOTEPORT,edit,1350631552
Control4=IDOK,button,1342242817
Control5=IDCANCEL,button,1342242816
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,button,1342177287
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT_STATUS,edit,1350633600
Control11=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOG_WATCH]
Type=1
Class=CWatchDlg
ControlCount=8
Control1=IDC_BUTTON_SEND,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT_DATARCVD,edit,1353779396
Control4=IDC_EDIT_DATA2SEND,edit,1350631492
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDIT_STATUS,edit,1350633600
Control8=IDC_STATIC,static,1342308352

[CLS:CActiveStreamDlg]
Type=0
HeaderFile=ActiveStreamDlg.h
ImplementationFile=ActiveStreamDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CActiveStreamDlg

[CLS:CPassiveStreamDlg]
Type=0
HeaderFile=PassiveStreamDlg.h
ImplementationFile=PassiveStreamDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDOK

[CLS:CDatagramDlg]
Type=0
HeaderFile=DatagramDlg.h
ImplementationFile=DatagramDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDIT_DG_REMOTEPORT

[CLS:CWatchDlg]
Type=0
HeaderFile=WatchDlg.h
ImplementationFile=WatchDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDCANCEL

