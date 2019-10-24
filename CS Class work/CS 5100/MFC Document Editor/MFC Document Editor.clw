; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCloseDialog
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MFC Document Editor.h"
LastPage=0

ClassCount=7
Class1=CMFCDocumentEditorApp
Class2=CMFCDocumentEditorDoc
Class3=CMFCDocumentEditorView
Class4=CMainFrame

ResourceCount=6
Resource1=IDR_MFCDOCTYPE_CNTR_IP
Resource2=IDD_DIALOGBAR
Resource3=IDD_ABOUTBOX
Resource4=IDR_MAINFRAME
Class5=CChildFrame
Class6=CAboutDlg
Resource5=IDR_MFCDOCTYPE
Class7=CCloseDialog
Resource6=IDD_CLOSE_WINDOWS

[CLS:CMFCDocumentEditorApp]
Type=0
HeaderFile=MFC Document Editor.h
ImplementationFile=MFC Document Editor.cpp
Filter=N

[CLS:CMFCDocumentEditorDoc]
Type=0
HeaderFile=MFC Document EditorDoc.h
ImplementationFile=MFC Document EditorDoc.cpp
Filter=N
BaseClass=CRichEditDoc
VirtualFilter=DC
LastObject=CMFCDocumentEditorDoc

[CLS:CMFCDocumentEditorView]
Type=0
HeaderFile=MFC Document EditorView.h
ImplementationFile=MFC Document EditorView.cpp
Filter=C
LastObject=CMFCDocumentEditorView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame
BaseClass=CMDIFrameWnd
VirtualFilter=fWC


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M
LastObject=CChildFrame
BaseClass=CMDIChildWnd
VirtualFilter=mfWC


[CLS:CAboutDlg]
Type=0
HeaderFile=MFC Document Editor.cpp
ImplementationFile=MFC Document Editor.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308480

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_MFCDOCTYPE]
Type=1
Class=CMFCDocumentEditorView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_CLOSE_WINDOWS
Command5=ID_FILE_SAVE
Command6=ID_FILE_SAVE_AS
Command7=ID_FILE_PRINT
Command8=ID_FILE_PRINT_PREVIEW
Command9=ID_FILE_PRINT_SETUP
Command10=ID_FILE_MRU_FILE1
Command11=ID_APP_EXIT
Command12=ID_EDIT_UNDO
Command13=ID_EDIT_CUT
Command14=ID_EDIT_COPY
Command15=ID_EDIT_PASTE
Command16=ID_EDIT_PASTE_SPECIAL
Command17=ID_EDIT_SELECT_ALL
Command18=ID_EDIT_FIND
Command19=ID_EDIT_REPEAT
Command20=ID_EDIT_REPLACE
Command21=ID_OLE_INSERT_NEW
Command22=ID_OLE_EDIT_LINKS
Command23=ID_OLE_EDIT_PROPERTIES
Command24=ID_OLE_VERB_FIRST
Command25=ID_VIEW_TOOLBAR
Command26=ID_VIEW_STATUS_BAR
Command27=ID_WINDOW_NEW
Command28=ID_WINDOW_CASCADE
Command29=ID_WINDOW_TILE_HORZ
Command30=ID_WINDOW_ARRANGE
Command31=ID_APP_ABOUT
CommandCount=31

[MNU:IDR_MFCDOCTYPE_CNTR_IP]
Type=1
Class=CMFCDocumentEditorView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_WINDOW_NEW
Command12=ID_WINDOW_CASCADE
Command13=ID_WINDOW_TILE_HORZ
Command14=ID_WINDOW_ARRANGE
CommandCount=14

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_SELECT_ALL
Command10=ID_EDIT_FIND
Command11=ID_EDIT_REPEAT
Command12=ID_EDIT_REPLACE
Command13=ID_OLE_EDIT_PROPERTIES
Command14=ID_EDIT_UNDO
Command15=ID_EDIT_CUT
Command16=ID_EDIT_COPY
Command17=ID_EDIT_PASTE
Command18=ID_NEXT_PANE
Command19=ID_PREV_PANE
Command20=ID_CANCEL_EDIT_CNTR
CommandCount=20

[ACL:IDR_MFCDOCTYPE_CNTR_IP]
Type=1
Class=CMFCDocumentEditorView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_NEXT_PANE
Command6=ID_PREV_PANE
Command7=ID_CANCEL_EDIT_CNTR
CommandCount=7

[DLG:IDD_DIALOGBAR]
Type=1
Class=?
ControlCount=2
Control1=IDC_FONT_COMBO,combobox,1344340227
Control2=IDC_SIZE_BOX,combobox,1344339971

[DLG:IDD_CLOSE_WINDOWS]
Type=1
Class=CCloseDialog
ControlCount=3
Control1=IDOK,button,1476460545
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST1,listbox,1352728843

[CLS:CCloseDialog]
Type=0
HeaderFile=CloseDialog.h
ImplementationFile=CloseDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_LIST1

