VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form EditMapping 
   Caption         =   "EditMapping"
   ClientHeight    =   5940
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   10125
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
   ScaleHeight     =   5940
   ScaleWidth      =   10125
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton AddBtn 
      Caption         =   "Add"
      Height          =   495
      Left            =   1560
      TabIndex        =   10
      Top             =   5160
      Width           =   1095
   End
   Begin VB.CommandButton RemoveBtn 
      Caption         =   "Remove"
      Height          =   495
      Left            =   240
      TabIndex        =   9
      Top             =   5160
      Width           =   1095
   End
   Begin VB.CommandButton DoneBtn 
      Caption         =   "Done"
      Height          =   495
      Left            =   8760
      TabIndex        =   8
      Top             =   5160
      Width           =   1215
   End
   Begin VB.CommandButton AddBEBtn 
      Caption         =   "Add Basic Events"
      Height          =   495
      Left            =   5280
      TabIndex        =   7
      Top             =   5160
      Width           =   1335
   End
   Begin VB.CommandButton RemoveBEBtn 
      Caption         =   "Remove Basic Events"
      Height          =   495
      Left            =   6840
      TabIndex        =   6
      Top             =   5160
      Width           =   1335
   End
   Begin MSComctlLib.TreeView GroupsBComps 
      Height          =   3975
      Left            =   120
      TabIndex        =   4
      Top             =   960
      Width           =   4935
      _ExtentX        =   8705
      _ExtentY        =   7011
      _Version        =   393217
      Style           =   7
      Appearance      =   1
   End
   Begin MSComctlLib.ListView BasicEventsLV 
      Height          =   3975
      Left            =   5160
      TabIndex        =   3
      Top             =   960
      Width           =   4815
      _ExtentX        =   8493
      _ExtentY        =   7011
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
      Left            =   4320
      Sorted          =   -1  'True
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
      Left            =   4920
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
    
    Private Sub AddBasicEvents_Click()
    
    Dim i As Integer
    Dim NumAvailBEs As Integer
    Dim AvailBEs As Variant
    Dim prevNBEs As Integer
    
    'Fill the AvailBEList.
    NumAvailBEs = 0
    i = 0
    mySQLStatement = "SELECT DISTINCT BaseCompBE.BEName, BaseCompBE.BEDesc From BaseCompBE WHERE (((BaseCompBE.BaseCompID)=-1));"
    Set resultSet = dbConnection.OpenResultset(mySQLStatement, rdOpenKeyset)
    
    While Not resultSet.EOF
            Dim rarray As Variant
            rarray = resultSet.GetRows(1)
            bForm.SelectedBasicEventsList.ListItems(i).Text = rarray(i, 0)
            bForm.SelectedBasicEventsList.ListSubItems(cCol - 1).Text = rarray(i, 1)
            
    Wend
    
    'BasicEventsLV.ListItems(i).text =
    
    
    prevNBEs = AssociatedEventsList.ColumnHeaders.Item(cCol).Tag
    bForm.Show 1
    If (bForm.Result = True) Then
        
        'AssociatedEventsList.Clear
        For i = 1 To bForm.SelectedBasicEventsList.ListItems.Count
            If i > AssociatedEventsList.ListItems.Count Then
                AddBERow
            End If
            If cCol = 1 Then
                BasicEventsLV.ListItems(i).Text = bForm.SelectedBasicEventsList.ListItems.Item(i).Text
            Else
                BasicEventsLV.ListItems(i).ListSubItems(cCol - 1).Text = bForm.SelectedBasicEventsList.ListItems.Item(i).Text
            End If
        Next i
        For i = i To prevNBEs
            If cCol = 1 Then
                BasicEventsLV.ListItems(i).Text = ""
            Else
                BasicEventsLV.ListItems(i).ListSubItems(cCol - 1).Text = ""
            End If
        Next i
        BasicEventsLV.ColumnHeaders(cCol).Tag = bForm.SelectedBasicEventsList.ListItems.Count
        
    End If
    
End Sub
    
End Sub


