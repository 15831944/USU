VERSION 5.00
Object = "{86CF1D34-0C5F-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCT2.OCX"
Begin VB.Form ModeTimeChange 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Mode Time"
   ClientHeight    =   4815
   ClientLeft      =   2760
   ClientTop       =   3750
   ClientWidth     =   3705
   ControlBox      =   0   'False
   Icon            =   "ModeTimeChange.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4815
   ScaleWidth      =   3705
   ShowInTaskbar   =   0   'False
   Begin VB.ComboBox Combo1 
      Height          =   315
      Left            =   480
      TabIndex        =   3
      Text            =   "0:00"
      Top             =   3600
      Width           =   2700
   End
   Begin MSComCtl2.MonthView MonthView1 
      Height          =   2370
      Left            =   480
      TabIndex        =   2
      Top             =   960
      Width           =   2700
      _ExtentX        =   4763
      _ExtentY        =   4180
      _Version        =   393216
      ForeColor       =   -2147483630
      BackColor       =   -2147483633
      Appearance      =   1
      StartOfWeek     =   22937601
      CurrentDate     =   37102
   End
   Begin VB.CommandButton CancelButton 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   1920
      TabIndex        =   1
      Top             =   4200
      Width           =   1215
   End
   Begin VB.CommandButton OKButton 
      Caption         =   "OK"
      Height          =   375
      Left            =   480
      TabIndex        =   0
      Top             =   4200
      Width           =   1215
   End
   Begin VB.Label Label2 
      Caption         =   "Select New Start Date:"
      Height          =   375
      Left            =   480
      TabIndex        =   5
      Top             =   720
      Width           =   3495
   End
   Begin VB.Label Label1 
      Caption         =   "Label1"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   0
      TabIndex        =   4
      Top             =   240
      Width           =   3615
   End
End
Attribute VB_Name = "ModeTimeChange"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Option Explicit

'variables must be set before form load is called
Public StartTime As Date
Public modeID As Integer
Public aWS As Workspace
Public myName As String
Public CancelClick As Boolean

'Function:CancelButton_Click
'Purpose:Handles the cancel event
Private Sub CancelButton_Click()
    CancelClick = True
    Me.Hide
End Sub
'Function:Form_Load
'Purpose:loads initial data into form
Private Sub Form_Load()
    CancelClick = False
    Label1.Caption = myName
    MonthView1.Value = StartTime
    
    Combo1.AddItem "0:00"
    Combo1.AddItem "1:00"
    Combo1.AddItem "2:00"
    Combo1.AddItem "3:00"
    Combo1.AddItem "4:00"
    Combo1.AddItem "5:00"
    Combo1.AddItem "6:00"
    Combo1.AddItem "7:00"
    Combo1.AddItem "8:00"
    Combo1.AddItem "9:00"
    Combo1.AddItem "10:00"
    Combo1.AddItem "11:00"
    Combo1.AddItem "12:00"
    Combo1.AddItem "13:00"
    Combo1.AddItem "14:00"
    Combo1.AddItem "15:00"
    Combo1.AddItem "16:00"
    Combo1.AddItem "17:00"
    Combo1.AddItem "18:00"
    Combo1.AddItem "19:00"
    Combo1.AddItem "20:00"
    Combo1.AddItem "21:00"
    Combo1.AddItem "22:00"
    Combo1.AddItem "23:00"
End Sub
'Function:OKButton_Click
'Purpose:handles the ok event. Sets the start time to the
'value the user input.
Private Sub OKButton_Click()
'
    Me.Hide
    
    If Combo1 = "" Then
        StartTime = "00:00:00 " & MonthView1.Month & "/" & MonthView1.Day & "/" & MonthView1.year
    Else
        StartTime = Combo1.text & " " & MonthView1.Month & "/" & MonthView1.Day & "/" & MonthView1.year
    End If
End Sub
