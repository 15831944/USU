VERSION 5.00
Object = "{6ABB9000-48F8-11CF-AC42-0040332ED4E5}#4.0#0"; "SFTTREEX.OCX"
Begin VB.Form TestSFTMultiSelect 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Dialog Caption"
   ClientHeight    =   3195
   ClientLeft      =   2760
   ClientTop       =   3750
   ClientWidth     =   6870
   Icon            =   "TestSFTMultiSelect.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3195
   ScaleWidth      =   6870
   ShowInTaskbar   =   0   'False
   Begin SftTree.SftTree AssociatedEventsList 
      Height          =   2775
      Left            =   240
      TabIndex        =   2
      Top             =   240
      Width           =   4815
      _Version        =   262144
      _ExtentX        =   8493
      _ExtentY        =   4895
      _StockProps     =   237
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      BorderStyle     =   1
      ItemPictureExpanded=   "TestSFTMultiSelect.frx":0442
      ItemPictureExpandable=   "TestSFTMultiSelect.frx":045E
      ItemPictureLeaf =   "TestSFTMultiSelect.frx":047A
      PlusMinusPictureExpanded=   "TestSFTMultiSelect.frx":0496
      PlusMinusPictureExpandable=   "TestSFTMultiSelect.frx":04B2
      PlusMinusPictureLeaf=   "TestSFTMultiSelect.frx":04CE
      ButtonPicture   =   "TestSFTMultiSelect.frx":04EA
      BeginProperty ColHeaderFont {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BeginProperty RowHeaderFont {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BeginProperty ItemEditFont {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      GridStyle       =   3
      ButtonStyle     =   0
      TreeLineStyle   =   0
      Columns         =   2
      ColWidth0       =   100
      ColTitle0       =   "Mode"
      ColWidth1       =   100
      ColTitle1       =   "Start Time"
      ColBmp1         =   "TestSFTMultiSelect.frx":0506
      MultiSelect     =   1
      MouseIcon       =   "TestSFTMultiSelect.frx":0522
      SelectStyle     =   2
      RowColHeaderAppearance=   0
      RowColPicture   =   "TestSFTMultiSelect.frx":053E
      RowHeaderAppearance=   0
      ColPict1        =   "TestSFTMultiSelect.frx":055A
      BackgroundPicture=   "TestSFTMultiSelect.frx":0576
   End
   Begin VB.CommandButton CancelButton 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   5400
      TabIndex        =   1
      Top             =   840
      Width           =   1215
   End
   Begin VB.CommandButton OKButton 
      Caption         =   "OK"
      Height          =   375
      Left            =   5400
      TabIndex        =   0
      Top             =   240
      Width           =   1215
   End
End
Attribute VB_Name = "TestSFTMultiSelect"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Option Explicit

Private Sub Form_Load()
    AssociatedEventsList.Clear
    AssociatedEventsList.Columns = 3
    AssociatedEventsList.AddItem ("(0,0)")
    AssociatedEventsList.CellText(0, 1) = "(0,1)"
    AssociatedEventsList.CellText(0, 2) = "(0,2)"
    AssociatedEventsList.AddItem ("(1,0)")
    AssociatedEventsList.CellText(1, 1) = "(1,1)"
    AssociatedEventsList.CellText(1, 2) = "(1,2)"
    AssociatedEventsList.AddItem ("(2,0)")
    AssociatedEventsList.CellText(2, 1) = "(2,1)"
    AssociatedEventsList.CellText(2, 2) = "(2,2)"
    AssociatedEventsList.AddItem ("(3,0)")
    AssociatedEventsList.CellText(3, 1) = "(3,1)"
    AssociatedEventsList.CellText(3, 2) = "(3,2)"
    
    
End Sub
