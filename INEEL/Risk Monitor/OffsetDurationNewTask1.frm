VERSION 5.00
Begin VB.Form OffsetDurationNewTask 
   Caption         =   "Hours"
   ClientHeight    =   2025
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   5505
   ControlBox      =   0   'False
   Icon            =   "OffsetDurationNewTask1.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   2025
   ScaleWidth      =   5505
   StartUpPosition =   1  'CenterOwner
   Begin VB.CommandButton Cancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   375
      Left            =   1080
      TabIndex        =   2
      Top             =   1560
      Width           =   1335
   End
   Begin VB.CommandButton ok 
      Caption         =   "OK"
      Height          =   375
      Left            =   2880
      TabIndex        =   1
      Top             =   1560
      Width           =   1335
   End
   Begin VB.TextBox Text1 
      Height          =   375
      Left            =   4320
      TabIndex        =   0
      Top             =   720
      Width           =   855
   End
   Begin VB.Label Label3 
      Caption         =   "Label3"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   18
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   120
      TabIndex        =   4
      Top             =   120
      Width           =   5295
   End
   Begin VB.Label Label1 
      Caption         =   "Enter tasks' Time Offset from Group Start Time (Hours):"
      Height          =   375
      Left            =   120
      TabIndex        =   3
      Top             =   720
      Width           =   4335
   End
End
Attribute VB_Name = "OffsetDurationNewTask"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Public CancelClick As Boolean
'Function/Subroutine:cancel_Click
'Purpose:Handles the cancel event
Private Sub Cancel_Click()
    CancelClick = True
    Me.Hide
End Sub
'Function/Subroutine:Form_Load
'Purpose:Loads the form setting the name of the task at the top.
Private Sub Form_Load()
    CancelClick = False
    Label3.Caption = EditTaskGroup.nameString
    
End Sub

'Function/Subroutine:ok_Click
'Purpose:Handles the ok event
Private Sub OK_Click()
    CancelClick = False
    Me.Hide
End Sub

'Function/Subroutine:ok_KeyPress
'Purpose:makes sure the ok button is activated

Private Sub ok_KeyPress(KeyAscii As Integer)
    If KeyAscii = 13 Then
        CancelClick = False
        Me.Hide
    End If
    
End Sub
'Function/Subroutine:Text1_KeyPress
'Purpose:makes sure the ok button is activated
Private Sub Text1_KeyPress(KeyAscii As Integer)
    If KeyAscii = 13 Then
        OK_Click
    End If
End Sub
