VERSION 5.00
Object = "{86CF1D34-0C5F-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCT2.OCX"
Begin VB.UserControl GanttChart 
   AutoRedraw      =   -1  'True
   ClientHeight    =   3630
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   5160
   OLEDropMode     =   1  'Manual
   PropertyPages   =   "GanttChart.ctx":0000
   ScaleHeight     =   3630
   ScaleWidth      =   5160
   ToolboxBitmap   =   "GanttChart.ctx":0019
   Begin VB.ComboBox ModeFillStyle 
      Height          =   315
      ItemData        =   "GanttChart.ctx":054B
      Left            =   480
      List            =   "GanttChart.ctx":0567
      Style           =   2  'Dropdown List
      TabIndex        =   2
      Top             =   3120
      Visible         =   0   'False
      Width           =   2175
   End
   Begin VB.ComboBox ModeStyle 
      Height          =   315
      ItemData        =   "GanttChart.ctx":05E9
      Left            =   480
      List            =   "GanttChart.ctx":05F9
      Style           =   2  'Dropdown List
      TabIndex        =   1
      Top             =   2760
      Visible         =   0   'False
      Width           =   2175
   End
   Begin VB.Timer DoubleClickTimer 
      Enabled         =   0   'False
      Left            =   0
      Top             =   0
   End
   Begin MSComCtl2.FlatScrollBar VScroll1 
      Height          =   2175
      Left            =   3600
      TabIndex        =   0
      Top             =   -240
      Width           =   255
      _ExtentX        =   450
      _ExtentY        =   3836
      _Version        =   393216
      Appearance      =   0
      Orientation     =   1179648
   End
   Begin MSComCtl2.FlatScrollBar HScroll1 
      Height          =   255
      Left            =   0
      TabIndex        =   3
      Top             =   1920
      Width           =   3615
      _ExtentX        =   6376
      _ExtentY        =   450
      _Version        =   393216
      Appearance      =   0
      Arrows          =   65536
      Orientation     =   1179649
   End
   Begin VB.Image ResizeHorizontalImage 
      Enabled         =   0   'False
      Height          =   480
      Left            =   4320
      Picture         =   "GanttChart.ctx":0623
      Top             =   3000
      Visible         =   0   'False
      Width           =   480
   End
   Begin VB.Image DraggingImage 
      Enabled         =   0   'False
      Height          =   480
      Left            =   3720
      Picture         =   "GanttChart.ctx":0775
      Top             =   3000
      Visible         =   0   'False
      Width           =   480
   End
End
Attribute VB_Name = "GanttChart"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

Type POINTAPI
    X As Long
    Y As Long
End Type

Type BarType
    rowID As Integer
    StartTime As Date
    EndTime As Date
    Color As Long
    Text As String
    Popuptext As String
    IsBlank As Boolean
End Type

Public Enum SelectionEnum
    HasFocus = 1
    LostFocus = 2
End Enum

Public Enum ModeBarStyleConstants
    None = 0
    TopBar = 1
    FixedAtTop = 2
    Background = 3
End Enum

Public Type SelectionType
    row As Integer
    sType As SelectionEnum
End Type

Private Declare Function GetCursorPos Lib "user32" (lpPoint As POINTAPI) As Long
Private Declare Function GetDoubleClickTime Lib "user32" () As Long

Dim ganttPeriodWidth As Integer
Dim ganttHeaderHeight As Integer
Dim ganttRowHeight As Integer
Dim ganttTimeResolution As TimeResolutionType
Dim ganttVisibleStartTime As Date
Dim ganttVisibleEndTime As Date
Dim ganttModePeriodBorderStyle As Integer
Dim ganttModePeriodFillStyle As FillStyleConstants
Dim ganttStartTime As Date
Dim ganttEndTime As Date
Dim IntervalStrings(1 To 7) As String
Dim IntervalsInPeriod(1 To 7) As String
Dim Bars() As BarType
Dim nBars As Integer
Dim nAllocatedBars As Integer
Public IsPopupVisible As Boolean
Private popupWindow As PopupForm
Dim mouseX As Integer
Dim mouseY As Integer

Dim totalMinutes As Long
Dim useableWidth As Long
Dim useableHeight As Integer
Dim mayStartDragging As Integer
Dim isDragging As Boolean
Dim wBarIsDragging As Integer
Dim explicitScrollChange As Boolean
Dim InitializationComplete As Boolean

Type ModePeriodType
    PeriodTime As Date
    modeID As Integer
    Color As Long
    Text As String
    Tag As Variant
End Type

Dim modePeriods() As ModePeriodType

Dim curModeIndex As Integer
Public nModePeriods As Integer

Dim ganttHeaderColor As Long, ganttHeaderFontColor As Long
Dim ganttHeaderGridColor As Long, ganttChartBackgroundColor As Long
Dim ganttChartHorizontalColor As Long, ganttChartBarOutlineColor As Long
Dim ganttHeaderFont As StdFont, ganttChartFont As StdFont
Dim ganttChartVerticalColor As Long

Dim useableLeft As Integer, useableRight As Integer
Dim useableTop As Integer, useableBottom As Integer

Dim minutesInPeriod As Long

Dim ganttVScrollVisible As Boolean, ganttHScrollVisible As Boolean
Dim firstVisibleBar As Integer
Dim nVisibleBars As Integer
Dim IsFormVisible As Integer
Dim maxAllowableGanttVisibleStartTime As Date
Dim ganttNotifyDuringVScroll As Boolean
Dim ganttSelection As SelectionType
Dim wBarWasClicked As Integer
Dim ganttModeBarStyle As ModeBarStyleConstants
Dim ganttPeriodWidthMultiplier As Single
Dim ganttEnableDoubleClick As Boolean

Public Event ChangeRowRequested(rowID As Integer, proposedStartTime As Date, proposedEndTime As Date, currentStartTime As Date, currentEndTime As Date)
Public Event ChangeModePeriodRequested(modeID As Integer, modeText As String, ArrayIndex As Integer, proposedTime As Date, currentTime As Date)
Public Event VerticalScrollChange(TopRow As Integer)
Public Event GanttGotFocus()
Public Event GanttLostFocus()
Public Event Click(wRow As Integer)
Public Event DblClick(wRow As Integer)

Public Enum TimeResolutionType
    hourView = 1
    shiftView = 2
    dayView = 3
    weekView = 4
    MonthView = 5 '744
    quarterView = 6 '2208
    yearView = 7 '8760
End Enum

Private Sub ErrorHandler(wSub As Variant)
    MsgBox ("Error Number " & Err.Number & " '" & Err.Description & "' occured in sub #" & wSub & " in " & Err.Source)
    Stop
End Sub

Public Function GetRowFromRowID(rowID As Integer) As Integer
    On Error GoTo ErrorLabel
    Dim i As Integer
    For i = 1 To nBars
        If Bars(i).rowID = rowID Then
            GetRowFromRowID = i
            Exit Function
        End If
    Next i
    GetRowFromRowID = -1
    Exit Function
ErrorLabel:
    ErrorHandler "GetRowFromRowID"
End Function

Public Function GetRowID(wRow As Integer)
    On Error GoTo ErrorLabel
    If wRow < 1 Or wRow > nBars Then
        GetRowID = -1
    Else
        GetRowID = Bars(wRow).rowID
    End If
    Exit Function
ErrorLabel:
    ErrorHandler 0
End Function

Public Function SetModePeriodTime(NewPeriodTime As Date, Optional ArrayIndex As Variant, Optional OldPeriodTime As Variant) As Boolean
    On Error GoTo ErrorLabel
    Dim aIndex As Integer, LocalTag As Object
    
    If Not IsMissing(ArrayIndex) Then
        aIndex = ArrayIndex
    ElseIf Not IsMissing(OldPeriodTime) Then
        aIndex = GetModeArrayIndexFromDate(OldPeriodTime)
        If aIndex = -1 Then
            SetModePeriodTime = False
            Exit Function
        End If
    Else
        SetModePeriodTime = False
        Exit Function
    End If
    
    ' called in response to dragging a mode period event...
    Dim modeID As Integer, Color As Long, Text As String, Tag As Variant
    modeID = modePeriods(aIndex).modeID
    Color = modePeriods(aIndex).Color
    Text = modePeriods(aIndex).Text
    If (Not IsEmpty(modePeriods(aIndex).Tag)) Then
        Set LocalTag = modePeriods(aIndex).Tag
    End If
    Dim timeToDelete As Date
    timeToDelete = modePeriods(aIndex).PeriodTime
    DeleteModePeriod timeToDelete
    AddModePeriod NewPeriodTime, modeID, Color, Text, LocalTag
    RedrawGanttChart
    SetModePeriodTime = True
    Exit Function
ErrorLabel:
    ErrorHandler 1
End Function

Public Sub AddModePeriod(StartTime As Date, modeID As Integer, Color As Long, Text As String, Optional Tag As Variant)
    On Error GoTo ErrorLabel
    nModePeriods = nModePeriods + 1
    ReDim Preserve modePeriods(1 To nModePeriods)
    
    If (nModePeriods = 1) Then
        modePeriods(1).PeriodTime = StartTime
        modePeriods(1).modeID = modeID
        modePeriods(1).Color = Color
        modePeriods(1).Text = Text
        If Not IsMissing(Tag) Then Set modePeriods(1).Tag = Tag
    Else
        Dim wPeriod As Integer
        For wPeriod = (nModePeriods - 1) To 1 Step -1
            If (StartTime > modePeriods(wPeriod).PeriodTime) Then
                modePeriods(wPeriod + 1).PeriodTime = StartTime
                modePeriods(wPeriod + 1).modeID = modeID
                modePeriods(wPeriod + 1).Color = Color
                modePeriods(wPeriod + 1).Text = Text
                If Not IsMissing(Tag) And Not IsEmpty(Tag) Then Set modePeriods(wPeriod + 1).Tag = Tag
                Exit For
            Else
                modePeriods(wPeriod + 1) = modePeriods(wPeriod)
            End If
            
        Next wPeriod
        If (StartTime < modePeriods(1).PeriodTime) Then
            modePeriods(1).PeriodTime = StartTime
            modePeriods(1).modeID = modeID
            modePeriods(1).Color = Color
            modePeriods(1).Text = Text
            If Not IsMissing(Tag) Then Set modePeriods(1).Tag = Tag
        End If
    End If
       
    Exit Sub
ErrorLabel:
    ErrorHandler 2
End Sub

Public Sub DeleteModePeriod(modeTime As Date)
    On Error GoTo ErrorLabel
    If (nModePeriods > 0) Then
    
        Dim wPeriod As Integer
        For wPeriod = 1 To nModePeriods - 1
            If (modeTime - modePeriods(wPeriod).PeriodTime < 0.00001) Then
                modePeriods(wPeriod) = modePeriods(wPeriod + 1)
            End If
        Next wPeriod
        
        nModePeriods = nModePeriods - 1
        If (nModePeriods = 0) Then
            ReDim Preserve modePeriods(1 To 1)
        Else
            ReDim Preserve modePeriods(1 To nModePeriods)
        End If
    End If
    
    Exit Sub
ErrorLabel:
    ErrorHandler 3
End Sub

Public Sub DeleteAllModePeriods()
    On Error GoTo ErrorLabel
    nModePeriods = 0
    Exit Sub
ErrorLabel:
    ErrorHandler 4
End Sub

Public Function GetModePeriodData(Optional wDate As Variant, Optional ArrayIndex As Variant) As ModePeriodType
    On Error GoTo ErrorLabel
    Dim wPeriod As Integer
    
    If Not IsMissing(ArrayIndex) Then
        GetModePeriodData = modePeriods(ArrayIndex)
        Exit Function
    ElseIf Not IsMissing(wDate) Then
        wPeriod = GetModeArrayIndexFromDate(wDate)
        If (wPeriod <> -1) Then
            GetModePeriodData = modePeriods(wPeriod)
            Exit Function
        End If
    End If
    
    Exit Function
ErrorLabel:
    ErrorHandler 5
End Function

