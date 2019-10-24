VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form BaseComponentMap 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Map Basic Events to Base Components"
   ClientHeight    =   6435
   ClientLeft      =   2760
   ClientTop       =   3750
   ClientWidth     =   9690
   BeginProperty Font 
      Name            =   "Arial"
      Size            =   9.75
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   Icon            =   "BaseComponentMap.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   6435
   ScaleWidth      =   9690
   ShowInTaskbar   =   0   'False
   Begin MSComctlLib.ListView AssociatedEventsList 
      Height          =   2775
      Left            =   4560
      TabIndex        =   19
      Top             =   2880
      Width           =   4815
      _ExtentX        =   8493
      _ExtentY        =   4895
      View            =   3
      LabelEdit       =   1
      MultiSelect     =   -1  'True
      LabelWrap       =   -1  'True
      HideSelection   =   -1  'True
      FullRowSelect   =   -1  'True
      GridLines       =   -1  'True
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
   Begin VB.CommandButton AddMode 
      Caption         =   "Add..."
      Height          =   375
      Left            =   4560
      TabIndex        =   17
      Top             =   1560
      Width           =   1095
   End
   Begin VB.CommandButton RemoveMode 
      Caption         =   "Remove"
      Height          =   375
      Left            =   7680
      TabIndex        =   16
      Top             =   1560
      Width           =   1215
   End
   Begin VB.CommandButton ModeProperties 
      Caption         =   "Properties..."
      Height          =   375
      Left            =   5880
      TabIndex        =   15
      Top             =   1560
      Width           =   1575
   End
   Begin VB.ComboBox ModeCombo 
      Height          =   360
      Left            =   4560
      Style           =   2  'Dropdown List
      TabIndex        =   14
      Top             =   960
      Width           =   4335
   End
   Begin VB.CommandButton RenameGroup 
      Caption         =   "Rename"
      Height          =   375
      Left            =   1680
      TabIndex        =   12
      Top             =   1560
      Width           =   1095
   End
   Begin VB.CommandButton RenameBaseComponent 
      Caption         =   "Rename"
      Height          =   375
      Left            =   1680
      TabIndex        =   11
      Top             =   5760
      Width           =   1095
   End
   Begin VB.CommandButton OKButton 
      Caption         =   "OK"
      Height          =   375
      Left            =   8280
      TabIndex        =   10
      Top             =   240
      Width           =   1215
   End
   Begin VB.CommandButton RemoveBaseComponent 
      Caption         =   "Remove"
      Height          =   375
      Left            =   3000
      TabIndex        =   9
      Top             =   5760
      Width           =   1215
   End
   Begin VB.CommandButton AddBaseComponent 
      Caption         =   "Add..."
      Height          =   375
      Left            =   360
      TabIndex        =   8
      Top             =   5760
      Width           =   1095
   End
   Begin MSComctlLib.ListView BaseComponentList 
      Height          =   3375
      Left            =   360
      TabIndex        =   7
      Top             =   2280
      Width           =   3855
      _ExtentX        =   6800
      _ExtentY        =   5953
      View            =   3
      LabelEdit       =   1
      LabelWrap       =   -1  'True
      HideSelection   =   -1  'True
      FullRowSelect   =   -1  'True
      GridLines       =   -1  'True
      _Version        =   393217
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      BorderStyle     =   1
      Appearance      =   1
      NumItems        =   0
   End
   Begin VB.CommandButton RemoveGroup 
      Caption         =   "Remove"
      Height          =   375
      Left            =   3000
      TabIndex        =   6
      Top             =   1560
      Width           =   1215
   End
   Begin VB.CommandButton AddGroup 
      Caption         =   "Add..."
      Height          =   375
      Left            =   360
      TabIndex        =   5
      Top             =   1560
      Width           =   1095
   End
   Begin VB.ComboBox Combo1 
      Height          =   360
      Left            =   360
      Style           =   2  'Dropdown List
      TabIndex        =   4
      Top             =   960
      Width           =   3855
   End
   Begin VB.CommandButton RemoveBasicEvents 
      Caption         =   "Remove"
      Height          =   375
      Left            =   6360
      TabIndex        =   3
      Top             =   5760
      Width           =   1455
   End
   Begin VB.CommandButton AddBasicEvents 
      Caption         =   "Add..."
      Height          =   375
      Left            =   4680
      TabIndex        =   2
      Top             =   5760
      Width           =   1455
   End
   Begin VB.Label Label2 
      Caption         =   "Mode"
      Height          =   375
      Left            =   4560
      TabIndex        =   18
      Top             =   480
      Width           =   735
   End
   Begin VB.Label BaseComponentName 
      Height          =   255
      Left            =   4560
      TabIndex        =   13
      Top             =   2520
      Width           =   4815
   End
   Begin VB.Label Label3 
      Caption         =   "Basic Events associated with"
      Height          =   255
      Left            =   4560
      TabIndex        =   1
      Top             =   2160
      Visible         =   0   'False
      Width           =   3135
   End
   Begin VB.Label Label1 
      Caption         =   "Base Component Group"
      Height          =   375
      Left            =   360
      TabIndex        =   0
      Top             =   480
      Width           =   2415
   End
