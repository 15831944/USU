VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form DiagramToolbox 
   BorderStyle     =   4  'Fixed ToolWindow
   Caption         =   "Diagram Control Toolbox"
   ClientHeight    =   2940
   ClientLeft      =   45
   ClientTop       =   285
   ClientWidth     =   4980
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2940
   ScaleWidth      =   4980
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton ParentDiagram 
      Caption         =   "Parent..."
      Height          =   375
      Left            =   3720
      TabIndex        =   19
      Top             =   520
      Width           =   1215
   End
   Begin VB.CheckBox TestModeButton 
      Caption         =   "Test Mode"
      Height          =   375
      Left            =   3720
      Style           =   1  'Graphical
      TabIndex        =   18
      Top             =   2120
      Width           =   1215
   End
   Begin VB.CommandButton Hide 
      Caption         =   "Hide Me"
      Height          =   375
      Left            =   3720
      TabIndex        =   15
      Top             =   120
      Width           =   1215
   End
   Begin VB.CheckBox Eraser 
      DownPicture     =   "DiagramToolbox.frx":0000
      Height          =   375
      Left            =   3720
      Picture         =   "DiagramToolbox.frx":056E
      Style           =   1  'Graphical
      TabIndex        =   12
      Top             =   1720
      Width           =   1215
   End
   Begin VB.Frame RegionFrame 
      Caption         =   "Region"
      Height          =   2895
      Left            =   0
      TabIndex        =   3
      Top             =   0
      Width           =   3495
      Begin VB.CheckBox SetCenter 
         Caption         =   "Set"
         Height          =   255
         Left            =   2400
         Style           =   1  'Graphical
         TabIndex        =   21
         Top             =   1680
         Width           =   855
      End
      Begin VB.CheckBox Highlight 
         Caption         =   "Highlight"
         Height          =   375
         Left            =   120
         Style           =   1  'Graphical
         TabIndex        =   20
         Top             =   2040
         Width           =   1095
      End
      Begin VB.CommandButton Rename 
         Caption         =   "Rename"
         Height          =   315
         Left            =   2520
         TabIndex        =   16
         Top             =   240
         Width           =   855
      End
      Begin VB.TextBox CompIDBox 
         Height          =   285
         Left            =   1200
         TabIndex        =   14
         Text            =   "1"
         Top             =   1320
         Width           =   1095
      End
      Begin MSComDlg.CommonDialog PickColor 
         Left            =   3000
         Top             =   2040
         _ExtentX        =   847
         _ExtentY        =   847
         _Version        =   393216
         CancelError     =   -1  'True
      End
      Begin VB.CommandButton SubDiagram 
         Caption         =   "Sub-Diagram..."
         Height          =   375
         Left            =   1440
         TabIndex        =   10
         Top             =   2040
         Width           =   1335
      End
      Begin VB.TextBox IDBox 
         BackColor       =   &H80000000&
         Height          =   285
         Left            =   1200
         Locked          =   -1  'True
         TabIndex        =   9
         Text            =   "1"
         Top             =   960
         Width           =   1095
      End
      Begin VB.TextBox CenterBox 
         BackColor       =   &H80000000&
         Height          =   285
         Left            =   1200
         Locked          =   -1  'True
         TabIndex        =   8
         Text            =   "(0,0)"
         Top             =   1680
         Width           =   1095
      End
      Begin VB.ComboBox RegionCombo 
         Height          =   315
         Left            =   1200
         Style           =   2  'Dropdown List
         TabIndex        =   4
         Top             =   240
         Width           =   1215
      End
      Begin VB.Label ColorBox 
         BorderStyle     =   1  'Fixed Single
         Height          =   285
         Left            =   1200
         TabIndex        =   17
         Top             =   600
         Width           =   1095
      End
      Begin VB.Label Label5 
         Caption         =   "CompID"
         Height          =   255
         Left            =   240
         TabIndex        =   13
         Top             =   1320
         Width           =   615
      End
      Begin VB.Label Label1 
         Caption         =   "Name"
         Height          =   255
         Left            =   240
         TabIndex        =   11
         Top             =   240
         Width           =   735
      End
      Begin VB.Label Label4 
         Caption         =   "Center"
         Height          =   255
         Left            =   240
         TabIndex        =   7
         Top             =   1680
         Width           =   735
      End
      Begin VB.Label Label3 
         Caption         =   "ID"
         Height          =   255
         Left            =   240
         TabIndex        =   6
         Top             =   960
         Width           =   615
      End
      Begin VB.Label Label2 
         Caption         =   "Color"
         Height          =   255
         Left            =   240
         TabIndex        =   5
         Top             =   600
         Width           =   615
      End
   End
   Begin VB.CommandButton SaveData 
      Caption         =   "Save"
      Height          =   375
      Left            =   3720
      TabIndex        =   2
      Top             =   2520
      Width           =   1215
   End
   Begin VB.CommandButton DrawOverlay 
      Caption         =   "Overlay"
      Height          =   375
      Left            =   3720
      TabIndex        =   1
      Top             =   1320
      Width           =   1215
   End
   Begin VB.CommandButton NewRegion 
      Caption         =   "New Region"
      Height          =   375
      Left            =   3720
      TabIndex        =   0
      Top             =   920
      Width           =   1215
   End
End
Attribute VB_Name = "DiagramToolbox"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Public dObject As DiagramControl

