VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "ProcessManager"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit
Public LastError As Integer

Private Sub CheckRiskPeriodCreate(wDate As Date, workspaceId As Integer)
    Dim mySQLStatement As String
    Dim resultSet As rdoResultset
    mySQLStatement = "SELECT * FROM [RiskPeriods] WHERE PeriodTime = " & SQLDate(wDate)
    Set resultSet = dbConnection.OpenResultset(mySQLStatement)
    If (resultSet.EOF) Then
        mySQLStatement = "SELECT ModeID, StartTime FROM [WorkspaceMode] WHERE WorkspaceID = " & _
            workspaceId & " AND StartTime <= " & SQLDate(wDate) & " ORDER BY StartTime DESC"
        Set resultSet = dbConnection.OpenResultset(mySQLStatement)
        If Not resultSet.EOF Then
            Dim rArray As Variant, modeID As Integer
            rArray = resultSet.GetRows(1)
            modeID = rArray(0, 0)
            mySQLStatement = "INSERT INTO RiskPeriods VALUES (" & _
            workspaceId & ", " & SQLDate(wDate) & ", Yes, 0," & modeID & ")"
            dbConnection.Execute (mySQLStatement)
        End If
    End If
End Sub

Private Sub CheckRiskPeriodDelete(wDate As Date, workspaceId As Integer)
    ' check to see if there are any procedures at this time
    Dim mySQLStatement As String, resultSet As rdoResultset
    
    mySQLStatement = "SELECT StartTime FROM WorkspaceProcedures" & _
        " WHERE WorkspaceID = " & workspaceId & _
        " AND (StartTime = " & SQLDate(wDate) & _
        " OR EndTime = " & SQLDate(wDate) & ")"
    Set resultSet = dbConnection.OpenResultset(mySQLStatement)
    If (resultSet.EOF) Then
        ' there might be an OOS item at this time
        mySQLStatement = "SELECT StartTime FROM OOSList" & _
            " WHERE WorkspaceID = " & workspaceId & _
            " AND (StartTime = " & SQLDate(wDate) & _
            " OR EndTime = " & SQLDate(wDate) & ")"
        Set resultSet = dbConnection.OpenResultset(mySQLStatement)
        If (resultSet.EOF) Then
            ' there might be a mode
            mySQLStatement = "SELECT StartTime FROM WorkspaceMode" & _
                " WHERE WorkspaceID = " & workspaceId & _
                " AND StartTime = " & SQLDate(wDate)
            Set resultSet = dbConnection.OpenResultset(mySQLStatement)
            If (resultSet.EOF) Then
                ' delete the risk period
                mySQLStatement = "DELETE FROM RiskPeriods WHERE WorkspaceID = " & _
                workspaceId & " AND PeriodTime = " & SQLDate(wDate)
                dbConnection.Execute (mySQLStatement)
            End If
        End If
    End If
End Sub

' error codes -
' 1 - procedure existed at specified time

' function AddProcedure
' return value true - procedure successfully added
' return value false - procedure could not be added because it already existed

Public Function AddProcedure(workspaceId As Integer, GroupID As Integer, TaskID As Integer, ProcedureID As Integer, TaskReference As Integer, StartTime As Date, EndTime As Date) As Boolean
    
    ' check to make sure there is no mode conflict first...
    Dim mySQLStatement As String
    Dim resultSet As rdoResultset
    
    'make sure the procedure is valid
    If isProcValid(StartTime, EndTime, ProcedureID) = True Then
 
        ' check to see if we need to create a new risk period at start time
        CheckRiskPeriodCreate StartTime, workspaceId
        ' check to see if we need to create a new risk period at end time
        CheckRiskPeriodCreate EndTime, workspaceId
        
        'check to see if this procedure is a duplicate
        mySQLStatement = "SELECT WorkspaceID, ProcedureID, TaskReference FROM " & _
            "WorkspaceProcedures WHERE WorkspaceID = " & workspaceId & _
            " AND ProcedureID = " & ProcedureID & _
            " AND TaskReference = " & TaskReference
            
        Set resultSet = dbConnection.OpenResultset(mySQLStatement)
        If (resultSet.EOF) Then
            mySQLStatement = "INSERT INTO [WorkspaceProcedures] (WorkspaceID, " & _
                "TaskID, StartTime, EndTime, GroupID, ProcedureID, TaskReference) " & _
                "VALUES ( " & workspaceId & ", " & TaskID & ", " & SQLDate(StartTime) & ", " & _
                SQLDate(EndTime) & ", " & GroupID & ", " & ProcedureID & ", " & TaskReference & ")"
            dbConnection.Execute (mySQLStatement)
        Else
            ' return an error
            LastError = 1
            AddProcedure = False
        End If
            
        RecalculateNeedUpdates StartTime, EndTime
            
        AddProcedure = True
    Else
        AddProcedure = False
    End If
    
