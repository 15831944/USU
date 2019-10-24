VERSION 5.00
Begin VB.UserControl DiagramControl 
   BackColor       =   &H8000000D&
   ClientHeight    =   3660
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   4530
   ClipBehavior    =   0  'None
   HasDC           =   0   'False
   KeyPreview      =   -1  'True
   ScaleHeight     =   244
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   302
   ToolboxBitmap   =   "RiskMap.ctx":0000
   Begin VB.Timer ScrollTimer 
      Enabled         =   0   'False
      Interval        =   40
      Left            =   120
      Top             =   120
   End
End
Attribute VB_Name = "DiagramControl"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit
Type POINTAPI
    x As Long
    y As Long
End Type

Type Point
    x As Integer
    y As Integer
End Type

Public Type RegionType
    Name As String
    Color As Long
    Center As Point
    CompID As Integer
    HasHighlight As Boolean
    Highlight1 As Point
    Highlight2 As Point
    HasSubDiagram As Boolean
    SubDiagramName As String
    IsSelected As Boolean
End Type

Public Type DiagramType
    SquareSize As Integer
    HasParent As Boolean
    parentFileName As String
    RegionCount As Integer
    Width As Integer
    Height As Integer
    xBox As Long
    yBox As Long
    Modified As Boolean
End Type

Public Enum FormModeType
    TestMode = 0
    DrawRegionsMode = 1
    SetCenterMode = 2
    EraseMode = 3
    drawHighlightMode = 4
End Enum

Public Enum RegionClickDefaultActionsType
    ActionRaiseClickEvent = 0
    ActionSelectRegion = 1
    ActionLoadSubDiagram = 2
End Enum
    
Private Declare Function GetCursorPos Lib "user32" (lpPoint As POINTAPI) As Long
Private Declare Function ScreenToClient Lib "user32" (ByVal hwnd As Long, lpPoint As POINTAPI) As Long

Private Const BorderScrollArea = 30 ' 100
Private Const maxScrollAmount = 40
Private Const minScrollAmount = 2
Private Const DefaultSquareSize = 8
' data that is dynamic
Private MouseX As Integer
Private MouseY As Integer
Private MouseIsDown As Boolean
Private PositionTop As Integer
Private PositionLeft As Integer
Public CurRegionIndex As Integer
Private MapData() As Byte
Private CurrentDiagram As DiagramType
Private Regions(0 To 255) As RegionType
' data that is saved / loaded to and from propbag
Private dFormMode As FormModeType
Private dDiagramFolder As String
Private dDiagramFileName As String
Public RegionA As Integer
Public RegionB As Integer
Attribute RegionB.VB_VarDescription = "0-Raise click event\r\n1-Select Region\r\n2-Load Sub-Diagram"
Private ImageLoaded As Boolean
' for help in drawing highlight...
Private DrawHighlight As Boolean
Private HighlightedRegion As Integer
Private HighlightStarted As Boolean
Private Highlight1 As Point
Private Highlight2 As Point
' for help in drawing selection
Private dRegionClickDefaultAction As RegionClickDefaultActionsType
Private dShowToolboxOnRightClick As Boolean

Public Event LeftClickRegion(RegionInfo As RegionType, RegionIndex As Integer, Shift As Integer)
Public Event RightClickRegion(RegionInfo As RegionType, RegionIndex As Integer, Shift As Integer)
Public Event MouseRegionChange(RegionIndex As Integer, Shift As Integer)
' this event is raised whenever the region that the mouse is over changes

Private ClientWidth As Integer
Private ClientHeight As Integer
Private RegionValidated As Boolean
Private Effects3dDrawn As Boolean
Private dAllowMultiSelection As Boolean
Private dSelectionCount As Integer
Dim dSelections(0 To 255) As Integer
Private currentMouseRegion As Integer
Private dShowDiagram As Boolean
Private dInitialDiagramFileName As String

Private Sub DoErrorMessage(subName As Variant)
    MsgBox "Error " & Err.Number & " '" & Err.Description & "' occured in " & subName & " in " & Err.Source
    Stop
End Sub

Public Function GetCurrentDiagram() As DiagramType
    GetCurrentDiagram = CurrentDiagram
End Function

Public Function GetRegionIDByCompID(CompID As Integer) As Integer
    On Error GoTo errorhandler
    On Error GoTo errorhandler
    Dim i As Integer
    For i = 1 To CurrentDiagram.RegionCount
        If Regions(i).CompID = CompID Then
            GetRegionIDByCompID = i
            Exit Function
        End If
    Next i
    GetRegionIDByCompID = 0
    Exit Function
errorhandler:
    DoErrorMessage "GetRegionIDByCompID"
End Function

Private Sub GetMousePosInTwips(ByRef x As Integer, ByRef y As Integer)
    On Error GoTo errorhandler
    On Error GoTo errorhandler
    Dim pos As POINTAPI
    GetCursorPos pos
    ScreenToClient UserControl.hwnd, pos
    x = pos.x 'Screen.TwipsPerPixelX * pos.X
    y = pos.y 'Screen.TwipsPerPixelY * pos.Y
    Exit Sub
errorhandler:
    DoErrorMessage "GetMousePosInTwips"
End Sub

