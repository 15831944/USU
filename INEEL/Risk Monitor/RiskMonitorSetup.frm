VERSION 5.00
Begin VB.Form RiskMonitorSetup 
   Caption         =   "Setup"
   ClientHeight    =   3465
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   6675
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
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3465
   ScaleWidth      =   6675
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Command3 
      Caption         =   "Create Operational Hierarchy"
      Height          =   495
      Left            =   1320
      TabIndex        =   3
      Top             =   2520
      Width           =   4095
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Map SAPHIRE BEs to Base Components"
      Height          =   495
      Left            =   1320
      TabIndex        =   2
      Top             =   1680
      Width           =   4095
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Risk Model / Mode Setup"
      Height          =   495
      Left            =   1320
      TabIndex        =   1
      Top             =   840
      Width           =   4095
   End
   Begin VB.Label Label1 
      Alignment       =   2  'Center
      Caption         =   "Risk Monitor for SAPHIRE Setup"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   15.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   6375
   End
End
Attribute VB_Name = "RiskMonitorSetup"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
    ' call the ModeSetupForm here
End Sub

Private Sub Command2_Click()
    If Module1.DBConnect2("MapDB") Then
        MappingWizard.Show vbModal
    Else
        MsgBox "Failed to connected to MapDB"
    End If
End Sub


Private Sub Command3_Click()
    MDIMain.compMap.FormMode = Edit
    MDIMain.compMap.CompDiagram.ShowToolboxOnRightClick = True
    MDIMain.compMap.Show 0
End Sub