End Function

' function DeleteProcedure
' return value true - process successfully deleted
' return value false - process could not be deleted because it did not exist according to specified parameters

Public Function DeleteProcedure(workspaceId As Integer, ProcedureID As Integer, TaskReference As Integer, StartTime As Date, EndTime As Date)

    Dim mySQLStatement As String
    Dim resultSet As rdoResultset
    
    ' check to make sure that a process with specified StartTime and EndTime exists
    mySQLStatement = "SELECT WorkspaceID, ProcedureID, TaskReference FROM " & _
        "WorkspaceProcedures WHERE WorkspaceID = " & workspaceId & _
        " AND ProcedureID = " & ProcedureID & _
        " AND TaskReference = " & TaskReference & _
        " AND StartTime = " & SQLDate(StartTime) & _
        " AND EndTime = " & SQLDate(EndTime)
        
    Set resultSet = dbConnection.OpenResultset(mySQLStatement)
    
    If (resultSet.EOF) Then
        ' such a row does not exist.  this is an error
        LastError = 1
        DeleteProcedure = False
        Exit Function
    Else
        ' row already exists. delete
        
        mySQLStatement = "DELETE FROM WorkspaceProcedures WHERE" & _
            " WorkspaceID = " & workspaceId & _
            " AND ProcedureID = " & ProcedureID & _
            " AND TaskReference = " & TaskReference
        dbConnection.Execute (mySQLStatement)
        
        ' now check to see if we need to delete Risk Period at start time
        CheckRiskPeriodDelete StartTime, workspaceId
        ' now check to see if we need to delete Risk Period at end time
        CheckRiskPeriodDelete EndTime, workspaceId
        
        DeleteProcedure = True
            
    End If
    RecalculateNeedUpdates StartTime, EndTime
    
End Function

' function ChangeProcedureTime
' return value true - success
' return value false - process could not be changed because process with
'                  specified time did not exist

Public Function ChangeProcedureTime(workspaceId As Integer, ProcedureID As Integer, TaskReference As Integer, OldStartTime As Date, OldEndTime As Date, NewStartTime As Date, NewEndTime As Date) As Boolean
    
    ' check to make sure that a process with specified StartTime and EndTime exists
    
    Dim mySQLStatement As String
    Dim resultSet As rdoResultset
    
    If isProcValid(NewStartTime, NewEndTime, ProcedureID) = True Then
    
         mySQLStatement = "SELECT WorkspaceID, ProcedureID, TaskReference FROM " & _
             "[WorkspaceProcedures] WHERE WorkspaceID = " & workspaceId & _
             " AND ProcedureID = " & ProcedureID & _
             " AND TaskReference = " & TaskReference & _
             " AND StartTime = " & SQLDate(OldStartTime) & _
             " AND EndTime = " & SQLDate(OldEndTime)
         Set resultSet = dbConnection.OpenResultset(mySQLStatement)
         
         If (resultSet.EOF) Then
             ' such a row does not exist.  this is an error
             LastError = 1
             ChangeProcedureTime = False
             Exit Function
         End If
             
         mySQLStatement = "UPDATE WorkspaceProcedures SET" & _
             " StartTime = " & SQLDate(NewStartTime) & _
             ", EndTime = " & SQLDate(NewEndTime) & _
             " WHERE WorkspaceID = " & workspaceId & _
             " AND ProcedureID = " & ProcedureID & _
             " AND TaskReference = " & TaskReference
             
         dbConnection.Execute (mySQLStatement)
             
         If (NewStartTime <> OldStartTime) Then
             ' now check to see if we need to delete Risk Period at old start time
              CheckRiskPeriodDelete OldStartTime, workspaceId
         End If
         
         If (NewEndTime <> OldEndTime) Then
             ' now check to see if we need to delete Risk Period at old end time
             CheckRiskPeriodDelete OldEndTime, workspaceId
         End If
         
         ' now check to see if we need to add a new Risk Period at new start time
         CheckRiskPeriodCreate NewStartTime, workspaceId
         ' check to see if we need to create a new risk period at end time
         CheckRiskPeriodCreate NewEndTime, workspaceId
                    
         Dim Date1 As Date, Date2 As Date
         If OldStartTime < NewStartTime Then Date1 = OldStartTime Else Date1 = NewStartTime
         If OldEndTime > NewEndTime Then Date2 = OldEndTime Else Date2 = NewEndTime
         RecalculateNeedUpdates Date1, Date2
         ChangeProcedureTime = True
    Else
        ChangeProcedureTime = False
    End If
    
