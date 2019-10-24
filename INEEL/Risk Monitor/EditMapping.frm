VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form EditMapping 
   Caption         =   "EditMapping"
   ClientHeight    =   6480
   ClientLeft      =   165
   ClientTop       =   450
   ClientWidth     =   8880
   BeginProperty Font 
      Name            =   "Arial"
      Size            =   9.75
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   LinkTopic       =   "Form1"
   ScaleHeight     =   6480
   ScaleWidth      =   8880
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton EditGorBC 
      Caption         =   "Edit"
      Height          =   495
      Left            =   2880
      TabIndex        =   12
      Top             =   5160
      Width           =   855
   End
   Begin VB.CommandButton EditBtn 
      Caption         =   "Edit"
      Height          =   495
      Left            =   7200
      TabIndex        =   11
      Top             =   5160
      Width           =   855
   End
   Begin VB.CommandButton AddBtn 
      Caption         =   "Add"
      Height          =   495
      Left            =   360
      TabIndex        =   10
      Top             =   5160
      Width           =   855
   End
   Begin VB.CommandButton RemoveBtn 
      Caption         =   "Remove"
      Height          =   495
      Left            =   1560
      TabIndex        =   9
      Top             =   5160
      Width           =   975
   End
   Begin VB.CommandButton DoneBtn 
      Caption         =   "Done"
      Height          =   495
      Left            =   4080
      TabIndex        =   8
      Top             =   5880
      Width           =   855
   End
   Begin VB.CommandButton AddBEBtn 
      Caption         =   "Add"
      Height          =   495
      Left            =   4800
      TabIndex        =   7
      Top             =   5160
      Width           =   855
   End
   Begin VB.CommandButton RemoveBEBtn 
      Caption         =   "Remove "
      Height          =   495
      Left            =   6000
      TabIndex        =   6
      Top             =   5160
      Width           =   855
   End
   Begin MSComctlLib.TreeView GroupsBComps 
      Height          =   3975
      Left            =   120
      TabIndex        =   4
      Top             =   960
      Width           =   4335
      _ExtentX        =   7646
      _ExtentY        =   7011
      _Version        =   393217
      Style           =   7
      Appearance      =   1
   End
   Begin MSComctlLib.ListView BasicEventsLV 
      Height          =   3975
      Left            =   4560
      TabIndex        =   3
      Top             =   960
      Width           =   4815
      _ExtentX        =   8493
      _ExtentY        =   7011
      View            =   3
      LabelEdit       =   1
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
   Begin VB.ComboBox Mode 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   315
      Left            =   3840
      TabIndex        =   0
      Text            =   "Combo1"
      Top             =   360
      Width           =   1695
   End
   Begin VB.Label BasicEventsLbl 
      Caption         =   "BasicEvents"
      Height          =   255
      Left            =   5280
      TabIndex        =   5
      Top             =   720
      Width           =   1455
   End
   Begin VB.Label GroupTxt 
      Caption         =   "Groups And Basic Components"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   240
      TabIndex        =   2
      Top             =   720
      Width           =   2415
   End
   Begin VB.Label ModeTxt 
      Caption         =   "Mode"
      Height          =   255
      Left            =   4320
      TabIndex        =   1
      Top             =   120
      Width           =   615
   End
End
Attribute VB_Name = "EditMapping"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private GroupsList As Variant
Private BCompsList As Variant
Private BEvents As Variant
Public Criteria As String
Public SelectedAvailBE As Integer
Private bForm As New AvalBEs
Public AddNodeSuc As Boolean
Public AddNodeName As String
Public AddNodeDesc As String
Private modeArray As Variant
Private groupArray As Variant
Public editName As Boolean
Private NumModes As Integer


Private Declare Function SystemCount Lib "riskMon" (ByVal Criteria As String) As Long
Private Declare Function GetSystemName Lib "riskMon" (ByVal Index As Long, ByRef sysName As String, ByVal desc As String, ByVal Criteria As Long) As Long

Private Declare Function GetNumOfBComps Lib "riskMon" (ByVal sysName As String) As Long
Private Declare Function GetBCompName Lib "riskMon" (ByVal Index As Long, ByVal sysName As String, ByRef BCompName As String) As Boolean

