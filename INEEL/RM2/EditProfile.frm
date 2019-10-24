VERSION 5.00
Begin VB.Form EditProfile 
   Caption         =   "Edit Profile"
   ClientHeight    =   4020
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   6090
   LinkTopic       =   "Edit Profile"
   ScaleHeight     =   4020
   ScaleWidth      =   6090
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Cancel 
      Caption         =   "Cancel"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   615
      Left            =   360
      TabIndex        =   11
      Top             =   3240
      Width           =   2055
   End
   Begin VB.CommandButton Change 
      Caption         =   "Change"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   615
      Left            =   3120
      TabIndex        =   2
      Top             =   3240
      Width           =   2295
   End
   Begin VB.TextBox RealName 
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   2400
      TabIndex        =   4
      Text            =   "Text4"
      Top             =   2040
      Width           =   3135
   End
   Begin VB.TextBox RePassword 
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      IMEMode         =   3  'DISABLE
      Left            =   2400
      PasswordChar    =   "*"
      TabIndex        =   1
      Text            =   "Text3"
      Top             =   1440
      Width           =   3135
   End
   Begin VB.TextBox Password 
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      IMEMode         =   3  'DISABLE
      Left            =   2400
      PasswordChar    =   "*"
      TabIndex        =   0
      Text            =   "Text2"
      Top             =   840
      Width           =   3135
   End
   Begin VB.TextBox UserName 
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   2400
      TabIndex        =   3
      Text            =   "Text1"
      Top             =   240
      Width           =   3135
   End
   Begin VB.CheckBox AdminCheck 
      Caption         =   "Check1"
      Height          =   255
      Left            =   240
      TabIndex        =   5
      Top             =   2640
      Width           =   255
   End
   Begin VB.Label MakeAdminLB 
      Caption         =   "Make User Administrator"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   840
      TabIndex        =   10
      Top             =   2640
      Width           =   2775
   End
   Begin VB.Label RealNameLB 
      Caption         =   "Users' Actual Name"
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
      Left            =   240
      TabIndex        =   9
      Top             =   2040
      Width           =   2295
   End
   Begin VB.Label ReTypePasLB 
      Caption         =   "Re-Type Password"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   240
      TabIndex        =   8
      Top             =   1440
      Width           =   2175
   End
   Begin VB.Label PassWorkLB 
      Caption         =   "Password"
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
      Left            =   240
      TabIndex        =   7
      Top             =   840
      Width           =   1215
   End
   Begin VB.Label UserNameLB 
      Caption         =   "User Name"
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
      Left            =   240
      TabIndex        =   6
      Top             =   240
      Width           =   1335
   End
End
Attribute VB_Name = "EditProfile"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Public EditUserID As Integer
Public rarray As Variant
Private mySQLstatement As String


Private Sub Cancel_Click()
    Unload Me
End Sub

Private Sub Change_Click()
    Dim newUserName As String
    Dim newPassword As String
    Dim newRealName As String
    Dim newIsAdmin As String
    
    newUserName = UserName.text
    newPassword = Password.text
    newRealName = RealName.text
    If Password.text = RePassword.text And Password.text <> "" Then
    
        If UserType = Administrator Then
            If AdminCheck.Value = 1 Then
                newIsAdmin = "A"
            Else
                newIsAdmin = "U"
            End If
            mySQLstatement = "UPDATE [User] SET UserName = '" & newUserName & "', UserPassword = '" & newPassword & "', RealName =  ' " & newRealName & " ', UserType = '" & newIsAdmin & "'  WHERE UserID = " & EditUserID
            Set resultSet = dbConnection.OpenResultset(mySQLstatement)
            
        Else
            mySQLstatement = "UPDATE [User] SET UserName = '" & newUserName & "', UserPassword = '" & newPassword & "', RealName = '" & newRealName & "' WHERE UserID = " & EditUserID
            Set resultSet = dbConnection.OpenResultset(mySQLstatement)
        End If
        Unload Me
    Else 'the password did not match or there was no pasword given
        MsgBox "The Passwords do not match", vbInformation
    End If
    
    
End Sub

Private Sub Form_Load()
    Dim resultSet As rdoResultset
    If UserType = Administrator Then
        MakeAdminLB.Visible = True
        AdminCheck.Visible = True
        UserName.Enabled = True
        RealName.Enabled = True
    Else
        MakeAdminLB.Visible = False
        AdminCheck.Visible = False
        UserName.Enabled = False
        RealName.Enabled = False
        
    End If
          
    
    mySQLstatement = "SELECT User.UserName, User.UserPassword, User.RealName, User.UserType FROM User where UserID = " & EditUserID
    Set resultSet = dbConnection.OpenResultset(mySQLstatement)
    If resultSet.EOF Then
        MsgBox "No user information existed", vbInformation
    Else
        rarray = resultSet.GetRows(1)
        UserName.text = rarray(0, 0)
        Password.text = rarray(1, 0)
        RePassword.text = rarray(1, 0)
        If rarray(3, 0) = "A" Then
            AdminCheck.Value = 1
        Else
            AdminCheck.Value = 0
        End If
        If IsNull(rarray(2, 0)) Then
            RealName.text = ""
        Else
            RealName.text = rarray(2, 0)
        End If
    End If
    
End Sub

Private Sub UserName_KeyPress(KeyAscii As Integer)
    If KeyAscii = 13 Then
        Password.SetFocus
    End If
End Sub

Private Sub Password_KeyPress(KeyAscii As Integer)
    If KeyAscii = 13 Then
        RePassword.SetFocus
        RePassword_Click
    End If
End Sub

Private Sub RePassword_KeyPress(KeyAscii As Integer)
    If KeyAscii = 13 Then
        Change_Click
    End If
End Sub

Private Sub RePassword_Click()
    RePassword.SelStart = 0
    RePassword.SelLength = Len(RePassword)
End Sub
Private Sub Password_Click()
    Password.SelStart = 0
    Password.SelLength = Len(RePassword)
End Sub
