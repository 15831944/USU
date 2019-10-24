VERSION 5.00
Object = "{86CF1D34-0C5F-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCT2.OCX"
Begin VB.Form frmScaleDate 
   Caption         =   "Set Date"
   ClientHeight    =   3840
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   7695
   ControlBox      =   0   'False
   Icon            =   "DateScale.frx":0000
   LinkTopic       =   "Form4"
   ScaleHeight     =   3840
   ScaleWidth      =   7695
   StartUpPosition =   3  'Windows Default
   Begin VB.Frame Frame2 
      Caption         =   "End Date"
      Height          =   2895
      Left            =   3960
      TabIndex        =   4
      Top             =   120
      Width           =   3375
      Begin MSComCtl2.MonthView EndView 
         Height          =   2370
         Left            =   360
         TabIndex        =   5
         Top             =   360
         Width           =   2700
         _ExtentX        =   4763
         _ExtentY        =   4180
         _Version        =   393216
         ForeColor       =   -2147483630
         BackColor       =   -2147483633
         Appearance      =   1
         StartOfWeek     =   44236801
         CurrentDate     =   37075
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "Start Time"
      Height          =   2895
      Left            =   360
      TabIndex        =   2
      Top             =   120
      Width           =   3375
      Begin MSComCtl2.MonthView StartView 
         Height          =   2370
         Left            =   360
         TabIndex        =   3
         Top             =   360
         Width           =   2700
         _ExtentX        =   4763
         _ExtentY        =   4180
         _Version        =   393216
         ForeColor       =   -2147483630
         BackColor       =   -2147483633
         Appearance      =   1
         StartOfWeek     =   44236801
         CurrentDate     =   37075
      End
   End
   Begin VB.CommandButton cancel 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   2040
      TabIndex        =   1
      Top             =   3240
      Width           =   1335
   End
   Begin VB.CommandButton ok 
      Caption         =   "OK"
      Height          =   375
      Left            =   4320
      TabIndex        =   0
      Top             =   3240
      Width           =   1335
   End
End
Attribute VB_Name = "frmScaleDate"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Public CancelClick As Boolean
'Function:cancel_Click
'Purpose:handle cancel event
Private Sub cancel_Click()
    Me.Hide
    CancelClick = True
End Sub
'Function:Form_Load
'Purpose:set initial date values
Private Sub Form_Load()

    CancelClick = False

    StartView.Value = ButtonFunctions.StartString
    EndView.Value = ButtonFunctions.EndString
    
End Sub
'Function:ok_Click
'Purpose:close window
Private Sub ok_Click()
    If EndView.Value - StartView.Value < 1 Then
        MsgBox "Workspace length must be at least one day", vbInformation
    Else
        Me.Hide
    End If
End Sub
