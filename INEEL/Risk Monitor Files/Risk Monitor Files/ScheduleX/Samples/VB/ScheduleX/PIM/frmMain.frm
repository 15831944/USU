VERSION 5.00
Object = "{22ACD161-99EB-11D2-9BB3-00400561D975}#1.0#0"; "PVCalendar.ocx"
Object = "{C2125AD1-D187-11D2-9C0D-00A0CC3A1AD6}#1.0#0"; "PVTaskPad.ocx"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{8FFC5771-EE23-11D3-9DC0-00A0CC3A1AD6}#1.0#0"; "PVDayView8.ocx"
Begin VB.Form frmMain 
   Caption         =   "Infragistics ScheduleX Outlook Sample"
   ClientHeight    =   6240
   ClientLeft      =   165
   ClientTop       =   765
   ClientWidth     =   9645
   Icon            =   "frmMain.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   6240
   ScaleWidth      =   9645
   StartUpPosition =   3  'Windows Default
   Begin VB.PictureBox picSplitterY 
      BackColor       =   &H00808080&
      BorderStyle     =   0  'None
      FillColor       =   &H00808080&
      Height          =   72
      Left            =   5160
      ScaleHeight     =   32.658
      ScaleMode       =   0  'User
      ScaleWidth      =   43212
      TabIndex        =   4
      Top             =   6000
      Visible         =   0   'False
      Width           =   4155
   End
   Begin VB.PictureBox picSplitter 
      BackColor       =   &H00808080&
      BorderStyle     =   0  'None
      FillColor       =   &H00808080&
      Height          =   6000
      Left            =   9480
      ScaleHeight     =   2612.657
      ScaleMode       =   0  'User
      ScaleWidth      =   780
      TabIndex        =   3
      Top             =   0
      Visible         =   0   'False
      Width           =   72
   End
   Begin PVDayView.PVDayView dayMain 
      Height          =   6135
      Left            =   0
      TabIndex        =   2
      Top             =   0
      Width           =   4695
      _Version        =   65536
      DOYAlignment    =   0
      UseCustomCaption=   0   'False
      Caption         =   "Tuesday, October 10, 2000"
      Appearance      =   1
      BorderStyle     =   0
      Increments      =   1
      SelectMode      =   1
      EnableDayChange =   -1  'True
      UseControlPanelSettings=   -1  'True
      TimeSeparator   =   ":"
      AMString        =   "AM"
      PMString        =   "PM"
      TimeBackColor   =   16777215
      SelectedTimeBackColor=   8388608
      AppointmentsForeColor=   0
      AppointmentsBackColor=   16777215
      AppointmentsBarColor=   16711680
      BeginProperty TimeFont {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BeginProperty CaptionFont {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BeginProperty AppointmentsFont {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      UseStandardDialogs=   -1  'True
   End
   Begin MSComDlg.CommonDialog OpenFile 
      Left            =   5160
      Top             =   600
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin MSComctlLib.ImageList imlCalendar 
      Left            =   2520
      Top             =   6240
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   18
      ImageHeight     =   17
      MaskColor       =   12632256
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   2
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":030A
            Key             =   ""
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":0468
            Key             =   ""
         EndProperty
      EndProperty
   End
   Begin PVATLTASKPADLibCtl.PVTaskPad tskmain 
      Height          =   2895
      Left            =   5160
      TabIndex        =   1
      Top             =   3000
      Width           =   4095
      _Version        =   524288
      BorderStyle     =   1
      Appearance      =   1
      CompletionStyle =   2
      SelectMode      =   1
      CompleteHidden  =   0   'False
      SubjectHidden   =   0   'False
      DueDateHidden   =   0   'False
      PercentCompleteHidden=   -1  'True
      NotesHidden     =   -1  'True
      AttachmentHidden=   -1  'True
      ActualWorkHidden=   -1  'True
      CategoriesHidden=   -1  'True
      PriorityHidden  =   -1  'True
      DateCompleteHidden=   -1  'True
      DateStartedHidden=   -1  'True
      StatusHidden    =   -1  'True
      CompanyHidden   =   -1  'True
      TotalWorkHidden =   -1  'True
      CompleteWorkHidden=   -1  'True
      BeginProperty HeaderFont {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BeginProperty TasksFont {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      OverdueColor    =   1769727
      DefaultItemForeColor=   1769472
      BackColor       =   16777215
      Caption         =   ""
   End
   Begin MSComDlg.CommonDialog cmndlgAppts 
      Left            =   1320
      Top             =   6240
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin MSComDlg.CommonDialog cmndlgTasks 
      Left            =   1920
      Top             =   6240
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin PVATLCALENDARLib.PVCalendar calMain 
      Height          =   2655
      Left            =   5160
      TabIndex        =   0
      Top             =   0
      Width           =   4215
      _Version        =   524288
      BorderStyle     =   1
      Appearance      =   1
      FirstDay        =   0
      Frame           =   1
      SelectMode      =   1
      DisplayFormat   =   0
      DateOrientation =   0
      CustomTextOrientation=   2
      ImageOrientation=   2
      DOWText0        =   "S"
      DOWText1        =   "M"
      DOWText2        =   "T"
      DOWText3        =   "W"
      DOWText4        =   "T"
      DOWText5        =   "F"
      DOWText6        =   "S"
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
      HeaderBackColor =   8454143
      HeaderForeColor =   0
      DisplayBackColor=   12632256
      DisplayForeColor=   0
      DayBackColor    =   16777215
      DayForeColor    =   0
      SelectedDayForeColor=   16777215
      SelectedDayBackColor=   8388608
      BeginProperty HeaderFont {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Tahoma"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BeginProperty DOWFont {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BeginProperty DaysFont {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      MultiLineText   =   0   'False
      EditMode        =   1
      BeginProperty TextFont {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
   End
   Begin VB.Image imgSplitterY 
      Height          =   150
      Left            =   6000
      MousePointer    =   7  'Size N S
      Top             =   2760
      Width           =   3015
   End
   Begin VB.Image imgSplitter 
      Height          =   6105
      Left            =   4800
      MousePointer    =   9  'Size W E
      Top             =   0
      Width           =   150
   End
   Begin VB.Menu mnuFile 
      Caption         =   "&File"
      Begin VB.Menu mnuFile_New 
         Caption         =   "&New"
      End
      Begin VB.Menu mnuFile_Open 
         Caption         =   "&Open"
         Begin VB.Menu mnuFile_Open_Calendar 
            Caption         =   "&Calendar File"
         End
         Begin VB.Menu mnuFile_Open_Appts 
            Caption         =   "&Appointments File"
         End
         Begin VB.Menu mnuFile_Open_Tasks 
            Caption         =   "&Tasks File"
         End
      End
      Begin VB.Menu mnuFile_ImportOL 
         Caption         =   "&Import from Outlook..."
      End
      Begin VB.Menu mnuFile_Sep0 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFile_Save 
         Caption         =   "&Save"
         Begin VB.Menu mnuFile_Save_Calendar 
            Caption         =   "&Calendar"
         End
         Begin VB.Menu mnuFile_Save_Appts 
            Caption         =   "&Appointments"
         End
         Begin VB.Menu mnuFile_Save_Tasks 
            Caption         =   "&Tasks"
         End
      End
      Begin VB.Menu mnuFile_SaveAs 
         Caption         =   "Save &As"
         Visible         =   0   'False
         Begin VB.Menu mnuFile_SaveAs_Appts 
            Caption         =   "Appointments"
         End
         Begin VB.Menu mnuFile_SaveAs_Tasks 
            Caption         =   "Tasks"
         End
      End
      Begin VB.Menu mnuFile_SaveAll 
         Caption         =   "Save A&ll"
         Visible         =   0   'False
      End
      Begin VB.Menu mnuFile_Sep1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFile_Exit 
         Caption         =   "E&xit"
      End
   End
   Begin VB.Menu mnuOutLook 
      Caption         =   "&Outlook"
      Begin VB.Menu mnuOutLook_SelApptFolder 
         Caption         =   "Select &Appointments Folder"
      End
      Begin VB.Menu mnuOutLook_SelTasksFolder 
         Caption         =   "Select &Tasks Folder"
      End
   End
   Begin VB.Menu mnuHelp 
      Caption         =   "&Help"
      Begin VB.Menu mnuHelp_About 
         Caption         =   "&About"
      End
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'About this sample:
'   I have created two classes for this sample
'       clsScheduleX (my instance "pvsx")
'           manages the 3 scheduleX components through its interface.
'           contains all code for adding Tasks, initializing the
'           components, events, etc.
'       clsPVSXOL (my instance "pvOL")
'           This class manages the interface between clsScheduleX
'               and the Outlook Object model.
'           It is dependant on clsScheduleX for adding Items to the
'               controls
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Option Explicit

Dim mbMoving As Boolean
Const sglSplitLimit = 500
Dim pvOL As clsPVSXOL
Dim pvsx As clsScheduleX

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'''''''''''''''''''''''''' Form events '''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

Private Sub Form_Load()

    InitMenus
            
    Set pvsx = New clsScheduleX
    pvsx.Init calMain, dayMain, tskmain
    
     pvsx.TaskPicture = imlCalendar.ListImages(2).Picture
    
    AddDummyData
    
End Sub

Private Sub Form_Resize()

    On Error Resume Next
    If Me.Width < 3000 Then Me.Width = 3000
    SizeControlsX imgSplitter.Left

End Sub

Private Sub imgSplitter_MouseDown(Button As Integer, Shift As Integer, x As Single, y As Single)
    With imgSplitter
        picSplitter.Move .Left, .Top, .Width \ 2, .Height - 20
    End With
    picSplitter.Visible = True
    mbMoving = True
End Sub

Private Sub imgSplitter_MouseMove(Button As Integer, Shift As Integer, x As Single, y As Single)
    Dim sglPos As Single
    

    If mbMoving Then
        sglPos = x + imgSplitter.Left
        If sglPos < sglSplitLimit Then
            picSplitter.Left = sglSplitLimit
        ElseIf sglPos > Me.Width - sglSplitLimit Then
            picSplitter.Left = Me.Width - sglSplitLimit
        Else
            picSplitter.Left = sglPos
        End If
    End If
End Sub

Private Sub imgSplitter_MouseUp(Button As Integer, Shift As Integer, x As Single, y As Single)
    SizeControlsX picSplitter.Left
    picSplitter.Visible = False
    mbMoving = False
End Sub




Private Sub imgSplitterY_MouseDown(Button As Integer, Shift As Integer, x As Single, y As Single)
    With imgSplitterY
        picSplitterY.Move .Left, .Top, .Width - 20, .Height / 2
    End With
    picSplitterY.Visible = True
    mbMoving = True
End Sub

Private Sub imgSplitterY_MouseMove(Button As Integer, Shift As Integer, x As Single, y As Single)
    Dim sglPos As Single
    

    If mbMoving Then
        sglPos = y + imgSplitterY.Top
        If sglPos < sglSplitLimit Then
            picSplitterY.Top = sglSplitLimit
        ElseIf sglPos > Me.Height - sglSplitLimit Then
            picSplitterY.Top = Me.Height - sglSplitLimit
        Else
            picSplitterY.Top = sglPos
        End If
    End If
End Sub

Private Sub imgSplitterY_MouseUp(Button As Integer, Shift As Integer, x As Single, y As Single)
    SizeControlsY picSplitterY.Top
    picSplitterY.Visible = False
    mbMoving = False
End Sub



Sub SizeControlsX(x As Single)
    On Error Resume Next
    

    dayMain.Top = 0
    
    dayMain.Height = Me.ScaleHeight

    'set the width
    If x < 1500 Then x = 1500
    If x > (Me.Width - 1500) Then x = Me.Width - 1500
    dayMain.Width = x
    imgSplitter.Left = x
    calMain.Left = x + 40
    calMain.Width = Me.Width - (dayMain.Width + 140)
    tskmain.Left = x + 40
    tskmain.Width = Me.Width - (dayMain.Width + 140)

    ' set the top
    calMain.Top = dayMain.Top

    calMain.Height = imgSplitterY.Top
    tskmain.Height = dayMain.Height - imgSplitterY.Top - 40
    imgSplitter.Top = dayMain.Top
    imgSplitter.Height = dayMain.Height
    
    tskmain.Top = calMain.Height + 40
    
    imgSplitterY.Left = dayMain.Width
    imgSplitterY.Width = calMain.Width
    imgSplitterY.Top = calMain.Height

End Sub

Sub SizeControlsY(y As Single)
    'set the height
    If y < 1500 Then y = 1500
    If y > (Me.Width - 1500) Then y = Me.Width - 1500
    imgSplitterY.Top = y
    
    calMain.Height = y
    tskmain.Top = calMain.Height + 40
    tskmain.Height = dayMain.Height - imgSplitterY.Top - 40

End Sub

Private Sub Form_Terminate()
    ShutdownApp
End Sub

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'''''''''''''''''''''''''' Menu events '''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

Private Sub mnuFile_New_Click()
   'remove all task and appt items
    pvsx.ResetDayView
    pvsx.ResetTaskPad
End Sub

Private Sub mnuFile_ImportOL_Click()
    
    On Error GoTo ImportOL_Error

    Me.MousePointer = vbHourglass
    pvsx.Redraw = False
    
    Set pvOL = New clsPVSXOL
    pvOL.Init pvsx

    If Not pvOL.InitOutlook Then
        Err.Raise vbObjectError, , "Outlook could not be initialized"
    End If
    
    'get default folders, if none let user select
    If Not pvOL.GetDefaultAppointmentFolder Then
        If Not pvOL.UserSelectAppointmentFolder Then
            Err.Raise vbObjectError, , "Appointment folder not specified"
        End If
    End If
    
    If Not pvOL.GetDefaultTaskFolder Then
        If Not pvOL.UserSelectAppointmentFolder Then
            Err.Raise vbObjectError, , "Task folder not specified"
        End If
    End If

    'set up items
    pvOL.SetupDayViewItems
    pvOL.SetupTaskPadItems

    'show Outlook submenu
    'mnuOutLook.Visible = True
    mnuOutLook.Enabled = True
    
    GoTo ImportOL_Done:
ImportOL_Error:
    pvOL.ShutdownOutlook
    Set pvOL = Nothing
    
ImportOL_Done:
    pvsx.Redraw = True
    Me.MousePointer = vbDefault
End Sub

Private Sub mnuFile_Exit_Click()
    ShutdownApp
End Sub

Private Sub mnuFile_Open_Appts_Click()
On Error GoTo ErrorHandler

OpenFile.CancelError = True
OpenFile.DefaultExt = ".day"
OpenFile.FileName = "apps.day"
OpenFile.Filter = "DayView Data Files (*.day)|*.day|All Files (*.*)|*.*"
OpenFile.FilterIndex = 0
OpenFile.Flags = cdlOFNHideReadOnly
OpenFile.ShowOpen

'calMain.Load OpenFile.FileName + "1", 0
dayMain.Load OpenFile.FileName + "1", 0

ErrorHandler:
End Sub

Private Sub mnuFile_Open_Calendar_Click()
On Error GoTo ErrorHandler

OpenFile.CancelError = True
OpenFile.DefaultExt = ".cal"
OpenFile.FileName = "calendar.cal"
OpenFile.Filter = "Calendar Data Files (*.cal)|*.cal|All Files (*.*)|*.*"
OpenFile.FilterIndex = 0
OpenFile.Flags = cdlOFNHideReadOnly
OpenFile.ShowOpen

calMain.Load OpenFile.FileName + "1", 0

ErrorHandler:
End Sub

Private Sub mnuFile_Open_Tasks_Click()
On Error GoTo ErrorHandler

OpenFile.CancelError = True
OpenFile.DefaultExt = ".tsk"
OpenFile.FileName = "TaskPad.tsk"
OpenFile.Filter = "Task Data Files (*.tsk)|*.tsk|All Files (*.*)|*.*"
OpenFile.FilterIndex = 0
OpenFile.Flags = cdlOFNHideReadOnly
OpenFile.ShowOpen

tskmain.Load OpenFile.FileName + "1", 0
ErrorHandler:

End Sub

Private Sub mnuFile_Save_Appts_Click()
On Error GoTo ErrorHandler

OpenFile.CancelError = True
OpenFile.DefaultExt = ".day"
OpenFile.FileName = "apps.day"
OpenFile.Filter = "DayView Data Files (*.day)|*.day|All Files (*.*)|*.*"
OpenFile.FilterIndex = 0
OpenFile.Flags = cdlOFNHideReadOnly
OpenFile.ShowSave

'calMain.Save OpenFile.FileName, 0
dayMain.Save OpenFile.FileName + "1", 0

ErrorHandler:
End Sub

Private Sub mnuFile_Save_Calendar_Click()
On Error GoTo ErrorHandler

OpenFile.CancelError = True
OpenFile.DefaultExt = ".cal"
OpenFile.FileName = "calendar.cal"
OpenFile.Filter = "Calendar Data Files (*.cal)|*.cal|All Files (*.*)|*.*"
OpenFile.FilterIndex = 0
OpenFile.Flags = cdlOFNHideReadOnly
OpenFile.ShowSave

calMain.Save OpenFile.FileName + "1", 0
ErrorHandler:
End Sub

Private Sub mnuFile_Save_Tasks_Click()
On Error GoTo ErrorHandler

OpenFile.CancelError = True
OpenFile.DefaultExt = ".tsk"
OpenFile.FileName = "TaskPad.tsk"
OpenFile.Filter = "Task Data Files (*.tsk)|*.tsk|All Files (*.*)|*.*"
OpenFile.FilterIndex = 0
OpenFile.Flags = cdlOFNHideReadOnly
OpenFile.ShowSave

tskmain.Save OpenFile.FileName + "1", 0
ErrorHandler:
End Sub

Private Sub mnuHelp_About_Click()
frmAbout.Show

End Sub

Private Sub mnuOutLook_SelApptFolder_Click()
    If pvOL.UserSelectAppointmentFolder Then
        pvsx.ResetDayView
        pvOL.SetupDayViewItems
    End If
End Sub

Private Sub mnuOutLook_SelTasksFolder_Click()
    If pvOL.UserSelectTaskFolder Then
        pvsx.ResetTaskPad
        pvOL.SetupTaskPadItems
    End If
End Sub

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'''''''''''''''''''' Misc Subs/Functions '''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub InitMenus()
    mnuFile.Visible = True
    'mnuOutLook.Visible = False
    mnuOutLook.Enabled = False
End Sub

Private Sub ShutdownApp()
    dayMain.AttachCalendar Nothing
    calMain.AttachDayView Nothing
    
    Set pvOL = Nothing
    Set pvsx = Nothing
    End
End Sub

Private Sub AddDummyData()
    Dim appt As PVAppointment
    
    Set appt = pvsx.AddApptItem("Developer Meeting", Date + (9 / 24), Date + (11 / 24))
    Set appt = pvsx.AddApptItem("Product Meeting", Date + (10 / 24), Date + (12 / 24))
    
    Set appt = pvsx.AddApptItem("Sales Meeting", Date + (13 / 24), Date + (15 / 24))
    pvsx.CreateAlarm appt, "MY Sales Meeting", "MY Oh no, not the sales meeting", Now + (1 / 24), True, 0
    
    Set appt = pvsx.AddApptItem("Marketing Meeting", Date + (15 / 24), Date + (17 / 24))
    pvsx.CreateAlarm appt, "Marketing Meeting", "Oh no, not the marketing meeting", Now + (1 / 24), True, 1
   
    'appt.Alarm.Description = "Marketing Meeting"
    'appt.Alarm.Display = "Oh no, not the marketing meeting"
    'appt.Alarm.StartDateTime = Date + #1:00:00 PM# '(13 / 24)
    'appt.Alarm.Repeat = 1
    'appt.Alarm.On = True
    
    Set appt = pvsx.AddApptItem("Try to rest before tomorrow's meetings", Date + (15 / 24), Date + (22 / 24))
    
    pvsx.AddTaskItem "Review Quarterly", Date - 2, False
    pvsx.AddTaskItem "Build new installations", Date + 1, False
    pvsx.AddTaskItem "Design new component specs", Date - 20, True
    pvsx.AddTaskItem "Test new installations", Date + 7, False
    pvsx.AddTaskItem "Plan Nova Scotia vacation", Date + 2, False
    
End Sub

'''''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub tskmain_BeforeFieldChanged(ByVal Field As String, ByVal item As PVATLTASKPADLibCtl.IPVTaskItem, ByVal newValue As Variant)
Debug.Print "BeforefieldChanged"
    If ((Field = "Complete") And (item.FieldValue("Complete") = True)) Then
        'uncomplete the task
        item.FieldValue("Date Complete") = "None"
    End If

End Sub

