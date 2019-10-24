VERSION 5.00
Begin VB.Form SelectMainViewFrm 
   Caption         =   "Situation Awareness and Risk Monitor Application"
   ClientHeight    =   9510
   ClientLeft      =   2775
   ClientTop       =   3765
   ClientWidth     =   12330
   BeginProperty Font 
      Name            =   "Arial"
      Size            =   9.75
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   LinkTopic       =   "Form1"
   ScaleHeight     =   9510
   ScaleWidth      =   12330
   StartUpPosition =   2  'CenterScreen
   Begin VB.Label Label1 
      BackStyle       =   0  'Transparent
      Caption         =   "Exit"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   36
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H8000000E&
      Height          =   1095
      Index           =   3
      Left            =   840
      TabIndex        =   3
      Top             =   5760
      Visible         =   0   'False
      Width           =   2055
   End
   Begin VB.Label Label1 
      BackStyle       =   0  'Transparent
      Caption         =   "Risk Meter"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   36
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H8000000E&
      Height          =   1095
      Index           =   2
      Left            =   840
      TabIndex        =   2
      Top             =   4440
      Visible         =   0   'False
      Width           =   4215
   End
   Begin VB.Label Label1 
      BackStyle       =   0  'Transparent
      Caption         =   "Task Scheduler"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   36
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H8000000E&
      Height          =   1095
      Index           =   1
      Left            =   840
      TabIndex        =   1
      Top             =   2880
      Visible         =   0   'False
      Width           =   7215
   End
   Begin VB.Label Label1 
      BackStyle       =   0  'Transparent
      Caption         =   "Risk Monitor Setup"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   36
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H8000000E&
      Height          =   1095
      Index           =   0
      Left            =   840
      TabIndex        =   0
      Top             =   1320
      Visible         =   0   'False
      Width           =   8655
   End
   Begin VB.Image Image1 
      Height          =   9465
      Left            =   0
      Picture         =   "SelectMainViewFrm.frx":0000
      Stretch         =   -1  'True
      Top             =   0
      Visible         =   0   'False
      Width           =   12300
   End
End
Attribute VB_Name = "SelectMainViewFrm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Public OptionSelected As Integer
Private ActiveLabelIndex As Integer
Private Declare Function MessageBeep Lib "user32" (ByVal wType As Long) As Long

Private Sub Form_Load()
    ActiveLabelIndex = -1
    Form_Resize
    Image1.Visible = True
    Label1(0).Visible = True
    Label1(1).Visible = True
    Label1(2).Visible = True
    Label1(3).Visible = True
End Sub

Private Sub Form_Resize()
    If ScaleHeight > 6000 Then
        Image1.Height = ScaleHeight
        Image1.Width = ScaleWidth
        Dim toppos As Integer
        toppos = (ScaleHeight - 1440 * 4) / 2
        Label1(0).Top = toppos
        Label1(1).Top = Label1(0).Top + 1440
        Label1(2).Top = Label1(1).Top + 1440
        Label1(3).Top = Label1(2).Top + 1440
        Label1(0).Left = ScaleWidth / 4
        Label1(1).Left = ScaleWidth / 4
        Label1(2).Left = ScaleWidth / 4
        Label1(3).Left = ScaleWidth / 4
    End If
End Sub

Private Sub Image1_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
    If (ActiveLabelIndex >= 0) Then
        Label1(0).ForeColor = vbHighlightText
        Label1(1).ForeColor = vbHighlightText
        Label1(2).ForeColor = vbHighlightText
        Label1(3).ForeColor = vbHighlightText
    End If
    ActiveLabelIndex = -1
End Sub

Private Sub Label1_Click(Index As Integer)
    OptionSelected = Index
    Me.Hide
End Sub

Private Sub Label1_MouseMove(Index As Integer, Button As Integer, Shift As Integer, X As Single, Y As Single)
    If ActiveLabelIndex <> Index Then
        MessageBeep 16
        ActiveLabelIndex = Index
        Label1(ActiveLabelIndex).ForeColor = vbHighlight
    End If
End Sub
