VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "clsScheduleX"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'ScheduleX class
' Encapsulates the integration of the ScheduleX components
'  to work together as a set.
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Option Explicit

'ScheduleX controls
Private WithEvents ctrlPVCalendar As PVCalendar
Attribute ctrlPVCalendar.VB_VarHelpID = -1
Private WithEvents ctrlPVTaskPad As PVTaskPad
Attribute ctrlPVTaskPad.VB_VarHelpID = -1
Private WithEvents ctrlPVDayView As PVDayView.PVDayView
Attribute ctrlPVDayView.VB_VarHelpID = -1

'member variables
Private m_bRedraw As Boolean
Private m_picTask As StdPicture
Private bResetingDayView As Boolean
Private bResetingTaskPad As Boolean

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''''' Properties '''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

Public Property Let Redraw(Enable As Boolean)
    ctrlPVTaskPad.Redraw = Enable
    ctrlPVDayView.Redraw = Enable
    ctrlPVCalendar.Redraw = Enable
    m_bRedraw = Enable
End Property
Public Property Get Redraw() As Boolean
    Redraw = m_bRedraw
End Property

Public Property Let TaskPicture(picTask As StdPicture)
    Set m_picTask = picTask
End Property
Public Property Get TaskPicture() As StdPicture
    Set TaskPicture = m_picTask
End Property


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'''''''''''''''''''''''''' Init Subs '''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'Init:
'   Attach ProtoView ScheduleX controls.
'   Execute individual Init procedures
'   Attach DayView to Calendar and vice-versa
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Sub Init(cal As PVCalendar, dv As PVDayView.PVDayView, tp As PVTaskPad)

    Set ctrlPVCalendar = cal
    Set ctrlPVDayView = dv
    Set ctrlPVTaskPad = tp
    
    InitCalendar
    InitDayView
    InitTaskPad
    
    'let cal and dayview change each others curDay
    ctrlPVDayView.AttachCalendar ctrlPVCalendar
    ctrlPVCalendar.AttachDayView ctrlPVDayView

    ctrlPVDayView.CurrentDate = Date
    
End Sub

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'InitDayView:
'   Initialize DayView
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub InitDayView()
    ctrlPVDayView.Increments = 1   'half hour
End Sub
    
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'InitTaskPad:
'   Initialize TaskPad
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub InitTaskPad()

End Sub
    
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'InitCalendar:
'   Initialize Calendar
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub InitCalendar()

End Sub

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'ResetDayView:
'   Remove all DayAppointment items
'   Note: there is a DayView.AppointmentSet.Reset
'       but I did not use it here, otherwise I would still have
'       the bolded dates in calendar
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Sub ResetDayView()
    Dim item As PVAppointment
    
    bResetingDayView = True
    
    'ctrlPVDayView.AppointmentSet.Reset
    
    Redraw = False
    Set item = ctrlPVDayView.AppointmentSet.GetLast
    While Not item Is Nothing
        RemoveApptItem item
        'ctrlPVDayView.AppointmentSet.Remove item.Key
        Set item = ctrlPVDayView.AppointmentSet.GetLast
        Wend
    Redraw = True
    bResetingDayView = False
End Sub

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'ResetTaskPad:
'   Reset TaskPad
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Sub ResetTaskPad()
    Dim i As Integer
    Dim task As PVTaskItem
    
    'ctrlPVTaskPad.Reset
    bResetingTaskPad = True
    For i = 1 To ctrlPVTaskPad.Count
        Set task = ctrlPVTaskPad.item(1)
        RemoveTaskItem task
    Next i
    bResetingTaskPad = False
End Sub

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''' Add/Create Functions '''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'AddApptItem
'   Adds a new PVAppointment item to PVDayView.
'   Change date number to bold in Calendar
'   Takes:
'       sDesc        - Appointment description
'       dtStart      - Start date and time
'       dtEnd        - End date and time
'       bAllDayEvent - (optional)
'   Returns:
'       reference to the PVDayApointment added
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Function AddApptItem( _
        sDesc As String, _
        dtStart As Date, _
        dtEnd As Date, _
        Optional bAllDayEvent As Boolean = False _
        ) As PVAppointment
        
    Dim appt As PVAppointment
    
    If bAllDayEvent Then
        Set appt = ctrlPVDayView.AppointmentSet.Add(" " & sDesc, dtStart, dtStart + 1 / 24)
        appt.AllDayEvent = True
    Else
        'add appt to day view
        Set appt = ctrlPVDayView.AppointmentSet.Add(sDesc, dtStart, dtEnd)
    End If
    
    'change date font to bold
    If ctrlPVCalendar.DATEFont(dtStart) Is Nothing Then
        Set ctrlPVCalendar.DATEFont(dtStart) = New StdFont
        ctrlPVCalendar.DATEFont(dtStart).Name = ctrlPVCalendar.DaysFont.Name
    End If
    ctrlPVCalendar.DATEFont(dtStart).Bold = True
    ctrlPVCalendar.DATEFont(dtStart).Size = ctrlPVCalendar.DATEFont(dtStart).Size
    
    Set AddApptItem = appt  'return
End Function

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'AddTaskItem
'   Adds a new PVTaskItem to PVTaskPad
'   Add a task image to the calendar on dtDueDate
'   Takes:
'       sDesc        - Appointment description
'       dtDueDate    - Date due (time is ignored)
'       bComplete    - Completion status of Task
'   Returns:
'       reference to the PVDayApointment added
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Function AddTaskItem( _
        sDesc As String, _
        dtDueDate As Date, _
        bComplete As Boolean _
        ) As PVTaskItem
    
    Dim task As PVTaskItem
    
    Set task = ctrlPVTaskPad.AddItem(bComplete, sDesc, dtDueDate)
    
    If dtDueDate = 949998 Then  'outlook date none
        task.FieldValue("Due Date") = "None"
    End If
    
    Set ctrlPVCalendar.DATEImage(dtDueDate) = m_picTask
    
    Set AddTaskItem = task

End Function

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'CreateAlarm:
'   Creates an alarm object which can be attached to a
'       PVDayAppointment item.
'    MyAppt.Alarm = MySXClass.CreateAlarm("Desc", "Display", DueDate)
'   Takes:
'       sDesc    - Description
'       sDisplay - Text to be displayed when alarm is fired
'       sStart   - Time alarm will fire
'       lOn      - (optional) 1 = on, 0 = off
'       iRepeat  - # of times alarm will repeat when snooze is used.
'   Returns:
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Function CreateAlarm(a As PVAppointment, _
    sDesc As String, _
    sDisplay As String, _
    dtStart As Date, _
    Optional lOn As Boolean = True, _
    Optional iRepeat As Integer = 0 _
    ) As PVAlarm
    
    
    'Dim al As New PVAlarm
    Dim al As PVAlarm
    
    Set al = a.Alarm
    
    al.Description = sDesc
    al.Display = sDisplay
    al.StartDateTime = dtStart
    al.Repeat = iRepeat
    al.On = lOn


    Set CreateAlarm = al
    
End Function

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''' Remove Items ''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'RemoveTaskItem:
'   Remove a TaskItem
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Sub RemoveTaskItem(task As PVTaskItem)
    ctrlPVTaskPad.RemoveItem task.Index