Private Declare Function GetNumOfBE Lib "riskMon" (ByVal sysName As String, ByVal BCompName As String) As Long
Private Declare Function GetBEName Lib "riskMon" (ByVal Index As Long, ByVal sysName, ByVal BCompName As String, ByRef beName As String, ByRef BEDesc As String) As Long

Private Declare Function SetModeID Lib "riskMon" (ByVal NewModeID As Long) As Long
Private Declare Function SuspendUpdates Lib "riskMon" () As Long
Private Declare Function ResumeUpdates Lib "riskMon" () As Long



Private Sub AddBEBtn_Click()

    Dim BCompID As Integer
    'only add if an item in the tree has been selected
    If Not GroupsBComps.SelectedItem Is Nothing Then
        'only add if a bace component group has been selected
        If GroupsBComps.SelectedItem.Child Is Nothing Then
            BCompID = GroupsBComps.SelectedItem.tag
            bForm.Show 1
            AddNodeSuc = False
            AddNodeSuc = bForm.AddSuc
            'only add if they clicked ok or add
            If AddNodeSuc Then
                Dim myListItem As ListItem
                Set myListItem = BasicEventsLV.ListItems.Add(, , AddNodeName)
                myListItem.ListSubItems.Add , , AddNodeDesc
                myListItem.tag = BCompID
                mySQLStatement = "UPDATE BaseCompBE SET BaseCompID = " & BCompID & " WHERE (((BaseCompBE.BaseCompID)= -1) AND ((BaseCompBE.BEName)='" & BasicEventsLV.SelectedItem.text & " '));"
                Set resultSet = dbConnection2.OpenResultset(mySQLStatement, rdOpenKeyset)
            End If
        Else
            MsgBox "You must select a Base Component to add to."
        End If
    Else
        
    End If
    
    
    
    
    
    
    
    
    
End Sub

Private Sub DoneBtn_Click()
    Unload bForm
    'let the dll continue the updates
    'ResumeUpdates
    Unload Me
End Sub

Private Sub EditBtn_Click()
    Dim EditFrom As AddNode
    Dim YNCancel As Boolean
    'if no basic event selected dont edit
    If Not BasicEventsLV.SelectedItem Is Nothing Then
        AddNodeName = BasicEventsLV.SelectedItem.text
        AddNodeDesc = BasicEventsLV.SelectedItem.ListSubItems(BasicEventsLV.SelectedItem.Index).text
        'stop themm from editing the name
        editName = False
        AddNode.Show vbModal
        'if they clicked add
        If AddNodeSuc Then
            BasicEventsLV.SelectedItem.text = AddNodeName
            BasicEventsLV.SelectedItem.ListSubItems(1).text = AddNodeDesc
            'associate the basic event with the base component in the database
            mySQLStatement = "UPDATE BaseCompBE SET BEDesc = '" & AddNodeDesc & "' WHERE BEName = '" & AddNodeName & "';"
            Set resultSet = dbConnection2.OpenResultset(mySQLStatement, rdOpenKeyset)
    
        End If
    Else
    MsgBox "No Basic Event Selected"
    
    End If
    Unload AddNode
    
    
End Sub

Private Sub EditGorBC_Click()
    Dim EditFrom As AddNode
    Dim YNCancel As Boolean
    
    'only edit if an item in the treeview has been selected
    If Not GroupsBComps.SelectedItem Is Nothing Then
        'if it is a Base componet
        If GroupsBComps.SelectedItem.Child Is Nothing And Not GroupsBComps.SelectedItem.parent Is Nothing Then
            AddNodeName = GroupsBComps.SelectedItem.text
            editName = True
            AddNode.Show vbModal
            If AddNodeSuc Then
                GroupsBComps.SelectedItem.text = AddNodeName
                        
                mySQLStatement = "UPDATE BaseComponent SET BaseCompDesc = '" & AddNodeDesc & "', Name = '" & AddNodeName & "' WHERE BaseCompID = " & GroupsBComps.SelectedItem.tag & ";"
                Set resultSet = dbConnection2.OpenResultset(mySQLStatement, rdOpenKeyset)
            End If
        'if it is a base component group
        Else
            Dim oldname As String
            
            AddNodeName = GroupsBComps.SelectedItem.text
            oldname = AddNodeName
            editName = True
            AddNode.Show vbModal
            If AddNodeSuc Then
                GroupsBComps.SelectedItem.text = AddNodeName
                        
                mySQLStatement = "UPDATE BaseCompGroups SET GroupDesc = '" & AddNodeDesc & "', GroupName = '" & AddNodeName & "' Where GroupName = '" & oldname & "' And ModeID = " & (modeArray(0, Mode.ListIndex)) & ";"
                Set resultSet = dbConnection2.OpenResultset(mySQLStatement, rdOpenKeyset)
            End If
        End If
    Else
    MsgBox "No Basic Event Selected"
    
    End If
    Unload AddNode