End
Attribute VB_Name = "BaseComponentMap"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Option Explicit
Dim nGroups As Integer
Public ActiveGroupName As String
Public ActiveName As String
Public ActiveID As Integer
Public nAssociatedBEs As Integer

Enum BCFormType
    MapBasicEvents = 0
    SelectBasicEvent = 1
End Enum

Public FormMode As BCFormType
'**************************| Steve's DLL Support |**************
Private Declare Function SetModeID Lib "riskMon" (ByVal NewModeID As Long) As Long
'***************************************************************

Private Sub AddBaseComponent_Click()
    Dim eFrm As New EnterString
    Dim mySQLStatement As String
    Dim i As Integer, duplicate As Boolean
        
    eFrm.Caption = "Enter Data"
    eFrm.Label1.Caption = "Base Component Name"
    Do
        eFrm.Show 1
        If eFrm.Result = False Then Exit Sub
        ' check to make sure than this name is not a duplicate
        duplicate = False
        For i = 1 To BaseComponentList.ListItems.Count
            If BaseComponentList.ListItems.Item(i).text = eFrm.Text1.text Then
                ' duplicate found
                duplicate = True
                Exit For
            End If
        Next i
        
        If eFrm.Result = True And eFrm.Text1.text <> "" And Not duplicate Then
            Dim ComponentList As ListItem
            Set ComponentList = BaseComponentList.ListItems.Add()
            ComponentList.text = eFrm.Text1.text
            mySQLStatement = "INSERT INTO [BaseComponent] (Name, GroupName) VALUES ('" & eFrm.Text1.text & "','" & ActiveGroupName & "')"
            dbConnection.Execute (mySQLStatement)
            Exit Sub
        ElseIf duplicate Then
            MsgBox "The name " & eFrm.Text1.text & " is already in use in group " & ActiveGroupName
        End If
    Loop
    
End Sub

Private Sub AddBasicEvents_Click()
    Dim bForm As New BEAssignment
    bForm.BaseComponentName.text = BaseComponentName.Caption
    Dim prevNBEs As Integer, i As Integer, cCol As Integer
    cCol = ModeCombo.ListIndex + 1
    
    prevNBEs = AssociatedEventsList.ColumnHeaders.Item(cCol).tag
    
    For i = 1 To prevNBEs
        If cCol = 1 Then
            bForm.SelectedBasicEventsList.ListItems.Add , , AssociatedEventsList.ListItems(i).text
        Else
            bForm.SelectedBasicEventsList.ListItems.Add , , AssociatedEventsList.ListItems(i).ListSubItems(cCol - 1).text
        End If
    Next i
    bForm.ModeName.text = ModeCombo.List(ModeCombo.ListIndex)
    bForm.ActiveModeID = ModeCombo.ItemData(ModeCombo.ListIndex)
    bForm.Show 1
    If (bForm.Result = True) Then
        
        'AssociatedEventsList.Clear
        For i = 1 To bForm.SelectedBasicEventsList.ListItems.Count
            If i > AssociatedEventsList.ListItems.Count Then
                AddBERow
            End If
            If cCol = 1 Then
                AssociatedEventsList.ListItems(i).text = bForm.SelectedBasicEventsList.ListItems.Item(i).text
            Else
                AssociatedEventsList.ListItems(i).ListSubItems(cCol - 1).text = bForm.SelectedBasicEventsList.ListItems.Item(i).text
            End If
        Next i
        For i = i To prevNBEs
            If cCol = 1 Then
                AssociatedEventsList.ListItems(i).text = ""
            Else
                AssociatedEventsList.ListItems(i).ListSubItems(cCol - 1).text = ""
            End If
        Next i
        AssociatedEventsList.ColumnHeaders(cCol).tag = bForm.SelectedBasicEventsList.ListItems.Count
        
    End If
    
End Sub

