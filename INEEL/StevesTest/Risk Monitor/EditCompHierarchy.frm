VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Object = "{86CF1D34-0C5F-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCT2.OCX"
Begin VB.Form EditCompHierarchy 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Component Hierarchy"
   ClientHeight    =   4770
   ClientLeft      =   2760
   ClientTop       =   3750
   ClientWidth     =   5940
   BeginProperty Font 
      Name            =   "Arial"
      Size            =   9.75
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   Icon            =   "EditCompHierarchy.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4770
   ScaleWidth      =   5940
   ShowInTaskbar   =   0   'False
   Begin VB.Frame Frame1 
      Caption         =   "Base Component Hierarchy Level"
      Height          =   1695
      Left            =   240
      TabIndex        =   9
      Top             =   2760
      Width           =   3615
      Begin VB.TextBox bcText 
         Height          =   390
         Left            =   1200
         TabIndex        =   11
         Text            =   "Text1"
         Top             =   480
         Width           =   1815
      End
      Begin VB.CommandButton ChangeBCIcon 
         Caption         =   "Change"
         Height          =   375
         Left            =   2040
         TabIndex        =   10
         Top             =   1080
         Width           =   1215
      End
      Begin VB.Label Label4 
         Caption         =   "Name"
         Height          =   375
         Left            =   240
         TabIndex        =   13
         Top             =   480
         Width           =   855
      End
      Begin VB.Label Label3 
         Caption         =   "Icon"
         Height          =   375
         Left            =   240
         TabIndex        =   12
         Top             =   1080
         Width           =   735
      End
      Begin VB.Image Image2 
         Height          =   375
         Left            =   1320
         Top             =   1080
         Width           =   375
      End
   End
   Begin MSComDlg.CommonDialog CommonDialog1 
      Left            =   4560
      Top             =   1680
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
      DialogTitle     =   "Select File for Icon"
      Filter          =   "*.bmp, *.jpg, *.gif, *.ico"
   End
   Begin MSComCtl2.UpDown UpDown1 
      Height          =   375
      Left            =   3240
      TabIndex        =   8
      Top             =   840
      Width           =   240
      _ExtentX        =   423
      _ExtentY        =   661
      _Version        =   393216
      Enabled         =   -1  'True
   End
   Begin VB.CommandButton DeleteH 
      Caption         =   "Delete Level"
      Height          =   375
      Left            =   4080
      TabIndex        =   7
      Top             =   960
      Width           =   1575
   End
   Begin VB.CommandButton InsertH 
      Caption         =   "Insert Level"
      Height          =   375
      Left            =   4080
      TabIndex        =   6
      Top             =   360
      Width           =   1575
   End
   Begin VB.Frame hLevelFrame 
      Caption         =   "Hierarchy Level"
      Height          =   2295
      Left            =   240
      TabIndex        =   1
      Top             =   240
      Width           =   3615
      Begin VB.CommandButton changeIcon 
         Caption         =   "Change"
         Height          =   375
         Left            =   2040
         TabIndex        =   5
         Top             =   1200
         Width           =   1215
      End
      Begin VB.TextBox hText 
         Height          =   390
         Left            =   1200
         TabIndex        =   3
         Text            =   "Text1"
         Top             =   600
         Width           =   1815
      End
      Begin VB.Label totalHLevels 
         Caption         =   "Total Hierarchy Levels"
         Height          =   375
         Left            =   240
         TabIndex        =   14
         Top             =   1800
         Width           =   3135
      End
      Begin VB.Image Image1 
         Height          =   375
         Left            =   1320
         Top             =   1200
         Width           =   375
      End
      Begin VB.Label Label2 
         Caption         =   "Icon"
         Height          =   375
         Left            =   240
         TabIndex        =   4
         Top             =   1200
         Width           =   735
      End
      Begin VB.Label Label1 
         Caption         =   "Name"
         Height          =   375
         Left            =   240
         TabIndex        =   2
         Top             =   600
         Width           =   855
      End
   End
   Begin VB.CommandButton OKButton 
      Caption         =   "OK"
      Height          =   375
      Left            =   4320
      TabIndex        =   0
      Top             =   4080
      Width           =   1335
   End
