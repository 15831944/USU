VERSION 5.00
Begin VB.Form SelectWorkspace 
   Caption         =   "Workspaces"
   ClientHeight    =   4335
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   5715
   ControlBox      =   0   'False
   Icon            =   "SelectWorkspaceId.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   4335
   ScaleWidth      =   5715
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton ok 
      Caption         =   "OK"
      Height          =   375
      Left            =   3120
      TabIndex        =   0
      Top             =   3600
      Width           =   1575
   End
   Begin VB.CommandButton cancel 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   1200
      TabIndex        =   2
      Top             =   3600
      Width           =   1575
   End
   Begin VB.ListBox List1 
      Height          =   2985
      Left            =   240
      TabIndex        =   1
      Top             =   480
      Width           =   5295
   End
   Begin VB.Label Label1 
      Caption         =   "Existing Workspaces"
      Height          =   255
      Left            =   240
      TabIndex        =   3
      Top             =   240
      Width           =   2535
   End
End
Attribute VB_Name = "SelectWorkspace"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
'data must be set before load function is called.
Public rArray As Variant
Public RowReturn As Integer
Public WSID As Integer
Public CancelClick As Boolean
'Function:cancel_Click
'Purpose:handles the cancel click event
Private Sub cancel_Click()
'
    CancelClick = True
    Me.Hide
    Exit Sub
End Sub
'Function:Form_Load
'Purpose:loads the form with a list of workspace from the database
Private Sub Form_Load()
    Dim i As Integer

    For i = 0 To RowReturn - 1
        List1.AddItem rArray(1, i)
    Next i
End Sub

'Function:List1_DblClick
'Purpose:handles the list1 double clict, acts the same as the ok button

Private Sub List1_DblClick()
'
    Dim Index As Integer
    Dim flag As Boolean
    Dim TaskName As String
    Dim i As Integer
   ' Dim WSID As Integer
    Dim mySQL As String
    Dim resultSet As rdoResultset
    
    Me.Hide
    flag = False
    
    'Get the selected Item
    For Index = 0 To List1.listCount - 1
        If List1.Selected(Index) Then
            TaskName = List1.text
            flag = True
        End If
    Next Index
    
    'Call Edit Window
    If flag = True Then

        For i = 0 To RowReturn - 1
            If TaskName = rArray(1, i) Then
                WSID = rArray(0, i)
                Exit Sub
            End If
        Next i
        
    Else
        MsgBox "No Workspace Selected", vbInformation
        Me.Show 1

        Exit Sub
    End If
    

    
    
End Sub
'Function:ok_Click
'Purpose:called when ok is clicked. determines the selected task name and id
'number
Private Sub ok_Click()
'
    Dim Index As Integer
    Dim flag As Boolean
    Dim TaskName As String
    Dim i As Integer
    'Dim WSID As Integer
    Dim mySQL As String
    Dim resultSet As rdoResultset
    
    Me.Hide
    flag = False
    
    'Get the selected Item
    For Index = 0 To List1.listCount - 1
        If List1.Selected(Index) Then
            TaskName = List1.text
            flag = True
        End If
    Next Index
    
    'Call Edit Window
    If flag = True Then
        For i = 0 To RowReturn - 1
            If TaskName = rArray(1, i) Then
                WSID = rArray(0, i)
                Exit Sub
            End If
        Next i
        
    Else
        MsgBox "No Workspace Selected", vbInformation
        Me.Show 1

        Exit Sub
    End If

End Sub
