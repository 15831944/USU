VERSION 5.00
Begin VB.Form AttackForm 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Attack!"
   ClientHeight    =   5580
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   6030
   ControlBox      =   0   'False
   BeginProperty Font 
      Name            =   "Arial"
      Size            =   14.25
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   372
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   402
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin VB.Timer CompRetreat 
      Enabled         =   0   'False
      Interval        =   1500
      Left            =   4800
      Top             =   4920
   End
   Begin VB.Timer CompActionD 
      Enabled         =   0   'False
      Interval        =   1200
      Left            =   4080
      Top             =   4920
   End
   Begin VB.Timer CompActionA 
      Enabled         =   0   'False
      Interval        =   800
      Left            =   3480
      Top             =   4920
   End
   Begin VB.Timer Timer1 
      Enabled         =   0   'False
      Interval        =   2000
      Left            =   2760
      Top             =   4920
   End
   Begin VB.CommandButton RetreatButton 
      Caption         =   "Retreat"
      Height          =   495
      Left            =   360
      TabIndex        =   10
      Top             =   4920
      Width           =   1815
   End
   Begin VB.CommandButton DefendButton 
      Caption         =   "Roll 1"
      Height          =   495
      Index           =   1
      Left            =   3840
      TabIndex        =   6
      Top             =   3360
      Width           =   1815
   End
   Begin VB.CommandButton DefendButton 
      Caption         =   "Roll 2"
      Height          =   495
      Index           =   2
      Left            =   3840
      TabIndex        =   5
      Top             =   2760
      Width           =   1815
   End
   Begin VB.CommandButton AttackButton 
      Caption         =   "Roll 1"
      Height          =   495
      Index           =   1
      Left            =   360
      TabIndex        =   4
      Top             =   3960
      Width           =   1815
   End
   Begin VB.CommandButton AttackButton 
      Caption         =   "Roll 2"
      Height          =   495
      Index           =   2
      Left            =   360
      TabIndex        =   3
      Top             =   3360
      Width           =   1815
   End
   Begin VB.CommandButton AttackButton 
      Caption         =   "Roll 3"
      Height          =   495
      Index           =   3
      Left            =   360
      TabIndex        =   2
      Top             =   2760
      Width           =   1815
   End
   Begin VB.PictureBox Picture2 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   900
      Left            =   4320
      Picture         =   "AttackForm.frx":0000
      ScaleHeight     =   840
      ScaleWidth      =   840
      TabIndex        =   1
      Top             =   1560
      Width           =   900
      Begin VB.Label ArmyCount 
         Alignment       =   2  'Center
         BackStyle       =   0  'Transparent
         Caption         =   "1"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   300
         Index           =   1
         Left            =   0
         TabIndex        =   14
         Top             =   12
         Width           =   300
      End
   End
   Begin VB.PictureBox Picture1 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   900
      Left            =   720
      Picture         =   "AttackForm.frx":2A72
      ScaleHeight     =   840
      ScaleWidth      =   840
      TabIndex        =   0
      Top             =   1560
      Width           =   900
      Begin VB.Label ArmyCount 
         Alignment       =   2  'Center
         BackStyle       =   0  'Transparent
         Caption         =   "1"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   300
         Index           =   0
         Left            =   0
         TabIndex        =   13
         Top             =   12
         Width           =   300
      End
   End
   Begin VB.Shape AH 
      BorderColor     =   &H000000FF&
      Height          =   585
      Index           =   3
      Left            =   2355
      Top             =   3915
      Visible         =   0   'False
      Width           =   585
   End
   Begin VB.Shape DH 
      BorderColor     =   &H000000FF&
      Height          =   585
      Index           =   2
      Left            =   3075
      Top             =   3315
      Visible         =   0   'False
      Width           =   585
   End
   Begin VB.Shape DH 
      BorderColor     =   &H000000FF&
      Height          =   585
      Index           =   1
      Left            =   3075
      Top             =   2715
      Visible         =   0   'False
      Width           =   585
   End
   Begin VB.Shape AH 
      BorderColor     =   &H000000FF&
      Height          =   585
      Index           =   2
      Left            =   2355
      Top             =   3315
      Visible         =   0   'False
      Width           =   585
   End
   Begin VB.Shape AH 
      BorderColor     =   &H000000FF&
      Height          =   585
      Index           =   1
      Left            =   2355
      Top             =   2715
      Visible         =   0   'False
      Width           =   585
   End
   Begin VB.Image DefendDie 
      Height          =   495
      Index           =   2
      Left            =   3120
      Picture         =   "AttackForm.frx":54E4
      Top             =   3360
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Image AttackDie 
      Height          =   495
      Index           =   1
      Left            =   2400
      Picture         =   "AttackForm.frx":620A
      Top             =   2760
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Image AttackDie 
      Height          =   495
      Index           =   2
      Left            =   2400
      Picture         =   "AttackForm.frx":6F30
      Top             =   3360
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Image AttackDie 
      Height          =   495
      Index           =   3
      Left            =   2400
      Picture         =   "AttackForm.frx":7C56
      Top             =   3960
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Image DefendDie 
      Height          =   495
      Index           =   1
      Left            =   3120
      Picture         =   "AttackForm.frx":897C
      Top             =   2760
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label Label5 
      Alignment       =   2  'Center
      Caption         =   "Label5"
      Height          =   375
      Left            =   3720
      TabIndex        =   12
      Top             =   1080
      Width           =   2055
   End
   Begin VB.Label Label4 
      Alignment       =   2  'Center
      Caption         =   "Label4"
      Height          =   375
      Left            =   240
      TabIndex        =   11
      Top             =   1080
      Width           =   1935
   End
   Begin VB.Label Label3 
      Alignment       =   2  'Center
      Caption         =   "Manchuria is under attack!"
      Height          =   375
      Left            =   0
      TabIndex        =   9
      Top             =   120
      Width           =   6015
   End
   Begin VB.Label Label2 
      Alignment       =   2  'Center
      Caption         =   "Defender"
      Height          =   375
      Left            =   3720
      TabIndex        =   8
      Top             =   600
      Width           =   1935
   End
   Begin VB.Label Label1 
      Alignment       =   2  'Center
      Caption         =   "Attacker"
      Height          =   375
      Left            =   240
      TabIndex        =   7
      Top             =   600
      Width           =   1935
   End
