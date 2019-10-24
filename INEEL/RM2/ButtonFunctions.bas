Attribute VB_Name = "ButtonFunctions"
Option Explicit
Public StartString As String
Public EndString As String

'Function/Subroutine: AddGroup
'Purpose: When the user clicks add group this function is called. It
'Brings up a selection window where the user can select from existing
'groups, checks to make sure a valid date was entered, Adds the group
'to the WorkspaceTaskGroup table, determines all the tasks associated
'with the group and passes that list to the AddGroupTask function.
Sub AddGroup(ByRef activeWS As Workspace)
'
    Dim temp As Integer
    Dim TimeStart As Date
    Dim TimeEnd As String
    Dim mySQLStatement As String
    Dim RowReturn, i As Integer
    Dim rarray As Variant
    Dim lrArray As Variant
    Dim TasklrArray As Variant
    Dim GroupID As Integer
    Dim resultSet As rdoResultset
    Dim VBDate As String
    Dim tempinteger As Integer
    Dim WSID As Integer
    Dim Start As Date
    Dim Reference As Integer
    Dim name As String
    Dim Index As Long
    
    RowReturn = 0
    frmAddTaskOrGroup.FormType = AddTaskGroupType
    frmAddTaskOrGroup.Show vbModal, MDIMain
    'If the process was not cancled then...
    If frmAddTaskOrGroup.CancelClick = False Then
        name = frmAddTaskOrGroup.ObjectName
        GroupID = frmAddTaskOrGroup.ObjectID
        
        'Check to make sure user did enter data
        If name = "" Then
            MsgBox "Invalid Group", vbInformation
            Unload frmAddTaskOrGroup
            Exit Sub
        End If
        
        'Convert Dates to Correct format
        TimeStart = frmAddTaskOrGroup.InsertTime
         
        'Enter group into WorkspaceTaskGroup table
        WSID = activeWS.workspaceId
        Start = activeWS.StartTime
        
        mySQLStatement = "INSERT INTO [WorkspaceTaskGroup] (WorkspaceID, TaskGroupID, StartTime) VALUES ( " & WSID & ", " & GroupID & ", " & SQLDate(TimeStart) & ")"
        Set resultSet = dbConnection.OpenResultset(mySQLStatement)
        
        mySQLStatement = "SELECT AutoReference FROM WorkspaceTaskGroup WHERE TaskGroupID = " & GroupID & " AND WorkspaceID = " & WSID & " AND StartTime = " & SQLDate(TimeStart) & " ORDER BY AutoReference DESC"
        Set resultSet = dbConnection.OpenResultset(mySQLStatement, rdOpenKeyset)
        lrArray = resultSet.GetRows(1)
        Reference = lrArray(0, 0) 'Reference = group auto reference

        'Add group to the tree and collection
        Dim tempNode As node_object
        Set tempNode = New node_object

        tempNode.StartTime = Format$(TimeStart, "m/d/yyyy h:mm:ss AM/PM")
        tempNode.nodeName = name
        tempNode.nodetype = 0
        tempNode.NodeState = 0
        tempNode.EndTime = " "
        tempNode.TaskAutoID = 0
        tempNode.GroupAutoID = Reference
        tempNode.ExpandColapse = True
        activeWS.ChildNodes.Add tempNode
        
        ''add' does not need to set dataRow as chart will get redrawn
        Index = MDIMain.Tree.AddItem(name)
        Set MDIMain.Tree.ItemPicture(Index) = MDIMain.nodePict1
        MDIMain.Tree.ItemLevel(Index) = 1
        
        'code to get group related tasks from database
        mySQLStatement = "SELECT TaskID, TimeOffset FROM [TaskGroupSchedule] WHERE TaskGroupID = " & GroupID
        Set resultSet = dbConnection.OpenResultset(mySQLStatement, rdOpenKeyset)
 
        While Not resultSet.EOF
            resultSet.MoveNext
            RowReturn = RowReturn + 1
        Wend
 
        resultSet.MoveFirst
        TasklrArray = resultSet.GetRows(RowReturn)
        
        'Add each task in the taskgroup
        Dim TaskIdentification As Integer
        Dim TaskOffset As Integer
        
        For i = 0 To RowReturn - 1
            TaskIdentification = TasklrArray(0, i)
            TaskOffset = TasklrArray(1, i)
            AddGroupTask Reference, tempNode.StartTime, TaskIdentification, TaskOffset, activeWS, 1, GroupID
        Next i
        
    End If
    Unload frmAddTaskOrGroup
    Dim sel As SelectionType
    sel.row = 0
    sel.sType = HasFocus
    MDIMain.GanttChart.Selection = sel
    
End Sub
'Function/Subroutine:AddTask
'Purpose:When the add task button is clicked this function is called to
'make the appropriate database queries and then add the task and associated
'procedures in to the database/Workspace
Sub AddTask(ByRef activeWS As Workspace)

    Dim temp As Integer
    Dim TimeStart As Date
    Dim TimeEnd As String
    Dim mySQLStatement As String
    Dim RowReturn, j As Integer
    Dim rarray As Variant
    Dim lrArray As Variant
    Dim TaskID As Integer
    Dim Duration As Double
    Dim DurationString As String
    Dim resultSet As rdoResultset
    Dim tempinteger As Integer
    Dim WSID As Integer
    Dim TimeOffset As Integer
    Dim Start As Date
    Dim Reference As Integer
    Dim name As String
    Dim Index As Long
    
    RowReturn = 0

    'get user entered data: task, starttime and endtime
    frmAddTaskOrGroup.FormType = AddTaskType
    frmAddTaskOrGroup.Show vbModal, MDIMain
    If frmAddTaskOrGroup.CancelClick = False Then
        name = frmAddTaskOrGroup.ObjectName
        TaskID = frmAddTaskOrGroup.ObjectID
        
        'Make sure name was entered
        If name = "" Then
            MsgBox "Invalid Task", vbInformation
            Unload frmAddTaskOrGroup
            Exit Sub
        End If

        'Convert Dates to Correct format
        TimeStart = frmAddTaskOrGroup.InsertTime
 
        'code to get task related procedures from database/calculate duration
        mySQLStatement = "SELECT ProcedureID, TimeOffset, Duration FROM TaskProc WHERE TaskID = " & TaskID
        Set resultSet = dbConnection.OpenResultset(mySQLStatement, rdOpenKeyset)
 
        While Not resultSet.EOF
            resultSet.MoveNext
            RowReturn = RowReturn + 1
        Wend
 
        resultSet.MoveFirst
        rarray = resultSet.GetRows(RowReturn)
 
        'determine duration using largest start offset plus duration
        For j = 0 To RowReturn - 1
            If (rarray(1, j) + rarray(2, j)) > Duration Then
                Duration = rarray(1, j) + rarray(2, j)
            End If
        Next j
 
        'set the duration value as string for chart
        DurationString = Str(Duration) & "hours"
 
        'enter task in workspaceTaskSchedule
        WSID = activeWS.workspaceId
        Start = activeWS.StartTime
        TimeEnd = DateAdd("h", Duration, TimeStart)
        mySQLStatement = "INSERT INTO [WorkspaceTaskSchedule] (WorkspaceID, TaskID, StartTime, EndTime, GroupID, GroupReference) VALUES ( " & WSID & ", " & TaskID & ", " & SQLDate(TimeStart) & ", " & SQLDate(TimeEnd) & ", 0, 0)"
        Set resultSet = dbConnection.OpenResultset(mySQLStatement)
 
        mySQLStatement = "SELECT AutoReference FROM WorkspaceTaskSchedule WHERE TaskID = " & TaskID & " AND WorkspaceID = " & WSID & " AND StartTime = " & SQLDate(TimeStart) & " AND EndTime = " & SQLDate(TimeEnd) & " AND GroupID = 0" & " ORDER BY AutoReference DESC"
        Set resultSet = dbConnection.OpenResultset(mySQLStatement, rdOpenKeyset)
        lrArray = resultSet.GetRows(1)
        Reference = lrArray(0, 0) 'Reference = task auto reference
 
        'Code to enter task into Tree
        Dim tempNode As node_object
        Set tempNode = New node_object

        tempNode.StartTime = TimeStart
        tempNode.nodeName = name
        tempNode.nodetype = 1
        tempNode.NodeState = 0
        tempNode.EndTime = TimeEnd
        tempNode.TaskAutoID = Reference
        tempNode.GroupAutoID = 0
        tempNode.Identification = TaskID
        tempNode.ExpandColapse = True
        activeWS.ChildNodes.Add tempNode
        
        ''add' does not need to set dataRow as chart will get redrawn
        Index = MDIMain.Tree.AddItem(name)
        Set MDIMain.Tree.ItemPicture(Index) = MDIMain.nodePict2
        MDIMain.Tree.ItemLevel(Index) = 1
        
        'Add procedures associated with the task
        tempinteger = RowReturn
        AddProc rarray, tempinteger, TimeStart, 1, TaskID, Reference, activeWS, 0, 0
        
        MDIMain.GanttChart.RedrawGanttChart
    End If
    Unload frmAddTaskOrGroup

    Dim sel As SelectionType
    sel.row = 0
    sel.sType = HasFocus
    MDIMain.GanttChart.Selection = sel