Public Sub DrawOverlay() ' draw overlay
    On Error GoTo errorhandler
    Dim r As Integer, c As Integer, xpos As Integer, ypos As Integer
    For r = PositionTop / CurrentDiagram.SquareSize To Int((ScaleHeight + PositionTop) / CurrentDiagram.SquareSize)
        For c = PositionLeft / CurrentDiagram.SquareSize To Int((ScaleWidth + PositionLeft) / CurrentDiagram.SquareSize)
            If c >= 0 And c <= CurrentDiagram.xBox And r >= 0 And r <= CurrentDiagram.yBox Then
                If MapData(c, r) <> 0 Then
                    xpos = c * CurrentDiagram.SquareSize - PositionLeft
                    ypos = r * CurrentDiagram.SquareSize - PositionTop
                    FillColor = Regions(MapData(c, r)).Color
                    FillStyle = vbFSSolid
                    Line (xpos, ypos)-Step(CurrentDiagram.SquareSize, CurrentDiagram.SquareSize), RGB(0, 0, 0), B
                End If
            End If
        Next
    Next
    
    Dim i As Integer
    For i = 1 To CurrentDiagram.RegionCount
        If Regions(i).Center.x > PositionLeft And Regions(i).Center.x < PositionLeft + ScaleWidth And _
            Regions(i).Center.y > PositionTop And Regions(i).Center.y < PositionTop + ScaleHeight Then
            DrawCross Regions(i).Center.x, Regions(i).Center.y
        End If
    Next
    Exit Sub
errorhandler:
    DoErrorMessage "DrawOverlay"
End Sub

Private Sub DrawCross(xp As Integer, yp As Integer)
    Line (xp - 4 - PositionLeft, yp - 4 - PositionTop)-Step(8, 8), RGB(0, 0, 0)
    Line (xp + 4 - PositionLeft, yp - 4 - PositionTop)-Step(-8, 8), RGB(0, 0, 0)
End Sub

Private Sub Command1_Click()
    'ValidateDrawArea
    SetSelection 3, True
    'MsgBox "Selection made"
    SetSelection 5, True
    SetSelection 6, True
    SetSelection 5, False
End Sub

Private Sub ScrollTimer_Timer()
    ' we need to determine if the mouse is still within the scroll range
    GetMousePosInTwips MouseX, MouseY
    DoScrolling
End Sub

Public Sub SaveDiagram()
    On Error GoTo errorhandler
    Dim fileName As String, diagramDataName As String, regionDataName As String
    Dim wRegion As Integer
    
    ' dDiagramFileName
    fileName = dDiagramFolder & dDiagramFileName
    Dim dotPos As Long
    dotPos = InStr(1, fileName, ".")
    If dotPos = 0 Then
        MsgBox "Cannot save file.  Invalid file name: " & fileName
        Exit Sub
    End If
    
    CurrentDiagram.Modified = False
    diagramDataName = Mid$(fileName, 1, dotPos - 1) & " Diagram Data.txt"
    regionDataName = Mid$(fileName, 1, dotPos - 1) & " Region Data.dat"
            
    Open diagramDataName For Output As #1
    Write #1, CurrentDiagram.SquareSize
    Write #1, CurrentDiagram.HasParent
    Write #1, CurrentDiagram.parentFileName
    Write #1, CurrentDiagram.RegionCount
    For wRegion = 1 To CurrentDiagram.RegionCount
        Write #1, Regions(wRegion).Name, _
            Regions(wRegion).Color, _
            Regions(wRegion).Center.x, _
            Regions(wRegion).Center.y, _
            Regions(wRegion).Highlight1.x, _
            Regions(wRegion).Highlight1.y, _
            Regions(wRegion).Highlight2.x, _
            Regions(wRegion).Highlight2.y, _
            Regions(wRegion).CompID, _
            Regions(wRegion).HasHighlight, _
            Regions(wRegion).HasSubDiagram
            
        If Regions(wRegion).HasSubDiagram Then
            Write #1, Regions(wRegion).SubDiagramName
        End If
    Next
    Close #1
    dSelectionCount = 0
    
    Open regionDataName For Binary As #1
    Put #1, , MapData
    Close #1
    Exit Sub
errorhandler:
    DoErrorMessage "SaveDiagram"
End Sub

