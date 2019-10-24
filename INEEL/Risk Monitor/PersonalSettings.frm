VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Object = "{BDC217C8-ED16-11CD-956C-0000C04E4C0A}#1.1#0"; "TABCTL32.OCX"
Begin VB.Form PersonalSettings 
   Caption         =   "Personal Settings"
   ClientHeight    =   5490
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   9210
   BeginProperty Font 
      Name            =   "Arial"
      Size            =   9.75
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   LinkTopic       =   "Form1"
   ScaleHeight     =   5490
   ScaleWidth      =   9210
   StartUpPosition =   3  'Windows Default
   Begin TabDlg.SSTab SSTab1 
      Height          =   4815
      Left            =   120
      TabIndex        =   2
      Top             =   240
      Width           =   9015
      _ExtentX        =   15901
      _ExtentY        =   8493
      _Version        =   393216
      Style           =   1
      Tabs            =   5
      Tab             =   1
      TabsPerRow      =   10
      TabHeight       =   520
      TabCaption(0)   =   "Calendar"
      TabPicture(0)   =   "PersonalSettings.frx":0000
      Tab(0).ControlEnabled=   0   'False
      Tab(0).Control(0)=   "ShowPeekRiskCB"
      Tab(0).Control(1)=   "ShowAvgRiskCB"
      Tab(0).Control(2)=   "RiskInicatorFrm"
      Tab(0).ControlCount=   3
      TabCaption(1)   =   "Colors"
      TabPicture(1)   =   "PersonalSettings.frx":001C
      Tab(1).ControlEnabled=   -1  'True
      Tab(1).Control(0)=   "DangerColorFrm"
      Tab(1).Control(0).Enabled=   0   'False
      Tab(1).Control(1)=   "SceduleBarColorFrm"
      Tab(1).Control(1).Enabled=   0   'False
      Tab(1).Control(2)=   "ColorSchemeFrm"
      Tab(1).Control(2).Enabled=   0   'False
      Tab(1).ControlCount=   3
      TabCaption(2)   =   "Scheduel Chart"
      TabPicture(2)   =   "PersonalSettings.frx":0038
      Tab(2).ControlEnabled=   0   'False
      Tab(2).Control(0)=   "PTCdispCB"
      Tab(2).Control(1)=   "ModeNameDispCB"
      Tab(2).Control(2)=   "ModeSetupFrm"
      Tab(2).ControlCount=   3
      TabCaption(3)   =   "General"
      TabPicture(3)   =   "PersonalSettings.frx":0054
      Tab(3).ControlEnabled=   0   'False
      Tab(3).Control(0)=   "DateStyleFrm"
      Tab(3).Control(1)=   "LanguageFrm"
      Tab(3).ControlCount=   2
      TabCaption(4)   =   "Identification"
      TabPicture(4)   =   "PersonalSettings.frx":0070
      Tab(4).ControlEnabled=   0   'False
      Tab(4).Control(0)=   "AdminCheck"
      Tab(4).Control(1)=   "UserName"
      Tab(4).Control(2)=   "Password"
      Tab(4).Control(3)=   "RePassword"
      Tab(4).Control(4)=   "RealName"
      Tab(4).Control(5)=   "UserNameLB"
      Tab(4).Control(6)=   "PassWorkLB"
      Tab(4).Control(7)=   "ReTypePasLB"
      Tab(4).Control(8)=   "RealNameLB"
      Tab(4).Control(9)=   "MakeAdminLB"
      Tab(4).ControlCount=   10
      Begin VB.CheckBox ShowPeekRiskCB 
         Caption         =   "Show Peak Risk"
         Height          =   255
         Left            =   -71520
         TabIndex        =   54
         Top             =   1680
         Width           =   3735
      End
      Begin VB.CheckBox ShowAvgRiskCB 
         Caption         =   "Show Average Risk"
         Height          =   255
         Left            =   -71520
         TabIndex        =   53
         Top             =   960
         Width           =   3255
      End
      Begin VB.Frame RiskInicatorFrm 
         Caption         =   "Risk Indicator"
         Height          =   3495
         Left            =   -74760
         TabIndex        =   50
         Top             =   600
         Width           =   2535
         Begin VB.OptionButton NumValOptB 
            Caption         =   "Numeric Values"
            Height          =   255
            Left            =   240
            TabIndex        =   52
            Top             =   1440
            Width           =   1695
         End
         Begin VB.OptionButton GaugeIndOptB 
            Caption         =   "Gauge Indicator"
            Height          =   375
            Left            =   240
            TabIndex        =   51
            Top             =   360
            Width           =   2055
         End
      End
      Begin VB.Frame ColorSchemeFrm 
         Caption         =   "Color Scheme"
         Height          =   3855
         Left            =   120
         TabIndex        =   37
         Top             =   480
         Width           =   2775
         Begin VB.CommandButton NewSchemeBtn 
            Caption         =   "New Scheme"
            Height          =   495
            Left            =   480
            TabIndex        =   49
            Top             =   2040
            Width           =   1695
         End
         Begin VB.CommandButton EditSchemeBtn 
            Caption         =   "Edit Scheme"
            Height          =   495
            Left            =   480
            TabIndex        =   48
            Top             =   1200
            Width           =   1695
         End
         Begin VB.ComboBox SchemeNameCB 
            Height          =   360
            Left            =   240
            Style           =   2  'Dropdown List
            TabIndex        =   47
            Top             =   360
            Width           =   2175
         End
      End
      Begin VB.Frame SceduleBarColorFrm 
         Caption         =   "Schedule Bar Colors"
         Height          =   3855
         Left            =   6000
         TabIndex        =   36
         Top             =   480
         Width           =   2895
         Begin VB.CommandButton ComponentColorComBt 
            Caption         =   "..."
            BeginProperty Font 
               Name            =   "MS Sans Serif"
               Size            =   13.5
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   375
            Left            =   2400
            TabIndex        =   43
            Top             =   1560
            Width           =   375
         End
         Begin VB.CommandButton ProcedureColorComBt 
            Caption         =   "..."
            BeginProperty Font 
               Name            =   "MS Sans Serif"
               Size            =   13.5
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   375
            Left            =   2400
            TabIndex        =   42
            Top             =   960
            Width           =   375
         End
         Begin VB.CommandButton TaskColorComBt 
            Caption         =   "..."
            BeginProperty Font 
               Name            =   "MS Sans Serif"
               Size            =   13.5
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   375
            Left            =   2400
            TabIndex        =   41
            Top             =   360
            Width           =   375
         End
         Begin VB.TextBox ComponentColorTB 
            Height          =   375
            Left            =   1680
            TabIndex        =   40
            Top             =   1560
            Width           =   615
         End
         Begin VB.TextBox ProcedureColorTB 
            Height          =   375
            Left            =   1680
            TabIndex        =   39
            Top             =   960
            Width           =   615
         End
         Begin VB.TextBox TaskColorTB 
            Height          =   375
            Left            =   1680
            TabIndex        =   38
            Top             =   360
            Width           =   615
         End
         Begin VB.Label ComponentColorLbl 
            Caption         =   "Component Color:"
            Height          =   375
            Left            =   120
            TabIndex        =   46
            Top             =   1680
            Width           =   1695
         End
         Begin VB.Label ProcedureColorLbl 
            Caption         =   "Procedure Color:"
            Height          =   375
            Left            =   120
            TabIndex        =   45
            Top             =   1080
            Width           =   1695
         End
         Begin VB.Label TaksColorLbl 
            Caption         =   "Task Color:"
            Height          =   375
            Left            =   120
            TabIndex        =   44
            Top             =   480
            Width           =   1695
         End
      End
      Begin VB.Frame DangerColorFrm 
         Caption         =   "Danger Colors"
         Height          =   3855
         Left            =   3000
         TabIndex        =   26
         Top             =   480
         Width           =   2895
         Begin VB.TextBox LowRiskTB 
            Height          =   375
            Left            =   1680
            TabIndex        =   32
            Top             =   360
            Width           =   615
         End
         Begin VB.TextBox MedRiskTB 
            Height          =   375
            Left            =   1680
            TabIndex        =   31
            Top             =   960
            Width           =   615
         End
         Begin VB.TextBox HighRiskTB 
            Height          =   375
            Left            =   1680
            TabIndex        =   30
            Top             =   1560
            Width           =   615
         End
         Begin VB.CommandButton LowRiskComBtn 
            Caption         =   "..."
            BeginProperty Font 
               Name            =   "MS Sans Serif"
               Size            =   13.5
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   375
            Left            =   2400
            TabIndex        =   29
            Top             =   360
            Width           =   375
         End
         Begin VB.CommandButton MediumRiskComBtn 
            Caption         =   "..."
            BeginProperty Font 
               Name            =   "MS Sans Serif"
               Size            =   13.5
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   375
            Left            =   2400
            TabIndex        =   28
            Top             =   960
            Width           =   375
         End
         Begin VB.CommandButton HighRiskComBtn 
            Caption         =   "..."
            BeginProperty Font 
               Name            =   "MS Sans Serif"
               Size            =   13.5
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   375
            Left            =   2400
            TabIndex        =   27
            Top             =   1560
            Width           =   375
         End
         Begin MSComDlg.CommonDialog ChooseColor 
            Left            =   120
            Top             =   2040
            _ExtentX        =   847
            _ExtentY        =   847
            _Version        =   393216
            CancelError     =   -1  'True
         End
         Begin VB.Label LowRiskLbl 
            Caption         =   "Low Risk Color:"
            Height          =   375
            Left            =   120
            TabIndex        =   35
            Top             =   480
            Width           =   1695
         End
         Begin VB.Label MediumRiskLbl 
            Caption         =   "Med Risk Color:"
            Height          =   375
            Left            =   120
            TabIndex        =   34
            Top             =   1080
            Width           =   1935
         End
         Begin VB.Label HighRiskLbl 
            Caption         =   "High Risk Color:"
            Height          =   375
            Left            =   120
            TabIndex        =   33
            Top             =   1680
            Width           =   1695
         End
      End
      Begin VB.CheckBox PTCdispCB 
         Caption         =   "Display procedure, task, component name"
         Height          =   255
         Left            =   -70920
         TabIndex        =   25
         Top             =   1680
         Width           =   4095
      End
      Begin VB.CheckBox ModeNameDispCB 
         Caption         =   "Display Mode Name on Chart"
         Height          =   255
         Left            =   -70920
         TabIndex        =   24
         Top             =   1080
         Width           =   3615
      End
      Begin VB.Frame ModeSetupFrm 
         Caption         =   "Mode Setup"
         Height          =   3975
         Left            =   -74760
         TabIndex        =   21
         Top             =   600
         Width           =   3495
         Begin VB.OptionButton modeAsBar 
            Caption         =   "Show mode as a bar"
            Height          =   255
            Left            =   240
            TabIndex        =   23
            Top             =   2280
            Width           =   2655
         End
         Begin VB.OptionButton modeAsBack 
            Caption         =   "Show mode as background"
            Height          =   255
            Left            =   240
            TabIndex        =   22
            Top             =   480
            Width           =   2895
         End
      End
      Begin VB.Frame DateStyleFrm 
         Caption         =   "Date Style"
         Height          =   2535
         Left            =   -74520
         TabIndex        =   16
         Top             =   600
         Width           =   3615
         Begin VB.OptionButton DateDMYslashes 
            Caption         =   "25/12/2001 dd/mm/yyyy"
            Height          =   255
            Left            =   120
            TabIndex        =   20
            Top             =   2040
            Width           =   2415
         End
         Begin VB.OptionButton DateDMYdots 
            Caption         =   "25.12.2001 dd.mm.yyyy"
            Height          =   255
            Left            =   120
            TabIndex        =   19
            Top             =   1440
            Width           =   2535
         End
         Begin VB.OptionButton DateMDYslashes 
            Caption         =   "12/25/2001  mm/dd/yyyy"
            Height          =   375
            Left            =   120
            TabIndex        =   18
            Top             =   840
            Width           =   2655
         End
         Begin VB.OptionButton DateTypedMonth 
            Caption         =   "25 Dec 2001"
            Height          =   255
            Left            =   120
            TabIndex        =   17
            Top             =   360
            Width           =   2775
         End
      End
      Begin VB.Frame LanguageFrm 
         Caption         =   "Language"
         Height          =   2175
         Left            =   -69120
         TabIndex        =   13
         Top             =   600
         Width           =   2655
         Begin VB.OptionButton Russianlang 
            Caption         =   "Russian"
            Height          =   255
            Left            =   120
            TabIndex        =   15
            Top             =   960
            Width           =   1095
         End
         Begin VB.OptionButton EnglishLang 
            Caption         =   "English"
            Height          =   255
            Left            =   120
            TabIndex        =   14
            Top             =   480
            Width           =   2175
         End
      End
      Begin VB.CheckBox AdminCheck 
         Caption         =   "Check1"
         Height          =   255
         Left            =   -74520
         TabIndex        =   7
         Top             =   3120
         Width           =   255
      End
      Begin VB.TextBox UserName 
         Height          =   375
         Left            =   -72360
         TabIndex        =   6
         Text            =   "Text1"
         Top             =   720
         Width           =   3135
      End
      Begin VB.TextBox Password 
         Height          =   375
         IMEMode         =   3  'DISABLE
         Left            =   -72360
         PasswordChar    =   "*"
         TabIndex        =   5
         Text            =   "Text2"
         Top             =   1320
         Width           =   3135
      End
      Begin VB.TextBox RePassword 
         Height          =   375
         IMEMode         =   3  'DISABLE
         Left            =   -72360
         PasswordChar    =   "*"
         TabIndex        =   4
         Text            =   "Text3"
         Top             =   1920
         Width           =   3135
      End
      Begin VB.TextBox RealName 
         Height          =   375
         Left            =   -72360
         TabIndex        =   3
         Text            =   "Text4"
         Top             =   2520
         Width           =   3135
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
         Left            =   -74520
         TabIndex        =   12
         Top             =   720
         Width           =   1335
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
         Left            =   -74520
         TabIndex        =   11
         Top             =   1320
         Width           =   1215
      End
      Begin VB.Label ReTypePasLB 
         Caption         =   "Re-Type Password"
         Height          =   255
         Left            =   -74520
         TabIndex        =   10
         Top             =   1920
         Width           =   2175
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
         Left            =   -74520
         TabIndex        =   9
         Top             =   2520
         Width           =   2295
      End
      Begin VB.Label MakeAdminLB 
         Caption         =   "Make User Administrator"
         Height          =   255
         Left            =   -73920
         TabIndex        =   8
         Top             =   3120
         Width           =   2775
      End
   End
   Begin VB.CommandButton Cancel 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   7920
      TabIndex        =   1
      Top             =   5040
      Width           =   1215
   End
   Begin VB.CommandButton OK 
      Caption         =   "OK"
      Height          =   375
      Left            =   6600
      TabIndex        =   0
      Top             =   5040
      Width           =   1215
   End