Private Sub AddBtn_Click()
    AddNode.Show
    Dim ModeName As String
    If AddNodeSuc Then
        If AddNodeGroup Then
            'add a group node
            ModeName = Mode.List(Combo1.ListIndex)
            
            mySQLStatement = "Insert new group with AdddNodeName, AddNodeDesc, and Mode (WHere mode = modeName)"
            Set resultSet = dbConnection.OpenResultset(mySQLStatement, rdOpenKeyset)
            
            mySQLStatement = "Get the GroupID for the just entered group"
            Set resultSet = dbConnection.OpenResultset(mySQLStatement, rdOpenKeyset)
            If resultSet.EOF Then
                MsgBox , , Error, , "Item did not get inserted into database"
            Else
                'GroupsBComps.Nodes.Add(,,
            End If
                
            
            'GroupsBComps.Nodes.Add(,,
        Else
            'add a bcomp node
            'GroupsBComps.SelectedItem.Text
        End If
    End If
    
    
End Sub

Private Sub DoneBtn_Click()
    ResumeUpdates
End Sub

Private Sub Form_Load()
    Dim NumOfSys As Integer
    Dim NumOfBComps As Integer
    Dim NumOfBE As Integer
    Dim sysName As String * 27
    Dim baseCompName As String * 27
    Dim beName As String * 27
    
   
    Dim BEDesc As String
    Dim success As Long
    
    Dim i, j, k As Integer
    Dim mySQLStatement As String
    
    'Load the Modes
    'get lise of modes
    mySQLStatement = "SELECT ModeID, ModeName FROM Mode"
    
    Set resultSet = dbConnection.OpenResultset(mySQLStatement, rdOpenKeyset)
    ' Run time error 40071 will be generated if no connection is present by this statement

    'check to make sure result was returned
    If (resultSet.EOF) Then
        MsgBox "No Modes Found", vbInformation
        Exit Sub
    End If
    
    'determine number of rows
    While Not resultSet.EOF
        resultSet.MoveNext
        RowReturn = RowReturn + 1
    Wend
    
    'get specified number of rows
    resultSet.MoveFirst
    rarray = resultSet.GetRows(RowReturn)
    'MsgBox Str(RowReturn)
    
    For i = 0 To RowReturn - 1
        If rarray(0, i) > 0 Then
            Mode.AddItem rarray(1, i)
        End If
    Next i
    
    
    'load avalBEs form
    
    
    
    
    
    
    
    
End Sub



Private Sub GroupsBComps_click()
    Dim BCompID As Integer
    If Not GroupsBComps.SelectedItem Is Nothing Then
        If GroupsBComps.SelectedItem.Child Is Nothing Then
            BCompID = GroupsBComps.SelectedItem.Tag
            mySQLStatement = "Get the Basic Events acording to BCompID"
            
            Set resultSet = dbConnection.OpenResultset(mySQLStatement, rdOpenKeyset)
            Dim lItem As ListItem
            While Not resultSet.EOF
                Set lItem = BasicEventsLV.ListItems.Add(, , resultSet(0))
                lItem.ListSubItems.Add , , resultSet(1)
                lItem.Tag = resultSet(2)
                resultSet.MoveNext
                
            Wend
        End If
    End If
End Sub

Private Sub RemoveBEBtn_Click()
    Dim BCompID As Integer
    If Not BasicEventsLV.SelectedItem Is Nothing Then
        BCompID = BasicEventsLV.SelectedItem.Tag
        mySQLStatement = "set the Basic Events bCompID -1 according to name"
        Set resultSet = dbConnection.OpenResultset(mySQLStatement, rdOpenKeyset)
        Dim ListItem As ListItem
        ListItem = bForm.SelectedBEList.ListItems.Add(, , BasicEventsLV.SelectedItem.Text)
        ListItem.ListSubItems.Add , , BasicEventsLV.SelectedItem.SubItems(BasicEventsLV.SelectedItem.Index)
        ListItem.Tag = BasicEventsLV.SelectedItem.Tag
        BasicEventsLV.ListItems.Remove (BasicEventsLV.SelectedItem.Index)
        
    End If
    
End Sub
