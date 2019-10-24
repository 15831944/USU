; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CChooseItem
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Condition Editor Text.h"

ClassCount=5
Class1=CConditionEditorTextApp
Class2=CConditionEditorTextDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_CONDITIONEDITORTEXT_DIALOG
Class4=EditCondition
Resource4=IDD_EDIT_CONDITION
Class5=CChooseItem
Resource5=IDD_CHOOSE_ITEM

[CLS:CConditionEditorTextApp]
Type=0
HeaderFile=Condition Editor Text.h
ImplementationFile=Condition Editor Text.cpp
Filter=N

[CLS:CConditionEditorTextDlg]
Type=0
HeaderFile=Condition Editor TextDlg.h
ImplementationFile=Condition Editor TextDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_ADD_CONDITION

[CLS:CAboutDlg]
Type=0
HeaderFile=Condition Editor TextDlg.h
ImplementationFile=Condition Editor TextDlg.cpp
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

[DLG:IDD_CONDITIONEDITORTEXT_DIALOG]
Type=1
Class=CConditionEditorTextDlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_ADD_CONDITION,button,1342242816
Control4=IDC_LIST1,listbox,1352728835
Control5=IDC_STATIC,static,1342308352

[DLG:IDD_EDIT_CONDITION]
Type=1
Class=EditCondition
ControlCount=13
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_VARIABLE,combobox,1344339970
Control4=IDC_CONDITIONAL_STATEMENT,edit,1350633600
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDHELP,button,1342242816
Control9=IDC_ITEM_LIST,listbox,1352663297
Control10=IDC_INSERT,button,1342242816
Control11=IDC_SPIN1,msctls_updown32,1342177376
Control12=IDC_DIRECTION_TEXT,static,1342308353
Control13=IDC_DELETE,button,1342242816

[CLS:EditCondition]
Type=0
HeaderFile=EditCondition.h
ImplementationFile=EditCondition.cpp
BaseClass=CDialog
Filter=D
LastObject=EditCondition
VirtualFilter=dWC

[CLS:CChooseItem]
Type=0
HeaderFile=ChooseItem.h
ImplementationFile=ChooseItem.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_COMBO1

[DLG:IDD_CHOOSE_ITEM]
Type=1
Class=CChooseItem
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_COMBO1,combobox,1344274433

