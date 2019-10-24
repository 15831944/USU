VERSION 5.00
Object = "{8A82C331-DBEA-11D0-8F12-444553540000}#1.0#0"; "ACTIVED3D.OCX"
Begin VB.Form ComponentDiagram 
   Caption         =   "Component Diagram"
   ClientHeight    =   4200
   ClientLeft      =   2775
   ClientTop       =   3765
   ClientWidth     =   4200
   Icon            =   "ComponentDiagram.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4200
   ScaleWidth      =   4200
   Begin ACTIVED3DLib.ActiveD3D ActiveD3D1 
      Height          =   3615
      Left            =   480
      TabIndex        =   0
      Top             =   600
      Width           =   3735
      _Version        =   65536
      _ExtentX        =   6588
      _ExtentY        =   6376
      _StockProps     =   0
   End
   Begin VB.Image Image1 
      BorderStyle     =   1  'Fixed Single
      Height          =   4200
      Left            =   0
      Stretch         =   -1  'True
      Top             =   0
      Width           =   4200
   End
End
Attribute VB_Name = "ComponentDiagram"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Option Explicit
Public pictureName
Private imageObj As IPictureDisp
'Function: Form_Load
'Purpose: insert image on form

Private Sub ActiveD3D1_SceneLoaded()
    ActiveD3D1.SetFileName pidDirectory & Left(pictureName, Len(pictureName) - 3) & "x"
    Select Case pictureName
    
        Case "ISS2.bmp"
            ActiveD3D1.SetPosition -2.61692, 1.08432, -2.48835
            ActiveD3D1.SetOrientation 0.737739, -0.19509, 0.646282, 0.146745, 0.980785, 0.12853
        
        Case "fan.bmp"
            ActiveD3D1.SetPosition 13.1086, 5.87673, -22.1671
ActiveD3D1.SetOrientation -0.395169, -0.290284, 0.871537, -0.119873, 0.95694, 0.264372
    End Select
        ActiveD3D1.SetObjRotation "scene", 0#, 1#, 0#, 0.02

End Sub

Private Sub Form_Load()
    
    If pictureName <> "(none)" And pictureName <> "" Then
        Set imageObj = LoadPicture(pidDirectory & pictureName)
        Height = Me.ScaleY(imageObj.Height, vbHimetric, vbTwips) + 405
        Width = Me.ScaleX(imageObj.Width, vbHimetric, vbTwips) + 120
        Image1.Height = Me.ScaleY(imageObj.Height + ActiveD3D1.Height, vbHimetric, vbTwips)
        Image1.Width = Me.ScaleX(imageObj.Width + ActiveD3D1.Width, vbHimetric, vbTwips)
        Set Image1.Picture = imageObj
        
    End If
End Sub

'Function/Subroutine:OKButton_Click
'Purpose: remove the form
Private Sub OKButton_Click()
    Unload Me
    
End Sub
'Function: Form_Resize
'Purpose: resize the form while keeping the correct ratio of
'picture (also resize picture)
Private Sub Form_Resize()
    If (Height > 450 And Width > 165) Then
        Image1.Height = Height - 405
        Image1.Width = Width - 120
    End If
End Sub