'Public Sub AddRegionToCombo(ItemString As String, ItemID As Integer)
'    RegionCombo.AddItem ItemString
'    RegionCombo.ItemData(RegionCombo.ListCount - 1) = ItemID
'End Sub

Private Sub CenterBox_Click()
    SetCenter_Click
End Sub

Private Sub ColorBox_Click()
On Error GoTo cancelClick
    PickColor.ShowColor
    dObject.SetRegionData RegionCombo.ListIndex + 1, , PickColor.Color
    ColorBox.BackColor = PickColor.Color
    dObject.DrawOverlay
cancelClick:
    
End Sub

Private Sub CompIDBox_Change()
    dObject.SetRegionData RegionCombo.ListIndex + 1, , , , CompIDBox.Text
End Sub

Private Sub DrawOverlay_Click()
    dObject.DrawOverlay
End Sub

Private Sub Eraser_Click()
    If Eraser.Value = Checked Then
        SetCenter.Value = Unchecked
        Highlight.Value = Unckecked
        TestModeButton.Value = Unchecked
         dObject.FormMode = EraseMode
    Else
         If dObject.FormMode <> DrawRegionsMode Then dObject.FormMode = DrawRegionsMode
    End If
End Sub

Private Sub Form_Load()
    If dObject.GetCurrentDiagram().RegionCount = 0 Then
        EnableRegionWindow False
    Else
        If RegionCombo.ListCount > 0 Then
            RegionCombo.ListIndex = 0
        End If
    End If
End Sub

Public Sub EnableRegionWindow(enable As Boolean)
    RegionFrame.Enabled = enable
    Label1.Enabled = enable
    RegionCombo.Enabled = enable
    Label2.Enabled = enable
    ColorBox.Enabled = enable
    Label3.Enabled = enable
    IDBox.Enabled = enable
    Label5.Enabled = enable
    CompIDBox.Enabled = enable
    Label4.Enabled = enable
    CenterBox.Enabled = enable
    SetCenter.Enabled = enable
    Highlight.Enabled = enable
    SubDiagram.Enabled = enable
    Rename.Enabled = enable
End Sub

Private Sub Hide_Click()
Me.Hide
End Sub

Private Sub Highlight_Click()
    If Highlight.Value = Checked Then
        SetCenter.Value = Unchecked
        Eraser.Value = Unckecked
        TestModeButton.Value = Unchecked
        dObject.FormMode = drawHighlightMode
    Else
        If dObject.FormMode <> DrawRegionsMode Then dObject.FormMode = DrawRegionsMode
    End If
End Sub

Private Sub NewRegion_Click()
    dObject.AddRegion
End Sub

Private Sub ParentDiagram_Click()
    PickParent.HasParent.Value = dObject.GetCurrentDiagram().HasParent
    PickParent.Text1.Text = dObject.GetCurrentDiagram().parentFileName
    PickParent.Show vbModal, Me
    dObject.SetParentDiagram PickParent.hasParentD, PickParent.pFileName
End Sub

Private Sub RegionCombo_Click()
    'If IDBox > 0 Then dObject.SetRegionData IDBox, RegionCombo.Text
    ColorBox.BackColor = dObject.GetRegionData(RegionCombo.ListIndex + 1).Color
    IDBox = RegionCombo.ListIndex + 1
    CompIDBox = dObject.GetRegionData(RegionCombo.ListIndex + 1).CompID
    CenterBox = "(" & dObject.GetRegionData(RegionCombo.ListIndex + 1).Center.x & "," & dObject.GetRegionData(RegionCombo.ListIndex + 1).Center.y & ")"
    dObject.CurRegionIndex = RegionCombo.ListIndex + 1
End Sub

Private Sub Rename_Click()
    Dim newName As String
    newName = InputBox("Enter New Region Name", , dObject.GetRegionData(IDBox).Name)
    If newName <> "" Then dObject.SetRegionData IDBox, newName
End Sub

Private Sub SaveData_Click()
    dObject.SaveDiagram
End Sub

Private Sub SetCenter_Click()
    If SetCenter.Value = Checked Then
        Highlight.Value = Unchecked
        Eraser.Value = Unckecked
        TestModeButton.Value = Unchecked
        dObject.FormMode = SetCenterMode
    Else
        If dObject.FormMode <> DrawRegionsMode Then dObject.FormMode = DrawRegionsMode
    End If

End Sub

Private Sub SubDiagram_Click()
    DiagramProperties.Text1.Enabled = False
    DiagramProperties.BrowseFolder.Enabled = False
    DiagramProperties.Label2 = "Diagram File"
    DiagramProperties.Show vbModal, Me
    If DiagramProperties.result = True Then
        dObject.SetRegionData IDBox, , , , , , True, DiagramProperties.Text2
    End If
    DiagramProperties.Text1.Enabled = True
    DiagramProperties.BrowseFolder.Enabled = True
    DiagramProperties.Label2 = "Initial Diagram File"
End Sub

Private Sub TestModeButton_Click()
    If TestModeButton.Value = Checked Then
        SetCenter.Value = Unchecked
        Eraser.Value = Unckecked
        Highlight.Value = Unchecked
        dObject.FormMode = TestMode
    Else
        If dObject.FormMode <> DrawRegionsMode Then dObject.FormMode = DrawRegionsMode
    End If
End Sub