End
Attribute VB_Name = "AttackForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private ToWhichCountryID As Integer
Private FromWhichCountryID As Integer
Private AEngaged As Boolean
Private DEngaged As Boolean
Private DCommitted As Integer
Private aName As String
Private aIsComputer, dIsComputer As Boolean
Private AttackerID As Integer
Private DefenderID As Long
Dim ADie(1 To 3) As Integer
Dim DDie(1 To 2) As Integer

Private StartACount As Integer
Private StartDCount As Integer

Public ACount As Integer
Public DCount As Integer
Public ACommitted As Integer
'Public TotalADead As Integer
'Public TotalDDead As Integer
Public DidRetreat As Boolean

Private AFired As Boolean
Private DFired As Boolean

Private Declare Function CallMakeMove Lib "ManagerDLL" (ByRef AttackWhere As Long, ByRef FromWhere As Long, ByRef nArmiesToUse As Long, ByRef result As Long) As Boolean
Private Declare Function CallDefendCountry Lib "ManagerDLL" (ByVal DefenderID As Long, ByVal OpposingArmies As Long, ByVal myArmies As Long, ByVal countryID As Long, ByRef DiceToRoll As Long) As Boolean
Private Declare Function GetPlayerInfo Lib "ManagerDLL" (ByVal wPlayer As Long, ByRef pInfo As PLAYER_INFO) As Long
Private Declare Function sndPlaySound Lib "winmm.dll" Alias "sndPlaySoundA" (ByVal lpszSoundName As String, _
    ByVal uFlags As Long) As Long
    
