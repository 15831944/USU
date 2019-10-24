VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form VScreen 
   AutoRedraw      =   -1  'True
   Caption         =   "VScreen"
   ClientHeight    =   8145
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   8385
   FillColor       =   &H00FFFFFF&
   FillStyle       =   0  'Solid
   BeginProperty Font 
      Name            =   "Arial"
      Size            =   9.75
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   ForeColor       =   &H00404040&
   Icon            =   "VScreen.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   8145
   ScaleWidth      =   8385
   StartUpPosition =   3  'Windows Default
   Begin MSComctlLib.ListView ComponentList 
      Height          =   4575
      Left            =   360
      TabIndex        =   9
      Top             =   840
      Width           =   6255
      _ExtentX        =   11033
      _ExtentY        =   8070
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
   Begin VB.CommandButton OK 
      Caption         =   "OK"
      Height          =   735
      Left            =   6960
      TabIndex        =   8
      Top             =   5040
      Width           =   1215
   End
   Begin VB.ComboBox Mode 
      Height          =   360
      Left            =   2385
      Style           =   2  'Dropdown List
      TabIndex        =   6
      Top             =   5760
      Width           =   3615
   End
   Begin VB.CommandButton CalcRiskLev 
      Caption         =   "Calculate Risk Level"
      Height          =   615
      Left            =   2865
      TabIndex        =   3
      Top             =   6480
      Width           =   2655
   End
   Begin VB.CommandButton RemoveComp 
      Caption         =   "Remove"
      Height          =   615
      Left            =   6960
      TabIndex        =   2
      Top             =   2400
      Width           =   1215
   End
   Begin VB.CommandButton AddComp 
      Caption         =   "      Add Component"
      Height          =   735
      Left            =   6960
      TabIndex        =   1
      Top             =   1440
      Width           =   1215
   End
   Begin VB.Label Label5 
      Caption         =   "Mode"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   1440
      TabIndex        =   7
      Top             =   5760
      Width           =   615
   End
   Begin VB.Shape UpdateBorder 
      BorderColor     =   &H0000FF00&
      BorderWidth     =   9
      Height          =   615
      Left            =   2880
      Top             =   6480
      Visible         =   0   'False
      Width           =   2655
   End
   Begin VB.Image Image1 
      Height          =   375
      Left            =   4800
      Top             =   7440
      Width           =   735
   End
   Begin VB.Shape Light 
      BorderWidth     =   3
      FillColor       =   &H000000FF&
      FillStyle       =   0  'Solid
      Height          =   1095
      Left            =   6960
      Shape           =   1  'Square
      Top             =   6720
      Width           =   1095
   End
   Begin VB.Label Label4 
      Alignment       =   1  'Right Justify
      Caption         =   "0.00"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00000000&
      Height          =   255
      Left            =   2880
      TabIndex        =   5
      Top             =   7440
      Width           =   1575
   End
   Begin VB.Label Label3 
      Caption         =   "Risk Level"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   1440
      TabIndex        =   4
      Top             =   7440
      Width           =   1335
   End
   Begin VB.Label Label1 
      Alignment       =   2  'Center
      Caption         =   "Components Out of Service "
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H000000FF&
      Height          =   495
      Left            =   1785
      TabIndex        =   0
      Top             =   240
      Width           =   4815
   End
End
Attribute VB_Name = "VScreen"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Private NumCompOff As Integer
Private rArray2 As Variant
Private OffCompArray As Variant
Private Calculated As Boolean
Private Risk As Double
Public cForm As ComponentMap

'*************************| Steve's DLL Support |********************
Private Declare Function CalcRiskFromCompList Lib "riskMon" (ByRef Risk As Double) As Long
Private Declare Function AddSingleComp Lib "riskMon" (ByVal CompID As Long) As Long
Private Declare Function ClearBEList Lib "riskMon" () As Long
Private Declare Function SetModeID Lib "riskMon" (ByVal NewModeID As Long) As Long
'********************************************************************
Private Declare Function sndPlaySound Lib "winmm.dll" Alias "sndPlaySoundA" (ByVal lpszSoundName As String, _
    ByVal uFlags As Long) As Long

'Function:AddComp_Click
'Purpose:show the hierarchy form and add a selected component to the list of
'out of service components for calculation.
Private Sub AddComp_Click()
    
    cForm.FormMode = SelectOnly
    cForm.CompDiagram.ShowToolboxOnRightClick = False
    cForm.Show vbModal
    
    Dim c As Integer, i As Integer, duplicate As Boolean, lItem As ListItem
    
    For c = 1 To cForm.GetSelectedCount
        duplicate = False
        For i = 1 To ComponentList.ListItems.Count
            If (ComponentList.ListItems(i).tag.ID = cForm.GetSelectedNode(c).ID) Then
                duplicate = True
                Exit For
            End If
        Next i
        If Not duplicate Then
            Set lItem = ComponentList.ListItems.Add(, , Space(cForm.GetSelectedNode(c).hLevel * 5) & cForm.GetSelectedNode(c).name, , cForm.GetSelectedNode(c).hLevel + 1)
            Set lItem.tag = cForm.GetSelectedNode(c)
            lItem.ListSubItems.Add , , compHierarchy.LevelStrings(cForm.GetSelectedNode(c).hLevel)
        End If
    Next c
    Calculated = False
    SetLight
    RemoveComp.Enabled = False
