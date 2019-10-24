VERSION 5.00
Begin VB.Form Splash 
   BackColor       =   &H8000000A&
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Risk Monitor for SAPHIRE Version 1.0"
   ClientHeight    =   4635
   ClientLeft      =   2850
   ClientTop       =   3780
   ClientWidth     =   7440
   Icon            =   "Splash.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4635
   ScaleWidth      =   7440
   ShowInTaskbar   =   0   'False
   Begin VB.PictureBox picLogo 
      BackColor       =   &H80000009&
      BorderStyle     =   0  'None
      Height          =   2385
      Left            =   480
      Picture         =   "Splash.frx":0442
      ScaleHeight     =   2385
      ScaleWidth      =   2535
      TabIndex        =   5
      Top             =   600
      Width           =   2535
   End
   Begin VB.CommandButton CancelButton 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   5880
      TabIndex        =   1
      Top             =   4080
      Width           =   1215
   End
   Begin VB.CommandButton OKButton 
      Caption         =   "Login"
      Default         =   -1  'True
      Height          =   375
      Left            =   4560
      TabIndex        =   0
      Top             =   4080
      Width           =   1215
   End
   Begin VB.Label lblCopyright 
      BackStyle       =   0  'Transparent
      Caption         =   "Copyright 2001"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   3360
      TabIndex        =   7
      Tag             =   "Copyright"
      Top             =   2640
      Width           =   2415
   End
   Begin VB.Label lblCompany 
      BackStyle       =   0  'Transparent
      Caption         =   "Idaho National Environmental and Engineering Laboratory"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   615
      Left            =   3360
      TabIndex        =   6
      Tag             =   "Company"
      Top             =   3000
      Width           =   3495
   End
   Begin VB.Label lblVersion 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "Version 1.0"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   18
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   435
      Left            =   3360
      TabIndex        =   4
      Tag             =   "Version"
      Top             =   1800
      Width           =   1920
   End
   Begin VB.Label lblCompanyProduct 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "Risk Monitor for"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   18
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   435
      Left            =   3360
      TabIndex        =   3
      Tag             =   "CompanyProduct"
      Top             =   480
      Width           =   2790
   End
   Begin VB.Label lblProductName 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "SAPHIRE"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   29.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   675
      Left            =   3360
      TabIndex        =   2
      Tag             =   "Product"
      Top             =   960
      Width           =   3420
   End
   Begin VB.Shape Shape1 
      BackStyle       =   1  'Opaque
      Height          =   3615
      Left            =   240
      Top             =   240
      Width           =   6975
   End
End
Attribute VB_Name = "Splash"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Option Explicit
'Function/Subroutine:CancelButton_Click
'Purpose:handles the cancel click event
Private Sub CancelButton_Click()
    Unload Me
    End
End Sub

'Function/Subroutine:OKButton_Click
'Purpose:handles the ok button click event
Private Sub OKButton_Click()
    Unload Me
End Sub
