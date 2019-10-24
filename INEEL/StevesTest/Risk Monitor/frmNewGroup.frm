VERSION 5.00
Begin VB.Form frmNewGroup 
   Caption         =   "Create Group"
   ClientHeight    =   2550
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   5865
   ControlBox      =   0   'False
   Icon            =   "frmNewGroup.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   2550
   ScaleWidth      =   5865
   StartUpPosition =   1  'CenterOwner
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
      Left            =   600
      TabIndex        =   3
      Top             =   1920
      Width           =   2055
   End
   Begin VB.CommandButton ok 
      Caption         =   "Next->"
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
      Left            =   2880
      TabIndex        =   2
      Top             =   1920
      Width           =   2055
   End
   Begin VB.TextBox Text1 
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
      Left            =   240
      TabIndex        =   0
      Top             =   480
      Width           =   3735
   End
   Begin VB.TextBox Text2 
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
      Left            =   240
      TabIndex        =   1
      Top             =   1320
      Width           =   5295
   End
   Begin VB.Label Label2 
      Caption         =   "Enter Group Name (25 Char max):"
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
      Left            =   240
      TabIndex        =   5
      Top             =   120
      Width           =   3735
   End
   Begin VB.Label Label3 
      Caption         =   "Enter Group Description (50 Char max):"
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
      Left            =   240
      TabIndex        =   4
      Top             =   960
      Width           =   3735
   End
End
Attribute VB_Name = "frmNewGroup"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Public TaskGroupName As String
Public Result As Boolean

'Function/Subroutine:cancel_Click
'Purpose:handel cancel event
Private Sub Cancel_Click()
    Result = False
    Me.Hide
End Sub

'Function: next_Click
'Purpose: Creates a new group in the database and adds selected components.
'If no components selected from list none are added. (Can be modified later.)
Private Sub OK_Click()
    Dim mySQLStatement As String, resultset As rdoResultset
 
    'check for valid input values
    If Text1 = "" Or Len(Text1) > 25 Then
        MsgBox "Invalid Group Name", vbInformation
        Exit Sub
    End If
    
    If Text2 = "" Or Len(Text2) > 50 Then
        MsgBox "Invalid Group Description", vbInformation
        Exit Sub
    End If
    
    'Check to see if task name already exists
    mySQLStatement = "SELECT TaskGroupName FROM [TaskGroup] WHERE TaskGroupName = '" & Text1.text & "'"
    Set resultset = dbConnection.OpenResultset(mySQLStatement)
    
    If Not resultset.EOF Then
        MsgBox "Group name already in use.", vbInformation
        Exit Sub
    End If
    
    TaskGroupName = Text1.text
    'Create New Task In Database
    mySQLStatement = "INSERT INTO [TaskGroup] (TaskGroupName, TaskGroupDesc) VALUES ( '" & Text1 & "', '" & Text2 & "')"
    dbConnection.Execute (mySQLStatement)
    Me.Hide
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
