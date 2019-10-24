VERSION 5.00
Begin VB.Form ComponentList 
   Caption         =   "Component List"
   ClientHeight    =   5265
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   5430
   ControlBox      =   0   'False
   Icon            =   "ComponentList.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   5265
   ScaleWidth      =   5430
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton ok 
      Caption         =   "OK"
      Height          =   375
      Left            =   2040
      TabIndex        =   1
      Top             =   4680
      Width           =   1335
   End
   Begin VB.ListBox List1 
      Height          =   4155
      Left            =   240
      TabIndex        =   0
      Top             =   240
      Width           =   4935
   End
End
Attribute VB_Name = "ComponentList"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

'Function/Subroutine:List1_DblClick
'Purpose: display the component diagram
Private Sub List1_DblClick()
    ComponentDiagram.Show 1
End Sub
'Function/Subroutine:ok_Click
'Purpose: unload form
Private Sub ok_Click()
    Unload Me
End Sub