'
End Sub
'Function/Subroutine:Add Mode
'Purpose:Adds a mode to the active workspace and updates database
Sub AddMode(ByRef activeWS As Workspace)
'
    Dim name As String
    Dim TimeStart As String
    Dim VBDate As String
    Dim finaldate As Date
    Dim modeID As Integer
    Dim resultSet As rdoResultset
    Dim mySQLStatement As String, nextModeStartTime As Date
        
    'Get user entered data
    frmAddMode.Show 1
    If frmAddMode.CancelClick = False Then
        name = frmAddMode.Combo3
        modeID = frmAddMode.modeID
        
        'make sure valid data was entered
        If name = "" Then
            MsgBox "Invalid Mode", vbInformation
            Unload frmAddMode
            Exit Sub
        End If
 
        
        'Convert Dates to Correct format
        TimeStart = frmAddMode.MonthView1.Value
 
        'Convert to VB date format for later calculations
 
        If frmAddMode.Combo6 = "" Then
            VBDate = "00:00:00 " & TimeStart
        Else
            VBDate = frmAddMode.Combo6 & ":00 " & TimeStart
        End If
        
        Dim WSID As Integer
        WSID = activeWS.workspaceId
        'Add new mode to gantt chart
        finaldate = VBDate
        
        'Check to make sure mode is allowed with procedures
        If pManager.isModeValid(finaldate, modeID, activeWS, nextModeStartTime) = True Then
            'Insert new mode into WorkspaceMode table
            'Dim wModeIndex As Integer
            'wModeIndex = MDIMain.GanttChart.GetModeArrayIndexFromDate(finaldate)
            'If wModeIndex <> -1 And wModeIndex < MDIMain.GanttChart.nModePeriods Then
            '    NextModeStartTime = MDIMain.GanttChart.GetModePeriodData(, wModeIndex + 1).PeriodTime
            'ElseIf finaldate < MDIMain.GanttChart.GetModePeriodData(, 1).PeriodTime Then
            '    NextModeStartTime = MDIMain.GanttChart.GetModePeriodData(, 1).PeriodTime
            'ElseIf finaldate > MDIMain.GanttChart.GetModePeriodData(, MDIMain.GanttChart.nModePeriods).PeriodTime Then
            '    NextModeStartTime = MDIMain.GetActiveWorkspace().EndTime
            'Else
                ' there is some kinda error
            '    MsgBox "Could not find next mode period.", "Program Error"
            'End If
            If Not pManager.AddWorkspaceMode(WSID, modeID, finaldate, name, nextModeStartTime) Then
                MsgBox "Mode Already Inserted", vbInformation
            Else
                'add mode to chart
                MDIMain.GanttChart.AddModePeriod finaldate, modeID, ModeList.Item(modeID).ModeColor, name
            End If
        Else
            MsgBox "Mode Can't be Added Due to Conflict With Existing Procedure or Mode.", vbInformation
        End If
        
    End If
    Unload frmAddMode
    
End Sub
'Function/Subroutine:AddProc
'Purpose: -startdate is task startdate
'Add a procedure to a workspace and update database
Sub AddProc(rarray As Variant, row As Integer, StartDate As Date, level As Integer, TaskID As Integer, Reference As Integer, ByRef WS As Workspace, GroupID As Integer, GroupReference As Integer)

    Dim i, j As Integer
    Dim ihour, iyear, iday, imonth As Integer
    Dim ProcStartDate As String
    Dim resultSet As rdoResultset
    Dim mySQLStatement As String
    Dim lrArray As Variant
    Dim tempString As String
    Dim tempString1 As String
    Dim WSID As Integer
    Dim name As String
    Dim Index As Long
    Dim ErrorString As String
    
    ErrorString = ""

    For i = 0 To row - 1
        'using the array of procedures passed to the sub get the procedure
        'information from the database
        ProcStartDate = DateAdd("h", rarray(1, i), StartDate)
        'Get procedure names
        mySQLStatement = "SELECT Procedure.ProcedureID, Procedure.ProcedureName From [Procedure] WHERE (((Procedure.ProcedureID)=" & rarray(0, i) & "))"
        Set resultSet = dbConnection.OpenResultset(mySQLStatement)
        'if empty procedure found display warning message (no associated procedures)
        If resultSet.EOF Then
                MsgBox "Task is Missing an Associated Procedure", vbInformation
        Else
        lrArray = resultSet.GetRows(1)
        name = lrArray(1, 0)

        'Add node to tree and collection
        Dim tempNode As node_object
                            
        Set tempNode = New node_object
                            
        tempNode.StartTime = Format$(ProcStartDate, "m/d/yyyy h:mm:ss AM/PM")
        tempNode.nodeName = name
        tempNode.nodetype = 2
        tempNode.NodeState = 0
        tempNode.TaskAutoID = Reference
        tempNode.GroupAutoID = GroupReference
        tempNode.Identification = lrArray(0, 0)
        tempNode.ExpandColapse = True
        tempNode.EndTime = Format$(DateAdd("h", rarray(2, i), tempNode.StartTime), "m/d/yyyy h:mm:ss AM/PM")
        
        
        WSID = WS.workspaceId
        
        'Enter Procedure in workspaceProcedure Table.
        Dim ProcID As Integer
        ProcID = lrArray(0, 0)
        'If node was valid add to tree and workspace
        If pManager.AddProcedure(WSID, GroupID, TaskID, ProcID, Reference, tempNode.StartTime, tempNode.EndTime) = True Then
            'add node to tree
            ''add' does not need to set dataRow as chart will get redrawn
            'Dim Index As Long
            Index = MDIMain.Tree.AddItem(name)
            Set MDIMain.Tree.ItemPicture(Index) = MDIMain.nodePict3
            MDIMain.Tree.ItemLevel(Index) = level + 1
         
            WS.ChildNodes.Add tempNode
        Else
            ErrorString = ErrorString & name & NewLine
        End If
        End If
    Next i
    
    If ErrorString <> "" Then
        MsgBox " The following procedures were not added due to mode conflicts: " & NewLine & NewLine & ErrorString, vbInformation
    End If
    'load updated data into objects
    OpenWorkspaces.LoadData WS
    

