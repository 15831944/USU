VERSION 5.00
Begin VB.Form CompList 
   Caption         =   "Component List"
   ClientHeight    =   5205
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   7440
   ControlBox      =   0   'False
   Icon            =   "CompList.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   5205
   ScaleWidth      =   7440
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton cancel 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   1800
      TabIndex        =   2
      Top             =   4680
      Width           =   1575
   End
   Begin VB.CommandButton ok 
      Caption         =   "OK"
      Height          =   375
      Left            =   4200
      TabIndex        =   1
      Top             =   4680
      Width           =   1575
   End
   Begin VB.ListBox List1 
      Height          =   3960
      Left            =   240
      TabIndex        =   0
      Top             =   360
      Width           =   7095
   End
   Begin VB.Label Label1 
      Caption         =   "Select Component:"
      Height          =   375
      Left            =   360
      TabIndex        =   3
      Top             =   120
      Width           =   2775
   End
End
Attribute VB_Name = "CompList"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Public CancelClick As Boolean
Public CompString As String
Public compID As Integer
Dim rArray As Variant
Dim RowReturn As Integer

'Function for adding columns to a list box
Private Declare Function SendMessageArray Lib "user32" Alias "SendMessageA" _
  (ByVal hwnd As Long, ByVal wMsg As Long, _
  ByVal wParam As Long, lParam As Any) As Long

'Function/Subroutine:cancel_Click
'Purpose:set cancel variable and unload form
Private Sub cancel_Click()
    CancelClick = True
    Unload Me
End Sub
'Function/Subroutine:Form_Load
'Purpose:Initialize variables and add components to list
Private Sub Form_Load()
    Dim mySQLStatement As String
    Dim resultSet As rdoResultset
    Dim i, j As Integer
    
    
    ''''Code to create list box columns
    'ReDim LBTab(1 To 3) As Long
    'LBTab(1) = 100
    'LBTab(2) = 100
    'LBTab(3) = 100
    'Const LB_SETTABSTOPS = &H192
     'SendMessageArray List1.hwnd, LB_SETTABSTOPS, 3, LBTab(1)
    'List1.AddItem "Item" & vbTab & "Item 2" & vbTab & "Item 3"

    CancelClick = False
    
    RowReturn = 0

    'Get list of components
    mySQLStatement = "SELECT Component.ComponentID, Component.ComponentName From [Component]"
    Set resultSet = dbConnection.OpenResultset(mySQLStatement, rdOpenKeyset)
    
    If resultSet.EOF Then
        MsgBox "No Components Found", vbInformation
        Unload Me
    End If
        
    While Not resultSet.EOF
        resultSet.MoveNext
        RowReturn = RowReturn + 1
    Wend
    
    resultSet.MoveFirst
    rArray = resultSet.GetRows(RowReturn)
        
    For i = 0 To RowReturn - 1
           List1.AddItem rArray(1, i)
    Next i
End Sub
'Function/Subroutine:ok_Click
'Purpose: determine selected component ID and hide form.
Private Sub ok_Click()
    Dim i As Integer
    'MsgBox Str(List1.ListIndex)

    If List1.ListIndex = -1 Then
        MsgBox "No Component Selected", vbInformation
    Else
        CompString = List1.text
        For i = 0 To RowReturn - 1
            If StrComp(rArray(1, i), CompString) = 0 Then
                compID = rArray(0, i)
            End If
        Next i
            
        Me.Hide
    End If
    
End Sub

