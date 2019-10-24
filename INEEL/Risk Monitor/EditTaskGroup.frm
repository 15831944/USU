VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form EditTaskGroup 
   Caption         =   "Edit Task Group"
   ClientHeight    =   5370
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   9915
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
   LinkTopic       =   "Form1"
   ScaleHeight     =   5370
   ScaleWidth      =   9915
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton ok 
      Caption         =   "OK"
      Height          =   375
      Left            =   7080
      TabIndex        =   7
      Top             =   4920
      Width           =   1335
   End
   Begin VB.CommandButton EditOffset 
      Caption         =   "Change Offset"
      Height          =   375
      Left            =   120
      TabIndex        =   6
      Top             =   4920
      Width           =   1695
   End
   Begin VB.CommandButton Remove 
      Caption         =   "Remove"
      Height          =   375
      Left            =   2040
      TabIndex        =   5
      Top             =   4920
      Width           =   975
   End
   Begin VB.CommandButton Cancel 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   8520
      TabIndex        =   4
      Top             =   4920
      Width           =   1335
   End
   Begin VB.CommandButton Add 
      Caption         =   "<- Add"
      Height          =   375
      Left            =   5760
      TabIndex        =   3
      Top             =   4920
      Width           =   1215
   End
   Begin MSComctlLib.ListView CurrentTasks 
      Height          =   3705
      Left            =   0
      TabIndex        =   8
      Top             =   1080
      Width           =   5895
      _ExtentX        =   10398
      _ExtentY        =   6535
      View            =   3
      LabelEdit       =   1
      MultiSelect     =   -1  'True
      LabelWrap       =   -1  'True
      HideSelection   =   -1  'True
      FullRowSelect   =   -1  'True
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
   Begin MSComctlLib.ListView AvailableTasks 
      Height          =   3735
      Left            =   5880
      TabIndex        =   9
      Top             =   1080
      Width           =   4095
      _ExtentX        =   7223
      _ExtentY        =   6588
      View            =   3
      LabelEdit       =   1
      MultiSelect     =   -1  'True
      LabelWrap       =   -1  'True
      HideSelection   =   -1  'True
      FullRowSelect   =   -1  'True
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
   Begin VB.Label Label3 
      Caption         =   "Label3"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   240
      TabIndex        =   2
      Top             =   120
      Width           =   7815
   End
   Begin VB.Label Label2 
      Caption         =   "Avaliable Tasks"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   5880
      TabIndex        =   1
      Top             =   720
      Width           =   1815
   End
   Begin VB.Label Label1 
      Caption         =   "Current Tasks"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000017&
      Height          =   375
      Left            =   120
      TabIndex        =   0
      Top             =   720
      Width           =   1575
   End
End
Attribute VB_Name = "EditTaskGroup"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Public TaskGroupID As Integer
Public nameString As String ' used by other forms
Public TaskGroupName As String

'Function/Subroutine:Add_Click
'Purpose: add a procedure to a task - button click
Private Sub Add_Click()
    Dim DuplicateFound As Boolean, lItem As ListItem
    Dim i As Integer, j As Integer, TaskOffset As String, haveOff As Boolean
    
    For i = 1 To AvailableTasks.ListItems.Count
        If AvailableTasks.ListItems(i).Selected Then
            ' user wants to add this item.  check to see if it is
            ' already included in the current procedures
            DuplicateFound = False
            For j = 1 To CurrentTasks.ListItems.Count
                ' compare tags because they are the unique identifier
                If CurrentTasks.ListItems(j).tag = AvailableTasks.ListItems(i).tag Then
                    DuplicateFound = True
                    Exit For
                End If
            Next j
            
            If Not DuplicateFound Then
                nameString = AvailableTasks.ListItems(i).text
                If Not haveOff Then
                    ' show the form to ask the user the offset
                    Offset.ObjectLabel = nameString
                    Offset.Show vbModal, Me
                    If Offset.CancelClick = True Then Exit Sub
                    TaskOffset = Offset.Text1.text
                    haveOff = True
                End If
                Set lItem = CurrentTasks.ListItems.Add(, , nameString)
                lItem.ToolTipText = nameString
                lItem.tag = AvailableTasks.ListItems(i).tag
                lItem.ListSubItems.Add , , AvailableTasks.ListItems(i).ListSubItems(1).text, , AvailableTasks.ListItems(i).ListSubItems(1).text
                lItem.ListSubItems.Add , , TaskOffset, , TaskOffset
            End If
        End If
    Next i
    
