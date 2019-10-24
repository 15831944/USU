VERSION 5.00
Begin VB.Form frmNewProc 
   Caption         =   "Create Prodecure"
   ClientHeight    =   2685
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   6075
   ControlBox      =   0   'False
   BeginProperty Font 
      Name            =   "Arial"
      Size            =   9.75
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   Icon            =   "frmNewProc.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   2685
   ScaleWidth      =   6075
   StartUpPosition =   1  'CenterOwner
   Begin VB.TextBox Text2 
      Height          =   375
      Left            =   360
      TabIndex        =   1
      Top             =   1440
      Width           =   5295
   End
   Begin VB.TextBox Text1 
      Height          =   375
      Left            =   360
      TabIndex        =   0
      Top             =   600
      Width           =   3735
   End
   Begin VB.CommandButton ok 
      Caption         =   "Next ->"
      Height          =   375
      Left            =   3120
      TabIndex        =   2
      Top             =   2040
      Width           =   2055
   End
   Begin VB.CommandButton cancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   375
      Left            =   720
      TabIndex        =   3
      Top             =   2040
      Width           =   2055
   End
   Begin VB.Label Label3 
      Caption         =   "Enter Procedure Description (50 Char max):"
      Height          =   375
      Left            =   360
      TabIndex        =   5
      Top             =   1080
      Width           =   5295
   End
   Begin VB.Label Label2 
      Caption         =   "Enter Procedure Name (25 Char max):"
      Height          =   375
      Left            =   360
      TabIndex        =   4
      Top             =   240
      Width           =   5295
   End
End
Attribute VB_Name = "frmNewProc"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Public Result As Boolean
Public ProcedureName As String

'Function/Subroutine:cancel_Click
'Purpose:handel cancel event
Private Sub Cancel_Click()
    Result = False
    Me.Hide
End Sub

'Function: next_Click
'Purpose: Creates a new procedure in the database and adds selected components.
'If no components selected from list non are added. (Can be modified later.)
Private Sub OK_Click()
    Dim mySQLStatement As String, resultset As rdoResultset
   
    'check for valid input
    If Text1 = "" Or Len(Text1) > NameMaxFieldLength Then
        MsgBox "Invalid Procedure Name", vbInformation
        Exit Sub
    End If
    
    If Text2 = "" Or Len(Text2) > NameMaxFieldLength Then
        MsgBox "Invalid Procedure Description", vbInformation
        Me.Show 1
        Exit Sub
    End If
    
    'Check to see if proc name already exists
    mySQLStatement = "SELECT ProcedureName FROM [Procedure] WHERE ProcedureName = '" & Text1.text & "'"
    Set resultset = dbConnection.OpenResultset(mySQLStatement)
       
    If Not resultset.EOF Then
        MsgBox "Procedure name already in use.", vbInformation
        Exit Sub
    End If
    
    ProcedureName = Text1.text
    
    'Create New Procedure In Database
    mySQLStatement = "INSERT INTO [Procedure] (ProcedureName, ProcedureDesc) VALUES ( '" & Text1 & "', '" & Text2 & "')"
    dbConnection.Execute (mySQLStatement)
    Result = True
    Me.Hide
    
End Sub
'Function/Subroutine:Text1_KeyPress
'Purpose: set focus
Private Sub Text1_KeyPress(KeyAscii As Integer)
    If KeyAscii = 13 Then
        Text2.SetFocus
    End If

End Sub
'Function/Subroutine:Text2_KeyPress
'Purpose:set focus
Private Sub Text2_KeyPress(KeyAscii As Integer)
    If KeyAscii = 13 Then
        OK_Click
    End If

End Sub
