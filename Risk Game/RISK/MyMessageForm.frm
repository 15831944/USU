VERSION 5.00
Begin VB.Form MyMessageForm 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "RISK"
   ClientHeight    =   1965
   ClientLeft      =   45
   ClientTop       =   390
   ClientWidth     =   5355
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
   Icon            =   "MyMessageForm.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1965
   ScaleWidth      =   5355
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin VB.Timer Timer1 
      Enabled         =   0   'False
      Interval        =   1000
      Left            =   0
      Top             =   1320
   End
   Begin VB.CommandButton OKButton 
      Caption         =   "OK"
      Height          =   495
      Left            =   2160
      TabIndex        =   3
      Top             =   1320
      Width           =   1215
   End
   Begin VB.CommandButton NoButton 
      Caption         =   "No"
      Height          =   495
      Left            =   2880
      TabIndex        =   2
      Top             =   1320
      Width           =   1215
   End
   Begin VB.CommandButton YesButton 
      Caption         =   "Yes"
      Height          =   495
      Left            =   1440
      TabIndex        =   1
      Top             =   1320
      Width           =   1215
   End
   Begin VB.Label Label1 
      Alignment       =   2  'Center
      Caption         =   "Label1"
      Height          =   975
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   5175
   End
End
Attribute VB_Name = "MyMessageForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Public result As VbMsgBoxResult
Public defaultResult As VbMsgBoxResult
Public mseconds As Integer

Public Sub ShowForm(Prompt As String, Title As String, frmType As VbMsgBoxStyle, Optional miliseconds As Variant)
    Label1.Caption = Prompt
    Me.Caption = Title
    YesButton.Visible = (frmType = vbYesNo)
    NoButton.Visible = (frmType = vbYesNo)
    OKButton.Visible = (frmType = vbOKOnly)
    If IsMissing(miliseconds) Then mseconds = 0 Else mseconds = miliseconds
    If mseconds > 0 Then
        Timer1.Interval = mseconds * Delay
        Timer1.Enabled = True
    Else
        Timer1.Enabled = False
    End If
    Me.Show vbModal
End Sub

Private Sub NoButton_Click()
    result = vbNo
    Timer1.Enabled = False
    Me.Hide
End Sub

Private Sub OKButton_Click()
    result = vbOK
    Timer1.Enabled = False
    Me.Hide
End Sub

Private Sub Timer1_Timer()
    result = defaultResult
    Timer1.Enabled = False
    Me.Hide
End Sub

Private Sub YesButton_Click()
    result = vbYes
    Timer1.Enabled = False
    Me.Hide
End Sub
