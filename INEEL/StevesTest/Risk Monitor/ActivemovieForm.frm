VERSION 5.00
Object = "{05589FA0-C356-11CE-BF01-00AA0055595A}#2.0#0"; "AMOVIE.OCX"
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
         _ExtentX        =   3836
         _ExtentY        =   1720
         EnableSelectionControls=   0   'False
         AllowHideDisplay=   0   'False
         AutoStart       =   -1  'True
         SelectionStart  =   -1
         Appearance      =   0
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

Private Sub Form_Unload(Cancel As Integer)
If ActiveMovie1.CurrentState <> amvStopped And ActiveMovie1.filename <> "" Then
    ActiveMovieFile = ""
    ActiveMovie1.Stop
End If
End Sub

