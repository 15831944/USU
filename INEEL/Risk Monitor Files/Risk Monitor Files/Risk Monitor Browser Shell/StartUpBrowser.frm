VERSION 5.00
Object = "{EAB22AC0-30C1-11CF-A7EB-0000C05BAE0B}#1.1#0"; "SHDOCVW.DLL"
Begin VB.Form frmBrowser 
   ClientHeight    =   5385
   ClientLeft      =   3060
   ClientTop       =   3345
   ClientWidth     =   6675
   LinkTopic       =   "Form1"
   MDIChild        =   -1  'True
   ScaleHeight     =   5385
   ScaleWidth      =   6675
   ShowInTaskbar   =   0   'False
   Begin SHDocVwCtl.WebBrowser brwWebBrowser 
      Height          =   5040
      Left            =   240
      TabIndex        =   0
      Top             =   120
      Width           =   6240
      ExtentX         =   11007
      ExtentY         =   8890
      ViewMode        =   1
      Offline         =   0
      Silent          =   0
      RegisterAsBrowser=   0
      RegisterAsDropTarget=   0
      AutoArrange     =   -1  'True
      NoClientEdge    =   -1  'True
      AlignLeft       =   0   'False
      NoWebView       =   0   'False
      HideFileNames   =   0   'False
      SingleClick     =   0   'False
      SingleSelection =   0   'False
      NoFolders       =   0   'False
      Transparent     =   0   'False
      ViewID          =   "{0057D0E0-3573-11CF-AE69-08002B2E1262}"
      Location        =   "http:///"
   End
End
Attribute VB_Name = "frmBrowser"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Public StartingAddress As String
Dim mbDontNavigateNow As Boolean
Private Sub Form_Load()
    On Error Resume Next
    Me.Show
    MsgBox ("I'm being shown")
    brwWebBrowser.Navigate "C:\Program Files\Microsoft Visual Studio\VB98\UserDocument1.vbd"

    Me.Caption = "Risk Monitor for SAPHIRE" 'brwWebBrowser.LocationName
    Form_Resize
End Sub

Private Sub Form_Resize()
    If (Me.ScaleWidth > 100 And Me.ScaleHeight > 100) Then
        brwWebBrowser.Width = Me.ScaleWidth - 100
        brwWebBrowser.Height = Me.ScaleHeight - 100
    Else
        brwWebBrowser.Width = 0
        brwWebBrowser.Height = 0
    End If
End Sub

