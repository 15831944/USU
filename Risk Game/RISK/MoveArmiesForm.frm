VERSION 5.00
Begin VB.Form MoveArmiesForm 
   BorderStyle     =   3  'Fixed Dialog
   ClientHeight    =   2865
   ClientLeft      =   45
   ClientTop       =   45
   ClientWidth     =   5775
   ControlBox      =   0   'False
   BeginProperty Font 
      Name            =   "AlgerianBasD"
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
   ScaleHeight     =   2865
   ScaleWidth      =   5775
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton OKButton 
      Caption         =   "OK"
      Height          =   495
      Left            =   2100
      TabIndex        =   2
      Top             =   2160
      Width           =   1575
   End
   Begin VB.TextBox Text1 
      Height          =   420
      Left            =   2160
      TabIndex        =   1
      Text            =   "12"
      Top             =   1560
      Width           =   1455
   End
   Begin VB.Label Label3 
      Alignment       =   1  'Right Justify
      Caption         =   "(3-12)"
      Height          =   375
      Left            =   600
      TabIndex        =   4
      Top             =   1560
      Width           =   1335
   End
   Begin VB.Label Label2 
      Alignment       =   2  'Center
      Caption         =   "How many armies will you move in?"
      Height          =   375
      Left            =   120
      TabIndex        =   3
      Top             =   1080
      Width           =   5535
   End
   Begin VB.Label Label1 
      Alignment       =   2  'Center
      Caption         =   "Western United States has been captured!"
      Height          =   615
      Left            =   240
      TabIndex        =   0
      Top             =   240
      Width           =   5295
   End
End
Attribute VB_Name = "MoveArmiesForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Public minArmies As Integer
Public maxArmies As Integer
Public CountryName As String
Public formType As Integer ' 0 - capture, 1 - reinforcement
Public ArmiesToMove As Integer

Public Sub ShowForm()
    If formType = 0 Then
        Label1 = CountryName & " has been captured!"
    Else
        Label1 = CountryName & " is being reinforced."
    End If
    Label3 = "(" & minArmies & "-" & maxArmies & ")"
    Text1.Text = maxArmies
    Me.Show vbModal
    
End Sub

Private Sub Form_Activate()
    Text1.SetFocus
End Sub

Private Sub OKButton_Click()
    If Text1 >= minArmies And Text1 <= maxArmies Then
        ArmiesToMove = Text1
        Me.Hide
    Else
        MyMessageBox "You may not move that many armies." ', vbInformation
    End If
End Sub

Private Sub Text1_KeyPress(KeyAscii As Integer)
    If KeyAscii = 13 Then OKButton_Click
End Sub
