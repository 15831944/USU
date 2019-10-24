VERSION 5.00
Begin VB.Form RiskValues 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Risk Cut Off Values"
   ClientHeight    =   3390
   ClientLeft      =   2760
   ClientTop       =   3750
   ClientWidth     =   5310
   BeginProperty Font 
      Name            =   "Arial"
      Size            =   9.75
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   Icon            =   "RiskValues.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3390
   ScaleWidth      =   5310
   ShowInTaskbar   =   0   'False
   Begin VB.ComboBox Combo1 
      Height          =   360
      Left            =   720
      Style           =   2  'Dropdown List
      TabIndex        =   9
      Top             =   600
      Width           =   3735
   End
   Begin VB.TextBox Text1 
      Alignment       =   1  'Right Justify
      Height          =   375
      Left            =   1680
      TabIndex        =   3
      Top             =   1200
      Width           =   1695
   End
   Begin VB.TextBox Text2 
      Alignment       =   1  'Right Justify
      Height          =   375
      Left            =   1680
      TabIndex        =   2
      Top             =   2040
      Width           =   1695
   End
   Begin VB.CommandButton CancelButton 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   1080
      TabIndex        =   1
      Top             =   2640
      Width           =   1215
   End
   Begin VB.CommandButton OKButton 
      Caption         =   "OK"
      Height          =   375
      Left            =   2760
      TabIndex        =   0
      Top             =   2640
      Width           =   1215
   End
   Begin VB.Label Label5 
      Caption         =   "Select Mode:"
      Height          =   375
      Left            =   720
      TabIndex        =   10
      Top             =   240
      Width           =   2055
   End
   Begin VB.Label Label1 
      Alignment       =   1  'Right Justify
      Caption         =   "0 to "
      Height          =   375
      Left            =   0
      TabIndex        =   8
      Top             =   1200
      Width           =   1575
   End
   Begin VB.Label Label2 
      Caption         =   "is LOW risk."
      Height          =   375
      Left            =   3480
      TabIndex        =   7
      Top             =   1200
      Width           =   1575
   End
   Begin VB.Label Label3 
      Alignment       =   1  'Right Justify
      Caption         =   "Label3"
      Height          =   375
      Left            =   1200
      TabIndex        =   6
      Top             =   1680
      Width           =   2100
   End
   Begin VB.Label Label4 
      Caption         =   "is MEDIUM risk"
      Height          =   375
      Left            =   3480
      TabIndex        =   5
      Top             =   1680
      Width           =   1650
   End
   Begin VB.Label Label6 
      Caption         =   "to 1 is HIGH risk"
      Height          =   375
      Left            =   3480
      TabIndex        =   4
      Top             =   2160
      Width           =   1575
   End
End
Attribute VB_Name = "RiskValues"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Option Explicit

Dim rArray As Variant
Dim RowReturn As Integer
Dim base As Double
Dim ActiveModeID As Integer
Dim curComboIndex As Integer
Dim explicitChange As Boolean


'Function:CancelButton_Click
'Purpose:handles the cancel click event
Private Sub CancelButton_Click()
    Unload Me
End Sub


'Function: Combo1_Click
'Purpose: reset values in text boxes when a different mode is selected
Private Sub Combo1_Click()
    If Text1.text <> "" And Not explicitChange Then
        If Not SaveRiskCutOffs() Then
            explicitChange = True
            Combo1.ListIndex = curComboIndex
            explicitChange = False
            Exit Sub
        End If
    End If
    
    curComboIndex = Combo1.ListIndex
    ActiveModeID = Combo1.ItemData(Combo1.ListIndex)
    'Dim i As Integer
    'For i = 0 To RowReturn - 1
    '    If rArray(0, i) = Combo1.text Then
    '        base = rArray(1, i)
    '        Label1.Caption = rArray(1, i) & " to"
    '        Label3.Caption = rArray(2, i) & " to " & rArray(3, i)
    '        Text1 = Str(rArray(2, i))
    '        Text2 = Str(rArray(3, i))
    '    End If
    '
    'Next i
    Dim Baseline, Medium, High As Double
    Baseline = ModeList.Item(ActiveModeID).BaselineRisk
    Medium = ModeList.Item(ActiveModeID).MediumRisk
    High = ModeList.Item(ActiveModeID).HighRisk
    base = Baseline
    Label1.Caption = Baseline & " to"
    Label3.Caption = Medium & " to " & High
    Text1 = Medium
    Text2 = High
    
End Sub

'Function:Form_Load
'Purpose:loads the form and displays the current risk values.
Private Sub Form_Load()

    'Dim mySQL As String
    'Dim resultSet As rdoResultset
    Dim i As Integer
    
    For i = 1 To ModeList.count
        If ModeList.Item(i).ObjectInUse Then
            Combo1.AddItem ModeList.Item(i).ModeName
            Combo1.ItemData(Combo1.listCount - 1) = i
        End If
    Next i
    
    If ModeCount > 0 Then
        ActiveModeID = Combo1.ItemData(0)
        curComboIndex = 0
        Combo1.ListIndex = 0
    Else
    
    End If

End Sub

'Function:OKButton_Click
'Purpose:handles the okbutton click by checking for correct values and then
'setting the variables in form main and the database.
Private Sub OKButton_Click()
    SaveRiskCutOffs
    Unload Me
End Sub
'Function:Text1_Change
'Purpose:make sure the text in the text boxes is current
Private Sub Text1_Change()
    Label3.Caption = Text1 & " to " & Text2
End Sub
'Function:Text2_Change
'Purpose:make sure the text in the text boxes is current
Private Sub Text2_Change()
    Label3.Caption = Text1 & " to " & Text2
End Sub

Private Function SaveRiskCutOffs() As Boolean
    Dim temp As Double
     Dim mySQLStatement As String
      
     'make sure medium is less than high cutoff value
     If Val(Text1) > Val(Text2) Then
        MsgBox "Invalid Values", vbInformation
        SaveRiskCutOffs = False
        Exit Function
     End If
     
    'check to make sure valid data was entered before resetting variables
    If Val(Text1) < base Or Val(Text1) > 1 Then
        MsgBox "Invalid Values", vbInformation
        SaveRiskCutOffs = False
        Exit Function
    End If
    
    If Val(Text2) < base Or Val(Text2) > 1 Then
        MsgBox "Invalid Values", vbInformation
        SaveRiskCutOffs = False
        Exit Function
    End If
    
    'Update values
    ModeList.Item(ActiveModeID).MediumRisk = Val(Text1)
    ModeList.Item(ActiveModeID).HighRisk = Val(Text2)
    mySQLStatement = "UPDATE [Mode] SET MediumRisk = " & Text1 & ", HighRisk = " & Text2 & " WHERE ModeID = " & ActiveModeID
    dbConnection.Execute (mySQLStatement)
    SaveRiskCutOffs = True
End Function