Private Sub AddGroup_Click()
    Dim eFrm As New EnterString
    Dim i As Integer, duplicate As Boolean
    eFrm.Caption = "Enter Data"
    eFrm.Label1.Caption = "Component Group Name"
    
    Do
        eFrm.Show 1
        If eFrm.Result = True And eFrm.Text1.text <> "" Then
            duplicate = False
            For i = 0 To Combo1.listCount - 1
                If Combo1.List(i) = eFrm.Text1.text Then
                    ' duplicate found
                    duplicate = True
                    Exit For
                End If
            Next i
            If duplicate Then
                MsgBox "There is a group with this name already.  Please choose a different name."
            Else
                nGroups = nGroups + 1
                Combo1.AddItem eFrm.Text1.text
                ActiveGroupName = eFrm.Text1.text
                Combo1.ListIndex = Combo1.listCount - 1
                RenameGroup.Enabled = True
                RemoveGroup.Enabled = True
                Exit Sub
            End If
        Else
            Exit Sub
        End If
    Loop
End Sub

Private Sub AssociatedEventsList_Click()
    RemoveBasicEvents.Enabled = True '(AssociatedEventsList.SelectedItem. > 0)
End Sub

Private Sub AssociatedEventsList_ColumnClick(ByVal ColumnHeader As MSComctlLib.ColumnHeader)
    ModeCombo.ListIndex = ColumnHeader.SubItemIndex
End Sub

Private Sub BaseComponentList_ItemClick(ByVal Item As MSComctlLib.ListItem)
    
    If FormMode = SelectBasicEvent Then
        ActiveName = Item.text
        Dim mySQLStatement As String
        Dim resultSet As rdoResultset
        mySQLStatement = "SELECT BaseCompID FROM [BaseComponent] WHERE Name = '" & ActiveName & "' AND GroupName = '" & ActiveGroupName & "'"
        Set resultSet = dbConnection.OpenResultset(mySQLStatement)
        If Not resultSet.EOF Then
            Dim rArray As Variant
            rArray = resultSet.GetRows(1)
            ActiveID = rArray(0, 0)
        Else
            MsgBox "Internal error.  statement " & mySQLStatement & NewLine & _
            "Failed to return any data"
        End If
        OKButton.Enabled = True
    End If
    If Item.text <> BaseComponentName.Caption Then
        SaveBEList BaseComponentName.Caption, ActiveGroupName
        BaseComponentName.Caption = Item.text
        LoadBEList BaseComponentName.Caption, ActiveGroupName
    End If
    RemoveBaseComponent.Enabled = True
    AddBasicEvents.Enabled = True
    RenameBaseComponent.Enabled = True
    Label3.Visible = True
    RemoveBasicEvents.Enabled = False
End Sub

Private Sub Combo1_Click()
    Dim mySQLStatement As String
    Dim rArray As Variant
    
    SaveBEList BaseComponentName.Caption, ActiveGroupName
    
    ActiveGroupName = Combo1.List(Combo1.ListIndex)
    mySQLStatement = "SELECT Name from [BaseComponent] WHERE GroupName = '" & ActiveGroupName & "'"
        
    Dim resultSet As rdoResultset
    Set resultSet = dbConnection.OpenResultset(mySQLStatement)
        
    BaseComponentList.ListItems.Clear
    Dim ComponentList As ListItem
    While Not resultSet.EOF
        rArray = resultSet.GetRows(1)
        Set ComponentList = BaseComponentList.ListItems.Add()
        'ComponentList.SmallIcon = X
        ComponentList.text = rArray(0, 0)
    Wend
    AssociatedEventsList.ListItems.Clear
    
    RemoveBaseComponent.Enabled = False
    AddBasicEvents.Enabled = False
    If FormMode = SelectBasicEvent Then OKButton.Enabled = False
    BaseComponentName.Caption = ""
    RenameBaseComponent.Enabled = False
    RemoveBasicEvents.Enabled = False
    Label3.Visible = False
    
    If ModeCombo.listCount > 0 Then AddBaseComponent.Enabled = True
End Sub

Private Sub MoveBENames(fromColumn As Integer, toColumn As Integer)
    Dim i As Integer
    For i = 1 To AssociatedEventsList.ListItems.Count
        If fromColumn = 1 Then
            If toColumn <> 1 Then
                AssociatedEventsList.ListItems(i).ListSubItems(toColumn - 1).text = AssociatedEventsList.ListItems(i).text
            End If
        Else
            If toColumn = 1 Then
                AssociatedEventsList.ListItems(i).text = AssociatedEventsList.ListItems(i).ListSubItems(fromColumn - 1).text
            Else
                AssociatedEventsList.ListItems(i).ListSubItems(toColumn - 1).text = AssociatedEventsList.ListItems(i).ListSubItems(fromColumn - 1).text
            End If
        End If
    Next i
End Sub