End Function

Private Sub RecalculateNeedUpdates(ByVal StartTime As Date, ByVal EndTime As Date)
    Dim mySQLStatement As String
    
    ' fetch all periods within specified times
    If (StartTime > EndTime) Then
        Dim tempTime As Date
        tempTime = StartTime
        StartTime = EndTime
        EndTime = tempTime
    End If
    
    mySQLStatement = "UPDATE [RiskPeriods] SET NeedUpdate = 1 WHERE " & _
        "PeriodTime >= " & SQLDate(StartTime) & _
        " AND PeriodTime <= " & SQLDate(EndTime)
        
    dbConnection.Execute (mySQLStatement)
    MDIMain.dataBaseChangesMade = 1
   
End Sub
'Function: isProcValid
'purpose: returns true if proc is valid for given time Startdate and EndDate
'are for procedure in question
Public Function isProcValid(StartDate As Date, EndDate As Date, ProcID As Integer) As Boolean
    Dim procMode As Variant
    Dim rArray As Variant
    Dim procModeRow As Integer
    Dim rArrayRow As Integer
    Dim mySQL As String
    Dim resultSet As rdoResultset
    Dim i As Integer
    Dim j As Integer
    Dim validProcedure As Boolean
    Dim startArray As Date
    Dim endArray As Date
    
    procModeRow = 0
    rArrayRow = 0
    
    'get list of procedure and mode relations
    mySQL = "SELECT ModeID, ProcedureID FROM [ProcMode]"
    Set resultSet = dbConnection.OpenResultset(mySQL, rdOpenKeyset)
        
        If resultSet.EOF Then
            isProcValid = False
            Exit Function
        Else
            While Not resultSet.EOF
                resultSet.MoveNext
                procModeRow = procModeRow + 1
            Wend
            
            resultSet.MoveFirst
            procMode = resultSet.GetRows(procModeRow)
        End If
        
    'Get workspace modes
    mySQL = "SELECT ModeID, StartTime FROM [WorkspaceMode] WHERE WorkspaceID = " & MDIMain.returnID & " ORDER BY StartTime DESC"
    Set resultSet = dbConnection.OpenResultset(mySQL, rdOpenKeyset)
    
    If resultSet.EOF Then
        isProcValid = False
        Exit Function
    Else
        While Not resultSet.EOF
            resultSet.MoveNext
            rArrayRow = rArrayRow + 1
        Wend
            
        resultSet.MoveFirst
        rArray = resultSet.GetRows(rArrayRow)
    End If
    
    'For each date
    For i = 0 To rArrayRow - 1
        validProcedure = False
        'if mode start date is between procedure start and end
        startArray = rArray(1, i)
        If (startArray < EndDate And startArray > StartDate) Then
            'Check to see if legal value
            For j = 0 To procModeRow - 1
                If procMode(0, j) = rArray(0, i) And procMode(1, j) = ProcID Then
                    validProcedure = True
                    Exit For
                End If
            Next j
            
            'if the procedure was not valid
            If validProcedure = False Then
                isProcValid = False
                Exit Function
            End If
        'else if mode start date is before procedure start
        ElseIf rArray(1, i) < StartDate Then
            'Check to see if legal value
            For j = 0 To procModeRow - 1
                If procMode(0, j) = rArray(0, i) And procMode(1, j) = ProcID Then
                    validProcedure = True
                    Exit For
                End If
            Next j
            
            'if the procedure was not valid
            If validProcedure = False Then
                isProcValid = False
                Exit Function
            End If
         isProcValid = True
         Exit Function
        End If
    Next i
    
    'if procedure starts and there is no mode (start of WS)
    If rArray(1, rArrayRow - 1) > StartDate Then
        isProcValid = False
        Exit Function
    End If
    
    isProcValid = True
        