End
Attribute VB_Name = "PersonalSettings"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Public epEditUserID As Integer
Private rarray As Variant
Private PasswordsGood As Boolean
Public Colour As Long
Public danger As Long, caution As Long
Private mySQLStatement As String

Public rColour As Long
Public rDanger As Long, rCaution As Long, rOK As Long

Private Sub MultiPage1_Change()

End Sub

Private Sub TabStrip1_Change()

End Sub

Private Sub Cancel_Click()
    Select Case SSTab1.Tab
        Case 0
            Unload Me
        Case 1
            Unload Me
        Case 2
            Unload Me
        Case 3
            Unload Me
        Case 4
            
            'epCancel
            Unload Me
            
    End Select
End Sub

Private Sub Form_Load()
    MakeAdminLB.Visible = False
    AdminCheck.Visible = False
    PasswordsGood = False
    LoadScheduel
    LoadCalendar
    LoadGeneral
    BarColorLoad
    RiskColorLoad
    schemeLoad
    GeneralLoad
    epEditUserID = userID
    epLoad
        
    
    
End Sub

Private Sub ok_Click()
    epChange
    If PasswordsGood = True Then
        Unload Me
    End If
    
End Sub

Private Sub Option4_Click()

End Sub

Private Sub RePassword_Click()
    RePassword.SelStart = 0
    RePassword.SelLength = Len(RePassword)
