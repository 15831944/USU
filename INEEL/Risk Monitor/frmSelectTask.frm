VERSION 5.00
Begin VB.Form frmSelectTask 
   Caption         =   "Select Task"
   ClientHeight    =   4965
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   7365
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
   Icon            =   "frmSelectTask.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   4965
   ScaleWidth      =   7365
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton next 
      Caption         =   "Next"
      Height          =   375
      Left            =   4080
      TabIndex        =   1
      Top             =   4440
      Width           =   2055
   End
   Begin VB.CommandButton cancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   375
      Left            =   1320
      TabIndex        =   2
      Top             =   4440
      Width           =   2055
   End
   Begin VB.ListBox List1 
      Height          =   3660
      Left            =   120
      Sorted          =   -1  'True
      TabIndex        =   0
      Top             =   600
      Width           =   7095
   End
   Begin VB.Label Label1 
      Caption         =   "Select Task to Edit:"
      Height          =   255
      Left            =   120
      TabIndex        =   3
      Top             =   240
      Width           =   3855
   End
End
Attribute VB_Name = "frmSelectTask"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Private lrArray As Variant
Private RowReturn As Integer
Public TaskName As String
'Function/Subroutine:cancel_Click
'Purpose: unload the form if operation cancled
Private Sub cancel_Click()
    Me.Hide
End Sub
'Function/Subroutine:Form_Load
'Purpose: load the list with task information from the database
Private Sub Form_Load()
    Dim mySQLStatement As String
    Dim resultSet As rdoResultset
    Dim i, j As Integer
    
    RowReturn = 0
    
    'Display List of all available tasks
    mySQLStatement = "SELECT Task.TaskID, Task.TaskName From [Task]"
    Set resultSet = dbConnection.OpenResultset(mySQLStatement, rdOpenKeyset)
        
    If resultSet.EOF Then
        MsgBox "No Tasks Found", vbInformation
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
'Purpose:double clicking on item in list is the same as clicking next
Private Sub List1_DblClick()
    next_Click
End Sub
'Function/Subroutine:List1_KeyPress
'Purpose:pressing enter is the same as clicking next
Private Sub List1_KeyPress(KeyAscii As Integer)
    If KeyAscii = 13 Then
        next_Click
    End If
End Sub
'Function/Subroutine:next_Click
'Purpose:determine task name and then call the edit procedure form
Private Sub next_Click()
    Dim Index As Integer
    Dim flag As Boolean
    
    
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
        EditTask.TaskName = TaskName
        EditTask.Show vbModal
        Unload EditTask
    Else
        MsgBox "No Task Selected", vbInformation
        Exit Sub
    End If
    Me.Hide
        
End Sub
