; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=HelpDialog
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "cube.h"
LastPage=0

ClassCount=5
Class1=CubeApp
Class2=CubeWin
Class3=RMApp
Class4=RMWin

ResourceCount=2
Resource1=IDR_MAINMENU
Class5=HelpDialog
Resource2=IDD_HELPDIALOG

[CLS:CubeApp]
Type=0
BaseClass=RMApp
HeaderFile=CubeApp.h
ImplementationFile=CubeApp.cpp
LastObject=CubeApp

[CLS:CubeWin]
Type=0
BaseClass=RMWin
HeaderFile=CubeWin.h
ImplementationFile=CubeWin.cpp
LastObject=CubeWin

[CLS:RMApp]
Type=0
BaseClass=CWinApp
HeaderFile=RMapp.h
ImplementationFile=RMapp.cpp

[CLS:RMWin]
Type=0
BaseClass=CFrameWnd
HeaderFile=RMwin.h
ImplementationFile=RMwin.cpp

[MNU:IDR_MAINMENU]
Type=1
Class=CubeWin
Command1=ID_APP_EXIT
Command2=ID_RENDER_WIREFRAME
Command3=ID_RENDER_FLAT
Command4=ID_RENDER_GOURAUD
Command5=ID_RENDER_PHONG
Command6=ID_HELP_ABOUT
CommandCount=6

[DLG:IDD_HELPDIALOG]
Type=1
Class=HelpDialog
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342181379
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352

[CLS:HelpDialog]
Type=0
HeaderFile=HelpDialog.h
ImplementationFile=HelpDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=HelpDialog
VirtualFilter=dWC

