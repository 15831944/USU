VERSION 5.00
Object = "{8A82C331-DBEA-11D0-8F12-444553540000}#1.0#0"; "ACTIVED3D.OCX"
Begin VB.Form Model3D 
   Caption         =   "3D Models"
   ClientHeight    =   3195
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   LinkTopic       =   "Form1"
   ScaleHeight     =   3195
   ScaleWidth      =   4680
   StartUpPosition =   3  'Windows Default
   Begin ACTIVED3DLib.ActiveD3D ActiveD3D1 
      Height          =   2895
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   4335
      _Version        =   65536
      _ExtentX        =   7646
      _ExtentY        =   5106
      _StockProps     =   0
   End
End
Attribute VB_Name = "Model3D"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Public pictureName
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

