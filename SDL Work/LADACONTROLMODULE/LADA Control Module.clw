; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CLADAControlModuleView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "lada control module.h"
LastPage=0

ClassCount=24
Class1=CCameradialogApp
Class2=CCameradialogDlg
Class3=CChangeLocationDlg
Class4=CChooseLocationsDlg
Class5=CChooseTime
Class6=CColorCheckButton
Class7=CDataTransfer
Class8=CGraphButtonForm
Class9=CGraphDisplayView
Class10=CGraphProperties
Class11=CGraphWindow
Class12=CLADAControlModuleApp
Class13=CAboutDlg
Class14=CLADAControlModuleDoc
Class15=CLADAControlModuleView
Class16=CLADADIAGDlg
Class17=CLADASetupDlg
Class18=CMainFrame
Class19=ProgressDialog
Class20=CProjectSettingsDlg
Class21=CRenameLocationDialog
Class22=CStartDialog

ResourceCount=17
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Resource3=IDR_GRAPHBUTTONFORM_TMPL
Resource4=IDD_LADADIAG_DIALOG
Resource5=IDD_LADASETUP_DIALOG
Resource6=IDD_NEW_PROJECT
Resource7=RENAME_LOCATION
Resource8=IDD_CAMERADIALOG_DIALOG
Resource9=MONITOR_DIALOG
Resource10=IDD_LADACONTROLMODULE_FORM
Resource11=IDD_DATA_TRANSFER
Resource12=IDD_CHOOSE_TIME
Resource13=PROGRESS_DIALOG
Resource14=IDD_GRAPH_PROPERTIES
Resource15=IDD_GRAPHBUTTONFORM_FORM
Class23=CCustomBitmapButton
Resource16=IDD_EDITLOCATION
Class24=CChooseIcon
Resource17=IDD_SELECTICON

[CLS:CCameradialogApp]
Type=0
BaseClass=CWinApp
HeaderFile=cameradialog.h
ImplementationFile=cameradialog.cpp

[CLS:CCameradialogDlg]
Type=0
BaseClass=CDialog
HeaderFile=cameradialogDlg.h
ImplementationFile=cameradialogDlg.cpp

[CLS:CChangeLocationDlg]
Type=0
BaseClass=CDialog
HeaderFile=ChangeLocationDlg.h
ImplementationFile=ChangeLocationDlg.cpp

[CLS:CChooseLocationsDlg]
Type=0
BaseClass=CDialog
HeaderFile=ChooseLocationsDialog.h
ImplementationFile=ChooseLocationsDialog.cpp

[CLS:CChooseTime]
Type=0
BaseClass=CDialog
HeaderFile=ChooseTime.h
ImplementationFile=ChooseTime.cpp

[CLS:CColorCheckButton]
Type=0
BaseClass=CButton
HeaderFile=ColorCheckButton.h
ImplementationFile=ColorCheckButton.cpp

[CLS:CDataTransfer]
Type=0
BaseClass=CDialog
HeaderFile=DataTransfer.h
ImplementationFile=DataTransfer.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_PCMCIA

[CLS:CGraphButtonForm]
Type=0
BaseClass=CFormView
HeaderFile=GraphButtonForm.h
ImplementationFile=GraphButtonForm.cpp

[CLS:CGraphDisplayView]
Type=0
BaseClass=CView
HeaderFile=GraphDisplayView.h
ImplementationFile=GraphDisplayView.cpp

[CLS:CGraphProperties]
Type=0
BaseClass=CDialog
HeaderFile=GraphProperties.h
ImplementationFile=GraphProperties.cpp

[CLS:CGraphWindow]
Type=0
BaseClass=CFrameWnd
HeaderFile=GraphWindow.h
ImplementationFile=GraphWindow.cpp

[CLS:CLADAControlModuleApp]
Type=0
BaseClass=CWinApp
HeaderFile=LADA Control Module.h
ImplementationFile=LADA Control Module.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=LADA Control Module.cpp
ImplementationFile=LADA Control Module.cpp
LastObject=CAboutDlg

[CLS:CLADAControlModuleDoc]
Type=0
BaseClass=CDocument
HeaderFile=LADA Control ModuleDoc.h
ImplementationFile=LADA Control ModuleDoc.cpp

[CLS:CLADAControlModuleView]
Type=0
BaseClass=CFormView
HeaderFile=LADA Control ModuleView.h
ImplementationFile=LADA Control ModuleView.cpp
LastObject=CLADAControlModuleView