Private Function LoadDiagram() As Boolean
    On Error GoTo errorhandler
    Dim fileName As String, diagramDataName As String, regionDataName As String
    Dim DiagramDataFound As Boolean, RegionDataFound As Boolean, wRegion As Integer
    
    dShowDiagram = True
    LoadDiagram = True ' innocent until proven guilty
    
    If Len(dDiagramFolder) = 0 Or Len(dDiagramFileName) = 0 Then
     ' there is not a valid picture to be loaded
            'Dim fileSize As Long
    'fileSize = (xBox + 1) * (yBox + 1)
    'MsgBox "File size for map data will be " & fileSize & " bytes"
        DiagramProperties.Show vbModal, Me
        If DiagramProperties.result = True Then
            CurrentDiagram.SquareSize = DiagramProperties.Text3
            DiagramFolder = DiagramProperties.Text1
            DiagramFileName = DiagramProperties.Text2
        Else
            dShowDiagram = False
            LoadDiagram = False
        End If
        Exit Function
    End If
    
    fileName = dDiagramFolder & dDiagramFileName
    Dim dotPos As Long
    dotPos = InStr(1, fileName, ".")
    If dotPos = 0 Then
        LoadDiagram = False
        dShowDiagram = False
        Exit Function
    End If
        
    On Error GoTo NoPictureFound
    UserControl.Picture = LoadPicture(fileName)
    On Error GoTo errorhandler
    
    diagramDataName = Mid$(fileName, 1, dotPos - 1) & " Diagram Data.txt"
    regionDataName = Mid$(fileName, 1, dotPos - 1) & " Region Data.dat"
    DiagramToolbox.RegionCombo.Clear
    DiagramToolbox.EnableRegionWindow False
    
    On Error GoTo NoDiagramDataFound
    Open diagramDataName For Input As #1
    On Error GoTo errorhandler
    DiagramDataFound = True
    Input #1, CurrentDiagram.SquareSize
    Input #1, CurrentDiagram.HasParent
    Input #1, CurrentDiagram.parentFileName
    Input #1, CurrentDiagram.RegionCount
    
    For wRegion = 1 To CurrentDiagram.RegionCount
        Input #1, Regions(wRegion).Name, _
        Regions(wRegion).Color, _
        Regions(wRegion).Center.x, _
        Regions(wRegion).Center.y, _
        Regions(wRegion).Highlight1.x, _
        Regions(wRegion).Highlight1.y, _
        Regions(wRegion).Highlight2.x, _
        Regions(wRegion).Highlight2.y, _
        Regions(wRegion).CompID, _
        Regions(wRegion).HasHighlight, _
        Regions(wRegion).HasSubDiagram
        Regions(wRegion).IsSelected = False
        If Regions(wRegion).HasSubDiagram Then
            Input #1, Regions(wRegion).SubDiagramName
        End If
        DiagramToolbox.RegionCombo.AddItem Regions(wRegion).Name
    Next
    If CurrentDiagram.RegionCount > 0 Then
        DiagramToolbox.RegionCombo.ListIndex = 0
        DiagramToolbox.EnableRegionWindow True
    End If
NoDiagramDataFound:
    Close #1
    On Error GoTo errorhandler
    If Not DiagramDataFound Then
        CurrentDiagram.SquareSize = DefaultSquareSize
        CurrentDiagram.HasParent = False
        CurrentDiagram.parentFileName = ""
        CurrentDiagram.RegionCount = 0
    End If
            
    ClearSelections
    CurRegionIndex = 0
    currentMouseRegion = 0
    ImageLoaded = True
    CurrentDiagram.Modified = False
    PositionTop = 0
    PositionLeft = 0
    
    CurrentDiagram.Height = ScaleY(UserControl.Picture.Height, vbHimetric, vbPixels)
    CurrentDiagram.Width = ScaleX(UserControl.Picture.Width, vbHimetric, vbPixels)
    CurrentDiagram.xBox = Int(CurrentDiagram.Width / CurrentDiagram.SquareSize) + 1
    CurrentDiagram.yBox = Int(CurrentDiagram.Height / CurrentDiagram.SquareSize) + 1

    ReDim MapData(0 To CurrentDiagram.xBox, 0 To CurrentDiagram.yBox) As Byte
    
    If DiagramDataFound Then
        On Error GoTo NoRegionDataFound
        Open regionDataName For Binary As #1
        Get #1, , MapData
        On Error GoTo errorhandler
NoRegionDataFound:
        Close #1
    End If
    
    RegionValidated = False
    RedrawMap
    
    Exit Function
NoPictureFound:
    LoadDiagram = False
    Exit Function

errorhandler:
    DoErrorMessage "loaddiagram"
End Function

Private Sub DoScrolling()
    On Error GoTo errorhandler
    If MouseX < 0 Or MouseY < 0 Or MouseX > ClientWidth Or MouseY > ClientHeight Then
        ScrollTimer.Enabled = False
        Exit Sub
    End If
    
    Dim needRedraw As Boolean
      
    If MouseX < BorderScrollArea Then
        If (PositionLeft > 0) Then
            PositionLeft = PositionLeft - GetScrollAmount(BorderScrollArea - MouseX)
            If (PositionLeft < 0) Then PositionLeft = 0
            needRedraw = True
        End If
    ElseIf MouseX > ClientWidth - BorderScrollArea Then
        If (PositionLeft < CurrentDiagram.Width - ClientWidth) Then
            PositionLeft = PositionLeft + GetScrollAmount(MouseX - (ClientWidth - BorderScrollArea))
            If (PositionLeft > CurrentDiagram.Width - ClientWidth) Then
                PositionLeft = CurrentDiagram.Width - ClientWidth
            End If
            needRedraw = True
        End If
    End If
 
    If (MouseY < BorderScrollArea) Then
        If (PositionTop > 0) Then
            PositionTop = PositionTop - GetScrollAmount(BorderScrollArea - MouseY)
            If (PositionTop < 0) Then PositionTop = 0
            needRedraw = True
        End If
    ElseIf (MouseY > ClientHeight - BorderScrollArea) Then
        If (PositionTop < CurrentDiagram.Height - ClientHeight) Then
            PositionTop = PositionTop + GetScrollAmount(MouseY - (ClientHeight - BorderScrollArea))
            If (PositionTop > CurrentDiagram.Height - ClientHeight) Then
                PositionTop = CurrentDiagram.Height - ClientHeight
            End If
            needRedraw = True
        End If
    End If

    If (needRedraw) Then
        If (ScrollTimer.Enabled = False) Then
            ScrollTimer.Enabled = True
        End If
        RedrawMap
    Else
        ScrollTimer.Enabled = False
    End If
    Exit Sub
