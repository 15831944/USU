VERSION 5.00
Begin VB.Form RiskCardForm 
   BorderStyle     =   3  'Fixed Dialog
   ClientHeight    =   6615
   ClientLeft      =   45
   ClientTop       =   45
   ClientWidth     =   3300
   ControlBox      =   0   'False
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
   Picture         =   "RiskCardForm.frx":0000
   ScaleHeight     =   6600
   ScaleMode       =   0  'User
   ScaleWidth      =   3300
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton SkipButton 
      Caption         =   "Skip All"
      Height          =   495
      Left            =   1440
      TabIndex        =   3
      Top             =   6000
      Width           =   1695
   End
   Begin VB.Timer Timer1 
      Enabled         =   0   'False
      Interval        =   2400
      Left            =   2760
      Top             =   5400
   End
   Begin VB.CommandButton OKButton 
      Caption         =   "OK"
      Height          =   495
      Left            =   240
      TabIndex        =   0
      Top             =   6000
      Width           =   1095
   End
   Begin VB.Label Label1 
      Alignment       =   2  'Center
      BackStyle       =   0  'Transparent
      Caption         =   "You have received a Risk Card!"
      Height          =   855
      Left            =   120
      TabIndex        =   2
      Top             =   1560
      Width           =   3015
   End
   Begin VB.Label Label2 
      Alignment       =   2  'Center
      BackStyle       =   0  'Transparent
      Caption         =   "You have 5 Cards"
      Height          =   375
      Left            =   23
      TabIndex        =   1
      Top             =   2760
      Width           =   3255
   End
End
Attribute VB_Name = "RiskCardForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Declare Function GetCardType Lib "ManagerDLL" (ByVal wCard As Long, ByRef CardType As Long) As Long

Public SkipAll As Boolean

Public Sub ShowFormGetRiskCard(ByVal nCards As Integer, ByVal wCard As Integer)
    
    Picture = LoadPicture("cards\Image" & wCard & ".jpg")
    Label1 = "You have received a Risk Card!"
    Label2.Visible = True
    If (nCards = 1) Then
        Label2.Caption = "You have 1 card"
    Else
        Label2.Caption = "You have " & nCards & " cards"
    End If
    OKButton.Left = 1080
    SkipButton.Visible = False
    Me.Show vbModal
    
End Sub

Public Sub ShowFormDealRiskCard(ByVal wCard, playerName As String)
    Picture = LoadPicture("cards\Image" & wCard & ".jpg")
    Label1 = "is dealt to " & playerName
    Label2.Visible = False
    OKButton.Left = 240
    SkipButton.Visible = True
    SkipAll = False
    Timer1.Interval = 2400 * Delay
    Me.Show vbModal
End Sub

Private Sub OKButton_Click()
    Me.Hide
End Sub

Private Sub SkipButton_Click()
    SkipAll = True
    Me.Hide
End Sub

Private Sub Timer1_Timer()
    Timer1.Enabled = False
    OKButton_Click
End Sub