Private Sub ModeCombo_Click()
     ' called when the mode changes
    If DLLActive Then
        Dim modeID As Long
        If ModeCombo.ListIndex <> -1 Then
            modeID = ModeCombo.ItemData(ModeCombo.ListIndex)
            If SetModeID(modeID) = 0 Then
                MsgBox "Failed to set mode in risk monitor DLL.", , "Error"
            End If
        End If
    End If
    
    Dim i As Integer
    Dim c As Integer, j As Integer ', pPos As Integer, k As Integer, toPos As Integer
    c = 2
    Dim bNames As Collection
    Set bNames = New Collection
    
    For i = 1 To AssociatedEventsList.ListItems.Count
        bNames.Add AssociatedEventsList.ListItems(i).text
    Next i
    
    For i = 1 To ModeCombo.listCount
        
        If i <> ModeCombo.ListIndex + 1 Then
            If AssociatedEventsList.ColumnHeaders(i).Position <> c Then
                AssociatedEventsList.ColumnHeaders(i).Position = c
            End If
            c = c + 1
        Else
            AssociatedEventsList.ColumnHeaders(i).Position = 1
        End If
        
    Next
    
    AssociatedEventsList.Refresh
    
End Sub

Private Sub OKButton_Click()
    SaveBEList BaseComponentName.Caption, ActiveGroupName
    Me.Hide
End Sub

Private Sub RemoveBaseComponent_Click()
    Dim mySQLStatement As String
    mySQLStatement = "DELETE FROM BaseCompBE WHERE BaseCompID IN (SELECT BaseCompID FROM BaseComponent WHERE GroupName = '" & ActiveGroupName & "' AND Name = '" & BaseComponentName.Caption & "')"
    
    dbConnection.Execute (mySQLStatement)
    mySQLStatement = "DELETE FROM BaseComponent WHERE GroupName = '" & ActiveGroupName & "' AND Name = '" & BaseComponentName.Caption & "'"
    dbConnection.Execute (mySQLStatement)
    
    AssociatedEventsList.ListItems.Clear
    BaseComponentList.ListItems.Remove (BaseComponentList.SelectedItem.Index)
 
    Label3.Visible = False
    BaseComponentName.Caption = ""
    AddBasicEvents.Enabled = False
    If FormMode = SelectBasicEvent Then OKButton.Enabled = False
    RemoveBasicEvents.Enabled = False
    
End Sub

Private Sub RemoveBasicEvents_Click()
    Dim i As Integer, nextSpace As Integer
    nextSpace = 1
    For i = 1 To AssociatedEventsList.ListItems.Count
        
        If Not AssociatedEventsList.ListItems(i).Selected Then
            'Do While AssociatedEventsList.ListItems(nextSpace).Selected = True
            '    nextSpace = nextSpace + 1
            '    If nextSpace > AssociatedEventsList.ListItems.Count Then Exit Do
            'Loop
            'If nextSpace > AssociatedEventsList.ListItems.Count Then Exit For
            If ModeCombo.ListIndex + 1 = 1 Then
                AssociatedEventsList.ListItems(nextSpace).text = AssociatedEventsList.ListItems(i).text
            Else
                AssociatedEventsList.ListItems(nextSpace).ListSubItems(ModeCombo.ListIndex).text = AssociatedEventsList.ListItems(i).ListSubItems(ModeCombo.ListIndex).text
            End If
            nextSpace = nextSpace + 1
            'If nextSpace > AssociatedEventsList.ListItems.Count Then Exit For
        End If
    Next i
    AssociatedEventsList.ColumnHeaders.Item(ModeCombo.ListIndex + 1).tag = nextSpace - 1
    
    For i = nextSpace To AssociatedEventsList.ListItems.Count
        If ModeCombo.ListIndex + 1 = 1 Then
            AssociatedEventsList.ListItems(i).text = ""
        Else
            AssociatedEventsList.ListItems(i).ListSubItems(ModeCombo.ListIndex).text = ""
        End If
        
    Next i
    
    RemoveBasicEvents.Enabled = False
    
End Sub

