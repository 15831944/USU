VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form MappingWizard 
   Caption         =   "Mapping Scheme for Groups and Base Comps"
   ClientHeight    =   6060
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   8310
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
   ScaleHeight     =   6060
   ScaleWidth      =   8310
   StartUpPosition =   3  'Windows Default
   Begin VB.ComboBox ModeCB 
      Height          =   360
      Left            =   1920
      TabIndex        =   9
      Text            =   "Combo1"
      Top             =   840
      Width           =   3135
   End
   Begin VB.CommandButton MapBtn 
      Caption         =   "Map"
      Height          =   615
      Left            =   4200
      TabIndex        =   8
      Top             =   4920
      Width           =   1335
   End
   Begin VB.CommandButton NextBtn 
      Caption         =   "Next"
      Height          =   615
      Left            =   6000
      TabIndex        =   7
      Top             =   4920
      Width           =   1335
   End
   Begin MSComctlLib.ListView MappingSchemeLV 
      Height          =   2895
      Left            =   1910
      TabIndex        =   6
      Top             =   1800
      Width           =   5445
      _ExtentX        =   9604
      _ExtentY        =   5106
      View            =   3
      LabelEdit       =   1
      LabelWrap       =   -1  'True
      HideSelection   =   -1  'True
      GridLines       =   -1  'True
      _Version        =   393217
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      BorderStyle     =   1
      Appearance      =   1
      NumItems        =   0
   End
   Begin VB.CommandButton HelpBtn 
      Caption         =   "Help"
      Height          =   495
      Left            =   360
      TabIndex        =   5
      Top             =   4920
      Width           =   1215
   End
   Begin VB.CommandButton BuildByHandBtn 
      Caption         =   "  Build By Hand Using Fault Tree"
      Height          =   615
      Left            =   1920
      TabIndex        =   1
      Top             =   4920
      Width           =   1815
   End
   Begin VB.Label ModeLbl 
      Caption         =   "Mode"
      Height          =   255
      Left            =   960
      TabIndex        =   10
      Top             =   960
      Width           =   735
   End
   Begin VB.Label BENamingLbl 
      Caption         =   "Basic Event Naming system.  Select One"
      Height          =   855
      Left            =   360
      TabIndex        =   4
      Top             =   1920
      Width           =   1575
   End
   Begin VB.Label BaseCompLbl 
      BackColor       =   &H80000018&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "Base Component"
      Height          =   375
      Left            =   3000
      TabIndex        =   3
      Top             =   1440
      Width           =   4335
   End
   Begin VB.Label GroupLbl 
      BackColor       =   &H80000018&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "Group"
      Height          =   375
      Left            =   1920
      TabIndex        =   2
      Top             =   1440
      Width           =   1095
   End
   Begin VB.Label InstructionsLb 
      Caption         =   "Select the mapping scheme that best matches the naming system used for that mode."
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   120
      TabIndex        =   0
      Top             =   240
      Width           =   8295
   End
End
Attribute VB_Name = "MappingWizard"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Declare Function GetSystemName Lib "riskMon" (ByVal Criteria As String, ByVal Index As Long, ByRef sysName As String, ByRef SysDesc As String) As Long
Private Declare Function SystemCount Lib "riskMon" (ByVal Criteria As String) As Long
Private Declare Function GetNumOfBE Lib "riskMon" (ByVal sysName As String) As Long
Private Declare Function GetBEName Lib "riskMon" (ByVal sysName, ByVal Index As Long, ByRef beName As String, ByRef BEDesc As String) As Long
Private Declare Function SetModeID Lib "riskMon" (ByVal NewModeID As Long) As Long
Private Declare Function SuspendUpdates Lib "riskMon" () As Long
Private Declare Function ResumeUpdates Lib "riskMon" () As Long

Private Sub BuildByHandBtn_Click()
    Dim cForm As New BaseComponentMap
    cForm.FormMode = MapBasicEvents
    If DLLActive Then SuspendUpdates
    cForm.Show 1
    If DLLActive Then ResumeUpdates
End Sub


