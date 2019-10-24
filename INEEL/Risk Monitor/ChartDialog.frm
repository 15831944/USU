VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{86CF1D34-0C5F-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCT2.OCX"
Object = "{65E121D4-0C60-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCHRT20.OCX"
Begin VB.Form ChartDialog 
   BackColor       =   &H8000000B&
   Caption         =   "Risk Level"
   ClientHeight    =   8685
   ClientLeft      =   2775
   ClientTop       =   3765
   ClientWidth     =   10740
   Icon            =   "ChartDialog.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   8685
   ScaleWidth      =   10740
   StartUpPosition =   2  'CenterScreen
   Begin MSComctlLib.ImageList DangerIcons 
      Left            =   8640
      Top             =   4920
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483633
      ImageWidth      =   16
      ImageHeight     =   16
      MaskColor       =   16777215
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   3
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "ChartDialog.frx":0442
            Key             =   ""
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "ChartDialog.frx":0794
            Key             =   ""
         EndProperty
         BeginProperty ListImage3 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "ChartDialog.frx":0AE6
            Key             =   ""
         EndProperty
      EndProperty
   End
   Begin VB.CommandButton UpdateGraph 
      Caption         =   "Update Graph"
      Height          =   495
      Left            =   8640
      TabIndex        =   8
      Top             =   3720
      Width           =   1695
   End
   Begin VB.OptionButton ViewOption 
      Caption         =   "Components out of service"
      Height          =   255
      Index           =   1
      Left            =   4200
      TabIndex        =   6
      Top             =   5880
      Width           =   2415
   End
   Begin VB.OptionButton ViewOption 
      Caption         =   "Procedures in process"
      Height          =   255
      Index           =   2
      Left            =   6720
      TabIndex        =   5
      Top             =   5880
      Width           =   2055
   End
   Begin VB.OptionButton ViewOption 
      Caption         =   "Critical components"
      Height          =   255
      Index           =   0
      Left            =   2040
      TabIndex        =   4
      Top             =   5880
      Value           =   -1  'True
      Width           =   2055
   End
   Begin VB.CommandButton ViewDiagram 
      Caption         =   "View Diagram"
      Enabled         =   0   'False
      Height          =   495
      Left            =   9120
      TabIndex        =   2
      Top             =   6240
      Width           =   1335
   End
   Begin MSComctlLib.ListView ComponentView 
      Height          =   2295
      Left            =   240
      TabIndex        =   1
      Top             =   6240
      Width           =   8535
      _ExtentX        =   15055
      _ExtentY        =   4048
      View            =   3
      LabelEdit       =   1
      LabelWrap       =   -1  'True
      HideSelection   =   0   'False
      FullRowSelect   =   -1  'True
      GridLines       =   -1  'True
      _Version        =   393217
      SmallIcons      =   "DangerIcons"
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      BorderStyle     =   1
      Appearance      =   1
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      NumItems        =   0
   End
   Begin VB.CommandButton OKButton 
      Caption         =   "OK"
      Height          =   495
      Left            =   9120
      TabIndex        =   0
      Top             =   8040
      Width           =   1335
   End
   Begin MSChart20Lib.MSChart RiskChart 
      Height          =   5175
      Left            =   120
      OleObjectBlob   =   "ChartDialog.frx":0E38
      TabIndex        =   3
      Top             =   0
      Width           =   7935
   End
   Begin MSComCtl2.DTPicker EndTime 
      Height          =   375
      Left            =   8640
      TabIndex        =   9
      Top             =   3120
      Width           =   1695
      _ExtentX        =   2990
      _ExtentY        =   661
      _Version        =   393216
      Format          =   22806530
      CurrentDate     =   37021
   End
   Begin MSComCtl2.DTPicker StartTime 
      Height          =   375
      Left            =   8640
      TabIndex        =   10
      Top             =   1440
      Width           =   1575
      _ExtentX        =   2778
      _ExtentY        =   661
      _Version        =   393216
      Format          =   22806530
      CurrentDate     =   37021
   End
   Begin MSComCtl2.DTPicker EndDate 
      Height          =   375
      Left            =   8640
      TabIndex        =   11
      Top             =   2640
      Width           =   1695
      _ExtentX        =   2990
      _ExtentY        =   661
      _Version        =   393216
      Format          =   22806529
      CurrentDate     =   37021
   End
   Begin MSComCtl2.DTPicker StartDate 
      Height          =   375
      Left            =   8640
      TabIndex        =   12
      Top             =   960
      Width           =   1575
      _ExtentX        =   2778
      _ExtentY        =   661
      _Version        =   393216
      Format          =   22806529
      CurrentDate     =   37021
   End
   Begin VB.Label Label3 
      Caption         =   "View Options"
      Height          =   255
      Left            =   360
      TabIndex        =   15
      Top             =   5880
      Width           =   1455
   End
   Begin VB.Label Label1 
      BackColor       =   &H80000005&
      BackStyle       =   0  'Transparent
      Caption         =   "Start Time"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   8640
      TabIndex        =   14
      Top             =   360
      Width           =   1575
   End
   Begin VB.Label Label2 
      BackColor       =   &H80000005&
      BackStyle       =   0  'Transparent
      Caption         =   "Finish Time"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   8640
      TabIndex        =   13
      Top             =   2040
      Width           =   1575
   End
   Begin VB.Shape HighZone 
      BackColor       =   &H000000FF&
      BackStyle       =   1  'Opaque
      Height          =   1215
      Left            =   8160
      Top             =   480
      Width           =   255
   End
   Begin VB.Shape MediumZone 
      BackColor       =   &H0000FFFF&
      BackStyle       =   1  'Opaque
      Height          =   1215
      Left            =   8160
      Top             =   1680
      Width           =   255
   End
   Begin VB.Shape LowZone 
      BackColor       =   &H0000FF00&
      BackStyle       =   1  'Opaque
      Height          =   1215
      Left            =   8160
      Top             =   2880
      Width           =   255
   End
   Begin VB.Label SelectedPointLabel 
      Caption         =   "Data Point Selected: No Point Selected"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   11.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   360
      TabIndex        =   7
      Top             =   5400
      Width           =   7815
   End
End
Attribute VB_Name = "ChartDialog"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Public RiskStartTime As Date   ' these correspond to the values the date/time
Public RiskEndTime As Date     ' controls are showing
Private cRiskStartTime As Date ' these values correspond to the values the
Private cRiskEndTime As Date   ' graph is actually showing (or should be)
                            ' if they are different, the update graph button is
                            ' enabled
Private SelectedViewOption As Integer
Private Period As Long
Private SelectedTime As Date
Private IsPointSelected As Boolean
Private ProcedureArray As Variant 'for storing procedure data
Private ProcedureRows As Integer 'for counting procedure data

'Function:Command1_Click
'Purpose:
Private Sub Command1_Click()
    MsgBox ("ScaleHeight = " & Str(ScaleHeight) & " ScaleWidth = " & Str(ScaleWidth)), vbInformation
End Sub
'Function:ComponentView_ItemClick
'Purpose: IF a component is clicked set the view diagram button to enabled
Private Sub ComponentView_ItemClick(ByVal Item As MSComctlLib.ListItem)
    If SelectedViewOption <> 2 Then
        viewDiagram.Enabled = True
    End If
    
End Sub
'Function:EndDate_Change
'Purpose: if time is chaged enable update graph button
Private Sub EndDate_Change()
    RiskEndTime = EndDate.Value
    RiskEndTime = DateAdd("h", EndTime.Hour, RiskEndTime)
    RiskEndTime = DateAdd("n", EndTime.Minute, RiskEndTime)
    RiskEndTime = DateAdd("s", EndTime.Second, RiskEndTime)
    UpdateGraph.Enabled = (RiskEndTime <> cRiskEndTime Or RiskStartTime <> cRiskStartTime)
End Sub
'Function:EndTime_Change
'Purpose: if time is changed update graph button
Private Sub EndTime_Change()
    RiskEndTime = EndDate
    RiskEndTime = DateAdd("h", EndTime.Hour, RiskEndTime)
    RiskEndTime = DateAdd("n", EndTime.Minute, RiskEndTime)
    RiskEndTime = DateAdd("s", EndTime.Second, RiskEndTime)
    UpdateGraph.Enabled = (RiskEndTime <> cRiskEndTime Or RiskStartTime <> cRiskStartTime)
End Sub
'Function:OptionCriticalComponents_Click
'Purpose: if the critical components radial button is selected
Private Sub OptionCriticalComponents_Click()
    
End Sub
'Function:StartDate_Change
'Purpose: if the start date is chage make sure update graph is enabled
Private Sub StartDate_Change()
    RiskStartTime = StartDate.Value
    RiskStartTime = DateAdd("h", StartTime.Hour, RiskStartTime)
    RiskStartTime = DateAdd("n", StartTime.Minute, RiskStartTime)
    RiskStartTime = DateAdd("s", StartTime.Second, RiskStartTime)
    UpdateGraph.Enabled = (RiskEndTime <> cRiskEndTime Or RiskStartTime <> cRiskStartTime)
End Sub
'Function:StartTime_Change
'Purpose: if the start date is changed make sure update graph is enabled
Private Sub StartTime_Change()
    RiskStartTime = StartDate
    RiskStartTime = DateAdd("h", StartTime.Hour, RiskStartTime)
    RiskStartTime = DateAdd("n", StartTime.Minute, RiskStartTime)
    RiskStartTime = DateAdd("s", StartTime.Second, RiskStartTime)
    UpdateGraph.Enabled = (RiskEndTime <> cRiskEndTime Or RiskStartTime <> cRiskStartTime)
End Sub
'Function:Form_Load
'Purpose: initialize form values and set up procedure table
Private Sub Form_Load()
    Dim resultSet As rdoResultset
    Dim mySQL As String
    
    ProcedureRows = 0
    
    SelectedViewOption = 0
    ViewOption(SelectedViewOption).Value = True
    ListHeaders
    
    StartDate.Value = RiskStartTime
    EndDate.Value = RiskEndTime
    
    cRiskStartTime = RiskStartTime
    cRiskEndTime = RiskEndTime
      
    RedrawGraph
    
    'Set up procedure table
    mySQL = "SELECT ProcedureID, ProcedureName, ProcedureDesc FROM [Procedure]"
    Set resultSet = dbConnection.OpenResultset(mySQL, rdOpenKeyset)
    
    While Not resultSet.EOF
        resultSet.MoveNext
        ProcedureRows = ProcedureRows + 1
    Wend
    
    If ProcedureRows > 0 Then
        resultSet.MoveFirst
        ProcedureArray = resultSet.GetRows(ProcedureRows)
    End If
    
    HighZone.BackColor = DangerColor
    MediumZone.BackColor = CautionColor
    LowZone.BackColor = OKColor
    

End Sub
'Function:Form_Resize
'Purpose: Called when the form gets resized
Private Sub Form_Resize()
    
    Dim HighFraction As Single
    Dim MediumFraction As Single
    Dim LowFraction As Single
    Dim useableHeight As Integer
    
    HighFraction = 0.33
    MediumFraction = 0.33
    LowFraction = 0.33
    
    If (ScaleWidth > 10395 And ScaleHeight > 7380) Then
        Label1.Left = ScaleWidth - 2100
        StartDate.Left = ScaleWidth - 2100
        StartTime.Left = ScaleWidth - 2100
        Label2.Left = ScaleWidth - 2100
        EndDate.Left = ScaleWidth - 2100
        EndTime.Left = ScaleWidth - 2100
        UpdateGraph.Left = ScaleWidth - 2100
        viewDiagram.Left = ScaleWidth - 1740
        OKButton.Left = ScaleWidth - 1740
        ComponentView.Width = ScaleWidth - (ComponentView.Left + 1965)
        
        HighZone.Left = ScaleWidth - 2580
        MediumZone.Left = ScaleWidth - 2580
        LowZone.Left = ScaleWidth - 2580
        
        ComponentView.Top = ScaleHeight - (ComponentView.Height + 100)
        SelectedPointLabel.Top = ComponentView.Top - 800
        RiskChart.Height = ComponentView.Top - 800
        RiskChart.Width = ScaleWidth - (RiskChart.Left + 2690)
        OKButton.Top = ScaleHeight - 800
        viewDiagram.Top = ScaleHeight - 1450
        
        Label3.Top = ComponentView.Top - 400
        ViewOption(0).Top = ComponentView.Top - 400
        ViewOption(1).Top = ComponentView.Top - 400
        ViewOption(2).Top = ComponentView.Top - 400
        useableHeight = RiskChart.Height - 1500
        
        HighZone.Top = RiskChart.Top + 320
        HighZone.Height = useableHeight * HighFraction + 20
        MediumZone.Top = HighZone.Top + HighZone.Height - 20
        MediumZone.Height = useableHeight * MediumFraction + 20
        LowZone.Top = MediumZone.Top + MediumZone.Height - 20
        LowZone.Height = useableHeight * LowFraction
    End If
End Sub
'Function:OKButton_Click
'Purpose: unload form
Private Sub OKButton_Click()
    Unload Me
End Sub
'Function: EnableViewOptions
'Purpose: Enable chart components when point on graph is selected
Private Sub EnableViewOptions(Enable As Boolean)
    SelectedPointLabel.Enabled = Enable
    Label3.Enabled = Enable
    ViewOption(0).Enabled = Enable
    ViewOption(1).Enabled = Enable
    ViewOption(2).Enabled = Enable
    ComponentView.Enabled = Enable
    SelectedPointLabel.Caption = "Data Point Selected: No Point Selected"
End Sub
'Function:RiskChart_PointSelected
'Purpose: called when user selects point on the graph
Private Sub RiskChart_PointSelected(Series As Integer, DataPoint As Integer, MouseFlags As Integer, cancel As Integer)
    ' if the user clicks on the first data point, DataPoint = 1
    IsPointSelected = True
    EnableViewOptions True
    SelectedTime = DateAdd("h", Period * (DataPoint - 1), RiskStartTime)
    SelectedPointLabel.Caption = "Data Point Selected: " & FormatDateTime(SelectedTime)
    UpdateComponentView
    
End Sub
'Function:UpdateComponentView
'Purpose: called to fill in chart data - dependant on which radial button
'is selected
Private Sub UpdateComponentView()
    '
    If (IsPointSelected = False) Then MsgBox ("Error:  UpdateComponentView called when IsPointSelected = FALSE")
    'clear everything from component list...

    ComponentView.ListItems.Clear
    'call appropriate sub based on SelectedViewOption
            
    'Selected Radial Item
    Select Case SelectedViewOption
        Case 0:
            ListEssentialComponents
        Case 1:
            ListOOSList
        Case 2:
            ListActiveProcedures
    End Select
    
    viewDiagram.Enabled = False
End Sub
'Function:ListEssentialComponents
'Purpose: fill in critical component list
Private Sub ListEssentialComponents()
    Dim i As Integer, lItem As ListItem, bComp As BaseCompRiskType
    If DLLActive Then
        Dim nCrit As Integer
        CriticalComponentCalculator.FindCriticalBaseComponents SelectedTime
        nCrit = CriticalComponentCalculator.SortCriticalBaseComponents(SortByPeakRiskIncrease)
        i = 1
        Do While i < 10 And i < nCrit
            bComp = CriticalComponentCalculator.GetCriticalBaseComponent(i)
            Set lItem = ComponentView.ListItems.Add(, , bComp.name, , 1)
            lItem.ToolTipText = bComp.name
            lItem.ListSubItems.Add , , bComp.GroupName
            lItem.ListSubItems.Add , , bComp.riskIncreasePeak, 1, bComp.riskIncreasePeak
            lItem.ListSubItems.Add , , bComp.BECount, , bComp.BECount
        Loop
    Else
        For i = 1 To 2
            Set lItem = ComponentView.ListItems.Add()
            lItem.SmallIcon = i
            lItem.text = compHierarchy.BaseName & " " & Str(i)
            lItem.ListSubItems.Add , , "Stand by Liquid Control Pump 1"
            lItem.ListSubItems.Add , , "Emergency Boration"
            lItem.ListSubItems.Add , , "NMP1-SLC1"
            lItem.ListSubItems.Add , , "Positive Displacement"
        Next
    End If
End Sub
'Function:ListOOSList
'Purpose:fill in out of service list
Private Sub ListOOSList()
    Dim mySQL As String
    Dim resultSet As rdoResultset
    Dim RowReturn As Integer
    Dim rArray As Variant
    Dim row As Integer
    Dim ComponentList As ListItem
    Dim flag As Boolean
    
    RowReturn = 0
    row = 1
    
    'get components from table
    mySQL = "SELECT StartTime, EndTime, ComponentName, ComponentID FROM [OOSList] WHERE WorkspaceID = " & MDIMain.returnID
    Set resultSet = dbConnection.OpenResultset(mySQL, rdOpenKeyset)
    
    While Not resultSet.EOF
        resultSet.MoveNext
        RowReturn = RowReturn + 1
    Wend
    
    If RowReturn > 0 Then
        resultSet.MoveFirst
        rArray = resultSet.GetRows(RowReturn)
       
        Dim i As Integer
        Dim j As Integer
        Dim tempDesc As String
        
        
        'determine if dates overlap - if so add to chart
        For i = 0 To RowReturn - 1
            If (rArray(0, i) = SelectedTime) Or (rArray(1, i) = SelectedTime) Or (rArray(0, i) < SelectedTime And rArray(1, i) > SelectedTime) Then
                Set ComponentList = ComponentView.ListItems.Add()
                ComponentList.text = rArray(2, i)
                ComponentView.ListItems(row).ListSubItems.Add , , rArray(0, i)
                ComponentView.ListItems(row).ListSubItems.Add , , rArray(1, i)
                row = row + 1
                flag = True
            End If
        Next i
    
    Else
        MsgBox SelectedTime & " - No Out of Service Components Found", vbInformation
        Exit Sub
    End If
    
    If flag = False Then
        MsgBox SelectedTime & " - No Out of Service Components Found", vbInformation
    End If
End Sub
'Function:ListActiveProcedures
'Purpose:fill in active procedures chart
Private Sub ListActiveProcedures()
    Dim mySQL As String
    Dim resultSet As rdoResultset
    Dim RowReturn As Integer
    Dim rArray As Variant
    Dim row As Integer
    Dim ComponentList As ListItem
    Dim flag As Boolean
    
    RowReturn = 0
    row = 1
    
    'get procedures from database
    mySQL = "SELECT StartTime, EndTime, ProcedureID FROM [WorkspaceProcedures] WHERE WorkspaceID = " & MDIMain.returnID
    Set resultSet = dbConnection.OpenResultset(mySQL, rdOpenKeyset)
    
    While Not resultSet.EOF
        resultSet.MoveNext
        RowReturn = RowReturn + 1
    Wend
    
    If RowReturn > 0 Then
        resultSet.MoveFirst
        rArray = resultSet.GetRows(RowReturn)
       
        Dim i As Integer
        Dim j As Integer
        Dim TempName As String
        Dim tempDesc As String
        For i = 0 To RowReturn - 1
            'check to see if times overlap - if so add to chart
            If (rArray(0, i) = SelectedTime) Or (rArray(1, i) = SelectedTime) Or (rArray(0, i) < SelectedTime And rArray(1, i) > SelectedTime) Then
                For j = 0 To ProcedureRows - 1
                    If ProcedureArray(0, j) = rArray(2, i) Then
                        TempName = ProcedureArray(1, j)
                        tempDesc = ProcedureArray(2, j)
                        Exit For
                    End If
                Next j
                
                Set ComponentList = ComponentView.ListItems.Add()
                ComponentList.text = TempName
                ComponentView.ListItems(row).ListSubItems.Add , , tempDesc
                ComponentView.ListItems(row).ListSubItems.Add , , rArray(0, i)
                ComponentView.ListItems(row).ListSubItems.Add , , rArray(1, i)
                row = row + 1
                flag = True
            End If
        Next i
    
    Else
        MsgBox SelectedTime & " - No Procedures Found", vbInformation
        Exit Sub
    End If
    
    If flag = False Then
        MsgBox SelectedTime & " - No Procedures Found", vbInformation
    End If
End Sub
'Function:ListHeaders
'Purpose:create the headders for the chart - dependant on radial button
Private Sub ListHeaders()
    ComponentView.ColumnHeaders.Clear
        
    Select Case SelectedViewOption
        Case 0: ' List Essential Components
            AddHeader compHierarchy.BaseName
            AddHeader compHierarchy.BaseName & " Group"
            AddHeader "Peak Risk Increase"
            AddHeader "BE Count"
        Case 1:
            AddHeader "Component Name"
            AddHeader "Start Time"
            AddHeader "End Time"
        Case 2:
            AddHeader "Procedure Name"
            AddHeader "Description"
            AddHeader "Start Time"
            AddHeader "End Time"
            
    End Select
    Dim wColumn As Integer
    
    For wColumn = 1 To ComponentView.ColumnHeaders.Count
        ComponentView.ColumnHeaders(wColumn).Width = (ComponentView.Width - 60) / ComponentView.ColumnHeaders.Count
    Next wColumn
        
End Sub
'Function:AddHeader
'Purpose: create chart header
Private Sub AddHeader(text As String)
    Dim colHeader As ColumnHeader
    Set colHeader = ComponentView.ColumnHeaders.Add()
    colHeader.text = text
End Sub
'Function:UpdateGraph_Click
'Purpose: error check user input then call function to redraw graph with
'user input
Private Sub UpdateGraph_Click()
    If (RiskStartTime >= RiskEndTime) Then
        Dim myVar
        myVar = MsgBox("The start time must be before the end time.  Please change your selection.", vbInformation, "Error")
    ElseIf (DateDiff("h", RiskStartTime, RiskEndTime) < 1) Then
        Dim myVar1
        myVar1 = MsgBox("The end time must be at least one hour after the start time.  Please change your selection.", vbInformation, "Error")
    Else
        cRiskStartTime = RiskStartTime
        cRiskEndTime = RiskEndTime
        RedrawGraph
    End If
End Sub
'Function:Ceil
'Purpose: set ceiling value
Private Function Ceil(X As Single) As Integer
    Ceil = Int(X) + Sgn(X - Int(X))
End Function
'Function:RedrawGraph
'Purpose:Redraw graph
Private Sub RedrawGraph()
    Dim X As Integer
    Dim numData As Integer
    Dim nHours As Long
    Dim label As String
    Dim curDate As Date
    Dim lastDay As Integer
    Dim invalidModeFound As Boolean
    
    lastDay = 0
    curDate = RiskStartTime
    nHours = DateDiff("h", RiskStartTime, RiskEndTime)
    Period = GetTimeResolution(nHours)
    
    numData = Ceil(nHours / Period)
    
    ReDim Data(0 To numData, 0 To 4) As Variant
    ' first dimension is the number of data points
    ' second dimension is the number of data series
    
    Data(0, 0) = "Relative Risk "
    Data(0, 1) = "Average"
    Dim resolution As Integer
    resolution = Sqr(Period / 10)
    If resolution < 1 Then resolution = 1
    
    RiskCalculator.UpdateRiskValues RiskStartTime, Period, numData, resolution
    
    Dim sum As Integer, rValue As Double, chartValue As Integer, Mode As Integer
    sum = 0
    ' to draw main risk line
    For X = 1 To numData
        rValue = RiskCalculator.GetRiskPeriod(X).PeakRiskValue
        Mode = RiskCalculator.GetRiskPeriod(X).modeID
        If Mode = -1 Then
            invalidModeFound = True
        Else
            If rValue = 0 Then
                chartValue = 0
            ElseIf RiskCalculator.ClassifyRisk(rValue, Mode) < 2 Then
                ' use m and b values for lower half of graph
                chartValue = ModeList.Item(Mode).Ml * Log(rValue) / Log(10) + ModeList.Item(Mode).Bl
            Else
                ' use m and b values for upper half of graph
                chartValue = ModeList.Item(Mode).Mh * Log(rValue) / Log(10) + ModeList.Item(Mode).Bh
            End If
            If chartValue < 0 Then chartValue = 0
            If chartValue > GraphHeight Then chartValue = GraphHeight
            Data(X, 0) = chartValue
            sum = sum + chartValue
        End If
        
    Next
    
    ' to draw average line
    For X = 1 To numData
        Data(X, 1) = sum / numData
        Data(X, 2) = PixelH
        Data(X, 3) = PixelM
        Data(X, 4) = PixelB
    Next
    
    RiskChart.ChartData = Data
    
    RiskChart.RowLabelCount = 1
    RiskChart.rowCount = numData
    curDate = RiskStartTime
    For X = 1 To numData
        RiskChart.row = X
        If ((Hour(curDate) = 0 And Minute(curDate) = 0) Or Day(curDate) <> lastDay) Then
            RiskChart.RowLabel = FormatDateTime(curDate, vbShortDate)
        Else
            RiskChart.RowLabel = FormatDateTime(curDate, vbShortTime)
        End If
        curDate = DateAdd("h", Period, curDate)
    Next
    'RiskChart.ColumnLabelCount = 1
    'RiskChart.ColumnCount = 9
    'For X = 1 To 9
    '    RiskChart.Column = X
    '    RiskChart.ColumnLabel = Str(X)
    'Next
    
    'Dim Data(1 To 5, 1 To 10) As Variant
    'Data(1, 1) = "Y values"
    'Dim X As Integer
    
    'For X = 1 To 10
    '    Data(2, X) = 1
    '    Data(3, X) = 2
    '    Data(4, X) = 3
    '    Data(5, X) = 4
    'Next
    'RiskChart.ChartData = Data
    UpdateGraph.Enabled = False
    IsPointSelected = False
    EnableViewOptions False
    
    'clear chart since no point is now selected
    ComponentView.ListItems.Clear
    
    If invalidModeFound Then
        MsgBox "All or part of the time period selected is not covered by a mode.  Without a mode risk calculation is not possible.", vbInformation
    End If
    
End Sub
'Function:GetTimeResolution
'Purpose: determine the time resolution for the graph
Private Function GetTimeResolution(hours As Long) As Integer
    'GetTimeResolution = DateAdd("h", 1, GetTimeResolution)
    Select Case hours                               '           min periods max periods
        Case Is <= 24: GetTimeResolution = 1        ' 1 day     -           24
        Case Is <= 72: GetTimeResolution = 3        ' 3 days    8           24
        Case Is <= 168: GetTimeResolution = 8       ' 1 week    9           21
        Case Is <= 744: GetTimeResolution = 24      ' 1 month   7           31
        Case Is <= 2208: GetTimeResolution = 72     ' 3 mos     10.33       30.667
        Case Is <= 8784: GetTimeResolution = 168    ' 1 year    13.14       52.28
        Case Is <= 26304: GetTimeResolution = 744   ' 3 years   11.81       35.35
        Case Is <= 157968: GetTimeResolution = 2208 ' 8 years   11.91       71.54
        Case Else: GetTimeResolution = 8784         ' 8+ years  17.98       -
    End Select
       
            
End Function
'Function:ViewDiagram_Click
'Purpose:Display a component diagram
Private Sub viewDiagram_Click()
    ComponentDiagram.Show (1)
End Sub
'Function:ViewOption_Click
'Purpose: update chart when radial button is clicked.
Private Sub ViewOption_Click(Index As Integer)
    
    If (Index <> SelectedViewOption) Then
        SelectedViewOption = Index
        ListHeaders
        UpdateComponentView
    End If
    
End Sub
