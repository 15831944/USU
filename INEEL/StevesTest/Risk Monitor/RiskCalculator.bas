Attribute VB_Name = "RiskCalculator"
Option Explicit

Public Type RiskPeriodType
    AverageRiskValue As Double
    InstantaneousRiskValue As Double
    modeID As Integer
    PeakRiskTime As Date
    PeakRiskValue As Double
End Type

Dim RiskPeriods() As RiskPeriodType
Private AllocatedArraySize As Integer
Public PeriodCount As Integer

Public Function GetRiskPeriod(wPeriod As Integer) As RiskPeriodType
    GetRiskPeriod = RiskPeriods(wPeriod)
End Function

'Function:
'Purpose
Public Function ClassifyRisk(rValue As Double, wMode As Integer) As Integer
    ' this function takes a risk value and classifies that risk value as
    ' low, medium, or high risk
    If wMode = -1 Then
        ClassifyRisk = -1
        Exit Function
    End If
    
    If Not ModeList.Item(wMode).ObjectInUse Then
        MsgBox "Error in classify risk... function called w/ invalid mode."
        ClassifyRisk = -1
        Exit Function
    End If
    
    If (rValue < ModeList.Item(wMode).BaselineRisk) Then
        ' negligible risk
        ClassifyRisk = 0
    ElseIf (rValue < ModeList.Item(wMode).MediumRisk) Then
        ' low risk
        ClassifyRisk = 1
    ElseIf (rValue < ModeList.Item(wMode).HighRisk) Then
        ' medium risk
        ClassifyRisk = 2
    Else
        ' high risk
        ClassifyRisk = 3
    End If
    
End Function

Public Sub UpdateRiskValues(ByVal StartDate As Date, TimeDiffInHours As Long, nPeriods As Integer, resolutionInHours As Integer)
    
    If (nPeriods > AllocatedArraySize) Then
        ReDim RiskPeriods(1 To nPeriods)
        AllocatedArraySize = nPeriods
    End If
    
    PeriodCount = nPeriods
    
    Dim wPeriod As Integer
    Dim EndDate As Date, curDate As Date, nextDate As Date
    Dim riskPeriodTime As Date, riskModeID As Integer
    
    Dim mySQLStatement As String, resultSet As rdoResultset, rArray As Variant
 
    EndDate = DateAdd("h", TimeDiffInHours * nPeriods, StartDate)
    curDate = DateAdd("h", -resolutionInHours, EndDate)
    riskPeriodTime = EndDate
    
    mySQLStatement = "SELECT PeriodTime, RiskValue, ModeID FROM [RiskPeriods] " & _
        "WHERE WorkspaceID = " & MDIMain.returnID & " AND " & _
        " PeriodTime < " & SQLDate(EndDate) & " ORDER BY PeriodTime DESC"
    Set resultSet = dbConnection.OpenResultset(mySQLStatement)
                              
    Dim pRValue As Double, totalRValue As Double, rValue As Double, pRTime As Date
                       
    For wPeriod = nPeriods To 1 Step -1
        ' get the average and peak risk values for this period
        nextDate = DateAdd("h", -TimeDiffInHours, curDate)
        totalRValue = 0
        pRValue = 0
        
        Do While curDate > nextDate
            If (curDate < riskPeriodTime And Not resultSet.EOF) Then
                ' we need to start using the next risk period value
                rArray = resultSet.GetRows(1)
                rValue = rArray(1, 0)
                riskPeriodTime = rArray(0, 0)
                riskModeID = rArray(2, 0)
            ElseIf resultSet.EOF Then
                rValue = 0
                riskPeriodTime = StartDate
                riskModeID = -1
            End If
            If rValue > pRValue Then
                pRValue = rValue
                pRTime = curDate
            End If
            If (riskModeID <> -1) Then
                totalRValue = totalRValue + ClassifyRisk(rValue, riskModeID)
            End If
            curDate = DateAdd("h", -resolutionInHours, curDate)
        Loop
        RiskPeriods(wPeriod).InstantaneousRiskValue = rValue
        RiskPeriods(wPeriod).AverageRiskValue = totalRValue / (TimeDiffInHours / resolutionInHours)
        RiskPeriods(wPeriod).PeakRiskValue = pRValue
        RiskPeriods(wPeriod).PeakRiskTime = pRTime
        RiskPeriods(wPeriod).modeID = riskModeID
        curDate = nextDate
    Next
    
End Sub

