VERSION 5.00
Object = "{86CF1D34-0C5F-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCT2.OCX"
Begin VB.Form TimeEdit 
   Caption         =   "Time Edit"
   ClientHeight    =   5160
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   7170
   ControlBox      =   0   'False
   Icon            =   "TimeEdit.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   5160
   ScaleWidth      =   7170
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton ok 
      Caption         =   "OK"
      Height          =   375
      Left            =   4200
      TabIndex        =   0
      Top             =   4560
      Width           =   2055
   End
   Begin VB.CommandButton cancel 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   1200
      TabIndex        =   7
      Top             =   4560
      Width           =   1815
   End
   Begin VB.Frame Frame2 
      Caption         =   "End Time"
      Height          =   3735
      Left            =   3720
      TabIndex        =   6
      Top             =   600
      Width           =   3255
      Begin VB.ComboBox EndCombo 
         Height          =   315
         Left            =   600
         Style           =   2  'Dropdown List
         TabIndex        =   4
         Top             =   3000
         Width           =   2055
      End
      Begin MSComCtl2.MonthView EndView 
         Height          =   2370
         Left            =   240
         TabIndex        =   3
         Top             =   360
         Width           =   2700
         _ExtentX        =   4763
         _ExtentY        =   4180
         _Version        =   393216
         ForeColor       =   -2147483630
         BackColor       =   -2147483633
         Appearance      =   1
         StartOfWeek     =   22872065
         CurrentDate     =   37075
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "Start Time"
      Height          =   3735
      Left            =   240
      TabIndex        =   5
      Top             =   600
      Width           =   3255
      Begin VB.ComboBox StartCombo 
         Height          =   315
         Left            =   600
         Style           =   2  'Dropdown List
         TabIndex        =   2
         Top             =   3000
         Width           =   1935
      End
      Begin MSComCtl2.MonthView StartView 
         Height          =   2370
         Left            =   240
         TabIndex        =   1
         Top             =   360
         Width           =   2700
         _ExtentX        =   4763
         _ExtentY        =   4180
         _Version        =   393216
         ForeColor       =   -2147483630
         BackColor       =   -2147483633
         Appearance      =   1
         StartOfWeek     =   22872065
         CurrentDate     =   37075
      End
   End
   Begin VB.Label Label1 
      Caption         =   "Label1"
      Height          =   375
      Left            =   240
      TabIndex        =   8
      Top             =   120
      Width           =   6735
   End
End
Attribute VB_Name = "TimeEdit"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Public CancelClick As Boolean
Public LabelText As String
Public StartDate As Date
Public EndDate As Date

'Function:cancel_Click
'Purpose:handles the event when cancel is clicked
Private Sub cancel_Click()
    CancelClick = True
    Me.Hide
End Sub
'Function:Form_Load
'Purpose:load the form with initial dates and times
Private Sub Form_Load()
    CancelClick = False
    
    Label1.Caption = LabelText
    StartView.Value = DatePart("m", StartDate) & "/" & DatePart("d", StartDate) & "/" & DatePart("yyyy", StartDate)
    EndView.Value = DatePart("m", EndDate) & "/" & DatePart("d", EndDate) & "/" & DatePart("yyyy", EndDate)
    
    StartCombo.AddItem "0:00"
    StartCombo.AddItem "1:00"
    StartCombo.AddItem "2:00"
    StartCombo.AddItem "3:00"
    StartCombo.AddItem "4:00"
    StartCombo.AddItem "5:00"
    StartCombo.AddItem "6:00"
    StartCombo.AddItem "7:00"
    StartCombo.AddItem "8:00"
    StartCombo.AddItem "9:00"
    StartCombo.AddItem "10:00"
    StartCombo.AddItem "11:00"
    StartCombo.AddItem "12:00"
    StartCombo.AddItem "13:00"
    StartCombo.AddItem "14:00"
    StartCombo.AddItem "15:00"
    StartCombo.AddItem "16:00"
    StartCombo.AddItem "17:00"
    StartCombo.AddItem "18:00"
    StartCombo.AddItem "19:00"
    StartCombo.AddItem "20:00"
    StartCombo.AddItem "21:00"
    StartCombo.AddItem "22:00"
    StartCombo.AddItem "23:00"
    
    EndCombo.AddItem "0:00"
    EndCombo.AddItem "1:00"
    EndCombo.AddItem "2:00"
    EndCombo.AddItem "3:00"
    EndCombo.AddItem "4:00"
    EndCombo.AddItem "5:00"
    EndCombo.AddItem "6:00"
    EndCombo.AddItem "7:00"
    EndCombo.AddItem "8:00"
    EndCombo.AddItem "9:00"
    EndCombo.AddItem "10:00"
    EndCombo.AddItem "11:00"
    EndCombo.AddItem "12:00"
    EndCombo.AddItem "13:00"
    EndCombo.AddItem "14:00"
    EndCombo.AddItem "15:00"
    EndCombo.AddItem "16:00"
    EndCombo.AddItem "17:00"
    EndCombo.AddItem "18:00"
    EndCombo.AddItem "19:00"
    EndCombo.AddItem "20:00"
    EndCombo.AddItem "21:00"
    EndCombo.AddItem "22:00"
    EndCombo.AddItem "23:00"
    
End Sub
'Function:ok_Click
'Purpose:get the date that the user enterd or the default, close form
Private Sub ok_Click()
    Dim temp As Date
    
    Me.Hide
    
    If StartCombo.text = "" Then
        StartDate = "00:00:00 " & StartView.Value
    Else
        StartDate = StartCombo & ":00 " & StartView.Value
    End If
    
    If EndCombo.text = "" Then
        EndDate = "00:00:00 " & EndView.Value
    Else
        EndDate = EndCombo & ":00 " & EndView.Value
    End If
    
    If StartDate > EndDate Then
        temp = StartDate
        StartDate = EndDate
        EndDate = temp
    End If
    
    
End Sub

