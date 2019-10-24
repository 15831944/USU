VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form SelectBaseComponent 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Select a Base Component"
   ClientHeight    =   4830
   ClientLeft      =   2760
   ClientTop       =   3750
   ClientWidth     =   8850
   BeginProperty Font 
      Name            =   "Arial"
      Size            =   9.75
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   Icon            =   "SelectBaseComponent.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4830
   ScaleWidth      =   8850
   ShowInTaskbar   =   0   'False
   Begin MSComctlLib.ListView SelectedBaseComponents 
      Height          =   2295
      Left            =   4080
      TabIndex        =   9
      Top             =   1680
      Width           =   4335
      _ExtentX        =   7646
      _ExtentY        =   4048
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
      NumItems        =   0
   End
   Begin VB.CommandButton RemoveSelectedComps 
      Caption         =   "Remove"
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
      Left            =   7080
      TabIndex        =   7
      Top             =   4200
      Width           =   1335
   End
   Begin VB.CommandButton AddComps 
      Caption         =   "Add ->"
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
      Left            =   2400
      TabIndex        =   6
      Top             =   4200
      Width           =   1215
   End
   Begin VB.ComboBox Combo1 
      Height          =   360
      ItemData        =   "SelectBaseComponent.frx":0442
      Left            =   240
      List            =   "SelectBaseComponent.frx":0444
      Style           =   2  'Dropdown List
      TabIndex        =   4
      Top             =   720
      Width           =   3375
   End
   Begin VB.CommandButton CancelButton 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   5760
      TabIndex        =   1
      Top             =   240
      Width           =   1215
   End
   Begin VB.CommandButton OKButton 
      Caption         =   "OK"
      Height          =   375
      Left            =   7200
      TabIndex        =   0
      Top             =   240
      Width           =   1215
   End
   Begin MSComctlLib.ListView BaseComponentList 
      Height          =   2295
      Left            =   240
      TabIndex        =   5
      Top             =   1680
      Width           =   3375
      _ExtentX        =   5953
      _ExtentY        =   4048
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
   Begin VB.Label CompLabel 
      Caption         =   "Label3"
      Height          =   615
      Left            =   3960
      TabIndex        =   8
      Top             =   960
      Width           =   3255
   End
   Begin VB.Label Label2 
      Caption         =   "Base Components"
      Height          =   375
      Left            =   240
      TabIndex        =   3
      Top             =   1200
      Width           =   2175
   End
   Begin VB.Label Label1 
      Caption         =   "Base Component Group"
      Height          =   375
      Left            =   240
      TabIndex        =   2
      Top             =   240
      Width           =   2415
   End
End
Attribute VB_Name = "SelectBaseComponent"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Option Explicit
Public nGroups As Integer
Public ActiveGroupName As String
Public ActiveName As String
Public ActiveID As Integer
Public nAssociatedBEs As Integer

Public Result As Boolean
Public cNode As componentNode
Public baseCompName As String
Private tempNode As componentNode

Private Sub AddComps_Click()

    Dim i As Integer, j As Integer, comp As ListItem, duplicate As Boolean
        
    For i = 1 To BaseComponentList.ListItems.Count
        Set comp = BaseComponentList.ListItems.Item(i)
            
        If (comp.Selected = True) Then
            duplicate = False
            For j = 1 To SelectedBaseComponents.ListItems.Count
                If (SelectedBaseComponents.ListItems(j).ListSubItems(1).text = comp.text And _
                    SelectedBaseComponents.ListItems(j).text = ActiveGroupName) Then
                    duplicate = True
                    Exit For
                End If
     
            Next j
            
            If Not duplicate Then
                Dim bComp As ListItem
                tempNode.AddBaseComponent ActiveGroupName, comp.text, comp.tag.ID, comp.tag.nBEs
                
                Set bComp = SelectedBaseComponents.ListItems.Add()
                bComp.text = ActiveGroupName
                bComp.ListSubItems.Add
                bComp.ListSubItems(1).text = comp.text
                Set bComp.tag = comp.tag
                'If ShowNumberAssociatedBasicEvents Then
                '    bComp.ListSubItems.Add
                '    bComp.ListSubItems(2).text = comp.tag.nBEs
                'End If

            End If
        End If
    Next i
    AddComps.Enabled = False
    RemoveSelectedComps.Enabled = True
End Sub

Private Sub BaseComponentList_ItemClick(ByVal Item As MSComctlLib.ListItem)
    AddComps.Enabled = True
    RemoveSelectedComps.Enabled = False
End Sub

Private Sub CancelButton_Click()
    Result = False
    Me.Hide
End Sub

Private Sub Combo1_Click()
    Dim mySQLStatement As String
    Dim rArray As Variant
    
    ActiveGroupName = Combo1.List(Combo1.ListIndex)
    mySQLStatement = "SELECT Name, nAssociatedBEs, BaseCompID from [BaseComponent] WHERE GroupName = '" & ActiveGroupName & "'"
        
    Dim resultSet As rdoResultset
    Set resultSet = dbConnection.OpenResultset(mySQLStatement)
        
    BaseComponentList.ListItems.Clear
    Dim ComponentList As ListItem
    While Not resultSet.EOF
        rArray = resultSet.GetRows(1)
        Set ComponentList = BaseComponentList.ListItems.Add()
        'ComponentList.SmallIcon = X
        ComponentList.text = rArray(0, 0)
        Dim tag As baseCompClass
        Set tag = New baseCompClass
        tag.GroupName = ActiveGroupName
        tag.name = rArray(0, 0)
        tag.ID = rArray(2, 0)
        tag.nBEs = rArray(1, 0)
        Set ComponentList.tag = tag
        'If ShowNumberAssociatedBasicEvents Then ComponentList.ListSubItems.Add , , rArray(1, 0)
    Wend
    ActiveName = ""
    AddComps.Enabled = False
    RemoveSelectedComps.Enabled = False
