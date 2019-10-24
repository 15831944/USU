VERSION 5.00
Begin VB.Form SaphireStats 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "SAPHIRE Statistics"
   ClientHeight    =   1920
   ClientLeft      =   2760
   ClientTop       =   3750
   ClientWidth     =   6030
   Icon            =   "TestDialog.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1920
   ScaleWidth      =   6030
   ShowInTaskbar   =   0   'False
   Begin VB.TextBox TotalUpdates 
      BackColor       =   &H80000000&
      Height          =   375
      Left            =   4080
      Locked          =   -1  'True
      TabIndex        =   4
      Text            =   "Text2"
      Top             =   720
      Width           =   1335
   End
   Begin VB.TextBox AverageTime 
      BackColor       =   &H80000004&
      Height          =   375
      Left            =   4080
      Locked          =   -1  'True
      TabIndex        =   3
      Text            =   "Text1"
      Top             =   240
      Width           =   1335
   End
   Begin VB.CommandButton OKButton 
      Caption         =   "OK"
      Height          =   375
      Left            =   2280
      TabIndex        =   0
      Top             =   1320
      Width           =   1215
   End
   Begin VB.Label Label2 
      Caption         =   "Total risk periods updated"
      Height          =   375
      Left            =   360
      TabIndex        =   2
      Top             =   720
      Width           =   3615
   End
   Begin VB.Label Label1 
      Caption         =   "Average time per individual risk period update (ms)"
      Height          =   375
      Left            =   360
      TabIndex        =   1
      Top             =   240
      Width           =   3615
   End
End
Attribute VB_Name = "SaphireStats"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Option Explicit

Private Sub OKButton_Click()
    Unload Me
End Sub