Public Function GetModeArrayIndexFromDate(ByVal wDate As Date)
    On Error GoTo ErrorLabel
    Dim wPeriod As Integer
    For wPeriod = nModePeriods To 1 Step -1
        If (modePeriods(wPeriod).PeriodTime - wDate < 0.00001) Then
            GetModeArrayIndexFromDate = wPeriod
            Exit Function
        End If
    Next wPeriod
    GetModeArrayIndexFromDate = -1
    Exit Function
ErrorLabel:
    ErrorHandler "GetModeArrayIndexFromDate"
End Function

Public Sub SetModePeriodData(Optional wDate As Variant, Optional ArrayIndex As Variant, Optional modeID As Variant, Optional Color As Variant, Optional Text As Variant, Optional Tag As Variant)
    On Error GoTo ErrorLabel
    Dim wPeriod As Integer, modeIndex As Integer
    modeIndex = -1
    
    If Not IsMissing(ArrayIndex) Then
        modeIndex = ArrayIndex
    ElseIf Not IsMissing(wDate) Then
        modeIndex = GetModeArrayIndexFromDate(modePeriods(wPeriod).PeriodTime)
    End If
    
    If modeIndex <> -1 Then
        If Not IsMissing(modeID) Then modePeriods(modeIndex).modeID = modeID
        If Not IsMissing(Color) Then modePeriods(modeIndex).Color = Color
        If Not IsMissing(Text) Then modePeriods(modeIndex).Text = Text
        If Not IsMissing(Tag) Then Set modePeriods(modeIndex).Tag = Tag
    End If
    Exit Sub
ErrorLabel:
    ErrorHandler 6
End Sub

Public Sub ClearAllRows()
    On Error GoTo ErrorLabel
    nBars = 0
    
    AdjustVScroll
    If (ganttModeBarStyle = FixedAtTop Or ganttModeBarStyle = Background) Then
        VScroll1.Max = 1
        firstVisibleBar = 1
    Else
        VScroll1.Max = 0
        firstVisibleBar = 0
    End If
    
    If (VScroll1.Value > VScroll1.Max) Then
        VScroll1.Value = VScroll1.Max
    End If
   
    ganttVScrollVisible = False
    PublicResize
    Exit Sub
ErrorLabel:
    ErrorHandler 7
End Sub

Public Sub SetRowStartEndTimes(StartTime As Date, EndTime As Date)
    On Error GoTo ErrorLabel
    If (wBarIsDragging > 0) Then
        Bars(wBarIsDragging).StartTime = StartTime
        Bars(wBarIsDragging).EndTime = EndTime
        RedrawGanttChart
    End If
    Exit Sub
ErrorLabel:
    ErrorHandler 8
End Sub

Public Sub AddRow(rowID As Integer, StartTime As Date, EndTime As Date, Color As Long, Optional Text As String, Optional Popuptext As String, Optional IsBlank As Boolean)
    On Error GoTo ErrorLabel
    nBars = nBars + 1
    If (nBars > nAllocatedBars) Then
        nAllocatedBars = nAllocatedBars + 10
        ReDim Preserve Bars(1 To nAllocatedBars)
    End If
    
    Bars(nBars).rowID = rowID
    Bars(nBars).StartTime = StartTime
    Bars(nBars).EndTime = EndTime
    Bars(nBars).Color = Color
    Bars(nBars).Text = Text
    Bars(nBars).Popuptext = Popuptext
    Bars(nBars).IsBlank = IsBlank
    
    If (nBars > nVisibleBars And nBars - 1 = nVisibleBars) Then
        ' the bar we just added created a need for a vertical scroll bar
        PublicResize
    Else
        AdjustVScroll
    End If
    
    Exit Sub
ErrorLabel:
    ErrorHandler 9
End Sub

Public Sub AddBlankRow(rowID As Integer)
    On Error GoTo ErrorLabel
    nBars = nBars + 1
    If (nBars > nAllocatedBars) Then
        nAllocatedBars = nAllocatedBars + 10
        ReDim Preserve Bars(1 To nAllocatedBars)
    End If
    Bars(nBars).IsBlank = True
    Bars(nBars).rowID = rowID
    
    If (nBars > nVisibleBars And nBars - 1 = nVisibleBars) Then
        ' the bar we just added created a need for a vertical scroll bar
        PublicResize
    Else
        AdjustVScroll
    End If
    
    Exit Sub
ErrorLabel:
    ErrorHandler 10
End Sub

Public Sub InsertRow(rowPosition As Integer, rowID As Integer, StartTime As Date, EndTime As Date, Color As Long, Optional Text As String, Optional Popuptext As String, Optional IsBlank As Boolean)
    On Error GoTo ErrorLabel
    nBars = nBars + 1
    If (nBars > nAllocatedBars) Then
        nAllocatedBars = nAllocatedBars + 10
        ReDim Preserve Bars(1 To nAllocatedBars)
    End If
    
    Dim wBar As Integer
        
    For wBar = nBars To (rowPosition + 1) Step -1
        Bars(wBar) = Bars(wBar - 1)
    Next
    
    Bars(rowPosition).rowID = rowID
    Bars(rowPosition).StartTime = StartTime
    Bars(rowPosition).EndTime = EndTime
    Bars(rowPosition).Color = Color
    Bars(rowPosition).Text = Text
    Bars(rowPosition).Popuptext = Popuptext
    Bars(rowPosition).IsBlank = IsBlank
    
    If (nBars > nVisibleBars And nBars - 1 = nVisibleBars) Then
        ' the bar we just added created a need for a vertical scroll bar
        PublicResize
    Else
        AdjustVScroll
    End If
    
    Exit Sub
ErrorLabel:
    ErrorHandler 11
End Sub

Public Sub DeleteRow(rowPosition As Integer)
    On Error GoTo ErrorLabel
    Dim wBar As Integer
    If (nBars > 0 And rowPosition > 0) Then
        For wBar = rowPosition To nBars - 1
            Bars(wBar) = Bars(wBar + 1)
        Next
        
        nBars = nBars - 1
        
        If (nBars <= nVisibleBars And nBars + 1 > nVisibleBars) Then
            ' the bar we just added removed the need for a vertical scroll bar
            If (ganttModeBarStyle = FixedAtTop Or ganttModeBarStyle = Background) Then
                firstVisibleBar = 1
            Else
                firstVisibleBar = 0
            End If
            PublicResize
        Else
            AdjustVScroll
        End If
    End If
    
    Exit Sub
ErrorLabel:
    ErrorHandler 12
End Sub

Private Sub SetCurModeIndex()
    On Error GoTo ErrorLabel
    ' this section of code sets the curModeIndex equal to the last index of
    ' the mode period which begins before ganttVisibleStartTime
    ' if no index begins before ganttVisibleStartTime, then it is set to 1
    If (nModePeriods > 0) Then
        If (modePeriods(nModePeriods).PeriodTime < ganttVisibleStartTime) Then
            curModeIndex = nModePeriods
        Else
            Dim wModePeriod As Integer
            curModeIndex = 1
            For wModePeriod = nModePeriods To 1 Step -1
                If (modePeriods(wModePeriod).PeriodTime < ganttVisibleStartTime) Then
                    curModeIndex = wModePeriod
                    Exit For
                End If
                
            Next
        End If
    End If
    Exit Sub
ErrorLabel:
    ErrorHandler 13
End Sub

Public Sub SetVerticalScrollBar(firstVisibleRow As Integer)
    On Error GoTo ErrorLabel
    If (firstVisibleRow > nBars) Then firstVisibleRow = nBars
    If (firstVisibleRow < 1) Then firstVisibleRow = 1
    
    If (ganttModeBarStyle = FixedAtTop Or ganttModeBarStyle = Background) Then
        firstVisibleBar = firstVisibleRow
    Else
        firstVisibleBar = firstVisibleRow - 1
    End If
          
    explicitScrollChange = True
    VScroll1.Value = firstVisibleBar
    explicitScrollChange = False
    RedrawGanttChart
    Exit Sub
ErrorLabel:
    ErrorHandler 14
End Sub

Private Sub SetVisibleStartTime(newDate As Date)
    On Error GoTo ErrorLabel
    If (InitializationComplete = False) Then Exit Sub
        
    If (newDate >= ganttStartTime) Then
        Dim onTheHour As Date
        If newDate > maxAllowableGanttVisibleStartTime Then
            newDate = maxAllowableGanttVisibleStartTime
        End If
        onTheHour = DateAdd("n", -Minute(newDate), newDate)
        onTheHour = DateAdd("s", -Second(onTheHour), onTheHour)
        ganttVisibleStartTime = onTheHour
        SetCurModeIndex
        Dim HourSpan As Long
        HourSpan = DateDiff("h", ganttStartTime, maxAllowableGanttVisibleStartTime)
        explicitScrollChange = True
        Dim hDiff As Long
        hDiff = DateDiff("h", ganttStartTime, ganttVisibleStartTime)
        If (HourSpan > 0) Then
            If (hDiff < 0) Then hDiff = 0
            HScroll1.Value = hDiff / HourSpan * HScroll1.Max
        Else
            ' we don't need a horizontal scroll bar anymore,
            ' but it should already be gone thanks to AdjustScrollSpeeds
        End If
        
        'explicitScrollChange = True
        'Dim newValue As Integer
        'newValue = DateDiff("h", ganttStartTime, ganttVisibleStartTime) * HScroll1.Max / HourSpan
        'If (newValue < HScroll1.Min) Then newValue = HScroll1.Min
        'HScroll1.Value = newValue
        'explicitScrollChange = False
        
        explicitScrollChange = False
        RedrawGanttChart
    End If
    Exit Sub
ErrorLabel:
    ErrorHandler 15
End Sub

Private Sub ChangeTime_Click()
    On Error GoTo ErrorLabel
    If TimeResolution > 2 Then
        TimeResolution = 1
    Else
        TimeResolution = TimeResolution + 1
    End If
    Exit Sub
ErrorLabel:
    ErrorHandler 16
End Sub

Private Sub HScroll1_Change()
    On Error GoTo ErrorLabel
    If (explicitScrollChange = False) Then
        Dim HourSpan As Long
        HourSpan = DateDiff("h", ganttStartTime, maxAllowableGanttVisibleStartTime)
        ganttVisibleStartTime = DateAdd("h", HourSpan / HScroll1.Max * HScroll1.Value, ganttStartTime)
        If (ganttVisibleStartTime > maxAllowableGanttVisibleStartTime) Then
            ganttVisibleStartTime = maxAllowableGanttVisibleStartTime
        End If
        SetCurModeIndex
        RedrawGanttChart
        ClosePopup
    End If
    Exit Sub
ErrorLabel:
    ErrorHandler 17
End Sub


Private Sub ModeFillStyle_Click()
    ModePeriodFillStyle = ModeFillStyle.ListIndex
End Sub

Private Sub ModeStyle_Click()
    ModeBarStyle = ModeStyle.ListIndex
End Sub

Private Sub UserControl_GotFocus()
    On Error GoTo ErrorLabel
    RaiseEvent GanttGotFocus
    DoEvents
    Exit Sub
ErrorLabel:
    ErrorHandler 18
End Sub

Private Sub UserControl_Hide()
    On Error GoTo ErrorLabel
    ' means visible property was set to false
    IsFormVisible = False
    Exit Sub
ErrorLabel:
    ErrorHandler 19
End Sub

Private Sub UserControl_LostFocus()
    On Error GoTo ErrorLabel
    RaiseEvent GanttLostFocus
    DoEvents
    Exit Sub
ErrorLabel:
    ErrorHandler 20
End Sub

Private Sub VScroll1_Scroll()
    On Error GoTo ErrorLabel
    firstVisibleBar = VScroll1.Value
    RedrawGanttChart
    Refresh
    If (NotifyDuringVScroll) Then
        If (ganttModeBarStyle = FixedAtTop Or ganttModeBarStyle = Background) Then
            RaiseEvent VerticalScrollChange(firstVisibleBar)
        Else
            RaiseEvent VerticalScrollChange(firstVisibleBar + 1)
        End If
        DoEvents
    End If
    Exit Sub