[CLS:CLADADIAGDlg]
Type=0
BaseClass=CDialog
HeaderFile=LADADIAGDlg.h
ImplementationFile=LADADIAGDlg.cpp

[CLS:CLADASetupDlg]
Type=0
BaseClass=CDialog
HeaderFile=LADASetupDlg.h
ImplementationFile=LADASetupDlg.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
VirtualFilter=fWC
LastObject=CMainFrame

[CLS:ProgressDialog]
Type=0
BaseClass=CDialog
HeaderFile=ProgressDialog.h
ImplementationFile=ProgressDialog.cpp

[CLS:CProjectSettingsDlg]
Type=0
BaseClass=CDialog
HeaderFile=ProjectSettingsDialog.h
ImplementationFile=ProjectSettingsDialog.cpp

[CLS:CRenameLocationDialog]
Type=0
BaseClass=CDialog
HeaderFile=RenameLocationDialog.h
ImplementationFile=RenameLocationDialog.cpp

[CLS:CStartDialog]
Type=0
BaseClass=CDialog
HeaderFile=StartDialog.h
ImplementationFile=StartDialog.cpp

[DLG:IDD_CAMERADIALOG_DIALOG]
Type=1
Class=CCameradialogDlg
ControlCount=13
Control1=IDC_FREQUENCY,combobox,1344339970
Control2=IDC_STATIC,static,1342308864
Control3=IDC_STATIC,static,1342308864
Control4=IDC_RESOLUTION,combobox,1344340226
Control5=IDC_FILEBOX,SysListView32,1350631425
Control6=IDC_PICTURE,static,1342177287
Control7=IDC_CAMERA1,button,1342242816
Control8=IDC_CAMERA2,button,1342242816
Control9=IDC_STATIC,static,1342308352
Control10=IDC_SPIN1,msctls_updown32,1342177314
Control11=IDC_TVALUE,edit,1350631552
Control12=IDC_SAVE,button,1476460544
Control13=IDC_CLEAR,button,1476460544

[DLG:IDD_EDITLOCATION]
Type=1
Class=CChangeLocationDlg
ControlCount=9
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308864
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_STATIC,static,1342308864
Control5=IDC_EDIT2,edit,1350631552
Control6=IDC_EDIT3,edit,1350631552
Control7=IDC_STATIC,static,1342308864
Control8=IDC_SETVALUE,button,1342242816
Control9=IDC_GETVALUE,button,1342242816

[DLG:MONITOR_DIALOG]
Type=1
Class=CChooseLocationsDlg
ControlCount=17
Control1=IDC_A_LOCATIONS,listbox,1352728841
Control2=IDC_TEXT3,static,1342312449
Control3=IDC_S_LOCATIONS,listbox,1352728841
Control4=IDC_INSERT,button,1342242816
Control5=IDC_REMOVE,button,1342242816
Control6=IDC_TEXT4,static,1342312449
Control7=IDC_RENAME_LOCATION,button,1342254848
Control8=IDOK,button,1342242817
Control9=IDCANCEL,button,1342242816
Control10=IDC_SORT_LOCATIONS,button,1342254848
Control11=IDC_FSL_FILE,button,1342254848
Control12=IDC_TEXT1,static,1342308864
Control13=IDC_N_LOCATIONS,edit,1350633600
Control14=IDC_SELECT_ALLI,button,1342254336
Control15=IDC_SELECT_ALLS,button,1342251776
Control16=IDC_WHICH_GRAPH,combobox,1210122243
Control17=IDC_TEXT2,static,1073873408

[DLG:IDD_CHOOSE_TIME]
Type=1
Class=CChooseTime
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_DATETIMEPICKER1,SysDateTimePick32,1342242848
Control4=IDC_DATETIMEPICKER2,SysDateTimePick32,1342242857
Control5=IDC_TEXT1,static,1342308353
Control6=IDC_TEXT2,static,1342308352
Control7=IDC_TEXT3,static,1342308352