errorhandler:
    DoErrorMessage "DoScrolling"
End Sub

Private Function GetScrollAmount(position As Integer) As Integer
    If (position < 0) Then position = 0
    If (position > BorderScrollArea) Then position = BorderScrollArea
    GetScrollAmount = position * (maxScrollAmount - minScrollAmount) / BorderScrollArea + minScrollAmount
End Function

Private Sub UserControl_Initialize()
    Set DiagramToolbox.dObject = Me
End Sub

Private Sub UserControl_InitProperties()
    On Error GoTo errorhandler
    dFormMode = TestMode
    dRegionClickDefaultAction = ActionRaiseClickEvent
    dShowToolboxOnRightClick = True
    dAllowMultiSelection = True
    DiagramProperties.Show vbModal
    If DiagramProperties.result = True Then
        CurrentDiagram.SquareSize = DiagramProperties.Text3
        DiagramFolder = DiagramProperties.Text1
        InitialDiagramFileName = DiagramProperties.Text2
        DiagramFileName = InitialDiagramFileName
    End If
    Exit Sub
errorhandler:
    DoErrorMessage "GetRegionIDByCompID"
End Sub

Private Sub UserControl_MouseDown(Button As Integer, Shift As Integer, x As Single, y As Single)
    On Error GoTo errorhandler
    If Not dShowDiagram Then Exit Sub
    If Not InPicture(x, y) Then Exit Sub
    
    RegionA = FindRegion(x, y)
    
    If Button = 1 Then
        MouseX = x
        MouseY = y
        MouseIsDown = True
        
        If dFormMode = DrawRegionsMode And CurRegionIndex > 0 Then
            DrawTile
        ElseIf dFormMode = EraseMode And CurRegionIndex > 0 Then
            EraseTile
        ElseIf dFormMode = SetCenterMode And RegionA > 0 Then
        
            Regions(RegionA).Center.x = PositionLeft + x
            Regions(RegionA).Center.y = PositionTop + y
            DrawCross Regions(RegionA).Center.x, Regions(RegionA).Center.y
            If DiagramToolbox.IDBox = RegionA Then
                DiagramToolbox.CenterBox = "(" & PositionLeft + x & "," & PositionTop + y & ")"
            End If
            DiagramToolbox.SetCenter.Value = Unchecked
            CurrentDiagram.Modified = True
        ElseIf dFormMode = TestMode And RegionA > 0 Then
            If dRegionClickDefaultAction = ActionSelectRegion Then
                SetSelection RegionA, Not Regions(RegionA).IsSelected
            ElseIf dRegionClickDefaultAction = ActionLoadSubDiagram Then
                If Regions(RegionA).HasSubDiagram Then
                   DiagramFileName = Regions(RegionA).SubDiagramName
                End If
            Else
                RaiseEvent LeftClickRegion(Regions(RegionA), RegionA, Shift)
            End If
            'The shift argument is a bit field with the least-significant
            'bits corresponding to the SHIFT key (bit 0), the CTRL key
            '(bit 1), and the ALT key (bit 2 ). These bits correspond to
            'the values 1, 2, and 4, respectively.
        ElseIf dFormMode = drawHighlightMode Then
            HighlightedRegion = CurRegionIndex
            Regions(CurRegionIndex).Highlight1.x = PositionLeft + x
            Regions(CurRegionIndex).Highlight1.y = PositionTop + y
            HighlightStarted = True
            DrawHighlight = True
            CurrentDiagram.Modified = True
        End If
    Else
    'If CurRegionIndex > 0 Then DiagramToolbox.RegionCombo.Text = Regions(CurRegionIndex).Name
        RaiseEvent RightClickRegion(Regions(RegionA), RegionA, Shift)
        If RegionA > 0 Then DiagramToolbox.RegionCombo.ListIndex = RegionA - 1
        If dShowToolboxOnRightClick Then
            If App.NonModalAllowed Then
                DiagramToolbox.Show vbModeless, Me
            Else
                DiagramToolbox.Show vbModal, Me
            End If
        End If
    End If
    Exit Sub
errorhandler:
    DoErrorMessage "MouseDown"
End Sub

Private Function FindRegion(xpos As Variant, ypos As Variant) As Integer
    On Error GoTo errorhandler
    Dim x, y As Integer
    x = Int((PositionLeft + xpos) / CurrentDiagram.SquareSize)
    y = Int((PositionTop + ypos) / CurrentDiagram.SquareSize)
    If x < 0 Or x > CurrentDiagram.xBox Or y < 0 Or y > CurrentDiagram.yBox Then
        FindRegion = 0
    Else
        FindRegion = MapData(x, y)
    End If
    Exit Function
errorhandler:
    DoErrorMessage "FindRegion"
