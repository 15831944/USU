VERSION 5.00
Begin VB.Form PlaceArmiesForm 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Place Armies"
   ClientHeight    =   2775
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   5865
   ControlBox      =   0   'False
   BeginProperty Font 
      Name            =   "AlgerianBasD"
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
   ScaleHeight     =   2775
   ScaleWidth      =   5865
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin VB.PictureBox ArmyImage 
      Height          =   975
      Index           =   0
      Left            =   2280
      Picture         =   "PlaceArmiesForm.frx":0000
      ScaleHeight     =   60
      ScaleMode       =   0  'User
      ScaleWidth      =   60
      TabIndex        =   2
      Top             =   600
      Width           =   975
      Begin VB.Label ArmyCount 
         Alignment       =   2  'Center
         BackStyle       =   0  'Transparent
         Caption         =   "1"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   305
         Index           =   0
         Left            =   0
         TabIndex        =   3
         Top             =   30
         Width           =   305
      End
   End
   Begin VB.Label Label2 
      Caption         =   "(Click on each country to place an army.  Press Shift to place 5 armies simultaneously)."
      BeginProperty Font 
         Name            =   "AlgerianBasD"
         Size            =   12
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   855
      Left            =   720
      TabIndex        =   1
      Top             =   1800
      Width           =   4335
   End
   Begin VB.Label Label1 
      Caption         =   "Mark, You have armies to Place"
      Height          =   375
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   5655
   End
End
Attribute VB_Name = "PlaceArmiesForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
' set active player
' set # of armies to place

Public Sub SetPlayer(ByVal playerIndex As Integer, playerName As String)
    Label1.Caption = playerName & ", you have armies to place"
    ArmyImage(0) = LoadPicture(GetPlayerPictureFileName(MainForm.GetPlayerColorIndex(playerIndex), True))
End Sub

Public Sub SetArmiesRemaining(ACount As Integer)
    ArmyCount(0).Caption = ACount
End Sub


