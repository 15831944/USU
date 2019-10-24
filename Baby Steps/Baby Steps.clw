; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Baby Steps.h"
LastPage=0

ClassCount=6
Class1=CBabyStepsApp
Class2=CBabyStepsDoc
Class3=CBabyStepsView
Class4=CMainFrame

ResourceCount=5
Resource1=IDR_POPUP_MENU
Class5=CAboutDlg
Resource2=IDD_ABOUTBOX
Class6=CSimPropertiesDlg
Resource3=IDD_GRID_PROPERTIES
Resource4=IDR_MAINFRAME
Resource5=IDD_DIALOGBAR

[CLS:CBabyStepsApp]
Type=0
HeaderFile=Baby Steps.h
ImplementationFile=Baby Steps.cpp
Filter=N
LastObject=CBabyStepsApp
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CBabyStepsDoc]
Type=0
HeaderFile=Baby StepsDoc.h
ImplementationFile=Baby StepsDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CBabyStepsDoc

[CLS:CBabyStepsView]
Type=0
HeaderFile=Baby StepsView.h
ImplementationFile=Baby StepsView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=CBabyStepsView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=IDC_PAUSE
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=Baby Steps.cpp
ImplementationFile=Baby Steps.cpp
Filter=D

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
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_APP_EXIT
Command6=ID_EDIT_UNDO
Command7=ID_EDIT_CUT
Command8=ID_EDIT_COPY
Command9=ID_EDIT_PASTE
Command10=ID_VIEW_TOOLBAR
Command11=ID_VIEW_STATUS_BAR
Command12=ID_APP_ABOUT
CommandCount=12

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

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_PLAY
Command5=ID_PAUSE
Command6=ID_STOP
Command7=ID_START_STATE
Command8=ID_GOAL_STATE
Command9=ID_OBSTACLE
CommandCount=9

[DLG:IDD_GRID_PROPERTIES]
Type=1
Class=CSimPropertiesDlg
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_N_ROWS,edit,1350631552
Control6=IDC_N_COLUMNS,edit,1350631552

[CLS:CSimPropertiesDlg]
Type=0
HeaderFile=SimPropertiesDlg.h
ImplementationFile=SimPropertiesDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDOK

[MNU:IDR_POPUP_MENU]
Type=1
Class=CBabyStepsView
Command1=ID_POPUP_START
Command2=ID_POPUP_GOAL
Command3=ID_POPUP_OBSTACLE
CommandCount=3

[DLG:IDD_DIALOGBAR]
Type=1
Class=CMainFrame
ControlCount=6
Control1=IDC_NEW,button,1342242827
Control2=IDC_SAVE,button,1342242827
Control3=IDC_OPEN,button,1342242827
Control4=IDC_PLAY,button,1342242827
Control5=IDC_PAUSE,button,1476460555
Control6=IDC_STOP,button,1476460555