End Sub
'Function/Subroutine: AddGroupTask
'Purpose:Adds tasks associated with task groups to workspace and database
'and then calls the function to add the associated procedurs
Sub AddGroupTask(Reference As Integer, StartTime As String, TaskID As Integer, startoffset As Integer, ByRef WS As Workspace, level As Integer, GroupID As Integer)

    Dim TaskStartDate As Date
    Dim resultSet As rdoResultset
    Dim mySQLStatement As String
    Dim lrArray As Variant
    Dim ProclrArray As Variant
    Dim Duration As Integer
    Dim TimeEnd As String
    Dim WSID As Integer
    Dim TimeStart As String
    Dim Start As Date
    Dim name As String
    Dim RowReturn As Integer
    Dim j As Integer
    Dim TaskReference As Integer
    Dim Index As Long
    
    
    'calculate the start date for the task
    TaskStartDate = DateAdd("h", startoffset, StartTime)
    
    'Get task from task table
    mySQLStatement = "SELECT Task.TaskID, Task.TaskName From [Task] WHERE (((Task.TaskID)=" & TaskID & "))"
    Set resultSet = dbConnection.OpenResultset(mySQLStatement)
        If resultSet.EOF Then
            MsgBox "IDnumbers have gotten REALLY messed up in the task table", vbInformation
        End If
    lrArray = resultSet.GetRows(1)
    name = lrArray(1, 0)
    
    'code to get task related procedures from database/calculate duration
        mySQLStatement = "SELECT ProcedureID, TimeOffset, Duration FROM TaskProc WHERE TaskID = " & TaskID
        Set resultSet = dbConnection.OpenResultset(mySQLStatement, rdOpenKeyset)
 
        While Not resultSet.EOF
        resultSet.MoveNext
        RowReturn = RowReturn + 1
        Wend
 
        resultSet.MoveFirst
        ProclrArray = resultSet.GetRows(RowReturn)

        'determine duration using largest start offset plus duration
        For j = 0 To RowReturn - 1
            If (ProclrArray(1, j) + ProclrArray(2, j)) > Duration Then
                Duration = ProclrArray(1, j) + ProclrArray(2, j)
            End If
        Next j
    
    'enter task in workspaceTaskSchedule
    WSID = WS.workspaceId
    Start = WS.StartTime
    TimeStart = TaskStartDate
    TimeEnd = DateAdd("h", Duration, TimeStart)
    mySQLStatement = "INSERT INTO [WorkspaceTaskSchedule] (WorkspaceID, TaskID, StartTime, EndTime, GroupID, GroupReference) VALUES ( " & WSID & ", " & TaskID & ", " & SQLDate(TimeStart) & ", " & SQLDate(TimeEnd) & ", " & GroupID & ", " & Reference & ")"
    Set resultSet = dbConnection.OpenResultset(mySQLStatement)
 
    mySQLStatement = "SELECT AutoReference FROM WorkspaceTaskSchedule WHERE TaskID = " & TaskID & " AND WorkspaceID = " & WSID & " AND StartTime = " & SQLDate(TimeStart) & " AND EndTime = " & SQLDate(TimeEnd) & " AND GroupID = " & GroupID & "AND GroupReference = " & Reference
    Set resultSet = dbConnection.OpenResultset(mySQLStatement, rdOpenKeyset)
    lrArray = resultSet.GetRows(1)
    TaskReference = lrArray(0, 0) 'Reference = task auto reference

    'Enter node into tree here
    Dim tempNode As node_object
    Set tempNode = New node_object
                            
    tempNode.StartTime = Format$(TaskStartDate, "m/d/yyyy h:mm:ss AM/PM")
    tempNode.nodeName = name
    tempNode.nodetype = 1
    tempNode.NodeState = 0
    tempNode.TaskAutoID = TaskReference
    tempNode.GroupAutoID = Reference
    tempNode.Identification = TaskID
    tempNode.EndTime = Format$(TimeEnd, "m/d/yyyy h:mm:ss AM/PM") 'DateAdd("h", Duration, tempNode.StartTime)
    tempNode.ExpandColapse = True
    
    ''add' does not need to set dataRow as chart will get redrawn
    Index = MDIMain.Tree.AddItem(name)
    Set MDIMain.Tree.ItemPicture(Index) = MDIMain.nodePict2
    MDIMain.Tree.ItemLevel(Index) = 2
        
                            
    WS.ChildNodes.Add tempNode
    WSID = WS.workspaceId

    'call function to add associated procedurs
     AddProc ProclrArray, RowReturn, TaskStartDate, 2, TaskID, TaskReference, WS, GroupID, Reference
  
