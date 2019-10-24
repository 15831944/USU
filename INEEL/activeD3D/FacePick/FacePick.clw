; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=FacePickWin
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "facepick.h"
LastPage=0

ClassCount=4
Class1=FacePickApp
Class2=FacePickWin
Class3=RMApp
Class4=RMWin

ResourceCount=2
Resource1=IDR_MAINMENU
Resource2=IDD_HELPDIALOG

[CLS:FacePickApp]
Type=0
BaseClass=RMApp
HeaderFile=FacePickApp.h
ImplementationFile=FacePickApp.cpp
LastObject=FacePickApp

[CLS:FacePickWin]
Type=0
BaseClass=RMWin
HeaderFile=FacePickWin.h
ImplementationFile=FacePickWin.cpp
LastObject=ID_COLORS_MESH

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
Class=FacePickWin
Command1=ID_FILE_OPEN
Command2=ID_FILE_SAVE
Command3=ID_APP_EXIT
Command4=ID_RENDER_WIREFRAME
Command5=ID_RENDER_UNLIT
Command6=ID_RENDER_FLAT
Command7=ID_RENDER_GOURAUD
Command8=ID_RENDER_PHONG
Command9=ID_COLORS_FACE
Command10=ID_COLORS_MESH
Command11=ID_HELP_ABOUT
CommandCount=11

[DLG:IDD_HELPDIALOG]
Type=1
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342181379
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352

