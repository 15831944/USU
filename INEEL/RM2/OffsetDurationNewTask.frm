VERSION 5.00
Begin VB.Form OffsetDuration 
   Caption         =   "Enter Offset and Duration"
   ClientHeight    =   2340
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   5175
   ControlBox      =   0   'False
   Icon            =   "OffsetDurationNewTask.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   2340
   ScaleWidth      =   5175
   StartUpPosition =   1  'CenterOwner
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
      Left            =   4080
      TabIndex        =   0
      Text            =   "0"
      Top             =   720
      Width           =   855
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
      Left            =   4080
      TabIndex        =   1
      Text            =   "1"
      Top             =   1200
      Width           =   855
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
      Left            =   2640
      TabIndex        =   2
      Top             =   1800
      Width           =   1335
   End
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
      Left            =   1080
      TabIndex        =   3
      Top             =   1800
      Width           =   1335
   End
   Begin VB.Label Label1 
      Caption         =   "Enter Offset from Start Time (Hours)"
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
      TabIndex        =   6
      Top             =   720
      Width           =   3255
   End
   Begin VB.Label Label2 
      Caption         =   "Enter Duration (Hours)"
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
      TabIndex        =   5
      Top             =   1200
      Width           =   3375
   End
   Begin VB.Label ObjectNameLabel 
      Caption         =   "[ObjectNameLabel]"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   18
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   120
      TabIndex        =   4
      Top             =   120
      Width           =   4695
   End
End
Attribute VB_Name = "OffsetDuration"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Option Explicit
Public CancelClick As Boolean
Public ObjectLabel As String

'Function/Subroutine:cancel_Click
'Purpose:handles cancel event
Private Sub Cancel_Click()
    CancelClick = True
    Me.Hide
End Sub
'Function/Subroutine:Form_Load
'Purpose:Set the procedure name as label and load form
Private Sub Form_Load()
    ObjectNameLabel.Caption = ObjectLabel
End Sub
'Function/Subroutine:ok_Click
'Purpose:handles the ok event
Private Sub OK_Click()
    CancelClick = False
    Me.Hide
End Sub

'Function/Subroutine:ok_KeyPress
'Purpose: hitting enter is equivilent to pressing ok.
Private Sub ok_KeyPress(KeyAscii As Integer)
    If KeyAscii = 13 Then
        OK_Click
    End If
End Sub

'Function/Subroutine:Text1_KeyPress
'Purpose:Set focus on correct form elemnt
Private Sub Text1_KeyPress(KeyAscii As Integer)
    If KeyAscii = 13 Then
        Text2.SetFocus
    End If
End Sub

'Function/Subroutine:Text2_KeyPress
'Purpose: set focus on ok button
Private Sub Text2_KeyPress(KeyAscii As Integer)
    If KeyAscii = 13 Then
        OK_Click
    End If
End Sub
