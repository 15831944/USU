VERSION 5.00
Begin VB.Form CreateGame 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Create New Game"
   ClientHeight    =   4665
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   6990
   BeginProperty Font 
      Name            =   "Arial"
      Size            =   15.75
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4665
   ScaleWidth      =   6990
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton OptionsButton 
      Caption         =   "Options"
      Height          =   495
      Left            =   2640
      TabIndex        =   26
      Top             =   3840
      Width           =   1695
   End
   Begin VB.CommandButton DeletePlayer 
      Caption         =   "Delete"
      Height          =   375
      Index           =   5
      Left            =   4800
      TabIndex        =   25
      Top             =   3000
      Visible         =   0   'False
      Width           =   1695
   End
   Begin VB.CommandButton DeletePlayer 
      Caption         =   "Delete"
      Height          =   375
      Index           =   4
      Left            =   4800
      TabIndex        =   24
      Top             =   1920
      Visible         =   0   'False
      Width           =   1695
   End
   Begin VB.CommandButton DeletePlayer 
      Caption         =   "Delete"
      Height          =   375
      Index           =   3
      Left            =   4800
      TabIndex        =   23
      Top             =   840
      Visible         =   0   'False
      Width           =   1695
   End
   Begin VB.CommandButton DeletePlayer 
      Caption         =   "Delete"
      Height          =   375
      Index           =   2
      Left            =   1440
      TabIndex        =   22
      Top             =   3000
      Visible         =   0   'False
      Width           =   1695
   End
   Begin VB.CommandButton DeletePlayer 
      Caption         =   "Delete"
      Height          =   375
      Index           =   1
      Left            =   1440
      TabIndex        =   21
      Top             =   1920
      Visible         =   0   'False
      Width           =   1695
   End
   Begin VB.CommandButton DeletePlayer 
      Caption         =   "Delete"
      Height          =   375
      Index           =   0
      Left            =   1440
      TabIndex        =   20
      Top             =   840
      Visible         =   0   'False
      Width           =   1695
   End
   Begin VB.CommandButton AddPlayer 
      Caption         =   "Add Player"
      Height          =   855
      Index           =   5
      Left            =   4800
      TabIndex        =   13
      Top             =   2520
      Width           =   1695
   End
   Begin VB.CommandButton AddPlayer 
      Caption         =   "Add Player"
      Height          =   855
      Index           =   4
      Left            =   4800
      TabIndex        =   12
      Top             =   1440
      Width           =   1695
   End
   Begin VB.CommandButton AddPlayer 
      Caption         =   "Add Player"
      Height          =   855
      Index           =   3
      Left            =   4800
      TabIndex        =   11
      Top             =   360
      Width           =   1695
   End
   Begin VB.CommandButton AddPlayer 
      Caption         =   "Add Player"
      Height          =   855
      Index           =   2
      Left            =   1440
      TabIndex        =   10
      Top             =   2520
      Width           =   1695
   End
   Begin VB.CommandButton AddPlayer 
      Caption         =   "Add Player"
      Height          =   855
      Index           =   1
      Left            =   1440
      TabIndex        =   9
      Top             =   1440
      Width           =   1695
   End
   Begin VB.CommandButton AddPlayer 
      Caption         =   "Add Player"
      Height          =   855
      Index           =   0
      Left            =   1440
      TabIndex        =   8
      Top             =   360
      Width           =   1695
   End
   Begin VB.CommandButton QuitGame 
      Caption         =   "Quit"
      Height          =   495
      Left            =   4560
      TabIndex        =   7
      Top             =   3840
      Width           =   1695
   End
   Begin VB.CommandButton StartGame 
      Caption         =   "Start"
      Enabled         =   0   'False
      Height          =   495
      Left            =   720
      TabIndex        =   6
      Top             =   3840
      Width           =   1695
   End
   Begin VB.PictureBox Picture1 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   855
      Index           =   5
      Left            =   3720
      Picture         =   "CreateGame.frx":0000
      ScaleHeight     =   52.131
      ScaleMode       =   0  'User
      ScaleWidth      =   46.087
      TabIndex        =   5
      Top             =   2520
      Width           =   855
   End
   Begin VB.PictureBox Picture1 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   855
      Index           =   4
      Left            =   3720
      Picture         =   "CreateGame.frx":245A
      ScaleHeight     =   52.131
      ScaleMode       =   0  'User
      ScaleWidth      =   46.087
      TabIndex        =   4
      Top             =   1440
      Width           =   855
   End
   Begin VB.PictureBox Picture1 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   855
      Index           =   3
      Left            =   3720
      Picture         =   "CreateGame.frx":48B4
      ScaleHeight     =   52.131
      ScaleMode       =   0  'User
      ScaleWidth      =   46.087
      TabIndex        =   3
      Top             =   360
      Width           =   855
   End
   Begin VB.PictureBox Picture1 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   855
      Index           =   2
      Left            =   360
      Picture         =   "CreateGame.frx":6D0E
      ScaleHeight     =   52.131
      ScaleMode       =   0  'User
      ScaleWidth      =   46.087
      TabIndex        =   2
      Top             =   2520
      Width           =   855
   End
   Begin VB.PictureBox Picture1 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   855
      Index           =   1
      Left            =   360
      Picture         =   "CreateGame.frx":9168
      ScaleHeight     =   52.131
      ScaleMode       =   0  'User
      ScaleWidth      =   46.087
      TabIndex        =   1
      Top             =   1440
      Width           =   855
   End
   Begin VB.PictureBox Picture1 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   855
      Index           =   0
      Left            =   360
      Picture         =   "CreateGame.frx":B5C2
      ScaleHeight     =   52.131
      ScaleMode       =   0  'User
      ScaleWidth      =   46.087
      TabIndex        =   0
      Top             =   360
      Width           =   855
   End
   Begin VB.Label NameLabel 
      Caption         =   "Label1"
      Height          =   375
      Index           =   5
      Left            =   4800
      TabIndex        =   19
      Top             =   2520
      Visible         =   0   'False
      Width           =   1695
   End
   Begin VB.Label NameLabel 
      Caption         =   "Label1"
      Height          =   375
      Index           =   4
      Left            =   4800
      TabIndex        =   18
      Top             =   1440
      Visible         =   0   'False
      Width           =   1695
   End
   Begin VB.Label NameLabel 
      Caption         =   "Label1"
      Height          =   375
      Index           =   3
      Left            =   4800
      TabIndex        =   17
      Top             =   360
      Visible         =   0   'False
      Width           =   1695
   End
   Begin VB.Label NameLabel 
      Caption         =   "Label1"
      Height          =   375
      Index           =   2
      Left            =   1440
      TabIndex        =   16
      Top             =   2520
      Visible         =   0   'False
      Width           =   1695
   End
   Begin VB.Label NameLabel 
      Caption         =   "Label1"
      Height          =   375
      Index           =   1
      Left            =   1440
      TabIndex        =   15
      Top             =   1440
      Visible         =   0   'False
      Width           =   1695
   End
   Begin VB.Label NameLabel 
      Caption         =   "Label1"
      Height          =   375
      Index           =   0
      Left            =   1440
      TabIndex        =   14
      Top             =   360
      Visible         =   0   'False
      Width           =   1695
   End