ErrorLabel:
    ErrorHandler 21
End Sub

Private Sub VScroll1_Change()
    On Error GoTo ErrorLabel
    firstVisibleBar = VScroll1.Value
    If (explicitScrollChange = False) Then
        RedrawGanttChart
        Refresh
        If (ganttModeBarStyle = FixedAtTop Or ganttModeBarStyle = Background) Then
            RaiseEvent VerticalScrollChange(firstVisibleBar)
        Else
            RaiseEvent VerticalScrollChange(firstVisibleBar + 1)
        End If
        DoEvents
        
    End If
    Exit Sub
ErrorLabel:
    ErrorHandler 22
End Sub

Private Sub GetMousePosInTwips(ByRef X As Integer, ByRef Y As Integer)
    On Error GoTo ErrorLabel
    Dim pos As POINTAPI
    GetCursorPos pos
    X = Screen.TwipsPerPixelX * pos.X
    Y = Screen.TwipsPerPixelY * pos.Y
    Exit Sub
ErrorLabel:
    ErrorHandler 23
End Sub

Private Sub HScroll1_Scroll()
    On Error GoTo ErrorLabel
    ' display a small window showing what time the user will move to if they
    ' stop scrolling
    Dim messageText As String
    Dim HourSpan As Long
    Dim currentTime As Date
    Dim prevValue As Integer
    prevValue = HScroll1.Value
    
    HourSpan = DateDiff("h", ganttStartTime, maxAllowableGanttVisibleStartTime)
    currentTime = DateAdd("h", HourSpan / HScroll1.Max * HScroll1.Value, ganttStartTime)
    messageText = FormatDateTime(currentTime, vbLongDate)
    DoPopup (messageText)
    Exit Sub
ErrorLabel:
    ErrorHandler 24
End Sub

Private Sub DoPopup(messageText As String)
    On Error GoTo ErrorLabel
    Dim xPos As Integer
    Dim yPos As Integer
    GetMousePosInTwips xPos, yPos
    yPos = yPos - 300
    If (IsPopupVisible = False) Then
        IsPopupVisible = True
        Set popupWindow = New PopupForm
        Set popupWindow.gChart = Me
        popupWindow.Left = xPos
        popupWindow.Top = yPos
        popupWindow.SetText messageText
        popupWindow.Show
        
    Else
        popupWindow.Left = xPos
        popupWindow.Top = yPos
        popupWindow.SetText messageText
    End If
    Exit Sub
ErrorLabel:
    ErrorHandler 25
End Sub

Private Sub ClosePopup()
    On Error GoTo ErrorLabel
    If (IsPopupVisible = True) Then
        IsPopupVisible = False
        Unload popupWindow
    End If
    Exit Sub
ErrorLabel:
    ErrorHandler 26
End Sub

Private Sub UserControl_Initialize()
    On Error GoTo ErrorLabel
    'The Initialize event occurs every time an instance of your control
    'is created or re-created. It is always the first event in a control
    'instance's lifetime.
    nAllocatedBars = 30
    ReDim Bars(1 To nAllocatedBars)
    
    IntervalStrings(1) = "h"
    IntervalStrings(2) = "h"
    IntervalStrings(3) = "d"
    IntervalStrings(4) = "ww"
    IntervalStrings(5) = "m"
    IntervalStrings(6) = "q"
    IntervalStrings(7) = "yyyy"
    IntervalsInPeriod(1) = 1
    IntervalsInPeriod(2) = 8
    IntervalsInPeriod(3) = 1
    IntervalsInPeriod(4) = 1
    IntervalsInPeriod(5) = 1
    IntervalsInPeriod(6) = 1
    IntervalsInPeriod(7) = 1
    
    FontName = "MS Sans Serif"
    FontSize = 12
    
    curModeIndex = 1
    ganttSelection.row = 0
    DoubleClickTimer.Interval = 300 'GetDoubleClickTime
    DoubleClickTimer.Enabled = False
    
    If (ganttModeBarStyle = FixedAtTop Or ganttModeBarStyle = Background) Then
        firstVisibleBar = 1
    Else
        firstVisibleBar = 0
    End If
    
    HScrollVisible = True
    
    
    Exit Sub
ErrorLabel:
    ErrorHandler 27
End Sub

Private Sub UserControl_InitProperties()
    On Error GoTo ErrorLabel
    'The InitProperties event occurs only in a control instance's first
    'incarnation, when an instance of the control is placed on a form.
    'In this event, you set the initial values of the control's properties.
    ganttPeriodWidth = 400
    ganttPeriodWidthMultiplier = 1#
    ganttHeaderHeight = 640
    ganttRowHeight = 315
    ganttTimeResolution = dayView
    ganttVisibleStartTime = "Jun-19-2001"
    ganttStartTime = "Jan-01-2000"
    ganttEndTime = "Dec-31-2009"
    ganttModeBarStyle = TopBar
    AddRow 1, "Jun-19-2001 8:00 AM", "Jun-22-2001 12:00 PM", RGB(255, 210, 210), "Process 1", "Take a nap"
    AddRow 2, "Jun-21-2001 8:00 AM", "Jun-25-2001 12:00 PM", RGB(255, 210, 210), "Process 2", "Play some cards"
    AddRow 3, "Jun-23-2001 8:00 AM", "Jun-29-2001 12:00 PM", RGB(210, 255, 210), "Process 3", "This one has no name"
    AddRow 4, "Jun-5-2001 8:00 AM", "Jul-29-2001 12:00 PM", RGB(210, 255, 180), "Process 4"
    AddRow 5, "Jul-1-2001 8:00 AM", "Aug-1-2001 12:00 PM", RGB(230, 255, 210), "Process 5"
    AddRow 6, "Jun-28-2001", "Jul-4-2001", RGB(210, 210, 230), "Fireworks sale - 6", "Just kidding"
    AddRow 1, "Jun-19-2001 8:00 AM", "Jun-22-2001 12:00 PM", RGB(255, 210, 210), "Process 7", "Take a nap"
    AddRow 2, "Jun-21-2001 8:00 AM", "Jun-25-2001 12:00 PM", RGB(255, 210, 210), "Process 8", "Play some cards"
    AddRow 3, "Jun-23-2001 8:00 AM", "Jun-29-2001 12:00 PM", RGB(210, 255, 210), "Process 9", "This one has no name"
    AddRow 4, "Jun-5-2001 8:00 AM", "Jul-29-2001 12:00 PM", RGB(210, 255, 180), "Process 10"
    AddRow 5, "Jul-1-2001 8:00 AM", "Aug-1-2001 12:00 PM", RGB(230, 255, 210), "Process 11"
    AddRow 6, "Jun-28-2001", "Jul-4-2001", RGB(210, 210, 230), "Fireworks sale - 12", "Just kidding"
    
    AddModePeriod "Jun-18-2001", 1, RGB(150, 0, 0), "Cool Shutdown"
    AddModePeriod "Jun-13-2001", 2, RGB(0, 150, 0), "Hot Shutdown"
    AddModePeriod "Jun-29-2001", 1, RGB(150, 0, 0), "Up all nite"
    AddModePeriod "May-31-2001", 1, RGB(150, 0, 0), "Normal operation"
    AddModePeriod "Jun-20-2001", 3, RGB(0, 0, 150), "Covert operation"
    
    ganttModePeriodBorderStyle = 1
    ganttModePeriodFillStyle = vbFSSolid
    Set ganttHeaderFont = New StdFont
    ganttHeaderFont.Name = "MS Sans Serif"
    ganttHeaderFont.Size = 12
    ganttHeaderFontColor = RGB(0, 0, 0)
    ganttHeaderGridColor = RGB(0, 0, 0)
    ganttHeaderColor = RGB(169, 189, 255)
    ganttChartBackgroundColor = RGB(255, 255, 255)
    Set ganttChartFont = New StdFont
    ganttChartFont.Name = "MS Sans Serif"
    ganttChartFont.Size = 12
    ganttChartBarOutlineColor = RGB(0, 0, 0)
    ganttChartHorizontalColor = RGB(180, 180, 180)
    ganttChartVerticalColor = RGB(230, 230, 230)
    ganttEnableDoubleClick = False
    'AdjustScrollSpeeds
    VScrollVisible = False
    NotifyDuringVScroll = True
    
    If (ganttModeBarStyle = FixedAtTop Or ganttModeBarStyle = Background) Then
        VScroll1.Min = 1
        If firstVisibleBar < 1 Then firstVisibleBar = 1
    Else
        VScroll1.Min = 0
        If firstVisibleBar < 0 Then firstVisibleBar = 0
    End If
    
    If VScroll1.Value < VScroll1.Min Then
        VScroll1.Value = VScroll1.Min
    End If

    Exit Sub
ErrorLabel:
    ErrorHandler 28
End Sub

Private Sub UserControl_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
    On Error GoTo ErrorLabel
    Dim wBar As Integer, wBarIndex As Integer, wBarPosition As Integer
    
    Dim mousetime As Date
    wBar = Int((mouseY - ganttHeaderHeight - useableTop) / ganttRowHeight)
    ' wBar is the physical position
    
    If ganttModeBarStyle = FixedAtTop Then
        ' draw the mode bar
        wBarIndex = wBar + firstVisibleBar - 1
        wBarPosition = wBarIsDragging - firstVisibleBar + 1
    Else
        wBarIndex = wBar + firstVisibleBar
        wBarPosition = wBarIsDragging - firstVisibleBar + 1
    End If
        
    If (mayStartDragging) Then
        ClosePopup
        isDragging = True
        Screen.MousePointer = 99
        Screen.MouseIcon = DraggingImage.Picture 'LoadPicture("icons\Dragging.cur")
    End If
    
    ' means that the mouse was clicked...
        
    ' wBarWasClicked is the index
    wBarWasClicked = wBarIndex
    If (ganttEnableDoubleClick) Then
        If (DoubleClickTimer.Enabled = True) Then
            ' kill double click timer
            DoubleClickTimer.Enabled = False
            RaiseEvent DblClick(wBarWasClicked)
            DoEvents
        Else
            ' start the single click timer
            DoubleClickTimer.Enabled = True
        End If
    Else
        RaiseEvent Click(wBarWasClicked)
        'Dim s As SelectionType
        's.row = wBarWasClicked
        's.sType = HasFocus
        'Selection = s
    End If
        
    Exit Sub
ErrorLabel:
    ErrorHandler 29
End Sub

