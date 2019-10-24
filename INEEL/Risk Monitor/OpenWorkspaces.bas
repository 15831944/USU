Attribute VB_Name = "OpenWorkspaces"
Option Explicit
Public check(0 To 10) As Integer
Public WorkspacesLoaded As Boolean
Public taskArray As Variant
Public ProcArray As Variant
Public activeWorkspace As Workspace
'Function/Subroutine:Get_Open_Workspaces
'Purpose: On openting the program Determines if the user has any
'open workspaces if so for each group it ads the group, included tasks
'included procedures. For any task not in a group adds tasks and
'included procedurs into the open workspace. The function then calles
'other functions to population the objects with the appropriate data.
Sub Get_Open_Workspaces()
    Dim RowReturn As Integer
    Dim i As Integer
    Dim j As Integer
    Dim k As Integer
    Dim l As Integer
    Dim n As Integer
    Dim a As Integer
    Dim rArray As Variant
    Dim lrArray As Variant
    Dim mySQLStatement As String
    Dim resultSet As rdoResultset
    Dim ProcRowReturn As Integer
    Dim TaskRowReturn As Integer
    Dim PRowReturn As Integer
    Dim TRowReturn As Integer
    Dim TasklrArray As Variant
    Dim ProclrArray As Variant
    Dim temp As Integer
    Dim STime As String
    Dim GIndex As Integer
    Dim Duration As Integer
    Dim GrouplrArray As Variant
    Dim GroupRowReturn As Integer
    Dim glrArray As Variant
    Dim name As String
    Dim GroupTime As String
    Dim wsOpened As Integer
    
    RowReturn = 0
    
    'Create a table to hold procedure data so It dosent have to be returned from the table more than once.
    mySQLStatement = "SELECT ProcedureID, ProcedureName FROM [Procedure]"
    Set resultSet = dbConnection.OpenResultset(mySQLStatement, rdOpenKeyset)
    
    While Not resultSet.EOF
        resultSet.MoveNext
        PRowReturn = PRowReturn + 1
    Wend
    If PRowReturn > 0 Then
        resultSet.MoveFirst
        ProcArray = resultSet.GetRows(PRowReturn)
    End If
    
    
    'Create a table to hold task data so It dosent have to be returned from the table more than once.
    mySQLStatement = "SELECT Task.TaskID, Task.TaskName FROM [Task]"
    Set resultSet = dbConnection.OpenResultset(mySQLStatement, rdOpenKeyset)
    
    While Not resultSet.EOF
        resultSet.MoveNext
        TRowReturn = TRowReturn + 1
    Wend
    
    If TRowReturn > 0 Then
        resultSet.MoveFirst
        taskArray = resultSet.GetRows(TRowReturn)
    End If
    
    
    'Get a list of workspaces the user has open
    mySQLStatement = "SELECT OpenWorkspaces.WorkspaceID FROM [OpenWorkspaces] WHERE UserID =" & userID
    Set resultSet = dbConnection.OpenResultset(mySQLStatement, rdOpenKeyset)
        
    'determine number of rows
    While Not resultSet.EOF
        resultSet.MoveNext
        RowReturn = RowReturn + 1
    Wend
    
    'If the user has no workspaces open
    If RowReturn > 0 Then
        MDIMain.active = True
        'get specified number of rows
        resultSet.MoveFirst
        rArray = resultSet.GetRows(RowReturn)
        
        'For each workspace found
        For i = 0 To RowReturn - 1
            'Get Workspace Information
            mySQLStatement = "SELECT Workspace.WorkspaceID, Workspace.WorkspaceName, Workspace.UserID, Workspace.AccessType, Workspace.StartTime, Workspace.EndTime, Workspace.CreateDate FROM [Workspace] WHERE WorkspaceID =" & rArray(0, i)
            Set resultSet = dbConnection.OpenResultset(mySQLStatement, rdOpenKeyset)
            If resultSet.EOF Then
                mySQLStatement = "DELETE FROM OpenWorkspaces WHERE WorkspaceID = " & rArray(0, i)
                dbConnection.Execute (mySQLStatement)
            Else
                wsOpened = wsOpened + 1
                lrArray = resultSet.GetRows(1)
                Set activeWorkspace = MDIMain.Active_Workspace
                
                'Set Workspace Data and create new active workspace
                With activeWorkspace
                    .workspaceId = lrArray(0, 0)
                    'If lrArray(3, 0) = 1 Then
                    '    .modifyAccess = True
                    'Else
                    '   .modifyAccess = False
                    'End If
                    .creatorId = lrArray(2, 0)
                    .StartTime = lrArray(4, 0)
                    .EndTime = lrArray(5, 0)
                    .dateLastModified = Now
                    .dateCreated = lrArray(6, 0)
                    .WorkspaceName = lrArray(1, 0) '"Workspace " & activeWorkspaceIndex
              End With
                
                'Add new workspace to collection
                MDIMain.Active_Workspace_Add activeWorkspace
                
                'create tab strip to represent workspace
                If (i = 0) Then
                     Set activeWorkspace.tabCtrl = MDIMain.TabStrip1.Tabs(1)
                Else
                    Set activeWorkspace.tabCtrl = MDIMain.TabStrip1.Tabs.Add()
                End If
                
                activeWorkspace.tabCtrl.Caption = activeWorkspace.WorkspaceName '"Workspace " & MDIMain.activeWorkspaceIndex
                activeWorkspace.tabCtrl.Selected = True
    '''''MODE''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
                'define the mode node for the tree
                Dim tempNode As node_object
                Set tempNode = New node_object
                
                tempNode.StartTime = activeWorkspace.StartTime
                tempNode.nodeName = "MODE"
                tempNode.nodetype = 3
                tempNode.NodeState = 0
                tempNode.EndTime = activeWorkspace.EndTime
                tempNode.TaskAutoID = 0
                tempNode.GroupAutoID = 0
                tempNode.ExpandColapse = True
                activeWorkspace.ChildNodes.Add tempNode
                
    '''''GROUPS''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
                'Get Groups associated with workspace
                mySQLStatement = "SELECT WorkspaceTaskGroup.TaskGroupID, WorkspaceTaskGroup.AutoReference, WorkspaceTaskGroup.StartTime FROM [WorkspaceTaskGroup] WHERE WorkspaceID = " & activeWorkspace.workspaceId
                Set resultSet = dbConnection.OpenResultset(mySQLStatement, rdOpenKeyset)
                While Not resultSet.EOF
                    resultSet.MoveNext
                    GroupRowReturn = GroupRowReturn + 1
                Wend
                
                'if groups do exist
                If GroupRowReturn > 0 Then
                    resultSet.MoveFirst
                    GrouplrArray = resultSet.GetRows(GroupRowReturn)
                    
                    
                    For a = 0 To GroupRowReturn - 1
                    
                        'get group name from table
                        mySQLStatement = "SELECT TaskGroup.TaskGroupName FROM [TaskGroup] WHERE TaskGroupID = " & GrouplrArray(0, a)
                        Set resultSet = dbConnection.OpenResultset(mySQLStatement, rdOpenKeyset)
                        glrArray = resultSet.GetRows(1)
                        name = glrArray(0, 0)
                    
                        Set tempNode = New node_object
    
                        'set up node to add to collection
                        tempNode.StartTime = GrouplrArray(2, a) 'DateAdd("h", GrouplrArray(2, a), activeWorkspace.StartTime)
                        tempNode.nodeName = name
                        tempNode.nodetype = 0
                        tempNode.NodeState = 0
                        tempNode.EndTime = " "
                        tempNode.TaskAutoID = 0
                         tempNode.GroupAutoID = GrouplrArray(1, a)
                        tempNode.nodeKey = name & tempNode.TaskAutoID
                        tempNode.Identification = GrouplrArray(0, a)
                        tempNode.ExpandColapse = True
                        
                        'Add workspace to collection
                        activeWorkspace.ChildNodes.Add tempNode
                        GroupTime = tempNode.StartTime
                        
                        'Get Tasks associated with group
                        mySQLStatement = "SELECT WorkspaceTaskSchedule.TaskID, WorkspaceTaskSchedule.StartTime, WorkspaceTaskSchedule.EndTime, WorkspaceTaskSchedule.AutoReference FROM [WorkspaceTaskSchedule] WHERE GroupReference = " & GrouplrArray(1, a) & " AND WorkspaceID = " & activeWorkspace.workspaceId
                        Set resultSet = dbConnection.OpenResultset(mySQLStatement, rdOpenKeyset)
                        While Not resultSet.EOF
                        resultSet.MoveNext
                        TaskRowReturn = TaskRowReturn + 1
                        Wend
                        If TaskRowReturn > 0 Then
                            resultSet.MoveFirst
                            TasklrArray = resultSet.GetRows(TaskRowReturn)
                
                        'Create Task in Group - Tree values.
                        For j = 0 To TaskRowReturn - 1
                    
                            'determine task name from ID number
                            For l = 0 To TRowReturn - 1
                                If taskArray(0, l) = TasklrArray(0, j) Then
                                 name = taskArray(1, l)
                                End If
                            Next l
                
                            'Setup new node to add to collection
                           Set tempNode = New node_object
                        
                            tempNode.StartTime = Format$(TasklrArray(1, j), "m/d/yyyy h:mm:ss AM/PM")  'DateAdd("h", TasklrArray(1, j), GroupTime)
                            tempNode.nodeName = name
                            tempNode.nodetype = 1
                            tempNode.NodeState = 0
                            tempNode.TaskAutoID = TasklrArray(3, j)
                            tempNode.GroupAutoID = GrouplrArray(1, a)
                            tempNode.EndTime = Format$(TasklrArray(2, j), "m/d/yyyy h:mm:ss AM/PM") 'DateAdd("h", TasklrArray(2, j), tempNode.StartTime)
                            STime = tempNode.StartTime
                            tempNode.nodeKey = name & tempNode.TaskAutoID
                            tempNode.Identification = TasklrArray(0, j)
                            tempNode.ExpandColapse = True
                        
                            'Add Node To tree and collection
                            activeWorkspace.ChildNodes.Add tempNode
                            
                            'Get Procedures associated with Task
                            mySQLStatement = "SELECT WorkspaceProcedures.ProcedureID, WorkspaceProcedures.StartTime, WorkspaceProcedures.EndTime FROM [WorkspaceProcedures] WHERE GroupID = " & GrouplrArray(0, a) & " AND WorkspaceID = " & activeWorkspace.workspaceId & " AND TaskID = " & TasklrArray(0, j) & " AND TaskReference = " & TasklrArray(3, j)
                            Set resultSet = dbConnection.OpenResultset(mySQLStatement, rdOpenKeyset)
                            While Not resultSet.EOF
                                resultSet.MoveNext
                                ProcRowReturn = ProcRowReturn + 1
                            Wend
                            If ProcRowReturn > 0 Then
                                resultSet.MoveFirst
                                ProclrArray = resultSet.GetRows(ProcRowReturn)
                                For k = 0 To ProcRowReturn - 1
                                
                                    For n = 0 To PRowReturn - 1
                                        If ProcArray(0, n) = ProclrArray(0, k) Then
                                            name = ProcArray(1, n)
                                        End If
                                    Next n
                                
                                    Set tempNode = New node_object
     
                                   tempNode.StartTime = Format$(ProclrArray(1, k), "m/d/yyyy h:mm:ss AM/PM")
                                    tempNode.nodeName = name
                                    tempNode.nodetype = 2
                                    tempNode.NodeState = 0
                                    tempNode.TaskAutoID = TasklrArray(3, j)
                                    tempNode.GroupAutoID = GrouplrArray(1, a)
                                    tempNode.EndTime = Format$(ProclrArray(2, k), "m/d/yyyy h:mm:ss AM/PM")
                                    tempNode.nodeKey = name & tempNode.TaskAutoID
                                    tempNode.Identification = ProclrArray(0, k)
                                    tempNode.ExpandColapse = True
                                
                                    'Add Node To collection
                                    activeWorkspace.ChildNodes.Add tempNode
                                
                                Next k
                            End If
                            ProcRowReturn = 0
                            
                        Next j
                        TaskRowReturn = 0
                        End If
                    Next a
                    GroupRowReturn = 0
                    
                    End If
                    
    '''''TASKS''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
                'Get Tasks associated individually with workspace
                mySQLStatement = "SELECT WorkspaceTaskSchedule.TaskID, WorkspaceTaskSchedule.StartTime, WorkspaceTaskSchedule.EndTime, WorkspaceTaskSchedule.AutoReference FROM [WorkspaceTaskSchedule] WHERE GroupID = 0 AND WorkspaceID = " & activeWorkspace.workspaceId
                Set resultSet = dbConnection.OpenResultset(mySQLStatement, rdOpenKeyset)
                While Not resultSet.EOF
                    resultSet.MoveNext
                    TaskRowReturn = TaskRowReturn + 1
                Wend
                If TaskRowReturn > 0 Then
                    resultSet.MoveFirst
                    TasklrArray = resultSet.GetRows(TaskRowReturn)
                    
                'Create Task in Workspace - Tree values.
                    For j = 0 To TaskRowReturn - 1
                        
                        For l = 0 To TRowReturn - 1
                            If taskArray(0, l) = TasklrArray(0, j) Then
                                name = taskArray(1, l)
                            End If
                        Next l
                
                       Set tempNode = New node_object
                        'setup node to add to collection
                        tempNode.StartTime = Format$(TasklrArray(1, j), "m/d/yyyy h:mm:ss AM/PM") 'DateAdd("h", TasklrArray(1, j), activeWorkspace.StartTime)
                        tempNode.nodeName = name
                        tempNode.nodetype = 1
                        tempNode.NodeState = 0
                        tempNode.TaskAutoID = TasklrArray(3, j)
                        tempNode.GroupAutoID = 0
                        tempNode.EndTime = Format$(TasklrArray(2, j), "m/d/yyyy h:mm:ss AM/PM") 'DateAdd("h", TasklrArray(2, j), tempNode.StartTime)
                        STime = tempNode.StartTime
                        tempNode.nodeKey = name & tempNode.TaskAutoID
                        tempNode.Identification = TasklrArray(0, j)
                        tempNode.ExpandColapse = True
                        
                        'Add Node To tree
                        activeWorkspace.ChildNodes.Add tempNode
    
                        'Get Procedures associated with Task
                        mySQLStatement = "SELECT WorkspaceProcedures.ProcedureID, WorkspaceProcedures.StartTime, WorkspaceProcedures.EndTime FROM [WorkspaceProcedures] WHERE GroupID = 0 AND WorkspaceID = " & activeWorkspace.workspaceId & " AND TaskID = " & TasklrArray(0, j) & " AND TaskReference = " & TasklrArray(3, j)
                        Set resultSet = dbConnection.OpenResultset(mySQLStatement, rdOpenKeyset)
                        While Not resultSet.EOF
                            resultSet.MoveNext
                            ProcRowReturn = ProcRowReturn + 1
                        Wend
                        If ProcRowReturn > 0 Then
                            resultSet.MoveFirst
                            ProclrArray = resultSet.GetRows(ProcRowReturn)
                            For k = 0 To ProcRowReturn - 1
                                
                                'get procedure name from procedure ID
                                For n = 0 To PRowReturn - 1
                                    If ProcArray(0, n) = ProclrArray(0, k) Then
                                        name = ProcArray(1, n)
                                    End If
                                Next n
     
                                Set tempNode = New node_object
                                
                                'setup node to add to collection
                                tempNode.StartTime = Format$(ProclrArray(1, k), "m/d/yyyy h:mm:ss AM/PM") 'DateAdd("h", ProclrArray(1, k), STime)
                                tempNode.nodeName = name
                                tempNode.nodetype = 2
                                tempNode.NodeState = 0
    
                                tempNode.TaskAutoID = TasklrArray(3, j)
                                tempNode.GroupAutoID = 0
                                tempNode.EndTime = Format$(ProclrArray(2, k), "m/d/yyyy h:mm:ss AM/PM") 'DateAdd("h", ProclrArray(2, k), tempNode.StartTime)
                                tempNode.nodeKey = name & tempNode.TaskAutoID
                                tempNode.Identification = ProclrArray(0, k)
                                tempNode.ExpandColapse = True
                                
                                'Add Node To workspace
                                activeWorkspace.ChildNodes.Add tempNode
    
                            Next k
                        End If
                        ProcRowReturn = 0
                    Next j
                        
                End If
                TaskRowReturn = 0
            End If
        Next i
    End If

    If wsOpened = 0 Then
        MDIMain.active = False
        Exit Sub
    End If
    
    'load data so it appears in the objects
    LoadData activeWorkspace
End Sub
'Function/Subroutine:LoadData
'Purpose: This function gets passed the active workspace. Using it's
'Data the function populates the tree and gantt chart
Sub LoadData(activeWorkspace As Workspace)
    Dim tabIndex As Integer
    Dim temp As Integer
    Dim i As Integer
    Dim tempString As String
    Dim CurrentIndex As Integer
    Dim treeNode As Long
    Dim tempInt As Integer
    Dim RowReturn As Integer
    Dim resultSet As rdoResultset
    Dim mySQLStatement As String
    Dim rArray As Variant
    Dim tempString1 As Date
    Dim tempInt2 As Integer
    
    'used to assign parent nodes in the tree
    Dim parentIndex As Integer
    Dim groupindex As Integer
    
    MDIMain.Tree.ColumnText(0) = activeWorkspace.WorkspaceName & " - " & activeWorkspace.StartTime & " through " & activeWorkspace.EndTime
    
    'delete any previous data
    MDIMain.GanttChart.ClearAllRows
    MDIMain.GanttChart.DeleteAllModePeriods
    
    'Set GanttChart times to the active workspace start & end time
    MDIMain.GanttChart.ChartStartTime = activeWorkspace.StartTime
    MDIMain.GanttChart.ChartEndTime = activeWorkspace.EndTime
    
    MDIMain.GanttChart1.ChartStartTime = activeWorkspace.StartTime
    MDIMain.GanttChart1.ChartEndTime = activeWorkspace.EndTime
    
    MDIMain.Tree.Clear
    
    'Create Top Node
    treeNode = MDIMain.Tree.InsertItem(CurrentIndex, activeWorkspace.WorkspaceName)
    MDIMain.Tree.ListIndex = treeNode
    Set MDIMain.Tree.ItemPicture(treeNode) = MDIMain.nodePict5
    CurrentIndex = MDIMain.Tree.ListIndex + 1 'CurrentIndex + 1
    
    'For each item in the active workspaces collection
    For i = 1 To activeWorkspace.ChildNodes.Count
        'Add task that is not part of a group
        If activeWorkspace.ChildNodes.Item(i).nodetype = 1 And activeWorkspace.ChildNodes.Item(i).GroupAutoID = 0 Then
           treeNode = MDIMain.Tree.InsertItem(CurrentIndex, activeWorkspace.ChildNodes.Item(i).nodeName)
           MDIMain.Tree.ItemLevel(treeNode) = 1
           Set MDIMain.Tree.ItemPicture(treeNode) = MDIMain.nodePict2
           MDIMain.Tree.CellText(treeNode, 1) = activeWorkspace.ChildNodes.Item(i).StartTime
           MDIMain.Tree.CellText(treeNode, 2) = activeWorkspace.ChildNodes.Item(i).EndTime
           MDIMain.Tree.CellText(treeNode, 3) = Str(DateDiff("h", activeWorkspace.ChildNodes.Item(i).StartTime, activeWorkspace.ChildNodes.Item(i).EndTime)) & " Hour(s)"
           tempInt = Int(treeNode)
           activeWorkspace.ChildNodes.Item(i).DataRow = tempInt
           'MDIMain.GanttChart.AddRow tempInt, activeWorkspace.ChildNodes.Item(i).StartTime, activeWorkspace.ChildNodes.Item(i).EndTime, RGB(250, 50, 50), , activeWorkspace.ChildNodes.Item(i).nodeName
           activeWorkspace.ChildNodes.Item(i).parentNode = 0
           parentIndex = tempInt
        End If
        'Add task that is part of a group
        If activeWorkspace.ChildNodes.Item(i).nodetype = 1 And activeWorkspace.ChildNodes.Item(i).GroupAutoID <> 0 Then
            treeNode = MDIMain.Tree.InsertItem(CurrentIndex, activeWorkspace.ChildNodes.Item(i).nodeName)
            MDIMain.Tree.ItemLevel(treeNode) = 2
            Set MDIMain.Tree.ItemPicture(treeNode) = MDIMain.nodePict2
            MDIMain.Tree.CellText(treeNode, 1) = activeWorkspace.ChildNodes.Item(i).StartTime
            MDIMain.Tree.CellText(treeNode, 2) = activeWorkspace.ChildNodes.Item(i).EndTime
            MDIMain.Tree.CellText(treeNode, 3) = Str(DateDiff("h", activeWorkspace.ChildNodes.Item(i).StartTime, activeWorkspace.ChildNodes.Item(i).EndTime)) & " Hour(s)"
            tempInt = Int(treeNode)
            activeWorkspace.ChildNodes.Item(i).DataRow = tempInt
            'MDIMain.GanttChart.AddRow tempInt, activeWorkspace.ChildNodes.Item(i).StartTime, activeWorkspace.ChildNodes.Item(i).EndTime, RGB(250, 50, 50), , activeWorkspace.ChildNodes.Item(i).nodeName
            activeWorkspace.ChildNodes.Item(i).parentNode = groupindex
            parentIndex = tempInt
        End If
        'add procedure that is not part of a group
        If activeWorkspace.ChildNodes.Item(i).nodetype = 2 And activeWorkspace.ChildNodes.Item(i).GroupAutoID = 0 Then
            treeNode = MDIMain.Tree.InsertItem(CurrentIndex, activeWorkspace.ChildNodes.Item(i).nodeName)
            MDIMain.Tree.ItemLevel(treeNode) = 2
            Set MDIMain.Tree.ItemPicture(treeNode) = MDIMain.nodePict3
            MDIMain.Tree.CellText(treeNode, 1) = activeWorkspace.ChildNodes.Item(i).StartTime
            MDIMain.Tree.CellText(treeNode, 2) = activeWorkspace.ChildNodes.Item(i).EndTime
            MDIMain.Tree.CellText(treeNode, 3) = Str(DateDiff("h", activeWorkspace.ChildNodes.Item(i).StartTime, activeWorkspace.ChildNodes.Item(i).EndTime)) & " Hour(s)"
            tempInt = Int(treeNode)
            activeWorkspace.ChildNodes.Item(i).DataRow = tempInt
            'MDIMain.GanttChart.AddRow tempInt, activeWorkspace.ChildNodes.Item(i).StartTime, activeWorkspace.ChildNodes.Item(i).EndTime, RGB(50, 50, 250), , activeWorkspace.ChildNodes.Item(i).nodeName
            activeWorkspace.ChildNodes.Item(i).parentNode = parentIndex
        End If
        'Add procedure that is part of a task group
        If activeWorkspace.ChildNodes.Item(i).nodetype = 2 And activeWorkspace.ChildNodes.Item(i).GroupAutoID <> 0 Then
            treeNode = MDIMain.Tree.InsertItem(CurrentIndex, activeWorkspace.ChildNodes.Item(i).nodeName)
            MDIMain.Tree.ItemLevel(treeNode) = 3
            Set MDIMain.Tree.ItemPicture(treeNode) = MDIMain.nodePict3
            MDIMain.Tree.CellText(treeNode, 1) = activeWorkspace.ChildNodes.Item(i).StartTime
            MDIMain.Tree.CellText(treeNode, 2) = activeWorkspace.ChildNodes.Item(i).EndTime
            MDIMain.Tree.CellText(treeNode, 3) = Str(DateDiff("h", activeWorkspace.ChildNodes.Item(i).StartTime, activeWorkspace.ChildNodes.Item(i).EndTime)) & " Hour(s)"
            tempInt = Int(treeNode)
            activeWorkspace.ChildNodes.Item(i).DataRow = tempInt
            'MDIMain.GanttChart.AddRow tempInt, activeWorkspace.ChildNodes.Item(i).StartTime, activeWorkspace.ChildNodes.Item(i).EndTime, RGB(50, 50, 250), , activeWorkspace.ChildNodes.Item(i).nodeName
            activeWorkspace.ChildNodes.Item(i).parentNode = parentIndex
            End If
        'add group node
        If activeWorkspace.ChildNodes.Item(i).nodetype = 0 Then
           treeNode = MDIMain.Tree.InsertItem(CurrentIndex, activeWorkspace.ChildNodes.Item(i).nodeName)
            MDIMain.Tree.ItemLevel(treeNode) = 1
            Set MDIMain.Tree.ItemPicture(treeNode) = MDIMain.nodePict1
            tempInt = Int(treeNode)
            'MDIMain.GanttChart.AddBlankRow tempInt
            activeWorkspace.ChildNodes.Item(i).DataRow = treeNode
            activeWorkspace.ChildNodes.Item(i).parentNode = 0
            groupindex = tempInt
        End If
        'add mode node
        If activeWorkspace.ChildNodes.Item(i).nodetype = 3 Then
           treeNode = MDIMain.Tree.InsertItem(CurrentIndex, activeWorkspace.ChildNodes.Item(i).nodeName)
            MDIMain.Tree.ItemLevel(treeNode) = 1
            Set MDIMain.Tree.ItemPicture(treeNode) = MDIMain.nodePict4
            activeWorkspace.ChildNodes.Item(i).DataRow = treeNode
            activeWorkspace.ChildNodes.Item(i).parentNode = 0
        End If
        CurrentIndex = CurrentIndex + 1
        
    Next i
    
    For i = 1 To activeWorkspace.ChildNodes.Count
        'set expanded or colapsed property of a node
        If activeWorkspace.ChildNodes.Item(i).ExpandColapse = True Then
            MDIMain.Tree.Expand activeWorkspace.ChildNodes.Item(i).DataRow, True, True
        Else
            MDIMain.Tree.Collapse activeWorkspace.ChildNodes.Item(i).DataRow, False
        End If
    Next i
    
    'update ganttchart
    For i = 0 To MDIMain.Tree.listCount - 1
        If MDIMain.Tree.ItemShown(i) Then
            'Place in gant chart
            If MDIMain.Tree.ItemPicture(i) = MDIMain.nodePict2 Then 'task
                MDIMain.GanttChart.AddRow i, MDIMain.Tree.CellText(i, 1), MDIMain.Tree.CellText(i, 2), TaskColor, , MDIMain.Tree.CellText(i, 0)
            End If
               
            If MDIMain.Tree.ItemPicture(i) = MDIMain.nodePict3 Then 'procedure
                MDIMain.GanttChart.AddRow i, MDIMain.Tree.CellText(i, 1), MDIMain.Tree.CellText(i, 2), ProcColor, , MDIMain.Tree.CellText(i, 0)
            End If
                
            If MDIMain.Tree.ItemPicture(i) = MDIMain.nodePict1 Then 'group
                MDIMain.GanttChart.AddBlankRow (i)
            End If
                
        End If
    Next i
    
    'Add modes to gantt chart
    RowReturn = 0
     mySQLStatement = "SELECT ModeID, StartTime, ModeName FROM [WorkspaceMode] WHERE WorkspaceID = " & activeWorkspace.workspaceId & " ORDER BY StartTime"
     Set resultSet = dbConnection.OpenResultset(mySQLStatement, rdOpenKeyset)
    While Not resultSet.EOF
        resultSet.MoveNext
        RowReturn = RowReturn + 1
    Wend
    If RowReturn > 0 Then
        resultSet.MoveFirst
        rArray = resultSet.GetRows(RowReturn)
        
        'generate color for mode - 250 must be divisible by addition number
       Dim ModeColor As Integer
        For i = 0 To RowReturn - 1
        
            tempString1 = rArray(1, i)
            tempInt2 = rArray(0, i)
            Dim nameString As String
            nameString = rArray(2, i)
            MDIMain.GanttChart.AddModePeriod tempString1, tempInt2, ModeList(tempInt2).ModeColor, nameString
        Next i
     End If
    
    MDIMain.GanttChart.RedrawGanttChart
    
    'Tree value must be calculated to make scroll bars work correctly
    MDIMain.Tree.RecalcHorizontalExtent
End Sub
'Function/Subroutine:ooslistControl
'Purpose:Called to update the ooslist objects
Sub ooslistControl(WS As Workspace)
'
    Dim treeNode As Long
    Dim name As String
    Dim CurrentIndex As Long
    Dim mySQL As String
    Dim resultSet As rdoResultset
    Dim rArray As Variant
    Dim RowReturn As Integer
    Dim i As Integer
    
    'clear existing data
    MDIMain.OOSTree.Clear
    MDIMain.GanttChart1.ClearAllRows
    MDIMain.GanttChart1.DeleteAllModePeriods
    name = WS.WorkspaceName & " (Components)"
    
    'Create Top Node & risk level bar
    treeNode = MDIMain.OOSTree.InsertItem(CurrentIndex, name)
    MDIMain.OOSTree.ListIndex = treeNode
    Set MDIMain.OOSTree.ItemPicture(treeNode) = MDIMain.nodePict5
    CurrentIndex = MDIMain.OOSTree.ListIndex + 1
    treeNode = MDIMain.OOSTree.InsertItem(CurrentIndex, "Risk Level")
    MDIMain.OOSTree.ListIndex = treeNode
    MDIMain.OOSTree.ItemLevel(treeNode) = 1
    Set MDIMain.OOSTree.ItemPicture(treeNode) = MDIMain.nodePict7
    CurrentIndex = MDIMain.OOSTree.ListIndex + 1
    
    'Get OOS components for workspace from table
    mySQL = "SELECT ComponentID, ComponentName, StartTime, EndTime FROM " & _
            "[OOSList] WHERE WorkspaceID = " & WS.workspaceId
    Set resultSet = dbConnection.OpenResultset(mySQL, rdOpenKeyset)
    
    While Not resultSet.EOF
        resultSet.MoveNext
        RowReturn = RowReturn + 1
    Wend
    
    If RowReturn > 0 Then
        resultSet.MoveFirst
        rArray = resultSet.GetRows(RowReturn)
        
        'put data into tree and ganttchart1
        For i = 0 To RowReturn - 1
            treeNode = MDIMain.OOSTree.InsertItem(CurrentIndex, rArray(1, i))
            MDIMain.OOSTree.ItemLevel(treeNode) = 1
            Set MDIMain.OOSTree.ItemPicture(treeNode) = MDIMain.nodePict6
            MDIMain.OOSTree.CellText(treeNode, 1) = rArray(2, i)
            MDIMain.OOSTree.CellText(treeNode, 2) = rArray(3, i)
            MDIMain.OOSTree.ListIndex = treeNode
            CurrentIndex = MDIMain.OOSTree.ListIndex + 1
            Dim temp As Integer
            temp = treeNode
            Dim st As Date
            st = rArray(2, i)
            Dim et As Date
            et = rArray(3, i)
            name = rArray(1, i)
            MDIMain.GanttChart1.AddRow temp, st, et, CompColor, , name
        Next i
    End If
    
    'Add risk periods to mode bar
    RowReturn = 0
    MDIMain.GanttChart1.AddModePeriod WS.StartTime, 0, OKColor, "Low Risk"
    
    mySQL = "SELECT PeriodTime, RiskValue FROM [RiskPeriods] WHERE WorkspaceID = " & WS.workspaceId
    Set resultSet = dbConnection.OpenResultset(mySQL, rdOpenKeyset)
    
    While Not resultSet.EOF
        resultSet.MoveNext
        RowReturn = RowReturn + 1
    Wend
    
    Dim tempDate As Date
    If RowReturn > 0 Then
    
        resultSet.MoveFirst
        rArray = resultSet.GetRows(RowReturn)
        
        For i = 0 To RowReturn - 1
            tempDate = rArray(0, i)
            If rArray(1, i) < MDIMain.MediumRisk Then
                MDIMain.GanttChart1.AddModePeriod tempDate, 0, OKColor, "Low Risk"
            ElseIf rArray(1, i) < MDIMain.HighRisk Then
                MDIMain.GanttChart1.AddModePeriod tempDate, -1, CautionColor, "Medium Risk"
            Else
                MDIMain.GanttChart1.AddModePeriod tempDate, -2, DangerColor, "High Risk"
            End If
        Next i
    End If
    
    MDIMain.GanttChart1.RedrawGanttChart
     'Tree value must be calculated to make scroll bars work correctly
    MDIMain.OOSTree.RecalcHorizontalExtent
    MDIMain.OOSTree.TopIndex = 0
    MDIMain.GanttChart1.SetVerticalScrollBar (1)
    
End Sub
'Function: open_workspace
'Purpose: open an existing workspace, for the workspace selected add
'all groups, tasks and procedurs.
Sub open_workspace(WSID As Integer)
'
    Dim RowReturn As Integer
    Dim j As Integer
    Dim k As Integer
    Dim l As Integer
    Dim n As Integer
    Dim a As Integer
    Dim rArray As Variant
    Dim lrArray As Variant
    Dim mySQLStatement As String
    Dim resultSet As rdoResultset
    Dim ProcRowReturn As Integer
    Dim TaskRowReturn As Integer
    Dim PRowReturn As Integer
    Dim TRowReturn As Integer
    Dim TasklrArray As Variant
    Dim ProclrArray As Variant
    Dim temp As Integer
    Dim STime As String
    Dim GIndex As Integer
    Dim Duration As Integer
    Dim GrouplrArray As Variant
    Dim GroupRowReturn As Integer
    Dim glrArray As Variant
    Dim name As String
    Dim GroupTime As String
    
    'Create a table to hold procedure data so It dosent have to be returned from the table more than once.
    mySQLStatement = "SELECT Procedure.ProcedureID, Procedure.ProcedureName FROM [Procedure]"
    Set resultSet = dbConnection.OpenResultset(mySQLStatement, rdOpenKeyset)
    
    While Not resultSet.EOF
        resultSet.MoveNext
        PRowReturn = PRowReturn + 1
    Wend
    resultSet.MoveFirst
    ProcArray = resultSet.GetRows(PRowReturn)
    
    
    'Create a table to hold task data so It dosent have to be returned from the table more than once.
    mySQLStatement = "SELECT Task.TaskID, Task.TaskName FROM [Task]"
    Set resultSet = dbConnection.OpenResultset(mySQLStatement, rdOpenKeyset)
    
    While Not resultSet.EOF
        resultSet.MoveNext
        TRowReturn = TRowReturn + 1
    Wend
    resultSet.MoveFirst
    taskArray = resultSet.GetRows(TRowReturn)
    
    'Get Workspace Information
     mySQLStatement = "SELECT WorkspaceID, WorkspaceName, UserID, AccessType, StartTime, EndTime, CreateDate, InitialModeID FROM [Workspace] WHERE WorkspaceID =" & WSID
     Set resultSet = dbConnection.OpenResultset(mySQLStatement, rdOpenKeyset)
     lrArray = resultSet.GetRows(1)
     Set activeWorkspace = MDIMain.Active_Workspace
     
     'Set Workspace Data and create new active workspace
     With activeWorkspace
         .workspaceId = lrArray(0, 0)
         'If lrArray(3, 0) = 1 Then
         '    .modifyAccess = True
         'Else
         '   .modifyAccess = False
         'End If
         .creatorId = lrArray(2, 0)
         .StartTime = lrArray(4, 0)
         .EndTime = lrArray(5, 0)
         .dateLastModified = Now
         .dateCreated = lrArray(6, 0)
         .WorkspaceName = lrArray(1, 0) '"Workspace " & activeWorkspaceIndex
         .InitialModeID = lrArray(7, 0)
    End With
            
    MDIMain.Active_Workspace_Add activeWorkspace
                 
    If (MDIMain.Existing_Workspaces = 1) Then
         Set activeWorkspace.tabCtrl = MDIMain.TabStrip1.Tabs(1)
    Else
        Set activeWorkspace.tabCtrl = MDIMain.TabStrip1.Tabs.Add()
    End If
    
    activeWorkspace.tabCtrl.Caption = activeWorkspace.WorkspaceName '"Workspace " & MDIMain.activeWorkspaceIndex
    activeWorkspace.tabCtrl.Selected = True
'''''MODE''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    Dim tempNode As node_object
    Set tempNode = New node_object
    
    tempNode.StartTime = activeWorkspace.StartTime
    tempNode.nodeName = "MODE"
    tempNode.nodetype = 3
    tempNode.NodeState = 0
    tempNode.EndTime = activeWorkspace.EndTime
    tempNode.TaskAutoID = 0
    tempNode.GroupAutoID = 0
    activeWorkspace.ChildNodes.Add tempNode
            