Private Sub RemoveGroup_Click()
    Dim curIndex As Integer
    Dim mySQLString As String
    mySQLString = "DELETE FROM BaseCompBE WHERE BaseCompID IN (SELECT BaseCompID FROM BaseComponent WHERE GroupName = '" & ActiveGroupName & "')"
    dbConnection.Execute (mySQLString)
    mySQLString = "DELETE FROM BaseComponent WHERE GroupName = '" & ActiveGroupName & "'"
    dbConnection.Execute (mySQLString)
    
    AssociatedEventsList.ListItems.Clear
    
    curIndex = Combo1.ListIndex
    Combo1.RemoveItem Combo1.ListIndex
    If (curIndex > Combo1.listCount - 1) Then
        Combo1.ListIndex = curIndex - 1
        If (Combo1.listCount = 0) Then
            BaseComponentList.ListItems.Clear
            RemoveGroup.Enabled = False
            RenameGroup.Enabled = False
            AddBaseComponent.Enabled = False
            RemoveBaseComponent.Enabled = False
            RenameBaseComponent.Enabled = False
            AddBasicEvents.Enabled = False
            If FormMode = SelectBasicEvent Then OKButton.Enabled = False
            RemoveBasicEvents.Enabled = False
            Label3.Visible = False
            BaseComponentName.Caption = ""
        End If
    Else
        Combo1.ListIndex = curIndex
    End If
    
    'ActiveGroupName = Combo1.List(Combo1.ListIndex)

End Sub

Private Sub RenameBaseComponent_Click()
    ' which one is selected?
    Dim eFrm As New EnterString
    Dim mySQLStatement As String
    Dim i As Integer, duplicate As Boolean
        
    eFrm.Caption = "Enter Data"
    eFrm.Label1.Caption = "New Base Component Name"
    Do
        eFrm.Show 1
        If eFrm.Result = True And eFrm.Text1.text <> "" Then
            ' if the user didn't change the name then exit out
            If eFrm.Text1.text = BaseComponentName.Caption Then Exit Sub
            ' check to make sure that this name is not a duplicate
            duplicate = False
            For i = 1 To BaseComponentList.ListItems.Count
                If BaseComponentList.ListItems.Item(i).text = eFrm.Text1.text Then
                    ' duplicate found
                    duplicate = True
                    Exit For
                End If
            Next i
            
            If Not duplicate Then
                BaseComponentList.ListItems(BaseComponentList.SelectedItem.Index).text = eFrm.Text1.text
                mySQLStatement = "UPDATE BaseComponent SET Name = '" & eFrm.Text1.text & "' WHERE GroupName = '" & ActiveGroupName & "' AND Name = '" & BaseComponentName.Caption & "'"
                dbConnection.Execute (mySQLStatement)
                BaseComponentName.Caption = eFrm.Text1.text
                Exit Sub
            ElseIf duplicate Then
                MsgBox "The name " & eFrm.Text1.text & " is already in use in group " & ActiveGroupName
            End If
        Else
            Exit Sub
        End If
    Loop
End Sub

Private Sub RenameGroup_Click()
    Dim eFrm As New EnterString, duplicate As Boolean, i As Integer
    eFrm.Caption = "Enter Data"
    eFrm.Label1.Caption = "New Component Group Name"
    eFrm.Text1.text = ActiveGroupName
    
    Do
        eFrm.Show 1
        If eFrm.Result = True And eFrm.Text1.text <> "" Then
            duplicate = False
            For i = 0 To Combo1.listCount - 1
                If Combo1.List(i) = eFrm.Text1.text Then
                    ' duplicate found
                    duplicate = True
                    Exit For
                End If
            Next i
            If duplicate Then
                MsgBox "There is a group with this name already.  Please choose a different name."
            Else
                Dim curIndex As Integer
                Dim mySQLString As String
                mySQLString = "UPDATE BaseComponent SET GroupName = '" & eFrm.Text1.tabIndex & "' WHERE GroupName = '" & ActiveGroupName & "'"
                dbConnection.Execute (mySQLString)
                curIndex = Combo1.ListIndex
                Combo1.RemoveItem curIndex
                Combo1.AddItem eFrm.Text1.text, curIndex
                ActiveGroupName = eFrm.Text1.text
                Combo1.ListIndex = curIndex
                Exit Sub
            End If
        Else
            Exit Sub
        End If
    Loop
End Sub

Private Sub ModeExists(Enable As Boolean)
    Label1.Enabled = Enable
    Combo1.Enabled = Enable
    AddGroup.Enabled = Enable
    RenameGroup.Enabled = Enable
    RemoveGroup.Enabled = Enable
    BaseComponentList.Enabled = Enable
    AddBaseComponent.Enabled = Enable
    RenameBaseComponent.Enabled = Enable
    RemoveBaseComponent.Enabled = Enable
    ModeProperties.Enabled = Enable
    RemoveMode.Enabled = Enable
    Label3.Enabled = Enable
    BaseComponentName.Enabled = Enable
    AssociatedEventsList.Enabled = Enable
    AddBasicEvents.Enabled = Enable
    RemoveBasicEvents.Enabled = Enable
End Sub