End Function
'Function: isModeValid
'purpose: returns true is mode is valid for given time and workspace
'startdate is start date of mode
Public Function isModeValid(StartDate As Date, modeID As Integer, WS As Workspace, nextModeTime As Date) As Boolean
'
    Dim procMode As Variant
    Dim rArray As Variant
    Dim procModeRow As Integer
    Dim rArrayRow As Integer
    Dim mySQL As String
    Dim resultSet As rdoResultset
    Dim i As Integer
    Dim j As Integer
    Dim validMode As Boolean
    
    'Check to make sure mode is not at the same time as another mode
    mySQL = "SELECT ModeID, StartTime FROM [WorkspaceMode] WHERE WorkspaceID = " & WS.workspaceId & " AND StartTime = " & SQLDate(StartDate)
    Set resultSet = dbConnection.OpenResultset(mySQL, rdOpenKeyset)
        
    If Not resultSet.EOF Then
        'MsgBox "Mode Already Exists at Requested Time", vbInformation
        isModeValid = False
        Exit Function
    End If
    
    'Get workspace modes where start date is greater than StartDate
    mySQL = "SELECT ModeID, StartTime FROM [WorkspaceMode] WHERE WorkspaceID = " & WS.workspaceId & " AND StartTime > " & SQLDate(StartDate) & " ORDER BY StartTime"
    Set resultSet = dbConnection.OpenResultset(mySQL, rdOpenKeyset)
    
    If Not resultSet.EOF Then
        'Get an end date for the mode
        rArray = resultSet.GetRows(1)
        nextModeTime = rArray(1, 0)
    Else
        nextModeTime = WS.EndTime
    End If

    'get list of procedure and mode relations
    mySQL = "SELECT ModeID, ProcedureID FROM [ProcMode]"
    Set resultSet = dbConnection.OpenResultset(mySQL, rdOpenKeyset)
        
    If resultSet.EOF Then
        isModeValid = True
        Exit Function
    Else
        While Not resultSet.EOF
            resultSet.MoveNext
            procModeRow = procModeRow + 1
        Wend
        
        resultSet.MoveFirst
        procMode = resultSet.GetRows(procModeRow)
    End If
    
    rArrayRow = 0
    'Get workspace procedures
    mySQL = "SELECT ProcedureID, StartTime, EndTime FROM [WorkspaceProcedures] WHERE WorkspaceID = " & WS.workspaceId
    Set resultSet = dbConnection.OpenResultset(mySQL, rdOpenKeyset)
    
    'if no procedure exists at that time the mode is fine
    If resultSet.EOF Then
        isModeValid = True
        Exit Function
    Else
        While Not resultSet.EOF
            resultSet.MoveNext
            rArrayRow = rArrayRow + 1
        Wend
            
        resultSet.MoveFirst
        rArray = resultSet.GetRows(rArrayRow)
        
    End If
    
    
    For i = 0 To rArrayRow - 1
        validMode = False
        'Determine if procedure and mode dates overlap
        If (StartDate > rArray(1, i) And StartDate < rArray(2, i)) Or _
            (nextModeTime > rArray(1, i) And nextModeTime < rArray(2, i)) Or _
            (rArray(1, i) > StartDate And rArray(2, i) < nextModeTime) Then
            
                'determine if the overlap is legal
                For j = 0 To procModeRow - 1
                    If procMode(1, j) = rArray(0, i) And procMode(0, j) = modeID Then
                        validMode = True
                        Exit For
                    End If
                Next j
                
                'if the mode was not valid
                If validMode = False Then
                    isModeValid = False
                    Exit Function
                End If
            
          isModeValid = True
          Exit Function
        End If
    
    Next i
    
    isModeValid = True
