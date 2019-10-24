VERSION 5.00
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

Private Sub Form_Load()
    
    If pictureName <> "(none)" And pictureName <> "" Then
        Set imageObj = LoadPicture(pidDirectory & pictureName)
        Height = Me.ScaleY(imageObj.Height, vbHimetric, vbTwips) + 405
        Width = Me.ScaleX(imageObj.Width, vbHimetric, vbTwips) + 120
        Image1.Height = Me.ScaleY(imageObj.Height, vbHimetric, vbTwips)
        Image1.Width = Me.ScaleX(imageObj.Width, vbHimetric, vbTwips)
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
