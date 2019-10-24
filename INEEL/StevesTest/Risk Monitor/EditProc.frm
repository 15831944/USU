VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form EditProc 
   Caption         =   "Edit Procedure"
   ClientHeight    =   5220
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   8535
   BeginProperty Font 
      Name            =   "Arial"
      Size            =   9.75
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   Icon            =   "EditProc.frx":0000
   LinkTopic       =   "Form1"
   MinButton       =   0   'False
   ScaleHeight     =   5220
   ScaleWidth      =   8535
   StartUpPosition =   1  'CenterOwner
   Begin VB.CommandButton Change 
      Caption         =   "Change..."
      Height          =   375
      Left            =   120
      TabIndex        =   8
      Top             =   4800
      Width           =   1335
   End
   Begin VB.CommandButton RemoveComp 
      Caption         =   "Remove"
      Height          =   375
      Left            =   1680
      TabIndex        =   7
      Top             =   4800
      Width           =   1335
   End
   Begin VB.CommandButton CancelButton 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   6960
      TabIndex        =   6
      Top             =   4800
      Width           =   1335
   End
   Begin MSComctlLib.ListView ModeView 
      Height          =   3495
      Left            =   4320
      TabIndex        =   3
      Top             =   1200
      Width           =   4215
      _ExtentX        =   7435
      _ExtentY        =   6165
      View            =   3
      LabelEdit       =   1
      LabelWrap       =   -1  'True
      HideSelection   =   -1  'True
      Checkboxes      =   -1  'True
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
   Begin VB.CommandButton ok 
      Caption         =   "OK"
      Height          =   375
      Left            =   5400
      TabIndex        =   0
      Top             =   4800
      Width           =   1335
   End
   Begin MSComctlLib.ListView ComponentList 
      Height          =   3495
      Left            =   0
      TabIndex        =   5
      Top             =   1200
      Width           =   4335
      _ExtentX        =   7646
      _ExtentY        =   6165
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
   Begin VB.Label Label2 
      Caption         =   "Valid Modes"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   4440
      TabIndex        =   4
      Top             =   840
      Width           =   2295
   End
   Begin VB.Label ProcedureNameLabel 
      Caption         =   "[procedure name goes here]"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   240
      TabIndex        =   2
      Top             =   240
      Width           =   8055
   End
   Begin VB.Label Label1 
      Caption         =   "Current Components"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000017&
      Height          =   255
      Left            =   120
      TabIndex        =   1
      Top             =   840
      Width           =   2535
   End
End
Attribute VB_Name = "EditProc"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Public ProcedureName As String
Private ProcID As Integer
Private cForm As ComponentMap
Private compsModified As Boolean
Private modesModified As Boolean
Public Result As Boolean

Private Sub CancelButton_Click()
    Result = False
    Me.Hide
End Sub

'Function/Subroutine:Change_Click
'Purpose: to change a component to a procedure being created.
Private Sub Change_Click()
    Dim c As Integer, i As Integer, lItem As ListItem
    cForm.FormMode = SelectOnly
    cForm.ClearSelectedNodes
    For i = 1 To ComponentList.ListItems.Count
        cForm.SetSelectedNode ComponentList.ListItems(i).tag, True
    Next i
    cForm.Show vbModal
    
    ComponentList.ListItems.Clear
    For c = 1 To cForm.GetSelectedCount
        Set lItem = ComponentList.ListItems.Add(, , Space(cForm.GetSelectedNode(c).hLevel * 5) & cForm.GetSelectedNode(c).name, , cForm.GetSelectedNode(c).hLevel + 1)
        lItem.tag = cForm.GetSelectedIndex(c) 'cForm.GetSelectedNode(c)
        lItem.ListSubItems.Add , , compHierarchy.LevelStrings(cForm.GetSelectedNode(c).hLevel)
    Next c
    compsModified = True
    RemoveComp.Enabled = False
End Sub


Private Sub ComponentList_Click()
    If Not ComponentList.SelectedItem Is Nothing Then
        RemoveComp.Enabled = True
    End If
End Sub

Private Sub ComponentList_DblClick()
    Change_Click
End Sub

Private Sub ComponentList_KeyDown(KeyCode As Integer, Shift As Integer)
    If KeyCode = 46 Then
        RemoveComp_Click
    End If
End Sub