End Function
'Function: removeModeCheck
'Purpose: Make sure it is legal to remove a mode in the active workspace
Public Function removeModeCheck(modeID As Integer, ModeName As String, ModeStart As Date) As Boolean
    Dim prevModeID As Integer
    Dim prevModeName As String
    Dim prevModeStart As Date
    Dim mySQL As String
    Dim modeArray As Variant
    Dim ProcArray As Variant
    Dim resultSet As rdoResultset
    Dim modeRow As Integer
    Dim procRow As Integer
    Dim modeEnd As Date
    Dim postModeStart As Date
    Dim procMode As Variant
    Dim procModeRow As Integer
    
    'MsgBox "workspace id = " & MDIMain.returnID
    
    'get list of procedure and mode relations
    mySQL = "SELECT ModeID, ProcedureID FROM [ProcMode]"
    Set resultSet = dbConnection.OpenResultset(mySQL, rdOpenKeyset)
        
        If resultSet.EOF Then
            removeModeCheck = True
            Exit Function
        Else
            While Not resultSet.EOF
                resultSet.MoveNext
                procModeRow = procModeRow + 1
            Wend
            
            resultSet.MoveFirst
            procMode = resultSet.GetRows(procModeRow)
        End If
        
    'get list of modes from database
    mySQL = "SELECT ModeID, ModeName, StartTime FROM [WorkspaceMode] WHERE WorkspaceID = " & MDIMain.returnID & " ORDER BY StartTime"
    Set resultSet = dbConnection.OpenResultset(mySQL, rdOpenKeyset)
    
    'if no mode exists
    If resultSet.EOF Then
        removeModeCheck = False
        Exit Function
    Else
        While Not resultSet.EOF
            resultSet.MoveNext
            modeRow = modeRow + 1
        Wend
            
        resultSet.MoveFirst
        modeArray = resultSet.GetRows(modeRow)
        
    End If
    
    
    'Get workspace procedures
    mySQL = "SELECT ProcedureID, StartTime, EndTime FROM [WorkspaceProcedures] WHERE WorkspaceID = " & MDIMain.returnID
    Set resultSet = dbConnection.OpenResultset(mySQL, rdOpenKeyset)
    
    'if no procedure exists at that time removing the mode is fine
    If resultSet.EOF Then
        removeModeCheck = True
        Exit Function
    Else
        While Not resultSet.EOF
            resultSet.MoveNext
            procRow = procRow + 1
        Wend
            
        resultSet.MoveFirst
        ProcArray = resultSet.GetRows(procRow)
    End If
    
    
    Dim i As Integer
    Dim j As Integer
    Dim k As Integer
    Dim flag As Boolean
    For i = 0 To modeRow - 1
        
        If modeArray(0, i) = modeID And modeArray(1, i) = ModeName And modeArray(2, i) = ModeStart Then
            'if mode is last mode in workspace
            If i = modeRow - 1 Then
                prevModeID = modeArray(0, i - 1)
                prevModeName = modeArray(1, i - 1)
                prevModeStart = modeArray(2, i - 1)
                For j = 0 To procRow - 1
                    flag = False
                    'if procedure time and time of mode that is
                    'being removed overlap check to make sure the mode
                    'that will fill its place is legal
                    If ProcArray(1, j) > ModeStart Or ProcArray(2, j) > ModeStart Then
                        For k = 0 To procModeRow - 1
                            If ProcArray(0, j) = procMode(1, k) And prevModeID = procMode(0, k) Then
                                flag = True
                            End If
                        Next k
                        If flag = False Then
                            removeModeCheck = False
                            Exit Function
                        End If
                    End If
                Next j
            ElseIf i = 0 Then 'mode is first mode in workspace
                'if mode is only mode
                If modeRow = 1 Then
                    removeModeCheck = False
                    Exit Function
                Else
                    postModeStart = modeArray(2, i + 1)
                    For j = 0 To procRow - 1
                        If ProcArray(1, j) < postModeStart Or ProcArray(2, j) < postModeStart Then
                           removeModeCheck = False
                           Exit Function
                        End If
                    Next j
                End If
            
            Else 'otherwise the mode is in the middle
                prevModeID = modeArray(0, i - 1)
                prevModeName = modeArray(1, i - 1)
                prevModeStart = modeArray(2, i - 1)
                For j = 0 To procRow - 1
                    flag = False
                    'if procedure time and time of mode that is
                    'being removed overlap check to make sure the mode
                    'that will fill its place is legal
                    If ProcArray(1, j) > ModeStart Or ProcArray(2, j) > ModeStart Then
                        For k = 0 To procModeRow - 1
                            If ProcArray(0, j) = procMode(1, k) And prevModeID = procMode(0, k) Then
                                flag = True
                            End If
                        Next k
                        If flag = False Then
                            removeModeCheck = False
                            Exit Function
                        End If
                    End If
                Next j
            End If
            
            removeModeCheck = True
            Exit Function
        End If
    Next i
    
    removeModeCheck = True