Private Sub Form_Load()
    
    Dim mySQLStatement As String
    Dim resultSet As rdoResultset
    Dim rArray As Variant
    Dim i As Integer
        
    If ModeCount > 0 Then
        For i = 1 To ModeList.Count
            If ModeList.Item(i).ObjectInUse = True Then
                ModeCombo.AddItem ModeList.Item(i).ModeName
                ModeCombo.ItemData(ModeCombo.listCount - 1) = i
                AssociatedEventsList.ColumnHeaders.Add , , ModeList.Item(i).ModeName
            End If
        Next i
        ModeCombo.ListIndex = 0
    Else ' no records were found in the Mode table
        ModeExists False
    End If
    
    Select Case FormMode
    Case SelectBasicEvent
        Me.Caption = "Select a Base Component"
        OKButton.Enabled = False
    Case MapBasicEvents
        Me.Caption = "Map Basic Events to Base Components"
    End Select
    If FormMode = SelectBasicEvent Then OKButton.Enabled = False
    mySQLStatement = "SELECT DISTINCT GroupName from BaseComponent"
      
    Set resultSet = dbConnection.OpenResultset(mySQLStatement)
    nGroups = 0
    
    While Not resultSet.EOF
        rArray = resultSet.GetRows(1)
        nGroups = nGroups + 1
        Combo1.AddItem rArray(0, 0)
    Wend
    
    If nGroups = 0 Then
        RemoveGroup.Enabled = False
        RenameGroup.Enabled = False
        AddBaseComponent.Enabled = False
        RemoveBaseComponent.Enabled = False
        RenameBaseComponent.Enabled = False
        AddBasicEvents.Enabled = False
        If FormMode = SelectBasicEvent Then OKButton.Enabled = False
        RemoveBasicEvents.Enabled = False
    Else
        Combo1.ListIndex = 0
    End If
    
    Dim colHeader As ColumnHeader
    Set colHeader = BaseComponentList.ColumnHeaders.Add()
    colHeader.text = "Base Components"
    
    BaseComponentList.ColumnHeaders(1).Width = BaseComponentList.Width - 80
    
End Sub

Private Sub SaveBEList(name As String, GroupName As String)
    Dim mySQLStatement As String, i As Integer, nBEs As Integer, m As Integer
    Dim rArray As Variant
    Dim resultSet As rdoResultset
    
    If name = "" Or GroupName = "" Then Exit Sub
    mySQLStatement = "SELECT BaseCompID FROM [BaseComponent] WHERE " & _
        "Name = '" & name & "' AND GroupName = '" & GroupName & "'"
    Set resultSet = dbConnection.OpenResultset(mySQLStatement)
    Dim beName As String
    If Not resultSet.EOF Then
        rArray = resultSet.GetRows(1)
        mySQLStatement = "DELETE FROM [BaseCompBE] WHERE BaseCompID = " & rArray(0, 0) '& _

        dbConnection.Execute (mySQLStatement)
        nBEs = 0
        
        For i = 1 To AssociatedEventsList.ListItems.Count
            If AssociatedEventsList.ListItems.Item(i).text <> "" Then
                mySQLStatement = "INSERT INTO [BaseCompBE] (BaseCompID,BEName,ModeID) VALUES (" & rArray(0, 0) & ",'" & AssociatedEventsList.ListItems(i).text & "'," & ModeCombo.ItemData(0) & ")"
                dbConnection.Execute (mySQLStatement)
            End If
            'nBEs = nBEs + 1
        Next i
            
        For m = 1 To ModeCombo.listCount - 1
            For i = 1 To AssociatedEventsList.ListItems.Count
                beName = AssociatedEventsList.ListItems(i).ListSubItems(m).text
                If beName <> "" Then
                    mySQLStatement = "INSERT INTO [BaseCompBE] (BaseCompID,BEName,ModeID) VALUES (" & rArray(0, 0) & ",'" & beName & "'," & ModeCombo.ItemData(m) & ")"
                    dbConnection.Execute (mySQLStatement)
                End If
                
            Next i
        Next m
    End If
    
End Sub

Private Sub AddBERow()
    AssociatedEventsList.ListItems.Add
    Dim i As Integer
    For i = 2 To ModeCombo.listCount
        AssociatedEventsList.ListItems(AssociatedEventsList.ListItems.Count).ListSubItems.Add
    Next i
End Sub