End Sub

Private Sub Form_Load()
    Dim NumOfSys As Integer
    Dim NumOfBComps As Integer
    Dim NumOfBE As Integer
    Dim sysName As String * 27
    Dim baseCompName As String * 27
    Dim beName As String * 27
    Dim groupArray As Variant
    Dim BCArray As Variant
   
    Dim BEDesc As String
    Dim success As Long
    
    Dim i, j, k As Integer
    Dim mySQLStatement As String
    
    'Load the Modes
    'get lise of modes
    Mode.Clear
    'add the headers
    BasicEventsLV.ColumnHeaders.Add , , "BE Name", (BasicEventsLV.Width - 60) * 1 / 3
    BasicEventsLV.ColumnHeaders.Add , , "BE Description", (BasicEventsLV.Width - 60) * 2 / 3
   
    
    
    mySQLStatement = "SELECT ModeID, ModeName FROM Mode"
    
    Set resultSet = dbConnection2.OpenResultset(mySQLStatement, rdOpenKeyset)
    ' Run time error 40071 will be generated if no connection is present by this statement

    'check to make sure result was returned
    If (resultSet.EOF) Then
        MsgBox "No Modes Found", vbInformation
        Exit Sub
    End If
    
    'determine number of rows
    Dim numRows As Integer
    While Not resultSet.EOF
        resultSet.MoveNext
        numRows = numRows + 1
        
    Wend
    NumModes = numRows
    
    'get specified number of rows
    resultSet.MoveFirst
    modeArray = resultSet.GetRows(numRows)
  
    For i = 0 To numRows - 1
        Dim ModeObj As ComboBox
        If modeArray(0, i) > 0 Then
            Mode.AddItem modeArray(1, i)
            Mode.ItemData(i) = modeArray(0, i)
            
        End If
    Next i
    Mode.ListIndex = 0
    Dim TestString As String
    TestString = "HEllo I am #" & Mode.ListIndex & " Yes"
    
    
    'Load the tree view
    LoadTree
    
    
    NumAvailBes = 0
    i = 0
    mySQLStatement = "SELECT DISTINCT BaseCompBE.BEName, BaseCompBE.BEDesc From BaseCompBE WHERE (((BaseCompBE.BaseCompID)=-1));"
    Set resultSet = dbConnection2.OpenResultset(mySQLStatement, rdOpenKeyset)
    While Not resultSet.EOF
        NumAvailBes = NumAvailBes + 1
        resultSet.MoveNext
    Wend
    If NumAvailBes > 0 Then
    
        resultSet.MoveFirst
        Dim rArray2 As Variant
        rArray2 = resultSet.GetRows(NumAvailBes)
        For i = 0 To NumAvailBes - 1
                
                'bForm.SelectedBEList.ListItems(i).Text = rarray2(i, 0)
                
                Dim myListItem As ListItem
                Set myListItem = bForm.SelectedBEList.ListItems.Add(, , rArray2(0, i))
                myListItem.ListSubItems.Add , , rArray2(1, i)
        Next i
    End If
    bForm.SelectedBEList.ColumnHeaders.Add , , "BE Name", (bForm.SelectedBEList.Width - 60) * 1 / 3
    bForm.SelectedBEList.ColumnHeaders.Add , , "BE Description", (bForm.SelectedBEList.Width - 60) * 2 / 3
    
    
    'ListItem.Tag = BasicEventsLV.SelectedItem.Tag

    
    
End Sub