End Sub
Private Sub Password_Click()
    Password.SelStart = 0
    Password.SelLength = Len(RePassword)
End Sub

Private Sub epChange()
    Dim newUserName As String
    Dim newPassword As String
    Dim newRealName As String
    Dim newIsAdmin As String
    Dim resultSet As rdoResultset
    
    newUserName = UserName.text
    newPassword = Password.text
    newRealName = RealName.text
    If Password.text = RePassword.text And Password.text <> "" Then
        PasswordsGood = True
        If UserType = Administrator Then
            If AdminCheck.Value = 1 Then
                newIsAdmin = "A"
            Else
                newIsAdmin = "U"
            End If
            mySQLStatement = "UPDATE [User] SET UserName = '" & newUserName & "', UserPassword = '" & newPassword & "', RealName =  ' " & newRealName & " ', UserType = '" & newIsAdmin & "'  WHERE UserID = " & userID
            Set resultSet = dbConnection.OpenResultset(mySQLStatement)
            
        Else
            mySQLStatement = "UPDATE [User] SET UserName = '" & newUserName & "', UserPassword = '" & newPassword & "', RealName = '" & newRealName & "' WHERE UserID = " & userID
            Set resultSet = dbConnection.OpenResultset(mySQLStatement)
        End If
        Unload Me
    Else 'the password did not match or there was no pasword given
        MsgBox "The Passwords do not match", vbInformation
    End If
    
    
