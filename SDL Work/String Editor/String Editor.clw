; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CStringEditorApp
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "string editor.h"
LastPage=0

ClassCount=9
Class1=CFind
Class2=CLeftView
Class3=CMainFrame
Class4=CNewStringTableDlg
Class5=CStringEditorApp
Class6=CAboutDlg
Class7=CStringEditorDoc
Class8=CStringEditorView
Class9=StringProperties

ResourceCount=7
Resource1=IDR_RIGHTPOPUP
Resource2=IDR_MAINFRAME
Resource3=IDD_NEWSTRINGTABLE
Resource4=IDD_CFIND
Resource5=IDD_ABOUTBOX
Resource6=IDD_PROPERTIES
Resource7=IDD_MERGE

[CLS:CFind]
Type=0
BaseClass=CDialog
HeaderFile=Find.h
ImplementationFile=Find.cpp

[CLS:CLeftView]
Type=0
BaseClass=CTreeView
HeaderFile=LeftView.h
ImplementationFile=LeftView.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:CNewStringTableDlg]
Type=0
BaseClass=CDialog
HeaderFile=NewStringTableDlg.h
ImplementationFile=NewStringTableDlg.cpp

[CLS:CStringEditorApp]
Type=0
BaseClass=CWinApp
HeaderFile=String Editor.h
ImplementationFile=String Editor.cpp
Filter=N
VirtualFilter=AC
LastObject=IDC_MERGE

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=String Editor.cpp
ImplementationFile=String Editor.cpp
LastObject=CAboutDlg

[CLS:CStringEditorDoc]
Type=0
BaseClass=CDocument
HeaderFile=String EditorDoc.h
ImplementationFile=String EditorDoc.cpp
LastObject=CStringEditorDoc

[CLS:CStringEditorView]
Type=0
BaseClass=CListView
HeaderFile=String EditorView.h
ImplementationFile=String EditorView.cpp
LastObject=CStringEditorView

[CLS:StringProperties]
Type=0
BaseClass=CDialog
HeaderFile=StringProperties.h
ImplementationFile=StringProperties.cpp

[DLG:IDD_CFIND]
Type=1
Class=CFind
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_CHECK1,button,1342242819
Control5=IDC_CHECK2,button,1342242819
Control6=IDC_STATIC,static,1342308352

[DLG:IDD_NEWSTRINGTABLE]
Type=1
Class=CNewStringTableDlg
ControlCount=17
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308864
Control4=IDC_STATIC,static,1342308864
Control5=IDC_CHANGEFONT,button,1342242816
Control6=IDC_STATIC,static,1342308864
Control7=IDC_NLANGUAGES,edit,1350631552
Control8=IDC_LNUMBER,edit,1350631552
Control9=IDC_SPIN1,msctls_updown32,1342177334
Control10=IDC_STATIC,static,1342308352
Control11=IDC_LNAME,edit,1350631552
Control12=IDC_STATIC,button,1342177287
Control13=IDC_STATIC,static,1342308864
Control14=IDC_STATIC,static,1342308864
Control15=IDC_FONTNAME,edit,1350633600
Control16=IDC_FSIZE,edit,1350633600
Control17=IDC_STATIC,button,1342177287

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_PROPERTIES]
Type=1
Class=StringProperties
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDC_ID,edit,1350631552
Control3=IDC_EL1,edit,1352728644
Control4=IDC_STATIC,static,1342308864
Control5=IDC_L1,static,1342308352
Control6=IDC_LNEXT,button,1342242816
Control7=IDC_LPREV,button,1342242816

[DLG:IDR_MAINFRAME]
Type=1
Class=?
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=IDC_MERGE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_APP_ABOUT
CommandCount=17

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_RIGHTPOPUP]
Type=1
Class=?
Command1=ID_EDIT_CUT
Command2=ID_EDIT_COPY
Command3=ID_PASTE
Command4=ID_DELETE
Command5=ID_NEWSTRING
Command6=ID_PROPERTIES
CommandCount=6

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_EDIT_FIND
Command3=ID_FILE_NEW
Command4=ID_FILE_OPEN
Command5=ID_FILE_PRINT
Command6=ID_FILE_SAVE
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_NEXT_PANE
Command11=ID_PREV_PANE
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_EDIT_CUT
Command15=ID_EDIT_UNDO
CommandCount=15

[DLG:IDD_MERGE]
Type=1
Class=?
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT1,edit,1350631552
Control6=IDC_EDIT2,edit,1350633600