Private Sub UserControl_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
    On Error GoTo ErrorLabel
    mouseX = X
    mouseY = Y
    'based on the y position of the mouse, are any bars present?
    Dim wBar As Integer, wBarIndex As Integer, wBarPosition As Integer
        
    Dim mousetime As Date
    
    wBar = Int((mouseY - ganttHeaderHeight - useableTop) / ganttRowHeight)
    ' wBar is the physical position
    
    If ganttModeBarStyle = FixedAtTop Then
        ' draw the mode bar
        wBarIndex = wBar + firstVisibleBar - 1
        wBarPosition = wBarIsDragging - firstVisibleBar + 1
    Else
        wBarIndex = wBar + firstVisibleBar
        wBarPosition = wBarIsDragging - firstVisibleBar + 1
    End If
    ' wBarIndex is the index of the bar over which the mouse is hovering
       
    mousetime = DateAdd("n", (X - useableLeft) * totalMinutes / useableWidth, ganttVisibleStartTime)
    mousetime = DateAdd("n", -Minute(mousetime), mousetime) ' remove any minutes from the time
    If (isDragging) Then
        ' if the user drags the mouse too close to the edge then begin
        ' scrolling automatically
        Dim newDate As Date
        If (mouseX < 200) Then
            ' scroll left
            newDate = DateAdd(IntervalStrings(ganttTimeResolution), -IntervalsInPeriod(ganttTimeResolution), ganttVisibleStartTime)
            ClosePopup
            SetVisibleStartTime (newDate)
                       
            'HScroll1.Value = HScroll1.Value - 1
            mousetime = DateAdd("n", X * totalMinutes / useableWidth, ganttVisibleStartTime)
            mousetime = DateAdd("n", -Minute(mousetime), mousetime) ' remove any minutes from the time
   
        ElseIf (mouseX > useableWidth - 200) Then
            ' scroll right
            newDate = DateAdd(IntervalStrings(ganttTimeResolution), IntervalsInPeriod(ganttTimeResolution), ganttVisibleStartTime)
            ClosePopup
            SetVisibleStartTime (newDate)
            
            mousetime = DateAdd("n", X * totalMinutes / useableWidth, ganttVisibleStartTime)
            mousetime = DateAdd("n", -Minute(mousetime), mousetime) ' remove any minutes from the time
   
        End If
        
        Dim startPos As Integer, endPos As Integer
        
        If (mayStartDragging = 3) Then
            DrawModeBar
            startPos = useableWidth * DateDiff("n", ganttVisibleStartTime, mousetime) / totalMinutes
            ForeColor = RGB(0, 0, 0)
            Line (startPos, useableTop + ganttHeaderHeight + 10)-(startPos, useableTop + ganttHeaderHeight + ganttRowHeight), , B
        Else
            'begin redrawing the bar
            If (mayStartDragging = 1) Then
                startPos = useableLeft + useableWidth * DateDiff("n", ganttVisibleStartTime, mousetime) / totalMinutes
            ElseIf (Bars(wBarIsDragging).StartTime <= ganttVisibleStartTime) Then
                startPos = useableLeft - Screen.TwipsPerPixelX
            Else
                startPos = useableLeft + useableWidth / totalMinutes * (DateDiff("n", ganttVisibleStartTime, Bars(wBarIsDragging).StartTime))
            End If
                
            If (mayStartDragging = 2) Then
                endPos = useableLeft + useableWidth * DateDiff("n", ganttVisibleStartTime, mousetime) / totalMinutes
            ElseIf (Bars(wBarIsDragging).EndTime >= ganttVisibleEndTime) Then
                endPos = useableRight
            Else
                endPos = useableLeft + useableWidth / totalMinutes * DateDiff("n", ganttVisibleStartTime, Bars(wBarIsDragging).EndTime)
            End If
            
            ' draw bar
            'clear bar area, draw hashes, then draw bar
            Dim leftPos As Integer, wPeriod As Integer, modeBarOffset
            
            If ganttModeBarStyle = FixedAtTop Then
                modeBarOffset = ganttRowHeight
            Else
                modeBarOffset = 0
            End If
                             
            FillStyle = vbFSSolid
            ForeColor = vbWindowBackground
            Line (useableLeft, useableTop + (wBarPosition - 1) * ganttRowHeight + ganttHeaderHeight + modeBarOffset + 15)-(useableRight - Screen.TwipsPerPixelX, useableTop + (wBarPosition) * ganttRowHeight + ganttHeaderHeight + modeBarOffset - 10), , BF
            ForeColor = ganttChartHorizontalColor
            Line (useableLeft, useableTop + wBarPosition * ganttRowHeight + ganttHeaderHeight + modeBarOffset)-(useableRight, useableTop + (wBarPosition) * ganttRowHeight + ganttHeaderHeight + modeBarOffset)
            wPeriod = 1
            Dim PeriodTime As Date, LastPeriodTime As Date
            PeriodTime = ganttVisibleStartTime
            leftPos = 1 - FractionInPeriod(PeriodTime) * ganttPeriodWidth
            ForeColor = ganttChartVerticalColor
            For leftPos = leftPos To (useableWidth) Step ganttPeriodWidth
                Line (useableLeft + leftPos + ganttPeriodWidth, useableTop + (wBarPosition - 1) * ganttRowHeight + ganttHeaderHeight + modeBarOffset + 10)-(useableLeft + leftPos + ganttPeriodWidth, useableTop + (wBarPosition) * ganttRowHeight + ganttHeaderHeight + modeBarOffset + 10)
                LastPeriodTime = PeriodTime
                PeriodTime = DateAdd(IntervalStrings(ganttTimeResolution), wPeriod * IntervalsInPeriod(ganttTimeResolution), ganttVisibleStartTime)
                wPeriod = wPeriod + 1
            Next leftPos
            ForeColor = RGB(0, 0, 0)
            FillColor = RGB(150, 255, 255)
            Line (startPos, useableTop + (wBarPosition - 1) * ganttRowHeight + ganttHeaderHeight + modeBarOffset + 10)-(endPos, useableTop + (wBarPosition) * ganttRowHeight + modeBarOffset + ganttHeaderHeight), , B
        End If
        
        ' display a small pop-up showing the end time of the drag
        Dim messageText As String
        If (ganttTimeResolution < weekView) Then
            messageText = FormatDateTime(mousetime)
        Else
            messageText = FormatDateTime(mousetime, vbLongDate)
        End If
        Refresh
        DoPopup messageText
        
    Else  ' we are not dragging anything...
        Dim testBlankArea As Boolean
        
        If (wBarIndex = 0 And ganttModeBarStyle = TopBar) Or (ganttModeBarStyle = FixedAtTop And wBar = 0) Then
            TestForMode mousetime
        ElseIf (wBarIndex >= 1 And wBarIndex <= nBars) Then
            If (Bars(wBarIndex).IsBlank = False) Then
                Dim diff As Double
                If (Abs(DateDiff("n", Bars(wBarIndex).StartTime, mousetime) / minutesInPeriod) < 0.25) Then
                    Screen.MousePointer = 99
                    Screen.MouseIcon = ResizeHorizontalImage.Picture 'LoadPicture("icons\ResizeHorizontal.cur")
                    mayStartDragging = 1
                    wBarIsDragging = wBarIndex
                    ' display a small pop-up showing the end time of the drag
                    If (ganttTimeResolution < weekView) Then
                        messageText = FormatDateTime(Bars(wBarIndex).StartTime)
                    Else
                        messageText = FormatDateTime(Bars(wBarIndex).StartTime, vbLongDate)
                    End If
                    DoPopup messageText
                ElseIf (Abs(DateDiff("n", Bars(wBarIndex).EndTime, mousetime) / minutesInPeriod) < 0.25) Then
                    Screen.MousePointer = 99
                    Screen.MouseIcon = ResizeHorizontalImage.Picture 'LoadPicture("icons\ResizeHorizontal.cur")
                    mayStartDragging = 2
                    wBarIsDragging = wBarIndex
                    ' display a small pop-up showing the end time of the drag
                    If (ganttTimeResolution < weekView) Then
                        messageText = FormatDateTime(Bars(wBarIndex).EndTime)
                    Else
                        messageText = FormatDateTime(Bars(wBarIndex).EndTime, vbLongDate)
                    End If
                    DoPopup messageText
                ElseIf (mousetime > Bars(wBarIndex).StartTime And mousetime < Bars(wBarIndex).EndTime) Then
                    If Bars(wBarIndex).Popuptext <> "" Then
                        DoPopup Bars(wBarIndex).Popuptext
                    End If
                    Screen.MousePointer = 1
                    mayStartDragging = 0
                Else
                    testBlankArea = True
                End If
            Else
                testBlankArea = True
            End If
        Else
            testBlankArea = True
        End If
        
        If testBlankArea Then
            If ganttModeBarStyle = Background Then
                ' now test to see which mode we are over, and if we are close
                ' to the mode boundary...
                TestForMode mousetime
            Else
                Screen.MousePointer = 1
                mayStartDragging = 0
                ClosePopup
            End If
        End If
                    
    End If
    Exit Sub
ErrorLabel:
    ErrorHandler 30
End Sub

Private Sub TestForMode(mousetime As Date)
    On Error GoTo ErrorLabel
    ' are we over any modes right now?
    Dim wModePeriod As Integer
    wModePeriod = curModeIndex
    If (nModePeriods > 0) Then
        Do
            If (Abs(DateDiff("n", modePeriods(wModePeriod).PeriodTime, mousetime) / minutesInPeriod) < 0.25) Then
                Screen.MousePointer = 99
                Screen.MouseIcon = ResizeHorizontalImage.Picture 'LoadPicture("icons\ResizeHorizontal.cur")
                mayStartDragging = 3
                wBarIsDragging = wModePeriod
                Exit Do
            ElseIf (mousetime < modePeriods(wModePeriod).PeriodTime Or wModePeriod = nModePeriods) Then
                If (mousetime < modePeriods(wModePeriod).PeriodTime) Then wModePeriod = wModePeriod - 1
                If (wModePeriod > 0) Then
                    DoPopup modePeriods(wModePeriod).Text & " begins at " & FormatDateTime(modePeriods(wModePeriod).PeriodTime)
                End If
                Screen.MousePointer = 1
                mayStartDragging = 0
                Exit Do
            End If
            wModePeriod = wModePeriod + 1
            If (wModePeriod > nModePeriods) Then Exit Do
        Loop
    End If
    Exit Sub
ErrorLabel:
    ErrorHandler 31
End Sub

Private Sub UserControl_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
    On Error GoTo ErrorLabel
    If (isDragging) Then
        ClosePopup
        mouseX = X
        If (mouseX < 0) Then mouseX = 0
        If (mouseX > useableWidth) Then mouseX = useableWidth
        mouseY = Y
    
        Dim mousetime As Date
           
        mousetime = DateAdd("n", (X - useableLeft) * totalMinutes / useableWidth, ganttVisibleStartTime)
        mousetime = DateAdd("n", -Minute(mousetime), mousetime) ' remove any minutes from the time
        
        ' a drag and drop operation has just completed.
        Screen.MousePointer = 0
        isDragging = False
        'wBarIsDragging is the bar that was dragged
        'mayStartDragging refers to which end of the bar was moved
        If (mayStartDragging = 3) Then
            Dim modeID As Integer, modeText As String, modePeriodTime As Date
            modeID = modePeriods(wBarIsDragging).modeID
            modeText = modePeriods(wBarIsDragging).Text
            modePeriodTime = modePeriods(wBarIsDragging).PeriodTime
            RaiseEvent ChangeModePeriodRequested(modeID, modeText, wBarIsDragging, mousetime, modePeriodTime)
            'SetModePeriodTime mousetime, , modePeriodTime
            
            DoEvents
        Else
            Dim proposedStartTime As Date, proposedEndTime As Date
                    
            If (mayStartDragging = 1) Then
                proposedStartTime = mousetime
                proposedEndTime = Bars(wBarIsDragging).EndTime
            ElseIf (mayStartDragging = 2) Then
                proposedStartTime = Bars(wBarIsDragging).StartTime
                proposedEndTime = mousetime
            Else
                ' this should not happen
            End If
            
            If proposedStartTime > proposedEndTime Then
                Dim tTime As Date
                tTime = proposedStartTime
                proposedStartTime = proposedEndTime
                proposedEndTime = tTime
            End If
            
            RaiseEvent ChangeRowRequested(Bars(wBarIsDragging).rowID, proposedStartTime, proposedEndTime, Bars(wBarIsDragging).StartTime, Bars(wBarIsDragging).EndTime)
            DoEvents
        End If
                        
        RedrawGanttChart
    End If
    Exit Sub
ErrorLabel:
    ErrorHandler 32
End Sub

Private Sub DoubleClickTimer_Timer()
    On Error GoTo ErrorLabel
    DoubleClickTimer.Enabled = False
    RaiseEvent Click(wBarWasClicked)
    DoEvents
    Exit Sub
ErrorLabel:
    ErrorHandler 33
End Sub

Private Sub AdjustVScroll()
    On Error GoTo ErrorLabel
    If (ganttModeBarStyle = FixedAtTop Or ganttModeBarStyle = Background Or ganttModeBarStyle = None) Then
        VScroll1.Max = nBars - nVisibleBars + 1
        If (VScroll1.Max <= 1) Then
            ganttVScrollVisible = False
            VScroll1.Max = 1
        ElseIf (VScroll1.Max > 1) Then
            ganttVScrollVisible = True
        End If
    Else
        VScroll1.Max = nBars - nVisibleBars
        If (VScroll1.Max <= 0) Then
            ganttVScrollVisible = False
            VScroll1.Max = 0
        ElseIf (VScroll1.Max > 0) Then
            ganttVScrollVisible = True
        End If
    End If
    'firstVisibleBar = VScroll1.Value
    explicitScrollChange = True
    If VScroll1.Value > VScroll1.Max Then
        VScroll1.Value = VScroll1.Max
    End If
    
    If firstVisibleBar > VScroll1.Value Then
        firstVisibleBar = VScroll1.Value
    End If
    explicitScrollChange = False

    VScroll1.SmallChange = 1
    Exit Sub
