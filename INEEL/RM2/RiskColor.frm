VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form RiskColor 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Risk Color"
   ClientHeight    =   3015
   ClientLeft      =   2760
   ClientTop       =   3750
   ClientWidth     =   5205
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3015
   ScaleWidth      =   5205
   ShowInTaskbar   =   0   'False
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
      Left            =   4200
      TabIndex        =   9
      Top             =   1560
      Width           =   495
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
      Left            =   4200
      TabIndex        =   8
      Top             =   960
      Width           =   495
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
      Left            =   4200
      TabIndex        =   7
      Top             =   360
      Width           =   495
   End
   Begin VB.TextBox HighRiskTB 
      Height          =   375
      Left            =   2040
      TabIndex        =   3
      Top             =   1560
      Width           =   2055
   End
   Begin VB.TextBox MedRiskTB 
      Height          =   375
      Left            =   2040
      TabIndex        =   2
      Top             =   960
      Width           =   2055
   End
   Begin VB.TextBox LowRiskTB 
      Height          =   375
      Left            =   2040
      TabIndex        =   1
      Top             =   360
      Width           =   2055
   End
   Begin VB.CommandButton OKButton 
      Caption         =   "OK"
      Height          =   375
      Left            =   2040
      TabIndex        =   0
      Top             =   2280
      Width           =   1215
   End
   Begin MSComDlg.CommonDialog ChooseColor 
      Left            =   480
      Top             =   2040
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
      CancelError     =   -1  'True
   End
   Begin VB.Label HighRiskLbl 
      Caption         =   "High Risk Color:"
      Height          =   375
      Left            =   600
      TabIndex        =   6
      Top             =   1680
      Width           =   1695
   End
   Begin VB.Label MediumRiskLbl 
      Caption         =   "Medium Risk Color:"
      Height          =   375
      Left            =   600
      TabIndex        =   5
      Top             =   1080
      Width           =   1695
   End
   Begin VB.Label LowRiskLbl 
      Caption         =   "Low Risk Color:"
      Height          =   375
      Left            =   600
      TabIndex        =   4
      Top             =   480
      Width           =   1695
   End
End
Attribute VB_Name = "RiskColor"
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

Private Sub LowRiskComBtn_Click()
    Dim mySQL As String
    ChooseColor.Color = LowRiskTB.BackColor
    On Error GoTo CancelError
    
    ChooseColor.ShowColor
    LowRiskTB.BackColor = ChooseColor.Color
    Colour = ChooseColor.Color
    OKColor = Colour

    mySQL = "UPDATE [UserPreferences] SET OKColor = " & Colour & " WHERE UserID = " & userID
    dbConnection.Execute (mySQL)
 
CancelError:
End Sub

Private Sub MediumRiskComBtn_Click()
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

Private Sub HighRiskComBtn_Click()
    Dim mySQL As String
    ChooseColor.Color = HighRiskTB.BackColor
    On Error GoTo CancelError
    
    ChooseColor.ShowColor
    HighRiskTB.BackColor = ChooseColor.Color
    Colour = ChooseColor.Color
    DangerColor = Colour

    mySQL = "UPDATE [UserPreferences] SET DangerColor = " & Colour & " WHERE UserID = " & userID
    dbConnection.Execute (mySQL)

CancelError:
End Sub

Private Sub Form_Load()
    Dim mySQL As String
    Dim rarray As Variant
    Dim resultSet As rdoResultset

    mySQL = "SELECT DangerColor, CautionColor, OKColor FROM [UserPreferences] WHERE UserID = " & userID
    Set resultSet = dbConnection.OpenResultset(mySQL, rdOpenKeyset)
    rarray = resultSet.GetRows(1)
    
    danger = rarray(0, 0)
    caution = rarray(1, 0)
    OK = rarray(2, 0)
    
    LowRiskTB.BackColor = OK
    MedRiskTB.BackColor = caution
    HighRiskTB.BackColor = danger
    
    
End Sub

Private Sub OKButton_Click()
    MDIMain.RefreshData
    Unload Me
End Sub


Private Sub LowRiskTB_Click()
    Dim mySQL As String
    ChooseColor.Color = LowRiskTB.BackColor
    On Error GoTo CancelError
    
    ChooseColor.ShowColor
    LowRiskTB.BackColor = ChooseColor.Color
    Colour = ChooseColor.Color
    OKColor = Colour

    mySQL = "UPDATE [UserPreferences] SET OKColor = " & Colour & " WHERE UserID = " & userID
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
    Colour = ChooseColor.Color
    DangerColor = Colour

    mySQL = "UPDATE [UserPreferences] SET DangerColor = " & Colour & " WHERE UserID = " & userID
    dbConnection.Execute (mySQL)

CancelError:
End Sub