'Private attackCountry As COUNTRY_DATA
'Private defendCountry As COUNTRY_DATA
'Private attackPlayer As PLAYER_INFO
'Private defendPlayer As PLAYER_INFO

Private Sub AttackButton_Click(index As Integer)
    AEngaged = True
    ACommitted = index
    AttackButton(3).Enabled = False
    AttackButton(2).Enabled = False
    AttackButton(1).Enabled = False
    RetreatButton.Enabled = False
    If AEngaged And DEngaged Then
        ResolveCombat
    End If
End Sub

Private Sub CompActionA_Timer()
    CompActionA.Enabled = False
    
    If ACount = 0 Then
      'MyMessageBox "CompActionA_Timer called, ACount = 0"
      Exit Sub
    End If
    
    If Not AEngaged Then
        ' figure out how many dice to commit
        Dim result As Long, nArmies As Long, ToWhere As Long, FromWhere As Long
        If CallMakeMove(ToWhere, FromWhere, nArmies, result) = False Then
            MyMessageBox "CallMakeMove in AttackForm returned False"
            ReleaseAndEnd
        End If
        
        AttackButton(3).Enabled = False
        AttackButton(2).Enabled = False
        AttackButton(1).Enabled = False
        RetreatButton.Enabled = False
        If result = False Or ToWhere <> ToWhichCountryID Or FromWhere <> FromWhichCountryID Then
            ' cancel attack
            Label3.Caption = aName & " is retreating!"
            MainForm.SetLastMove Retreat, ToWhichCountryID, FromWhichCountryID
            CompRetreat.Enabled = True
            If result = False Then MainForm.GamePhase = Reinforcement
            Exit Sub
        End If
        If nArmies > ACount Then nArmies = ACount
        If nArmies > 3 Then nArmies = 3
        If nArmies < 1 Then nArmies = 1
        AFired = True
        ACommitted = nArmies
        AEngaged = True
    End If
    If AEngaged And DEngaged Then
        ResolveCombat
    End If
End Sub

Private Sub CompActionD_Timer()
    CompActionD.Enabled = False
    If DCount = 0 Then
      'MyMessageBox "CompActionD_Timer called, DCount = 0"
      Exit Sub
    End If
    
    If Not DEngaged Then
        ' figure out how many dice to commit
        Dim DiceToRoll As Long
        DiceToRoll = 1
        If DCount > 1 Then
            If CallDefendCountry(DefenderID, ACount, DCount, ToWhichCountryID, DiceToRoll) = False Then
                MyMessageBox "CallDefendCountry returned False"
                ReleaseAndEnd
            End If
        End If
        DEngaged = True
        DFired = True
        DCommitted = DiceToRoll
        DefendButton(2).Enabled = False
        DefendButton(1).Enabled = False
    End If
    If AEngaged And DEngaged Then
        ResolveCombat
    End If
End Sub

Private Sub CompRetreat_Timer()
    CompRetreat.Enabled = False
    RetreatButton_Click
End Sub

Private Sub DefendButton_Click(index As Integer)
    DEngaged = True
    DCommitted = index
    DefendButton(2).Enabled = False
    DefendButton(1).Enabled = False
    If AEngaged And DEngaged Then
        ResolveCombat
    End If
End Sub

Private Sub Swap(a As Integer, b As Integer)
    Dim temp As Integer
    temp = a
    a = b
    b = temp
End Sub

Private Sub HideDice()
     AttackDie(1).Visible = False
    AttackDie(2).Visible = False
    AttackDie(3).Visible = False
    DefendDie(1).Visible = False
    DefendDie(2).Visible = False
    AH(1).Visible = False
    AH(2).Visible = False
    AH(3).Visible = False
    DH(1).Visible = False
    DH(2).Visible = False
End Sub

