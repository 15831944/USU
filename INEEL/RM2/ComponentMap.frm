VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{6ABB9000-48F8-11CF-AC42-0040332ED4E5}#4.0#0"; "SFTTREEX.OCX"
Object = "{FA9BBD85-B6A4-11D5-B022-0002E3059EB4}#2.0#0"; "DiagramControl.ocx"
Begin VB.Form ComponentMap 
   Caption         =   "Operational Hierarchy"
   ClientHeight    =   6930
   ClientLeft      =   2775
   ClientTop       =   4050
   ClientWidth     =   9210
   BeginProperty Font 
      Name            =   "Arial"
      Size            =   9.75
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   Icon            =   "ComponentMap.frx":0000
   LinkTopic       =   "Form1"
   NegotiateMenus  =   0   'False
   ScaleHeight     =   6930
   ScaleWidth      =   9210
   Begin SftTree.SftTree ComponentTree 
      Height          =   6015
      Left            =   120
      TabIndex        =   9
      Top             =   360
      Width           =   6255
      _Version        =   262144
      _ExtentX        =   11033
      _ExtentY        =   10610
      _StockProps     =   237
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Arial"
         Size            =   12
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BorderStyle     =   1
      Appearance      =   1
      Appearance      =   1
      BeginProperty ColHeaderFont {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Arial"
         Size            =   12
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BeginProperty RowHeaderFont {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BeginProperty ItemEditFont {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      GridStyle       =   3
      TreeLineColor   =   -2147483640
      Columns         =   4
      ColWidth0       =   67
      ColTitle0       =   "Operational Hierarchy"
      ColWidth1       =   67
      ColTitle1       =   "Immediate Base Comps"
      ColBmp1         =   "ComponentMap.frx":0442
      ColWidth2       =   67
      ColTitle2       =   "Total Base Comps"
      ColBmp2         =   "ComponentMap.frx":045E
      ColWidth3       =   67
      ColTitle3       =   "Has P&ID"
      ColBmp3         =   "ComponentMap.frx":047A
      AutoRespond     =   0   'False
      ColHeaderBackColor=   16760233
      Scrollbars      =   0
      RowColHeaderAppearance=   0
      LeftButtonOnly  =   0   'False
      RowHeaderStyle  =   192
      RowHeaderAppearance=   0
      ColPict1        =   "ComponentMap.frx":0496
      ColPict2        =   "ComponentMap.frx":04B2
      ColPict3        =   "ComponentMap.frx":04CE
      SplitterBar     =   -1  'True
      SplitColumn     =   1
      SplitterOffset  =   178
   End
   Begin DiagramControlProject.DiagramControl CompDiagram 
      Height          =   5535
      Left            =   120
      TabIndex        =   10
      Top             =   840
      Width           =   6255
      _ExtentX        =   11033
      _ExtentY        =   9763
      DiagramFolder   =   "C:\Program Files\RiskMonitor\pid\"
      DiagramFileName =   "NuclearPP.bmp"
      FormMode        =   0
      RegionClickDefaultAction=   0
      ShowToolboxOnRightClick=   -1  'True
      InitialDiagramFileName=   "NuclearPP.bmp"
      AllowMultiSelect=   -1  'True
   End
   Begin VB.CommandButton RemoveComponentButton 
      Caption         =   "Remove "
      Height          =   375
      Left            =   6600
      TabIndex        =   7
      Top             =   5520
      Width           =   2535
   End
   Begin VB.CommandButton UpLevelButton 
      Caption         =   "Up One Level"
      Enabled         =   0   'False
      Height          =   375
      Left            =   240
      TabIndex        =   4
      Top             =   360
      Width           =   2175
   End
   Begin VB.OptionButton OptionDiagramView 
      Caption         =   "Diagram View"
      Height          =   255
      Left            =   2880
      TabIndex        =   3
      Top             =   0
      Width           =   2415
   End
   Begin VB.OptionButton OptionHierarchyView 
      Caption         =   "Hierarchial View"
      Height          =   255
      Left            =   240
      TabIndex        =   2
      Top             =   0
      Value           =   -1  'True
      Width           =   2535
   End
   Begin VB.CommandButton OKButton 
      Caption         =   "OK"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   7560
      TabIndex        =   1
      Top             =   6480
      Width           =   1575
   End
   Begin VB.CommandButton EditHierarchy 
      Caption         =   "Hierarchy..."
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   120
      TabIndex        =   0
      Top             =   6480
      Width           =   1575
   End
   Begin MSComctlLib.ListView SelectedComponentList 
      Height          =   4935
      Left            =   6480
      TabIndex        =   6
      Top             =   360
      Width           =   2655
      _ExtentX        =   4683
      _ExtentY        =   8705
      View            =   3
      LabelEdit       =   1
      MultiSelect     =   -1  'True
      LabelWrap       =   -1  'True
      HideSelection   =   -1  'True
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
   Begin VB.Label Label1 
      Alignment       =   2  'Center
      Caption         =   "Selected Components"
      Height          =   375
      Left            =   6480
      TabIndex        =   8
      Top             =   0
      Width           =   2655
   End
   Begin VB.Label ComponentLabel 
      Caption         =   "Component:"
      Height          =   375
      Left            =   2760
      TabIndex        =   5
      Top             =   360
      Width           =   3615
   End
   Begin VB.Menu menu1 
      Caption         =   ""
      Visible         =   0   'False
      Begin VB.Menu menuItems 
         Caption         =   "(place holder)"
         Index           =   0
      End
   End
   Begin VB.Menu menu2 
      Caption         =   ""
      Begin VB.Menu menuItems2 
         Caption         =   "(place holder)"
         Index           =   0
      End
   End
End
Attribute VB_Name = "ComponentMap"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False


Option Explicit

Enum componentNodeType
    emptyNode = 0
    componentNode = 1
    baseComponentNode = 2
End Enum
    
Enum formModeType
    SelectOnly = 0
    Edit = 1
End Enum

Enum formViewType
    HiearchialView = 0
    DiagramView = 1
End Enum

Dim ActiveListIndex As Integer
Dim Node As componentNode
Dim nextCompID As Integer
Dim changesMade As Boolean

Public FormMode As formModeType
Public FormView As formViewType

Private menuActive As Boolean
Private selectedNodes As Collection
' the selectedNodes collection is used at form creation and destruction...
' when the form is created any node indexes stored in the collection are selected
' when the form is closed all selected indexes are stored in the collection
' while the form is open no changes are made to this collection

Public BaseDiagramFileName As String
' this file will point to the base diagram...


'Private TreeLoaded As Boolean
Public Function FindIndexByID(CompID As Integer) As Integer
    FindIndexByID = ComponentTree.FindItemData(0, CompID)
End Function

Public Function NodeData(Index As Integer) As componentNode
    Set NodeData = ComponentTree.ItemDataTag(Index)
End Function

Private Sub CompDiagram_LeftClickRegion(RegionInfo As DiagramControlProject.RegionType, RegionIndex As Integer, Shift As Integer)
    Dim Index As Integer
    If (Shift And 1) Or (Shift And 2) Then
        If FormMode = SelectOnly Then
            ' if the user holds down the shift key or ctrl key while clicking on a region...
            ' add to selections, otherwise go into sub diagram
            If RegionInfo.CompID > 0 Then
                Index = FindIndexByID(RegionInfo.CompID)
                If Index <> -1 Then
                    If NodeData(Index).IsSelected Then
                        RemoveSelection Index, False
                    Else
                        If Not RequestSelection(Index, True) Then
                            MsgBox RegionInfo.name & " could not be selected because it is selected by a parent component."
                        End If
                    End If
                    CompDiagram.SetSelection RegionIndex, NodeData(Index).IsSelected
                Else
                    MsgBox "Program error in ComponentMap"
                End If
            End If
        Else
            MsgBox "You may not select an object in edit mode."
        End If
    Else
        If RegionInfo.HasSubDiagram Then
            Dim pName As String
            pName = CompDiagram.DiagramFileName
            CompDiagram.LoadSubDiagram RegionIndex
            CompDiagram.SetParentDiagram True, pName
            SelectAllVisibleRegionsInDiagram
            If CompDiagram.GetCurrentDiagram().HasParent = False Then
                MsgBox "Error:  Diagram does not have parent diagram"
                UpLevelButton.Enabled = False
            Else
                UpLevelButton.Enabled = True
            End If
        End If
    End If
End Sub

Private Sub UpLevelButton_Click()
    CompDiagram.DiagramFileName = CompDiagram.GetCurrentDiagram().parentFileName
    SelectAllVisibleRegionsInDiagram
    UpLevelButton.Enabled = CompDiagram.GetCurrentDiagram().HasParent
    
End Sub

Private Sub SelectAllVisibleRegionsInDiagram()
    Dim listCount As Integer, Index As Integer
    listCount = ComponentTree.listCount
    CompDiagram.ClearSelections
    For Index = 0 To listCount - 1
        If NodeData(Index).IsSelected Then
            CompDiagram.SetSelection CompDiagram.GetRegionIDByCompID(NodeData(Index).ID), True
        End If
    Next Index
    
End Sub

Private Sub CompDiagram_MouseRegionChange(RegionIndex As Integer, Shift As Integer)
    If RegionIndex <> 0 Then
        'RegionLabel.Caption = "Region: " & CompDiagram.GetRegionData(RegionIndex).name
        Dim ID As Integer
        ID = CompDiagram.GetRegionData(RegionIndex).CompID
        ID = FindIndexByID(ID)
        If ID = -1 Then
            ComponentLabel.Caption = "Component: ?"
        Else
            ComponentLabel.Caption = "Component: " & NodeData(ID).name
        End If
     Else
        'RegionLabel.Caption = "Region: ?"
        ComponentLabel.Caption = "Component: ?"
     End If
End Sub

Private Sub ComponentTree_ItemClick(ByVal Index As Long, ByVal ColNum As Integer, ByVal AreaType As Integer, ByVal Button As Integer, ByVal Shift As Integer)
    ''add' does not need to set dataRow as chart will get redrawn
        'Index = MDIMain.Tree.AddItem(Name)
        'Set MDIMain.Tree.ItemPicture(Index) = MDIMain.nodePict1
        'MDIMain.Tree.ItemLevel(Index) = 1
    
    If (menuActive = True) Then
        menuActive = False
        Exit Sub
    End If
    
    ActiveListIndex = ComponentTree.ListIndex
    
    If (Button = 2) Then
        Select Case FormMode
        Case SelectOnly
            ShowSelectMenu
        Case Edit
            ShowEditMenu
        End Select
    Else ' button should be one...
        If AreaType = 3 Then
            'Expand or collapse item as needed
            ComponentTree.ItemExpand(Index) = Not ComponentTree.ItemExpand(Index)
            'MsgBox "Index=" & Index & " ActiveListIndex=" & ActiveListIndex
        ElseIf AreaType = 9 Or AreaType = 4 Then
            If (Shift And 1) Or (Shift And 2) Then
                If FormMode = SelectOnly And NodeData(ActiveListIndex).nodetype <> emptyNode Then
                    If NodeData(ActiveListIndex).IsSelected Then
                        RemoveSelection ActiveListIndex, True
                    Else
                        If Not RequestSelection(ActiveListIndex) Then
                            MsgBox "You may not select this node.  This node is inherently selected by a parent node.", vbInformation
                        End If
                    End If
                ElseIf FormMode = Edit Then
                    MsgBox "You may not select an object in edit mode."
                End If
            End If
        End If
    End If
    
End Sub

'*********************| Request Selection |******************************************
' This function selects a node (if not already selected by a parent)
' and removes selections from all children.
' It can also cause objects is the diagram control to become selected,
' and any parent items in the control to loose their selection
' Returns True if the object could be selected, False if the object could
' not be selected.
' This function does error checking on top of the change selection item function

Private Function RequestSelection(ListIndex As Integer, Optional selectDiagramObject As Boolean = True) As Boolean
    Dim isAParentSelected As Boolean, pID As Integer
    pID = ComponentTree.Object.Parent(ListIndex)
    Do While pID <> -1
        If NodeData(pID).IsSelected Then isAParentSelected = True
        pID = ComponentTree.Object.Parent(pID)
    Loop
    
    If isAParentSelected Then
        RequestSelection = False
        If NodeData(ListIndex).IsSelected Then
            ChangeSelectionItem ListIndex, False, selectDiagramObject
            ' really it should already be false
            MsgBox "why is it selected?"
        End If
        Exit Function
    Else
        ChangeSelectionItem ListIndex, True, selectDiagramObject
        RequestSelection = True
        ' make sure all visible children are not selected
        Dim aRow As Integer
        aRow = ListIndex + 1
        Do While (NodeData(aRow).nodetype <> emptyNode And NodeData(aRow).hLevel > NodeData(ListIndex).hLevel)
            If NodeData(aRow).IsSelected = True Then
                ChangeSelectionItem aRow, False, selectDiagramObject
            End If
            aRow = aRow + 1
        Loop
    End If
End Function

Private Sub RemoveSelection(ListIndex As Integer, Optional DeselectDiagramObject As Boolean = True)
    ChangeSelectionItem ListIndex, False, DeselectDiagramObject
End Sub

Private Sub ChangeSelectionItem(treeRowIndex As Integer, SelectItem As Boolean, Optional selectDiagramObject As Boolean = True)
    ' The purpose of this subroutine is to turn the selection for an item on or
    ' off in the tree and diagram control, as well as add or remove it from the
    ' selected components list
    ' Do not call this directly.  It is only called from RemoveSelection or RequestSelection
    If NodeData(treeRowIndex).IsSelected = SelectItem Then
        MsgBox "Error: ChangeSelectionItem called to change state of item to previous state."
        Exit Sub
    End If
    
    Dim regionID As Integer, CompID As Integer, ListIndex As Integer
    CompID = NodeData(treeRowIndex).ID
    NodeData(treeRowIndex).IsSelected = SelectItem
    
    ' try and find the item
    Dim itemFound As Boolean, i As Integer
    itemFound = False
    For i = 1 To SelectedComponentList.ListItems.Count
        If SelectedComponentList.ListItems.Item(i).tag = treeRowIndex Then
            itemFound = True
            ListIndex = i
            Exit For
        End If
    Next i
    
    If SelectItem Then
        If Not itemFound Then
            Dim lItem As ListItem
            Set lItem = SelectedComponentList.ListItems.Add(, , NodeData(treeRowIndex).name)
            lItem.tag = treeRowIndex
        Else
            MsgBox "error... line 223 in ComponentMap"
        End If
    Else
        If itemFound Then
            SelectedComponentList.ListItems.Remove ListIndex
        End If
    End If
    
    If selectDiagramObject = True Then
        ' we need to test for this because if this entire event is generated because
        ' the diagram is clicked and an object is selected we do not want to
        ' set a selection over again and start a non-terminating cycle
        regionID = CompDiagram.GetRegionIDByCompID(CompID)
        If regionID <> 0 Then
            ' this region is in the current diagram
            CompDiagram.SetSelection regionID, SelectItem
        End If
    End If
End Sub

Public Sub ClearSelectedNodes()
    Dim i As Integer
    ' item tag specifies which SftTree Index
    CompDiagram.ClearSelections
    For i = 1 To SelectedComponentList.ListItems.Count
        RemoveSelection SelectedComponentList.ListItems(i).tag, False
    Next i
    'the way this function works needs to be changed
End Sub

Public Function GetSelectedCount() As Integer
    GetSelectedCount = SelectedComponentList.ListItems.Count
End Function

Public Function GetSelectedIndex(Index As Integer) As Integer
    GetSelectedIndex = SelectedComponentList.ListItems(Index).tag
End Function

Public Function GetSelectedNode(Index As Integer) As componentNode
    Set GetSelectedNode = NodeData(SelectedComponentList.ListItems(Index).tag)
End Function

Public Sub SetSelectedNode(Index As Integer, State As Boolean)
    If State <> NodeData(Index).IsSelected Then
        If State = True Then
            RequestSelection Index, True
        Else
            RemoveSelection Index, True
        End If
    End If
End Sub
Private Sub Form_Initialize()
    'Set selectedNodes = New Collection
End Sub

Private Sub ShowEditMenu()
    ' determine what can be done at this location and present the options
    ' to the user in a pop-up menu
    ' 1.  If the user has clicked on the empty row, they can
    '       New Node
    ' 2.  If the user has clicked on a non-empty row, they can
    '       New Sibling Node
    '       New Child Node (* except for the bottom level of hierarchy)
    '       Add Base Component
    
    If (ActiveListIndex = -1) Then
        'PopupMenu menu1
    Else
        If (NodeData(ActiveListIndex).nodetype = emptyNode) Then
            menuActive = True
            menuItems(1).Caption = "New Node"
            menuItems(1).Enabled = True
            menuItems(2).Enabled = False
            menuItems(3).Enabled = False
            menuItems(4).Enabled = False
            menuItems(5).Enabled = False
            menuItems(6).Enabled = False
            menuItems(7).Enabled = False
            PopupMenu menu1
        ElseIf (NodeData(ActiveListIndex).nodetype = componentNode) Then
            menuActive = True
            menuItems(1).Caption = "New Sibling Node"
            menuItems(1).Enabled = True
            menuItems(2).Enabled = (NodeData(ActiveListIndex).hLevel < compHierarchy.nLevels - 1)
            menuItems(3).Enabled = True
            menuItems(4).Enabled = (ComponentTree.DependentCount(ActiveListIndex, 1) = 0)
            menuItems(5).Enabled = (NodeData(ActiveListIndex).diagramPath <> "" And NodeData(ActiveListIndex).diagramPath <> "(none)")
            menuItems(7).Enabled = True
            menuItems(6).Enabled = DoesParentHaveDiagram(ActiveListIndex)
            PopupMenu menu1
        End If
    End If
End Sub

Private Function DoesParentHaveDiagram(ListIndex As Integer) As Boolean
    Dim pIndex As Integer
    pIndex = ComponentTree.Object.Parent(ListIndex)
    If pIndex = -1 Then
        DoesParentHaveDiagram = (CompDiagram.InitialDiagramFileName <> "" And CompDiagram.InitialDiagramFileName <> "(none)")
    Else
        DoesParentHaveDiagram = (NodeData(pIndex).diagramPath <> "" And NodeData(pIndex).diagramPath <> "(none)")
    End If
End Function

Private Function GetParentDiagramName(ListIndex As Integer) As String
    Dim pIndex As Integer
    pIndex = ComponentTree.Object.Parent(ListIndex)
    If pIndex = -1 Then
        GetParentDiagramName = CompDiagram.InitialDiagramFileName
    Else
        GetParentDiagramName = NodeData(pIndex).diagramPath
    End If
End Function

Private Sub ShowSelectMenu()
    ' determine what can be done at this location and present the options
    ' to the user in a pop-up menu
       
    If (ActiveListIndex = -1) Then
        'PopupMenu menu1
    Else
        If (NodeData(ActiveListIndex).nodetype = componentNode) Then
            menuActive = True
            menuItems2(1).Enabled = (NodeData(ActiveListIndex).diagramPath <> "" And NodeData(ActiveListIndex).diagramPath <> "(none)")
            menuItems2(2).Enabled = True
            PopupMenu menu2
        End If
    End If
End Sub

Private Sub ComponentTree_KeyDown(KeyCode As Integer, Shift As Integer)
    If KeyCode = 13 Then
        Dim ncForm As NewComponent, newIndex As Integer
        ActiveListIndex = ComponentTree.ListSelection
        If ActiveListIndex = -1 Then Exit Sub
        Set ncForm = New NewComponent
        ncForm.componentName = "New " & compHierarchy.LevelStrings(ComponentTree.ItemLevel(ActiveListIndex))
        ncForm.minHLevel = ComponentTree.ItemLevel(ActiveListIndex)
        ncForm.hLevel = ComponentTree.ItemLevel(ActiveListIndex)
        ncForm.maxHLevel = compHierarchy.nLevels - 1
        ncForm.diagramPath = "(none)"
        ncForm.Show vbModal, Me
        
        If (ncForm.Result = True) Then
            Set Node = New componentNode
            Node.createBaseCompCollection
            Node.nodetype = componentNode
            Node.hLevel = ncForm.hLevel
            If (Node.hLevel > compHierarchy.nLevelsInUse) Then
                compHierarchy.nLevelsInUse = Node.hLevel
            End If
            Node.ID = nextCompID
            nextCompID = nextCompID + 1
            Node.name = ncForm.componentName
            'Node.parentID = NodeData(ActiveListIndex).ID
            Node.diagramPath = ncForm.diagramPath
            Do While (NodeData(ActiveListIndex).nodetype <> emptyNode)
                ActiveListIndex = ActiveListIndex + 1
                If NodeData(ActiveListIndex).hLevel < Node.hLevel Then Exit Do
            Loop
            newIndex = ComponentTree.InsertItem(ActiveListIndex, ncForm.componentName)
            ComponentTree.ItemData(newIndex) = Node.ID
            ComponentTree.ItemLevel(newIndex) = ncForm.hLevel 'ComponentTree.ItemLevel(ActiveListIndex) + 1
            ComponentTree.ItemDataTag(newIndex) = Node
            Set ComponentTree.ItemPicture(newIndex) = compHierarchy.Icon(Node.hLevel)
            
            ComponentTree.CellText(newIndex, 1) = "0"
            ComponentTree.CellText(newIndex, 2) = "0"
            If Node.diagramPath <> "(none)" And Node.diagramPath <> "" Then
                ComponentTree.CellText(newIndex, 3) = "Yes"
            Else
                ComponentTree.CellText(newIndex, 3) = "No"
            End If
        End If
        Unload ncForm
    End If
End Sub

Private Sub EditHierarchy_Click()
    Dim ECHDlg As EditCompHierarchy
    Set ECHDlg = New EditCompHierarchy
    ECHDlg.Show 1
    
    Dim mySQLString As String, i As Integer
    mySQLString = "DELETE FROM CompHLevels"
    dbConnection.Execute (mySQLString)
    mySQLString = "INSERT INTO CompHLevels(nLevels,nLevelsInUse) VALUES(" & compHierarchy.nLevels & "," & compHierarchy.nLevelsInUse & ")"
    dbConnection.Execute (mySQLString)
    mySQLString = "DELETE FROM CompHData"
    dbConnection.Execute (mySQLString)
    
    mySQLString = "INSERT INTO [CompHData] (hLevel, Name, IconFileName) VALUES (10 ,'" & compHierarchy.BaseName & "' ,'" & compHierarchy.BaseIconFileName & "' )"
    dbConnection.Execute (mySQLString)
    
    For i = 0 To compHierarchy.nLevels - 1
        mySQLString = "INSERT INTO [CompHData] (hLevel,Name,IconFileName) VALUES(" & i & ",'" & compHierarchy.LevelStrings(i) & "','" & compHierarchy.IconFileName(i) & "')"
        dbConnection.Execute (mySQLString)
    Next i
End Sub

Private Sub Form_Activate()
    
    Select Case FormMode
    Case SelectOnly
        ' select all nodes which are currently in the selected nodes collection
        'Dim i As Integer
        'For i = 1 To selectedNodes.Count
        '    RequestSelection selectedNodes.Item(i)
            'ComponentTree.Selected(selectedNodes.Item(i)) = True
        'Next i
        EditHierarchy.Visible = False
        ShowFormView
    Case Edit
        EditHierarchy.Visible = True
        
    End Select
End Sub

Private Sub ShowFormView()
    
    ComponentTree.Visible = (FormView = HiearchialView)
    If FormView = DiagramView Then
        SelectedComponentList.Top = 840
        SelectedComponentList.Height = ScaleHeight - 2720
        If DoesParentHaveDiagram(ActiveListIndex) Then
            If CompDiagram.DiagramFileName <> GetParentDiagramName(ActiveListIndex) Then
                CompDiagram.DiagramFileName = GetParentDiagramName(ActiveListIndex)
            End If
            CompDiagram.ShowDiagram = True
            SelectAllVisibleRegionsInDiagram
            Dim rID As Integer
            rID = CompDiagram.GetRegionIDByCompID(NodeData(ActiveListIndex).ID)
            If rID > 0 Then
                CompDiagram.CenterDiagram rID
            End If
        Else
            CompDiagram.ShowDiagram = False
        End If
                
        If CompDiagram.ShowDiagram = True Then
            UpLevelButton.Enabled = CompDiagram.GetCurrentDiagram().HasParent
        Else
            UpLevelButton.Enabled = False
        End If
    Else
        SelectedComponentList.Top = 360
        SelectedComponentList.Height = ScaleHeight - 2000
    End If
    
    CompDiagram.Visible = (FormView = DiagramView)
    UpLevelButton.Visible = (FormView = DiagramView)
    'RegionLabel.Visible = (FormView = DiagramView)
    ComponentLabel.Visible = (FormView = DiagramView)
    'OptionHierarchyView.Value = (FormView = HiearchialView)
    'OptionDiagramView.Value = (FormView = HiearchialView)
    
End Sub

Public Sub Form_Load()
    ' get level strings
    CompDiagram.DiagramFolder = pidDirectory
    'CompDiagram.DiagramFileName = "ISS1.bmp"
    nextCompID = 1
    
    ComponentTree.ItemPictureExpandable = MDIMain.nodePict1
    ComponentTree.ItemPictureExpanded = MDIMain.nodePict2
    ComponentTree.ItemPictureLeaf = LoadPicture(workingDirectory & "icons\blank.bmp") 'MDIMain.nodePict3
        
    ComponentTree.ColumnText(1) = "Immediate " & compHierarchy.BaseName & "s"
    ComponentTree.ColumnText(2) = "Total " & compHierarchy.BaseName & "s"
    
    SelectedComponentList.ColumnHeaders.Add , , "Component Name"
    
    LoadTree
    
    ' load select-only menu
    Load menuItems2(1)
    menuItems2(1).Caption = "View P&ID"
    Load menuItems2(2)
    menuItems2(2).Caption = "Properties..."
    menuItems2(0).Visible = False
    ' load edit menu
    Load menuItems(1)
    menuItems(1).Caption = "New Sibling Node"
    Load menuItems(2)
    menuItems(2).Caption = "New Child Node"
    Load menuItems(3)
    menuItems(3).Caption = compHierarchy.BaseName & "s..."
    Load menuItems(4)
    menuItems(4).Caption = "Delete Node"
    Load menuItems(5)
    menuItems(5).Caption = "View P&ID"
    Load menuItems(6)
    menuItems(6).Caption = "Create Region in Parent Diagram"
    Load menuItems(7)
    menuItems(7).Caption = "Properties..."
    menuItems(0).Visible = False
    Select Case FormMode
    Case SelectOnly
        ComponentTree.MultiSelect = selectSftTreeMulti
    Case Edit
        ComponentTree.MultiSelect = selectSftTreeSingle
    End Select
End Sub

Private Sub Form_Resize()
    If Me.Width > 3200 And ScaleHeight > 3000 Then
        ComponentTree.Height = ScaleHeight - 915 'Height - 1650
        ComponentTree.Width = ScaleWidth - 2955 'Width - 795
        CompDiagram.Height = ScaleHeight - 1755
        CompDiagram.Width = ScaleWidth - 2955
        SelectedComponentList.Left = ScaleWidth - 2730
        If FormView = HiearchialView Then
            SelectedComponentList.Height = ScaleHeight - 2000
        Else
            SelectedComponentList.Height = ScaleHeight - 2360
        End If
        RemoveComponentButton.Top = ScaleHeight - 1410
        Label1.Left = ScaleWidth - 2730
        RemoveComponentButton.Left = ScaleWidth - 2730
        EditHierarchy.Top = ScaleHeight - 450 'Height - 1065
        OKButton.Top = ScaleHeight - 450 'Height - 1065
        OKButton.Left = ScaleWidth - 1680 'Width - 2010
    End If
End Sub

Private Sub menuItems_Click(Index As Integer)
    ' menu in edit mode
    Select Case Index
    Case 1 ' New Sibling Node
        NewSibling
    Case 2 ' New Child Node
        NewChild
    Case 3 ' Add Base Component(s)
        AddBaseComps
    Case 4 ' Delete Node
        DeleteNode
    Case 5 ' View P&ID
        Dim cForm As ComponentDiagram
        Set cForm = New ComponentDiagram
        cForm.pictureName = NodeData(ActiveListIndex).diagramPath
        cForm.Show vbModal
    Case 6 ' Properties...
        DefineRegionInParentDiagram
    Case 7
        DoProperties
    End Select
    
End Sub

Private Sub DefineRegionInParentDiagram()
    If DoesParentHaveDiagram(ActiveListIndex) Then
        CompDiagram.DiagramFileName = GetParentDiagramName(ActiveListIndex)
        FormView = DiagramView
        ShowFormView
        CompDiagram.AddRegion
    End If
End Sub

Private Sub menuItems2_Click(Index As Integer)
    ' menu in select only mode
    Select Case Index
    Case 1 ' View P&ID
        Dim cForm As ComponentDiagram
        Set cForm = New ComponentDiagram
        cForm.pictureName = NodeData(ActiveListIndex).diagramPath
        cForm.Show vbModal
    Case 2 ' Properties...
        DoProperties
    End Select
End Sub

Private Sub NewSibling()
    Dim newIndex As Integer
    Dim ncForm As NewComponent
    
    Set ncForm = New NewComponent
    ncForm.componentName = "New " & compHierarchy.LevelStrings(ComponentTree.ItemLevel(ActiveListIndex))
    ncForm.minHLevel = ComponentTree.ItemLevel(ActiveListIndex)
    ncForm.hLevel = ComponentTree.ItemLevel(ActiveListIndex)
    ncForm.maxHLevel = ComponentTree.ItemLevel(ActiveListIndex)
    ncForm.diagramPath = "(none)"
    ncForm.Show vbModal, Me
    
    If (ncForm.Result = True) Then
        changesMade = True
        Set Node = New componentNode
        Node.createBaseCompCollection
        Node.nodetype = componentNode
        Node.hLevel = ComponentTree.ItemLevel(ActiveListIndex)
        Node.ID = nextCompID 'next node ID
        nextCompID = nextCompID + 1
        Node.name = ncForm.componentName
        'Node.parentID = NodeData(ActiveListIndex).parentID
        If (NodeData(ActiveListIndex).nodetype = emptyNode) Then
            newIndex = ComponentTree.InsertItem(ActiveListIndex, ncForm.componentName)
        Else
            ' find the next node at this level, insert there,
            ' unless you get to the empty node, then you can
            ' insert there
            
            Do
                ActiveListIndex = ActiveListIndex + 1
            Loop While (NodeData(ActiveListIndex).nodetype <> emptyNode And NodeData(ActiveListIndex).hLevel > Node.hLevel)
            newIndex = ComponentTree.InsertItem(ActiveListIndex, ncForm.componentName)
        End If
        ComponentTree.ItemData(newIndex) = Node.ID
        ComponentTree.ItemLevel(newIndex) = Node.hLevel
        Node.diagramPath = ncForm.diagramPath
        ComponentTree.ItemDataTag(newIndex) = Node
        Set ComponentTree.ItemPicture(newIndex) = compHierarchy.Icon(Node.hLevel)
        ComponentTree.CellText(newIndex, 1) = "0"
        ComponentTree.CellText(newIndex, 2) = "0"
        If Node.diagramPath <> "(none)" And Node.diagramPath <> "" Then
            ComponentTree.CellText(newIndex, 3) = "Yes"
        Else
            ComponentTree.CellText(newIndex, 3) = "No"
        End If
    End If
    Unload ncForm
End Sub

Private Sub NewChild()
    Dim newIndex As Integer
    Dim ncForm As NewComponent
    
    Set ncForm = New NewComponent
    ncForm.componentName = "New " & compHierarchy.LevelStrings(ComponentTree.ItemLevel(ActiveListIndex) + 1)
    ncForm.minHLevel = ComponentTree.ItemLevel(ActiveListIndex) + 1
    ncForm.hLevel = ComponentTree.ItemLevel(ActiveListIndex) + 1
    ncForm.maxHLevel = compHierarchy.nLevels - 1
    ncForm.diagramPath = "(none)"
    ncForm.Show vbModal, Me
    
    If (ncForm.Result = True) Then
        changesMade = True
        Set Node = New componentNode
        Node.createBaseCompCollection
        Node.nodetype = componentNode
        Node.hLevel = ncForm.hLevel
        If (Node.hLevel > compHierarchy.nLevelsInUse) Then
            compHierarchy.nLevelsInUse = Node.hLevel
        End If
        Node.ID = nextCompID
        nextCompID = nextCompID + 1
        Node.name = ncForm.componentName
        'Node.parentID = NodeData(ActiveListIndex).ID
        Node.diagramPath = ncForm.diagramPath
        Do
            ActiveListIndex = ActiveListIndex + 1
        Loop While (NodeData(ActiveListIndex).nodetype <> emptyNode And NodeData(ActiveListIndex).hLevel >= Node.hLevel)
        newIndex = ComponentTree.InsertItem(ActiveListIndex, ncForm.componentName)
        ComponentTree.ItemData(newIndex) = Node.ID
        ComponentTree.ItemLevel(newIndex) = ncForm.hLevel 'ComponentTree.ItemLevel(ActiveListIndex) + 1
        ComponentTree.ItemDataTag(newIndex) = Node
        Set ComponentTree.ItemPicture(newIndex) = compHierarchy.Icon(Node.hLevel)
        
        ComponentTree.CellText(newIndex, 1) = "0"
        ComponentTree.CellText(newIndex, 2) = "0"
        If Node.diagramPath <> "(none)" And Node.diagramPath <> "" Then
            ComponentTree.CellText(newIndex, 3) = "Yes"
        Else
            ComponentTree.CellText(newIndex, 3) = "No"
        End If
    End If
    Unload ncForm
End Sub

Private Sub AddBaseComps()
    Dim pIndex As Integer
    Dim bcForm As SelectBaseComponent
    Set bcForm = New SelectBaseComponent
    Dim i As Integer, isDuplicate As Boolean, cinBC
    cinBC = NodeData(ActiveListIndex).BaseComponentCount
    Set bcForm.cNode = NodeData(ActiveListIndex)
    bcForm.baseCompName = compHierarchy.BaseName
    bcForm.Show 1
    If (bcForm.Result = True) Then
        changesMade = True
        cinBC = NodeData(ActiveListIndex).BaseComponentCount - cinBC
        NodeData(ActiveListIndex).totalBaseComponents = NodeData(ActiveListIndex).totalBaseComponents + cinBC
        ComponentTree.CellText(ActiveListIndex, 1) = NodeData(ActiveListIndex).BaseComponentCount
        ComponentTree.CellText(ActiveListIndex, 2) = NodeData(ActiveListIndex).totalBaseComponents
        Dim pLevel As Integer
        pIndex = ActiveListIndex
        For pLevel = NodeData(ActiveListIndex).hLevel - 1 To 0 Step -1
            pIndex = ComponentTree.Object.Parent(pIndex)
            NodeData(pIndex).totalBaseComponents = NodeData(pIndex).totalBaseComponents + cinBC
            ComponentTree.CellText(pIndex, 2) = NodeData(pIndex).totalBaseComponents
        Next pLevel
    End If
    
    Unload bcForm
End Sub

Private Sub DeleteNode()
    Dim dCount As Long
    
    Dim doDelete As Boolean, mySQLstatement As String, resultSet As rdoResultset, resultSet2 As rdoResultset
    dCount = ComponentTree.DependentCount(ActiveListIndex, 1)
    If dCount > 0 Then
        MsgBox "You may not delete a node with any dependent nodes.  First delete all dependent nodes.", vbInformation
        'If MsgBox("Are you sure you want to delete this node?  This will remove " & dCount & " dependent node(s).", vbQuestion + vbYesNo) = vbYes Then
        '    ComponentTree.BulkUpdate = True
        '    ComponentTree.DeleteDependents (ActiveListIndex)
        '    ComponentTree.BulkUpdate = False
        '    doDelete = True
        'End If
    Else
        doDelete = True
    End If
    
    If doDelete Then
        
        mySQLstatement = "SELECT ProcedureID FROM ProcComp WHERE ComponentID = " & NodeData(ActiveListIndex).ID
        Set resultSet = dbConnection.OpenResultset(mySQLstatement)
              
        If Not resultSet.EOF Then
            
            Dim mFrm As ListMessage, ProcName As String, procDesc As String, rArray2 As Variant
            Set mFrm = New ListMessage
            mFrm.boxcaption = "Confirm Node Deletion"
            mFrm.message = "Deleting " & NodeData(ActiveListIndex).name & " will cause this component to be removed from the following procedures.  Are you sure you want to delete this component?"
            mFrm.AddHeader "Procedure Name"
            mFrm.AddHeader "Procedure Description"
        
            Dim rarray As Variant
            While Not resultSet.EOF
                rarray = resultSet.GetRows(1)
                mySQLstatement = "SELECT ProcedureName, ProcedureDesc FROM [Procedure] WHERE ProcedureID = " & rarray(0, 0)
                Set resultSet2 = dbConnection.OpenResultset(mySQLstatement)
                rArray2 = resultSet2.GetRows(1)
                ProcName = rArray2(0, 0)
                procDesc = rArray2(1, 0)
                mFrm.AddRow ProcName
                mFrm.AddRowSubText procDesc
            Wend
            mFrm.Show 1
            If mFrm.Result = False Then Exit Sub
            mySQLstatement = "DELETE FROM ProcComp WHERE ComponentID = " & NodeData(ActiveListIndex).ID
            dbConnection.Execute (mySQLstatement)
        End If
        changesMade = True
        Dim cBC As Integer
        cBC = NodeData(ActiveListIndex).totalBaseComponents
        If (cBC > 0) Then
            Dim pL As Integer, pIndex As Integer
            pIndex = ActiveListIndex
            For pL = NodeData(ActiveListIndex).hLevel - 1 To 0 Step -1
                pIndex = ComponentTree.Object.Parent(pIndex)
                NodeData(pIndex).totalBaseComponents = NodeData(pIndex).totalBaseComponents - cBC
                ComponentTree.CellText(pIndex, 2) = NodeData(pIndex).totalBaseComponents
            Next pL
        End If
        ComponentTree.RemoveItem (ActiveListIndex)
    End If
End Sub

Private Sub DoProperties()
    Dim ncForm As NewComponent
    Dim pIndex As Integer
    
    Select Case NodeData(ActiveListIndex).nodetype
    Case componentNode
        Set ncForm = New NewComponent
        pIndex = ComponentTree.Object.Parent(ActiveListIndex)
        If (pIndex >= 0) Then
            ncForm.minHLevel = NodeData(pIndex).hLevel
        Else
            ncForm.minHLevel = 0
        End If
        ' check to see if it has dependents... if it does, don't let
        ' this node become lower than it's greatest dependent...
        ncForm.maxHLevel = compHierarchy.nLevels - 1
        Dim cIndex As Integer
        cIndex = ActiveListIndex
        Do
            cIndex = cIndex + 1
            If (NodeData(cIndex).nodetype = emptyNode Or NodeData(cIndex).hLevel <= NodeData(ActiveListIndex).hLevel) Then
                Exit Do
            Else
                If NodeData(cIndex).hLevel < ncForm.maxHLevel Then ncForm.maxHLevel = NodeData(cIndex).hLevel
            End If
        Loop
        ncForm.hLevel = NodeData(ActiveListIndex).hLevel
        ncForm.componentName = NodeData(ActiveListIndex).name
        ncForm.diagramPath = NodeData(ActiveListIndex).diagramPath
        ncForm.dlgCaption = ncForm.componentName & " Properties"
        If FormMode = SelectOnly Then
            ncForm.LockForm = True
            ncForm.minHLevel = ncForm.hLevel
            ncForm.maxHLevel = ncForm.hLevel
        Else
            ncForm.LockForm = False
            ncForm.CompIDLabel.Caption = NodeData(ActiveListIndex).ID
        End If
        ncForm.Show vbModal, Me
        
        If (ncForm.Result = True And ncForm.changesMade And FormMode = Edit) Then
            changesMade = True
            ComponentTree.ItemLevel(ActiveListIndex) = ncForm.hLevel
            NodeData(ActiveListIndex).hLevel = ncForm.hLevel
            Set ComponentTree.ItemPicture(ActiveListIndex) = compHierarchy.Icon(ncForm.hLevel)
            NodeData(ActiveListIndex).name = ncForm.componentName
            NodeData(ActiveListIndex).diagramPath = ncForm.diagramPath
            ComponentTree.CellText(ActiveListIndex, 0) = NodeData(ActiveListIndex).name
            If NodeData(ActiveListIndex).diagramPath <> "(none)" And NodeData(ActiveListIndex).diagramPath <> "" Then
                ComponentTree.CellText(ActiveListIndex, 3) = "Yes"
            Else
                ComponentTree.CellText(ActiveListIndex, 3) = "No"
            End If
        End If
        Unload ncForm
    Case baseComponentNode
        MsgBox "No properties available", vbInformation
    End Select
End Sub

Private Sub OKButton_Click()
    Select Case FormMode
    Case SelectOnly
        'Dim listCount As Integer, Index As Integer
        'listCount = ComponentTree.listCount
        'ClearSelectedNodes
        'For Index = 0 To listCount - 1
        '    If ComponentTree.Selected(Index) Then
        '        selectedNodes.Add Index
                ' make sure all children are not selected
        '        Dim aRow As Integer
        '        Do While (NodeData(Index + 1).nodetype <> emptyNode And NodeData(Index + 1).hLevel > NodeData(ActiveListIndex).hLevel)
        '            Index = Index + 1
        '        Loop
        '    End If
        'Next Index
    Case Edit
        SaveTree
    End Select
    Me.Hide
End Sub

Private Sub SaveTree()
    If (changesMade) Then
        Dim i As Integer, pIndex As Integer, pID As Integer, j As Integer
        Dim mySQLstatement As String
        mySQLstatement = "DELETE FROM Component"
        dbConnection.Execute (mySQLstatement)
        mySQLstatement = "DELETE FROM CompBaseComponent"
        dbConnection.Execute (mySQLstatement)
        
        For i = 0 To ComponentTree.listCount - 1
        
            If NodeData(i).nodetype <> emptyNode Then
        
                pIndex = ComponentTree.Object.Parent(i)
                If pIndex >= 0 Then
                    pIndex = NodeData(pID).ID
                Else
                    pIndex = 0
                End If
                mySQLstatement = "INSERT INTO [Component] (ComponentID, ComponentName, DatabaseID, hLevel, parentComponentID, PIDiagram) VALUES (" & NodeData(i).ID & ",'" & NodeData(i).name & "',0," & NodeData(i).hLevel & "," & pID & ",'" & NodeData(i).diagramPath & "')"
                dbConnection.Execute (mySQLstatement)
                
                If NodeData(i).BaseComponentCount > 0 Then
                    ' insert base components into hierarchy
                    pIndex = i
                    Do
                        ' write all base components to CompBaseComponent table
                        For j = 1 To NodeData(i).BaseComponentCount
                            If pIndex = i Then
                                mySQLstatement = "INSERT INTO [CompBaseComponent] (ComponentID, BaseCompID, Immediate) VALUES (" & NodeData(pIndex).ID & "," & NodeData(i).GetBaseComponent(j).ID & ",Yes)"
                            Else
                                mySQLstatement = "INSERT INTO [CompBaseComponent] (ComponentID, BaseCompID, Immediate) VALUES (" & NodeData(pIndex).ID & "," & NodeData(i).GetBaseComponent(j).ID & ",No)"
                            End If
                            dbConnection.Execute (mySQLstatement)
                        Next j
                        pIndex = ComponentTree.Object.Parent(pIndex)
                    Loop While pIndex <> -1
                End If
            End If
        Next i
        changesMade = False
    End If
End Sub

Private Sub LoadTree()
    
    Dim mySQLstatement As String, newIndex As Integer, ActiveListIndex As Integer, pID As Integer
    Dim name As String, gName As String, nBEs As Integer
    mySQLstatement = "SELECT ComponentID, ComponentName, hLevel, parentComponentID, PIDiagram FROM Component"
    Dim resultSet As rdoResultset, resultSet2 As rdoResultset, resultSet3 As rdoResultset
    Set resultSet = dbConnection.OpenResultset(mySQLstatement)
    Dim rarray As Variant, rArray2 As Variant, baseID As Integer
    nextCompID = 1
    ComponentTree.Clear
    ActiveListIndex = 0
    'TreeLoaded = True
    
    While Not resultSet.EOF
        rarray = resultSet.GetRows(1)
        Set Node = New componentNode
        Node.createBaseCompCollection
        Node.nodetype = componentNode
        
        Node.hLevel = rarray(2, 0)
        Node.ID = rarray(0, 0)
        If Node.ID >= nextCompID Then
            nextCompID = Node.ID + 1
        End If
        Node.name = rarray(1, 0)
        'Node.parentID = rArray(3, 0)
        newIndex = ComponentTree.InsertItem(ActiveListIndex, Node.name)
        ComponentTree.ItemData(newIndex) = Node.ID
        ComponentTree.ItemLevel(newIndex) = Node.hLevel
        Node.diagramPath = rarray(4, 0)
        ComponentTree.ItemDataTag(newIndex) = Node
        Set ComponentTree.ItemPicture(newIndex) = compHierarchy.Icon(Node.hLevel)
        
        mySQLstatement = "SELECT BaseCompID FROM [CompBaseComponent] WHERE ComponentID = " & Node.ID & " AND Immediate = 1"
        Set resultSet2 = dbConnection.OpenResultset(mySQLstatement)
        While Not resultSet2.EOF
            rArray2 = resultSet2.GetRows(1)
            baseID = rArray2(0, 0)
            mySQLstatement = "SELECT Name, GroupName, nAssociatedBEs FROM BaseComponent WHERE BaseCompID = " & baseID
            Set resultSet3 = dbConnection.OpenResultset(mySQLstatement)
            If resultSet3.EOF Then
                ' somehow this base component was deleted... let's get rid of the entry in the CompBaseComp table
                mySQLstatement = "DELETE FROM CompBaseComponent WHERE ComponentID = " & Node.ID & " AND BaseCompID = " & baseID
                dbConnection.Execute (mySQLstatement)
            Else
                rArray2 = resultSet3.GetRows(1)
                name = rArray2(0, 0)
                gName = rArray2(1, 0)
                nBEs = rarray(2, 0)
                Node.AddBaseComponent gName, name, baseID, nBEs
            End If
        Wend
        Node.totalBaseComponents = Node.BaseComponentCount
        ComponentTree.CellText(newIndex, 1) = Node.BaseComponentCount
        ComponentTree.CellText(newIndex, 2) = Node.BaseComponentCount
        
        If Node.diagramPath <> "(none)" And Node.diagramPath <> "" Then
            ComponentTree.CellText(newIndex, 3) = "Yes"
        Else
            ComponentTree.CellText(newIndex, 3) = "No"
        End If
        
        ' now update the base component count for all parent nodes of this node
        pID = ComponentTree.Object.Parent(newIndex)
        Do While pID <> -1
            NodeData(pID).totalBaseComponents = NodeData(pID).totalBaseComponents + Node.BaseComponentCount
            ComponentTree.CellText(pID, 2) = NodeData(pID).totalBaseComponents
            pID = ComponentTree.Object.Parent(pID)
        Loop
        ActiveListIndex = ActiveListIndex + 1
    Wend
    
    Set Node = New componentNode
    Node.nodetype = emptyNode
    newIndex = ComponentTree.AddItem("")
    ComponentTree.ItemLevel(newIndex) = 0
    ComponentTree.ItemDataTag(newIndex) = Node
    ComponentTree.ItemData(newIndex) = 0
    changesMade = False
    
End Sub

Private Sub OptionDiagramView_Click()
    FormView = DiagramView
    ShowFormView
End Sub

Private Sub OptionHierarchyView_Click()
    FormView = HiearchialView
    ShowFormView
End Sub

