VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form AdminEditProfiles 
   Caption         =   "Administrator Edit Profiles"
   ClientHeight    =   3270
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4890
   LinkTopic       =   "Form1"
   ScaleHeight     =   3270
   ScaleWidth      =   4890
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Cancel 
      Caption         =   "Cancel"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   360
      TabIndex        =   2
      Top             =   2640
      Width           =   1815
   End
   Begin VB.CommandButton EditNext 
      Caption         =   "Edit"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   2520
      TabIndex        =   1
      Top             =   2640
      Width           =   1815
   End
   Begin MSComctlLib.ListView Users 
      Height          =   2295
      Left            =   240
      TabIndex        =   0
      Top             =   120
      Width           =   4215
      _ExtentX        =   7435
      _ExtentY        =   4048
      View            =   3
      LabelWrap       =   -1  'True
      HideSelection   =   -1  'True
      _Version        =   393217
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      BorderStyle     =   1
      Appearance      =   1
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      NumItems        =   0
   End
End
Attribute VB_Name = "AdminEditProfiles"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private rarray As Variant
Public AdminUserSelect As Integer

Private Sub Cancel_Click()
    Unload Me
End Sub

Private Sub EditNext_Click()
    If Users.SelectedItem Is Nothing Then
        MsgBox "No Task Selected", vbInformation
        Exit Sub
    Else
        Dim eFrm As EditProfile
        Set eFrm = New EditProfile
        eFrm.EditUserID = Users.SelectedItem.tag
        eFrm.Show
    End If
End Sub

Private Sub Form_Load()
    Dim resultSet As rdoResultset
    Dim i As Integer
    Dim UserName As String, RealName As String
    
    Users.ListItems.Clear
    Users.ColumnHeaders.Add , , "User Name"
    Users.ColumnHeaders.Add , , "Actual Name"
    
    
    Users.ColumnHeaders(1).Width = (Users.Width - 80) * 2 / 5
    Users.ColumnHeaders(2).Width = (Users.Width - 80) * 3 / 5
    
    
    
    mySQLStatement = "SELECT  UserID, UserName, RealName From User;"
    Set resultSet = dbConnection.OpenResultset(mySQLStatement)
    Dim lItem As ListItem
    i = 0
    While Not resultSet.EOF
        rarray = resultSet.GetRows(1)
        If IsNull(rarray(1, i)) Then
            UserName = ""
        Else
            UserName = rarray(1, i)
        End If
        Set lItem = Users.ListItems.Add(, , UserName)
        If IsNull(rarray(2, i)) Then
            RealName = ""
        Else
            RealName = rarray(2, i)
        End If
        lItem.ListSubItems.Add , , RealName
        lItem.tag = rarray(0, i)
        i = i = 1
    Wend
End Sub

Private Sub Users_KeyPress(KeyAscii As Integer)
    If KeyAscii = 13 Then
        EditNext_Click
    End If
End Sub
