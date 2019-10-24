VERSION 5.00
Begin VB.Form frmLogin 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Login"
   ClientHeight    =   2790
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   3750
   Icon            =   "frmLogin.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2790
   ScaleWidth      =   3750
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Tag             =   "1047"
   Begin VB.ComboBox nameDriver 
      Height          =   315
      Left            =   600
      TabIndex        =   9
      TabStop         =   0   'False
      Text            =   "Combo1"
      Top             =   1920
      Visible         =   0   'False
      Width           =   3015
   End
   Begin VB.ComboBox cboDSNList 
      Height          =   315
      ItemData        =   "frmLogin.frx":0442
      Left            =   630
      List            =   "frmLogin.frx":0444
      Style           =   2  'Dropdown List
      TabIndex        =   6
      TabStop         =   0   'False
      Top             =   1560
      Width           =   3000
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   360
      Left            =   480
      TabIndex        =   4
      TabStop         =   0   'False
      Tag             =   "1051"
      Top             =   2280
      Width           =   1140
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   360
      Left            =   2160
      TabIndex        =   1
      Tag             =   "1050"
      Top             =   2280
      Width           =   1140
   End
   Begin VB.TextBox txtPassword 
      Height          =   285
      IMEMode         =   3  'DISABLE
      Left            =   1305
      PasswordChar    =   "*"
      TabIndex        =   0
      Top             =   525
      Width           =   2325
   End
   Begin VB.TextBox txtUserName 
      Height          =   285
      Left            =   1305
      TabIndex        =   2
      Top             =   135
      Width           =   2325
   End
   Begin VB.Label Label1 
      Caption         =   "Select Risk Monitor Database"
      Height          =   255
      Left            =   120
      TabIndex        =   8
      Top             =   1200
      Width           =   3015
   End
   Begin VB.Label lblStep3 
      AutoSize        =   -1  'True
      Caption         =   "&DSN:"
      Height          =   195
      Index           =   1
      Left            =   120
      TabIndex        =   7
      Top             =   1560
      Width           =   390
   End
   Begin VB.Label lblLabels 
      Caption         =   "&Password:"
      Height          =   248
      Index           =   1
      Left            =   105
      TabIndex        =   3
      Tag             =   "1049"
      Top             =   540
      Width           =   1080
   End
   Begin VB.Label lblLabels 
      Caption         =   "&User Name:"
      Height          =   248
      Index           =   0
      Left            =   105
      TabIndex        =   5
      Tag             =   "1048"
      Top             =   150
      Width           =   1080
   End
End
Attribute VB_Name = "frmLogin"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Private Declare Function GetUserName Lib "advapi32.dll" Alias "GetUserNameA" (ByVal lpBuffer As String, nSize As Long) As Long
'Public dbConnection As rdoConnection

'functions for generation list of existing databases
Private Declare Function SQLDataSources Lib "ODBC32.DLL" (ByVal henv&, ByVal fDirection%, ByVal szDSN$, ByVal cbDSNMax%, pcbDSN%, ByVal szDescription$, ByVal cbDescriptionMax%, pcbDescription%) As Integer
Private Declare Function SQLAllocEnv% Lib "ODBC32.DLL" (env&)
Const SQL_SUCCESS As Long = 0
Const SQL_FETCH_NEXT As Long = 1
Public sDSN As String


Public OK As Boolean
'Function/Subroutine:Form_Load
'Purpose: set initial value in username text box
Private Sub Form_Load()
    Dim sBuffer As String
    Dim lSize As Long
    LoadResStrings Me
    sBuffer = Space$(255)
    lSize = Len(sBuffer)
    Call GetUserName(sBuffer, lSize)
    If lSize > 0 Then
        txtUserName.text = Left$(sBuffer, lSize)
    Else
        txtUserName.text = vbNullString
    End If
    
    GetDSNsAndDrivers
End Sub

'Function/Subroutine:cmdCancel_Click
'Purpose:cancel the login - returns to splash screen
Private Sub cmdCancel_Click()
    OK = False
    Me.Hide
End Sub

'Function/Subroutine:cmdOK_Click
'Purpose:Get information from database - if login correct procede else reshow
'this form with error message
Private Sub cmdOK_Click()
   
    Dim resultSet As rdoResultset
    Dim mySQLStatement As String
    Dim connection As Boolean
    Dim tempInt As Integer
    
    'Connect to the Database
    connection = Module1.DBConnect(cboDSNList.text)
    tempInt = cboDSNList.ListIndex
    nameDriver.ListIndex = tempInt
    'Get the type of driver for database (access or sql)
    Module1.connectionType = nameDriver.text
    
    If connection = True Then
    
       mySQLStatement = "SELECT UserID, UserType FROM [User] WHERE UserName = '" & txtUserName.text & "' AND UserPassword = '" & txtPassword.text & "'"
        
        'On Error GoTo checkError
        Set resultSet = dbConnection.OpenResultset(mySQLStatement)
        ' Run time error 40071 will be generated if no connection is present by this statement
        
        
        If (resultSet.EOF) Then
            MsgBox "Invalid Username or Password", , "Login"
            txtPassword.SetFocus
            txtPassword.SelStart = 0
            txtPassword.SelLength = Len(txtPassword.text)
        Else
            Dim rArray As Variant
            rArray = resultSet.GetRows(1)
            userID = rArray(0, 0) ' first subscript is which column, second is which row
            If rArray(1, 0) = "A" Then
                UserType = Administrator
            Else
                UserType = NormalUser
            End If
            'MDIMain.SetUserID userID
            OK = True
            Me.Hide
        End If
    Else
checkError:
        MsgBox "Invalid Database", , "Login"
    End If
    
   
End Sub
'Function/Subroutine:txtPassword_KeyPress
'Purpose: sets the focus once enter has been pressed
Private Sub txtPassword_KeyPress(KeyAscii As Integer)
    If KeyAscii = 13 Then
        cmdOK.SetFocus
    End If
End Sub
'Function/Subroutine:txtUserName_KeyPress
'Purpose:sets the focus once enter has been pressed
Private Sub txtUserName_KeyPress(KeyAscii As Integer)
    If KeyAscii = 13 Then
        txtPassword.SetFocus
    End If
End Sub

Sub GetDSNsAndDrivers()
    Dim i As Integer
    Dim sDSNItem As String * 1024
    Dim sDRVItem As String * 1024
    Dim sDSN As String
    Dim sDRV As String
    Dim iDSNLen As Integer
    Dim iDRVLen As Integer
    Dim lHenv As Long         'handle to the environment

    On Error Resume Next

    'get the DSNs - insert into combo boxes
    If SQLAllocEnv(lHenv) <> -1 Then
        Dim j As Integer
        j = 1
        Do Until i <> SQL_SUCCESS
            'code to recieve stuff from odbc administrator
            sDSNItem = Space$(1024)
            sDRVItem = Space$(1024)
            i = SQLDataSources(lHenv, SQL_FETCH_NEXT, sDSNItem, 1024, iDSNLen, sDRVItem, 1024, iDRVLen)
            sDSN = Left$(sDSNItem, iDSNLen)
            sDRV = Left$(sDRVItem, iDRVLen)
                
            If sDSN <> Space(iDSNLen) Then
                cboDSNList.AddItem sDSN
               nameDriver.AddItem sDRV
            End If
            
            j = j + 1
        Loop
    End If

    cboDSNList.text = Module1.databaseName
End Sub
