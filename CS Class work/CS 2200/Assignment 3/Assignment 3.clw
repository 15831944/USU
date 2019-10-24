; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAssignment3Dlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Assignment 3.h"

ClassCount=3
Class1=CAssignment3App
Class2=CAssignment3Dlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_ASSIGNMENT3_DIALOG
Resource4=IDR_MENU1

[CLS:CAssignment3App]
Type=0
HeaderFile=Assignment 3.h
ImplementationFile=Assignment 3.cpp
Filter=N

[CLS:CAssignment3Dlg]
Type=0
HeaderFile=Assignment 3Dlg.h
ImplementationFile=Assignment 3Dlg.cpp
Filter=D
LastObject=ID_EDIT_UPDATERECORD
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=Assignment 3Dlg.h
ImplementationFile=Assignment 3Dlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_ASSIGNMENT3_DIALOG]
Type=1
Class=CAssignment3Dlg
ControlCount=21
Control1=IDC_SAVE,button,1342242816
Control2=IDC_FIRST_NAME,edit,1350631552
Control3=IDC_STATIC,static,1342308864
Control4=IDC_STATIC,static,1342308864
Control5=IDC_STATIC,static,1342308864
Control6=IDC_STATIC,static,1342308864
Control7=IDC_LAST_NAME,edit,1350631552
Control8=IDC_PHONE_NUMBER,edit,1350631552
Control9=IDC_BIRTH_DATE,edit,1350631552
Control10=IDC_STATIC,static,1342308864
Control11=IDC_STREET1,edit,1350631552
Control12=IDC_STREET2,edit,1350631552
Control13=IDC_STATIC,static,1342308864
Control14=IDC_STATIC,button,1342177287
Control15=IDC_ADD_RECORD,button,1342242817
Control16=IDC_REMOVE,button,1342242816
Control17=IDC_UPDATE_RECORD,button,1342242816
Control18=IDC_OPEN,button,1342242816
Control19=IDC_NAMES,SysListView32,1350631437
Control20=IDC_SAVEAS,button,1342242816
Control21=IDC_EXIT,button,1342242816

[MNU:IDR_MENU1]
Type=1
Class=CAssignment3Dlg
Command1=ID_FILE_OPEN
Command2=ID_FILE_SAVEAS
Command3=ID_FILE_SAVE
Command4=ID_FILE_EXIT
Command5=ID_EDIT_ADDRECORD
Command6=ID_EDIT_UPDATERECORD
Command7=ID_EDIT_REMOVERECORD
CommandCount=7