'''''GROUPS''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    'Get Groups associated with workspace
    mySQLStatement = "SELECT WorkspaceTaskGroup.TaskGroupID, WorkspaceTaskGroup.AutoReference, WorkspaceTaskGroup.StartTime FROM [WorkspaceTaskGroup] WHERE WorkspaceID = " & activeWorkspace.workspaceId
    Set resultSet = dbConnection.OpenResultset(mySQLStatement, rdOpenKeyset)
    While Not resultSet.EOF
    resultSet.MoveNext
    GroupRowReturn = GroupRowReturn + 1
    Wend
    
    If GroupRowReturn > 0 Then
    resultSet.MoveFirst
    GrouplrArray = resultSet.GetRows(GroupRowReturn)
    
    
    For a = 0 To GroupRowReturn - 1
    
        'get group name from table
        mySQLStatement = "SELECT TaskGroup.TaskGroupName FROM [TaskGroup] WHERE TaskGroupID = " & GrouplrArray(0, a)
        Set resultSet = dbConnection.OpenResultset(mySQLStatement, rdOpenKeyset)
        glrArray = resultSet.GetRows(1)
        name = glrArray(0, 0)
    
        Set tempNode = New node_object
    
        tempNode.StartTime = GrouplrArray(2, a) 'DateAdd("h", GrouplrArray(2, a), activeWorkspace.StartTime)
        tempNode.nodeName = name
        tempNode.nodetype = 0
        tempNode.NodeState = 0
        tempNode.EndTime = " "
        tempNode.TaskAutoID = 0
         tempNode.GroupAutoID = GrouplrArray(1, a)
        tempNode.nodeKey = name & tempNode.TaskAutoID
        activeWorkspace.ChildNodes.Add tempNode
        GroupTime = tempNode.StartTime
        tempNode.Identification = GrouplrArray(0, a)
        
        'Get Tasks associated with group
        mySQLStatement = "SELECT WorkspaceTaskSchedule.TaskID, WorkspaceTaskSchedule.StartTime, WorkspaceTaskSchedule.EndTime, WorkspaceTaskSchedule.AutoReference FROM [WorkspaceTaskSchedule] WHERE GroupReference = " & GrouplrArray(1, a) & " AND WorkspaceID = " & activeWorkspace.workspaceId
        Set resultSet = dbConnection.OpenResultset(mySQLStatement, rdOpenKeyset)
        While Not resultSet.EOF
        resultSet.MoveNext
        TaskRowReturn = TaskRowReturn + 1
        Wend
        If TaskRowReturn > 0 Then
            resultSet.MoveFirst
            TasklrArray = resultSet.GetRows(TaskRowReturn)
    
        'Create Task in Group - Tree values.
        For j = 0 To TaskRowReturn - 1
    
            For l = 0 To TRowReturn - 1
                If taskArray(0, l) = TasklrArray(0, j) Then
                 name = taskArray(1, l)
                End If
            Next l
    
           Set tempNode = New node_object
        
            tempNode.StartTime = TasklrArray(1, j) 'DateAdd("h", TasklrArray(1, j), GroupTime)
            tempNode.nodeName = name
            tempNode.nodetype = 1
            tempNode.NodeState = 0
            tempNode.TaskAutoID = TasklrArray(3, j)
            tempNode.GroupAutoID = GrouplrArray(1, a)
            tempNode.EndTime = TasklrArray(2, j) 'DateAdd("h", TasklrArray(2, j), tempNode.StartTime)
            STime = tempNode.StartTime
            tempNode.nodeKey = name & tempNode.TaskAutoID
            tempNode.Identification = TasklrArray(0, j)
        
            'Add Node To tree
            activeWorkspace.ChildNodes.Add tempNode
            
            'Get Procedures associated with Task
            mySQLStatement = "SELECT WorkspaceProcedures.ProcedureID, WorkspaceProcedures.StartTime, WorkspaceProcedures.EndTime FROM [WorkspaceProcedures] WHERE GroupID = " & GrouplrArray(0, a) & " AND WorkspaceID = " & activeWorkspace.workspaceId & " AND TaskID = " & TasklrArray(0, j) & " AND TaskReference = " & TasklrArray(3, j)
            Set resultSet = dbConnection.OpenResultset(mySQLStatement, rdOpenKeyset)
            While Not resultSet.EOF
                resultSet.MoveNext
                ProcRowReturn = ProcRowReturn + 1
            Wend
            If ProcRowReturn > 0 Then
                resultSet.MoveFirst
                ProclrArray = resultSet.GetRows(ProcRowReturn)
                For k = 0 To ProcRowReturn - 1
                    'Dim pParentNode As PVBranch
                    'Dim pChildNode As PVBranch
                
                    For n = 0 To PRowReturn - 1
                        If ProcArray(0, n) = ProclrArray(0, k) Then
                            name = ProcArray(1, n)
                        End If
                    Next n
                
                    Set tempNode = New node_object
    
                   tempNode.StartTime = ProclrArray(1, k) 'DateAdd("h", ProclrArray(1, k), STime)
                    tempNode.nodeName = name
                    tempNode.nodetype = 2
                    tempNode.NodeState = 0
                    tempNode.TaskAutoID = TasklrArray(3, j)
                    tempNode.GroupAutoID = GrouplrArray(1, a)
                    tempNode.EndTime = ProclrArray(2, k) 'DateAdd("h", ProclrArray(2, k), tempNode.StartTime)
                    'STime = tempNode.StartTime
                    tempNode.nodeKey = name & tempNode.TaskAutoID
                    tempNode.Identification = ProclrArray(0, k)
                
                    'Add Node To tree
                    activeWorkspace.ChildNodes.Add tempNode
                
                Next k
            End If
            ProcRowReturn = 0
            
        Next j
        TaskRowReturn = 0
        End If
    Next a
    GroupRowReturn = 0
    
    End If
                
'''''TASKS''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    'Get Tasks associated with workspace
    mySQLStatement = "SELECT WorkspaceTaskSchedule.TaskID, WorkspaceTaskSchedule.StartTime, WorkspaceTaskSchedule.EndTime, WorkspaceTaskSchedule.AutoReference FROM [WorkspaceTaskSchedule] WHERE GroupID = 0 AND WorkspaceID = " & activeWorkspace.workspaceId
    Set resultSet = dbConnection.OpenResultset(mySQLStatement, rdOpenKeyset)
    While Not resultSet.EOF
        resultSet.MoveNext
        TaskRowReturn = TaskRowReturn + 1
    Wend
    If TaskRowReturn > 0 Then
        resultSet.MoveFirst
        TasklrArray = resultSet.GetRows(TaskRowReturn)
        
    'Create Task in Workspace - Tree values.
        For j = 0 To TaskRowReturn - 1
            
            For l = 0 To TRowReturn - 1
                If taskArray(0, l) = TasklrArray(0, j) Then
                    name = taskArray(1, l)
                End If
            Next l
    
           Set tempNode = New node_object
            
            tempNode.StartTime = TasklrArray(1, j) 'DateAdd("h", TasklrArray(1, j), activeWorkspace.StartTime)
            tempNode.nodeName = name
            tempNode.nodetype = 1
            tempNode.NodeState = 0
            tempNode.TaskAutoID = TasklrArray(3, j)
            tempNode.GroupAutoID = 0
            tempNode.EndTime = TasklrArray(2, j) 'DateAdd("h", TasklrArray(2, j), tempNode.StartTime)
            STime = tempNode.StartTime
            tempNode.nodeKey = name & tempNode.TaskAutoID
            tempNode.Identification = TasklrArray(0, j)
            
            'Add Node To tree
            activeWorkspace.ChildNodes.Add tempNode

            'Get Procedures associated with Task
            mySQLStatement = "SELECT WorkspaceProcedures.ProcedureID, WorkspaceProcedures.StartTime, WorkspaceProcedures.EndTime FROM [WorkspaceProcedures] WHERE GroupID = 0 AND WorkspaceID = " & activeWorkspace.workspaceId & " AND TaskID = " & TasklrArray(0, j) & " AND TaskReference = " & TasklrArray(3, j)
            Set resultSet = dbConnection.OpenResultset(mySQLStatement, rdOpenKeyset)
            While Not resultSet.EOF
                resultSet.MoveNext
                ProcRowReturn = ProcRowReturn + 1
            Wend
            If ProcRowReturn > 0 Then
                resultSet.MoveFirst
                ProclrArray = resultSet.GetRows(ProcRowReturn)
                For k = 0 To ProcRowReturn - 1
                    
                    For n = 0 To PRowReturn - 1
                        If ProcArray(0, n) = ProclrArray(0, k) Then
                            name = ProcArray(1, n)
                        End If
                    Next n

                    Set tempNode = New node_object
                    
                    tempNode.StartTime = ProclrArray(1, k)
                    tempNode.nodeName = name
                    tempNode.nodetype = 2
                    tempNode.NodeState = 0

                    tempNode.TaskAutoID = TasklrArray(3, j)
                    tempNode.GroupAutoID = 0
                    tempNode.EndTime = ProclrArray(2, k)
                    tempNode.nodeKey = name & tempNode.TaskAutoID
                    tempNode.Identification = ProclrArray(0, k)
                    
                    'Add Node To tree
                    activeWorkspace.ChildNodes.Add tempNode
                    
                    

                Next k
            End If
            ProcRowReturn = 0
        Next j
            
    End If
    TaskRowReturn = 0
            
    mySQLStatement = "INSERT INTO [OpenWorkspaces] (WorkspaceID, UserID) VALUES ( " & WSID & ", " & userID & ")"
    Set resultSet = dbConnection.OpenResultset(mySQLStatement)
    
    'fill in tree and gantt charts
    LoadData activeWorkspace
    ooslistControl activeWorkspace
    
End Sub
'Function close_workspace
'purpose: close a workspace the user has open. dosent allow the last
'open workspace to be closed.
Sub close_workspace(WS As Workspace)
'
    Dim deletetab As Integer
    Dim WSID As Integer
    Dim mySQLStatement As String
    Dim resultSet As rdoResultset
    
    If MDIMain.Existing_Workspaces > 1 Then
        deletetab = MDIMain.TabStrip1.SelectedItem.Index
        WSID = WS.workspaceId
    
        'remove tabstrip
        MDIMain.TabStrip1.Tabs.Remove deletetab
    
        'Remove from open workspaces tabel
        mySQLStatement = "DELETE FROM [OpenWorkspaces] WHERE WorkspaceID = " & WSID & " AND UserID = " & userID
        Set resultSet = dbConnection.OpenResultset(mySQLStatement)
    
        'remove WS from collection
        MDIMain.Active_Workspace_Remove WS
    Else
        MsgBox "Can't Close Last Open Workspace", vbInformation
        
    End If
    
End Sub
