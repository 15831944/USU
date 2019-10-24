VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form DiagramProperties 
   Caption         =   "Diagram Properties"
   ClientHeight    =   3630
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   3930
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   ScaleHeight     =   3630
   ScaleWidth      =   3930
   StartUpPosition =   3  'Windows Default
   Begin MSComDlg.CommonDialog FindFile 
      Left            =   3000
      Top             =   2040
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
      CancelError     =   -1  'True
      DialogTitle     =   "Select Diagram File"
      Filter          =   "Picture Files (*.jpg, *.bmp, *.gif)"
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   2040
      TabIndex        =   9
      Top             =   3000
      Width           =   975
   End
   Begin VB.CommandButton Command1 
      Caption         =   "OK"
      Height          =   375
      Left            =   360
      TabIndex        =   8
      Top             =   3000
      Width           =   975
   End
   Begin VB.TextBox Text3 
      Height          =   375
      Left            =   1320
      TabIndex        =   7
      Text            =   "8"
      Top             =   2160
      Width           =   855
   End
   Begin VB.CommandButton BrowseFile 
      Caption         =   "..."
      Height          =   375
      Left            =   3000
      TabIndex        =   5
      Top             =   1560
      Width           =   495
   End
   Begin VB.TextBox Text2 
      Height          =   375
      Left            =   240
      TabIndex        =   4
      Top             =   1560
      Width           =   2655
   End
   Begin VB.CommandButton BrowseFolder 
      Caption         =   "..."
      Height          =   375
      Left            =   3000
      TabIndex        =   2
      Top             =   600
      Width           =   495
   End
   Begin VB.TextBox Text1 
      Height          =   375
      Left            =   240
      TabIndex        =   1
      Text            =   "C:\Program Files\RiskMonitor\pid"
      Top             =   600
      Width           =   2655
   End
   Begin VB.Label Label3 
      Caption         =   "Square size"
      Height          =   255
      Left            =   240
      TabIndex        =   6
      Top             =   2280
      Width           =   855
   End
   Begin VB.Label Label2 
      Caption         =   "Initial Diagram File"
      Height          =   255
      Left            =   240
      TabIndex        =   3
      Top             =   1200
      Width           =   1335
   End
   Begin VB.Label Label1 
      Caption         =   "Diagram Folder"
      Height          =   255
      Left            =   240
      TabIndex        =   0
      Top             =   240
      Width           =   1455
   End
End
Attribute VB_Name = "DiagramProperties"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Public result As Boolean

Private Sub BrowseFile_Click()
    On Error GoTo filecancel
    FindFile.InitDir = Text1
    FindFile.ShowOpen
    Text2 = FindFile.FileTitle
    Exit Sub
filecancel:
End Sub

Private Sub BrowseFolder_Click()
    Dim fName As String
    fName = BrowseForFolder("Select folder for diagrams")
    If fName <> "" Then
        Text1 = fName
    End If
End Sub

Private Sub Command1_Click()
    result = True
    Me.Hide
End Sub

Private Sub Command2_Click()
    result = False
    Me.Hide
End Sub