End Sub


Private Sub epLoad()
    Dim resultSet As rdoResultset
    
    If UserType = Administrator Then
        
        UserName.Enabled = True
        RealName.Enabled = True
    Else
        UserName.Enabled = False
        RealName.Enabled = False
        
    End If
          
    
    mySQLStatement = "SELECT User.UserName, User.UserPassword, User.RealName, User.UserType FROM User where UserID = " & userID
    Set resultSet = dbConnection.OpenResultset(mySQLStatement)
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

Public Sub Password_KeyPress(KeyAscii As Integer)
    If KeyAscii = 13 Then
        RePassword.SetFocus
        RePassword_Click
    End If
End Sub

Private Sub RePassword_KeyPress(KeyAscii As Integer)
    If KeyAscii = 13 Then
        OK.SetFocus
    End If
End Sub

Private Sub GeneralLoad()
    EnglishLang.Enabled = False
    Russianlang.Enabled = False
    DateTypedMonth.Enabled = False
    DateMDYslashes.Enabled = False
    DateDMYdots.Enabled = False
    DateDMYslashes.Enabled = False
End Sub

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'schedule bar color code
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''



Private Sub TaskColorComBt_Click()
    Dim mySQL As String
    ChooseColor.Color = TaskColorTB.BackColor
    On Error GoTo CancelError
    
    ChooseColor.ShowColor
    TaskColorTB.BackColor = ChooseColor.Color
    Colour = ChooseColor.Color
    TaskColor = Colour

    mySQL = "UPDATE [UserPreferences] SET TaskColor = " & Colour & " WHERE UserID = " & userID
    dbConnection.Execute (mySQL)
 