Private Sub LoadTree()
    ' Set Treeview control properties.
    GroupsBComps.Nodes.Clear
    GroupsBComps.LineStyle = tvwRootLines  ' Linestyle 1
    
    ' Add Node objects.
    Dim nodX As Node  ' Declare Node variable.
    Dim num, num2 As Integer
    Dim k As Integer
    mySQLStatement = "SELECT DISTINCT BaseCompGroups.GroupName, BaseCompGroups.GroupDesc, BaseCompGroups.GroupID FROM BaseCompGroups WHERE (((BaseCompGroups.ModeID)=" & (modeArray(0, Mode.ListIndex)) & "));"
 
    Set resultSet = dbConnection2.OpenResultset(mySQLStatement, rdOpenKeyset)
    i = 0
    k = 0
    Dim Key As String
    num = 0
    RowReturn = 0
    While Not resultSet.EOF
        RowReturn = RowReturn + 1
        resultSet.MoveNext
    Wend
    
    If RowReturn > 0 Then
    resultSet.MoveFirst
    groupArray = resultSet.GetRows(RowReturn)
    For k = 0 To RowReturn - 1
        Set nodX = GroupsBComps.Nodes.Add(, , "Group" & CStr(k), groupArray(0, k))
       
         j = 0
        
        'fix so that it gets the selected
        mySQLStatement = "SELECT DISTINCT BaseComponent.Name, BaseComponent.BaseCompDesc, BaseComponent.BaseCompID FROM BaseComponent WHERE (((BaseComponent.GroupID)=  " & groupArray(2, k) & "));"
        Set resultSet2 = dbConnection2.OpenResultset(mySQLStatement, rdOpenKeyset)
        
        RowReturn = 0
        While Not resultSet2.EOF
            RowReturn = RowReturn + 1
            resultSet2.MoveNext
        Wend
        Dim rarray As Variant
        If RowReturn > 0 Then
            resultSet2.MoveFirst
            rarray = resultSet2.GetRows(RowReturn)
        
            For i = 0 To RowReturn - 1
                Set nodX = GroupsBComps.Nodes.Add("Group" & CStr(k), tvwChild, "BC" & CStr(i) & CStr(rarray(2, i)), rarray(0, i))
                nodX.tag = rarray(2, i)
               
                j = j + 1
                
            Next i
            
            
        
        End If
        
    Next k
    End If
    GroupsBComps.Refresh
    
End Sub


   
Private Sub Mode_Click()
    BasicEventsLV.ListItems.Clear
    LoadTree
End Sub

Private Sub GroupsBComps_click()
    

    
    'add the Basic Events in
    BasicEventsLV.ListItems.Clear
    Dim BCompID As Integer
    Dim numRows As Integer
    Dim BEarray As Variant
    If Not GroupsBComps.SelectedItem Is Nothing Then
        If GroupsBComps.SelectedItem.Child Is Nothing And Not GroupsBComps.SelectedItem.parent Is Nothing Then
            BCompID = GroupsBComps.SelectedItem.tag
            mySQLStatement = "SELECT BaseCompBE.BEName, BaseCompBE.BEDesc, BaseCompBE.BaseCompID, BaseCompBE.ModeID FROM BaseCompBE WHERE (((BaseCompBE.BaseCompID)=" & GroupsBComps.SelectedItem.tag & ") AND ((BaseCompBE.ModeID)=" & (modeArray(0, Mode.ListIndex)) & "));"
            
            Set resultSet = dbConnection2.OpenResultset(mySQLStatement, rdOpenKeyset)
            Dim lItem As ListItem
            While Not resultSet.EOF
                resultSet.MoveNext
                numRows = numRows + 1
            Wend
            
            'get specified number of rows
            If numRows > 0 Then
                resultSet.MoveFirst
                BEarray = resultSet.GetRows(numRows)
                For i = 0 To numRows - 1
                    Dim myListItem As ListItem
                    Set myListItem = BasicEventsLV.ListItems.Add(, , BEarray(0, i))
                    myListItem.ListSubItems.Add , , BEarray(1, i)
                    myListItem.tag = BEarray(2, i)
                                       
                Next i
           End If
        
        End If
    End If
End Sub

