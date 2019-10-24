VERSION 5.00
Begin VB.Form AddNode 
   Caption         =   "Edit or ADD"
   ClientHeight    =   2910
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4110
   BeginProperty Font 
      Name            =   "Arial"
      Size            =   9.75
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   LinkTopic       =   "Form2"
   ScaleHeight     =   2910
   ScaleWidth      =   4110
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox DescTxtB 
      Height          =   360
      Left            =   360
      TabIndex        =   4
      Text            =   "Text1"
      Top             =   1560
      Width           =   3615
   End
   Begin VB.CommandButton ADDbtn 
      Caption         =   "OK"
      Height          =   615
      Left            =   2040
      TabIndex        =   3
      Top             =   2160
      Width           =   1335
   End
   Begin VB.CommandButton CancelBtn 
      Caption         =   "Cancel"
      Height          =   615
      Left            =   360
      TabIndex        =   2
      Top             =   2160
      Width           =   1335
   End
   Begin VB.TextBox NameTxtB 
      Height          =   360
      Left            =   360
      TabIndex        =   0
      Text            =   "Text1"
      Top             =   840
      Width           =   3615
   End
   Begin VB.Label NameEditing 
      Caption         =   "Label2"
      Height          =   255
      Left            =   360
      TabIndex        =   6
      Top             =   120
      Width           =   3015
   End
   Begin VB.Label DescTxt 
      Caption         =   "Enter Description"
      Height          =   255
      Left            =   360
      TabIndex        =   5
      Top             =   1320
      Width           =   2415
   End
   Begin VB.Label Label1 
      Caption         =   "Enter the Name"
      Height          =   255
      Left            =   360
      TabIndex        =   1
      Top             =   600
      Width           =   3015
   End
End
Attribute VB_Name = "AddNode"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'Public YNCancel As Boolean
Public EditingName As String
Public NewName As String
Public NewDisc As String


Private Sub ADDbtn_Click()
    EditMapping.AddNodeName = NameTxtB.Text
    EditMapping.AddNodeDesc = DescTxtB.Text
    
    
    
    
    EditMapping.AddNodeSuc = True
    
    Me.Hide
End Sub

Private Sub CancelBtn_Click()
    EditMapping.AddNodeSuc = False
    Me.Hide
End Sub

Private Sub Form_Load()
    
    NameEditing.Caption = EditMapping.AddNodeName
    If Not EditMapping.editName Then
        NameTxtB.Text = EditMapping.AddNodeName
        NameTxtB.Enabled = False
    Else
        NameTxtB.Text = EditMapping.AddNodeName
        
        
        
    End If
    DescTxtB.Text = EditMapping.AddNodeDesc
    EditMapping.AddNodeSuc = False
    
    
    
End Sub