Private Sub LoadBEList(name As String, GroupName As String)
    Dim mySQLStatement As String, i As Integer, m As Integer, baseCompID As Integer
    Dim rArray As Variant, beName As String
    Dim resultSet As rdoResultset
    
    mySQLStatement = "SELECT BaseCompID FROM [BaseComponent] WHERE " & _
        "Name = '" & name & "' AND GroupName = '" & GroupName & "'"
    Set resultSet = dbConnection.OpenResultset(mySQLStatement)
        
    AssociatedEventsList.ListItems.Clear
    
    If Not resultSet.EOF Then
        rArray = resultSet.GetRows(1)
        baseCompID = rArray(0, 0)
        For m = 1 To ModeCombo.listCount
            mySQLStatement = "SELECT BEName FROM BaseCompBE WHERE BaseCompID = " & baseCompID & _
                " AND ModeID = " & ModeCombo.ItemData(m - 1)
                
            Set resultSet = dbConnection.OpenResultset(mySQLStatement)
            
            Dim BECount As Integer
            BECount = 0
            While Not resultSet.EOF
                rArray = resultSet.GetRows(1)
                BECount = BECount + 1
                beName = rArray(0, 0)
                If m = 1 Then
                    If (AssociatedEventsList.ListItems.Count < BECount) Then
                        AddBERow
                    End If
                    AssociatedEventsList.ListItems.Item(BECount).text = beName
                    
                Else
                    If (AssociatedEventsList.ListItems.Count < BECount) Then
                        AddBERow
                    End If
                    AssociatedEventsList.ListItems.Item(BECount).ListSubItems(m - 1).text = beName
                End If
            Wend
            AssociatedEventsList.ColumnHeaders.Item(m).tag = BECount
        Next m
    End If
    
End Sub

Private Sub addmode_Click()
    Dim modeID As Integer, Mode As ModeClass, i As Integer
    Set Mode = New ModeClass
    Mode.CreateNewMode
    If Mode.addmode(modeID) Then
        Dim NewMode As ModeClass
        Set NewMode = ModeList.Item(modeID)
        
        ' now add it to the list view and combo box
        Dim cH As ColumnHeader
        Set cH = AssociatedEventsList.ColumnHeaders.Add(, , NewMode.ModeName)
        cH.tag = 0
        For i = 1 To AssociatedEventsList.ListItems.Count
            AssociatedEventsList.ListItems(i).ListSubItems.Add
        Next i
        
        ModeCombo.AddItem NewMode.ModeName
        ModeCombo.ItemData(ModeCombo.listCount - 1) = modeID
        ModeCombo.ListIndex = 0
        
        If ModeCount = 1 Then
            If nGroups > 0 Then
                RemoveGroup.Enabled = True
                RenameGroup.Enabled = True
                AddBaseComponent.Enabled = True
                BaseComponentList.Enabled = True
                AssociatedEventsList.Enabled = True
                Combo1.Enabled = True
            End If
            AddGroup.Enabled = True
            BaseComponentName.Enabled = True
            Label3.Enabled = True
            RemoveMode.Enabled = True
            ModeProperties.Enabled = True
            Label1.Enabled = True
        End If
    End If
    
End Sub

Private Sub ModeProperties_Click()
    Dim Mode As ModeClass, tempMode As ModeClass, frmMode As ModeProperties, holeFound As Boolean
    Set frmMode = New ModeProperties
    
    Dim modeID As Integer
    
    Set Mode = ModeList.Item(ModeCombo.ListIndex + 1)
    Set tempMode = New ModeClass
    tempMode.CopyMode Mode
    
    Set frmMode.ModeObject = tempMode
    frmMode.ModeIndex = ModeCombo.ItemData(ModeCombo.ListIndex)
    frmMode.Show 1
    
    If frmMode.Result = True Then
        Mode.CopyMode tempMode
        ' update the database now
        Dim mySQLStatement As String, resultSet As rdoResultset
        mySQLStatement = "UPDATE [Mode] SET " & _
            "ModeName = '" & Mode.ModeName & "', " & _
            "ModeDesc = '" & Mode.ModeDescription & "', " & _
            "SaphireProjPath = '" & Mode.ProjectPath & "', " & _
            "BaselineRisk = " & Mode.BaselineRisk & ", " & _
            "MediumRisk = " & Mode.MediumRisk & ", " & _
            "HighRisk = " & Mode.HighRisk & ", " & _
            "ModeColor = " & Mode.ModeColor & _
            " WHERE modeID = " & ModeCombo.ItemData(ModeCombo.ListIndex)
        dbConnection.Execute (mySQLStatement)
        ' now update the list view and combo box
        AssociatedEventsList.ColumnHeaders.Item(ModeCombo.ListIndex + 1).text = Mode.ModeName
        ModeCombo.List(ModeCombo.ListIndex) = Mode.ModeName
    End If
End Sub