[DLG:IDD_DATA_TRANSFER]
Type=1
Class=CDataTransfer
ControlCount=27
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308866
Control4=IDC_SOURCE_FOLDER,edit,1350633600
Control5=IDC_DESTINATION_FOLDER,edit,1350631552
Control6=IDC_SET_DEFAULT,button,1342242816
Control7=IDC_ALL_FILES,button,1342177284
Control8=IDC_NEW_FILES_ONLY,button,1342177284
Control9=IDC_PICTURE_FILES,button,1342242819
Control10=IDC_STATIC,static,1342308866
Control11=IDC_NUM_SELECTED,static,1342308865
Control12=IDC_FLOPPY,button,1342242827
Control13=IDC_PCMCIA,button,1342242827
Control14=IDC_STATIC,static,1342308864
Control15=IDC_OTHER,button,1342242816
Control16=IDC_STATIC,button,1342177287
Control17=IDC_ARCHIVE_FILES,button,1342242819
Control18=IDC_REAL_TIME_FILES,button,1342242819
Control19=IDC_STATIC,button,1342177287
Control20=IDC_STATIC,button,1342177287
Control21=IDC_FILELIST,SysListView32,1350631705
Control22=IDC_DIAGNOSTIC,button,1342242819
Control23=IDC_JPG,button,1342242819
Control24=IDC_DIB,button,1342242819
Control25=IDC_DIBTOJPG,button,1342242816
Control26=IDC_STATIC,static,1342308866
Control27=IDC_TOTAL_BYTES,static,1342308865

[DLG:IDD_GRAPHBUTTONFORM_FORM]
Type=1
Class=CGraphButtonForm
ControlCount=0

[DLG:IDD_GRAPH_PROPERTIES]
Type=1
Class=CGraphProperties
ControlCount=15
Control1=IDOK,button,1342242817
Control2=IDC_TEXT2,button,1342177287
Control3=IDC_TEXT1,static,1342308864
Control4=IDC_DATA_PLOT_FREQ,combobox,1344339971
Control5=IDC_TEXT4,static,1342308864
Control6=IDC_NPOINTS,edit,1350631552
Control7=IDC_VIS_TIME_SPAN,edit,1350633600
Control8=IDC_TEXT6,static,1342308864
Control9=IDC_TEXT5,static,1342308864
Control10=IDC_TEXT3,static,1342308864
Control11=IDC_C_WGRAPH,combobox,1344339971
Control12=IDC_EDIT_LIST,button,1342242816
Control13=IDC_ACTIVE_LIST,SysListView32,1350647809
Control14=IDC_SHOW_GRAPH,button,1342242819
Control15=IDC_STATIC,static,1342308864

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=6
Control1=IDC_STATIC,static,1342177283
Control2=IDC_ABOUT_TEXT_1,static,1342308480
Control3=IDC_ABOUT_TEXT_2,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_ABOUT_TEXT_3,static,1342308352
Control6=IDC_ABOUT_TEXT_4,static,1342308352

[DLG:IDD_LADACONTROLMODULE_FORM]
Type=1
Class=CLADAControlModuleView
ControlCount=34
Control1=IDC_BUTTON2,button,1342242816
Control2=IDC_BUTTON1,button,1342242816
Control3=IDC_BUTTON3,button,1342242816
Control4=IDC_TEXT6,button,1342177287
Control5=IDC_CONNECTED,static,1342177550
Control6=IDC_TEXT1,button,1342177287
Control7=IDC_TEXT2,static,1342308352
Control8=IDC_TEXT3,static,1342308352
Control9=IDC_TEXT4,button,1342177287
Control10=IDC_TEXT5,static,1342308864
Control11=IDC_CR10TIME,static,1342312960
Control12=IDC_BUTTON4,button,1342242816
Control13=IDC_BUTTON5,button,1342242816
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_BUTTON12,button,1342242816
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_EDITDELAY,edit,1350631552
Control24=IDC_STATIC,static,1342308352
Control25=IDC_TW1,edit,1350633600
Control26=IDC_TW2,edit,1350633600
Control27=IDC_TW3,edit,1350633600
Control28=IDC_RETR_TIME,edit,1350633600
Control29=IDC_JTIME,edit,1350633600
Control30=IDC_JTIMEMAX,edit,1350633600
Control31=IDC_KTIME,edit,1350633600
Control32=IDC_KTIMEMAX,edit,1350633600
Control33=IDC_OTIME,edit,1350633600
Control34=IDC_OTIMEMAX,edit,1350633600

[DLG:IDD_LADADIAG_DIALOG]
Type=1
Class=CLADADIAGDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDC_DIAGNOSTICLIST,SysListView32,1350631425
Control3=IDC_START,button,1342242816

[DLG:IDD_LADASETUP_DIALOG]
Type=1
Class=CLADASetupDlg
ControlCount=16
Control1=ID_NEXT,button,1342242817
Control2=ID_BACK,button,1342242816
Control3=ID_HELP,button,1342242816
Control4=IDC_STEP,static,1342308352
Control5=IDC_CHECK1,button,1342242819
Control6=IDC_CHECK2,button,1342242819
Control7=IDC_CHECK3,button,1342242819
Control8=IDC_CHECK4,button,1342242819
Control9=IDC_CHECK5,button,1342242819
Control10=IDC_PICTURE,static,1342179854
Control11=IDC_CHECK6,button,1342242819
Control12=IDC_CHECK7,button,1342242819
Control13=IDC_CHECK8,button,1342242819
Control14=IDC_CHECK9,button,1342242819
Control15=IDC_TITLE,static,1342308352
Control16=IDC_TEXT,button,1342177287

