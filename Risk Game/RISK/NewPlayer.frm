VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "comdlg32.ocx"
Begin VB.Form NewPlayerForm 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "New Player"
   ClientHeight    =   3735
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   6630
   BeginProperty Font 
      Name            =   "Times New Roman"
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
   ScaleHeight     =   3735
   ScaleWidth      =   6630
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin MSComDlg.CommonDialog CommonDialog1 
      Left            =   120
      Top             =   2880
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
      CancelError     =   -1  'True
      DefaultExt      =   ".dll"
      DialogTitle     =   "Select DLL File for Computer Player"
      Filter          =   "DLLs (.dll)|*.dll"
   End
   Begin VB.CommandButton CancelButton 
      Caption         =   "Cancel"
      Height          =   495
      Left            =   2880
      TabIndex        =   8
      Top             =   3000
      Width           =   1575
   End
   Begin VB.CommandButton OKButton 
      Caption         =   "OK"
      Height          =   495
      Left            =   4800
      TabIndex        =   7
      Top             =   3000
      Width           =   1575
   End
   Begin VB.CommandButton Browse 
      Caption         =   "Browse"
      Height          =   495
      Left            =   4920
      TabIndex        =   6
      Top             =   2160
      Width           =   1455
   End
   Begin VB.TextBox DLLPath 
      BackColor       =   &H80000004&
      Height          =   480
      Left            =   2160
      Locked          =   -1  'True
      TabIndex        =   5
      Text            =   "C:\Source Code\My Projects\Risk Game\SampleDLL1\Debug\SampleDLL1.dll"
      Top             =   2160
      Width           =   2535
   End
   Begin VB.OptionButton OptionComputer 
      Caption         =   "Computer"
      Height          =   495
      Left            =   240
      TabIndex        =   3
      Top             =   1560
      Width           =   2655
   End
   Begin VB.TextBox NameLabel 
      Height          =   480
      Left            =   2160
      TabIndex        =   1
      Top             =   840
      Width           =   2535
   End
   Begin VB.OptionButton OptionHuman 
      Caption         =   "Human"
      Height          =   495
      Left            =   240
      TabIndex        =   0
      Top             =   240
      Width           =   1575
   End
   Begin VB.Label Label2 
      Caption         =   "DLL"
      Height          =   375
      Left            =   600
      TabIndex        =   4
      Top             =   2160
      Width           =   1335
   End
   Begin VB.Label Label1 
      Caption         =   "Name"
      Height          =   495
      Left            =   600
      TabIndex        =   2
      Top             =   840
      Width           =   1335
   End
End
Attribute VB_Name = "NewPlayerForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Public result As Boolean
Private Declare Function TestPlayerDLL Lib "ManagerDLL" (ByVal DLLName As String, ByVal playerName As String) As Long

Private Sub TestDLL(displayMessage As Boolean)
    If DLLPath.Text <> "" Then
        Dim playerName As String * 100
        
        ' if this one is already in use... don't use it
        If MainForm.IsDLLPathInUse(DLLPath.Text) Then
            DLLPath.Text = ""
            If displayMessage Then
                MyMessageBox "This DLL is already in use.  Please select a different DLL for use."
            End If
            Exit Sub
        End If
        
        If TestPlayerDLL(DLLPath.Text, playerName) = False Then
            If displayMessage Then
                MyMessageBox "This DLL could not be loaded correctly.  Please select a different file."
            End If
            DLLPath.Text = ""
        Else
            SaveSetting "RISK", "Settings", "LastDLL", DLLPath.Text
            Dim i As Integer
            For i = 1 To 100
                If Mid$(playerName, i, 1) = Chr$(0) Then Exit For
            Next
            NameLabel.Text = Mid(playerName, 1, i - 1)
        End If
    End If
End Sub

Private Sub Browse_Click()
    ' the function needs to check the DLL... if it is bad, then leave the text field blank
    On Error GoTo canceled
    CommonDialog1.ShowOpen
    DLLPath.Text = CommonDialog1.FileName
    On Error GoTo 0
    TestDLL True
canceled:
    
End Sub

Private Sub CancelButton_Click()
    result = False
    Me.Hide
End Sub

Private Sub Form_Activate()
    
    If OptionHuman.value = True Then
        NameLabel.Text = ""
        NameLabel.SetFocus
    Else
        TestDLL False
    End If
    
End Sub

Private Sub Form_Load()
    OptionHuman.value = True
    DLLPath.Text = GetSetting("RISK", "Settings", "LastDLL", "")
End Sub

Private Sub NameLabel_KeyPress(KeyAscii As Integer)
    If KeyAscii = 13 Then OKButton_Click
End Sub

Private Sub OKButton_Click()
    If OptionHuman.value = True Then
        If NameLabel.Text = "" Then
            MyMessageBox "Please enter a name for this player" ', vbInformation
            Exit Sub
        End If
    Else
        If DLLPath.Text = "" Then
            MyMessageBox "Please select the player's DLL by pressing BROWSE" ', vbInformation
            Exit Sub
        End If
    End If
    result = True
    Me.Hide
End Sub

Private Sub OptionComputer_Click()
    Label1.Enabled = False
    NameLabel.Enabled = False
    Label2.Enabled = True
    DLLPath.Enabled = True
    Browse.Enabled = True
    TestDLL True
End Sub

Private Sub OptionHuman_Click()
    Label2.Enabled = False
    DLLPath.Enabled = False
    Browse.Enabled = False
    Label1.Enabled = True
    NameLabel.Enabled = True
End Sub