End Function
'Function: isModeValidBetweenDates
'purpose: returns true is mode is valid for given time period and workspace
'startdate is start date of mode
Public Function isModeValidBetweenDates(StartDate As Date, EndDate As Date, modeID As Integer, WS As Workspace) As Boolean
'
    Dim procMode As Variant
    Dim rArray As Variant
    Dim procModeRow As Integer
    Dim rArrayRow As Integer
    Dim mySQL As String
    Dim resultSet As rdoResultset
    Dim i As Integer
    Dim j As Integer
    Dim validMode As Boolean
    'Dim EndDate As Date
    
    'get list of procedure and mode relations
    mySQL = "SELECT ModeID, ProcedureID FROM [ProcMode]"
    Set resultSet = dbConnection.OpenResultset(mySQL, rdOpenKeyset)
        
        If resultSet.EOF Then
            isModeValidBetweenDates = True
            Exit Function
        Else
            While Not resultSet.EOF
                resultSet.MoveNext
                procModeRow = procModeRow + 1
            Wend
            
            resultSet.MoveFirst
            procMode = resultSet.GetRows(procModeRow)
        End If
    
    rArrayRow = 0
    'Get workspace procedures
    mySQL = "SELECT ProcedureID, StartTime, EndTime FROM [WorkspaceProcedures] WHERE WorkspaceID = " & WS.workspaceId
    Set resultSet = dbConnection.OpenResultset(mySQL, rdOpenKeyset)
    
    'if no procedure exists at that time the mode is fine
    If resultSet.EOF Then
        isModeValidBetweenDates = True
        Exit Function
    Else
        While Not resultSet.EOF
            resultSet.MoveNext
            rArrayRow = rArrayRow + 1
        Wend
            
        resultSet.MoveFirst
        rArray = resultSet.GetRows(rArrayRow)
        
    End If
    
    
    For i = 0 To rArrayRow - 1
        validMode = False
        'Determine if procedure and mode dates overlap
        If (StartDate > rArray(1, i) And StartDate < rArray(2, i)) Or _
            (EndDate > rArray(1, i) And EndDate < rArray(2, i)) Or _
            (rArray(1, i) > StartDate And rArray(2, i) < EndDate) Then
            
                'determine if the overlap is legal
                For j = 0 To procModeRow - 1
                    If procMode(1, j) = rArray(0, i) And procMode(0, j) = modeID Then
                        validMode = True
                        Exit For
                    End If
                Next j
                
                'if the mode was not valid
                If validMode = False Then
                    isModeValidBetweenDates = False
                    Exit Function
                End If
            
          isModeValidBetweenDates = True
          Exit Function
        End If
    
    Next i
    
    isModeValidBetweenDates = True
End Function

Public Sub AddOOSItem(workspaceId As Integer, ComponentID As Integer, StartTime As Date, EndTime As Date, componentName As String)
    ' we are assuming error checking is already done,
    ' so simply add the OOSItem without further ado
    
    CheckRiskPeriodCreate StartTime, workspaceId
    CheckRiskPeriodCreate EndTime, workspaceId
    Dim mySQL As String
    mySQL = "INSERT INTO [OOSList] (WorkspaceID, ComponentID, StartTime, EndTime, ComponentName) VALUES ( " & workspaceId & ", " & ComponentID & ", " & SQLDate(StartTime) & ", " & SQLDate(EndTime) & ", '" & componentName & "')"
    dbConnection.Execute (mySQL)
    
    RecalculateNeedUpdates StartTime, EndTime
    
End Sub

Public Sub RemoveOOSItem(workspaceId As Integer, componentName As String, StartTime As Date, EndTime As Date)
    Dim mySQLStatement As String
    ' we are assuming that error checking has been done, in other words
    ' we won't be asked to delete an OOS Item which does not exist
    
    mySQLStatement = "DELETE FROM [OOSList] WHERE WorkspaceID = " & workspaceId _
                    & " AND ComponentName = '" & componentName & "' AND StartTime = " _
                    & SQLDate(StartTime) & " AND EndTime = " & SQLDate(EndTime)
    dbConnection.Execute (mySQLStatement)
    
    CheckRiskPeriodDelete StartTime, workspaceId
    CheckRiskPeriodDelete EndTime, workspaceId
    
    RecalculateNeedUpdates StartTime, EndTime
