VERSION 5.00
Begin VB.Form PopupForm 
   AutoRedraw      =   -1  'True
   BackColor       =   &H80000018&
   BorderStyle     =   0  'None
   Caption         =   "Form1"
   ClientHeight    =   180
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   510
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   180
   ScaleWidth      =   510
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  'CenterOwner
   Begin VB.Timer Timer1 
      Enabled         =   0   'False
      Interval        =   2000
      Left            =   0
      Top             =   0
   End
End
Attribute VB_Name = "PopupForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Public messageText As String
Public gChart As GanttChart

Public Sub SetText(newText As String)
    If (messageText <> newText) Then
        messageText = newText
        Width = TextWidth(messageText) + 200
        Height = TextHeight(messageText) + 80
        Redraw
    End If
End Sub

Public Sub Redraw()
    FillColor = vbInfoBackground
    FillStyle = vbFSSolid
    Line (0, 0)-(ScaleWidth - 10, ScaleHeight - 20), , B
    CurrentX = 100
    CurrentY = 40
    Print messageText
End Sub

Private Sub Form_Load()
Timer1.Enabled = True
End Sub

Private Sub Timer1_Timer()
Unload Me
gChart.IsPopupVisible = False
End Sub
