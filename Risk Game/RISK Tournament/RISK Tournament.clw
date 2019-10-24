; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CGameProcessorThread
LastTemplate=CWinThread
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "RISK Tournament.h"

ClassCount=4
Class1=CRISKTournamentApp
Class2=CRISKTournamentDlg

ResourceCount=3
Resource2=IDD_RISKTOURNAMENT_DIALOG
Resource1=IDR_MAINFRAME
Class3=CTournamentCfgDlg
Class4=CGameProcessorThread
Resource3=IDD_CONFIGURATION_DIALOG

[CLS:CRISKTournamentApp]
Type=0
HeaderFile=RISK Tournament.h
ImplementationFile=RISK Tournament.cpp
Filter=N

[CLS:CRISKTournamentDlg]
Type=0
HeaderFile=RISK TournamentDlg.h
ImplementationFile=RISK TournamentDlg.cpp
Filter=D
LastObject=CRISKTournamentDlg
BaseClass=CDialog
VirtualFilter=dWC



[DLG:IDD_RISKTOURNAMENT_DIALOG]
Type=1
Class=CRISKTournamentDlg
ControlCount=24
Control1=IDC_START_STOP,button,1476460544
Control2=IDC_DLL_LIST,SysListView32,1350631425
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,button,1342177287
Control5=IDC_PROGRESS1,msctls_progress32,1350565888
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_TIME_REMAINING,edit,1350633600
Control9=IDC_STATIC,static,1342308352
Control10=IDC_GAMES_PLAYED,edit,1350633600
Control11=IDC_STATIC,static,1342308352
Control12=IDC_CURRENT_GAME,edit,1350633600
Control13=IDC_T2,static,1342308352
Control14=IDC_PLAYERS_PER_GAME,edit,1350631552
Control15=IDC_SPIN1,msctls_updown32,1342177334
Control16=IDC_T4,static,1342308352
Control17=IDC_T3,static,1342308352
Control18=IDC_N_REPETITIONS,edit,1350631552
Control19=IDC_TOTAL_GAMES,edit,1350633600
Control20=IDC_T1,static,1342308352
Control21=IDC_N_PLAYERS,edit,1350633600
Control22=IDC_T5,button,1342177287
Control23=IDC_ADD_DLL,button,1342242816
Control24=IDC_REMOVE_DLL,button,1342242816

[DLG:IDD_CONFIGURATION_DIALOG]
Type=1
Class=CTournamentCfgDlg
ControlCount=12
Control1=IDOK,button,1342242817
Control2=IDC_DLL_LIST,SysListView32,1350631425
Control3=IDC_T2,static,1342308352
Control4=IDC_PLAYERS_PER_GAME,edit,1350631552
Control5=IDC_SPIN1,msctls_updown32,1342177334
Control6=IDC_T4,static,1342308352
Control7=IDC_T3,static,1342308352
Control8=IDC_N_REPETITIONS,edit,1350631552
Control9=IDC_TOTAL_GAMES,edit,1350633600
Control10=IDC_T1,static,1342308352
Control11=IDC_N_PLAYERS,edit,1350633600
Control12=IDC_ADD_DLL,button,1342242816

[CLS:CTournamentCfgDlg]
Type=0
HeaderFile=TournamentCfgDlg.h
ImplementationFile=TournamentCfgDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDOK

[CLS:CGameProcessorThread]
Type=0
HeaderFile=GameProcessorThread.h
ImplementationFile=GameProcessorThread.cpp
BaseClass=CWinThread
Filter=N
LastObject=CGameProcessorThread
VirtualFilter=TC