Private Sub RemoveBEBtn_Click()
    Dim BCompID As Integer
    If Not BasicEventsLV.SelectedItem Is Nothing Then
        BCompID = BasicEventsLV.SelectedItem.tag
        Dim AlreadyExists As Boolean
        AlreadyExists = False
        Dim i As Integer
        For i = 1 To bForm.SelectedBEList.ListItems.Count
            If bForm.SelectedBEList.ListItems(i).text = BasicEventsLV.SelectedItem.text Then
                AlreadyExists = True
            End If
            
        Next i
        If (AlreadyExists = False) Then
            mySQLStatement = "UPDATE BaseCompBE SET BaseCompID = -1 WHERE (((BaseCompBE.BaseCompID)= " & BCompID & ") AND ((BaseCompBE.BEName)='" & BasicEventsLV.SelectedItem.text & " '));"
            
            Set resultSet = dbConnection2.OpenResultset(mySQLStatement, rdOpenKeyset)
            Dim myListItem As ListItem
            Set myListItem = bForm.SelectedBEList.ListItems.Add(, , BasicEventsLV.SelectedItem.text)
        
            myListItem.ListSubItems.Add , , BasicEventsLV.SelectedItem.SubItems(1)
            myListItem.tag = BasicEventsLV.SelectedItem.tag
            BasicEventsLV.ListItems.Remove (BasicEventsLV.SelectedItem.Index)
        Else
            mySQLStatement = "DELETE BaseCompBE SET BaseCompID = -1 WHERE (((BaseCompBE.BaseCompID)= " & BCompID & ") AND ((BaseCompBE.BEName)='" & BasicEventsLV.SelectedItem.text & " '));"
            
            Set resultSet = dbConnection2.OpenResultset(mySQLStatement, rdOpenKeyset)

        End If
    End If
    
End Sub
Private Sub ADDbtn_Click()
    Dim BCompID As Integer
    'If Not GroupsBComps.SelectedItem Is Nothing Then
    If 1 > 2 Then
        If GroupsBComps.SelectedItem.Child Is Nothing Then
            BCompID = GroupsBComps.SelectedItem.tag
            bForm.Show 1
            AddNodeSuc = False
            AddNodeSuc = bForm.AddSuc
            If AddNodeSuc Then
                Dim myListItem As ListItem
                Dim k As Integer
                k = BasicEventsLV.SelectedItem
                Set myListItem = BasicEventsLV.ListItems.Add(, , AddNodeName)
                myListItem.ListSubItems.Add , , AddNodeDesc
                myListItem.tag = BCompID
                Set resultSet = dbConnection2.OpenResultset(mySQLStatement, rdOpenKeyset)
                
            End If
        Else
            BCompID = GroupsBComps.SelectedItem.tag
            bForm.Show 1
            AddNodeSuc = False
            AddNodeSuc = bForm.AddSuc
            If AddNodeSuc Then
                 Set myListItem = BasicEventsLV.ListItems.Add(, , AddNodeName)
                myListItem.ListSubItems.Add , , AddNodeDesc
                myListItem.tag = BCompID
                mySQLStatement = "UPDATE BaseCompBE SET BaseCompID = " & BCompID & " WHERE (((BaseCompBE.BaseCompID)= -1) AND ((BaseCompBE.BEName)='" & BasicEventsLV.SelectedItem.text & " '));"
                Set resultSet = dbConnection2.OpenResultset(mySQLStatement, rdOpenKeyset)
                
            End If
            
        End If
    Else
        'MsgBox "You must select a Base Component to add to."
    End If
    
    
    
    
    
    
    
    
    
    
    
    
End Sub

Private Sub RemoveBtn_Click()
    'If Not GroupsBComps.SelectedItem Is Nothing Then
    If 1 > 2 Then
        If GroupsBComps.SelectedItem.Child Is Nothing Then
            While BasicEventsLV.ListItems.Count > 0
                BasicEventsLV.SelectedItem = BasicEventsLV.ListItems(1)
                RemoveBEBtn_Click
            Wend
            
        Else
            Dim parent As Node
            Set parent = GroupsBComps.SelectedItem
            Dim j, total As Integer
            While Not parent.Child Is Nothing
                GroupsBComps.SelectedItem = parent.Child
                GroupsBComps_click
                total = BasicEventsLV.ListItems.Count
                For j = 1 To total
                    BasicEventsLV.SelectedItem = BasicEventsLV.ListItems(1)
                    RemoveBEBtn_Click
                Next j
                GroupsBComps.Nodes.Remove (parent.Child.Index)

            Wend

        End If
        
    Else
        'MsgBox "No Item Selected"
    End If
End Sub
