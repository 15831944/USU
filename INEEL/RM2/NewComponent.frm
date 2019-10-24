VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form NewComponent 
   AutoRedraw      =   -1  'True
   BorderStyle     =   3  'Fixed Dialog
   ClientHeight    =   2835
   ClientLeft      =   2760
   ClientTop       =   3750
   ClientWidth     =   5550
   Icon            =   "NewComponent.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2835
   ScaleWidth      =   5550
   ShowInTaskbar   =   0   'False
   Begin MSComctlLib.ImageList hIconsList 
      Left            =   4800
      Top             =   240
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   17
      ImageHeight     =   17
      MaskColor       =   12632256
      _Version        =   393216
   End
   Begin MSComctlLib.ImageCombo hCombo 
      Height          =   330
      Left            =   2040
      TabIndex        =   9
      Top             =   240
      Width           =   1935
      _ExtentX        =   3413
      _ExtentY        =   582
      _Version        =   393216
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      Text            =   "ImageCombo1"
   End
   Begin VB.CommandButton changeDiagram 
      Caption         =   "Change..."
      Height          =   375
      Left            =   3840
      TabIndex        =   8
      Top             =   1200
      Width           =   1455
   End
   Begin VB.TextBox Text3 
      Height          =   375
      Left            =   2040
      TabIndex        =   7
      Text            =   "Text3"
      Top             =   1200
      Width           =   1695
   End
   Begin VB.CommandButton viewDiagram 
      Caption         =   "View Diagram..."
      Height          =   375
      Left            =   240
      TabIndex        =   5
      Top             =   1680
      Width           =   1575
   End
   Begin VB.TextBox Text1 
      Height          =   375
      Left            =   2040
      TabIndex        =   3
      Text            =   "Text1"
      Top             =   720
      Width           =   1695
   End
   Begin VB.CommandButton CancelButton 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   4080
      TabIndex        =   1
      Top             =   2280
      Width           =   1215
   End
   Begin VB.CommandButton OKButton 
      Caption         =   "OK"
      Height          =   375
      Left            =   2760
      TabIndex        =   0
      Top             =   2280
      Width           =   1215
   End
   Begin MSComDlg.CommonDialog CommonDialog1 
      Left            =   4080
      Top             =   240
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
      DialogTitle     =   "Select File for P&ID Diagram"
      Filter          =   "*.bmp, *.jpg, *.gif, *.ico"
   End
   Begin VB.Label CompIDLabel 
      Height          =   375
      Left            =   3840
      TabIndex        =   10
      Top             =   720
      Width           =   1455
   End
   Begin VB.Label Label3 
      Caption         =   "Component Diagram"
      Height          =   375
      Left            =   240
      TabIndex        =   6
      Top             =   1200
      Width           =   1695
   End
   Begin VB.Label Label2 
      Caption         =   "Hierarchy Level"
      Height          =   375
      Left            =   240
      TabIndex        =   4
      Top             =   240
      Width           =   1695
   End
   Begin VB.Label Label1 
      Caption         =   "Component Name"
      Height          =   375
      Left            =   240
      TabIndex        =   2
      Top             =   720
      Width           =   1695
   End
End
Attribute VB_Name = "NewComponent"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Option Explicit
Public dlgCaption As String
Public componentName As String
Public diagramPath As String
Public Result As Boolean
Public hLevel As Integer
Public minHLevel As Integer
Public maxHLevel As Integer
Public changesMade As Boolean
Public LockForm As Boolean

Private Sub CancelButton_Click()
    Result = False
    Me.Hide
End Sub

Private Sub changeDiagram_Click()
    If (pidDirectory = "") Then
        If (MsgBox("There is no P&ID directory (directory for component diagrams) associated with this project." & NewLine & _
            "Would you like to select a P&ID directory now?", vbYesNo + vbQuestion) = vbYes) Then
            pidDirectory = BrowseForFolder("Select P&ID directory")
            If pidDirectory = "" Then Exit Sub
            pidDirectory = pidDirectory & "\"
            SaveSetting "RiskMonitor", "STARTUP", "PID_Directory", pidDirectory
        Else
            Exit Sub
        End If
    End If
                
    If Text3.text = "(none)" Then
        CommonDialog1.FileName = ""
    Else
        CommonDialog1.FileName = Text3.text
    End If
    
    CommonDialog1.InitDir = pidDirectory
    CommonDialog1.Flags = cdlOFNFileMustExist Or cdlOFNHideReadOnly Or cdlOFNNoChangeDir Or cdlOFNPathMustExist

    Do
        CommonDialog1.ShowOpen
        'Set Image1.Picture = LoadPicture(CommonDialog1.FileName, , , 17, 17)
        If (CommonDialog1.FileTitle = "") Then
            Exit Sub
        ElseIf (CommonDialog1.FileName <> pidDirectory & CommonDialog1.FileTitle) Then
            MsgBox "You may only select files for P&ID diagrams in the " & pidDirectory, vbInformation
        Else
            changesMade = True
            viewDiagram.Enabled = True
            Text3.text = CommonDialog1.FileTitle
            Exit Sub
        End If
    Loop
 
    
End Sub

Private Sub Form_Activate()
    Text1.SetFocus
    changesMade = False
End Sub

Private Sub Form_Load()
    If (diagramPath = "(none)" Or diagramPath = "") Then
        viewDiagram.Enabled = False
    End If
    
    Dim i As Integer
    
    For i = minHLevel To maxHLevel 'compHierarchy.nLevels - 1
        hIconsList.ListImages.Add , , compHierarchy.Icon(i)
    Next i
       
    hCombo.ImageList = hIconsList
       
    For i = 1 To maxHLevel - minHLevel + 1   'compHierarchy.nLevels
        hCombo.ComboItems.Add
        hCombo.ComboItems.Item(i).Image = i ' + minHLevel
        hCombo.ComboItems.Item(i).text = compHierarchy.LevelStrings(i + minHLevel - 1)
        hCombo.ComboItems.Item(i).tag = i + minHLevel - 1
    Next i
    
    If hLevel < minHLevel Then hLevel = minHLevel
    If hLevel > maxHLevel Then hLevel = maxHLevel
    
    hCombo.SelectedItem = hCombo.ComboItems.Item(hLevel - minHLevel + 1)
    
    Text1.text = componentName
    Text3.text = diagramPath
    Me.Caption = dlgCaption
    hCombo_Click
    
    hCombo.Locked = LockForm
    Text1.Locked = LockForm
    Text3.Locked = LockForm
    changeDiagram.Enabled = Not LockForm
    CancelButton.Enabled = Not LockForm
End Sub

Private Sub hCombo_Click()
    Label1.Caption = hCombo.SelectedItem.text & " Name"
    Label3.Caption = hCombo.SelectedItem.text & " Diagram"
    Me.Caption = "New " & hCombo.SelectedItem.text
    hLevel = hCombo.SelectedItem.tag
    changesMade = True
End Sub

Private Sub OKButton_Click()
    Result = True
    componentName = Text1.text
    diagramPath = Text3.text
    Me.Hide
End Sub

Private Sub Text1_Change()
    changesMade = True
End Sub

Private Sub Text1_KeyPress(KeyAscii As Integer)
    If KeyAscii = 13 And Len(Text1.text) > 0 Then
        OKButton_Click
    End If
End Sub

Private Sub viewDiagram_Click()
    Dim cForm As ComponentDiagram
    Set cForm = New ComponentDiagram
    cForm.pictureName = Text3.text
    cForm.Show vbModal
End Sub
