VERSION 5.00
Object = "{86CF1D34-0C5F-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCT2.OCX"
Begin VB.Form WorkspaceProperties 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Workspace Properties"
   ClientHeight    =   4875
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   9210
   ControlBox      =   0   'False
   BeginProperty Font 
      Name            =   "Arial"
      Size            =   9.75
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   Icon            =   "WorkspaceName.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4875
   ScaleWidth      =   9210
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton cancel 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   7680
      TabIndex        =   14
      Top             =   4200
      Width           =   1335
   End
   Begin VB.OptionButton ReadOnlyAccess 
      Caption         =   "Read-only Access"
      Height          =   375
      Left            =   840
      TabIndex        =   13
      Top             =   3120
      Width           =   3135
   End
   Begin VB.OptionButton FullAccess 
      Caption         =   "Full Access (anyone can modify)"
      Height          =   375
      Left            =   840
      TabIndex        =   12
      Top             =   2640
      Width           =   3855
   End
   Begin VB.ComboBox InitialModeCombo 
      Height          =   360
      Left            =   6720
      TabIndex        =   11
      Text            =   "Combo1"
      Top             =   1560
      Width           =   2055
   End
   Begin MSComCtl2.DTPicker WSEndDate 
      Height          =   375
      Left            =   6720
      TabIndex        =   10
      Top             =   1080
      Width           =   2055
      _ExtentX        =   3625
      _ExtentY        =   661
      _Version        =   393216
      Format          =   22740993
      CurrentDate     =   37109
   End
   Begin MSComCtl2.DTPicker WSStartDate 
      Height          =   375
      Left            =   6720
      TabIndex        =   9
      Top             =   600
      Width           =   2055
      _ExtentX        =   3625
      _ExtentY        =   661
      _Version        =   393216
      Format          =   22740993
      CurrentDate     =   37109
   End
   Begin VB.OptionButton privateW 
      Caption         =   "Private Workspace"
      Height          =   375
      Left            =   360
      TabIndex        =   5
      Top             =   3720
      Width           =   2895
   End
   Begin VB.TextBox Text2 
      Height          =   375
      Left            =   360
      TabIndex        =   4
      Top             =   1560
      Width           =   4215
   End
   Begin VB.CommandButton ok 
      Caption         =   "OK"
      Height          =   375
      Left            =   6000
      TabIndex        =   1
      Top             =   4200
      Width           =   1455
   End
   Begin VB.TextBox Text1 
      Height          =   375
      Left            =   360
      TabIndex        =   0
      Top             =   720
      Width           =   4215
   End
   Begin VB.Label Label6 
      Caption         =   "Public Workspace"
      Height          =   375
      Left            =   480
      TabIndex        =   15
      Top             =   2280
      Width           =   2775
   End
   Begin VB.Label Label5 
      Caption         =   "Initial Mode"
      Height          =   375
      Left            =   4920
      TabIndex        =   8
      Top             =   1560
      Width           =   1815
   End
   Begin VB.Label Label4 
      Caption         =   "End Date"
      Height          =   375
      Left            =   4920
      TabIndex        =   7
      Top             =   1080
      Width           =   1695
   End
   Begin VB.Label Label3 
      Caption         =   "Start Date"
      Height          =   375
      Left            =   4920
      TabIndex        =   6
      Top             =   600
      Width           =   1695
   End
   Begin VB.Label Label2 
      Caption         =   "Enter Workspace Description (50 Char. Max):"
      Height          =   255
      Left            =   360
      TabIndex        =   3
      Top             =   1200
      Width           =   4215
   End
   Begin VB.Label Label1 
      Caption         =   "Enter Name for New Workspace (25 Char. Max):"
      Height          =   255
      Left            =   360
      TabIndex        =   2
      Top             =   480
      Width           =   4215
   End
End
Attribute VB_Name = "WorkspaceProperties"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Public WorkspaceType As Integer
Public InitialMode As Integer
Public StartDate As Date
Public EndDate As Date
Public result As Integer

Private Sub Cancel_Click()
    result = False
    Me.Hide
End Sub

'Function/Subroutine:Form_Load
'Purpose:
Private Sub Form_Load()
    Dim i As Integer
    For i = 1 To ModeList.Count
        If ModeList.Item(i).ObjectInUse Then
            InitialModeCombo.AddItem ModeList.Item(i).ModeName
            InitialModeCombo.ItemData(InitialModeCombo.listCount - 1) = i
            If InitialMode = i Then
                InitialModeCombo.ListIndex = InitialModeCombo.listCount - 1
            End If
        End If
    Next i
    If InitialModeCombo.ListIndex < 0 Then
        InitialModeCombo.ListIndex = 0
    End If
    
    If WorkspaceType = 1 Then
        FullAccess.Value = True
    ElseIf WorkspaceType = 2 Then
        ReadOnlyAccess.Value = True
    Else ' WorkspaceType = 0
        privateW.Value = True
    End If
    
End Sub

Private Sub InitialModeCombo_Click()
    InitialMode = InitialModeCombo.ItemData(InitialModeCombo.ListIndex)
End Sub

'Function/Subroutine:ok_Click
'Purpose:
Private Sub ok_Click()

    Dim mySQLStatement As String
    Dim rArray As Variant
    Dim resultSet As rdoResultset
    Dim lRowReturn As Integer
    Dim i As Integer
    
    'check workspace name
    If Len(Text1) > 25 Or Len(Text1) < 1 Then
        MsgBox "Invalid Workspace Name, must be less than 25 characters", vbInformation
        Exit Sub
    End If
    'check workspace description
     If Len(Text2) > 50 Or Len(Text2) < 1 Then
        MsgBox "Invalid Workspace Description, must be less than 50 characters", vbInformation
        Exit Sub
    End If
    
    If (WSEndDate.Value - WSStartDate.Value < 1) Then
        MsgBox "Workspace length must be at minimum 1 day.", vbInformation
        Exit Sub
    End If
    
    StartDate = WSStartDate.Value
    EndDate = WSEndDate.Value
    
    If FullAccess.Value = True Then
        WorkspaceType = 1
    ElseIf ReadOnlyAccess.Value = True Then
        WorkspaceType = 2
    Else ' must be a private workspace
        WorkspaceType = 0
    End If
        
    mySQLStatement = "SELECT Workspace.WorkspaceName FROM [Workspace] WHERE Workspace.WorkspaceName = '" & Trim(Text1.text) & "'"
    Set resultSet = dbConnection.OpenResultset(mySQLStatement)
    If Not resultSet.EOF Then
        MsgBox "Workspace name already in use.", vbInformation
        Exit Sub
    End If
    result = True
    Me.Hide
End Sub

'Function/Subroutine:Text1_KeyPress
'Purpose:
Private Sub Text1_KeyPress(KeyAscii As Integer)
    If KeyAscii = 13 Then
        ok.SetFocus
    End If
End Sub