Private Sub ResolveCombat()
    If ACount > 0 And DCount > 0 Then
        If ACommitted > ACount Then ACommitted = ACount
        If DCommitted > DCount Then DCommitted = DCount
        If ACommitted > 3 Then ACommitted = 3
        If DCommitted > 2 Then DCommitted = 2
        
        HideDice
        Dim i As Integer
        ADie(1) = Int(Rnd() * 6) + 1
        ADie(2) = Int(Rnd() * 6) + 1
        ADie(3) = Int(Rnd() * 6) + 1
        DDie(1) = Int(Rnd() * 6) + 1
        DDie(2) = Int(Rnd() * 6) + 1
        
        If ACommitted = 3 Then
            If ADie(3) > ADie(2) And ADie(3) > ADie(1) Then Swap ADie(3), ADie(1)
            If ADie(2) > ADie(1) Then Swap ADie(2), ADie(1)
            If ADie(3) > ADie(2) Then Swap ADie(3), ADie(2)
        ElseIf ACommitted = 2 Then
            If ADie(2) > ADie(1) Then Swap ADie(2), ADie(1)
        End If
        
        For i = 1 To ACommitted
            AttackDie(i).Picture = LoadPicture("D" & ADie(i) & ".bmp")
            AttackDie(i).Visible = True
        Next i
        
        If DCommitted = 2 Then
            If DDie(2) > DDie(1) Then Swap DDie(2), DDie(1)
        End If
        
        For i = 1 To DCommitted
            DefendDie(i).Picture = LoadPicture("D" & DDie(i) & ".bmp")
            DefendDie(i).Visible = True
        Next i
        
        i = 1
        Dim ADead As Integer, DDead As Integer
        ADead = 0
        DDead = 0
        Do
            If ADie(i) > DDie(i) Then
                If DDead + 1 > DCount Then
                    'MyMessageBox "DDead > DCount", , "Error"
                    ' Don't understand why this is happening, but I believe if
                    ' I don't let the consequences take place, then we'll be ok
                Else
                    DDead = DDead + 1
                End If
                AH(i).Visible = True
            Else
                If ADead + 1 > ACount Then
                    'MyMessageBox "ADead > ACount", , "Error"
                    ' Don't understand why this is happening, but I believe if
                    ' I don't let the consequences take place, then we'll be ok
                Else
                    ADead = ADead + 1
                End If
                DH(i).Visible = True
            End If
            i = i + 1
        Loop While (i <= ACommitted) And (i <= DCommitted)
        
        ACount = ACount - ADead
        DCount = DCount - DDead
        
        If ACount < 0 Or DCount < 0 Then
            MyMessageBox "ACount < 0 Or DCount < 0", , "Error"
        End If
        
        'TotalADead = TotalADead + ADead
        'TotalDDead = TotalDDead + DDead
        'attackCountry.ArmyCount = attackCountry.ArmyCount - ADead
        'defendCountry.ArmyCount = defendCountry.ArmyCount - DDead
        'attackPlayer.ArmyCount = attackPlayer.ArmyCount - ADead
        'defendPlayer.ArmyCount = defendPlayer.ArmyCount - DDead
        frmMain.SetCountryArmyCount FromWhichCountryID, frmMain.GetCountryData(FromWhichCountryID).ArmyCount - ADead
        frmMain.SetCountryArmyCount ToWhichCountryID, frmMain.GetCountryData(ToWhichCountryID).ArmyCount - DDead
        frmMain.SetPlayerArmyCount AttackerID, frmMain.GetPlayerData(AttackerID).ArmyCount - ADead
        frmMain.SetPlayerArmyCount DefenderID, frmMain.GetPlayerData(DefenderID).ArmyCount - DDead
        
        If ACount = 0 Or DCount = 0 Then
            Dim name As String
            Select Case Int(Rnd() * 5) + 1
            Case 1: name = "mchnguns.wav"
            Case 2: name = "smallexp.wav"
            Case 3: name = "medexpl.wav"
            Case 4: name = "medgun.wav"
            Case 5: name = "infantry.wav"
            End Select
            sndPlaySound name, 1
        End If
    End If
    
    If ACount = 0 Then
        ' attacker lost
        Label3 = aName & " has lost!"
        Timer1.Enabled = True
        If aIsComputer Then
            MainForm.SetLastMove Defeat, FromWhichCountryID, ToWhichCountryID
        End If
    ElseIf DCount = 0 Then
        ' defender lost
        Label3 = aName & " has won!"
        Timer1.Enabled = True
        If aIsComputer Then
            MainForm.SetLastMove CapturedCountry, FromWhichCountryID, ToWhichCountryID
        End If
    Else
        If aIsComputer Then
            MainForm.SetLastMove MadeAttack, FromWhichCountryID, ToWhichCountryID
        End If
        PrepareNewRound
    End If
    
