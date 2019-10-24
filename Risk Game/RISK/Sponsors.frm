VERSION 5.00
Begin VB.Form Sponsors 
   Caption         =   "Special Thanks Our Contest Sponsors!"
   ClientHeight    =   5925
   ClientLeft      =   60
   ClientTop       =   405
   ClientWidth     =   7005
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   Picture         =   "Sponsors.frx":0000
   ScaleHeight     =   5925
   ScaleWidth      =   7005
   StartUpPosition =   3  'Windows Default
   Begin VB.Timer KillMe 
      Interval        =   2000
      Left            =   6480
      Top             =   120
   End
   Begin VB.Image Image1 
      Height          =   1830
      Left            =   0
      Picture         =   "Sponsors.frx":7FC5
      Top             =   4080
      Width           =   6990
   End
End
Attribute VB_Name = "Sponsors"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub KillMe_Timer()
    Unload Me
End Sub