End Sub

Private Sub OKButton_Click()
    Dim i As Integer
    
    Result = True
    cNode.ClearBaseComponents
    For i = 1 To tempNode.BaseComponentCount
        cNode.AddBaseComponent tempNode.GetBaseComponent(i).GroupName, tempNode.GetBaseComponent(i).name, tempNode.GetBaseComponent(i).ID, tempNode.GetBaseComponent(i).nBEs
    Next i
    
    Me.Hide
End Sub

Private Sub Form_Load()
    
    Dim mySQLStatement As String
    Dim rArray As Variant, i As Integer

    ' copy the base component info into a temporary object,
    ' in case the user decides to cancel
    Set tempNode = New componentNode
    tempNode.createBaseCompCollection
    For i = 1 To cNode.BaseComponentCount
        tempNode.AddBaseComponent cNode.GetBaseComponent(i).GroupName, cNode.GetBaseComponent(i).name, cNode.GetBaseComponent(i).ID, cNode.GetBaseComponent(i).nBEs
    Next i
    
    Label1.Caption = baseCompName & " Groups"
    Label2.Caption = baseCompName & "s"
    Me.Caption = "Select " & baseCompName & "s"
    
    mySQLStatement = "SELECT DISTINCT GroupName from BaseComponent"
    
    Dim resultSet As rdoResultset
    Set resultSet = dbConnection.OpenResultset(mySQLStatement)
    nGroups = 0
    
    While Not resultSet.EOF
        rArray = resultSet.GetRows(1)
        nGroups = nGroups + 1
        Combo1.AddItem rArray(0, 0)
    Wend
     
    Combo1.ListIndex = 0
    
    Dim colHeader As ColumnHeader
    Set colHeader = BaseComponentList.ColumnHeaders.Add()
    colHeader.text = baseCompName & "s"
    
    'If ShowNumberAssociatedBasicEvents Then
    '    Set colHeader = BaseComponentList.ColumnHeaders.Add()
    '    colHeader.text = "# B.E.s"
    '    BaseComponentList.ColumnHeaders(1).Width = (BaseComponentList.Width - 80) * 3 / 4
    '    BaseComponentList.ColumnHeaders(2).Width = (BaseComponentList.Width - 80) * 1 / 4
    'Else
    BaseComponentList.ColumnHeaders(1).Width = BaseComponentList.Width - 80
    'End If
    
    CompLabel.Caption = baseCompName & "s associated with " & NewLine & cNode.name
            
    ' display all base components...
    Set colHeader = SelectedBaseComponents.ColumnHeaders.Add()
    colHeader.text = baseCompName & " Group"
    Set colHeader = SelectedBaseComponents.ColumnHeaders.Add()
    colHeader.text = baseCompName
    'If ShowNumberAssociatedBasicEvents Then
    '    Set colHeader = SelectedBaseComponents.ColumnHeaders.Add()
    '    colHeader.text = "# B.E.s"
    '    SelectedBaseComponents.ColumnHeaders(1).Width = (SelectedBaseComponents.Width - 80) * 3 / 8
    '    SelectedBaseComponents.ColumnHeaders(2).Width = (SelectedBaseComponents.Width - 80) * 3 / 8
    '    SelectedBaseComponents.ColumnHeaders(3).Width = (SelectedBaseComponents.Width - 80) * 2 / 8
    'Else
    SelectedBaseComponents.ColumnHeaders(1).Width = (SelectedBaseComponents.Width - 80) * 1 / 2
    SelectedBaseComponents.ColumnHeaders(2).Width = (SelectedBaseComponents.Width - 80) * 1 / 2
    'End If
    
    Dim bComp As ListItem
    For i = 1 To tempNode.BaseComponentCount
        Set bComp = SelectedBaseComponents.ListItems.Add()
        bComp.text = tempNode.GetBaseComponent(i).GroupName
        bComp.ListSubItems.Add
        bComp.ListSubItems(1).text = tempNode.GetBaseComponent(i).name
        Set bComp.tag = tempNode.GetBaseComponent(i)
        'If ShowNumberAssociatedBasicEvents Then
        bComp.ListSubItems.Add
        bComp.ListSubItems(2).text = tempNode.GetBaseComponent(i).nBEs
        'End If
    Next i
    AddComps.Enabled = False
    RemoveSelectedComps.Enabled = False
End Sub

Private Sub RemoveSelectedComps_Click()
    Dim i As Integer, comp As ListItem
    
    For i = SelectedBaseComponents.ListItems.Count To 1 Step -1
        Set comp = SelectedBaseComponents.ListItems.Item(i)
            
        If (comp.Selected = True) Then
            tempNode.DeleteBaseComponent (i)
            SelectedBaseComponents.ListItems.Remove (i)
        End If
    Next i
End Sub

Private Sub SelectedBaseComponents_Click()
    RemoveSelectedComps.Enabled = True
    AddComps.Enabled = False
End Sub
