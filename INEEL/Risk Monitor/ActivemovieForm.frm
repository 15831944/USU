VERSION 5.00
Object = "{05589FA0-C356-11CE-BF01-00AA0055595A}#2.0#0"; "amcompat.tlb"
Begin VB.Form ActivemovieForm 
   Caption         =   "Movie"
   ClientHeight    =   7500
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   9450
   LinkTopic       =   "Form1"
   ScaleHeight     =   7500
   ScaleWidth      =   9450
   StartUpPosition =   3  'Windows Default
   Visible         =   0   'False
   Begin VB.PictureBox Picture1 
      Height          =   7335
      Left            =   120
      ScaleHeight     =   7275
      ScaleWidth      =   8715
      TabIndex        =   0
      Top             =   120
      Width           =   8775
      Begin AMovieCtl.ActiveMovie ActiveMovie1 
         Height          =   975
         Left            =   120
         TabIndex        =   1
         Top             =   120
         Width           =   2175
         Appearance      =   0
         AutoStart       =   -1  'True
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
         Volume          =   -290
      End
   End
End
Attribute VB_Name = "ActivemovieForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Sub ActiveMovie1_StateChange(ByVal oldState As Long, ByVal newState As Long)
    If ActiveMovie1.CurrentState = amvStopped Then
        ActiveMovie1.Visible = False
        Picture1.Visible = False
        
        
    End If

End Sub



Private Sub Form_Load()
    'AVI control setup
    On Error Resume Next
    Picture1.Visible = True
    ActiveMovie1.Visible = True
    If ActiveMovieFile <> "" Then
        ActiveMovie1.filename = ActiveMovieFile
    End If
    'ActiveMovie1.filename = "C:\Program Files\RiskMonitor\pid\ISS1.avi"
    ActivemovieForm.SetFocus

End Sub

Private Sub Form_Unload(cancel As Integer)
If ActiveMovie1.CurrentState <> amvStopped Then
    ActiveMovieFile = ""
    ActiveMovie1.Stop
End If
End Sub
