VERSION 5.00
Begin VB.Form WorkspaceList 
   Caption         =   "Workspaces"
   ClientHeight    =   4335
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   5685
   ControlBox      =   0   'False
   Icon            =   "WorkspaceList.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   4335
   ScaleWidth      =   5685
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton ok 
      Caption         =   "OK"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   3120
      TabIndex        =   0
      Top             =   3600
      Width           =   1575
   End
   Begin VB.CommandButton cancel 
      Caption         =   "Cancel"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   1200
      TabIndex        =   2
      Top             =   3600
      Width           =   1575
   End
   Begin VB.ListBox List1 
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   2700
      Left            =   240
      TabIndex        =   1
      Top             =   600
      Width           =   5175
   End
   Begin VB.Label Label1 
      Caption         =   "Existing Workspaces"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   240
      TabIndex        =   3
      Top             =   240
      Width           =   2535
   End
End
Attribute VB_Name = "WorkspaceList"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
'These variables must be set before the form is loaded
Public WorkspaceCount As Integer
Public result As Boolean
Public CantSelectIfOpen As Boolean
Public WSID As Integer

Public Enum WSCriteriaType
    All = 0
    CreatedByUser = 1
    PublicOrCreatedByUser = 2
End Enum

Public Sub Load(WorkspaceCriteria As WSCriteriaType)
    Dim mySQL As String, resultSet As rdoResultset, rArray As Variant
    Select Case WorkspaceCriteria
    Case All
        ' open all workspaces
        mySQL = "SELECT WorkspaceID, WorkspaceName FROM [Workspace]"
    Case CreatedByUser
        ' all workspaces created by user
        mySQL = "SELECT WorkspaceID, WorkspaceName FROM [Workspace] WHERE UserID = " & userID
    Case PublicOrCreatedByUser
        ' all public workspaces or workspaces created by user
        mySQL = "SELECT WorkspaceID, WorkspaceName FROM [Workspace] WHERE UserID = " & userID & " OR AccessType = 1 OR AccessType = 2"
    End Select
    
    Set resultSet = dbConnection.OpenResultset(mySQL)

    WorkspaceCount = 0
    'determine number of rows
    While Not resultSet.EOF
        rArray = resultSet.GetRows(1)
        List1.AddItem rArray(1, 0)
        List1.ItemData(List1.listCount - 1) = rArray(0, 0)
        WorkspaceCount = WorkspaceCount + 1
    Wend

End Sub
'Function:cancel_Click
'Purpose:register cancel click
Private Sub Cancel_Click()
    result = False
    Me.Hide
End Sub
'Function:Form_Load
'Purpose:Load the form and initialize all values in the list
Private Sub Form_Load()
    ' the load function should be called previous to this
    ok.Enabled = False
End Sub

Private Sub List1_Click()
    ok.Enabled = True
End Sub

Private Function SelectWorkspace() As Boolean
    
    If List1.ListIndex = -1 Then
        SelectWorkspace = False
        Exit Function
    End If
    
    WSID = List1.ItemData(List1.ListIndex)
    If CantSelectIfOpen Then
        Dim mySQL As String
        Dim resultSet As rdoResultset
        'Check to make sure workspace not already open
        mySQL = "SELECT * FROM [OpenWorkspaces] WHERE WorkspaceID = " & WSID & " AND UserID = " & Module1.userID
        Set resultSet = dbConnection.OpenResultset(mySQL, rdOpenKeyset)
        If resultSet.EOF Then
            'Open the Workspace
            SelectWorkspace = True
        Else
            MsgBox "Workspace Already Open", vbInformation
            SelectWorkspace = False
        End If
    Else
        SelectWorkspace = True
    End If
     
End Function

'Function:list1_DblClick
'Purpose:handles the double click event (same as clicking on ok)

Private Sub List1_DblClick()
    result = True
    If SelectWorkspace Then Me.Hide
End Sub
'Function:ok_Click
'Purpose: gets the seleceted workspace ID (from list) and checks to see if it is already
'open or not
Private Sub ok_Click()
    result = True
    If SelectWorkspace Then Me.Hide
End Sub