ErrorLabel:
    ErrorHandler 34
End Sub

Public Sub PublicResize()
    On Error GoTo ErrorLabel
    
    If Not InitializationComplete Then Exit Sub
    
    HScroll1.Top = UserControl.Height - HScroll1.Height - Screen.TwipsPerPixelY * 2
    HScroll1.Left = Screen.TwipsPerPixelX * 2
    
    If (ganttHScrollVisible = True) Then
        useableHeight = HScroll1.Top - Screen.TwipsPerPixelY * 2
    Else
        useableHeight = UserControl.Height - Screen.TwipsPerPixelY * 4
    End If
    
    Dim vHeight  As Integer
    
    If ganttModeBarStyle = FixedAtTop Or ganttModeBarStyle = TopBar Then
        nVisibleBars = Int((useableHeight - (ganttRowHeight + ganttHeaderHeight)) / ganttRowHeight)
    Else
        nVisibleBars = Int((useableHeight - ganttHeaderHeight) / ganttRowHeight)
    End If
    
    If (ganttVScrollVisible <> (nBars > nVisibleBars)) Then
        ' we need to add or remove the vertical scroll bar
        ganttVScrollVisible = (nBars > nVisibleBars)
        VScroll1.Visible = ganttVScrollVisible
        If Not ganttVScrollVisible Then
            SetVerticalScrollBar VScroll1.Min
        End If
    End If
    
    If (ganttVScrollVisible) Then
        AdjustVScroll
    End If
    
    If (ganttVScrollVisible = True) Then
        If UserControl.Width - VScroll1.Width - Screen.TwipsPerPixelX * 4 > 50 Then
            HScroll1.Width = UserControl.Width - VScroll1.Width - Screen.TwipsPerPixelX * 4
        End If
    Else
        If UserControl.Width - Screen.TwipsPerPixelX * 4 > 50 Then
            HScroll1.Width = UserControl.Width - Screen.TwipsPerPixelX * 4
        End If
    End If
    
    VScroll1.Top = Screen.TwipsPerPixelY * 2
    VScroll1.Left = UserControl.Width - VScroll1.Width - Screen.TwipsPerPixelX * 2
    If (ganttHScrollVisible = True) Then
        If UserControl.Height - HScroll1.Height - Screen.TwipsPerPixelY * 4 > 50 Then
            VScroll1.Height = UserControl.Height - HScroll1.Height - Screen.TwipsPerPixelY * 4
        End If
    Else
        If UserControl.Height - Screen.TwipsPerPixelY * 4 > 50 Then
            VScroll1.Height = UserControl.Height - Screen.TwipsPerPixelY * 4
        End If
    End If
    
    If (ganttVScrollVisible = True) Then
        useableWidth = VScroll1.Left - Screen.TwipsPerPixelX * 2
    Else
        useableWidth = UserControl.Width - Screen.TwipsPerPixelX * 4
    End If
      
    useableLeft = Screen.TwipsPerPixelX * 2
    useableRight = useableLeft + useableWidth
    useableTop = Screen.TwipsPerPixelY * 2
    useableBottom = useableTop + useableHeight
    
    Exit Sub
ErrorLabel:
    ErrorHandler 35
End Sub

Private Sub UserControl_Resize()
    On Error GoTo ErrorLabel
    'The Resize event occurs every time a control instance is re-created,
    'and every time it is resized — whether in design mode, by the
    'developer of a form, or at run time, in code. If your UserControl
    'object contains constituent controls, you arrange them in the event
    'procedure for this event, thus providing your control's appearance.

    PublicResize
    AdjustScrollSpeeds
    RedrawGanttChart
    
    Exit Sub
ErrorLabel:
    ErrorHandler 36
End Sub

Private Sub UserControl_Show()
    On Error GoTo ErrorLabel
    ' when the user changes the length of a bar, use this code
    VisibleStartTime = Now
    InitializationComplete = True
    PublicResize
    IsFormVisible = True
    AdjustScrollSpeeds
    RedrawGanttChart
    
    Exit Sub
ErrorLabel:
    ErrorHandler 37
End Sub

Public Sub RedrawGanttChart()
    On Error GoTo ErrorLabel
    ' redraw everything...
    Dim leftPos As Integer
    Dim Text As String
    Dim firstPeriodWidth As Integer
    Dim wPeriod As Integer
    Dim PeriodTime As Date, LastPeriodTime As Date
    
    If Not InitializationComplete Then Exit Sub
    If Not IsFormVisible Then Exit Sub
    
    If (HScroll1.Visible <> ganttHScrollVisible Or VScroll1.Visible <> ganttVScrollVisible) Then
        HScroll1.Visible = ganttHScrollVisible
        VScroll1.Visible = ganttVScrollVisible
    End If
    
    ForeColor = ganttChartBackgroundColor
    FillStyle = vbFSSolid
    Line (useableLeft, useableTop)-(useableRight, useableBottom), , BF
      
    ForeColor = ganttHeaderGridColor
    FillColor = ganttHeaderColor
    Line (useableLeft, useableTop)-(useableRight, useableTop + ganttHeaderHeight), , B
    Line (useableLeft, useableTop + ganttHeaderHeight / 2)-(useableRight, useableTop + ganttHeaderHeight / 2)
    
    wPeriod = 1
    firstPeriodWidth = 0
    PeriodTime = ganttVisibleStartTime
    leftPos = 1 - FractionInPeriod(PeriodTime) * ganttPeriodWidth
    
    Dim IsTopDifferent As Boolean
    
    For leftPos = leftPos To (useableWidth) Step ganttPeriodWidth
        ForeColor = ganttHeaderGridColor
        Line (useableLeft + leftPos + ganttPeriodWidth, useableTop + ganttHeaderHeight / 2)-(useableLeft + leftPos + ganttPeriodWidth, useableTop + ganttHeaderHeight)
        ForeColor = ganttChartVerticalColor
        Line (useableLeft + leftPos + ganttPeriodWidth, useableTop + ganttHeaderHeight + 10)-(useableLeft + leftPos + ganttPeriodWidth, useableBottom)
            
        LastPeriodTime = PeriodTime
        PeriodTime = DateAdd(IntervalStrings(ganttTimeResolution), wPeriod * IntervalsInPeriod(ganttTimeResolution), ganttVisibleStartTime)
        Text = BottomTime(LastPeriodTime, PeriodTime, IsTopDifferent)
        CurrentX = useableLeft + leftPos + (ganttPeriodWidth - TextWidth(Text)) / 2
        CurrentY = useableTop + ganttHeaderHeight / 2 + (ganttHeaderHeight / 2 - TextHeight(Text)) / 2
        ForeColor = ganttHeaderFontColor
        Print Text
        
        If (IsTopDifferent) Then
            Text = TopTime(PeriodTime)
            CurrentX = useableLeft + leftPos + ganttPeriodWidth + ganttPeriodWidth / 2
            CurrentY = useableTop + (ganttHeaderHeight / 2 - TextHeight(Text)) / 2
            Print Text
            Line (useableLeft + leftPos + ganttPeriodWidth, useableTop)-(useableLeft + leftPos + ganttPeriodWidth, useableTop + ganttHeaderHeight / 2)
            If (firstPeriodWidth = 0) Then
                firstPeriodWidth = leftPos + ganttPeriodWidth
            End If
        End If
        
        wPeriod = wPeriod + 1
    Next leftPos
         
    Text = TopTime(ganttVisibleStartTime)
    If (TextWidth(Text) < firstPeriodWidth - ganttPeriodWidth Or firstPeriodWidth = 0) Then
        CurrentX = useableLeft + ganttPeriodWidth / 2
        CurrentY = useableTop + (ganttHeaderHeight / 2 - TextHeight(Text)) / 2
        ForeColor = ganttHeaderFontColor
        Print Text
    End If
    
    Dim wBar As Integer
    Dim startPos As Integer
    Dim endPos As Integer
    Dim totalPeriods As Double
    Dim modeBarOffset As Integer
    
    ganttVisibleEndTime = DateAdd("n", totalMinutes, ganttVisibleStartTime)
    
    If ganttModeBarStyle = FixedAtTop Or (firstVisibleBar = 0 And ganttModeBarStyle = TopBar) Then
        modeBarOffset = ganttRowHeight
        DrawModeBar
    ElseIf ganttModeBarStyle = Background Then
        modeBarOffset = 0
        DrawModeBar
    Else
        modeBarOffset = 0
    End If
    
    
    
    Dim wBarPos As Integer
    Dim barTopPos As Integer
    Dim firstBarToDraw As Integer
       
    wBarPos = 1
    FillStyle = vbFSSolid
    
    If nBars > 0 Then
        For wBar = firstVisibleBar To nBars
            
            If (wBar = 0) Then wBar = 1 ' this means that ganttModeBarStyle = TopBar and we have just drawn the mode bar
            
            If (ganttSelection.row = wBar) Then
                If (ganttSelection.sType = HasFocus) Then
                    ForeColor = vbHighlight
                    Line (useableLeft - Screen.TwipsPerPixelX, useableTop + (wBarPos - 1) * ganttRowHeight + ganttHeaderHeight + modeBarOffset + 25)-(useableRight, useableTop + (wBarPos) * ganttRowHeight + ganttHeaderHeight + modeBarOffset - Screen.TwipsPerPixelY), , BF
                    ForeColor = vbYellow
                    DrawStyle = 5
                Else
                    ForeColor = vbHighlight
                End If
                FillStyle = vbFSTransparent
                Line (useableLeft - Screen.TwipsPerPixelX, useableTop + (wBarPos - 1) * ganttRowHeight + ganttHeaderHeight + modeBarOffset + 25)-(useableRight, useableTop + (wBarPos) * ganttRowHeight + ganttHeaderHeight + modeBarOffset - Screen.TwipsPerPixelY), , B
                
                FillStyle = vbFSSolid
                DrawStyle = vbSolid
            End If
            
            If (useableTop + (wBarPos - 1) * ganttRowHeight + ganttHeaderHeight + modeBarOffset > useableBottom) Then
                Exit For
            End If
            
            ForeColor = ganttChartHorizontalColor
            Line (useableLeft, useableTop + wBarPos * ganttRowHeight + ganttHeaderHeight + modeBarOffset)-(useableRight, useableTop + (wBarPos) * ganttRowHeight + ganttHeaderHeight + modeBarOffset)
            
            If Bars(wBar).IsBlank = False And _
               ((Bars(wBar).StartTime < ganttVisibleEndTime And Bars(wBar).StartTime >= ganttVisibleStartTime) Or _
               (Bars(wBar).EndTime <= ganttVisibleEndTime And Bars(wBar).EndTime > ganttVisibleStartTime) Or _
               (Bars(wBar).StartTime < ganttVisibleStartTime And Bars(wBar).EndTime > ganttVisibleEndTime)) Then
               
                If (Bars(wBar).StartTime <= ganttVisibleStartTime And Bars(wBar).EndTime > ganttVisibleStartTime) Then
                    startPos = useableLeft - Screen.TwipsPerPixelX
                Else
                    startPos = useableLeft + useableWidth / totalMinutes * DateDiff("n", ganttVisibleStartTime, Bars(wBar).StartTime)
                End If
                
                If (Bars(wBar).EndTime >= ganttVisibleEndTime) Then
                    endPos = useableRight
                Else
                    endPos = useableLeft + useableWidth / totalMinutes * DateDiff("n", ganttVisibleStartTime, Bars(wBar).EndTime)
                End If
                
                ' draw bar
                FillColor = Bars(wBar).Color
                ForeColor = ganttChartBarOutlineColor
                Line (startPos, useableTop + (wBarPos - 1) * ganttRowHeight + ganttHeaderHeight + modeBarOffset + 10)-(endPos, useableTop + (wBarPos) * ganttRowHeight + ganttHeaderHeight + modeBarOffset), , B
                
                If (Bars(wBar).Text <> "") Then
                    CurrentX = startPos + ganttPeriodWidth / 2
                    CurrentY = useableTop + (wBarPos - 1) * ganttRowHeight + ganttHeaderHeight + modeBarOffset + 10 + (ganttRowHeight - TextHeight(Bars(wBar).Text)) / 2
                    ForeColor = ganttChartBarOutlineColor
                    Print Bars(wBar).Text
                    'CurrentX = startPos + ganttPeriodWidth / 2 - Screen.TwipsPerPixelX
                    'CurrentY = useableTop + (wBar - 1) * ganttRowHeight + ganttHeaderHeight + modeBarOffset + 10 + (ganttRowHeight - TextHeight(Bars(wBar).text)) / 2 - Screen.TwipsPerPixelY
                    'ForeColor = RGB(255, 255, 255)
                    'Print Bars(wBar).text
                End If
            End If
            wBarPos = wBarPos + 1
                
        Next wBar
    End If
    
    'draw 3-d effects
    'BackColor = vbWindowBackground
    FillColor = vbWindowBackground
    FillStyle = vbFSTransparent
    Line (0, 0)-(Width - Screen.TwipsPerPixelX, Height - Screen.TwipsPerPixelY), vb3DHighlight, B 'vb3DLight - Screen.TwipsPerPixelY
    Line (0, 0)-(Width - Screen.TwipsPerPixelX, 0), vb3DShadow
    Line (0, 0)-(0, Height - Screen.TwipsPerPixelY), vb3DShadow
    Line (Screen.TwipsPerPixelX, Screen.TwipsPerPixelY)-(Width - Screen.TwipsPerPixelX * 2, Screen.TwipsPerPixelY), vb3DDKShadow
    Line (Screen.TwipsPerPixelX, Screen.TwipsPerPixelY)-(Screen.TwipsPerPixelY, Height - Screen.TwipsPerPixelY * 2), vb3DDKShadow
    Line (Screen.TwipsPerPixelX, Height - Screen.TwipsPerPixelY * 2)-(Width - Screen.TwipsPerPixelX * 2, Height - Screen.TwipsPerPixelY * 2), vb3DLight
    Line (Width - Screen.TwipsPerPixelX * 2, Screen.TwipsPerPixelY)-(Width - Screen.TwipsPerPixelX * 2, Height - Screen.TwipsPerPixelY), vb3DLight
    If (ganttHScrollVisible And ganttVScrollVisible) Then
        Line (VScroll1.Left, HScroll1.Top)-(Width - Screen.TwipsPerPixelX * 3, Height - Screen.TwipsPerPixelY * 3), vbScrollBars, BF
    End If
    Exit Sub
