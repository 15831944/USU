; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDrawingView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Drawing.h"
LastPage=0

ClassCount=7
Class1=CDrawingApp
Class2=CDrawingDoc
Class3=CDrawingView
Class4=CMainFrame

ResourceCount=3
Resource1=IDR_MAINFRAME
Class5=CAboutDlg
Class6=MyButton
Resource2=IDD_ABOUTBOX
Class7=ModelessD
Resource3=IDD_DIALOG1

[CLS:CDrawingApp]
Type=0
HeaderFile=Drawing.h
ImplementationFile=Drawing.cpp
Filter=N

[CLS:CDrawingDoc]
Type=0
HeaderFile=DrawingDoc.h
ImplementationFile=DrawingDoc.cpp
Filter=N

[CLS:CDrawingView]
Type=0
HeaderFile=DrawingView.h
ImplementationFile=DrawingView.cpp
Filter=C
LastObject=CDrawingView
BaseClass=CView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T




[CLS:CAboutDlg]
Type=0
HeaderFile=Drawing.cpp
ImplementationFile=Drawing.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_APP_EXIT
Command2=ID_APP_ABOUT
CommandCount=2

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[CLS:MyButton]
Type=0
HeaderFile=MyButton.h
ImplementationFile=MyButton.cpp
BaseClass=CButton
Filter=W
VirtualFilter=BWC
LastObject=ID_APP_ABOUT

[DLG:IDD_DIALOG1]
Type=1
Class=ModelessD
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352

[CLS:ModelessD]
Type=0
HeaderFile=ModelessD.h
ImplementationFile=ModelessD.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=ID_APP_ABOUT

