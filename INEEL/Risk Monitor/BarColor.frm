VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form BarColor 
   Caption         =   "Bar Color"
   ClientHeight    =   3000
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   5190
   LinkTopic       =   "Form1"
   ScaleHeight     =   3000
   ScaleWidth      =   5190
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton OKButton 
      Caption         =   "OK"
      Height          =   375
      Left            =   2040
      TabIndex        =   6
      Top             =   2280
      Width           =   1215
   End
   Begin VB.TextBox TaskColorTB 
      Height          =   375
      Left            =   2040
      TabIndex        =   5
      Top             =   360
      Width           =   2055
   End
   Begin VB.TextBox ProcedureColorTB 
      Height          =   375
      Left            =   2040
      TabIndex        =   4
      Top             =   960
      Width           =   2055
   End
   Begin VB.TextBox ComponentColorTB 
      Height          =   375
      Left            =   2040
      TabIndex        =   3
      Top             =   1560
      Width           =   2055
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
      Left            =   4200
      TabIndex        =   2
      Top             =   360
      Width           =   495
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
      Left            =   4200
      TabIndex        =   1
      Top             =   960
      Width           =   495
   End
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
      Left            =   4200
      TabIndex        =   0
      Top             =   1560
      Width           =   495
   End
   Begin MSComDlg.CommonDialog ChooseColor 
      Left            =   120
      Top             =   1920
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
      CancelError     =   -1  'True
   End
   Begin VB.Label TaksColorLbl 
      Caption         =   "Task Color:"
      Height          =   375
      Left            =   600
      TabIndex        =   9
      Top             =   480
      Width           =   1695
   End
   Begin VB.Label ProcedureColorLbl 
      Caption         =   "Procedure Color:"
      Height          =   375
      Left            =   600
      TabIndex        =   8
      Top             =   1080
      Width           =   1695
   End
   Begin VB.Label ComponentColorLbl 
      Caption         =   "Component Color:"
      Height          =   375
      Left            =   600
      TabIndex        =   7
      Top             =   1680
      Width           =   1695
   End
End
Attribute VB_Name = "BarColor"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Option Explicit
Public Colour As Long
Public danger As Long, caution As Long, OK As Long



Private Sub CancelButton_Click()
    Unload Me
End Sub


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

Private Sub Form_Load()
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

Private Sub OKButton_Click()
    MDIMain.RefreshData
    Unload Me
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