End Function

Private Sub UserControl_MouseMove(Button As Integer, Shift As Integer, x As Single, y As Single)
    On Error GoTo errorhandler
    If Not dShowDiagram Then Exit Sub
    If Not InPicture(x, y) Then Exit Sub
    
    MouseX = x
    MouseY = y
    If Not ScrollTimer.Enabled Then
        DoScrolling
    End If
    If dFormMode = DrawRegionsMode And CurRegionIndex > 0 And MouseIsDown Then
        DrawTile
    ElseIf dFormMode = EraseMode And MouseIsDown Then
        EraseTile
    ElseIf dFormMode = drawHighlightMode And HighlightStarted = True Then
        Regions(CurRegionIndex).Highlight2.x = PositionLeft + x
        Regions(CurRegionIndex).Highlight2.y = PositionTop + y
        RedrawMap
    ElseIf dFormMode = TestMode Then
        Dim wRegion As Integer
        wRegion = FindRegion(x, y)
        If wRegion <> currentMouseRegion Then
            currentMouseRegion = wRegion
            RaiseEvent MouseRegionChange(wRegion, Shift)
        End If
        If wRegion <> HighlightedRegion Then
            If wRegion > 0 Then
                DrawHighlight = True
            Else
                DrawHighlight = False
            End If
            HighlightedRegion = wRegion
            RedrawMap
        End If
        
    End If
    Exit Sub
errorhandler:
    DoErrorMessage "MouseMove"
End Sub

Private Sub DrawTile()
    On Error GoTo errorhandler
    Dim xpos As Integer, ypos As Integer
    xpos = MouseX - ((MouseX + PositionLeft) Mod CurrentDiagram.SquareSize) '(Screen.TwipsPerPixelX * SquareSize)
    ypos = MouseY - ((MouseY + PositionTop) Mod CurrentDiagram.SquareSize) '(Screen.TwipsPerPixelY * SquareSize)
    FillColor = Regions(CurRegionIndex).Color
    FillStyle = vbFSSolid
    Line (xpos, ypos)-Step(CurrentDiagram.SquareSize, CurrentDiagram.SquareSize), RGB(0, 0, 0), B
    MapData(Int((PositionLeft + xpos) / CurrentDiagram.SquareSize), Int((PositionTop + ypos) / CurrentDiagram.SquareSize)) = CurRegionIndex
    CurrentDiagram.Modified = True
    Exit Sub
errorhandler:
    DoErrorMessage "DrawTile"
End Sub

Private Sub EraseTile()
    On Error GoTo errorhandler
    Dim xpos, ypos, boardX, boardY As Integer
    xpos = MouseX - ((MouseX + PositionLeft) Mod CurrentDiagram.SquareSize) '(Screen.TwipsPerPixelX * SquareSize)
    ypos = MouseY - ((MouseY + PositionTop) Mod CurrentDiagram.SquareSize) '(Screen.TwipsPerPixelY * SquareSize)
    boardX = PositionLeft + xpos
    boardY = PositionTop + ypos
    Dim s As Integer
    s = CurrentDiagram.SquareSize + 1
'    UserControl.PaintPicture DiagramPicture, xpos, ypos, s, s, boardX, boardY, s, s, vbSrcCopy
    UserControl.PaintPicture UserControl.Picture, xpos, ypos, s, s, boardX, boardY, s, s, vbSrcCopy
    MapData(Int(boardX / CurrentDiagram.SquareSize), Int(boardY / CurrentDiagram.SquareSize)) = 0
    CurrentDiagram.Modified = True
    Exit Sub
errorhandler:
    DoErrorMessage "EraseTile"
End Sub

Private Sub UserControl_MouseUp(Button As Integer, Shift As Integer, x As Single, y As Single)
    On Error GoTo errorhandler
    If Not dShowDiagram Then Exit Sub
    If Not InPicture(x, y) Then Exit Sub
    
    MouseIsDown = False
    RegionB = FindRegion(x, y)
    
    If dFormMode = drawHighlightMode And HighlightStarted Then
        Regions(CurRegionIndex).Highlight2.x = PositionLeft + x
        Regions(CurRegionIndex).Highlight2.y = PositionTop + y
        RedrawMap
        HighlightStarted = False
        CurrentDiagram.Modified = True
    End If
    'If dFormMode = TestMode Then
    '    If RegionA = 0 Then
    '        MsgBox "Start region is invalid", vbInformation
    '    ElseIf RegionB = 0 Then
    '        MsgBox "End region is invalid"
    '    Else
    '        MsgBox "Drag and drop from " & Regions(RegionA).Name & " to " & Regions(RegionB).Name
    '    End If
    'End If
    Exit Sub
errorhandler:
    DoErrorMessage "UserControl_MouseUp"
End Sub

Private Function InPicture(ByVal x As Integer, ByVal y As Integer) As Boolean
    InPicture = (PositionTop + y <= CurrentDiagram.Height And PositionLeft + x <= CurrentDiagram.Width)
End Function

Private Sub UserControl_Paint()
    RedrawMap
    'If Not Effects3dDrawn Then
    Draw3DEffects
End Sub