Private Sub Form_Load()
    Dim lItem As ListItem
    Dim mySQLStatement As String, resultSet As rdoResultset, rarray As Variant
    Dim NumOfModes, i As Integer
    
    MappingSchemeLV.ColumnHeaders.Add , , "System", GroupLbl.Width
    MappingSchemeLV.ColumnHeaders.Add , , "Component Type", BaseCompLbl.Width / 3 + 250
    MappingSchemeLV.ColumnHeaders.Add , , "Fail Mode", BaseCompLbl.Width / 3 - 250
    MappingSchemeLV.ColumnHeaders.Add , , "Component ID", BaseCompLbl.Width / 3
    BaseCompLbl.ToolTipText = "The Base Component name will be made from the Component type and the ComponentID"
    
    Set lItem = MappingSchemeLV.ListItems.Add(, , "  *-")
    lItem.ToolTipText = "Will create groups from all unique character sequences before the first dash"
    lItem.tag = 1
    MappingSchemeLV.ListItems(1).ListSubItems.Add , , "  *-     ", , "The Component Type is until the next dash.  Used as the first of the Component Name"
    MappingSchemeLV.ListItems(1).ListSubItems.Add , , "  *-     ", , "The Fail Mode is until the next dash. Not used in Base Component Name"
    MappingSchemeLV.ListItems(1).ListSubItems.Add , , "  *      ", , "The Component ID is until the next dash. Used as the last part of the Component Name"
    Set lItem = MappingSchemeLV.ListItems.Add(, , "  ??")
    lItem.ToolTipText = "Will create groups from all unique character sequences using the fist 2 characters"
    MappingSchemeLV.ListItems(2).ListSubItems.Add , , "  -*-    ", , "The Component Type is From first dash until the next dash.  Used as the first of the Component Name"
    MappingSchemeLV.ListItems(2).ListSubItems.Add , , "  *-     ", , "The Fail Mode is until the next dash. Not used in Base Component Name"
    MappingSchemeLV.ListItems(2).ListSubItems.Add , , "  -*     ", , "The Component ID is until the next dash. Used as the last part of the Component Name"
    lItem.tag = 2
    Set lItem = MappingSchemeLV.ListItems.Add(, , "  ???")
    lItem.ToolTipText = "Will create groups from all unique character sequences using the fist 3 characters"
    MappingSchemeLV.ListItems(3).ListSubItems.Add , , "  -*-     ", , "The Component Type is From first dash until the next dash.  Used as the first of the Component Name"
    MappingSchemeLV.ListItems(3).ListSubItems.Add , , "  *-     ", , "The Fail Mode is until the next dash. Not used in Base Component Name"
    MappingSchemeLV.ListItems(3).ListSubItems.Add , , "  -*     ", , "The Component ID is until the next dash. Used as the last part of the Component Name"
    lItem.tag = 3
    Set lItem = MappingSchemeLV.ListItems.Add(, , "  ????")
    lItem.ToolTipText = "Will create groups from all unique character sequences using the fist 4 characters"
    MappingSchemeLV.ListItems(4).ListSubItems.Add , , "  -*-     ", , "The Component Type is From first dash until the next dash.  Used as the first of the Component Name"
    MappingSchemeLV.ListItems(4).ListSubItems.Add , , "  -*-     ", , "The Fail Mode is From first dash until the next dash. Not used in Base Component Name"
    MappingSchemeLV.ListItems(4).ListSubItems.Add , , "  -*      ", , "The Component ID is until the next dash. Used as the last part of the Component Name"
    lItem.tag = 4
    BuildByHandBtn.ToolTipText = "If you desire to associate all basic events with Groups and Base Components Manualy.  Use only if you have extencive knowledge with the fault trees."
    NextBtn.ToolTipText = "Map the Base Components and then make any changes if needed."
    
    
    
    
    If ModeCount > 0 Then
        For i = 1 To ModeList.Count
            If ModeList.Item(i).ObjectInUse = True Then
                ModeCB.AddItem ModeList.Item(i).ModeName
                ModeCB.ItemData(ModeCB.listCount - 1) = i
            End If
        Next i
        ModeCB.ListIndex = 0
    Else ' no records were found in the Mode table
        ModeExists False
    End If
    ModeCB.ListIndex = 0
    
End Sub

Private Sub ModeExists(Enable As Boolean)
    Label1.Enabled = Enable
    
End Sub
Private Sub HelpBtn_Click()
    MappingHelp.Show
End Sub

Private Sub MapBtn_Click()
    Dim NumOfSystems As Long
    Dim NumOfBEvents As Long
    Dim tempSysName As String * 25
    Dim tempBEName As String * 25
    Dim tempBCompName As String * 25
    Dim Mode As Long
    Dim mySQLStatement As String, resultSet As rdoResultset, rarray As Variant
    Dim i, j As Integer
    
    'MappingSchemeLV.SelectedItem.ListSubItems(1).text
    
    If SetModeID(Mode) Then
        NumOfSystems = SystemCount(MappingSchemeLV.SelectedItem.text)
        For i = 0 To NumOfSystems
            GetSysName MappingSchemeLV.SelectedItem.text, i, tempSysName
            NumOfBEvents = GetNumOfBE(tempSysName)
            For j = 0 To NumOfBEvents
                GetBCompName MappingSchemeLV.SelectedItem.ListSubItems(1).text
                GetBEName MappingSchemeLV.SelectedItem.ListSubItems(1).text, tempSysName, j, tempBEName
                mySQLStatement = "INSERT INTO BaseComponent (Name, GroupName ) Values ('" & tempBEName & "', '" & tempSysName & "');"
                Set resultSet = dbConnection.OpenResultset(mySQLStatement)
                mySQLStatement = "INSERT INTO BaseCompBE ( BaseCompID, BEName, ModeID) VALUES ( ,tempBEName, );"
                Set resultSet = dbConnection.OpenResultset(mySQLStatement)
                
            Next j
            
        Next i
        
    Else
        MsgBox "Mode Failed", vbInformation
    End If
       
       
    
End Sub