End Sub
'Function/Subroutine: Remove
'Purpose: Removes a group, task or procecdure from the activeWorkspace
Sub Remove(WS As Workspace)
    Dim CheckBranch As Long
    Dim removeNode As node_object
    Dim mySQLStatement As String
    Dim mySQL As String
    Dim RowReturn, i As Integer
    Dim rarray As Variant
    Dim j As Integer
    Dim idnumber As Integer

    Dim resultSet As rdoResultset
    
    CheckBranch = MDIMain.Tree.ListSelection
    
    For i = 1 To WS.ChildNodes.Count
        If CheckBranch = WS.ChildNodes.Item(i).DataRow Then
            Set removeNode = WS.ChildNodes.Item(i)
            'MsgBox Str(removeNode.parentNode)
            
            'remove a group
            If removeNode.nodetype = 0 Then
                
                'remove from database
                mySQLStatement = "DELETE FROM [WorkspaceTaskGroup] WHERE AutoReference = " & removeNode.GroupAutoID
                dbConnection.Execute (mySQLStatement)
                
                'remove tasks
                mySQLStatement = "DELETE FROM [WorkspaceTaskSchedule] WHERE GroupReference = " & removeNode.GroupAutoID
                dbConnection.Execute (mySQLStatement)
                
                'remove from collection
                idnumber = removeNode.GroupAutoID
                For j = WS.ChildNodes.Count To 1 Step -1
                    If WS.ChildNodes.Item(j).GroupAutoID = idnumber Then
                        If WS.ChildNodes.Item(j).nodetype = 2 Then
                            'remove procedures
                            pManager.DeleteProcedure WS.workspaceId, WS.ChildNodes.Item(j).Identification, WS.ChildNodes.Item(j).TaskAutoID, WS.ChildNodes.Item(j).StartTime, WS.ChildNodes.Item(j).EndTime
                        End If
                        WS.ChildNodes.Remove (j)
                    End If
                Next j
            End If
            
            'remove a task
            If removeNode.nodetype = 1 Then
                
                'remove from database

                mySQLStatement = "DELETE FROM [WorkspaceTaskSchedule] WHERE AutoReference = " & removeNode.TaskAutoID
                dbConnection.Execute (mySQLStatement)
                
                'remove from collection
                idnumber = removeNode.TaskAutoID
                For j = WS.ChildNodes.Count To 1 Step -1
                    If WS.ChildNodes.Item(j).TaskAutoID = idnumber Then
                        If WS.ChildNodes.Item(j).nodetype = 2 Then
                            'remove procedures
                            pManager.DeleteProcedure WS.workspaceId, WS.ChildNodes.Item(j).Identification, WS.ChildNodes.Item(j).TaskAutoID, WS.ChildNodes.Item(j).StartTime, WS.ChildNodes.Item(j).EndTime
                        End If
                        WS.ChildNodes.Remove (j)
                    End If
                Next j
            End If
            
            'remove a procedure
            If removeNode.nodetype = 2 Then
                'remove from database
                pManager.DeleteProcedure WS.workspaceId, removeNode.Identification, removeNode.TaskAutoID, removeNode.StartTime, removeNode.EndTime
                'remove from collection
                WS.ChildNodes.Remove (i)
            End If
            
            'remove a Mode
            If removeNode.nodetype = 3 Then
                RowReturn = 0
                'get list of workspace modes
                mySQL = "SELECT ModeID, StartTime, ModeName FROM [WorkspaceMode] WHERE WorkspaceID = " & MDIMain.returnID & " ORDER BY StartTime"
                Set resultSet = dbConnection.OpenResultset(mySQL, rdOpenKeyset)
                
                'If there are no modes
                If resultSet.EOF Then
                    MsgBox "No Modes Running", vbInformation
                    Exit Sub
                'Otherwise add them to the list
                Else
                    While Not resultSet.EOF
                    resultSet.MoveNext
                    RowReturn = RowReturn + 1
                    Wend
                    resultSet.MoveFirst
                    rarray = resultSet.GetRows(RowReturn)
                End If
            
                'move items to removeMode form
                RemoveMode.rarray = rarray
                RemoveMode.RowReturn = RowReturn
                'Implement remove mode form - does actual removal of mode
                RemoveMode.Show 1
                Unload RemoveMode
            End If

            
            Exit For
        End If
    Next i
    
    
    OpenWorkspaces.LoadData WS
    
    
End Sub
'Function/Subroutine: StartEnd
'Purpose: Change the start and end times of the active workspace
Sub StartEnd(ByRef WS As Workspace)
'
    Dim StartDate As String
    Dim EndDate As String
    Dim mySQL As String, resultSet As rdoResultset, rarray As Variant
    Dim OOSCount, ProcCount, TaskCount As Integer
    
    StartString = WS.StartTime
    EndString = WS.EndTime
    
    'get the new start and end time
    frmScaleDate.Show 1

    'if the process was not cancled then...
    If frmScaleDate.CancelClick = False Then

        StartDate = frmScaleDate.StartView.Value
        EndDate = frmScaleDate.EndView.Value
    
        ' determine impact of changing start and end times
        ' it could affect modes, tasks, procedures, taskgroups,
        ' and oos items
        'mySQL = "SELECT COUNT(*) FROM [OOSList] WHERE StartTime < " & SQLDate(StartTime) & " AND WorkspaceID = " & WS.workspaceId
        'Set resultSet = dbConnection.OpenResultset(mySQL)
        'rArray = resultSet.GetRows(1)
        ' for now, make the change regardless of how that affects
        ' items that are no longer withing workspace start and end time
        
        'update data in database
        mySQL = "UPDATE Workspace SET StartTime = " & SQLDate(StartDate) & ", EndTime = " & SQLDate(EndDate) & " WHERE WorkspaceID = " & WS.workspaceId
        dbConnection.Execute (mySQL)
        ' update the first mode so it begins at workspace start time
        mySQL = "UPDATE WorkspaceMode SET StartTime = " & SQLDate(StartDate) & " WHERE StartTime = " & SQLDate(WS.StartTime) & " AND WorkspaceID = " & WS.workspaceId & " AND ModeID = " & WS.InitialModeID
        dbConnection.Execute (mySQL)
        
        WS.StartTime = StartDate
        WS.EndTime = EndDate
        
        'load new data into objects
        OpenWorkspaces.LoadData WS
        
    Else
        Unload frmScaleDate
        Exit Sub
    End If
    Unload frmScaleDate
