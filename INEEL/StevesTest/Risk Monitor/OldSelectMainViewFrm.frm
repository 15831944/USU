VERSION 5.00
Object = "{05589FA0-C356-11CE-BF01-00AA0055595A}#2.0#0"; "amcompat.tlb"
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
   Begin VB.PictureBox Picture1 
      Height          =   8895
      Left            =   0
      ScaleHeight     =   8835
      ScaleWidth      =   11355
      TabIndex        =   4
      Top             =   -600
      Width           =   11415
      Begin AMovieCtl.ActiveMovie ActiveMovie1 
         Height          =   615
         Left            =   240
         TabIndex        =   5
         Top             =   840
         Width           =   3615
         Appearance      =   0
         AutoStart       =   0   'False
         AllowChangeDisplayMode=   -1  'True
         AllowHideDisplay=   0   'False
         AllowHideControls=   -1  'True
         AutoRewind      =   -1  'True
         Balance         =   0
         CurrentPosition =   0
         DisplayBackColor=   0
         DisplayForeColor=   16777215
         DisplayMode     =   0
         Enabled         =   -1  'True
         EnableContextMenu=   -1  'True
         EnablePositionControls=   -1  'True
         EnableSelectionControls=   0   'False
         EnableTracker   =   -1  'True
         Filename        =   ""
         FullScreenMode  =   0   'False
         MovieWindowSize =   0
         PlayCount       =   1
         Rate            =   1
         SelectionStart  =   -1
         SelectionEnd    =   -1
         ShowControls    =   -1  'True
         ShowDisplay     =   -1  'True
         ShowPositionControls=   0   'False
         ShowTracker     =   -1  'True
         Volume          =   -350
      End
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
      Index           =   3
      Left            =   720
      TabIndex        =   3
      Top             =   480
      Visible         =   0   'False
      Width           =   7335
   End
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
      Index           =   2
      Left            =   840
      TabIndex        =   2
      Top             =   5280
      Visible         =   0   'False
      Width           =   7815
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
      Index           =   1
      Left            =   840
      TabIndex        =   1
      Top             =   3600
      Visible         =   0   'False
      Width           =   7815
   End
   Begin VB.Label Label1 
      BackStyle       =   0  'Transparent
      Caption         =   "Operational Tasks"
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
      Top             =   1920
      Visible         =   0   'False
      Width           =   7335
   End
   Begin VB.Image Image1 
      Height          =   9465
      Left            =   480
      Picture         =   "OldSelectMainViewFrm.frx":0000
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
Private Declare Function PlaySound Lib "winmm.dll" Alias "PlaySoundA" (ByVal lpszName As String, ByVal hModule As Long, ByVal dwFlags As Long) As Long


Private Sub ActiveMovie1_StateChange(ByVal oldState As Long, ByVal newState As Long)
    If ActiveMovie1.CurrentState = amvStopped Then
        ActiveMovie1.Visible = False
        Picture1.Visible = False
    End If
End Sub

Private Sub Form_Load()
    'AVI control setup
    'On Error Resume Next
    ActiveMovie1.filename = pidDirectory & "World4_V.AVI"
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
        Label1(0).Top = Label1(3).Top + 1440
        Label1(1).Top = Label1(0).Top + 1440
        Label1(2).Top = Label1(1).Top + 1440
        Label1(3).Top = toppos
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
Dim retval As Long
    If ActiveLabelIndex <> Index Then
        If Index <> 2 Then
            retval = PlaySound("c:\Program Files\RiskMonitor\pid\camera.wav", 0&, &H20000)
        Else
            retval = PlaySound("c:\Program Files\RiskMonitor\pid\Doorslam.wav", 0&, &H20000)
        End If
        'Play "/sounds/whoosh"
        ActiveLabelIndex = Index
        Label1(ActiveLabelIndex).ForeColor = vbHighlight
    End If
End Sub

Private Sub MMControl1_Done(NotifyCode As Integer)
    Dim DoneEvent As Integer
    DoneEvent = NotifyCode
End Sub