End Sub

'Function/Subroutine:Form_Load
'Purpose: initialize variables and set up arrays of database info so
'database dosent have to be accessed too often
Private Sub Form_Load()
    Dim mySQLStatement As String, resultSet As rdoResultset, rarray As Variant
    Dim TaskName As String, TaskDescription As String, lItem As ListItem
    Dim DaskOff As String
    'Get Task ID from Task Name
    '*******************
    mySQLStatement = "SELECT TaskGroupID FROM TaskGroup WHERE TaskGroupName = '" & TaskGroupName & "'"
    Set resultSet = dbConnection.OpenResultset(mySQLStatement)
    ' Run time error 40071 will be generated if no connection is present by this statement
    
    CurrentTasks.ColumnHeaders.Add , , "Task Name", (CurrentTasks.Width - 80) * 1 / 3
    CurrentTasks.ColumnHeaders.Add , , "Task Description", (CurrentTasks.Width - 80) * 1 / 3
    CurrentTasks.ColumnHeaders.Add , , "Offset from Start (hrs)", (CurrentTasks.Width - 80) * 1 / 3
    
    AvailableTasks.ColumnHeaders.Add , , "Task Name", (AvailableTasks.Width - 80) * 1 / 2
    AvailableTasks.ColumnHeaders.Add , , "Task Description", (AvailableTasks.Width - 80) * 1 / 2
    
    ' check to make sure result was returned
    If (resultSet.EOF) Then
        MsgBox "No TaskGroup Found, Program Error", vbInformation
        Me.Hide
        Exit Sub
    Else
        rarray = resultSet.GetRows(1)
        TaskGroupID = rarray(0, 0)
        ' we should not get the task by the task name, since it could be a duplicate, but for now, it will do
        mySQLStatement = "SELECT TaskGroupSchedule.TaskID, Task.TaskName, Task.TaskDesc, TaskGroupSchedule.TimeOffset FROM [TaskGroupSchedule], [Task] WHERE TaskGroupID = " & TaskGroupID & " AND TaskGroupSchedule.TaskID = Task.TaskID"
        Set resultSet = dbConnection.OpenResultset(mySQLStatement)
        If (resultSet.EOF) Then
            EditOffset.Enabled = False
            Remove.Enabled = False
        Else
            'Display Current Procedure names in a list view
            While Not resultSet.EOF
                rarray = resultSet.GetRows(1)
                TaskName = rarray(1, 0)
                'TaskDescription = "hello"
                TaskDescription = rarray(2, 0)
                TaskOff = rarray(3, 0)
                Set lItem = CurrentTasks.ListItems.Add(, , TaskName)
                lItem.ToolTipText = TaskName
                lItem.ListSubItems.Add , , TaskDescription, , TaskDescription
                lItem.ListSubItems.Add , , TaskOff, , TaskOff

                ' we can store the procedure id in the list item tag
                lItem.tag = rarray(0, 0)
            Wend
        End If
    End If

    'populate available procedure list view
    mySQLStatement = "SELECT TaskID, TaskName, TaskDesc From [Task]"
    Set resultSet = dbConnection.OpenResultset(mySQLStatement)
    
    If resultSet.EOF Then
        MsgBox "No Tasks Found", vbInformation
    Else
        While Not resultSet.EOF
            rarray = resultSet.GetRows(1)
            TaskName = rarray(1, 0)
            'TaskDescription = "Hello"
            If IsNull(rarray(2, 0)) Then
                TaskDescription = ""
            Else
                TaskDescription = rarray(2, 0)
            End If
            Set lItem = AvailableTasks.ListItems.Add(, , TaskName)
            lItem.ToolTipText = ProcName
            lItem.ListSubItems.Add , , TaskDescription, , TaskDescription
            ' we can store the procedure id in the list item tag
            lItem.tag = rarray(0, 0)
        Wend
    End If
    Label3.Caption = TaskGroupName