CancelError:
End Sub

Private Sub ProcedureColorComBt_Click()
    Dim mySQL As String
    ChooseColor.Color = ProcedureColorTB.BackColor
    On Error GoTo CancelError
    
    ChooseColor.ShowColor
    ProcedureColorTB.BackColor = ChooseColor.Color
    Colour = ChooseColor.Color
    ProcColor = Colour

    mySQL = "UPDATE [UserPreferences] SET ProcColor = " & Colour & " WHERE UserID = " & userID
    dbConnection.Execute (mySQL)

        
    
CancelError:
End Sub

Private Sub ComponentColorComBt_Click()
    Dim mySQL As String
    ChooseColor.Color = ComponentColorTB.BackColor
    On Error GoTo CancelError
    
    ChooseColor.ShowColor
    ComponentColorTB.BackColor = ChooseColor.Color
    Colour = ChooseColor.Color
    CompColor = Colour

    mySQL = "UPDATE [UserPreferences] SET CompColor = " & Colour & " WHERE UserID = " & userID
    dbConnection.Execute (mySQL)

CancelError:
End Sub

Private Sub BarColorLoad()
    Dim mySQL As String
    Dim rarray As Variant
    Dim resultSet As rdoResultset

    mySQL = "SELECT TaskColor, ProcColor, CompColor FROM [UserPreferences] WHERE UserID = " & userID
    Set resultSet = dbConnection.OpenResultset(mySQL, rdOpenKeyset)
    rarray = resultSet.GetRows(1)
    
    TaskColorTB.BackColor = rarray(0, 0)
    ProcedureColorTB.BackColor = rarray(1, 0)
    ComponentColorTB.BackColor = rarray(2, 0)
    
    
