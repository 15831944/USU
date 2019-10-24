VERSION 5.00
Begin VB.Form OffsetDuration 
   Caption         =   "Procedure Offset and Duration"
   ClientHeight    =   2115
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   6780
   ControlBox      =   0   'False
   Icon            =   "OffsetDuration.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   2115
   ScaleWidth      =   6780
   StartUpPosition =   1  'CenterOwner
   Begin VB.CommandButton Cancel 
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
      Left            =   1920
      TabIndex        =   3
      Top             =   1680
      Width           =   1335
   End
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
      Left            =   3720
      TabIndex        =   2
      Top             =   1680
      Width           =   1335
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
      Left            =   5760
      TabIndex        =   1
      Top             =   1080
      Width           =   855
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
      Left            =   5760
      TabIndex        =   0
      Top             =   600
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
      Height          =   375
      Left            =   120
      TabIndex        =   6
      Top             =   120
      Width           =   5295
   End
   Begin VB.Label Label2 
      Caption         =   "Enter Procedures' Time Duration (Hours):"
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
      TabIndex        =   5
      Top             =   1080
      Width           =   5535
   End
   Begin VB.Label Label1 
      Caption         =   "Enter Procedures' Time Offset from Task Start Time (Hours):"
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
      TabIndex        =   4
      Top             =   600
      Width           =   5415
   End
End
Attribute VB_Name = "OffsetDuration"
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
'Purpose:Sets the procedure name as form caption and loads form
Private Sub Form_Load()
    CancelClick = False
    Label3.Caption = EditTask.nameString
End Sub

'Function/Subroutine:ok_Click
'Purpose:Handles ok evnt
Private Sub OK_Click()
    CancelClick = False
    Me.Hide
End Sub
'Function/Subroutine:Text1_KeyPress
'Purpose:sets the focus
Private Sub Text1_KeyPress(KeyAscii As Integer)
    If KeyAscii = 13 Then
        Text2.SetFocus
    End If

End Sub
'Function/Subroutine:Text2_KeyPress
'Purpose:sets the focus
Private Sub Text2_KeyPress(KeyAscii As Integer)
    If KeyAscii = 13 Then
        OK_Click
    End If

End Sub