Private Sub UserControl_ReadProperties(PropBag As PropertyBag)
    dDiagramFolder = PropBag.ReadProperty("DiagramFolder")
    dDiagramFileName = PropBag.ReadProperty("DiagramFileName")
    dFormMode = PropBag.ReadProperty("FormMode")
    dRegionClickDefaultAction = PropBag.ReadProperty("RegionClickDefaultAction")
    dShowToolboxOnRightClick = PropBag.ReadProperty("ShowToolboxOnRightClick")
    dInitialDiagramFileName = PropBag.ReadProperty("InitialDiagramFileName")
    dAllowMultiSelection = PropBag.ReadProperty("AllowMultiSelect")
    DiagramFileName = dInitialDiagramFileName
    'LoadDiagram
End Sub

Private Sub UserControl_Resize()
    RegionValidated = False
    RedrawMap
End Sub

Private Sub ValidateDrawArea()
    On Error GoTo errorhandler
    If ScaleWidth > CurrentDiagram.Width + 4 Then
        ClientWidth = CurrentDiagram.Width + 4
    Else
        ClientWidth = ScaleWidth - 4
    End If
    
    If ScaleHeight > CurrentDiagram.Height + 4 Then
        ClientHeight = CurrentDiagram.Height + 4
    Else
        ClientHeight = ScaleHeight - 4
    End If
    If ClientWidth < 1 Then ClientWidth = 1
    If ClientHeight < 1 Then ClientHeight = 1
    If PositionTop > CurrentDiagram.Height - ClientHeight Then PositionTop = CurrentDiagram.Height - ClientHeight
    If PositionLeft > CurrentDiagram.Width - ClientWidth Then PositionLeft = CurrentDiagram.Width - ClientWidth
    Effects3dDrawn = False
    RegionValidated = True
    Exit Sub
errorhandler:
    DoErrorMessage "ValidateDrawArea"
End Sub

Private Sub Draw3DEffects()
    On Error GoTo errorhandler
    'draw 3-d effects
    'BackColor = vbWindowBackground
    FillColor = vbWindowBackground
    FillStyle = vbFSTransparent
    Line (0, 0)-(ScaleWidth - 1, ScaleHeight - 1), vb3DHighlight, B
    Line (0, 0)-(ScaleWidth - 1, 0), vb3DShadow
    Line (0, 0)-(0, ScaleHeight - 1), vb3DShadow
    Line (1, 1)-(ScaleWidth - 2, 1), vb3DDKShadow
    Line (1, 1)-(1, ScaleHeight - 2), vb3DDKShadow
    Line (1, ScaleHeight - 2)-(ScaleWidth - 2, ScaleHeight - 2), vb3DLight
    Line (ScaleWidth - 2, 1)-(ScaleWidth - 2, ScaleHeight - 1), vb3DLight
    Effects3dDrawn = True
    Exit Sub
errorhandler:
    DoErrorMessage "Draw3DEffects"
End Sub

Private Sub UserControl_Show()
     RedrawMap
End Sub

Private Sub RedrawMap()
    On Error GoTo errorhandler
    If ImageLoaded And dShowDiagram Then
        If Not RegionValidated Then ValidateDrawArea
'        UserControl.PaintPicture DiagramPicture, 2, 2, , , PositionLeft, PositionTop, ClientWidth, ClientHeight, vbSrcCopy
        UserControl.PaintPicture UserControl.Picture, 2, 2, , , PositionLeft, PositionTop, ClientWidth, ClientHeight, vbSrcCopy
        If DrawHighlight Then
            FillStyle = vbFSTransparent
            Line (Regions(HighlightedRegion).Highlight1.x - PositionLeft, Regions(HighlightedRegion).Highlight1.y - PositionTop)-(Regions(HighlightedRegion).Highlight2.x - PositionLeft, Regions(HighlightedRegion).Highlight2.y - PositionTop), RGB(255, 255, 0), B
        End If
        Dim i As Integer
        FillStyle = vbFSTransparent
        For i = 1 To dSelectionCount
            Line (Regions(dSelections(i)).Highlight1.x - PositionLeft, Regions(dSelections(i)).Highlight1.y - PositionTop)-(Regions(dSelections(i)).Highlight2.x - PositionLeft, Regions(dSelections(i)).Highlight2.y - PositionTop), RGB(255, 0, 255), B
        Next i
    Else
        UserControl.Line (2, 2)-(2 + ClientWidth, 2 + ClientHeight), UserControl.BackColor, BF
    End If
    Draw3DEffects
    Exit Sub
errorhandler:
    DoErrorMessage "RedrawMap"
End Sub

