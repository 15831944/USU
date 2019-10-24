VERSION 5.00
Begin VB.Form FirstLogin 
   Caption         =   "First Login"
   ClientHeight    =   3765
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
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
   Icon            =   "FirstLogin.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   3765
   ScaleWidth      =   4680
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Cancel 
      Caption         =   "Cancel"
      Height          =   495
      Left            =   480
      TabIndex        =   3
      Top             =   2880
      Width           =   3735
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Open an Existing Workspace"
      Height          =   495
      Left            =   480
      TabIndex        =   1
      Top             =   2040
      Width           =   3735
   End
   Begin VB.CommandButton new 
      Caption         =   "Create a New Workspace"
      Height          =   495
      Left            =   480
      TabIndex        =   0
      Top             =   1200
      Width           =   3735
   End
   Begin VB.Label Label3 
      Alignment       =   2  'Center
      Caption         =   "There are no existing open workspaces. Please select from the following:"
      Height          =   495
      Left            =   480
      TabIndex        =   2
      Top             =   240
      Width           =   3735
   End
End
Attribute VB_Name = "FirstLogin"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Public result As Boolean
Private wsList As WorkspaceList

Private Sub Cancel_Click()
    result = False
    Me.Hide
End Sub

'function: command2_Click
'Purpose: open an existing workspace - option is grayed out if
'no workspaces exist.
Private Sub Command2_Click()

    wsList.CantSelectIfOpen = True
    wsList.Show vbModal
    If wsList.result = True Then
        result = True
        Me.Hide
        OpenWorkspaces.open_workspace wsList.WSID
    End If
    
End Sub
'Function:Form_Load
'purpose: if a user has no open workspaces upon login this form is
'called to open an existing workspace or create a new one
Private Sub Form_Load()
'
    Set wsList = New WorkspaceList
    wsList.Load PublicOrCreatedByUser
      
    If wsList.WorkspaceCount = 0 Then
        'MsgBox "No workspaces or no workspaces to which you have rights to access found", vbInformation
        Command2.Enabled = False
        Exit Sub
    End If

End Sub
'Function:new_click
'Purpose: Create a new workspace
Private Sub new_Click()
    Me.Hide
    If MDIMain.LoadNewWorkspace() = True Then
        result = True
        Exit Sub
    End If
    Me.Show
End Sub


