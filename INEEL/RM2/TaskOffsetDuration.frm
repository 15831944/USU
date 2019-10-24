VERSION 5.00
Begin VB.Form TaskOffsetDuration 
   Caption         =   "Task Offset and Duration"
   ClientHeight    =   2025
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   5535
   ControlBox      =   0   'False
   Icon            =   "TaskOffsetDuration.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   2025
   ScaleWidth      =   5535
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox Text1 
      Height          =   375
      Left            =   4560
      TabIndex        =   0
      Top             =   720
      Width           =   855
   End
   Begin VB.CommandButton ok 
      Caption         =   "OK"
      Height          =   375
      Left            =   2880
      TabIndex        =   1
      Top             =   1440
      Width           =   1335
   End
   Begin VB.CommandButton Cancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   375
      Left            =   1080
      TabIndex        =   2
      Top             =   1440
      Width           =   1335
   End
   Begin VB.Label Label1 
      Caption         =   "Enter Tasks' Time Offset from Task Group Start Time (Hours):"
      Height          =   375
      Left            =   120
      TabIndex        =   4
      Top             =   720
      Width           =   4335
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
      Height          =   375
      Left            =   120
      TabIndex        =   3
      Top             =   0
      Width           =   5295
   End
End
Attribute VB_Name = "TaskOffsetDuration"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Public CancelClick As Boolean
'Function/Subroutine:cancel_Click
'Purpose:handles the cancel event
Private Sub Cancel_Click()
    CancelClick = True
    Me.Hide
End Sub
'Function/Subroutine:Form_Load
'Purpose:loads the form with the name from the calling form
Private Sub Form_Load()
    CancelClick = False
    Label3.Caption = frmNewGroup.TaskGroupName
End Sub


'Function/Subroutine:ok_Click
'Purpose:handles the ok click event
Private Sub OK_Click()
    Me.Hide
End Sub
'Function/Subroutine:Text1_KeyPress
'Purpose: make sure the focus is on the ok button
Private Sub Text1_KeyPress(KeyAscii As Integer)
    If KeyAscii = 13 Then
        ok.SetFocus
    End If
End Sub
