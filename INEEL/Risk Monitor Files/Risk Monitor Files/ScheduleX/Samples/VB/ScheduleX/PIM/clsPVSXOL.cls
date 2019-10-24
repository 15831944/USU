VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "clsPVSXOL"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'ScheduleX/Outlook interface class
' Encapsulates the functionality between the ScheduleX
'  components (through clsScheduleX) and the
'  Outlook Object Model
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'DoEvents:
' When adding large quantities of data in a loop as in SetupTaskItems,
'   use the DoEvents method so that your app does not appear to lock up.
'   Also it will even let you scroll the taskpad as it is still
'   adding items.
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Option Explicit

'private members
Private pvsx As clsScheduleX
Private OLapp As Outlook.Application
Private OLns As NameSpace
Private OLApptFolder As MAPIFolder
Private OLTaskFolder As MAPIFolder

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''' PUBLIC subs and functions ''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'Init:
'   Attach ScheduleX interface class
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Sub Init(sx As clsScheduleX)
    Set pvsx = sx
End Sub


Public Function InitOutlook() As Long
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'InitOutlook:
'   Start Outlook and get the NameSpace
'   Returns:
'       0  - Failure
'       -1 - Success
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    
    On Error GoTo InitOutlook_Error

'start outlook
    Set OLapp = New Outlook.Application
    If OLapp Is Nothing Then
        Err.Raise vbObjectError, , "Outlook not available"
    End If

    Set OLns = OLapp.GetNamespace("MAPI")
    InitOutlook = -1
Exit Function
InitOutlook_Error:
    InitOutlook = 0
    MsgBox "Outlook not available", vbOKOnly, "Error opening Outlook"
End Function

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'ShutdownOutlook:
'   Remove all references
'   Returns:
'       0  - Failure
'       -1 - Success
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Sub ShutdownOutlook()

    Set pvsx = Nothing

    'Outlook references
    Set OLapp = Nothing
    Set OLns = Nothing
    Set OLApptFolder = Nothing
    Set OLTaskFolder = Nothing
    
End Sub

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'SetupDayViewItems:
'   Will retrieve all AppointmentItems from OutLook.
'   If no task folder has previously been specified the default
'   will be used.
'   Returns:
'       0  - Failure
'       -1 - Success
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Sub SetupDayViewItems()
    Dim OLappt As AppointmentItem
    Dim i As Integer
    
    On Error GoTo SetupDayViewItems_Error
    
    If OLApptFolder Is Nothing Then
        MsgBox "No ApptFolder has been specified"
        Exit Sub
        'GetDefaultAppointmentFolder
    End If
    
    For i = 1 To OLApptFolder.Items.Count
        Set OLappt = OLApptFolder.Items.item(i)
        AddOLApptToDayView OLappt
        DoEvents
    Next i
    
Exit Sub
SetupDayViewItems_Error:
    MsgBox Err.Description, vbOKOnly, "clsPVOL::SetupDayViewItems"
End Sub

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'SetupTaskPadItems:
'   Will retrieve all TaskItems from OutLook.
'   If no task folder has previously been specified the default
'   will be used.
'   Returns:
'       0  - Failure
'       -1 - Success
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Sub SetupTaskPadItems()
    Dim OLtsk As TaskItem
    Dim i As Integer
    
    On Error GoTo SetupTaskPadItems_Error
    
    If OLTaskFolder Is Nothing Then
        'GetDefaultTaskFolder
        MsgBox "No Task folder has been specified"
        Exit Sub
    End If
    
    For i = 1 To OLTaskFolder.Items.Count
        Set OLtsk = OLTaskFolder.Items.item(i)
        AddOLTaskToTaskPad OLtsk
        DoEvents
    Next i
    
Exit Sub
SetupTaskPadItems_Error:
    MsgBox Err.Description, vbOKOnly, "clsPVOL::SetupTaskPadItems"
End Sub

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'GetDefaultAppointmentFolder:
'   Will retrieve the MAPIFolder in Outlook specified as the default
'       for olAppointmentItems and assign to OLApptFolder.
'   Returns:
'       0  - Failure
'       -1 - Success
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Function GetDefaultAppointmentFolder() As Long

    On Error GoTo GetDefaultAppointmentFolder_Error
    
    Set OLApptFolder = OLns.GetDefaultFolder(olFolderCalendar)
    
    If OLApptFolder Is Nothing Then
        Err.Raise vbObjectError, , "Could not get Default Appointment folder"
    End If
    
    GetDefaultAppointmentFolder = -1     'success
    
Exit Function

GetDefaultAppointmentFolder_Error:
    GetDefaultAppointmentFolder = 0
End Function

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'GetDefaultTaskFolder:
'   Will retrieve the MAPIFolder in Outlook specified as the default
'       for olTaskItems and assign to OLTaskFolder.
'   Returns:
'       0  - Failure
'       -1 - Success
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Function GetDefaultTaskFolder() As Long

    On Error GoTo GetDefaultTaskFolder_Error
    
    Set OLTaskFolder = OLns.GetDefaultFolder(olFolderTasks)
    
    If OLTaskFolder Is Nothing Then
        Err.Raise vbObjectError, , "Could not get default Task Folder"
    End If
    
    GetDefaultTaskFolder = -1
    
Exit Function

GetDefaultTaskFolder_Error:
    GetDefaultTaskFolder = 0
End Function

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'UserSelectAppointmentFolder:
'   Will invoke an Outlook folder list for user selection of
'       a MAPIFolder for retrieving olAppointmentItems and
'       assign to OLApptFolder.
'   Returns:
'       0  - Failure
'       -1 - Success
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Function UserSelectAppointmentFolder() As Integer
    On Error GoTo UserSelectAppointmentFolder_Error

'Pick a folder
    Set OLApptFolder = OLns.PickFolder
    
    If OLApptFolder Is Nothing Then
        Err.Raise vbObjectError, , "No folder selected"
    ElseIf OLApptFolder.DefaultItemType <> olAppointmentItem Then
        Err.Raise vbObjectError, , "Not an Appointment folder"
    Else
        UserSelectAppointmentFolder = -1
    End If
Exit Function
UserSelectAppointmentFolder_Error:
    'MsgBox Err.Description, , "clsPVOL::UserSelectAppointmentFolder"
    UserSelectAppointmentFolder = 0
End Function

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'UserSelectTaskFolder:
'   Will invoke an Outlook folder list for user selection of
'       a MAPIFolder for retrieving olTaskItems and assign to
'       OLTaskFolder
'   Returns:
'       0  - Failure
'       -1 - Success
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Function UserSelectTaskFolder() As Integer
    On Error GoTo UserSelecttaskFolder_Error

    'Pick a folder
    Set OLTaskFolder = OLns.PickFolder
    
    If OLTaskFolder Is Nothing Then
        Err.Raise vbObjectError, , "No folder selected"
    ElseIf OLTaskFolder.DefaultItemType <> olTaskItem Then
        Err.Raise vbObjectError, , "Not a Task folder"
    Else
        UserSelectTaskFolder = -1
    End If
Exit Function
UserSelecttaskFolder_Error:
    'MsgBox Err.Description, , "clsPVOL::UserSelectTaskFolder"
    UserSelectTaskFolder = 0
End Function

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''' PRIVATE subs and functions '''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

Private Sub AddOLTaskToTaskPad(OLtask As TaskItem)
    pvsx.AddTaskItem OLtask.Subject, OLtask.DueDate, OLtask.Complete
End Sub

Private Sub AddOLApptToDayView(OLappt As AppointmentItem)
    pvsx.AddApptItem OLappt.Subject, OLappt.Start, OLappt.End, OLappt.AllDayEvent
End Sub

Private Sub Class_Terminate()
    ShutdownOutlook
End Sub