End Sub
'Function:AddOOSComponents
'Purpose: add a component to the out of service list, fisrt checking to
'make sure the move is a leagle one.
Sub AddOOSComponents(WS As Workspace)
'
    Dim mySQL As String
    Dim resultSet As rdoResultset
    Dim RowReturn As Integer
    Dim rarray As Variant
    Dim WSID As Integer
    Dim compID As Integer
    Dim CompName As String
    Dim StartTime As Date
    Dim EndTime As Date
    Dim overlap As Boolean
    Dim i As Integer
    
    'get user requested times
    frmComponent.StartDate = Now
    frmComponent.EndDate = Now
    frmComponent.Show 1
    
    'If the process wasn't cancled then...
    If frmComponent.CancelClick = False Then
        WSID = WS.workspaceId
        compID = frmComponent.compID
        CompName = frmComponent.CompName
        StartTime = Format$(frmComponent.StartDate, "m/d/yyyy h:mm:ss AM/PM")
        EndTime = Format$(frmComponent.EndDate, "m/d/yyyy h:mm:ss AM/PM")
        
        'Check to see if component is already in the out of service list
        mySQL = "SELECT StartTime, EndTime FROM [OOSList] WHERE ComponentName = '" & CompName & "'AND WorkspaceID = " & WS.workspaceId
        Set resultSet = dbConnection.OpenResultset(mySQL, rdOpenKeyset)
        
        If resultSet.EOF Then 'if not already listed add to table
            pManager.AddOOSItem WSID, compID, StartTime, EndTime, CompName
        Else
            While Not resultSet.EOF
                resultSet.MoveNext
                RowReturn = RowReturn + 1
            Wend
            resultSet.MoveFirst
            rarray = resultSet.GetRows(RowReturn)
                
            'Check to make sure times dont overlap if component is already
            'listed as out of service (component can be out of service more
            'than once just not at the same time.
            For i = 0 To RowReturn - 1
                If (StartTime > rarray(0, i) And StartTime < rarray(1, i)) Or (StartTime < rarray(0, i) And EndTime > rarray(0, i)) Then
                    MsgBox "Can't Place Component OOS More Than Once During Time Period", vbInformation
                    overlap = True
                ElseIf (EndTime > rarray(0, i) And EndTime < rarray(1, i)) Or (EndTime < rarray(1, i) And StartTime > rarray(1, i)) Then
                    MsgBox "Can't Place Component OOS More Than Once During Time Period", vbInformation
                    overlap = True
                End If
            Next i
            
            If overlap = False Then 'if no conflict that add to list
                pManager.AddOOSItem WSID, compID, StartTime, EndTime, CompName
            End If
        End If
        'update data in objects
        OpenWorkspaces.ooslistControl WS
        MDIMain.GanttChart1.RedrawGanttChart
    End If
    
    Unload frmComponent
    
    Dim sel As SelectionType
    sel.row = 0
    sel.sType = HasFocus
    MDIMain.GanttChart1.Selection = sel
    MDIMain.OOSTree.Selected(0) = True
End Sub
'Function: RemoveOOSComponents
'Purpose: To remove a component from the out of service list
Sub RemoveOOSComponents(WS As Workspace)
'
    Dim Index As Long
    Dim name As String
    Dim StartTime As Date
    Dim EndTime As Date
    Dim mySQLStatement As String
    
    Index = MDIMain.OOSTree.ListSelection
    If Index > 1 Then
        name = MDIMain.OOSTree.CellText(Index, 0)
        StartTime = MDIMain.OOSTree.CellText(Index, 1)
        EndTime = MDIMain.OOSTree.CellText(Index, 2)
        
        'remove element from database
        pManager.RemoveOOSItem WS.workspaceId, name, StartTime, EndTime
        'update objects
        OpenWorkspaces.ooslistControl WS
        MDIMain.GanttChart1.RedrawGanttChart
    Else
        MsgBox "No Component Selected", vbInformation
    End If
End Sub
'Function: ChangeOOSComponents
'Purpose: Change the start and endtime of a component in the out of service
'list, check to make sure chage is leagle then change.
Sub ChangeOOSComponents(WS As Workspace)
'
    Dim Index As Long
    Dim OldStart As Date
    Dim OldEnd As Date
    Dim name As String
    Dim StartDate As Date
    Dim EndDate As Date
    Dim mySQL As String
    Dim resultSet As rdoResultset
    Dim rarray As Variant
    Dim RowReturn As Integer
    Dim i As Integer
    Dim overlap As Boolean 'flad to determine if OOS component times overlap
    
    overlap = False
    
    Index = MDIMain.OOSTree.ListSelection
    
    If Index > 1 Then ' make sure selected node is a component
    
        name = MDIMain.OOSTree.CellText(Index, 0)
        TimeEdit.LabelText = name
        OldStart = MDIMain.OOSTree.CellText(Index, 1)
        OldEnd = MDIMain.OOSTree.CellText(Index, 2)
        
        'get user input
        TimeEdit.StartDate = OldStart
        TimeEdit.EndDate = OldEnd
        TimeEdit.Show 1
        
        StartDate = Format$(TimeEdit.StartDate, "m/d/yyyy h:mm:ss AM/PM")
        EndDate = Format$(TimeEdit.EndDate, "m/d/yyyy h:mm:ss AM/PM")
        
        Unload TimeEdit
        
        'Check to see if component is already in the out of service list
        mySQL = "SELECT StartTime, EndTime FROM [OOSList] WHERE ComponentName = '" & name & "'AND WorkspaceID = " & WS.workspaceId
        Set resultSet = dbConnection.OpenResultset(mySQL, rdOpenKeyset)
        
        If resultSet.EOF Then 'if no conflict than add to list
            pManager.UpdateOOSItem StartDate, EndDate, OldStart, OldEnd, WS.workspaceId, name
            'update objects
            OpenWorkspaces.ooslistControl WS
            MDIMain.GanttChart1.RedrawGanttChart
        Else
            While Not resultSet.EOF
                resultSet.MoveNext
                RowReturn = RowReturn + 1
            Wend
            resultSet.MoveFirst
            rarray = resultSet.GetRows(RowReturn)
                
            For i = 0 To RowReturn - 1
                If OldStart = rarray(0, i) And OldEnd = rarray(1, i) Then
                    'Do Nothing - dont check components own record
                Else
                    'if startdates overlap
                    If (StartDate > rarray(0, i) And StartDate < rarray(1, i)) Or (StartDate < rarray(0, i) And EndDate > rarray(0, i)) Then
                        MsgBox "Can't Place Component OOS More Than Once During Time Period", vbInformation
                        overlap = True
                    'if enddates overlap
                    ElseIf (EndDate > rarray(0, i) And EndDate < rarray(1, i)) Or (EndDate < rarray(1, i) And StartDate > rarray(1, i)) Then
                        MsgBox "Can't Place Component OOS More Than Once During Time Period", vbInformation
                        overlap = True
                    End If
                End If
            Next i
            
            If overlap = False Then 'if no conflict than add to list
                pManager.UpdateOOSItem StartDate, EndDate, OldStart, OldEnd, WS.workspaceId, name
                'update objects
                OpenWorkspaces.ooslistControl WS
                MDIMain.GanttChart1.RedrawGanttChart
            End If
        End If
    Else
        MsgBox "No Component Selected", vbInformation
    End If
    