End
Attribute VB_Name = "EditCompHierarchy"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Option Explicit
Private cHLevel As Integer

Private Sub ChangeBCIcon_Click()
    CommonDialog1.ShowOpen
    Set Image2.Picture = LoadPicture(CommonDialog1.FileName, , , 17, 17)
    compHierarchy.SetBaseIcon CommonDialog1.FileTitle
End Sub

Private Sub changeIcon_Click()
    CommonDialog1.ShowOpen
    Set Image1.Picture = LoadPicture(CommonDialog1.FileName, , , 17, 17)
    compHierarchy.SetIcon cHLevel, CommonDialog1.FileTitle
End Sub

Private Sub DeleteH_Click()
    If cHLevel > compHierarchy.nLevelsInUse Then
        compHierarchy.nLevels = compHierarchy.nLevels - 1
        Dim i As Integer
        For i = cHLevel To compHierarchy.nLevels
            compHierarchy.SetIcon i, compHierarchy.IconFileName(i + 1)
            compHierarchy.SetLevelString i, compHierarchy.LevelStrings(i + 1)
        Next i
        'compHierarchy.SetIcon compHierarchy.nLevels + 1, Nothing
        compHierarchy.SetLevelString compHierarchy.nLevels + 1, ""
        DeleteH.Enabled = compHierarchy.nLevels > 1
        InsertH.Enabled = compHierarchy.nLevels < 10
        UpdateDisplay
        UpDown1.Max = compHierarchy.nLevels - 1
    Else
        MsgBox "Cannot delete this level of hierarchy because it is in use."
    End If
End Sub

Private Sub Form_Load()
    cHLevel = 0
    UpdateDisplay
    
    UpDown1.Max = compHierarchy.nLevels - 1
    UpDown1.Value = cHLevel
    
    bcText.text = compHierarchy.BaseName
    Set Image2.Picture = compHierarchy.BaseIcon
    
    If (compHierarchy.nLevels = 1) Then DeleteH.Enabled = False
    If (compHierarchy.nLevels = 10) Then InsertH.Enabled = False
End Sub

Private Sub InsertH_Click()
    compHierarchy.nLevels = compHierarchy.nLevels + 1
    cHLevel = cHLevel + 1
    Dim i As Integer
    For i = compHierarchy.nLevels To cHLevel + 1 Step -1
        compHierarchy.SetIcon i, compHierarchy.IconFileName(i - 1)
        compHierarchy.SetLevelString i, compHierarchy.LevelStrings(i - 1)
    Next i
    compHierarchy.SetIcon cHLevel, ""
    compHierarchy.SetLevelString cHLevel, "New Hierarchy Level"
    DeleteH.Enabled = compHierarchy.nLevels > 1
    InsertH.Enabled = compHierarchy.nLevels < 10
    UpdateDisplay
    UpDown1.Max = compHierarchy.nLevels - 1
End Sub

Private Sub OKButton_Click()
    compHierarchy.BaseName = bcText.text
    'compHierarchy.SetBaseIcon Image2.Picture
    UpdateSettings
    Unload Me
End Sub

Private Sub UpDown1_Change()
    UpdateSettings
    cHLevel = UpDown1.Value
    UpdateDisplay
End Sub

Private Sub UpdateDisplay()
    hText.text = compHierarchy.LevelStrings(cHLevel)
    hLevelFrame.Caption = "Hierarchy Level " & cHLevel + 1
    Set Image1.Picture = compHierarchy.Icon(cHLevel)
    
    totalHLevels.Caption = "Total Hierarchy Levels = " & compHierarchy.nLevels
End Sub

Private Sub UpdateSettings()
    compHierarchy.SetLevelString cHLevel, hText.text
    'compHierarchy.SetIcon cHLevel, Image1.Picture
End Sub