ErrorLabel:
    ErrorHandler 38
End Sub

Private Function DrawModeBar()
    On Error GoTo ErrorLabel
    Dim endPos As Integer, startPos As Integer, wModePeriod As Integer
    If Not IsFormVisible Then Exit Function
    If nModePeriods = 0 Then Exit Function
    
       
    If ganttModeBarStyle = FixedAtTop Or ganttModeBarStyle = TopBar Then
        ForeColor = ganttChartBarOutlineColor
        
        FillColor = vbWindowBackground
        FillStyle = vbFSSolid
        Line (useableLeft, useableTop + ganttHeaderHeight + 10)-(useableRight, useableTop + ganttRowHeight + ganttHeaderHeight), , B
        endPos = useableRight
        FillStyle = ganttModePeriodFillStyle
        For wModePeriod = curModeIndex To nModePeriods
            If (modePeriods(wModePeriod).PeriodTime < ganttVisibleEndTime) Then
                If (modePeriods(wModePeriod).PeriodTime < ganttVisibleStartTime) Then
                    startPos = useableLeft - Screen.TwipsPerPixelX
                Else
                    startPos = useableLeft + useableWidth / totalMinutes * (DateDiff("n", ganttVisibleStartTime, modePeriods(wModePeriod).PeriodTime))
                End If
                
                If ganttModePeriodBorderStyle = 0 Then
                    ForeColor = modePeriods(wModePeriod).Color
                End If
                
                FillColor = modePeriods(wModePeriod).Color
                Line (startPos, useableTop + ganttHeaderHeight + 25)-(endPos, useableTop + ganttRowHeight + ganttHeaderHeight - 15), , B
            Else
                Exit For
            End If
        Next
    ElseIf ganttModeBarStyle = Background Then
        For wModePeriod = nModePeriods To curModeIndex Step -1
            If modePeriods(wModePeriod).PeriodTime < ganttVisibleEndTime Then Exit For
        Next
        endPos = useableRight
        FillStyle = ganttModePeriodFillStyle
        For wModePeriod = wModePeriod To curModeIndex Step -1
            If (modePeriods(wModePeriod).PeriodTime < ganttVisibleEndTime) Then
                If (modePeriods(wModePeriod).PeriodTime < ganttVisibleStartTime) Then
                    startPos = useableLeft - Screen.TwipsPerPixelX
                Else
                    startPos = useableLeft + useableWidth / totalMinutes * (DateDiff("n", ganttVisibleStartTime, modePeriods(wModePeriod).PeriodTime))
                End If
                
                If ganttModePeriodBorderStyle = 0 Then
                    ForeColor = modePeriods(wModePeriod).Color
                End If
                
                FillColor = modePeriods(wModePeriod).Color
                Line (startPos, useableTop + ganttHeaderHeight + 25)-(endPos, useableBottom - 15), , B
            Else
                Exit For
            End If
            endPos = startPos
        Next
    
    End If
    Exit Function
ErrorLabel:
    ErrorHandler 39
End Function

Private Function BottomTime(time1 As Date, time2 As Date, ByRef TopIsDifferent As Boolean) As String
    On Error GoTo ErrorLabel
    Select Case ganttTimeResolution
    Case hourView:
        BottomTime = FormatDateTime(time1, vbShortTime)
        TopIsDifferent = (Hour(time2) = 0)
    Case shiftView:
        Dim nTime As Date, nTime2
        nTime = DateAdd("h", -(Hour(time1) Mod 8), time1)
        nTime2 = DateAdd("h", -(Hour(time2) Mod 8), time2)
        BottomTime = FormatDateTime(nTime, vbShortTime)
        TopIsDifferent = (Hour(nTime2) = 0)
    Case dayView:
        BottomTime = Day(time1)
        TopIsDifferent = (Weekday(time2) = 1)
    Case weekView:
        Dim wDayInWeek As Integer
        wDayInWeek = Weekday(time1) - 1
        Dim fDay1 As Date, fDay2 As Date
        fDay1 = DateAdd("d", -wDayInWeek, time1)
        fDay2 = DateAdd("d", -wDayInWeek, time2)
        BottomTime = MonthName(Month(fDay1), True) & " " & Day(fDay1)
        TopIsDifferent = (Month(fDay2) <> Month(fDay1))
    Case MonthView:
        BottomTime = MonthName(Month(time1), True)
        TopIsDifferent = (year(time2) <> year(time1))
    Case quarterView:
        BottomTime = MonthName(Int((Month(time1) - 1) / 3) * 3 + 1, True)
        TopIsDifferent = (year(time2) <> year(time1))
    Case yearView:
        BottomTime = year(time1)
        TopIsDifferent = False
    End Select
    Exit Function
ErrorLabel:
    ErrorHandler 40
End Function

Private Function TopTime(wDate As Date) As String
    On Error GoTo ErrorLabel
    Select Case ganttTimeResolution
    Case hourView:
        TopTime = MonthName(Month(wDate), True) & " " & Day(wDate) & ", " & year(wDate)
    Case shiftView:
        TopTime = MonthName(Month(wDate), True) & " " & Day(wDate) & ", " & year(wDate)
    Case dayView:
        TopTime = MonthName(Month(wDate), True) & " " & Day(wDate) & ", " & year(wDate)
    Case weekView:
        TopTime = MonthName(Month(wDate), True) & " " & year(wDate)
    Case MonthView:
        TopTime = year(wDate)
    Case quarterView:
        TopTime = year(wDate)
    Case yearView:
        TopTime = ""
    End Select
    Exit Function
ErrorLabel:
    ErrorHandler 41
End Function

