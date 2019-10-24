Attribute VB_Name = "CriticalComponentCalculator"
Option Explicit

' Explanation of how to use this module
' the purpose is to calculate the critical components at any given
' time.
' this is accomplished in several steps.  first, the saphire API is
' called to find the critical BEs.  they are those basic events
' which, if probability of failure were set to 1, would increase
' the risk level the most.
' since the user of this system cares little for basic event names,
' those basic events are mapped to base components.  since the
' relationship between base components and basic events is
' many to many (but hopefully should be mainly one to many
' relationships), there are different ways of sorting the the base
' components in terms of criticality
'
' First, call FindCriticalBaseComponents.  This will call the saphire
' api and redimension the critical base component array.
' Next, call SortCriticalBaseComponents.  This will sort the critical
' base components according to the sorting method you have selected.
' It will return the number of critical base components sorted.
' next, call GetCriticalBaseComponent to retrieve those elements in
' highest priority.
' It is possible to call SortCriticalBaseComponents again with a
' different method before calling findCriticalbase components.
'
' there are several ways of looking at most critical base components
' 1 - by peak risk increase (of basic events)
' 2 - by highest average risk increase (of basic events)
'     riskIncreaseSum / beCount
' 3 - by highest average risk increase (of basic events)
'     riskIncreaseSum / riskIncreaseCount
' 4 - by highest risk increase sum (of basic events)
'
' * I guess method 2 would give a better average than 3...

Public Enum SortMethodType
    SortByPeakRiskIncrease = 1
    SortByHighestAverageRiskBEs = 2
    SortByHighestAverageRisk = 3
    SortByHighRiskIncreaseSum = 4
End Enum

Private Type CritBEType
    beName As String
    RiskIncrease As Double
End Type

Public Type BaseCompRiskType
    ID As Integer
    InUse As Boolean
    BECount As Integer
    riskIncreaseSum As Double
    riskIncreasePeak As Double
    riskIncreaseCount As Integer
    name As String
    GroupName As String
End Type
    
' critical components are similiar.  they are to base components
' as base components are to basic events in this sense
' 1 - by peak risk increase (of base components)
' 2 - by highest average risk increase (of basic events)
' 3 - by highest risk increase sum (of basic events)

Dim critBEList() As CritBEType
Dim BaseComps() As BaseCompRiskType
Dim ActiveModeID As Integer
Private nBaseComponents As Integer
Private nBaseComponentsInUse As Integer
Private sortMethod As SortMethodType

'******************| Steve's DLL Support |*********************************************************
Private Declare Function LoadCritBE Lib "riskMon" (ByVal Time As String) As Long
Private Declare Function GetNextCritBE Lib "riskMon" (ByRef beName As String, ByRef RiskIncrease As Double) As Long
'**************************************************************************************************


Private Sub AddBERiskToBaseComponent(baseCompID As Integer, RiskIncrease As Double)
    ' basically, the idea is that each base component has 1 or more basic events,
    ' and now we want to find out which base components have basic events that
    ' if set to 1 would increase risk the most
    BaseComps(baseCompID).ID = baseCompID
    BaseComps(baseCompID).InUse = True
    BaseComps(baseCompID).riskIncreaseCount = BaseComps(baseCompID).riskIncreaseCount + 1
    BaseComps(baseCompID).riskIncreaseSum = BaseComps(baseCompID).riskIncreaseSum + RiskIncrease
    If RiskIncrease > BaseComps(baseCompID).riskIncreasePeak Then
        BaseComps(baseCompID).riskIncreasePeak = RiskIncrease
    End If
    If BaseComps(baseCompID).BECount = 0 Then
        Dim mySQL As String, resultSet As rdoResultset, rArray As Variant
        mySQL = "SELECT COUNT(*) FROM BaseCompBE WHERE ModeID = " & ActiveModeID
        Set resultSet = dbConnection.OpenResultset(mySQL)
        rArray = resultSet.GetRows(1)
        BaseComps(baseCompID).BECount = rArray(0, 0)
        mySQL = "SELECT Name, GroupName FROM [BaseComponent] WHERE BaseCompID = " & baseCompID
        Set resultSet = dbConnection.OpenResultset(mySQL)
        rArray = resultSet.GetRows(1)
        BaseComps(baseCompID).name = rArray(0, 0)
        BaseComps(baseCompID).GroupName = rArray(1, 0)
    End If
End Sub

