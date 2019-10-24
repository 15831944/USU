VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form ProgressDialog 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Operation in progress"
   ClientHeight    =   2085
   ClientLeft      =   2760
   ClientTop       =   3750
   ClientWidth     =   3960
   Icon            =   "ProgressDialog.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2085
   ScaleWidth      =   3960
   ShowInTaskbar   =   0   'False
   Begin MSComctlLib.ProgressBar ProgressBar1 
      Height          =   375
      Left            =   240
      TabIndex        =   1
      Top             =   600
      Width           =   3495
      _ExtentX        =   6165
      _ExtentY        =   661
      _Version        =   393216
      Appearance      =   1
      Scrolling       =   1
   End
   Begin VB.CommandButton CancelButton 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   1320
      TabIndex        =   0
      Top             =   1560
      Width           =   1215
   End
   Begin VB.Label Label2 
      Alignment       =   2  'Center
      Caption         =   "98% Complete"
      Height          =   375
      Left            =   1200
      TabIndex        =   3
      Top             =   1080
      Width           =   1335
   End
   Begin VB.Label Label1 
      Alignment       =   2  'Center
      Caption         =   "Risk calculation in progress..."
      Height          =   255
      Left            =   120
      TabIndex        =   2
      Top             =   240
      Width           =   3735
   End
End
Attribute VB_Name = "ProgressDialog"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Option Explicit
Public CancelPressed As Boolean
Private percentComplete As Integer
Private formloaded As Boolean
'Function:CancelButton_Click
'Purpose:handels the cancel event
Private Sub CancelButton_Click()
    CancelPressed = True
    Me.Hide
End Sub
'Function:Form_Load
'Purpose:loads the form with the current statis of the status bar
Private Sub Form_Load()
    formloaded = True
    CancelPressed = False
    ProgressBar1.Value = percentComplete
    Label2.Caption = percentComplete & "% complete"
End Sub
'Function:SetCompletion
'Purpose:displays the percentage complete information
Public Sub SetCompletion(ByVal pComplete As Integer)
    percentComplete = pComplete
    If (formloaded) Then
        ProgressBar1.Value = percentComplete
        Label2.Caption = percentComplete & "% complete"
    End If
End Sub
