VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form ModeSetupForm 
   Caption         =   "Form1"
   ClientHeight    =   3945
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   5730
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
   ScaleHeight     =   3945
   ScaleWidth      =   5730
   StartUpPosition =   3  'Windows Default
   Begin MSComctlLib.ListView ModeList 
      Height          =   2175
      Left            =   240
      TabIndex        =   0
      Top             =   600
      Width           =   5055
      _ExtentX        =   8916
      _ExtentY        =   3836
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
   Begin VB.Label Label1 
      Caption         =   "Modes in this project:"
      Height          =   255
      Left            =   240
      TabIndex        =   1
      Top             =   120
      Width           =   3975
   End
End
Attribute VB_Name = "ModeSetupForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Sub Form_Load()
    Dim modecount As Integer, resultSet As rdoResultset, mySQLstatement As String
    Dim modeID As Integer
    
    modecount = 0
    mySQLstatement = "SELECT ModeID FROM Mode ORDER BY ModeID DESC"
    Set resultSet = dbConnection.OpenResultset(mySQLstatement)
    
    If Not resultSet.EOF Then
        rarray = resultSet.GetRows(1)
        upperModeID = rarray(0, 0)
        Dim i As Integer
        For i = 1 To upperModeID
            Set Mode = New ModeClass
            Mode.CreateNewMode
            ModeList.Add Mode
        Next i
        mySQLstatement = "SELECT ModeID, ModeName, ModeDesc, SaphireProjPath, BaselineRisk, MediumRisk, HighRisk, ModeColor FROM Mode"

        Set resultSet = dbConnection.OpenResultset(mySQLstatement)
        While Not resultSet.EOF
            rarray = resultSet.GetRows(1)
            modeID = rarray(0, 0)
            ModeList.Item(modeID).SetMode rarray(1, 0), rarray(2, 0), rarray(3, 0), rarray(4, 0), rarray(5, 0), rarray(6, 0), rarray(7, 0)
            ModeList.Item(modeID).ObjectInUse = True
            modecount = modecount + 1
        Wend
    Else
        ' have the user try and create at least one mode now if none exist
        Set Mode = New ModeClass
        Mode.CreateNewMode
        If MsgBox("No modes or associated SAPHIRE projects have been found.  At least one mode must be created before the Risk Monitor can be used.  Would you like to create a mode now?", vbYesNo) = vbYes Then
            If Not Mode.AddMode(modeID) Then
                MsgBox "Risk Monitor could not load because no modes or associated SAPHIRE projects were found.", vbExclamation
                Unload Me
            End If
            Do While MsgBox("Would you like to add another mode now?", vbYesNo) = vbYes
                Mode.AddMode modeID
            Loop
        Else
            MsgBox "Risk Monitor could not load because no modes or associated SAPHIRE projects were found.", vbExclamation
            Unload Me
        End If
    End If

End Sub