End Sub

Private Sub AvailableProcedures_DblClick()
    Add_Click
End Sub

Private Sub Cancel_Click()
    Me.Hide
End Sub

Private Sub CurrentProcedures_Click()
    EditOffset.Enabled = True
    Remove.Enabled = True
End Sub

Private Sub CurrentProcedures_DblClick()
    Remove_Click
End Sub

Private Sub CurrentProcedures_KeyPress(KeyAscii As Integer)
    If KeyAscii = 13 Then
        Remove_Click
    End If
End Sub

'Function/Subroutine:EditOffset_Click
'Purpose: edit the offset of a procedure in a task
Private Sub EditOffset_Click()
    Dim i As Integer, getTime As Boolean
    For i = 1 To CurrentTasks.ListItems.Count
        If CurrentTasks.ListItems(i).Selected Then
            ' user wants to change this item.
            ' show the form to ask the user the duration
            If Not getTime Then
                Offset.ObjectLabel = CurrentTasks.ListItems(i).text
                Offset.Show vbModal, Me
                If Offset.CancelClick = True Then Exit Sub
                getTime = True
            End If
            CurrentTasks.ListItems(i).ListSubItems(2).text = Offset.Text1.text
        End If
    Next i
    If getTime Then Unload Offset
End Sub


Private Sub Form_Resize()
    If Height > 5700 Then
        EditOffset.Top = Height - 900
        Remove.Top = Height - 900
        Add.Top = Height - 900
        OK.Top = Height - 900
        Cancel.Top = Height - 900
        CurrentTasks.Height = Height - 2000
        AvailableTasks.Height = Height - 2000
    End If
    
    If Width > 9990 Then
        CurrentTasks.Width = (Width - 100) * 57 / 100
        AvailableTasks.Left = CurrentTasks.Left + CurrentTasks.Width
        AvailableTasks.Width = (Width - 100) * 43 / 100
        OK.Left = Width - 3000
        Cancel.Left = Width - 1600
        Add.Left = AvailableTasks.Left
        Label2.Left = AvailableTasks.Left
        
        CurrentTasks.ColumnHeaders(1).Width = (CurrentTasks.Width - 80) * 1 / 3
        CurrentTasks.ColumnHeaders(2).Width = (CurrentTasks.Width - 80) * 1 / 3
        CurrentTasks.ColumnHeaders(3).Width = (CurrentTasks.Width - 80) * 1 / 3
    
        AvailableTasks.ColumnHeaders(1).Width = (AvailableTasks.Width - 80) * 1 / 2
        AvailableTasks.ColumnHeaders(2).Width = (AvailableTasks.Width - 80) * 1 / 2
    End If
End Sub

'Function/Subroutine:ok_Click
'Purpose: handles enter press - adds item
Private Sub OK_Click()
    ' this is where we save the data
    Dim mySQLStatement As String, i As Integer, TaskID As String, TaskOff As String
    
    mySQLStatement = "DELETE FROM [TaskGroupSchedule] WHERE TaskGroupID = " & TaskGroupID
    dbConnection.Execute (mySQLStatement)
    For i = 1 To CurrentTasks.ListItems.Count
        TaskID = CurrentTasks.ListItems(i).tag
        TaskOff = CurrentTasks.ListItems(i).ListSubItems(2).text
        
        mySQLStatement = "INSERT INTO [TaskGroupSchedule] (TaskGroupID, TaskID, TimeOffset) VALUES ( " & TaskGroupID & ", " & TaskID & ", " & TaskOff & ")"
        dbConnection.Execute (mySQLStatement)
    Next i
    
    Me.Hide
End Sub

'Function/Subroutine:Remove_Click
'Purpose:remove and item from the database and the lists.
Private Sub Remove_Click()
    Dim i As Integer
    For i = AvailableTasks.ListItems.Count To 1 Step -1
        If AvailableTasks.ListItems(i).Selected Then
            ' user wants to delete this item.
            AvailableTasks.ListItems.Remove (i)
        End If
    Next i
End Sub