Private Function FractionInPeriod(time1 As Date) As Single
    On Error GoTo ErrorLabel
    Select Case ganttTimeResolution
    Case hourView:
        FractionInPeriod = (Minute(time1) / 60#)
    Case shiftView:
        FractionInPeriod = (Hour(time1) Mod 8) / 8#
    Case dayView:
        FractionInPeriod = (Hour(time1) * 60# + Minute(time1)) / 1440#
    Case weekView:
        FractionInPeriod = (Hour(time1) * 60# + Minute(time1) + (Weekday(time1) - 1) * 1440#) / 10080#
    Case MonthView:
        FractionInPeriod = (Hour(time1) + (Day(time1) - 1) * 24#) / (DaysInMonth(year(time1), Month(time1)) * 24#)
    Case quarterView:
        Dim firstDayInQuarter As Date
        Dim firstDayNextQuarter As Date
        Dim totalMinutesThisQuarter As Long
        Dim minutesIntoQuarter As Long
        firstDayInQuarter = (DatePart("q", time1) - 1) * 3 + 1 & "/1/" & year(time1)
        firstDayNextQuarter = DateAdd("q", 1, firstDayInQuarter)
        totalMinutesThisQuarter = DateDiff("n", firstDayInQuarter, firstDayNextQuarter)
        minutesIntoQuarter = DateDiff("n", firstDayInQuarter, time1)
        FractionInPeriod = minutesIntoQuarter / totalMinutesThisQuarter '((DatePart("y", time1) - 1) Mod 92) / 92#
    Case yearView:
        FractionInPeriod = (DatePart("y", time1) - 1) / 365#
    End Select
    Exit Function
ErrorLabel:
    ErrorHandler 42
End Function

Private Function DaysInMonth(year As Integer, Month As Integer) As Integer
    On Error GoTo ErrorLabel
    Select Case Month
        Case 1, 3, 5, 7, 8, 10, 12
            DaysInMonth = 31
        Case 4, 6, 9, 11
            DaysInMonth = 30
        Case 2
            If ((year Mod 4 = 0 And year Mod 100 <> 0) Or year Mod 400 = 0) Then
                DaysInMonth = 29
            Else
                DaysInMonth = 28
            End If
    End Select
    Exit Function
ErrorLabel:
    ErrorHandler 43
End Function

Private Sub UserControl_Terminate()
    On Error GoTo ErrorLabel
    '
    Exit Sub
ErrorLabel:
    ErrorHandler 44
End Sub

Private Sub UserControl_WriteProperties(PropBag As PropertyBag)
    On Error GoTo ErrorLabel
    'The WriteProperties event occurs when a design-time instance of your
    'control is being destroyed, if at least one property value has changed.
    'In this event, you save all the property values a developer has set
    'for the control instance. The values are written to the in-memory copy
    'of the .frm file.

    PropBag.WriteProperty "RowHeight", ganttRowHeight
    PropBag.WriteProperty "TimeResolution", ganttTimeResolution
    PropBag.WriteProperty "HeaderHeight", ganttHeaderHeight
    PropBag.WriteProperty "VisibleStartTime", ganttVisibleStartTime
    PropBag.WriteProperty "PeriodWidth", ganttPeriodWidth
    PropBag.WriteProperty "StartTime", ganttStartTime
    PropBag.WriteProperty "EndTime", ganttEndTime
    PropBag.WriteProperty "VScrollVisible", ganttVScrollVisible
    PropBag.WriteProperty "HScrollVisible", ganttHScrollVisible
    PropBag.WriteProperty "HeaderColor", ganttHeaderColor
    PropBag.WriteProperty "HeaderFontColor", ganttHeaderFontColor
    PropBag.WriteProperty "HeaderGridColor", ganttHeaderGridColor
    PropBag.WriteProperty "ChartBackgroundColor", ganttChartBackgroundColor
    PropBag.WriteProperty "ChartHorizontalColor", ganttChartHorizontalColor
    PropBag.WriteProperty "ChartVerticalColor", ganttChartVerticalColor
    PropBag.WriteProperty "ChartBarOutlineColor", ganttChartBarOutlineColor
    PropBag.WriteProperty "NotifyDuringVScroll", ganttNotifyDuringVScroll
    PropBag.WriteProperty "HeaderFont", ganttHeaderFont
    PropBag.WriteProperty "ganttChartFont", ganttChartFont
    PropBag.WriteProperty "ModePeriodBorderStyle", ganttModePeriodBorderStyle
    PropBag.WriteProperty "ModePeriodFillStyle", ganttModePeriodFillStyle
    PropBag.WriteProperty "ModeBarStyle", ganttModeBarStyle
    PropBag.WriteProperty "EnableDoubleClick", ganttEnableDoubleClick
    Exit Sub
ErrorLabel:
    ErrorHandler 45
End Sub

Private Sub UserControl_ReadProperties(PropBag As PropertyBag)
    On Error GoTo ErrorLabel
    'The ReadProperties event occurs the second time a control instance
    'is created, and on all subsequent re-creations. In this event, you
    'retrieve the control instance's property values from the in-memory
    'copy of the .frm file belonging to the form the control was placed on.
  
    ChartStartTime = PropBag.ReadProperty("StartTime", "Jan-1-2000")
    ChartEndTime = PropBag.ReadProperty("EndTime", "Dec-31-2009")
    RowHeight = PropBag.ReadProperty("RowHeight", 315)
    TimeResolution = PropBag.ReadProperty("TimeResolution", dayView)
    HeaderHeight = PropBag.ReadProperty("HeaderHeight", 640)
    PeriodWidth = PropBag.ReadProperty("PeriodWidth", 1)
    VScrollVisible = PropBag.ReadProperty("VScrollVisible", True)
    HScrollVisible = PropBag.ReadProperty("HScrollVisible", True)
    VisibleStartTime = PropBag.ReadProperty("VisibleStartTime", Now)
    ganttHeaderColor = PropBag.ReadProperty("HeaderColor", RGB(169, 189, 255))
    ganttHeaderFontColor = PropBag.ReadProperty("HeaderFontColor", RGB(0, 0, 0))
    ganttHeaderGridColor = PropBag.ReadProperty("HeaderGridColor", RGB(0, 0, 0))
    ganttChartBackgroundColor = PropBag.ReadProperty("ChartBackgroundColor", RGB(255, 255, 255))
    ganttChartHorizontalColor = PropBag.ReadProperty("ChartHorizontalColor", RGB(180, 180, 180))
    ganttChartVerticalColor = PropBag.ReadProperty("ChartVerticalColor", RGB(230, 230, 230))
    ganttChartBarOutlineColor = PropBag.ReadProperty("ChartBarOutlineColor", RGB(0, 0, 0))
    ganttNotifyDuringVScroll = PropBag.ReadProperty("NotifyDuringVScroll", True)
    ganttModePeriodBorderStyle = PropBag.ReadProperty("ModePeriodBorderStyle", 0)
    ganttModePeriodFillStyle = PropBag.ReadProperty("ModePeriodFillStyle", vbFSSolid)
    ganttModeBarStyle = PropBag.ReadProperty("ModeBarStyle", TopBar)
    ganttEnableDoubleClick = PropBag.ReadProperty("EnableDoubleClick", False)
    If (ganttModeBarStyle = FixedAtTop Or ganttModeBarStyle = Background) Then
        VScroll1.Min = 1
        If firstVisibleBar < 1 Then firstVisibleBar = 1
    Else
        VScroll1.Min = 0
        If firstVisibleBar < 0 Then firstVisibleBar = 0
    End If
    
    If VScroll1.Value < VScroll1.Min Then
        VScroll1.Value = VScroll1.Min
    End If

    Dim defaultFont As StdFont
    Set defaultFont = New StdFont
    defaultFont.Name = "MS Sans Serif"
    defaultFont.Size = 12
    Set ganttHeaderFont = PropBag.ReadProperty("HeaderFont", defaultFont)
    Set ganttChartFont = PropBag.ReadProperty("ganttChartFont", defaultFont)
    
    Exit Sub
ErrorLabel:
    ErrorHandler 46
End Sub

Public Static Property Get RowHeight() As Variant
Attribute RowHeight.VB_ProcData.VB_Invoke_Property = ";Scale"
    On Error GoTo ErrorLabel
    RowHeight = ganttRowHeight
    Exit Property
ErrorLabel:
    ErrorHandler 47
End Property

Public Static Property Let RowHeight(ByVal vNewValue As Variant)
    On Error GoTo ErrorLabel
    ganttRowHeight = vNewValue
    PropertyChanged "rowheight"
    RedrawGanttChart
    Exit Property
ErrorLabel:
    ErrorHandler 48
End Property

Public Static Property Get TimeResolution() As Variant
Attribute TimeResolution.VB_ProcData.VB_Invoke_Property = "TimeResolutionPage;Appearance"
    On Error GoTo ErrorLabel
    TimeResolution = ganttTimeResolution
    
    Exit Property
ErrorLabel:
    ErrorHandler 49
End Property

Public Static Property Let TimeResolution(ByVal vNewValue As Variant)
    On Error GoTo ErrorLabel
    ganttTimeResolution = vNewValue
    AdjustScrollSpeeds
    PropertyChanged "TimeResolution"
    RedrawGanttChart
    
    Exit Property
ErrorLabel:
    ErrorHandler 50
End Property

Public Static Property Get VisibleStartTime() As Variant
Attribute VisibleStartTime.VB_Description = "Date visible at left side of gantt chart"
Attribute VisibleStartTime.VB_ProcData.VB_Invoke_Property = ";Data"
    On Error GoTo ErrorLabel
    VisibleStartTime = ganttVisibleStartTime
    
    Exit Property
ErrorLabel:
    ErrorHandler 51
End Property

Public Static Property Let VisibleStartTime(ByVal vNewValue As Variant)
    On Error GoTo ErrorLabel
      Dim sTime As Date
      sTime = vNewValue
      SetVisibleStartTime sTime
      PropertyChanged "VisibleStartTime"
      
    Exit Property
ErrorLabel:
    ErrorHandler 52
End Property

Public Static Property Get ChartStartTime() As Variant
Attribute ChartStartTime.VB_ProcData.VB_Invoke_Property = ";Data"
    On Error GoTo ErrorLabel
    ChartStartTime = ganttStartTime
    
    Exit Property
ErrorLabel:
    ErrorHandler 53
End Property

Public Static Property Let ChartStartTime(ByVal vNewValue As Variant)
    On Error GoTo ErrorLabel
    ganttStartTime = vNewValue
    
    If (ganttVisibleStartTime < ganttStartTime) Then
        ganttVisibleStartTime = ganttStartTime
        PropertyChanged "VisibleStartTime"
    End If
    AdjustScrollSpeeds
    RedrawGanttChart
    PropertyChanged "ChartStartTime"
    Exit Property
ErrorLabel:
    ErrorHandler 54
End Property

Public Static Property Get ChartEndTime() As Variant
Attribute ChartEndTime.VB_ProcData.VB_Invoke_Property = ";Data"
    On Error GoTo ErrorLabel
    ChartEndTime = ganttEndTime
    Exit Property
ErrorLabel:
    ErrorHandler 55
End Property

Public Static Property Let ChartEndTime(ByVal vNewValue As Variant)
    On Error GoTo ErrorLabel
    ganttEndTime = vNewValue
    AdjustScrollSpeeds
    PropertyChanged "ChartEndTime"
    Exit Property
ErrorLabel:
    ErrorHandler 56
End Property

Public Property Get PeriodWidth() As Variant
Attribute PeriodWidth.VB_ProcData.VB_Invoke_Property = ";Scale"
    On Error GoTo ErrorLabel
    PeriodWidth = ganttPeriodWidthMultiplier
    Exit Property
ErrorLabel:
    ErrorHandler 57
End Property

Public Property Let PeriodWidth(ByVal vNewValue As Variant)
    On Error GoTo ErrorLabel
    ganttPeriodWidthMultiplier = vNewValue
    AdjustScrollSpeeds
    PropertyChanged "PeriodWidth"
    RedrawGanttChart
    Exit Property
ErrorLabel:
    ErrorHandler 58
End Property

Public Static Property Get HeaderHeight() As Variant
Attribute HeaderHeight.VB_ProcData.VB_Invoke_Property = ";Position"
    On Error GoTo ErrorLabel
    HeaderHeight = ganttHeaderHeight
    Exit Property
ErrorLabel:
    ErrorHandler 59
End Property

Public Static Property Let HeaderHeight(ByVal vNewValue As Variant)
    On Error GoTo ErrorLabel
    ganttHeaderHeight = vNewValue
    PropertyChanged "HeaderHeight"
    RedrawGanttChart
    Exit Property
ErrorLabel:
    ErrorHandler 60
End Property

Public Static Property Get VScrollVisible() As Variant
    On Error GoTo ErrorLabel
    VScrollVisible = ganttVScrollVisible
    Exit Property
ErrorLabel:
    ErrorHandler 61
End Property

Public Static Property Let VScrollVisible(ByVal vNewValue As Variant)
    On Error GoTo ErrorLabel
    ganttVScrollVisible = vNewValue
    PropertyChanged "VScrollVisible"
    RedrawGanttChart
    Exit Property
ErrorLabel:
    ErrorHandler 62
End Property

Public Static Property Get HScrollVisible() As Variant
    On Error GoTo ErrorLabel
    HScrollVisible = ganttHScrollVisible
    Exit Property
ErrorLabel:
    ErrorHandler 63
End Property

Public Static Property Let HScrollVisible(ByVal vNewValue As Variant)
    On Error GoTo ErrorLabel
    ganttHScrollVisible = vNewValue
    PropertyChanged "HScrollVisible"
    RedrawGanttChart
    Exit Property
ErrorLabel:
    ErrorHandler 64
End Property

Private Sub AdjustScrollSpeeds()
    On Error GoTo ErrorLabel
    If Not InitializationComplete Then Exit Sub
    
    Select Case ganttTimeResolution
        Case hourView: ganttPeriodWidth = 800
        Case shiftView:  ganttPeriodWidth = 800
        Case dayView:   ganttPeriodWidth = 400
        Case weekView:  ganttPeriodWidth = 800
        Case MonthView:   ganttPeriodWidth = 600
        Case quarterView:  ganttPeriodWidth = 600
        Case yearView:  ganttPeriodWidth = 800
    End Select
    
    'ganttPeriodWidth = ganttPeriodWidth * ganttPeriodWidthMultiplier
    Dim HourSpan As Long, SmallChange As Integer
    Dim timeA As Date, timeB As Date
    Dim prevTotalMinutes As Long
      
    timeA = "Jan-1-2000"
    timeB = DateAdd(IntervalStrings(ganttTimeResolution), IntervalsInPeriod(ganttTimeResolution), timeA)
    
    If (ganttTimeResolution = MonthView) Then
        minutesInPeriod = 365 / 12 * 1440 ' minutes in an average month
    ElseIf (ganttTimeResolution = quarterView) Then
        minutesInPeriod = 365 / 4 * 1440 ' minutes in an average quarter
    Else
        minutesInPeriod = DateDiff("n", timeA, timeB)
    End If
    
    prevTotalMinutes = totalMinutes
    
    totalMinutes = minutesInPeriod / ganttPeriodWidth * useableWidth
    maxAllowableGanttVisibleStartTime = DateAdd("n", -totalMinutes, ganttEndTime)
    
    If (maxAllowableGanttVisibleStartTime < ganttStartTime) Then
        ' we don't need a horizontal scroll bar anymore
        maxAllowableGanttVisibleStartTime = ganttStartTime
        If (ganttVisibleStartTime > maxAllowableGanttVisibleStartTime) Then
            ganttVisibleStartTime = maxAllowableGanttVisibleStartTime
        End If
        
        If (ganttHScrollVisible = True) Then
            ganttHScrollVisible = False
            PublicResize
        End If
    Else
        If (ganttVisibleStartTime > maxAllowableGanttVisibleStartTime) Then
            ganttVisibleStartTime = maxAllowableGanttVisibleStartTime
        End If
        
        HourSpan = DateDiff("h", ganttStartTime, maxAllowableGanttVisibleStartTime)
        Dim scaleDown As Single
                       
        HScroll1.Min = 0
        If (HourSpan > 32767) Then
            scaleDown = HourSpan / 32767
            HScroll1.Max = 32767
        Else
            scaleDown = 1
            HScroll1.Max = HourSpan
        End If
        
        Select Case ganttTimeResolution
            Case hourView:  SmallChange = 1 / scaleDown
            Case shiftView:  SmallChange = 8 / scaleDown
            Case dayView: SmallChange = 24 / scaleDown
            Case weekView:  SmallChange = 72 / scaleDown
            Case MonthView:  SmallChange = 216 / scaleDown
            Case quarterView:   SmallChange = 864 / scaleDown
            Case yearView:  SmallChange = 864 * 4 / scaleDown
        End Select
        
        If SmallChange = 0 Then SmallChange = 1
        HScroll1.SmallChange = SmallChange
        HScroll1.LargeChange = HScroll1.SmallChange * 3
        
        If (ganttHScrollVisible = False) Then
            ganttHScrollVisible = True
            PublicResize
        End If
    End If
      
    If (prevTotalMinutes <> 0) Then
        ganttVisibleStartTime = DateAdd("n", (prevTotalMinutes - totalMinutes) / 2, ganttVisibleStartTime)
        If (ganttVisibleStartTime < ganttStartTime) Then
            ganttVisibleStartTime = ganttStartTime
        ElseIf (ganttVisibleStartTime > maxAllowableGanttVisibleStartTime) Then
            ganttVisibleStartTime = maxAllowableGanttVisibleStartTime
        End If
        
    End If
    SetVisibleStartTime (ganttVisibleStartTime)
    
    'explicitScrollChange = True
    'Dim newValue As Integer
    'newValue = DateDiff("h", ganttStartTime, ganttVisibleStartTime) * HScroll1.Max / HourSpan
    'If (newValue < HScroll1.Min) Then newValue = HScroll1.Min
    'HScroll1.Value = newValue
    'explicitScrollChange = False
        
    Exit Sub
ErrorLabel:
    ErrorHandler 65
End Sub

Public Property Get HeaderColor() As Variant
Attribute HeaderColor.VB_Description = "Color used to fill the header of the gantt chart"
Attribute HeaderColor.VB_ProcData.VB_Invoke_Property = "StandardColor;Appearance"
    HeaderColor = ganttHeaderColor
End Property

Public Property Let HeaderColor(ByVal vNewValue As Variant)
    ganttHeaderColor = vNewValue
    PropertyChanged "HeaderColor"
    RedrawGanttChart
End Property

Public Property Get HeaderFontColor() As Variant
Attribute HeaderFontColor.VB_Description = "color of the font used in the header, should contrast with the HeaderColor to make the text more readable"
Attribute HeaderFontColor.VB_ProcData.VB_Invoke_Property = "StandardColor;Appearance"
    HeaderFontColor = ganttHeaderFontColor
End Property

Public Property Let HeaderFontColor(ByVal vNewValue As Variant)
    ganttHeaderFontColor = vNewValue
    PropertyChanged "HeaderFontColor"
    RedrawGanttChart
End Property

Public Property Get HeaderGridColor() As Variant
Attribute HeaderGridColor.VB_ProcData.VB_Invoke_Property = "StandardColor;Appearance"
    HeaderGridColor = ganttHeaderGridColor
End Property

Public Property Let HeaderGridColor(ByVal vNewValue As Variant)
    ganttHeaderGridColor = vNewValue
    PropertyChanged "HeaderGridColor"
    RedrawGanttChart
End Property

Public Property Get ChartBackgroundColor() As Variant
Attribute ChartBackgroundColor.VB_ProcData.VB_Invoke_Property = "StandardColor;Appearance"
    ChartBackgroundColor = ganttChartBackgroundColor
End Property

Public Property Let ChartBackgroundColor(ByVal vNewValue As Variant)
    ganttChartBackgroundColor = vNewValue
    PropertyChanged "ChartBackgroundColor"
    RedrawGanttChart
End Property

Public Property Get ChartHorizontalColor() As Variant
Attribute ChartHorizontalColor.VB_ProcData.VB_Invoke_Property = "StandardColor;Appearance"
    ChartHorizontalColor = ganttChartHorizontalColor
End Property

Public Property Let ChartHorizontalColor(ByVal vNewValue As Variant)
    ganttChartHorizontalColor = vNewValue
    PropertyChanged "ChartHorizontalColor"
    RedrawGanttChart
End Property

Public Property Get ChartVerticalColor() As Variant
    ChartVerticalColor = ganttChartVerticalColor
End Property

Public Property Let ChartVerticalColor(ByVal vNewValue As Variant)
    ChartVerticalColor = vNewValue
    PropertyChanged "ChartVerticalColor"
    RedrawGanttChart
End Property

Public Property Get ChartBarOutlineColor() As Variant
Attribute ChartBarOutlineColor.VB_ProcData.VB_Invoke_Property = "StandardColor;Appearance"
    ChartBarOutlineColor = ganttChartBarOutlineColor
End Property

Public Property Let ChartBarOutlineColor(ByVal vNewValue As Variant)
    ganttChartBarOutlineColor = vNewValue
    PropertyChanged "ChartBarOutlineColor"
    RedrawGanttChart
End Property

Public Property Get HeaderFont() As Variant
Attribute HeaderFont.VB_Description = "Font used in chart header"
Attribute HeaderFont.VB_ProcData.VB_Invoke_Property = "StandardFont;Font"
    HeaderFont = ganttHeaderFont
End Property

Public Property Let HeaderFont(ByVal vNewValue As Variant)
    ganttHeaderFont = vNewValue
    PropertyChanged "HeaderFont"
    RedrawGanttChart
End Property

Public Property Get ChartFont() As Variant
Attribute ChartFont.VB_Description = "Font used to display text over bars"
Attribute ChartFont.VB_ProcData.VB_Invoke_Property = "StandardFont;Font"
    ChartFont = ganttChartFont
End Property

Public Property Let ChartFont(ByVal vNewValue As Variant)
    ganttChartFont = vNewValue
    PropertyChanged "ChartFont"
    RedrawGanttChart
End Property

Public Property Get NotifyDuringVScroll() As Variant
    NotifyDuringVScroll = ganttNotifyDuringVScroll
End Property

Public Property Let NotifyDuringVScroll(ByVal vNewValue As Variant)
    ganttNotifyDuringVScroll = vNewValue
    PropertyChanged "NotifyDuringVScroll"
End Property

Public Property Get Selection() As Variant
    Selection = ganttSelection
End Property

Public Property Let Selection(ByVal vNewValue As Variant)
    ganttSelection = vNewValue
    RedrawGanttChart
End Property

Public Property Get ModePeriodBorderStyle() As Variant
    ModePeriodBorderStyle = ganttModePeriodBorderStyle
End Property

Public Property Let ModePeriodBorderStyle(ByVal vNewValue As Variant)
    ganttModePeriodBorderStyle = vNewValue
    PropertyChanged "ModePeriodBorderStyle"
End Property

Public Property Get ModePeriodFillStyle() As Variant
    ModePeriodFillStyle = ganttModePeriodFillStyle
End Property

Public Property Let ModePeriodFillStyle(ByVal vNewValue As Variant)
    ganttModePeriodFillStyle = vNewValue
    PropertyChanged "ModePeriodFillStyle"
    RedrawGanttChart
End Property

Public Property Get ModeBarStyle() As Variant
    ModeBarStyle = ganttModeBarStyle
End Property

Public Property Let ModeBarStyle(ByVal vNewValue As Variant)
    On Error GoTo ErrorLabel
    ganttModeBarStyle = vNewValue
    
    If ganttModeBarStyle = FixedAtTop Or ganttModeBarStyle = TopBar Then
        nVisibleBars = Int((useableHeight - (ganttRowHeight + ganttHeaderHeight)) / ganttRowHeight)
    Else
        nVisibleBars = Int((useableHeight - ganttHeaderHeight) / ganttRowHeight)
    End If
    
    AdjustVScroll
    If (ganttModeBarStyle = FixedAtTop Or ganttModeBarStyle = Background) Then
        VScroll1.Min = 1
        If firstVisibleBar < 1 Then firstVisibleBar = 1
    Else
        VScroll1.Min = 0
        If firstVisibleBar < 0 Then firstVisibleBar = 0
    End If
    
    If VScroll1.Value < VScroll1.Min Then
        VScroll1.Value = VScroll1.Min
    End If

    RedrawGanttChart
    PropertyChanged "ModeBarStyle"
    Exit Property
ErrorLabel:
    ErrorHandler "ModeBarStyle"
End Property


'*********************************************************************************
' functions used during design and testing...
'*********************************************************************************

Private Sub ShowMode_Click()
    'HasModeBar = ShowMode.Value
End Sub

Private Sub AddRow_Click()
    AddRow 1, "Jul-1-2001", "Aug-1-2001", RGB(230, 230, 255), "Bar " & Str(nBars + 1), , 0
End Sub

Private Sub ClearAllRows_Click()
    ClearAllRows
End Sub

Private Sub Combo1_Click()
    'TimeResolution = Combo1.ListIndex + 1
    RedrawGanttChart
End Sub

Private Sub Command1_Click()
    'List1.Clear
    'Dim text As String
    'Dim wPeriod As Integer
    'For wPeriod = 1 To nModePeriods
    '    text = FormatDateTime(modePeriods(wPeriod).PeriodTime)
        'List1.AddItem text
    'Next
    'ChartStartTime = "Jan-01-2001"
    'ChartEndTime = "Dec-31-2001"
    'If (ganttTimeResolution = yearView) Then
    '    TimeResolution = hourView
    'Else
     '   TimeResolution = TimeResolution + 1
    'End If
    'If (ganttModeBarStyle = FixedAtTop) Then
    '    RaiseEvent VerticalScrollChange(firstVisibleBar)
    'Else
    '    RaiseEvent VerticalScrollChange(firstVisibleBar + 1)
    'End If
    'Dim i As Integer
    'For i = 1 To 20
    '    AddRow i, "Jun-1-2001", "Jul-1-2001", RGB(255, 230, 240), "Procedure " & i, "", False
    'Next i
    'RedrawGanttChart
    
    'Dim cSelection As SelectionType
    'If (Selection.row = 0) Then
    '    cSelection.row = 3
    '    cSelection.sType = LostFocus
    '    Selection = cSelection
    'Else
    '    cSelection.row = 0
    '    Selection = cSelection
    'End If
    '********************8
    'AddRow 1, "Jun-1-2001", "Jul-1-2001", RGB(255, 230, 240), "Procedure 1", "", False
    '***************
    'ClearAllRows
    '**********
    Height = 275
    
End Sub

Private Sub Command2_Click()
    'ClearAllRows
    'Dim i As Integer
    'For i = 1 To 6
    '    AddRow i, "Jun-1-2001", "Jul-1-2001", RGB(255, 230, 240), "Procedure " & i, "", False
    'Next i
    'RedrawGanttChart
    'DeleteRow 1
    '************

End Sub

Public Property Get EnableDoubleClick() As Variant
    EnableDoubleClick = ganttEnableDoubleClick
End Property

Public Property Let EnableDoubleClick(ByVal vNewValue As Variant)
    ganttEnableDoubleClick = vNewValue
    PropertyChanged "EnableDoubleClick"
End Property