End Sub

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'RemoveApptItem:
'   Remove an DayAppointment item
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Sub RemoveApptItem(appt As PVAppointment)
    ctrlPVDayView.AppointmentSet.Remove appt.Key
End Sub

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'''''''''''''''''''''''''' Events ''''''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub ctrlPVDayView_BeforeAppointmentRemove(ByVal Appointment As PVDayView.IPVAppointment)

    Dim DateAndTime As Date
    Dim DateOnly As Long
    Dim DateOnly2 As Long
    Dim bRemoveBold As Boolean
    Dim item As PVAppointment
    
    DateAndTime = Appointment.StartDateTime
    DateOnly = DateAndTime / 1 'remove the time value
    Set item = ctrlPVDayView.AppointmentSet.Get(DateOnly)
    
    If item Is Nothing Then
        bRemoveBold = True

    ElseIf item.Key = Appointment.Key Then
        'try next in time order
        Set item = ctrlPVDayView.AppointmentSet.GetNext(item)
        If item Is Nothing Then
            bRemoveBold = True
        Else
            DateOnly = Appointment.StartDateTime / 1
            DateOnly2 = item.StartDateTime / 1
            If Not DateOnly = DateOnly2 Then
                bRemoveBold = True
            End If
        End If

    End If

    If bRemoveBold Then
        ctrlPVCalendar.DATEFont(DateAndTime) = Nothing
    End If
End Sub

Private Sub ctrlPVTaskPad_BeforeDeleteItem(ByVal item As PVATLTASKPADLibCtl.IPVTaskItem)

    Dim dt As Date
    Dim cnt As Integer
    Dim i As Integer
    
    dt = item.FieldValue("Due Date")
    
    For i = 1 To ctrlPVTaskPad.Count
        If (ctrlPVTaskPad.item(i).FieldValue("Due Date") = dt) Then
            cnt = cnt + 1
        End If
    Next i
    
    If cnt <= 1 Then
        'remove image
        Set ctrlPVCalendar.DATEImage(dt) = Nothing
    End If
    
End Sub

