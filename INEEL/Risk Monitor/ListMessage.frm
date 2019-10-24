VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form ListMessage 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Dialog Caption"
   ClientHeight    =   4515
   ClientLeft      =   2760
   ClientTop       =   3750
   ClientWidth     =   4335
   BeginProperty Font 
      Name            =   "Arial"
      Size            =   9.75
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   Icon            =   "ListMessage.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4515
   ScaleWidth      =   4335
   ShowInTaskbar   =   0   'False
   Begin VB.CommandButton OKButton 
      Caption         =   "OK"
      Height          =   375
      Left            =   1560
      TabIndex        =   4
      Top             =   3960
      Width           =   1215
   End
   Begin MSComctlLib.ListView ListView1 
      Height          =   2295
      Left            =   240
      TabIndex        =   2
      Top             =   1440
      Width           =   3855
      _ExtentX        =   6800
      _ExtentY        =   4048
      View            =   3
      LabelEdit       =   1
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
   Begin VB.CommandButton NoButton 
      Caption         =   "No"
      Height          =   375
      Left            =   2280
      TabIndex        =   1
      Top             =   3960
      Width           =   1215
   End
   Begin VB.CommandButton YesButton 
      Caption         =   "Yes"
      Height          =   375
      Left            =   840
      TabIndex        =   0
      Top             =   3960
      Width           =   1215
   End
   Begin VB.Label Label1 
      Alignment       =   2  'Center
      Caption         =   "you can set the message property of this form before it is shown to change the text that will be shown here"
      Height          =   1095
      Left            =   240
      TabIndex        =   3
      Top             =   120
      Width           =   3855
   End
End
Attribute VB_Name = "ListMessage"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Option Explicit
Public message As String
Public boxcaption As String
Public result As Boolean
Public style As VbMsgBoxStyle ' can be vbOKOnly or vbYesNo

Public Sub AddHeader(text As String)
    ListView1.ColumnHeaders.Add , , text
    Dim i As Integer
    For i = 1 To ListView1.ColumnHeaders.Count
        ListView1.ColumnHeaders(i).Width = (ListView1.Width - 80) / ListView1.ColumnHeaders.Count
    Next i
End Sub

Public Sub AddRow(text As String)
    ListView1.ListItems.Add , , text
End Sub

Public Sub AddRowSubText(text As String)
    ListView1.ListItems(ListView1.ListItems.Count).ListSubItems.Add , , text
End Sub

Private Sub CancelButton_Click()
    result = False
    Me.Hide
End Sub

Private Sub Form_Load()
    OKButton.Visible = (style = vbOKOnly)
    YesButton.Visible = (style = vbYesNo)
    NoButton.Visible = (style = vbYesNo)
    
    Label1.Caption = message
    Me.Caption = boxcaption
End Sub

Private Sub OKButton_Click()
    result = True
    Me.Hide
End Sub