End Sub

Private Sub PrepareNewRound()
    ArmyCount(0).Caption = ACount
    ArmyCount(1).Caption = DCount
    AttackButton(3).Enabled = ((ACount >= 3) And Not aIsComputer)
    AttackButton(2).Enabled = ((ACount >= 2) And Not aIsComputer)
    DefendButton(2).Enabled = ((DCount >= 2) And Not dIsComputer)
    AttackButton(1).Enabled = (True And Not aIsComputer)
    DefendButton(1).Enabled = (True And Not dIsComputer)
    RetreatButton.Enabled = (True And Not aIsComputer)
    DEngaged = False
    AEngaged = False
    AFired = False
    DFired = False
    If DCount = 0 Then
      MyMessageBox "PrepareNewRound called, DCount = 0"
    End If
    If ACount = 0 Then
      MyMessageBox "PrepareNewRound called, ACount = 0"
    End If
    If aIsComputer Then
        CompActionA.Enabled = True
    End If
    If dIsComputer Then
        CompActionD.Enabled = True
    End If
End Sub

Friend Sub SetInfo(CountryName As String, _
                   AttackerName As String, _
                   DefenderName As String, _
                   ByVal AttackerColor As Integer, _
                   ByVal DefenderColor As Integer, _
                   CountryA As Integer, _
                   CountryB As Integer, _
                   Optional ADiceToRoll As Long = 1)
    
    'ByRef AttackerC As COUNTRY_DATA, _
    'ByRef DefenderC As COUNTRY_DATA, _
    'ByRef APlayer As PLAYER_INFO, _
    'ByRef DPlayer As PLAYER_INFO, _
    'DefID As Long, _

    HideDice
            
    FromWhichCountryID = CountryA
    ToWhichCountryID = CountryB
    AttackerID = frmMain.GetCountryData(CountryA).OwnerID
    DefenderID = frmMain.GetCountryData(CountryB).OwnerID 'DefID
    
    DidRetreat = False
    Label3.Caption = CountryName & " is under attack!"
    Label4.Caption = AttackerName
    aName = AttackerName
    Label5.Caption = DefenderName
    Picture1.Picture = LoadPicture(GetPlayerPictureFileName(AttackerColor, True))
    Picture2.Picture = LoadPicture(GetPlayerPictureFileName(DefenderColor, True))
    
    ACount = frmMain.GetCountryData(CountryA).ArmyCount - 1
    DCount = frmMain.GetCountryData(CountryB).ArmyCount
    
'    TotalADead = 0
'    TotalDDead = 0
    StartACount = ACount
    StartDCount = DCount
    
    aIsComputer = Not frmMain.GetPlayerIsHuman(AttackerID)     ' attackPlayer.IsPlayerHuman
    dIsComputer = Not frmMain.GetPlayerIsHuman(DefenderID)     ' defendPlayer.IsPlayerHuman
    
    PrepareNewRound
    If aIsComputer Then
        AEngaged = True
        ACommitted = ADiceToRoll
        If ACommitted > ACount Then
            ACommitted = ACount
        End If
        
        If ACommitted > 3 Then ACommitted = 3
        If ACommitted < 1 Then ACommitted = 1
        
        
        If ADiceToRoll < 1 Then
            MyMessageBox "Error: computer did not commit any dice to the attack"
        End If
    End If
    
End Sub

Private Sub RetreatButton_Click()
    DidRetreat = True
    Me.Hide
End Sub

Private Sub Timer1_Timer()
    Timer1.Enabled = False
    Me.Hide
End Sub