End Sub




Private Sub TaskColorTB_Click()
    Dim mySQL As String
    ChooseColor.Color = TaskColorTB.BackColor
    On Error GoTo CancelError
    
    ChooseColor.ShowColor
    TaskColorTB.BackColor = ChooseColor.Color
    Colour = ChooseColor.Color
    TaskColor = Colour

    mySQL = "UPDATE [UserPreferences] SET TaskColor = " & Colour & " WHERE UserID = " & userID
    dbConnection.Execute (mySQL)
 
CancelError:
End Sub

Private Sub ProcedureColorTB_Click()
    Dim mySQL As String
    ChooseColor.Color = ProcedureColorTB.BackColor
    On Error GoTo CancelError
    
    ChooseColor.ShowColor
    ProcedureColorTB.BackColor = ChooseColor.Color
    Colour = ChooseColor.Color
    ProcColor = Colour

    mySQL = "UPDATE [UserPreferences] SET ProcColor = " & Colour & " WHERE UserID = " & userID
    dbConnection.Execute (mySQL)

        
    
CancelError:
End Sub

Private Sub ComponentColorTB_Click()
    Dim mySQL As String
    ChooseColor.Color = ComponentColorTB.BackColor
    On Error GoTo CancelError
    
    ChooseColor.ShowColor
    ComponentColorTB.BackColor = ChooseColor.Color
    Colour = ChooseColor.Color
    CompColor = Colour

    mySQL = "UPDATE [UserPreferences] SET CompColor = " & Colour & " WHERE UserID = " & userID
    dbConnection.Execute (mySQL)

CancelError:
End Sub

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'end scheduel bar color code
'''''''''''''''''''''''''''''''''''''

'''''''''''''''''''''''''''''''''''''
'begin danger bar color code
''''''''''''''''''''''''''''''''''''''''''''
Private Sub LowRiskComBtn_Click()
    Dim mySQL As String
    ChooseColor.Color = LowRiskTB.BackColor
    On Error GoTo CancelError
    
    ChooseColor.ShowColor
    LowRiskTB.BackColor = ChooseColor.Color
    rColour = ChooseColor.Color
    OKColor = rColour

    mySQL = "UPDATE [UserPreferences] SET OKColor = " & rColour & " WHERE UserID = " & userID
    dbConnection.Execute (mySQL)
 
CancelError:
End Sub

Private Sub MediumRiskComBtn_Click()
    Dim mySQL As String
    ChooseColor.Color = MedRiskTB.BackColor
    On Error GoTo CancelError
    
    ChooseColor.ShowColor
    MedRiskTB.BackColor = ChooseColor.Color
    rColour = ChooseColor.Color
    CautionColor = rColour

    mySQL = "UPDATE [UserPreferences] SET CautionColor = " & rColour & " WHERE UserID = " & userID
    dbConnection.Execute (mySQL)

        
    
CancelError:
End Sub

Private Sub HighRiskComBtn_Click()
    Dim mySQL As String
    ChooseColor.Color = HighRiskTB.BackColor
    On Error GoTo CancelError
    
    ChooseColor.ShowColor
    HighRiskTB.BackColor = ChooseColor.Color
    rColour = ChooseColor.Color
    DangerColor = rColour

    mySQL = "UPDATE [UserPreferences] SET DangerColor = " & rColour & " WHERE UserID = " & userID
    dbConnection.Execute (mySQL)

CancelError:
End Sub

Private Sub RiskColorLoad()
    Dim mySQL As String
    Dim rarray As Variant
    Dim resultSet As rdoResultset

    mySQL = "SELECT DangerColor, CautionColor, OKColor FROM [UserPreferences] WHERE UserID = " & userID
    Set resultSet = dbConnection.OpenResultset(mySQL, rdOpenKeyset)
    rarray = resultSet.GetRows(1)
    
    rDanger = rarray(0, 0)
    rCaution = rarray(1, 0)
    rOK = rarray(2, 0)
    
    LowRiskTB.BackColor = rOK
    MedRiskTB.BackColor = rCaution
    HighRiskTB.BackColor = rDanger
    
    