'Function/Subroutine:Form_Load
'Purpose:set initial values and set up add and remove lists
Private Sub Form_Load()
    Dim mySQLStatement As String, c As Integer, CompID As Integer, rarray As Variant
    Dim lItem As ListItem, i As Integer
    Dim resultSet As rdoResultset
    ProcedureNameLabel.Caption = ProcedureName
    Set cForm = MDIMain.compMap
    Set ComponentList.smallIcons = compHierarchy.smallIcons
    ComponentList.ColumnHeaders.Add , , "Component Name", (ComponentList.Width - 60) * 2 / 3
    ComponentList.ColumnHeaders.Add , , "Hierarchy Level", (ComponentList.Width - 60) * 1 / 3
    RemoveComp.Enabled = False
    ModeView.ColumnHeaders.Add , , "Mode Name", (ModeView.Width - 80) * 1 / 3
    ModeView.ColumnHeaders.Add , , "Mode Description", (ModeView.Width - 80) * 2 / 3
    
    'Get ComponentID from ComponentName
    mySQLStatement = "SELECT ProcedureID FROM [Procedure] WHERE ProcedureName = '" & ProcedureName & "'"
    Set resultSet = dbConnection.OpenResultset(mySQLStatement)
    ' Run time error 40071 will be generated if no connection is present by this statement

    'check to make sure result was returned
    If resultSet.EOF Then
        MsgBox "Procedure ID Not Found", vbInformation
        Exit Sub
    End If
    
    rarray = resultSet.GetRows(1)
    ProcID = rarray(0, 0)
    'Get ComponentID and ComponentName of all Components associated with selected proc
    mySQLStatement = "SELECT ComponentID FROM [ProcComp] WHERE ProcedureID = " & ProcID
    Set resultSet = dbConnection.OpenResultset(mySQLStatement)
    
    While Not resultSet.EOF
        rarray = resultSet.GetRows(1)
        CompID = rarray(0, 0)
        c = cForm.FindIndexByID(CompID)
        If c = -1 Then
            MsgBox "Program Error... Comp found through ProcComp table which is not in the component hierarchy.", vbCritical
            Exit Sub
        End If
        'Display component names in a list.
        Set lItem = ComponentList.ListItems.Add(, , Space(cForm.NodeData(c).hLevel * 5) & cForm.NodeData(c).name, , cForm.NodeData(c).hLevel + 1)
        lItem.tag = c 'cForm.NodeData(c)
        lItem.ListSubItems.Add , , compHierarchy.LevelStrings(cForm.NodeData(c).hLevel)
    Wend
    
    'add modes now
    For i = 1 To ModeList.Count
        If ModeList.Item(i).ObjectInUse Then
            Set lItem = ModeView.ListItems.Add(, , ModeList.Item(i).ModeName)
            lItem.tag = i
            lItem.ToolTipText = ModeList.Item(i).ModeName
            lItem.ListSubItems.Add , , ModeList.Item(i).ModeDescription, , ModeList.Item(i).ModeDescription
            mySQLStatement = "SELECT ProcedureID FROM ProcMode WHERE ProcedureID = " & ProcID
            Set resultSet = dbConnection.OpenResultset(mySQLStatement)
            lItem.Checked = Not resultSet.EOF
        End If
    Next i
End Sub

Private Sub Form_Resize()
    '
    If Height > 5625 Then
        Change.Top = Height - 900
        RemoveComp.Top = Height - 900
        OK.Top = Height - 900
        CancelButton.Top = Height - 900
        ComponentList.Height = Height - 2130
        ModeView.Height = Height - 2130
    End If
    
    If Width > 8655 Then
        ComponentList.Width = (Width - 100) * 1 / 2
        ModeView.Left = ComponentList.Left + ComponentList.Width
        ModeView.Width = (Width - 100) * 1 / 2
        OK.Left = Width - 3255
        CancelButton.Left = Width - 1695
        
        Label2.Left = ModeView.Left + 100
        
        ComponentList.ColumnHeaders(1).Width = (ComponentList.Width - 80) * 1 / 2
        ComponentList.ColumnHeaders(2).Width = (ComponentList.Width - 80) * 1 / 2
        
        ModeView.ColumnHeaders(1).Width = (ModeView.Width - 80) * 1 / 2
        ModeView.ColumnHeaders(2).Width = (ModeView.Width - 80) * 1 / 2
    End If
End Sub

Private Sub ModeView_ItemCheck(ByVal Item As MSComctlLib.ListItem)
    modesModified = True
End Sub

'Function/Subroutine:ok_Click
'Purpose: unloads form
Private Sub OK_Click()
    Dim mySQLStatement As String, i As Integer, CompID As Integer, modeID As Integer
    ' take care of proc comp table
    If compsModified Then
        mySQLStatement = "DELETE FROM ProcComp WHERE ProcedureID = " & ProcID
        dbConnection.Execute (mySQLStatement)
        For i = 1 To ComponentList.ListItems.Count
            CompID = cForm.NodeData(ComponentList.ListItems(i).tag).ID
            mySQLStatement = "INSERT INTO [ProcComp] (ProcedureID, ComponentID) VALUES(" & ProcID & "," & CompID & ")"
            dbConnection.Execute (mySQLStatement)
        Next i
    End If
    If modesModified Then
        mySQLStatement = "DELETE FROM ProcMode WHERE ProcedureID = " & ProcID
        dbConnection.Execute (mySQLStatement)
        For i = 1 To ModeView.ListItems.Count
            If ModeView.ListItems(i).Checked = True Then
                ' add to procmode table
                modeID = ModeView.ListItems(i).tag
                mySQLStatement = "INSERT INTO [ProcMode] (ProcedureID, ModeID) VALUES(" & ProcID & "," & modeID & ")"
                dbConnection.Execute (mySQLStatement)
            End If
        Next i
    End If
    
    Result = True
    Me.Hide
End Sub

'Function/Subroutine:Remove_Click
'Purpose: removes an Item from component list - here and in database
Private Sub RemoveComp_Click()
    
    Dim c As Integer

    For c = ComponentList.ListItems.Count To 1 Step -1
        If ComponentList.ListItems.Item(c).Selected = True Then
            cForm.SetSelectedNode ComponentList.ListItems(c).tag, False
            ComponentList.ListItems.Remove (c)
            compsModified = True
        End If
    Next c
    
    RemoveComp.Enabled = False
End Sub