End Sub
'Function: Copy_Workspace
'Purpose: Copy an existing workspace - save as command
Public Sub Copy_Workspace(WS As Workspace)
    Dim WSName As String, WSDescription As String
    Dim mySQLStatement As String
    Dim resultSet As rdoResultset
    Dim lrArray As Variant
    Dim workspaceId As Integer
    Dim RowReturn As Integer
    Dim i As Integer
    Dim groupindex As Integer
    Dim taskindex As Integer
    Dim groupArray As Variant
    Dim taskArray As Variant
    Dim ProcArray As Variant
    Dim taskrow As Integer
    Dim procRow As Integer
    Dim taskindexArray As Variant
    Dim WorkspaceType As Integer
    
    
    'Query user for new workspace name
    WorkspaceProperties.WSEndDate.Value = MDIMain.GetActiveWorkspace().EndTime
    WorkspaceProperties.WSStartDate.Value = MDIMain.GetActiveWorkspace().StartTime
    WorkspaceProperties.WSEndDate.Enabled = False
    WorkspaceProperties.WSStartDate.Enabled = False
    WorkspaceProperties.InitialModeCombo.Enabled = False
    WorkspaceProperties.InitialMode = MDIMain.GetActiveWorkspace().InitialModeID
    WorkspaceProperties.Text1.text = MDIMain.GetActiveWorkspace().WorkspaceName & " Copy"
    WorkspaceProperties.Text2.text = MDIMain.GetActiveWorkspace().WorkspaceDescription
    WorkspaceProperties.Show 1
    If WorkspaceProperties.result = False Then
        Exit Sub
    End If
    WSName = WorkspaceProperties.Text1
    WSDescription = WorkspaceProperties.Text2
    WorkspaceType = WorkspaceProperties.WorkspaceType
    Unload WorkspaceProperties

    'Create new workspace in database
    mySQLStatement = "INSERT INTO [Workspace] (WorkspaceName, WorkspaceDesc, UserID, AccessType, StartTime, EndTime, CreateDate) VALUES ( '" & WSName & "','" & WSDescription & "'," & userID & ", " & WorkspaceType & "," & SQLDate(WS.StartTime) & "," & SQLDate(WS.EndTime) & "," & SQLDate(Now) & ")"
    Set resultSet = dbConnection.OpenResultset(mySQLStatement)

    'Get the worspace Id from the newly created record
    mySQLStatement = "SELECT Workspace.WorkspaceID FROM [Workspace] WHERE WorkspaceName = '" & WSName & "'"
    Set resultSet = dbConnection.OpenResultset(mySQLStatement)
    lrArray = resultSet.GetRows(1)
    workspaceId = lrArray(0, 0)

    'Put workspace in openWorkspaces list
    'mySQLStatement = "INSERT INTO [OpenWorkspaces] (WorkspaceID, UserID) VALUES ( " & lrArray(0, 0) & ", " & userID & ")"
    'Set resultSet = dbConnection.OpenResultset(mySQLStatement)
    
    'Copy information in workspacemodes table
    mySQLStatement = "SELECT ModeID, StartTime, ModeName FROM [WorkspaceMode] WHERE WorkspaceID = " & WS.workspaceId
    Set resultSet = dbConnection.OpenResultset(mySQLStatement, rdOpenKeyset)
    
    While Not resultSet.EOF
        resultSet.MoveNext
        RowReturn = RowReturn + 1
    Wend
    
    If RowReturn > 0 Then
        resultSet.MoveFirst
        lrArray = resultSet.GetRows(RowReturn)
    
        For i = 0 To RowReturn - 1
            mySQLStatement = "INSERT INTO [WorkspaceMode] (WorkspaceID, ModeID, StartTime, ModeName) VALUES ( " & workspaceId & ", " & lrArray(0, i) & ", " & SQLDate(lrArray(1, i)) & ", '" & lrArray(2, i) & "')"
            dbConnection.Execute (mySQLStatement)
        Next i
    End If
    
   
    
   RowReturn = 0
    'Copy information in ooslist table
    mySQLStatement = "SELECT ComponentID, StartTime, EndTime, ComponentName FROM [OOSList] WHERE WorkspaceID = " & WS.workspaceId
    Set resultSet = dbConnection.OpenResultset(mySQLStatement, rdOpenKeyset)
    
    While Not resultSet.EOF
        resultSet.MoveNext
        RowReturn = RowReturn + 1
    Wend
    
    If RowReturn > 0 Then
        resultSet.MoveFirst
        lrArray = resultSet.GetRows(RowReturn)
    
        For i = 0 To RowReturn - 1
            mySQLStatement = "INSERT INTO [OOSList] (WorkspaceID, ComponentID, StartTime, EndTime, ComponentName) VALUES ( " & workspaceId & ", " & lrArray(0, i) & ", " & SQLDate(lrArray(1, i)) & ", '" & lrArray(2, i) & "', '" & lrArray(3, i) & "')"
            dbConnection.Execute (mySQLStatement)
        Next i
    End If
    
    RowReturn = 0
    'Copy information in riskperiods table
    mySQLStatement = "SELECT PeriodTime, NeedUpdate, RiskValue FROM [RiskPeriods] WHERE WorkspaceID = " & WS.workspaceId
    Set resultSet = dbConnection.OpenResultset(mySQLStatement, rdOpenKeyset)
    
    While Not resultSet.EOF
        resultSet.MoveNext
        RowReturn = RowReturn + 1
    Wend
    
    If RowReturn > 0 Then
        resultSet.MoveFirst
        lrArray = resultSet.GetRows(RowReturn)
    
        For i = 0 To RowReturn - 1
            mySQLStatement = "INSERT INTO [RiskPeriods] (WorkspaceID, PeriodTime, NeedUpdate, RiskValue) VALUES ( " & workspaceId & ", " & SQLDate(lrArray(0, i)) & ", " & lrArray(1, i) & ", " & lrArray(2, i) & ")"
            dbConnection.Execute (mySQLStatement)
        Next i
    End If
    
     RowReturn = 0
    'Copy information in workspacetaskgroup table
    mySQLStatement = "SELECT TaskGroupID, StartTime, AutoReference FROM [WorkspaceTaskGroup] WHERE WorkspaceID = " & WS.workspaceId
    Set resultSet = dbConnection.OpenResultset(mySQLStatement, rdOpenKeyset)
    
    While Not resultSet.EOF
        resultSet.MoveNext
        RowReturn = RowReturn + 1
    Wend
    
    If RowReturn > 0 Then
        resultSet.MoveFirst
        lrArray = resultSet.GetRows(RowReturn)
    
        For i = 0 To RowReturn - 1
            mySQLStatement = "INSERT INTO [WorkspaceTaskGroup] (WorkspaceID, TaskGroupID, StartTime) VALUES ( " & workspaceId & ", " & lrArray(0, i) & ", '" & lrArray(1, i) & "')"
            dbConnection.Execute (mySQLStatement)
            
            mySQLStatement = "SELECT AutoReference FROM WorkspaceTaskGroup WHERE TaskGroupID = " & lrArray(0, i) & " AND WorkspaceID = " & workspaceId & " AND StartTime = " & SQLDate(lrArray(1, i)) & " ORDER BY AutoReference DESC"
            Set resultSet = dbConnection.OpenResultset(mySQLStatement, rdOpenKeyset)
            groupArray = resultSet.GetRows(1)
            groupindex = groupArray(0, 0) 'index= group auto reference
            
            taskrow = 0
            'Copy group information in workspacetaskschedule table
             mySQLStatement = "SELECT TaskID, StartTime, EndTime, GroupID, AutoReference FROM [WorkspaceTaskSchedule] WHERE WorkspaceID = " & WS.workspaceId & " AND GroupReference = " & lrArray(2, i)
             Set resultSet = dbConnection.OpenResultset(mySQLStatement, rdOpenKeyset)
    
             While Not resultSet.EOF
                 resultSet.MoveNext
                taskrow = taskrow + 1
                Wend
    
             If taskrow > 0 Then
                resultSet.MoveFirst
                 taskArray = resultSet.GetRows(taskrow)
    
                Dim j As Integer
                 For j = 0 To taskrow - 1
                     mySQLStatement = "INSERT INTO [WorkspaceTaskSchedule] (WorkspaceID, TaskID, StartTime, EndTime, GroupID, GroupReference) VALUES ( " & workspaceId & ", " & taskArray(0, j) & ", " & SQLDate(taskArray(1, j)) & ", " & SQLDate(taskArray(2, j)) & ", " & taskArray(3, j) & ", " & groupindex & ")"
                     dbConnection.Execute (mySQLStatement)
                     
                     mySQLStatement = "SELECT AutoReference FROM WorkspaceTaskSchedule WHERE GroupReference = " & groupindex & " AND WorkspaceID = " & workspaceId & " AND StartTime = " & SQLDate(taskArray(1, j)) & " ORDER BY AutoReference DESC"
                    Set resultSet = dbConnection.OpenResultset(mySQLStatement, rdOpenKeyset)
                    taskindexArray = resultSet.GetRows(1)
                    taskindex = taskindexArray(0, 0) 'index= group auto reference
                     
                    procRow = 0
                    'copy procedure information from table
                    mySQLStatement = "SELECT ProcedureID, StartTime, EndTime, TaskID, GroupID FROM [WorkspaceProcedures] WHERE WorkspaceID = " & WS.workspaceId & " AND TaskReference = " & taskArray(4, j)
                    Set resultSet = dbConnection.OpenResultset(mySQLStatement, rdOpenKeyset)
                    
                    While Not resultSet.EOF
                        resultSet.MoveNext
                        procRow = procRow + 1
                    Wend
    
                    If procRow > 0 Then
                        resultSet.MoveFirst
                        ProcArray = resultSet.GetRows(procRow)
                         
                        Dim k As Integer
                        For k = 0 To procRow - 1
                            mySQLStatement = "INSERT INTO [WorkspaceProcedures] (WorkspaceID, ProcedureID, StartTime, EndTime, TaskID, GroupID, TaskReference) VALUES ( " & workspaceId & ", " & ProcArray(0, k) & ", " & SQLDate(ProcArray(1, k)) & ", " & SQLDate(ProcArray(2, k)) & ", " & ProcArray(3, k) & ", " & ProcArray(4, k) & ", " & taskindex & ")"
                            dbConnection.Execute (mySQLStatement)
                        Next k
                    End If
                    
                Next j
             End If
        Next i
    End If
    
    taskrow = 0
    'Copy non-group information in workspacetaskschedule table
     mySQLStatement = "SELECT TaskID, StartTime, EndTime, GroupID, AutoReference FROM [WorkspaceTaskSchedule] WHERE WorkspaceID = " & WS.workspaceId & " AND GroupReference = 0"
     Set resultSet = dbConnection.OpenResultset(mySQLStatement, rdOpenKeyset)

     While Not resultSet.EOF
         resultSet.MoveNext
        taskrow = taskrow + 1
        Wend

     If taskrow > 0 Then
        resultSet.MoveFirst
         taskArray = resultSet.GetRows(taskrow)

       ' Dim j As Integer
         For j = 0 To taskrow - 1
             mySQLStatement = "INSERT INTO [WorkspaceTaskSchedule] (WorkspaceID, TaskID, StartTime, EndTime, GroupID, GroupReference) VALUES ( " & workspaceId & ", " & taskArray(0, j) & ", " & SQLDate(taskArray(1, j)) & ", " & SQLDate(taskArray(2, j)) & ", " & taskArray(3, j) & ", 0)"
             dbConnection.Execute (mySQLStatement)
             
             mySQLStatement = "SELECT AutoReference FROM WorkspaceTaskSchedule WHERE GroupReference = 0 AND WorkspaceID = " & workspaceId & " AND StartTime = " & SQLDate(taskArray(1, j)) & " ORDER BY AutoReference DESC"
            Set resultSet = dbConnection.OpenResultset(mySQLStatement, rdOpenKeyset)
            taskindexArray = resultSet.GetRows(1)
            taskindex = taskindexArray(0, 0) 'index= group auto reference
             
            procRow = 0
            'copy procedure information from table
            mySQLStatement = "SELECT ProcedureID, StartTime, EndTime, TaskID, GroupID FROM [WorkspaceProcedures] WHERE WorkspaceID = " & WS.workspaceId & " AND TaskReference = " & taskArray(4, j)
            Set resultSet = dbConnection.OpenResultset(mySQLStatement, rdOpenKeyset)
            
            While Not resultSet.EOF
                resultSet.MoveNext
                procRow = procRow + 1
            Wend

            If procRow > 0 Then
                resultSet.MoveFirst
                ProcArray = resultSet.GetRows(procRow)
                 
            '    Dim k As Integer
                For k = 0 To procRow - 1
                    mySQLStatement = "INSERT INTO [WorkspaceProcedures] (WorkspaceID, ProcedureID, StartTime, EndTime, TaskID, GroupID, TaskReference) VALUES ( " & workspaceId & ", " & ProcArray(0, k) & ", " & SQLDate(ProcArray(1, k)) & ", " & SQLDate(ProcArray(2, k)) & ", " & ProcArray(3, k) & ", " & ProcArray(4, k) & ", " & taskindex & ")"
                    dbConnection.Execute (mySQLStatement)
                Next k
            End If
            
        Next j
     End If
    
    'load workspace
    
    OpenWorkspaces.open_workspace workspaceId
    
        