End Sub
'Function:CalcRiskLev_Click
'Purpose:calculate the risk level with the out of service list as shown
Private Sub CalcRiskLev_Click()
    Dim CompIDs As Variant
    Dim NumOfComp As Integer
    Dim i As Integer, CompID As Long
        
    Dim tRisk As Double ' this is a temp value
    
    NumOfComp = ComponentList.ListItems.Count
    
    If DLLActive Then ClearBEList
    For i = 1 To NumOfComp
        CompID = ComponentList.ListItems.Item(i).tag.ID
        If DLLActive Then
            AddSingleComp CompID
        Else
            tRisk = tRisk + ComponentList.ListItems.Item(i).tag.totalBaseComponents / 10
        End If
    Next i
    If DLLActive Then
        If CalcRiskFromCompList(Risk) = 0 Then
            MsgBox "CalcRiskFromCompList failed", vbInformation
        End If
    Else
        Risk = tRisk
    End If
    Label4.Caption = Format(Risk, "##.#########")
    
    'Dim Comp As String
    
    'OffCompArray = List1.Columns
    
    'Comp = OffCompArray

    Calculated = True
    SetLight
    RemoveComp.Enabled = False
End Sub
'Function:SetLight
'Purpose:loads the high medium and low indecators and turns the green 'go'
'shading to on or off depending on calculation
Private Sub SetLight()
    If Calculated Then
        Light.Visible = True
        Label3.Visible = True
        Label4.Visible = True
        Image1.Visible = True
        UpdateBorder.Visible = False
        CalcRiskLev.Enabled = False
        
        Select Case RiskCalculator.ClassifyRisk(Risk, Mode.ItemData(Mode.ListIndex))
            Case 0, 1
                Light.FillColor = vbGreen
                Image1.Picture = LoadPicture(workingDirectory & "icons\LowIndicator.bmp")
            Case 2
                Light.FillColor = vbYellow
                Image1.Picture = LoadPicture(workingDirectory & "icons\MediumIndicator.bmp")
            Case 3
                Light.FillColor = vbRed
                'make noise
                Image1.Picture = LoadPicture(workingDirectory & "icons\HighIndicator.bmp")
                'ReturnLength As Long
                Dim i As Integer
                Label4.Caption = Risk
                For i = 0 To 5
                   ' result = sndPlaySound("E:\StevesTest\alarm.wav", 1)
                Next i

        End Select
        Label4.Caption = Risk
        
    Else
        Light.Visible = False
        Label3.Visible = False
        Label4.Visible = False
        Image1.Visible = False
        UpdateBorder.Visible = True
        CalcRiskLev.Enabled = True
        
    End If
    
End Sub
'Function:ComponentList_Click
'Purpose:makes sure the remove component button is enabled if object in list
'has been selected
Private Sub ComponentList_Click()
    
    RemoveComp.Enabled = True
    
End Sub

'Function:ComponentList_DblClick
'Purpose:double clicking on the list is equivalet to clicking on the remove
'button
Private Sub ComponentList_DblClick()
    RemoveComp_Click
End Sub

'Function:Form_Load
'Purpose:loads the form, sets the list columns and adds appropriate items to
'the mode combo box.
Private Sub Form_Load()
    Dim mySQLstatement As String
    Dim mySQLStatement2 As String
    Dim resultSet As rdoResultset
    Dim resultSet2 As rdoResultset
    Dim i, i2, j2 As Integer
    Dim colArray As Variant
    Dim rowCount As Integer
    
    cForm.ClearSelectedNodes
    Set ComponentList.smallIcons = compHierarchy.smallIcons
    
    Calculated = False
    
    Risk = 0#
    Label4.Caption = Risk
    Label4.Refresh
    SetLight
    
    'Load the combo box mode
    For i = 1 To ModeList.Count
        If ModeList.Item(i).ObjectInUse Then
            Mode.AddItem ModeList.Item(i).ModeName
            Mode.ItemData(Mode.listCount - 1) = i
        End If
    Next i
    If ModeCount > 0 Then
        Mode.ListIndex = 0
    Else
        AddComp.Enabled = False
        RemoveComp.Enabled = False
        CalcRiskLev.Enabled = False
        Mode.Enabled = False
    End If
    
    ComponentList.ColumnHeaders.Add , , "Component Name", (ComponentList.Width - 60) * 2 / 3
    ComponentList.ColumnHeaders.Add , , "Hierarchy Level", (ComponentList.Width - 60) * 1 / 3
    RemoveComp.Enabled = False
End Sub


'Function:Form_Unload
'Purpose:unload the form resetting the icons
Private Sub Form_Unload(cancel As Integer)
    Set ComponentList.smallIcons = Nothing
End Sub

Private Sub Mode_Click()
    ' called when the mode changes
    If DLLActive Then
        Dim modeID As Long
        If Mode.ListIndex <> -1 Then
            modeID = Mode.ItemData(Mode.ListIndex)
            If SetModeID(modeID) = 0 Then
                MsgBox "Failed to set mode in risk monitor DLL.", , "Error"
            End If
        End If
    End If
End Sub

'Function:ok_Click
'Purpose:unload the form
Private Sub ok_Click()
    Unload Me
End Sub
'Function:RemoveAllComp_Click
'Purpose:removes all components from the list
Private Sub RemoveAllComp_Click()
    ComponentList.ListItems.Clear
    Calculated = False
    SetLight
    RemoveComp.Enabled = False
End Sub
'Function:RemoveComp_Click
'Purpose:removes selected item from the list
Private Sub RemoveComp_Click()
    Dim i As Integer, comp As ListItem, itemRemoved As Boolean
    itemRemoved = False
    
    For i = ComponentList.ListItems.Count To 1 Step -1
        Set comp = ComponentList.ListItems.Item(i)
            
        If (comp.Selected = True) Then
            itemRemoved = True
            ComponentList.ListItems.Remove (i)
        End If
    Next i
    
    If itemRemoved Then
        Calculated = False
        SetLight
    End If
    RemoveComp.Enabled = False
End Sub