End Sub

Private Sub LowRiskTB_Click()
    Dim mySQL As String
    ChooseColor.Color = LowRiskTB.BackColor
    On Error GoTo CancelError
    
    ChooseColor.ShowColor
    LowRiskTB.BackColor = ChooseColor.Color
    rColour = ChooseColor.Color
    OKColor = rColour

    mySQL = "UPDATE [UserPreferences] SET OKColor = " & rColour & " WHERE UserID = " & userID
    dbConnection.Execute (mySQL)
 
CancelError:
End Sub

Private Sub MedRiskTB_Click()
    Dim mySQL As String
    ChooseColor.Color = MedRiskTB.BackColor
    On Error GoTo CancelError
    
    ChooseColor.ShowColor
    MedRiskTB.BackColor = ChooseColor.Color
    Colour = ChooseColor.Color
    CautionColor = Colour

    mySQL = "UPDATE [UserPreferences] SET CautionColor = " & Colour & " WHERE UserID = " & userID
    dbConnection.Execute (mySQL)

        
    
CancelError:
End Sub

Private Sub HighRiskTB_Click()
    Dim mySQL As String
    ChooseColor.Color = HighRiskTB.BackColor
    On Error GoTo CancelError
    
    ChooseColor.ShowColor
    HighRiskTB.BackColor = ChooseColor.Color
    rColour = ChooseColor.Color
    DangerColor = rColour

    mySQL = "UPDATE [UserPreferences] SET DangerColor = " & Colour & " WHERE UserID = " & userID
    dbConnection.Execute (mySQL)

CancelError:
End Sub

''''''''''''''''''''''''''''''''''''''''''
'end danger bar color code
''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''
'start of color scheme code
'''''''''''''''''''''''''''''''''
Private Sub schemeLoad()
    Dim mySQL As String
    Dim rarray As Variant
    Dim resultSet As rdoResultset
    Dim i As Integer
    i = 0
    mySQL = "SELECT Name From ColorScheme "
    Set resultSet = dbConnection.OpenResultset(mySQL)
    While Not resultSet.EOF
          rarray = resultSet.GetRows(1)
          SchemeNameCB.AddItem rarray(0, 0)
    Wend
    SchemeNameCB.ListIndex = 0
    rarray = resultSet
    
    
    EditSchemeBtn.Enabled = False
    NewSchemeBtn.Enabled = False
End Sub

Private Sub schemeTabOK()

End Sub


'''''''''''''''''''''''''
'End Color scheme Code''''''''
''''''''''''''''''''''''''''''


''''''''''''''''''
'Start General Tab code
''''''''''''''''''''''
Private Sub LoadGeneral()
    Russianlang.Enabled = False
    EnglishLang.Value = True
    EnglishLang.Enabled = False
    DateTypedMonth.Enabled = False
    DateMDYslashes.Enabled = False
    DateDMYdots.Enabled = False
    DateDMYslashes.Enabled = False
    
    
End Sub

Private Sub GeneralTabOK()

End Sub

''''''''''''''''''''''''''''
'End Start General Tab code
'''''''''''''''''''''''

''''''''''''''''''
'Start Scheduel Tab code
''''''''''''''''''''''
Private Sub LoadScheduel()
    modeAsBack.Value = True
    modeAsBack.Enabled = False
    modeAsBar.Enabled = False
    PTCdispCB.Enabled = False
    ModeNameDispCB.Enabled = False
End Sub

Private Sub ScheduelTabOK()

End Sub




''''''''''''''''''''''''''''
'End Scheduel Tab code
'''''''''''''''''''''''

''''''''''''''''''
'Start Calendar Tab code
''''''''''''''''''''''
Private Sub LoadCalendar()
    GaugeIndOptB.Value = True
    GaugeIndOptB.Enabled = False
    NumValOptB.Enabled = False
    ShowAvgRiskCB.Enabled = False
    ShowPeekRiskCB.Enabled = False
End Sub

Private Sub CalendarTabOK()

End Sub



''''''''''''''''''''''''''''
'End Calendar Tab code
'''''''''''''''''''''''