[DLG:PROGRESS_DIALOG]
Type=1
Class=ProgressDialog
ControlCount=4
Control1=IDCANCEL,button,1342242817
Control2=IDC_PROGRESS1,msctls_progress32,1350565889
Control3=IDC_WINDOW_TEXT,static,1342308865
Control4=IDC_PERCENT,static,1342308865

[DLG:IDD_NEW_PROJECT]
Type=1
Class=CProjectSettingsDlg
ControlCount=33
Control1=IDOK,button,1342373888
Control2=IDC_TEXT12,static,1342308864
Control3=IDC_TEXT3,static,1342308864
Control4=IDC_TEXT4,static,1342308864
Control5=IDC_TEXT10,static,1342308864
Control6=IDC_SAVE_FINAL_STORAGE,button,1342242819
Control7=IDC_TEXT11,static,1342308864
Control8=IDC_BY_SIZE,button,1342373897
Control9=IDC_BY_TIME,button,1342373897
Control10=IDC_TEXT13,static,1342308864
Control11=IDC_TEXT6,static,1342308866
Control12=IDC_BROWSE_DATA_FOLDER,button,1342373888
Control13=IDC_DATA_FOLDER,edit,1350762624
Control14=IDC_LOCATION_LIST,listbox,1352859907
Control15=IDC_AVERAGE,button,1342373897
Control16=IDC_ONE_INSTANT,button,1342373897
Control17=IDC_SAVE_PROJECT,edit,1350762624
Control18=IDC_DATA_RETRIEVAL_FREQ,combobox,1344471043
Control19=IDC_GRAPH_PLOT_FREQ,combobox,1344471043
Control20=IDC_SAVE_DATA_FREQ,combobox,1344471043
Control21=IDC_TEXT14,button,1342177287
Control22=IDC_EDIT_LOCATION_LIST,button,1342373888
Control23=IDC_TEXT1,button,1342177287
Control24=IDC_TEXT2,button,1342177287
Control25=IDC_N_BACK_POINTS,combobox,1344471043
Control26=IDC_TEXT7,static,1342308866
Control27=IDC_TEXT9,static,1342308352
Control28=IDC_SIZE_TIME,combobox,1344339971
Control29=IDC_TEXT8,static,1342308866
Control30=IDC_VISIBLE_SPAN,edit,1350568064
Control31=IDC_SAVE_LOCATIONS,button,1342242819
Control32=IDC_TEXT5,static,1342308866
Control33=IDC_N_GRAPHS,combobox,1344471043

[DLG:RENAME_LOCATION]
Type=1
Class=CRenameLocationDialog
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_WIN_TEXT,static,1342308865
Control4=IDC_STATIC,static,1342308865
Control5=IDC_NEW_NAME,edit,1350635520
Control6=IDC_NUMBER,static,1342312961
Control7=IDC_OLD_NAME,static,1342312960
Control8=IDC_STATIC,static,1342308865

[DLG:IDR_MAINFRAME]
Type=1
Class=CStartDialog
ControlCount=2
Control1=IDC_AUTOWRAP,button,1342242819
Control2=IDC_EDITLIST,button,1342242816

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
Command9=ID_CONTEXT_HELP
CommandCount=9

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_SEND_MAIL
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_HELP_FINDER
Command18=ID_APP_ABOUT
CommandCount=18

[MNU:IDR_GRAPHBUTTONFORM_TMPL]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_APP_ABOUT
CommandCount=16

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
Command15=ID_CONTEXT_HELP
Command16=ID_HELP
CommandCount=16

[CLS:CCustomBitmapButton]
Type=0
HeaderFile=CustomBitmapButton.h
ImplementationFile=CustomBitmapButton.cpp
BaseClass=CButton
Filter=W
LastObject=CCustomBitmapButton

[DLG:IDD_SELECTICON]
Type=1
Class=?
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_FLOPPY,button,1342177289
Control4=IDC_PCMCIA,button,1342177289

[CLS:CChooseIcon]
Type=0
HeaderFile=ChooseIcon.h
ImplementationFile=ChooseIcon.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CChooseIcon

