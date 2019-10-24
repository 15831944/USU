; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=SquareEdge
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "squaresgame.h"
LastPage=0

ClassCount=9
Class1=BestScoresDialog
Class2=GameOverDialog
Class3=Square
Class4=SquareEdge
Class5=CSquaresGameApp
Class6=CAboutDlg
Class7=CSquaresGameDlg

ResourceCount=7
Resource1=IDD_GAME_OVER
Resource2=IDD_BEST_SCORES
Resource3=IDD_SQUARESGAME_DIALOG
Resource4=IDD_SELECT_GAME_SIZE
Resource5=IDD_NEW_GAME
Class8=NewGameDialog
Resource6=IDD_ABOUTBOX
Class9=GameSizeDialog
Resource7=IDR_MENU1

[CLS:BestScoresDialog]
Type=0
BaseClass=CDialog
HeaderFile=BestScoresDialog.h
ImplementationFile=BestScoresDialog.cpp
LastObject=BestScoresDialog
Filter=D
VirtualFilter=dWC

[CLS:GameOverDialog]
Type=0
BaseClass=CDialog
HeaderFile=GameOverDialog.h
ImplementationFile=GameOverDialog.cpp
Filter=D
VirtualFilter=dWC
LastObject=GameOverDialog

[CLS:Square]
Type=0
BaseClass=CButton
HeaderFile=Square.h
ImplementationFile=Square.cpp
Filter=W
VirtualFilter=BWC
LastObject=Square

[CLS:SquareEdge]
Type=0
BaseClass=CButton
HeaderFile=SquareEdge.h
ImplementationFile=SquareEdge.cpp
Filter=W
VirtualFilter=BWC
LastObject=SquareEdge

[CLS:CSquaresGameApp]
Type=0
BaseClass=CWinApp
HeaderFile=SquaresGame.h
ImplementationFile=SquaresGame.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=SquaresGameDlg.cpp
ImplementationFile=SquaresGameDlg.cpp

[CLS:CSquaresGameDlg]
Type=0
BaseClass=CDialog
HeaderFile=SquaresGameDlg.h
ImplementationFile=SquaresGameDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=CSquaresGameDlg

[DLG:IDD_BEST_SCORES]
Type=1
Class=BestScoresDialog
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDC_S1,static,1342308864
Control3=IDC_S2,static,1342308864
Control4=IDC_S3,static,1342308864
Control5=IDC_S4,static,1342308864
Control6=IDC_S5,static,1342308864

[DLG:IDD_GAME_OVER]
Type=1
Class=GameOverDialog
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDC_TEXT1,static,1342308865
Control3=IDC_TEXT2,static,1342308865

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SQUARESGAME_DIALOG]
Type=1
Class=CSquaresGameDlg
ControlCount=4
Control1=IDC_PLAYER1,static,1342308865
Control2=IDC_PLAYER2,static,1342308865
Control3=IDC_PLAYER1_SCORE,edit,1350641793
Control4=IDC_PLAYER2_SCORE,edit,1350641793

[MNU:IDR_MENU1]
Type=1
Class=?
Command1=ID_FILE_NEWGAME
Command2=ID_FILE_BESTGAMES
Command3=ID_FILE_EXIT
Command4=ID_OPTIONS_GAMESIZE
Command5=ID_OPTIONS_PLAYER1COLOR
Command6=ID_OPTIONS_PLAYER2COLOR
Command7=ID_OPTIONS_SIDECOLOR
CommandCount=7

[DLG:IDD_NEW_GAME]
Type=1
Class=NewGameDialog
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_RADIO1,button,1342177289
Control4=IDC_RADIO2,button,1342177289
Control5=IDC_RADIO3,button,1342177289
Control6=IDC_EDIT1,edit,1350639744
Control7=IDC_STATIC,static,1342308864

[CLS:NewGameDialog]
Type=0
HeaderFile=NewGameDialog.h
ImplementationFile=NewGameDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=ID_FILE_BESTGAMES

[DLG:IDD_SELECT_GAME_SIZE]
Type=1
Class=GameSizeDialog
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308864
Control4=IDC_EDIT1,edit,1350631552

[CLS:GameSizeDialog]
Type=0
HeaderFile=GameSizeDialog.h
ImplementationFile=GameSizeDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDOK

