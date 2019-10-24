VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form PickParent 
   Caption         =   "Parent Diagram Properties"
   ClientHeight    =   1800
   ClientLeft      =   60
   ClientTop       =   405
   ClientWidth     =   4110
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   ScaleHeight     =   1800
   ScaleWidth      =   4110
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton OKButton 
      Caption         =   "OK"
      Height          =   375
      Left            =   1680
      TabIndex        =   4
      Top             =   1320
      Width           =   855
   End
   Begin VB.CommandButton BrowseButton 
      Caption         =   "Browse"
      Height          =   375
      Left            =   3240
      TabIndex        =   3
      Top             =   720
      Width           =   735
   End
   Begin VB.TextBox Text1 
      Height          =   375
      Left            =   1320
      TabIndex        =   1
      Top             =   720
      Width           =   1695
   End
   Begin VB.CheckBox HasParent 
      Caption         =   "Has Parent Diagram"
      Height          =   255
      Left            =   360
      TabIndex        =   0
      Top             =   240
      Width           =   2295
   End
   Begin MSComDlg.CommonDialog PickFile 
      Left            =   120
      Top             =   1200
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
      CancelError     =   -1  'True
   End
   Begin VB.Label Label1 
      Caption         =   "File Name"
      Height          =   255
      Left            =   360
      TabIndex        =   2
      Top             =   720
      Width           =   855
   End
End
Attribute VB_Name = "PickParent"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Public pFileName As String
Public hasParentD As Boolean
Private Sub BrowseButton_Click()
    PickFile.ShowOpen
    Text1.Text = PickFile.FileTitle
End Sub

Private Sub OKButton_Click()
    hasParentD = HasParent.Value
    If HasParent.Value = True Then
        If Text1.Text = "" Then
            MsgBox "You must select a parent file name"
        Else
            pFileName = Text1.Text
            Me.Hide
        End If
    Else
        Me.Hide
    End If
End Sub
