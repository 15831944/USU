VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form ModeColor 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Mode Color"
   ClientHeight    =   3030
   ClientLeft      =   2760
   ClientTop       =   3750
   ClientWidth     =   4215
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3030
   ScaleWidth      =   4215
   ShowInTaskbar   =   0   'False
   Begin VB.CommandButton Command1 
      Caption         =   "..."
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   18
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   3000
      TabIndex        =   5
      Top             =   1320
      Width           =   615
   End
   Begin VB.TextBox Text1 
      Height          =   375
      Left            =   600
      TabIndex        =   4
      Top             =   1320
      Width           =   2295
   End
   Begin VB.ComboBox Combo1 
      Height          =   315
      Left            =   600
      TabIndex        =   2
      Text            =   "Combo1"
      Top             =   600
      Width           =   3015
   End
   Begin VB.CommandButton CancelButton 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   600
      TabIndex        =   1
      Top             =   2280
      Width           =   1215
   End
   Begin VB.CommandButton OKButton 
      Caption         =   "OK"
      Height          =   375
      Left            =   2400
      TabIndex        =   0
      Top             =   2280
      Width           =   1215
   End
   Begin MSComDlg.CommonDialog ChooseColor 
      Left            =   0
      Top             =   0
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
      CancelError     =   -1  'True
   End
   Begin VB.Label Label1 
      Caption         =   "Select Mode:"
      Height          =   375
      Left            =   600
      TabIndex        =   3
      Top             =   360
      Width           =   2295
   End
End
Attribute VB_Name = "ModeColor"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Option Explicit
Public colour As Long
Public rArray As Variant
Public RowReturn As Integer

Private Sub CancelButton_Click()
    Unload Me
End Sub

Private Sub Combo1_Click()
'
    Dim i As Integer
    For i = 0 To RowReturn - 1
        If Combo1.text = rArray(0, i) Then
            Text1.BackColor = rArray(1, i)
            colour = rArray(1, i)
            Exit Sub
        End If
        
    Next i
End Sub

Private Sub Command1_Click()
    Dim mySQL As String
    ChooseColor.Color = Text1.BackColor
    On Error GoTo CancelError
    
    ChooseColor.ShowColor
    Text1.BackColor = ChooseColor.Color
    colour = ChooseColor.Color
    
    Dim i As Integer
    For i = 0 To RowReturn - 1
        If Combo1.text = rArray(0, i) Then
            mySQL = "UPDATE [Mode] SET ModeColor = " & colour & " WHERE ModeID = " & rArray(2, i)
            dbConnection.Execute (mySQL)
            ModeList(rArray(2, i)).ModeColor = colour
            rArray(1, i) = colour
            Exit Sub
        End If
        
    Next i
CancelError:
End Sub

Private Sub Form_Load()
    Dim mySQL As String
    Dim resultSet As rdoResultset
    Dim i As Integer
    
    
    RowReturn = 0
    
    mySQL = "SELECT ModeName, ModeColor, ModeID FROM [MODE]"
    Set resultSet = dbConnection.OpenResultset(mySQL, rdOpenKeyset)
    
    While Not resultSet.EOF
        resultSet.MoveNext
        RowReturn = RowReturn + 1
    Wend
    resultSet.MoveFirst
    rArray = resultSet.GetRows(RowReturn)

    For i = 0 To RowReturn - 1
        Combo1.AddItem rArray(0, i)
    Next i
    
    Combo1.text = rArray(0, 0)
    colour = rArray(1, 0)
    Text1.BackColor = colour
End Sub

Private Sub OKButton_Click()
    MDIMain.RefreshData
    Unload Me
End Sub

Private Sub Text1_Click()
'
    Dim mySQL As String
    ChooseColor.Color = Text1.BackColor
    On Error GoTo CancelError
    
    ChooseColor.ShowColor
    Text1.BackColor = ChooseColor.Color
    colour = ChooseColor.Color
    
    Dim i As Integer
    For i = 0 To RowReturn - 1
        If Combo1.text = rArray(0, i) Then
            mySQL = "UPDATE [Mode] SET ModeColor = " & colour & " WHERE ModeID = " & rArray(2, i)
            dbConnection.Execute (mySQL)
            ModeList(rArray(2, i)).ModeColor = colour
            rArray(1, i) = colour
            Exit Sub
        End If
        
    Next i
CancelError:
End Sub
