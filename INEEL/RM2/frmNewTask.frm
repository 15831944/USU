VERSION 5.00
Begin VB.Form frmNewTask 
   Caption         =   "Create Task"
   ClientHeight    =   2640
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   6120
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
   Icon            =   "frmNewTask.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   2640
   ScaleWidth      =   6120
   StartUpPosition =   1  'CenterOwner
   Begin VB.CommandButton cancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   375
      Left            =   720
      TabIndex        =   3
      Top             =   2040
      Width           =   2055
   End
   Begin VB.CommandButton ok 
      Caption         =   "Next->"
      Height          =   375
      Left            =   3000
      TabIndex        =   2
      Top             =   2040
      Width           =   2055
   End
   Begin VB.TextBox Text1 
      Height          =   375
      Left            =   240
      TabIndex        =   0
      Top             =   600
      Width           =   3735
   End
   Begin VB.TextBox Text2 
      Height          =   375
      Left            =   240
      TabIndex        =   1
      Top             =   1440
      Width           =   5295
   End
   Begin VB.Label Label2 
      Caption         =   "Enter Task Name (25 Char max):"
      Height          =   375
      Left            =   240
      TabIndex        =   5
      Top             =   240
      Width           =   3735
   End
   Begin VB.Label Label3 
      Caption         =   "Enter Task Description (50 Char max):"
      Height          =   375
      Left            =   240
      TabIndex        =   4
      Top             =   1080
      Width           =   3735
   End
End
Attribute VB_Name = "frmNewTask"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Private lrArray As Variant
Private RowReturn As Integer
Public TaskName As String
Public Result As Boolean
'Function/Subroutine:cancel_Click
'Purpose:Handel cancel event
Private Sub Cancel_Click()
    Result = False
    Me.Hide
End Sub

'Function: next_Click
'Purpose: Creates a new procedure in the database
Private Sub OK_Click()
    Dim mySQLStatement As String, resultset As rdoResultset
    
    'determine if name and description are acceptable
    If Text1 = "" Or Len(Text1) > NameMaxFieldLength Then
        MsgBox "Invalid Task Name", vbInformation
        Exit Sub
    End If
    
    If Text2 = "" Or Len(Text2) > NameMaxFieldLength Then
        MsgBox "Invalid Task Description", vbInformation
        Exit Sub
    End If
    
    'Check to see if task name already exists
    TaskName = Text1.text
    mySQLStatement = "SELECT TaskName FROM [Task] WHERE TaskName = '" & TaskName & "'"
    Set resultset = dbConnection.OpenResultset(mySQLStatement)
    If Not resultset.EOF Then
        MsgBox "Invalid task name.  Task name already in use.", vbInformation
        Exit Sub
    End If
    
    Me.Hide
    'Create New Task In Database
    mySQLStatement = "INSERT INTO [Task] (TaskName, TaskDesc) VALUES ( '" & TaskName & "', '" & Text2 & "')"
    dbConnection.Execute (mySQLStatement)
    Result = True
End Sub
'Function/Subroutine:Text1_KeyPress
'Purpose:set focus
Private Sub Text1_KeyPress(KeyAscii As Integer)
    If KeyAscii = 13 Then
        Text2.SetFocus
    End If

End Sub
'Function/Subroutine:Text2_KeyPress
'Purpose:set focus
Private Sub Text2_KeyPress(KeyAscii As Integer)
    If KeyAscii = 13 Then
        OK_Click
    End If

End Sub