End
Attribute VB_Name = "CreateGame"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Public result As Boolean

Private Sub AddPlayer_Click(index As Integer)
    NewPlayerForm.Show vbModal, Me
    
    If NewPlayerForm.result = True Then
        NameLabel(index).Caption = NewPlayerForm.NameLabel
        nPlayers = nPlayers + 1
        MainForm.SetStartPlayerInfo NewPlayerForm.OptionHuman.value, NewPlayerForm.NameLabel, NewPlayerForm.DLLPath, index
        AddPlayer(index).Visible = False
        NameLabel(index).Visible = True
        DeletePlayer(index).Visible = True
        StartGame.Enabled = Module1.nPlayers > 1
    End If
End Sub

Private Sub Command2_Click()
    Me.Hide
End Sub

Private Sub DeletePlayer_Click(index As Integer)
    MainForm.DeleteStartPlayer index
    NameLabel(index).Visible = False
    DeletePlayer(index).Visible = False
    AddPlayer(index).Visible = True
    Module1.nPlayers = Module1.nPlayers - 1
    StartGame.Enabled = Module1.nPlayers > 1
End Sub


Private Sub OptionsButton_Click()
    GameOptions.Show vbModal, Me
    Delay = 1# - GameOptions.Slider1.value / 20
    PromptForNextTurn = GameOptions.Check1.value
    AttackForm.Timer1.Interval = 2000 * Delay
    AttackForm.CompActionA.Interval = 800 * Delay
    AttackForm.CompActionD.Interval = 1200 * Delay
    AttackForm.CompRetreat.Interval = 1500 * Delay
End Sub

Private Sub QuitGame_Click()
    result = False
    Me.Hide
End Sub

Private Sub StartGame_Click()
    result = True
    Me.Hide
End Sub