Public Sub AddRegion(Optional RegionName As String = "", Optional CompID As Integer = 0)
    On Error GoTo errorhandler
    If CurrentDiagram.RegionCount < 254 Then
        If RegionName = "" Then RegionName = "Region " & CurRegionIndex
        RegionName = InputBox("Enter New Region Name", , RegionName)
        If RegionName = "" Then Exit Sub
        
        If DiagramToolbox.RegionFrame.Enabled = False Then DiagramToolbox.EnableRegionWindow True
        CurrentDiagram.RegionCount = CurrentDiagram.RegionCount + 1
        CurRegionIndex = CurrentDiagram.RegionCount
        Regions(CurRegionIndex).Name = RegionName
        Regions(CurRegionIndex).Color = RGB(Rnd * 200 + 50, Rnd * 200 + 50, Rnd * 200 + 50)
        Regions(CurRegionIndex).Center.x = 0
        Regions(CurRegionIndex).Center.y = 0
        Regions(CurRegionIndex).CompID = CompID
        Regions(CurRegionIndex).HasHighlight = False
        Regions(CurRegionIndex).HasSubDiagram = False
        Regions(CurRegionIndex).SubDiagramName = ""
        DiagramToolbox.RegionCombo.AddItem "Region" & CurRegionIndex
        CurrentDiagram.Modified = True
        SetRegionData CurRegionIndex, RegionName
        DiagramToolbox.RegionCombo.ListIndex = DiagramToolbox.RegionCombo.ListCount - 1
        
    End If
    Exit Sub
errorhandler:
    DoErrorMessage "AddRegion"
End Sub

Public Sub SetRegionData(RegionID As Integer, Optional Name As Variant, Optional Color As Variant, Optional Center As Variant, Optional CompID As Variant, Optional HasHighlight As Variant, Optional HasSubD As Variant, Optional SubDName As Variant)
    On Error GoTo errorhandler
    If Not IsMissing(Name) Then
        DiagramToolbox.RegionCombo.List(RegionID - 1) = Name
        Regions(RegionID).Name = Name
    End If
    If Not IsMissing(Color) Then Regions(RegionID).Color = Color
    If Not IsMissing(Center) Then Regions(RegionID).Center = Center
    If Not IsMissing(CompID) Then Regions(RegionID).CompID = CompID
    If Not IsMissing(HasHighlight) Then Regions(RegionID).HasHighlight = HasHighlight
    If Not IsMissing(HasSubD) Then Regions(RegionID).HasSubDiagram = HasSubD
    If Not IsMissing(SubDName) Then Regions(RegionID).SubDiagramName = SubDName
    CurrentDiagram.Modified = True
    Exit Sub
errorhandler:
    DoErrorMessage "SetRegionData"
End Sub

Public Function GetRegionData(RegionID As Integer) As RegionType
    On Error GoTo errorhandler
    GetRegionData = Regions(RegionID)
    Exit Function
errorhandler:
    DoErrorMessage "GetRegionData"
End Function

Public Sub CenterDiagram(RegionID As Integer)
    If RegionID < 1 Or RegionID > CurrentDiagram.RegionCount Then Exit Sub
    PositionLeft = Regions(RegionID).Center.x - ClientWidth / 2
    PositionTop = Regions(RegionID).Center.y - ClientHeight / 2
    If (PositionLeft < 0) Then PositionLeft = 0
    If (PositionLeft > CurrentDiagram.Width - ClientWidth) Then PositionLeft = CurrentDiagram.Width - ClientWidth
    If (PositionTop < 0) Then PositionTop = 0
    If (PositionTop > CurrentDiagram.Width - ClientHeight) Then PositionTop = CurrentDiagram.Height - ClientHeight
    RedrawMap
End Sub

Public Property Get DiagramFolder() As Variant
    DiagramFolder = dDiagramFolder
End Property

Public Property Let DiagramFolder(ByVal vNewValue As Variant)
    dDiagramFolder = vNewValue
    If Len(dDiagramFolder) > 0 Then
        If Mid(dDiagramFolder, Len(dDiagramFolder), 1) <> "\" Then
            dDiagramFolder = dDiagramFolder & "\"
        End If
    End If
    PropertyChanged "DiagramFolder"
End Property

Public Property Get DiagramFileName() As Variant
    DiagramFileName = dDiagramFileName
End Property

Public Property Let DiagramFileName(ByVal vNewValue As Variant)
    On Error GoTo errorhandler
    Dim pName As String
    pName = dDiagramFileName
    If CurrentDiagram.Modified = True Then
        If (MsgBox("Current diagram has changed.  Would you like to save the current diagram?", vbYesNo, "Save Diagram") = vbYes) Then
            SaveDiagram
        End If
    End If
    dDiagramFileName = vNewValue
    PropertyChanged "DiagramFileName"
    If LoadDiagram() = False Then
    dDiagramFileName = pName
        
    End If
    'If LoadDiagram() = True Then
    '    If pName <> "" Then
    '
    '    End If
    'End If
    Exit Property
errorhandler:
    DoErrorMessage "DiagramFileName"
End Property

Public Sub SetParentDiagram(HasParent As Boolean, parentFileName As String)
    If CurrentDiagram.HasParent <> HasParent Or CurrentDiagram.parentFileName <> parentFileName Then
        CurrentDiagram.HasParent = True
        CurrentDiagram.parentFileName = parentFileName
        CurrentDiagram.Modified = True
    End If
End Sub
Public Function LoadSubDiagram(RegionIndex As Integer)
    On Error GoTo errorhandler
    If Regions(RegionIndex).HasSubDiagram Then
        DiagramFileName = Regions(RegionIndex).SubDiagramName
        LoadSubDiagram = True
    End If
    LoadSubDiagram = False
    Exit Function
errorhandler:
    DoErrorMessage "LoadSubDiagram"
End Function