End Sub

Public Sub UpdateOOSItem(NewStartTime As Date, NewEndTime As Date, OldStartTime As Date, OldEndTime As Date, workspaceId As Integer, componentName As String)
    ' assume error checking has been done
    Dim mySQL As String
    
    mySQL = "UPDATE OOSList SET StartTime = " & SQLDate(NewStartTime) & ", EndTime = " & SQLDate(NewEndTime) & " WHERE WorkspaceID = " & workspaceId _
            & " AND ComponentName = '" & componentName & "' AND StartTime = " _
            & SQLDate(OldStartTime) & " AND EndTime = " & SQLDate(OldEndTime)
                  
    dbConnection.Execute (mySQL)
             
    If (NewStartTime <> OldStartTime) Then
        ' now check to see if we need to delete Risk Period at old start time
         CheckRiskPeriodDelete OldStartTime, workspaceId
    End If
    
    If (NewEndTime <> OldEndTime) Then
        ' now check to see if we need to delete Risk Period at old end time
        CheckRiskPeriodDelete OldEndTime, workspaceId
    End If
    
    ' now check to see if we need to add a new Risk Period at new start time
    CheckRiskPeriodCreate NewStartTime, workspaceId
    ' check to see if we need to create a new risk period at end time
    CheckRiskPeriodCreate NewEndTime, workspaceId
               
    Dim Date1 As Date, Date2 As Date
    If OldStartTime < NewStartTime Then Date1 = OldStartTime Else Date1 = NewStartTime
    If OldEndTime > NewEndTime Then Date2 = OldEndTime Else Date2 = NewEndTime
    RecalculateNeedUpdates Date1, Date2
    
End Sub

Public Function AddWorkspaceMode(workspaceId As Integer, modeID As Integer, StartTime As Date, ModeName As String, nextModeStartTime As Date) As Boolean
    ' assume error checking has been done
    On Error GoTo check
    Dim mySQLStatement As String
    mySQLStatement = "INSERT INTO [WorkspaceMode] (WorkspaceID, ModeID, StartTime, ModeName) VALUES ( " & _
        workspaceId & ", " & modeID & ", " & SQLDate(StartTime) & ", '" & ModeName & "')"
    dbConnection.Execute (mySQLStatement)
    
    GoTo endcheck
check:
    AddWorkspaceMode = False
    Exit Function
endcheck:
    On Error GoTo 0
    CheckRiskPeriodCreate StartTime, workspaceId
    RecalculateNeedUpdates StartTime, nextModeStartTime
    AddWorkspaceMode = True
End Function

Public Sub DeleteWorkspaceMode(workspaceId As Integer, modeID As Integer, StartTime As Date, nextModeStartTime As Date)
    ' assume error checking has been done
    Dim mySQL As String
    mySQL = "DELETE FROM [WorkspaceMode] WHERE ModeID = " & modeID & _
            " AND StartTime = " & SQLDate(StartTime) & " AND WorkspaceID = " & workspaceId
    dbConnection.Execute (mySQL)
    CheckRiskPeriodDelete StartTime, workspaceId
    RecalculateNeedUpdates StartTime, nextModeStartTime
    
End Sub

Public Sub ChangeWorkspaceMode(workspaceId As Integer, NewStartTime As Date, OldStartTime As Date, nextModeStartTime As Date)
    ' assume error checking has been done
    Dim mySQL As String
    mySQL = "UPDATE WorkspaceMode SET StartTime = " & SQLDate(NewStartTime) & _
            " WHERE WorkspaceID = " & workspaceId & " AND StartTime  =" & SQLDate(OldStartTime)
    dbConnection.Execute (mySQL)
    
    ' now check to see if we need to add a new Risk Period at new start time
    CheckRiskPeriodCreate NewStartTime, workspaceId
    CheckRiskPeriodDelete OldStartTime, workspaceId
    RecalculateNeedUpdates NewStartTime, nextModeStartTime
End Sub
