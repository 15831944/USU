VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form ModeProperties 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "[name of mode here]"
   ClientHeight    =   5145
   ClientLeft      =   2760
   ClientTop       =   3750
   ClientWidth     =   7590
   BeginProperty Font 
      Name            =   "Arial"
      Size            =   9.75
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   Icon            =   "ModeForm.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   5145
   ScaleWidth      =   7590
   ShowInTaskbar   =   0   'False
   Begin VB.CommandButton Help 
      Caption         =   "Help"
      Height          =   375
      Left            =   6120
      TabIndex        =   17
      Top             =   4560
      Width           =   1215
   End
   Begin VB.Frame Frame1 
      Caption         =   "Mode Properties"
      Height          =   4095
      Left            =   240
      TabIndex        =   2
      Top             =   240
      Width           =   7095
      Begin VB.CommandButton colorButton 
         Caption         =   "..."
         Height          =   375
         Left            =   4200
         TabIndex        =   20
         Top             =   1440
         Width           =   375
      End
      Begin MSComDlg.CommonDialog ChooseColor 
         Left            =   6360
         Top             =   3480
         _ExtentX        =   847
         _ExtentY        =   847
         _Version        =   393216
         CancelError     =   -1  'True
      End
      Begin VB.TextBox Text7 
         BackColor       =   &H000080FF&
         Height          =   375
         Left            =   2400
         Locked          =   -1  'True
         TabIndex        =   19
         Top             =   1440
         Width           =   1695
      End
      Begin VB.CommandButton AcquireBaseRisk 
         Caption         =   "Acquire"
         Height          =   375
         Left            =   4320
         TabIndex        =   16
         Top             =   2400
         Width           =   1215
      End
      Begin VB.CommandButton BrowseForProj 
         Caption         =   "Browse..."
         Height          =   375
         Left            =   5640
         TabIndex        =   15
         Top             =   1920
         Width           =   1215
      End
      Begin VB.TextBox Text6 
         Height          =   375
         Left            =   2400
         TabIndex        =   14
         Text            =   "Text6"
         Top             =   3360
         Width           =   1695
      End
      Begin VB.TextBox Text5 
         Height          =   375
         Left            =   2400
         TabIndex        =   13
         Text            =   "Text5"
         Top             =   2880
         Width           =   1695
      End
      Begin VB.TextBox Text4 
         Height          =   375
         Left            =   2400
         TabIndex        =   10
         Text            =   "Text4"
         Top             =   2400
         Width           =   1695
      End
      Begin VB.TextBox Text3 
         BackColor       =   &H80000000&
         Height          =   375
         Left            =   2400
         Locked          =   -1  'True
         TabIndex        =   8
         Text            =   "Text3"
         Top             =   1920
         Width           =   3015
      End
      Begin VB.TextBox Text2 
         Height          =   375
         Left            =   2400
         TabIndex        =   6
         Text            =   "Text2"
         Top             =   960
         Width           =   4455
      End
      Begin VB.TextBox Text1 
         Height          =   375
         Left            =   2400
         TabIndex        =   4
         Text            =   "Text1"
         Top             =   480
         Width           =   3015
      End
      Begin VB.Label Label7 
         Caption         =   "Mode Color"
         Height          =   255
         Left            =   360
         TabIndex        =   18
         Top             =   1440
         Width           =   1455
      End
      Begin VB.Label Label6 
         Caption         =   "High Risk Level"
         Height          =   375
         Left            =   360
         TabIndex        =   12
         Top             =   3360
         Width           =   1815
      End
      Begin VB.Label Label5 
         Caption         =   "Medium Risk Level"
         Height          =   375
         Left            =   360
         TabIndex        =   11
         Top             =   2880
         Width           =   1695
      End
      Begin VB.Label Label4 
         Caption         =   "Baseline Risk Level"
         Height          =   375
         Left            =   360
         TabIndex        =   9
         Top             =   2400
         Width           =   1935
      End
      Begin VB.Label Label3 
         Caption         =   "SAPHIRE Folder"
         Height          =   375
         Left            =   360
         TabIndex        =   7
         Top             =   1920
         Width           =   1935
      End
      Begin VB.Label Label2 
         Caption         =   "Description"
         Height          =   375
         Left            =   360
         TabIndex        =   5
         Top             =   960
         Width           =   1095
      End
      Begin VB.Label Label1 
         Caption         =   "Name"
         Height          =   375
         Left            =   360
         TabIndex        =   3
         Top             =   480
         Width           =   1095
      End
   End
   Begin VB.CommandButton CancelButton 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   4680
      TabIndex        =   1
      Top             =   4560
      Width           =   1215
   End
   Begin VB.CommandButton OKButton 
      Caption         =   "OK"
      Height          =   375
      Left            =   3240
      TabIndex        =   0
      Top             =   4560
      Width           =   1215
   End