Private Sub RemoveMode_Click()
    Dim mySQLStatement As String, resultSet As rdoResultset, resultSet2 As rdoResultset
    Dim l As ListMessage, rArray As Variant, wName As String, wDesc As String
    
    mySQLStatement = "SELECT DISTINCT WorkspaceID FROM WorkspaceMode WHERE ModeID = " & _
        ModeCombo.ItemData(ModeCombo.ListIndex)
    Set resultSet = dbConnection.OpenResultset(mySQLStatement)
    
    If Not resultSet.EOF Then
        Set l = New ListMessage
        l.boxcaption = "Error"
        l.message = "You may not remove this mode because the following workspaces are using it:"
        l.style = vbOKOnly
        l.AddHeader "Workspace Name"
        l.AddHeader "Workspace Description"
        While Not resultSet.EOF
            rArray = resultSet.GetRows(1)
            mySQLStatement = "SELECT WorkspaceName, WorkspaceDesc FROM [Workspace] WHERE WorkspaceID = " & rArray(0, 0)
            Set resultSet2 = dbConnection.OpenResultset(mySQLStatement)
            rArray = resultSet2.GetRows(1)
            If Not IsNull(rArray(0, 0)) Then wName = rArray(0, 0)
            If Not IsNull(rArray(1, 0)) Then wDesc = rArray(1, 0)
            l.AddRow wName
            l.AddRowSubText wDesc
        Wend
        l.Show vbModal
    Else
        mySQLStatement = "SELECT DISTINCT WorkspaceID FROM RiskPeriods WHERE ModeID = " & _
            ModeCombo.ItemData(ModeCombo.ListIndex)
        Set resultSet = dbConnection.OpenResultset(mySQLStatement)
        If Not resultSet.EOF Then
            Set l = New ListMessage
            l.boxcaption = "Program Error"
            l.message = "You may not remove this mode because the following workspaces are using it [RiskPeriods Table]:"
            l.style = vbOKOnly
            l.AddHeader "Workspace Name"
            l.AddHeader "Workspace Description"
            While Not resultSet.EOF
                rArray = resultSet.GetRows(1)
                mySQLStatement = "SELECT WorkspaceName, WorkspaceDesc FROM [Workspace] WHERE WorkspaceID = " & rArray(0, 0)
                Set resultSet2 = dbConnection.OpenResultset(mySQLStatement)
                rArray = resultSet2.GetRows(1)
                If Not IsNull(rArray(0, 0)) Then wName = rArray(0, 0)
                If Not IsNull(rArray(1, 0)) Then wDesc = rArray(1, 0)
                l.AddRow wName
                l.AddRowSubText wDesc
            Wend
            l.Show vbModal
        Else
            mySQLStatement = "DELETE FROM ProcMode WHERE ModeID = " & _
                ModeCombo.ItemData(ModeCombo.ListIndex)
            dbConnection.Execute (mySQLStatement)
            mySQLStatement = "DELETE FROM BaseCompBE WHERE ModeID = " & _
                ModeCombo.ItemData(ModeCombo.ListIndex)
            dbConnection.Execute (mySQLStatement)
            mySQLStatement = "DELETE FROM Mode WHERE ModeID = " & _
                ModeCombo.ItemData(ModeCombo.ListIndex)
            dbConnection.Execute (mySQLStatement)
            ' clear the mode object out from the modelist
            ModeList.Item(ModeCombo.ListIndex + 1).CreateNewMode
            ModeCount = ModeCount - 1
            Dim wMode As Integer, i As Integer
            For wMode = ModeCombo.ListIndex + 1 To ModeCount
                For i = 1 To AssociatedEventsList.ListItems.Count
                    If (wMode = 1) Then
                        AssociatedEventsList.ListItems(i).text = AssociatedEventsList.ListItems(i).ListSubItems(1).text
                    Else
                        AssociatedEventsList.ListItems(i).ListSubItems(wMode - 1).text = AssociatedEventsList.ListItems(i).ListSubItems(wMode).text
                    End If
                Next i
            Next wMode
            If (ModeCount > 0) Then
                For i = 1 To AssociatedEventsList.ListItems.Count
                    AssociatedEventsList.ListItems(i).ListSubItems.Remove (ModeCount)
                Next i
            End If
            
            AssociatedEventsList.ColumnHeaders.Remove (ModeCombo.ListIndex + 1)
            AssociatedEventsList.Refresh
            ModeCombo.RemoveItem (ModeCombo.ListIndex)
            If ModeCombo.listCount > 0 Then
                ModeCombo.ListIndex = 0
            Else
                ModeExists False
            End If
        End If
    
    End If
    
End Sub
