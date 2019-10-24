VERSION 5.00
Object = "{6ABB9000-48F8-11CF-AC42-0040332ED4E5}#4.0#0"; "SFTTREEX.OCX"
Begin VB.Form EditModeTime 
   Caption         =   "Edit Mode Time"
   ClientHeight    =   5385
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   5775
   Icon            =   "EditModeTime.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   5385
   ScaleWidth      =   5775
   StartUpPosition =   3  'Windows Default
   Begin SftTree.SftTree SftTree1 
      Height          =   4215
      Left            =   120
      TabIndex        =   0
      Top             =   360
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
      ItemPictureExpanded=   "EditModeTime.frx":0442
      ItemPictureExpandable=   "EditModeTime.frx":045E
      ItemPictureLeaf =   "EditModeTime.frx":047A
      PlusMinusPictureExpanded=   "EditModeTime.frx":0496
      PlusMinusPictureExpandable=   "EditModeTime.frx":04B2
      PlusMinusPictureLeaf=   "EditModeTime.frx":04CE
      ButtonPicture   =   "EditModeTime.frx":04EA
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
      ColBmp1         =   "EditModeTime.frx":0506
      MouseIcon       =   "EditModeTime.frx":0522
      RowColHeaderAppearance=   0
      RowColPicture   =   "EditModeTime.frx":053E
      RowHeaderAppearance=   0
      ColPict1        =   "EditModeTime.frx":055A
      BackgroundPicture=   "EditModeTime.frx":0576
   End
   Begin VB.CommandButton OKButton 
      Caption         =   "OK"
      Height          =   375
      Left            =   3240
      TabIndex        =   2
      Top             =   4800
      Width           =   1215
   End
   Begin VB.CommandButton CancelButton 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   1320
      TabIndex        =   1
      Top             =   4800
      Width           =   1215
   End
   Begin VB.Label Label1 
      Caption         =   "Select Mode to edit:"
      Height          =   255
      Left            =   120
      TabIndex        =   4
      Top             =   120
      Width           =   1935
   End
   Begin VB.Label Label2 
      Alignment       =   1  'Right Justify
      Caption         =   "Label2"
      Height          =   255
      Left            =   2760
      TabIndex        =   3
      Top             =   120
      Width           =   2895
   End
End
Attribute VB_Name = "EditModeTime"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Option Explicit
Public RowReturn As Integer
Public rarray As Variant
Public aWorkspace As Workspace
'Function: CancelButton_Click
'Purpose: Handles the event when cancel is clicked
Private Sub CancelButton_Click()
    Me.Hide
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
        SftTree1.ItemData(Index) = rarray(0, i)
    Next i
    
    Label2.Caption = "Total Mode(s) = " & SftTree1.listCount
    

End Sub
'Function: OKButton_Click
'Purpose: Handles the event when ok is clicked.
Private Sub OKButton_Click()
    
    Dim i, j As Integer
    Dim name As String
    Dim StartTime As Date
    Dim NewStartTime As Date
    Dim modeID As Integer
    Dim mySQL As String
    Dim Index As Long
    'Dim modeID As Integer
    
    Index = SftTree1.ListSelection
    name = SftTree1.CellText(Index, 0)
    StartTime = SftTree1.CellText(Index, 1)
    modeID = SftTree1.ItemData(Index)
    
    ModeTimeChange.StartTime = StartTime
    ModeTimeChange.myName = name
    ModeTimeChange.modeID = modeID
    Set ModeTimeChange.aWS = aWorkspace
    
    ModeTimeChange.Show 1
    
    If ModeTimeChange.CancelClick = False Then
        NewStartTime = ModeTimeChange.StartTime
        ButtonFunctions.ChangeModeTime modeID, name, StartTime, NewStartTime, aWorkspace
    
    End If
    Unload ModeTimeChange
                
    Me.Hide

End Sub