End Sub
'Function:Delete_workspace
'Purpose:delete and existing workspace that is not currently open.
Public Function Delete_workspace()
'
    Dim WSID As Integer
    Dim RowReturn As Integer
    Dim mySQL As String
    Dim resultSet As rdoResultset
    Dim rarray As Variant
    Dim i As Integer
    
    RowReturn = 0
    
    mySQL = "SELECT WorkspaceID, WorkspaceName FROM [Workspace] WHERE UserID = " & userID
    Set resultSet = dbConnection.OpenResultset(mySQL, rdOpenKeyset)
        
    'determine number of rows
    While Not resultSet.EOF
        resultSet.MoveNext
        RowReturn = RowReturn + 1
    Wend
    If RowReturn = 0 Then
        MsgBox "There are no workspaces found which you have rights to delete.", vbInformation
        Exit Function
    End If
    
    resultSet.MoveFirst
    rarray = resultSet.GetRows(RowReturn)
    
    SelectWorkspace.rarray = rarray
    SelectWorkspace.RowReturn = RowReturn
    

    SelectWorkspace.Show 1
    WSID = SelectWorkspace.WSID
    
    If SelectWorkspace.CancelClick = False Then
        Unload SelectWorkspace
        
        RowReturn = 0
        mySQL = "SELECT * FROM [OpenWorkspaces] WHERE WorkspaceId = " & WSID
        Set resultSet = dbConnection.OpenResultset(mySQL, rdOpenKeyset)
        
        While Not resultSet.EOF
            resultSet.MoveNext
            RowReturn = RowReturn + 1
        Wend
        
        'check to make sure workspace is not in use
        If RowReturn > 0 Then
            MsgBox "Can't Delete Open Workspace", vbInformation
            Exit Function
        End If
        
        'remove workspace entries from OOSList
        mySQL = "DELETE FROM [OOSList] WHERE WorkspaceID = " & WSID
        dbConnection.Execute (mySQL)
        
        'remove workspace entries from RiskPeriods
        mySQL = "DELETE FROM [RiskPeriods] WHERE WorkspaceID = " & WSID
        dbConnection.Execute (mySQL)
        
        'remove workspace entries from WorkspaceTaskSchedule
        mySQL = "DELETE FROM [WorkspaceTaskSchedule] WHERE WorkspaceID = " & WSID
        dbConnection.Execute (mySQL)
        
        'remove workspace entries from Workspace
        mySQL = "DELETE FROM [Workspace] WHERE WorkspaceID = " & WSID
        dbConnection.Execute (mySQL)
        
        'remove workspace entries from WorkspaceMode
        mySQL = "DELETE FROM [WorkspaceMode] WHERE WorkspaceID = " & WSID
        dbConnection.Execute (mySQL)
        
        'remove workspace entries from WorkspaceProcedures
        mySQL = "DELETE FROM [WorkspaceProcedures] WHERE WorkspaceID = " & WSID
        dbConnection.Execute (mySQL)
        
        'remove workspace entries from WorkspaceTaskGroup
        mySQL = "DELETE FROM [WorkspaceTaskGroup] WHERE WorkspaceID = " & WSID
        dbConnection.Execute (mySQL)
    Else
        Unload SelectWorkspace
    End If
    