End
Attribute VB_Name = "ModeProperties"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Option Explicit
Public ModeObject As ModeClass
Public ModeIndex As Integer
Public Result As Boolean
'**************| Steve's DLL support |****************************
Private Declare Function IsProjectGood Lib "riskMon" (ByVal ProjectPath As String, ByRef errorDesc As String) As Long
'*****************************************************************



Private Sub AcquireBaseRisk_Click()
    If ModeObject.ProjectPath = "(none)" Then
        MsgBox "You must first select a SAPHIRE 7 project to associate with this mode.", vbInformation
        Exit Sub
    End If
End Sub

Private Sub BrowseForProj_Click()
    Dim pPath As String
    pPath = BrowseForFolder("Select the SAPHIRE 7 Project Folder for Mode " & ModeObject.ModeName)
    If pPath <> "" Then
        ' test out pPath to make sure it is ok (a valid SAPH 7 project)
        Dim i As Integer, duplicate As Boolean
        For i = 1 To ModeList.Count
            If ModeList.Item(i).ObjectInUse = True And i <> ModeIndex Then
                If pPath = ModeList.Item(i).ProjectPath Then
                    duplicate = True
                    Exit For
                End If
            End If
        Next i
        If duplicate Then
            MsgBox "This SAPHIRE project is already in use by another mode.  Two modes may not be associated with the same project.", vbInformation
        Else
            Dim errorDesc As String * 61, rValue As Long
            'rValue = IsProjectGood(pPath & "\", errorDesc)
            If rValue = 0 Then
                ModeObject.ProjectPath = pPath
                Text3.text = pPath
            Else
                MsgBox "The following error occured when opening this project: " & errorDesc, vbInformation, "Invalid SAPHIRE 7.0 Project"
            End If
        End If
    End If
End Sub

Private Sub CancelButton_Click()
    Result = False
    Me.Hide
End Sub

Private Sub colorButton_Click()
    ChooseColor.Color = Text7.BackColor
    On Error GoTo CancelError
    
    ChooseColor.ShowColor
    Text7.BackColor = ChooseColor.Color
CancelError:

End Sub

Private Sub Help_Click()
    MsgBox "No Help is available yet.", vbInformation
End Sub


Private Sub OKButton_Click()
    ' make sure that the SAPHIRE project is OK before allowing the user to
    ' exit out with Result = True
    If ModeObject.ProjectPath = "(none)" Then
        MsgBox "You must first select a SAPHIRE 7 project to associate with this mode.", vbInformation
        Exit Sub
    End If
    ModeObject.ModeName = Text1.text
    ModeObject.ModeDescription = Text2.text

    ModeObject.BaselineRisk = Text4.text
    ModeObject.MediumRisk = Text5.text
    ModeObject.HighRisk = Text6.text
    ModeObject.ModeColor = Text7.BackColor
    
    Result = True
    Me.Hide
End Sub

Private Sub Form_Load()
    Text1.text = ModeObject.ModeName
    Text2.text = ModeObject.ModeDescription
    Text3.text = ModeObject.ProjectPath
    Text4.text = ModeObject.BaselineRisk
    Text5.text = ModeObject.MediumRisk
    Text6.text = ModeObject.HighRisk
    Text7.BackColor = ModeObject.ModeColor
    Caption = ModeObject.ModeName
End Sub

Private Sub Text1_Change()
    Caption = Text1.text
End Sub


Private Sub Text7_Click()
    ChooseColor.Color = Text7.BackColor
    On Error GoTo CancelError
    
    ChooseColor.ShowColor
    Text7.BackColor = ChooseColor.Color
CancelError:
        
End Sub