Public Sub FindCriticalBaseComponents(STime As Date)
        
    Dim i As Integer, beName As String * 25, nBEs As Integer
    Dim mySQL As String, resultSet As rdoResultset
    Dim rArray As Variant, baseCompID As Integer, RiskIncrease As Double
    
    mySQL = "SELECT BaseCompID FROM BaseComponent ORDER BY BaseCompID DESC"
    Set resultSet = dbConnection.OpenResultset(mySQL)
    rArray = resultSet.GetRows(1)
    nBaseComponents = rArray(0, 0)
    ReDim BaseComps(1 To nBaseComponents) As BaseCompRiskType
        
    If LoadCritBE(Format$(STime, "m/d/yyyy h:mm:ss AM/PM")) = 0 Then
        MsgBox "LoadCritBE failed", vbExclamation
        Exit Sub
    End If
    
    ReDim critBEList(1 To 40) As CritBEType
    ActiveModeID = MDIMain.GanttChart.GetModePeriodData(STime).modeID
    
    For i = 1 To 40
        If GetNextCritBE(beName, RiskIncrease) = 0 Then Exit For
        If RiskIncrease < ModeList(ActiveModeID).BaselineRisk Then Exit For
        nBEs = nBEs + 1
        critBEList(nBEs).beName = beName
        critBEList(nBEs).RiskIncrease = RiskIncrease
    Next i
    
    For i = 1 To nBEs
        'mySQL = "SELECT Component.ComponentName, Component.ComponentID FROM BaseCompBE INNER JOIN (CompBaseComponent INNER JOIN Component ON CompBaseComponent.ComponentID = Component.ComponentID) ON BaseCompBE.BaseCompID = CompBaseComponent.BaseCompID Where (((BaseCompBE.beName) = '" & critBEList(i).beName & "') And ((BaseCompBE.modeID) = " & ActiveModeID & "))"
        mySQL = "SELECT BaseCompID FROM [BaseCompBE] WHERE BEName = '" & critBEList(i).beName & "' AND ModeID = " & ActiveModeID
        Set resultSet = dbConnection.OpenResultset(mySQL)
        RiskIncrease = critBEList(i).RiskIncrease
        While Not resultSet.EOF
            rArray = resultSet.GetRows(1)
            baseCompID = rArray(0, 0)
            AddBERiskToBaseComponent baseCompID, RiskIncrease
        Wend
    Next i
        
    ' now it should be possible to sort base components by risk
    ' increase.  this can be done according to different methods
    
    ' take the holes out
    Dim wIndex As Integer, nextHole As Integer, nextPiece As Integer
    For wIndex = 1 To nBaseComponents
        ' find the next hole
        Do While BaseComps(wIndex).InUse = True And wIndex <= nBaseComponents
            nBaseComponentsInUse = wIndex
            wIndex = wIndex + 1
        Loop
        nextHole = wIndex ' this one should not be in use... it is a hole
        For nextPiece = nextHole + 1 To nBaseComponents
            If BaseComps(nextPiece).InUse Then Exit For
        Next
        If nextPiece <= nBaseComponents Then
            BaseComps(nextHole) = BaseComps(nextPiece)
            BaseComps(nextPiece).InUse = False
        End If
    Next
    
End Sub

Public Function SortCriticalBaseComponents(sortType As SortMethodType) As Integer
    sortMethod = sortType
    QuickSortBaseComps nBaseComponentsInUse
    SortCriticalBaseComponents = nBaseComponentsInUse
End Function

Public Function GetCriticalBaseComponent(wIndex As Integer) As BaseCompRiskType
    GetCriticalBaseComponent = BaseComps(wIndex)
End Function

Public Function GetCriticalBE(wIndex As Integer) As CritBEType
    GetCriticalBE = critBEList(wIndex)
End Function

Private Sub QuickSortBaseComps(nElements As Integer)
    PartitionSort 1, nElements
End Sub

Private Function compareLessThan(index1 As Integer, index2 As Integer) As Boolean
    
    Select Case sortMethod
        Case SortByPeakRiskIncrease
            compareLessThan = (BaseComps(index1).riskIncreasePeak < BaseComps(index2).riskIncreasePeak)
        Case SortByHighestAverageRiskBEs
            compareLessThan = (BaseComps(index1).riskIncreaseSum / BaseComps(index1).BECount < BaseComps(index2).riskIncreaseSum / BaseComps(index2).BECount)
        Case SortByHighestAverageRisk
            compareLessThan = (BaseComps(index1).riskIncreaseSum / BaseComps(index1).riskIncreaseCount < BaseComps(index2).riskIncreaseSum / BaseComps(index2).riskIncreaseCount)
        Case SortByHighRiskIncreaseSum
            compareLessThan = (BaseComps(index1).riskIncreaseSum < BaseComps(index2).riskIncreaseSum)
    End Select

End Function

Private Sub swapElements(index1 As Integer, index2 As Integer)
    Dim tempComp As BaseCompRiskType
    tempComp = BaseComps(index1)
    BaseComps(index1) = BaseComps(index2)
    BaseComps(index2) = tempComp
End Sub

Private Sub PartitionSort(firstIndex As Integer, lastIndex As Integer)
    ' this is the quick sort algorithm
    ' take the first element of this array and determine its final position within this
    ' array (i.e., all values to the left are less than and all to the right are greater than)
    Dim rightPos As Integer, leftPos As Integer, firstElementLocation As Integer
    rightPos = lastIndex
    leftPos = firstIndex + 1
    firstElementLocation = firstIndex
    Do
        Do
            If rightPos <= firstElementLocation Then GoTo done
            If compareLessThan(rightPos, firstElementLocation) Then Exit Do
            rightPos = rightPos - 1
        Loop
        swapElements firstElementLocation, rightPos
        firstElementLocation = rightPos
        rightPos = rightPos - 1
        Do
            If leftPos = firstElementLocation Then GoTo done
            If compareLessThan(firstElementLocation, leftPos) Then Exit Do
            leftPos = leftPos + 1
        Loop
        swapElements firstElementLocation, leftPos
        firstElementLocation = leftPos
        leftPos = leftPos - 1
    Loop
done:
    If firstIndex < firstElementLocation - 1 Then PartitionSort firstIndex, firstElementLocation - 1
    If firstElementLocation + 1 < lastIndex Then PartitionSort firstElementLocation + 1, lastIndex
End Sub
