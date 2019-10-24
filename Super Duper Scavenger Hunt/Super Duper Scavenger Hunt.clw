; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSuperDuperScavengerHuntDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Super Duper Scavenger Hunt.h"

ClassCount=5
Class1=CSuperDuperScavengerHuntApp
Class2=CSuperDuperScavengerHuntDlg

ResourceCount=5
Resource2=IDD_INSTRUCTIONS1
Resource1=IDR_MAINFRAME
Class3=CWelcome
Resource3=IDD_WELCOME
Resource4=IDD_SUPERDUPERSCAVENGERHUNT_DIALOG
Class4=CInstructions1Dlg
Class5=CInstructions2Dlg
Resource5=IDD_INSTRUCTIONS2

[CLS:CSuperDuperScavengerHuntApp]
Type=0
HeaderFile=Super Duper Scavenger Hunt.h
ImplementationFile=Super Duper Scavenger Hunt.cpp
Filter=N

[CLS:CSuperDuperScavengerHuntDlg]
Type=0
HeaderFile=Super Duper Scavenger HuntDlg.h
ImplementationFile=Super Duper Scavenger HuntDlg.cpp
Filter=D
LastObject=CSuperDuperScavengerHuntDlg
BaseClass=CDialog
VirtualFilter=dWC



[DLG:IDD_SUPERDUPERSCAVENGERHUNT_DIALOG]
Type=1
Class=CSuperDuperScavengerHuntDlg
ControlCount=16
Control1=IDC_ANSWER,edit,1350631552
Control2=IDC_ANSWER_TEXT,static,1342308864
Control3=IDC_STATIC,static,1342308864
Control4=IDC_TEXT1,static,1342308864
Control5=IDC_TEXT2,static,1342308864
Control6=IDC_TEXT3,static,1342308864
Control7=IDC_TEXT4,static,1342308864
Control8=IDC_TEXT5,static,1342308864
Control9=IDC_BUTTON1,button,1342242817
Control10=IDC_RIDDLE_TEXT,static,1342308352
Control11=IDC_BUTTON2,button,1342242816
Control12=IDC_DIRECTION_TEXT,static,1342308864
Control13=IDC_LOCATION,static,1342308352
Control14=IDC_TIME_LEFT,static,1342308864
Control15=IDC_HEADING,static,1342308864
Control16=IDC_DISTANCE,static,1342308864

[DLG:IDD_WELCOME]
Type=1
Class=CWelcome
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352

[CLS:CWelcome]
Type=0
HeaderFile=Welcome.h
ImplementationFile=Welcome.cpp
BaseClass=CDialog
Filter=D
LastObject=CWelcome

[DLG:IDD_INSTRUCTIONS1]
Type=1
Class=CInstructions1Dlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352

[DLG:IDD_INSTRUCTIONS2]
Type=1
Class=CInstructions2Dlg
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[CLS:CInstructions1Dlg]
Type=0
HeaderFile=Instructions1Dlg.h
ImplementationFile=Instructions1Dlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CInstructions1Dlg

[CLS:CInstructions2Dlg]
Type=0
HeaderFile=Instructions2Dlg.h
ImplementationFile=Instructions2Dlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CInstructions2Dlg

