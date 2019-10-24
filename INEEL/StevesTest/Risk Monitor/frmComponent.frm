VERSION 5.00
Object = "{86CF1D34-0C5F-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCT2.OCX"
Begin VB.Form frmComponent 
   Caption         =   "Component"
   ClientHeight    =   6225
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   8295
   Icon            =   "frmComponent.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   6225
   ScaleWidth      =   8295
   StartUpPosition =   3  'Windows Default
   Begin VB.ListBox List1 
      Height          =   1035
      Left            =   840
      TabIndex        =   9
      Top             =   360
      Width           =   6735
   End
   Begin VB.Frame Frame1 
      Caption         =   "Start Time"
      Height          =   3735
      Left            =   840
      TabIndex        =   5
      Top             =   1680
      Width           =   3255
      Begin VB.ComboBox StartCombo 
         Height          =   315
         Left            =   600
         Style           =   2  'Dropdown List
         TabIndex        =   6
         Top             =   3000
         Width           =   1935
      End
      Begin MSComCtl2.MonthView StartView 
         Height          =   2370
         Left            =   240
         TabIndex        =   7
         Top             =   360
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
   Begin VB.Frame Frame2 
      Caption         =   "End Time"
      Height          =   3735
      Left            =   4320
      TabIndex        =   2
      Top             =   1680
      Width           =   3255
      Begin VB.ComboBox EndCombo 
         Height          =   315
         Left            =   600
         Style           =   2  'Dropdown List
         TabIndex        =   3
         Top             =   3000
         Width           =   2055
      End
      Begin MSComCtl2.MonthView EndView 
         Height          =   2370
         Left            =   240
         TabIndex        =   4
         Top             =   360
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
   Begin VB.CommandButton cancel 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   1800
      TabIndex        =   1
      Top             =   5640
      Width           =   1815
   End
   Begin VB.CommandButton ok 
      Caption         =   "OK"
      Height          =   375
      Left            =   4800
      TabIndex        =   0
      Top             =   5640
      Width           =   2055
   End
   Begin VB.Label Label1 
      Caption         =   "Components:"
      Height          =   375
      Left            =   840
      TabIndex        =   8
      Top             =   120
      Width           =   6735
   End
End
Attribute VB_Name = "frmComponent"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'Adds a component to the oos list
Option Explicit

Public CancelClick As Boolean
Public LabelText As String
Public StartDate As Date
Public EndDate As Date
Public CompName As String
Public compID As Integer
Private rArray As Variant
Private RowReturn As Integer

'Function:cancel_click
'Purpose: handles the cancel click event
Private Sub cancel_Click()
    CancelClick = True
    Me.Hide
End Sub
'Function: Form_Load
'Purpose Add items to the list box and set the initial dates for the
'calendar control
Private Sub Form_Load()
    CancelClick = False
    
    Dim mySQL As String
    Dim resultSet As rdoResultset
    
    Dim i As Integer
    RowReturn = 0
    
'These variables need to be set before form load is called
    'initial dates for calender control
    StartView.Value = DatePart("m", StartDate) & "/" & DatePart("d", StartDate) & "/" & DatePart("yyyy", StartDate)
    EndView.Value = DatePart("m", EndDate) & "/" & DatePart("d", EndDate) & "/" & DatePart("yyyy", EndDate)
    
    'Create List Boxes
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
    
    'Get component information from database
    mySQL = "SELECT ComponentID, ComponentName FROM [Component]"
    Set resultSet = dbConnection.OpenResultset(mySQL, rdOpenKeyset)
    
    While Not resultSet.EOF
        resultSet.MoveNext
        RowReturn = RowReturn + 1
    Wend
 
    If RowReturn > 0 Then
        resultSet.MoveFirst
        rArray = resultSet.GetRows(RowReturn)
    
        For i = 0 To RowReturn - 1
            List1.AddItem rArray(1, i)
     Next i
    Else
        MsgBox "No Components Found", vbInformation
        cancel_Click
    End If
End Sub
'Function: ok_Click
'purpose: handle the event when ok is clicked. get the component ID of
'user selection and the OOS start and end time.
Private Sub ok_Click()
    Dim temp As Date
    Dim i As Integer
    
    Me.Hide
    
    'get date from calendar and set to correct format
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
    
    'Switch start and end if start is after end
    If StartDate > EndDate Then
        temp = StartDate
        StartDate = EndDate
        EndDate = temp
    End If
    
    CompName = List1.text
    compID = 0
    
    'determine component ID
    For i = 0 To RowReturn - 1
        If CompName = rArray(1, i) Then
            compID = rArray(0, i)
        End If
    Next i
    
    'close form if no component was selected
    If compID = 0 Then
        MsgBox "No component Selected", vbInformation
        CancelClick = True
    End If

End Sub
