VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form GameOptions 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Game Options"
   ClientHeight    =   4560
   ClientLeft      =   45
   ClientTop       =   390
   ClientWidth     =   5385
   ControlBox      =   0   'False
   BeginProperty Font 
      Name            =   "Arial"
      Size            =   14.25
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4560
   ScaleWidth      =   5385
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox RndSeed 
      Height          =   495
      Left            =   2520
      TabIndex        =   7
      Top             =   3000
      Width           =   1095
   End
   Begin VB.CommandButton Command1 
      Caption         =   "OK"
      Height          =   495
      Left            =   1800
      TabIndex        =   5
      Top             =   3840
      Width           =   1455
   End
   Begin VB.CheckBox Check1 
      Caption         =   "Prompt for Next Turn (Computers Only Game)"
      Height          =   855
      Left            =   360
      TabIndex        =   1
      Top             =   360
      Value           =   1  'Checked
      Width           =   3855
   End
   Begin MSComctlLib.Slider Slider1 
      Height          =   375
      Left            =   360
      TabIndex        =   0
      Top             =   2040
      Width           =   4215
      _ExtentX        =   7435
      _ExtentY        =   661
      _Version        =   393216
      Max             =   19
   End
   Begin VB.Label Label4 
      Caption         =   "Random Seed"
      Height          =   375
      Left            =   480
      TabIndex        =   6
      Top             =   3120
      Width           =   1935
   End
   Begin VB.Label Label3 
      Caption         =   "Fast"
      Height          =   375
      Left            =   3480
      TabIndex        =   4
      Top             =   2520
      Width           =   1095
   End
   Begin VB.Label Label2 
      Caption         =   "Slow"
      Height          =   375
      Left            =   480
      TabIndex        =   3
      Top             =   2520
      Width           =   1455
   End
   Begin VB.Label Label1 
      Caption         =   "Game Delay "
      Height          =   375
      Left            =   360
      TabIndex        =   2
      Top             =   1560
      Width           =   3735
   End
End
Attribute VB_Name = "GameOptions"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
    Me.Hide
End Sub
