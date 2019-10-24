VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{86CF1D34-0C5F-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCT2.OCX"
Object = "{22ACD161-99EB-11D2-9BB3-00400561D975}#1.0#0"; "PVCalendar.ocx"
Begin VB.Form frmAddTaskOrGroup 
   Caption         =   "Add Group"
   ClientHeight    =   5370
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   8295
   ControlBox      =   0   'False
   BeginProperty Font 
      Name            =   "Arial"
      Size            =   9.75
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   Icon            =   "frmAddGroup.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   5370
   ScaleWidth      =   8295
   StartUpPosition =   3  'Windows Default
   Begin MSComCtl2.DTPicker StartTime 
      Height          =   375
      Left            =   4920
      TabIndex        =   4
      Top             =   4080
      Width           =   3135
      _ExtentX        =   5530
      _ExtentY        =   661
      _Version        =   393216
      CustomFormat    =   "hh:mm"
      Format          =   22937602
      UpDown          =   -1  'True
      CurrentDate     =   37113
   End
   Begin PVATLCALENDARLib.PVCalendar StartDate 
      Height          =   2655
      Left            =   4920
      TabIndex        =   3
      Top             =   960
      Width           =   3135
      _Version        =   524288
      BorderStyle     =   0
      Appearance      =   0
      FirstDay        =   0
      Frame           =   3
      SelectMode      =   1
      DisplayFormat   =   0
      DateOrientation =   0
      CustomTextOrientation=   2
      ImageOrientation=   8
      DOWText0        =   ""
      DOWText1        =   ""
      DOWText2        =   ""
      DOWText3        =   ""
      DOWText4        =   ""
      DOWText5        =   ""
      DOWText6        =   ""
      MonthText0      =   "January"
      MonthText1      =   "February"
      MonthText2      =   "March"
      MonthText3      =   "April"
      MonthText4      =   "May"
      MonthText5      =   "June"
      MonthText6      =   "July"
      MonthText7      =   "August"
      MonthText8      =   "September"
      MonthText9      =   "October"
      MonthText10     =   "November"
      MonthText11     =   "December"
      HeaderBackColor =   12632256
      HeaderForeColor =   0
      DisplayBackColor=   16711680
      DisplayForeColor=   0
      DayBackColor    =   16777215
      DayForeColor    =   0
      SelectedDayForeColor=   16777215
      SelectedDayBackColor=   8388608
      BeginProperty HeaderFont {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BeginProperty DOWFont {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BeginProperty DaysFont {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      MultiLineText   =   -1  'True
      EditMode        =   0
      BeginProperty TextFont {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
   End
   Begin MSComctlLib.ListView ObjectList 
      Height          =   3975
      Left            =   240
      TabIndex        =   2
      Top             =   600
      Width           =   4455
      _ExtentX        =   7858
      _ExtentY        =   7011
      View            =   3
      LabelEdit       =   1
      LabelWrap       =   -1  'True
      HideSelection   =   -1  'True
      GridLines       =   -1  'True
      _Version        =   393217
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      BorderStyle     =   1
      Appearance      =   1
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      NumItems        =   0
   End
   Begin VB.CommandButton ok 
      Caption         =   "OK"
      Height          =   375
      Left            =   6720
      TabIndex        =   0
      Top             =   4800
      Width           =   1335
   End
   Begin VB.CommandButton cancel 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   5160
      TabIndex        =   1
      Top             =   4800
      Width           =   1335
   End
   Begin VB.Label Label3 
      Caption         =   "Select Task Group and Task Group Start Time"
      Height          =   255
      Left            =   240
      TabIndex        =   7
      Top             =   120
      Width           =   4695
   End
   Begin VB.Label Label2 
      Caption         =   "Start Date"
      Height          =   255
      Left            =   4920
      TabIndex        =   6
      Top             =   600
      Width           =   3135
   End
   Begin VB.Label Label1 
      Caption         =   "Start Time"
      Height          =   255
      Left            =   4920
      TabIndex        =   5
      Top             =   3720
      Width           =   3135
   End
End
Attribute VB_Name = "frmAddTaskOrGroup"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Public Enum SelectAddFormTypeEnum
    AddTaskGroupType = 0
    AddTaskType = 1
End Enum

Public FormType As SelectAddFormTypeEnum
Public ObjectName As String
Public ObjectID As Integer
Public InsertTime As Date
Public CancelClick As Boolean

'Function/Subroutine:cancel_Click
'Purpose: cancel the add group operation
Private Sub Cancel_Click()
    CancelClick = True
    Me.Hide
End Sub

'Function/Subroutine:Combo6_KeyPress
'Purpose: if enter is pressed while over combo box
Private Sub Combo6_KeyPress(KeyAscii As Integer)
    If KeyAscii = 13 Then
        OK_Click
    End If
End Sub
'Function/Subroutine:Form_Load
'Purpose: load times and task group names into comboboxes
Private Sub Form_Load()

    Dim mySQLStatement As String, resultSet As rdoResultset
    Dim rarray As Variant, name As String, desc As String, ID As Integer, lItem As ListItem
    
    'get list of existing objects
    If FormType = AddTaskGroupType Then
        Label3.Caption = "Select Task Group and Task Group Start Time"
        ObjectList.ColumnHeaders.Add , , "Task Group", (ObjectList.Width - 80) / 2
        mySQLStatement = "SELECT TaskGroupID, TaskGroupName, TaskGroupDesc FROM [TaskGroup]"
    Else
        Label3.Caption = "Select Task and Task Start Time"
        ObjectList.ColumnHeaders.Add , , "Task", (ObjectList.Width - 80) / 2
        mySQLStatement = "SELECT TaskID, TaskName, TaskDesc FROM [Task]"
    End If
    ObjectList.ColumnHeaders.Add , , "Description", (ObjectList.Width - 80) / 2
    
    Set resultSet = dbConnection.OpenResultset(mySQLStatement)
    ' Run time error 40071 will be generated if no connection is present by this statement

    'check to make sure result was returned
    If (resultSet.EOF) Then
        If FormType = AddTaskGroupType Then
            MsgBox "No Task Groups Found", vbInformation
        Else
            MsgBox "No Tasks Found", vbInformation
        End If
        CancelClick = True
        Exit Sub
    End If
    
    'determine number of rows
    While Not resultSet.EOF
        rarray = resultSet.GetRows(1)
        ID = rarray(0, 0)
        name = rarray(1, 0)
        desc = rarray(2, 0)
        Set lItem = ObjectList.ListItems.Add(, , name)
        lItem.ToolTipText = name
        lItem.ListSubItems.Add , , desc, , desc
        lItem.tag = ID
    Wend
   
    OK.Enabled = False
End Sub

Private Sub ObjectList_Click()
    OK.Enabled = (Not ObjectList.SelectedItem Is Nothing)
End Sub

'Function/Subroutine: ok_Click
'Purpose: get groupID from array and close form.
Private Sub OK_Click()
    If ObjectList.SelectedItem Is Nothing Then
        MsgBox "No item selected", vbInformation
        Exit Sub
    End If
    InsertTime = StartDate.Value + TimeValue(StartTime.Value)
    ObjectName = ObjectList.SelectedItem.text
    ObjectID = ObjectList.SelectedItem.tag
    CancelClick = False
    Me.Hide
End Sub

