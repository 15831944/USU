VERSION 5.00
Begin VB.Form PasswordCheck 
   Caption         =   "Form1"
   ClientHeight    =   2625
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4305
   LinkTopic       =   "Form1"
   ScaleHeight     =   2625
   ScaleWidth      =   4305
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton OK 
      Caption         =   "OK"
      Height          =   615
      Left            =   2400
      TabIndex        =   4
      Top             =   1800
      Width           =   1455
   End
   Begin VB.CommandButton Cancel 
      Caption         =   "Cancel"
      Height          =   615
      Left            =   480
      TabIndex        =   3
      Top             =   1800
      Width           =   1335
   End
   Begin VB.TextBox Password 
      Height          =   375
      Left            =   1320
      TabIndex        =   2
      Top             =   840
      Width           =   2535
   End
   Begin VB.Label PasswordTxt 
      Caption         =   "Password"
      Height          =   255
      Left            =   120
      TabIndex        =   1
      Top             =   960
      Width           =   975
   End
   Begin VB.Label userNameTxt 
      Alignment       =   2  'Center
      Caption         =   "Label1"
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
      Left            =   240
      TabIndex        =   0
      Top             =   120
      Width           =   3615
   End
End
Attribute VB_Name = "PasswordCheck"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private mySQLStatement As String
Private myUserName As String
Private myPassword As String
Private rarray As Variant



Private Sub Cancel_Click()
    Unload Me
End Sub

Private Sub Form_Load()
    
    Dim resultSet As rdoResultset
    mySQLStatement = "SELECT User.UserName, User.UserPassword, User.UserType FROM User Where UserID = " & userID
    Set resultSet = dbConnection.OpenResultset(mySQLStatement)
    If resultSet.EOF Then
        MsgBox "User Name not found", vbInformation
        myUserName = ""
    Else
        rarray = resultSet.GetRows(1)
        myUserName = rarray(0, 0)
        myPassword = rarray(1, 0)
    End If
        userNameTxt.Caption = myUserName
End Sub

Public Sub epChange()
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
            mySQLStatement = "UPDATE [User] SET UserName = '" & newUserName & "', UserPassword = '" & newPassword & "', RealName =  ' " & newRealName & " ', UserType = '" & newIsAdmin & "'  WHERE UserID = " & EditUserID
            Set resultSet = dbConnection.OpenResultset(mySQLStatement)
            
        Else
            mySQLStatement = "UPDATE [User] SET UserName = '" & newUserName & "', UserPassword = '" & newPassword & "', RealName = '" & newRealName & "' WHERE UserID = " & EditUserID
            Set resultSet = dbConnection.OpenResultset(mySQLStatement)
        End If
        Unload Me
    Else 'the password did not match or there was no pasword given
        MsgBox "The Passwords do not match", vbInformation
    End If
    
    
End Sub
        


Private Sub ok_Click()
    
    If myPassword <> Password.text Then
        MsgBox "Password incorrect", vbInformation
    Else
        If rarray(2, 0) = "A" Then
            AdminEditProfiles.Show
            Unload Me
        Else
            Dim eFrm As EditProfile
            Set eFrm = New EditProfile
            eFrm.EditUserID = userID
            eFrm.Show
            Unload Me
        End If
    End If
End Sub

Private Sub Password_KeyPress(KeyAscii As Integer)
    If KeyAscii = 13 Then
        ok_Click
    End If
End Sub
