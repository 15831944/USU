VERSION 5.00
Begin VB.Form MappingHelp 
   Caption         =   "Mapping Help"
   ClientHeight    =   9915
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   12120
   LinkTopic       =   "Form1"
   ScaleHeight     =   9915
   ScaleWidth      =   12120
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Close 
      Caption         =   "Close"
      Height          =   495
      Left            =   10680
      TabIndex        =   12
      Top             =   9240
      Width           =   1215
   End
   Begin VB.CommandButton BuildByHandBtn 
      Caption         =   "  Build By Hand Using Fault Tree"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   615
      Left            =   7320
      TabIndex        =   4
      Top             =   6480
      Width           =   1815
   End
   Begin VB.ListBox CompTypeMethod 
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   3420
      Left            =   4920
      TabIndex        =   3
      Top             =   2880
      Width           =   1575
   End
   Begin VB.ListBox CompIDMethod 
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   3420
      Left            =   7800
      TabIndex        =   2
      Top             =   2880
      Width           =   1455
   End
   Begin VB.ListBox FailModeMethod 
      BackColor       =   &H80000011&
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   3420
      Left            =   6480
      TabIndex        =   1
      Top             =   2880
      Width           =   1335
   End
   Begin VB.ListBox SystemMethod 
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   3420
      Left            =   3840
      TabIndex        =   0
      Top             =   2880
      Width           =   1095
   End
   Begin VB.Label BENamingLbl 
      Caption         =   "Basic Event Naming system"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   615
      Left            =   2280
      TabIndex        =   11
      Top             =   3000
      Width           =   1575
   End
   Begin VB.Label BaseCompLbl 
      BackColor       =   &H80000018&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "Base Component"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   4920
      TabIndex        =   10
      Top             =   2160
      Width           =   4335
   End
   Begin VB.Label GroupLbl 
      BackColor       =   &H80000018&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "Group"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   3840
      TabIndex        =   9
      Top             =   2160
      Width           =   1095
   End
   Begin VB.Label CompIDLbl 
      BorderStyle     =   1  'Fixed Single
      Caption         =   "Component ID"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   7800
      TabIndex        =   8
      Top             =   2520
      Width           =   1455
   End
   Begin VB.Label FailModeLbl 
      BackColor       =   &H80000011&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "Fail Mode"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   6480
      TabIndex        =   7
      Top             =   2520
      Width           =   1335
   End
   Begin VB.Label CompTypeLbl 
      BorderStyle     =   1  'Fixed Single
      Caption         =   "Component Type"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   4920
      TabIndex        =   6
      Top             =   2520
      Width           =   1575
   End
   Begin VB.Label SystemLbl 
      BorderStyle     =   1  'Fixed Single
      Caption         =   "System"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   3840
      TabIndex        =   5
      Top             =   2520
      Width           =   1095
   End
End
Attribute VB_Name = "MappingHelp"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
