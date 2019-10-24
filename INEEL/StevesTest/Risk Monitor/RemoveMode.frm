VERSION 5.00
Object = "{6ABB9000-48F8-11CF-AC42-0040332ED4E5}#4.0#0"; "SFTTREEX.OCX"
Begin VB.Form RemoveMode 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Remove Mode"
   ClientHeight    =   5655
   ClientLeft      =   2760
   ClientTop       =   3750
   ClientWidth     =   6000
   ControlBox      =   0   'False
   Icon            =   "RemoveMode.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   5655
   ScaleWidth      =   6000
   ShowInTaskbar   =   0   'False
   Begin SftTree.SftTree SftTree1 
      Height          =   4215
      Left            =   240
      TabIndex        =   2
      Top             =   600
      Width           =   5535
      _Version        =   262144
      _ExtentX        =   9763
      _ExtentY        =   7435
      _StockProps     =   237
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BorderStyle     =   1
      ItemPictureExpanded=   "RemoveMode.frx":0442
      ItemPictureExpandable=   "RemoveMode.frx":045E
      ItemPictureLeaf =   "RemoveMode.frx":047A
      PlusMinusPictureExpanded=   "RemoveMode.frx":0496
      PlusMinusPictureExpandable=   "RemoveMode.frx":04B2
      PlusMinusPictureLeaf=   "RemoveMode.frx":04CE
      ButtonPicture   =   "RemoveMode.frx":04EA
      BeginProperty ColHeaderFont {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BeginProperty RowHeaderFont {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BeginProperty ItemEditFont {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      GridStyle       =   1
      ButtonStyle     =   0
      TreeLineStyle   =   0
      Columns         =   2
      ColWidth0       =   100
      ColTitle0       =   "Mode"
      ColWidth1       =   100
      ColTitle1       =   "Start Time"
      ColBmp1         =   "RemoveMode.frx":0506
      MultiSelect     =   1
      MouseIcon       =   "RemoveMode.frx":0522
      RowColHeaderAppearance=   0
      RowColPicture   =   "RemoveMode.frx":053E
      RowHeaderAppearance=   0
      ColPict1        =   "RemoveMode.frx":055A
      BackgroundPicture=   "RemoveMode.frx":0576
   End
   Begin VB.CommandButton CancelButton 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   1440
      TabIndex        =   1
      Top             =   5040
      Width           =   1215
   End
   Begin VB.CommandButton OKButton 
      Caption         =   "OK"
      Height          =   375
      Left            =   3360
      TabIndex        =   0
      Top             =   5040
      Width           =   1215
   End
   Begin VB.Label Label2 
      Alignment       =   1  'Right Justify
      Caption         =   "Label2"
      Height          =   255
      Left            =   2880
      TabIndex        =   4
      Top             =   360
      Width           =   2895
   End
   Begin VB.Label Label1 
      Caption         =   "Select Mode(s) to remove:"
      Height          =   255
      Left            =   240
      TabIndex        =   3
      Top             =   360
      Width           =   1935
   End
End
Attribute VB_Name = "RemoveMode"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Option Explicit
Public RowReturn As Integer
Public rarray As Variant
'Function: CancelButton_Click
'Purpose: Handles the event when cancel is clicked
Private Sub CancelButton_Click()
    Me.Hide
    'Unload Me
End Sub
'Function: Form Load
'Purpose: load data into the remove mode form
Private Sub Form_Load()
    Dim mySQL As String
    Dim resultSet As rdoResultset
 
    SftTree1.ColumnWidth(0) = SftTree1.Width / 2 - 150
    
    Dim i As Integer
    Dim Index As Long
    
    For i = 0 To RowReturn - 1
        Index = SftTree1.AddItem(rarray(2, i))
        SftTree1.CellText(Index, 1) = rarray(1, i)
    Next i
    
    Label2.Caption = "Total Mode(s) = " & SftTree1.listCount
    

End Sub
'Function: OKButton_Click
'Purpose: Handles the event when ok is clicked. Does error checking and then
'removes modes.
Private Sub OKButton_Click()
    
    Dim i, j As Integer
    Dim SearchString As String
    Dim modeID As Integer
    Dim mySQL As String
    Dim nextModeTime As Date
    
    'for each node that is selected
    For i = 0 To SftTree1.listCount - 1
        If SftTree1.Selected(i) = True Then
            SearchString = SftTree1.CellText(i, 0)
            'get mode id
            For j = 0 To RowReturn - 1
                If SearchString = rarray(2, j) And SftTree1.CellText(i, 1) = rarray(1, j) Then
                    modeID = rarray(0, j)
                    If pManager.removeModeCheck(modeID, SearchString, SftTree1.CellText(i, 1)) = True Then
                        'remove mode
                        If i = SftTree1.listCount - 1 Then
                            nextModeTime = MDIMain.GetActiveWorkspace().EndTime
                        Else
                            nextModeTime = SftTree1.CellText(i + 1, 1)
                        End If
                        pManager.DeleteWorkspaceMode MDIMain.returnID, modeID, SftTree1.CellText(i, 1), nextModeTime
                    Else
                        MsgBox "Mode: " & SearchString & Module1.NewLine _
                            & "Start Time: " & SftTree1.CellText(i, 1) _
                            & Module1.NewLine & "Could not be removed due to Procedure/Mode time conflict.", vbInformation
                    End If
                    'MsgBox "Mode Should be Deleted Here ModeID = " & modeid
                End If
            Next j
        End If
    Next i
                
    Me.Hide

End Sub


