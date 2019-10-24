VERSION 5.00
Begin VB.Form frmSelectTaskGroup 
   Caption         =   "Task Group List"
   ClientHeight    =   4920
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   7350
   ControlBox      =   0   'False
   Icon            =   "frmSelectTaskGroup.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   4920
   ScaleWidth      =   7350
   StartUpPosition =   3  'Windows Default
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
      Height          =   3660
      Left            =   120
      Sorted          =   -1  'True
      TabIndex        =   0
      Top             =   600
      Width           =   7095
   End
   Begin VB.CommandButton cancel 
      Cancel          =   -1  'True
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
      Left            =   1560
      TabIndex        =   2
      Top             =   4440
      Width           =   2055
   End
   Begin VB.CommandButton next 
      Caption         =   "Next"
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
      Left            =   3840
      TabIndex        =   1
      Top             =   4440
      Width           =   2055
   End
   Begin VB.Label Label1 
      Caption         =   "Select a Group to Edit:"
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
      Left            =   120
      TabIndex        =   3
      Top             =   120
      Width           =   3855
   End
End
Attribute VB_Name = "frmSelectTaskGroup"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Private lrArray As Variant
Private RowReturn As Integer
Public TaskGroupName As String
'Function/Subroutine:cancel_Click
'Purpose: unload form if operation cancled
Private Sub cancel_Click()
    Me.Hide
End Sub
'Function/Subroutine:Form_Load
'Purpose: load the form with group list
Private Sub Form_Load()
    Dim mySQLStatement As String
    Dim resultSet As rdoResultset
    Dim i, j As Integer
    
    RowReturn = 0
    
    'Display List of all available groups
    mySQLStatement = "SELECT TaskGroup.TaskGroupID, TaskGroup.TaskGroupName From [TaskGroup]"
    Set resultSet = dbConnection.OpenResultset(mySQLStatement, rdOpenKeyset)
        
    If resultSet.EOF Then
        MsgBox "No Groups Found", vbInformation
        Me.Hide
        Exit Sub
    End If
        
    While Not resultSet.EOF
        resultSet.MoveNext
        RowReturn = RowReturn + 1
    Wend
    
    resultSet.MoveFirst
    lrArray = resultSet.GetRows(RowReturn)
        
    For i = 0 To RowReturn - 1
           List1.AddItem lrArray(1, i)
    Next i
End Sub
'Function/Subroutine:List1_DblClick
'Purpose: if a node is couble clicked - same as clicking next
Private Sub List1_DblClick()
    next_Click
End Sub
'Function/Subroutine:List1_KeyPress
'Purpose: if enter is pressed - same as clicking next
Private Sub List1_KeyPress(KeyAscii As Integer)
    If KeyAscii = 13 Then
        next_Click
    End If
End Sub
'Function/Subroutine:next_Click
'Purpose: Get task group name and call edit task form
Private Sub next_Click()
    Dim Index As Integer
    Dim flag As Boolean
    
    flag = False
    
    'Get the selected Item
    For Index = 0 To List1.listCount - 1
        If List1.Selected(Index) Then
            TaskGroupName = List1.text
            flag = True
        End If
    Next Index
    
    'Call Edit Window
    If flag = True Then
        EditTaskGroup.TaskGroupName = TaskGroupName
        EditTaskGroup.Show vbModal
        Unload EditTaskGroup
    Else
        MsgBox "No Task Selected", vbInformation
        Exit Sub
    End If
    Me.Hide
    
End Sub