End Function
'Function ChangeModeTime
'Purpose : when the user clicks and drags a mode bar this function is
'called. It determines weather or not the change would be valid and if
'so performs the update.
Public Function ChangeModeTime(modeID As Integer, ModeName As String, OldStartTime As Date, NewStartTime As Date, WS As Workspace)
    Dim mySQL As String
    Dim ModeBefore As Variant
    Dim ModeAfter As Variant
    Dim resultSet As rdoResultset
    Dim tempv As Variant
    Dim tempb As Boolean, nextModeTime As Date
    
    If OldStartTime > NewStartTime Then
        mySQL = "SELECT ModeID, StartTime, ModeName FROM [WorkspaceMode] WHERE WorkspaceID = " _
            & WS.workspaceId & " AND StartTime < " & SQLDate(OldStartTime) & _
            " ORDER BY StartTime DESC"
        Set resultSet = dbConnection.OpenResultset(mySQL, rdOpenKeyset)
        
        If resultSet.EOF Then
            'update data in database
            mySQL = "UPDATE WorkspaceMode SET StartTime = " & SQLDate(NewStartTime) & _
                " WHERE WorkspaceID = " _
                & WS.workspaceId & " AND StartTime = " & SQLDate(OldStartTime)
            dbConnection.Execute (mySQL)
            tempv = OldStartTime
            MDIMain.GanttChart.SetModePeriodTime NewStartTime, , tempv
            Exit Function
        Else
            ModeBefore = resultSet.GetRows(1)
            
            If ModeBefore(1, 0) > NewStartTime Then
                MsgBox "Invalid Change", vbInformation
                Exit Function
            Else
                If pManager.isModeValid(NewStartTime, modeID, WS, nextModeTime) Then
                    'update data in database
                     'mySQL = "UPDATE WorkspaceMode SET StartTime = " & getDataDelimitor() & NewStartTime & getDataDelimitor() _
                     '& " WHERE WorkspaceID = " _
                     '   & WS.workspaceId & " AND StartTime  =" & getDataDelimitor() & OldStartTime _
                     '   & getDataDelimitor()
                     'dbConnection.Execute (mySQL)
                     pManager.ChangeWorkspaceMode WS.workspaceId, NewStartTime, OldStartTime, nextModeTime

                     'Dim tempv As Variant
                     tempv = OldStartTime
                     tempb = MDIMain.GanttChart.SetModePeriodTime(NewStartTime, , OldStartTime)
                Else
                    MsgBox "Mode is invalid at time specified.", vbInformation
                    Exit Function
                End If
            End If
        End If
        
        
    ElseIf NewStartTime > OldStartTime Then
        'GET MODE BEFORE
        mySQL = "SELECT ModeID, StartTime, ModeName FROM [WorkspaceMode] WHERE WorkspaceID = " _
            & WS.workspaceId & " AND StartTime < " & SQLDate(OldStartTime) _
            & " ORDER BY StartTime DESC"
        Set resultSet = dbConnection.OpenResultset(mySQL, rdOpenKeyset)
    
        If Not resultSet.EOF Then
            ModeBefore = resultSet.GetRows(1)
        Else
            MsgBox "Can't Change First Mode", vbInformation
            Exit Function
        End If
        Dim tempDate As Date
        Dim tempID As Integer
        tempDate = ModeBefore(1, 0)
        tempID = ModeBefore(0, 0)
        If pManager.isModeValidBetweenDates(tempDate, NewStartTime, tempID, WS) Then
            'mySQL = "UPDATE WorkspaceMode SET StartTime = " & getDataDelimitor() & NewStartTime & getDataDelimitor() _
            '         & " WHERE WorkspaceID = " _
            '            & WS.workspaceId & " AND StartTime  =" & getDataDelimitor() & OldStartTime _
            '            & getDataDelimitor()
            'dbConnection.Execute (mySQL)
            'Insert new mode into WorkspaceMode table
            Dim wModeIndex As Integer
            wModeIndex = MDIMain.GanttChart.GetModeArrayIndexFromDate(NewStartTime)
            If wModeIndex <> -1 And wModeIndex < MDIMain.GanttChart.nModePeriods Then
                nextModeTime = MDIMain.GanttChart.GetModePeriodData(, wModeIndex + 1).PeriodTime
            ElseIf NewStartTime < MDIMain.GanttChart.GetModePeriodData(, 1).PeriodTime Then
                nextModeTime = MDIMain.GanttChart.GetModePeriodData(, 1).PeriodTime
            ElseIf NewStartTime > MDIMain.GanttChart.GetModePeriodData(, MDIMain.GanttChart.nModePeriods).PeriodTime Then
                nextModeTime = MDIMain.GetActiveWorkspace().EndTime
            Else
                ' there is some kinda error
                MsgBox "Could not find next mode period.", "Program Error"
            End If
            pManager.ChangeWorkspaceMode WS.workspaceId, NewStartTime, OldStartTime, nextModeTime
            'Dim tempv As Variant
            tempv = OldStartTime
            MDIMain.GanttChart.SetModePeriodTime NewStartTime, , tempv
        Else
            MsgBox "Mode is invalid at time specified", vbInformation
            Exit Function
        End If
    End If
End Function