Public Sub ClearSelections()
    On Error GoTo errorhandler
    Dim i As Integer
    For i = 1 To dSelectionCount
        Regions(dSelections(i)).IsSelected = False
        SetSelection dSelections(i), False
    Next i
    dSelectionCount = 0
    RedrawMap
    Exit Sub
errorhandler:
    DoErrorMessage "ClearSelections"
End Sub

Public Function GetSelectionCount()
    GetSelectionCount = dSelectionCount
End Function

Public Function GetSelection(index As Integer)
    If index > dSelectionCount Then
        GetSelection = -1
    Else
        GetSelection = dSelections(index)
    End If
End Function

Public Sub SetSelection(index As Integer, selected As Boolean)
    On Error GoTo errorhandler
    ' the only difference between single select and multi select is than when
    ' the user wants to set a selection and multiSelect is false, then
    ' all current selections are cleared first
    
    If dAllowMultiSelection = False And dSelectionCount > 0 And selected = True Then
        ClearSelections
    End If
    
    If Regions(index).IsSelected <> selected Then
        If selected = True Then
            dSelectionCount = dSelectionCount + 1
            dSelections(dSelectionCount) = index
        Else
            Dim wSel As Integer
            For wSel = 1 To dSelectionCount - 1
                If dSelections(wSel) = index Then
                    dSelections(wSel) = dSelections(dSelectionCount)
                End If
            Next wSel
            dSelectionCount = dSelectionCount - 1
        End If
        Regions(index).IsSelected = selected
        RedrawMap
    End If
    Exit Sub
errorhandler:
    DoErrorMessage "SetSelection"
End Sub



Private Sub UserControl_Terminate()
    If CurrentDiagram.Modified = True Then
        If (MsgBox("The diagram has changed.  Would you like to save the current diagram?", vbYesNo, "Save Diagram") = vbYes) Then
            SaveDiagram
        End If
    End If
End Sub

Private Sub UserControl_WriteProperties(PropBag As PropertyBag)
    PropBag.WriteProperty "DiagramFolder", dDiagramFolder
    PropBag.WriteProperty "DiagramFileName", dDiagramFileName
    PropBag.WriteProperty "FormMode", dFormMode
    PropBag.WriteProperty "RegionClickDefaultAction", dRegionClickDefaultAction
    PropBag.WriteProperty "ShowToolboxOnRightClick", dShowToolboxOnRightClick
    PropBag.WriteProperty "InitialDiagramFileName", dInitialDiagramFileName
    PropBag.WriteProperty "AllowMultiSelect", dAllowMultiSelection
End Sub

Public Property Get FormMode() As Variant
Attribute FormMode.VB_Description = "Basically, this option controls how the form respons to mouse click events.\r\n0 - TestMode (Normal Mode)\r\n1 - DrawRegionsMode\r\n2 - SetCenterMode\r\n3 - EraseMode\r\n4 - DrawHighlightMode"
    FormMode = dFormMode
End Property

Public Property Let FormMode(ByVal vNewValue As Variant)
    If dFormMode <> vNewValue Then
        dFormMode = vNewValue
        If dFormMode = TestMode Then
            RedrawMap
        ElseIf dFormMode = DrawRegionsMode Then
            DiagramToolbox.Highlight.Value = Unchecked
            DiagramToolbox.SetCenter.Value = Unchecked
            DiagramToolbox.Eraser.Value = Unchecked
            DiagramToolbox.TestModeButton.Value = Unchecked
        End If
        
        PropertyChanged "FormMode"
    End If
End Property

Public Property Get ShowToolboxOnRightClick() As Variant
    ShowToolboxOnRightClick = dShowToolboxOnRightClick
End Property

Public Property Let ShowToolboxOnRightClick(ByVal vNewValue As Variant)
    dShowToolboxOnRightClick = vNewValue
     PropertyChanged "ShowToolboxOnRightClick"
End Property

Public Property Get RegionClickDefaultAction() As Variant
Attribute RegionClickDefaultAction.VB_Description = "0-Raise Click Event\r\n1-Select Region\r\n2-Load Sub-Diagram"
    RegionClickDefaultAction = dRegionClickDefaultAction
End Property

Public Property Let RegionClickDefaultAction(ByVal vNewValue As Variant)
     dRegionClickDefaultAction = vNewValue
     PropertyChanged "RegionClickDefaultAction"
End Property

Public Property Get AllowMultiSelect() As Variant
    AllowMultiSelect = dAllowMultiSelection
End Property

Public Property Let AllowMultiSelect(ByVal vNewValue As Variant)
    dAllowMultiSelection = vNewValue
    PropertyChanged "AllowMultiSelect"
End Property
Public Property Get ShowDiagram() As Variant
    ShowDiagram = dShowDiagram
End Property

Public Property Let ShowDiagram(ByVal vNewValue As Variant)
    If (vNewValue <> dShowDiagram) Then
        dShowDiagram = vNewValue
        RedrawMap
    End If
End Property

Public Property Get InitialDiagramFileName() As Variant
    InitialDiagramFileName = dInitialDiagramFileName
End Property

Public Property Let InitialDiagramFileName(ByVal vNewValue As Variant)
    dInitialDiagramFileName = vNewValue
    PropertyChanged "InitialDiagramFileName"
End Property
