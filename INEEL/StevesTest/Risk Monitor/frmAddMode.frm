VERSION 5.00
Object = "{86CF1D34-0C5F-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCT2.OCX"
Begin VB.Form frmAddMode 
   Caption         =   "Add Mode"
   ClientHeight    =   5790
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   3840
   ControlBox      =   0   'False
   Icon            =   "frmAddMode.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   5790
   ScaleWidth      =   3840
   StartUpPosition =   3  'Windows Default
   Begin VB.Frame Frame1 
      Caption         =   "Start Date"
      Height          =   3135
      Left            =   240
      TabIndex        =   6
      Top             =   960
      Width           =   3375
      Begin MSComCtl2.MonthView MonthView1 
         Height          =   2370
         Left            =   360
         TabIndex        =   7
         Top             =   480
         Width           =   2700
         _ExtentX        =   4763
         _ExtentY        =   4180
         _Version        =   393216
         ForeColor       =   -2147483630
         BackColor       =   -2147483633
         Appearance      =   1
         StartOfWeek     =   22937601
         CurrentDate     =   37075
      End
   End
   Begin VB.CommandButton ok 
      Caption         =   "OK"
      Height          =   375
      Left            =   2160
      TabIndex        =   0
      Top             =   5160
      Width           =   1335
   End
   Begin VB.CommandButton cancel 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   360
      TabIndex        =   1
      Top             =   5160
      Width           =   1335
   End
   Begin VB.ComboBox Combo3 
      Height          =   315
      Left            =   240
      Style           =   2  'Dropdown List
      TabIndex        =   3
      Top             =   360
      Width           =   3375
   End
   Begin VB.ComboBox Combo6 
      Height          =   315
      Left            =   240
      Style           =   2  'Dropdown List
      TabIndex        =   2
      Top             =   4560
      Width           =   3375
   End
   Begin VB.Label Label1 
      Caption         =   "Mode"
      Height          =   255
      Left            =   240
      TabIndex        =   5
      Top             =   120
      Width           =   1695
   End
   Begin VB.Label Label2 
      Caption         =   "Start Time"
      Height          =   375
      Left            =   240
      TabIndex        =   4
      Top             =   4320
      Width           =   975
   End
End
Attribute VB_Name = "frmAddMode"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private RowReturn As Integer
Private rArray As Variant
Public CancelClick As Boolean
Public modeID As Integer
'Function/Subroutine:cancel_Click
'Purpose: handles the event when cancel is clicked
Private Sub cancel_Click()
    Me.Hide
    CancelClick = True
End Sub

'Function/Subroutine:Combo3_KeyPress
'Purpose:handles the event when enter is pressed over the combo box
Private Sub Combo3_KeyPress(KeyAscii As Integer)
    If KeyAscii = 13 Then
        ok_Click
    End If
End Sub
'Function/Subroutine:Combo6_KeyPress
'Purpose:handles the event when enter is pressed over the combo box
Private Sub Combo6_KeyPress(KeyAscii As Integer)
    If KeyAscii = 13 Then
        ok_Click
    End If
End Sub
'Function/Subroutine:Form_Load
'Purpose:load comboboxes from mode table
Private Sub Form_Load()

    CancelClick = False

Dim resultSet As rdoResultset

    Dim mySQLStatement As String
    Dim i As Integer
    
    RowReturn = 0
    
    'get lise of modes
    mySQLStatement = "SELECT ModeID, ModeName FROM Mode"
    
    Set resultSet = dbConnection.OpenResultset(mySQLStatement, rdOpenKeyset)
    ' Run time error 40071 will be generated if no connection is present by this statement

    'check to make sure result was returned
    If (resultSet.EOF) Then
        MsgBox "No Modes Found", vbInformation
        Exit Sub
    End If
    
    'determine number of rows
    While Not resultSet.EOF
        resultSet.MoveNext
        RowReturn = RowReturn + 1
    Wend
    
    'get specified number of rows
    resultSet.MoveFirst
    rArray = resultSet.GetRows(RowReturn)
    'MsgBox Str(RowReturn)
    
    For i = 0 To RowReturn - 1
        If rArray(0, i) > 0 Then
            Combo3.AddItem rArray(1, i)
        End If
    Next i
    

    'Set up static boxes
    
    Combo6.AddItem "0:00"
    Combo6.AddItem "1:00"
    Combo6.AddItem "2:00"
    Combo6.AddItem "3:00"
    Combo6.AddItem "4:00"
    Combo6.AddItem "5:00"
    Combo6.AddItem "6:00"
    Combo6.AddItem "7:00"
    Combo6.AddItem "8:00"
    Combo6.AddItem "9:00"
    Combo6.AddItem "10:00"
    Combo6.AddItem "11:00"
    Combo6.AddItem "12:00"
    Combo6.AddItem "13:00"
    Combo6.AddItem "14:00"
    Combo6.AddItem "15:00"
    Combo6.AddItem "16:00"
    Combo6.AddItem "17:00"
    Combo6.AddItem "18:00"
    Combo6.AddItem "19:00"
    Combo6.AddItem "20:00"
    Combo6.AddItem "21:00"
    Combo6.AddItem "22:00"
    Combo6.AddItem "23:00"
   
    
End Sub
'Function/Subroutine:ok_Click
'Purpose: get mode ID and hide form
Private Sub ok_Click()
    Dim i As Integer

    Me.Hide
    
    modeID = -1
    
    For i = 0 To RowReturn - 1
        If Combo3.text = rArray(1, i) Then
            modeID = rArray(0, i)
        End If
    Next i
End Sub
'Function/Subroutine:Text2_KeyPress
'Purpose:handles the event when enter is pressed
Private Sub Text2_KeyPress(KeyAscii As Integer)
    If KeyAscii = 13 Then
        Combo6.SetFocus
    End If
End Sub
