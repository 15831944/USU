VERSION 5.00
Object = "{8EB15BDB-9D20-11D5-B021-0002E3059EB4}#1.0#0"; "RiskBoardVC.ocx"
Begin VB.Form MainForm 
   Caption         =   "RISK"
   ClientHeight    =   6735
   ClientLeft      =   60
   ClientTop       =   405
   ClientWidth     =   9480
   Icon            =   "frmMain.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   6735
   ScaleWidth      =   9480
   WindowState     =   2  'Maximized
   Begin VB.CommandButton EndTurnButton 
      Caption         =   "End Turn"
      Enabled         =   0   'False
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   15.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   120
      TabIndex        =   27
      Top             =   6170
      Width           =   3975
   End
   Begin RISKBOARDVCLib.RiskBoardVC RiskBoardVC1 
      Height          =   10215
      Left            =   4200
      TabIndex        =   26
      Top             =   120
      Width           =   9615
      _Version        =   65536
      _ExtentX        =   16960
      _ExtentY        =   18018
      _StockProps     =   0
   End
   Begin VB.PictureBox ArmyImage 
      Height          =   975
      Index           =   0
      Left            =   3120
      Picture         =   "frmMain.frx":0CFA
      ScaleHeight     =   60
      ScaleMode       =   0  'User
      ScaleWidth      =   60
      TabIndex        =   14
      Top             =   240
      Visible         =   0   'False
      Width           =   975
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
         TabIndex        =   20
         Top             =   15
         Visible         =   0   'False
         Width           =   300
      End
   End
   Begin VB.Frame Frame1 
      Height          =   6135
      Left            =   120
      TabIndex        =   1
      Top             =   0
      Width           =   4095
      Begin VB.PictureBox ArmyImage 
         Height          =   975
         Index           =   5
         Left            =   3000
         Picture         =   "frmMain.frx":376C
         ScaleHeight     =   60
         ScaleMode       =   0  'User
         ScaleWidth      =   60
         TabIndex        =   19
         Top             =   5040
         Visible         =   0   'False
         Width           =   975
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
            Height          =   305
            Index           =   5
            Left            =   0
            TabIndex        =   25
            Top             =   30
            Visible         =   0   'False
            Width           =   305
         End
      End
      Begin VB.PictureBox ArmyImage 
         Height          =   975
         Index           =   4
         Left            =   3000
         Picture         =   "frmMain.frx":61DE
         ScaleHeight     =   60
         ScaleMode       =   0  'User
         ScaleWidth      =   60
         TabIndex        =   18
         Top             =   4080
         Visible         =   0   'False
         Width           =   975
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
            Height          =   305
            Index           =   4
            Left            =   0
            TabIndex        =   24
            Top             =   30
            Visible         =   0   'False
            Width           =   305
         End
      End
      Begin VB.PictureBox ArmyImage 
         Height          =   975
         Index           =   3
         Left            =   3000
         Picture         =   "frmMain.frx":8C50
         ScaleHeight     =   60
         ScaleMode       =   0  'User
         ScaleWidth      =   60
         TabIndex        =   17
         Top             =   3120
         Visible         =   0   'False
         Width           =   975
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
            Height          =   305
            Index           =   3
            Left            =   0
            TabIndex        =   23
            Top             =   30
            Visible         =   0   'False
            Width           =   305
         End
      End
      Begin VB.PictureBox ArmyImage 
         Height          =   975
         Index           =   2
         Left            =   3000
         Picture         =   "frmMain.frx":B6C2
         ScaleHeight     =   60
         ScaleMode       =   0  'User
         ScaleWidth      =   60
         TabIndex        =   16
         Top             =   2160
         Visible         =   0   'False
         Width           =   975
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
            Height          =   305
            Index           =   2
            Left            =   0
            TabIndex        =   22
            Top             =   30
            Visible         =   0   'False
            Width           =   305
         End
      End
      Begin VB.PictureBox ArmyImage 
         Height          =   975
         Index           =   1
         Left            =   3000
         Picture         =   "frmMain.frx":E134
         ScaleHeight     =   60
         ScaleMode       =   0  'User
         ScaleWidth      =   60
         TabIndex        =   15
         Top             =   1200
         Visible         =   0   'False
         Width           =   975
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
            Height          =   305
            Index           =   1
            Left            =   0
            TabIndex        =   21
            Top             =   30
            Visible         =   0   'False
            Width           =   305
         End
      End
      Begin VB.Label PlayerNameLabel 
         Caption         =   "Player 1"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   15.75
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Index           =   0
         Left            =   120
         TabIndex        =   13
         Top             =   240
         Visible         =   0   'False
         Width           =   2655
      End
      Begin VB.Label PlayerNameLabel 
         Caption         =   "Player 2"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   15.75
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Index           =   1
         Left            =   120
         TabIndex        =   12
         Top             =   1215
         Visible         =   0   'False
         Width           =   2655
      End
      Begin VB.Label PlayerNameLabel 
         Caption         =   "Player 3"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   15.75
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Index           =   2
         Left            =   120
         TabIndex        =   11
         Top             =   2190
         Visible         =   0   'False
         Width           =   2655
      End
      Begin VB.Label PlayerNameLabel 
         Caption         =   "Player 4"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   15.75
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Index           =   3
         Left            =   120
         TabIndex        =   10
         Top             =   3165
         Visible         =   0   'False
         Width           =   2655
      End
      Begin VB.Label PlayerNameLabel 
         Caption         =   "Player 5"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   15.75
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Index           =   4
         Left            =   120
         TabIndex        =   9
         Top             =   4140
         Visible         =   0   'False
         Width           =   2655
      End
      Begin VB.Label PlayerNameLabel 
         Caption         =   "Player 6"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   15.75
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Index           =   5
         Left            =   120
         TabIndex        =   8
         Top             =   5115
         Visible         =   0   'False
         Width           =   2655
      End
      Begin VB.Label PlayerInfoLabel 
         Caption         =   "12 Countries, 4 Cards"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Index           =   0
         Left            =   120
         TabIndex        =   7
         Top             =   720
         Visible         =   0   'False
         Width           =   2895
      End
      Begin VB.Label PlayerInfoLabel 
         Caption         =   "6 armies, 12 Countries"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Index           =   1
         Left            =   120
         TabIndex        =   6
         Top             =   1704
         Visible         =   0   'False
         Width           =   2895
      End
      Begin VB.Label PlayerInfoLabel 
         Caption         =   "6 armies, 12 Countries"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Index           =   2
         Left            =   120
         TabIndex        =   5
         Top             =   2688
         Visible         =   0   'False
         Width           =   2895
      End
      Begin VB.Label PlayerInfoLabel 
         Caption         =   "6 armies, 12 Countries"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Index           =   3
         Left            =   120
         TabIndex        =   4
         Top             =   3672
         Visible         =   0   'False
         Width           =   2895
      End
      Begin VB.Label PlayerInfoLabel 
         Caption         =   "6 armies, 12 Countries"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Index           =   4
         Left            =   120
         TabIndex        =   3
         Top             =   4656
         Visible         =   0   'False
         Width           =   2895
      End
      Begin VB.Label PlayerInfoLabel 
         Caption         =   "6 armies, 12 Countries"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Index           =   5
         Left            =   120
         TabIndex        =   2
         Top             =   5640
         Visible         =   0   'False
         Width           =   2895
      End
   End
   Begin VB.PictureBox sbStatusBar 
      Align           =   2  'Align Bottom
      Height          =   270
      Left            =   0
      ScaleHeight     =   210
      ScaleWidth      =   9420
      TabIndex        =   0
      Top             =   6465
      Width           =   9480
   End
   Begin VB.Image Image1 
      Height          =   3690
      Left            =   120
      Picture         =   "frmMain.frx":10BA6
      Top             =   6720
      Width           =   3945
   End
End
Attribute VB_Name = "MainForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
' If this code works it was written by Mark Salisbury, otherwise it was written by someone else
Option Explicit

Public MinBoxHeight As Integer

Enum GamePhaseType
    InitialPlacement = 0
    TradeIn = 1
    TurnPlacement = 2
    attack = 3
    Reinforcement = 4
End Enum

' 0 - initial placement of armies
' 1 - turn start placement of armies
' 2 - trade in
' 3 - attacking mode
' 4 - selecting reinforcement move

Public GamePhase As GamePhaseType

Private Countries(0 To 42) As COUNTRY_DATA
Private Players(0 To 5) As PLAYER_INFO
Private playerName(0 To 5) As String
Private PlayerDLLName(0 To 5) As String
Private PlayerColorIndex(0 To 5) As Integer
Private cards(0 To 5) As CARD_DATA ' for each player
Private RiskCards(0 To 43) As Integer
Private CountryCaptured As Boolean
Private RiskCardIndex As Integer
Private LastMove As LAST_MOVE_INFO

Private Declare Function GetCurrentDirectory Lib "kernel32" Alias "GetCurrentDirectoryA" (ByVal nBufferLength As Long, ByVal lpBuffer As String) As Long
Private Declare Function SetCurrentDirectory Lib "kernel32" Alias "SetCurrentDirectoryA" (ByVal lpPathName As String) As Long
' the reason for keeping cards out of player_info is so that a player info struct may be obtained
' for any player by any player without giving away what cards that player has
Private Declare Function AreCountriesAdjacent Lib "ManagerDLL" (ByVal CountryA As Long, ByVal CountryB As Long) As Long
Private Declare Function CalculateArmiesToPlace Lib "ManagerDLL" (ByVal wPlayer As Long, ByRef ArmyCount As Long) As Long
Private Declare Function GetCountryName Lib "ManagerDLL" (ByVal wCountry As Long, ByVal name As String) As Long
Private Declare Function InitializeDLL Lib "ManagerDLL" (ByRef FirstCountry As COUNTRY_DATA, ByRef currentPlayer As Long, ByVal nPlayers As Long, ByRef FirstPlayerInfo As PLAYER_INFO, ByRef FirstCard As CARD_DATA, ByRef nTradeIns As Long, ByRef LastMove As LAST_MOVE_INFO, ByVal UsePointer As Long, ByRef WinCount As Long, ByVal TotalDLLCount As Long) As Long
Private Declare Function SetDLLName Lib "ManagerDLL" (ByVal wPlayer As Long, ByVal DLLName As String) As Long
Private Declare Function GetAdjacentCountryCount Lib "ManagerDLL" (ByVal wCountry As Long, ByRef AdjacentCount As Long) As Long
Private Declare Function GetAdjacentCountryID Lib "ManagerDLL" (wCountry As Long, wIndex As Long, ByRef AdjacentID As Long) As Long
Private Declare Function GetCardType Lib "ManagerDLL" (ByVal wCard As Long, ByRef CardType As Long) As Long
Private Declare Function GetNextTradeInValue Lib "ManagerDLL" () As Long
Private Declare Function GetAttackError Lib "ManagerDLL" (ByVal FromCountry As Long, ByVal ToCountry As Long) As Long
Private Declare Function GetLastErrorDescription Lib "ManagerDLL" () As String
' AI calls
Private Declare Function CallPlaceArmiesAtStart Lib "ManagerDLL" (ByVal ArmiesToPlace As Long, ByRef wCountry As Long, ByRef nArmies As Long) As Boolean
Private Declare Function CallPlaceArmies Lib "ManagerDLL" (ByVal ArmiesToPlace As Long, ByRef wCountry As Long, ByRef nArmies As Long) As Boolean
Private Declare Function CallMakeMove Lib "ManagerDLL" (ByRef AttackWhere As Long, ByRef FromWhere As Long, ByRef nArmiesToUse As Long, ByRef result As Long) As Boolean
Private Declare Function CallCaptureCountry Lib "ManagerDLL" (ByVal FromWhere As Long, ByVal ToWhere As Long, ByVal minArmies As Long, ByVal maxArmies As Long, ByRef nArmiesToMove As Long) As Boolean
Private Declare Function CallDoReinforcement Lib "ManagerDLL" (ByRef FromWhere As Long, ByRef ToWhere As Long, ByRef nArmies As Long, ByRef result As Long) As Boolean
Private Declare Sub CallTurnComplete Lib "ManagerDLL" ()

Friend Function GetCountryData(countryID As Integer) As COUNTRY_DATA
    GetCountryData = Countries(countryID)
End Function

Friend Function GetPlayerData(ByVal playerID As Integer) As PLAYER_INFO
    GetPlayerData = Players(playerID)
End Function

Public Sub SetCountryArmyCount(countryID As Integer, ArmyCount As Integer)
    Countries(countryID).ArmyCount = ArmyCount
    RiskBoardVC1.SetArmies countryID, PlayerColorIndex(Countries(countryID).OwnerID), ArmyCount
    RiskBoardVC1.RefreshMap
End Sub

Public Sub SetPlayerArmyCount(ByVal playerID As Integer, ac As Integer)
    Players(playerID).ArmyCount = ac
    ArmyCount(playerID).Caption = ac
End Sub

Private Sub CheckArmies()
  Dim i As Integer
  For i = 1 To 42
    If Countries(i).ArmyCount < 1 Then
        MsgBox ("Error, number armies is < 1 in Country(" & i & "), " & GetBasicCountryName(i))
        Dim a As Integer
        a = 0
    End If
  Next i
End Sub

Public Sub SetLastMove(Optional Action As Variant, Optional FromID As Variant, Optional ToID As Variant)
    If Not IsMissing(Action) Then LastMove.LastAction = Action
    If Not IsMissing(FromID) Then LastMove.FromID = FromID
    If Not IsMissing(ToID) Then LastMove.ToID = ToID
End Sub

Private Sub HighlightActivePlayer()
    Dim i As Integer
    For i = 0 To nPlayers - 1
        If Players(i).IsPlayerAlive = True Then
            If i = wPlayer Then
                ArmyImage(i).Appearance = 0
                PlayerNameLabel(i).FontBold = True
            Else
                ArmyImage(i).Appearance = 1
                PlayerNameLabel(i).FontBold = False
            End If
        End If
    Next i
End Sub

Public Function GetPlayerColorIndex(pIndex As Integer) As Integer
    GetPlayerColorIndex = PlayerColorIndex(pIndex)
End Function

Public Function GetPlayerIsHuman(ByVal wIndex As Integer) As Boolean
    GetPlayerIsHuman = Players(wIndex).IsPlayerHuman
End Function

Public Function GetPlayerName(wIndex As Integer) As String
    GetPlayerName = playerName(wIndex)
End Function

Private Sub Command1_Click()
    
End Sub

Private Sub EndTurnButton_Click()
    If Players(wPlayer).IsPlayerHuman Then
        If MyMessageBox("Do you wish to do a reinforcement move?", vbYesNo) = vbYes Then
            GamePhase = Reinforcement
            MyMessageBox "Drag armies to the country you wish to reinforce" ', vbInformation
        Else
            AdvanceToNextPlayer
        End If
    End If
End Sub

Private Sub AdvanceToNextPlayer()
    EndTurnButton.Enabled = False
    If noHumanPlayers = True And PromptForNextTurn = True Then
        If MyMessageBox("Continue this game?", vbYesNo, "RISK") = vbNo Then
            Unload Me
        End If
    End If
    If CountryCaptured And Players(wPlayer).CardCount < 5 Then
        ' give player a risk card
        Dim c As Integer, cType As Long
        c = RiskCards(RiskCardIndex)
        GetCardType c, cType
        cards(wPlayer).CardType(Players(wPlayer).CardCount) = cType
        cards(wPlayer).wCard(Players(wPlayer).CardCount) = c
        Players(wPlayer).CardCount = Players(wPlayer).CardCount + 1
        PlayerInfoLabel(wPlayer).Caption = Players(wPlayer).CountryCount & " Countries, " & Players(wPlayer).CardCount & " Cards"
        If Players(wPlayer).IsPlayerHuman = True Then
            RiskCardForm.ShowFormGetRiskCard Players(wPlayer).CardCount, c
        Else
            MyMessageBox playerName(wPlayer) + " has received a risk card.", vbOKOnly, , 1000
        End If
        RiskCardIndex = RiskCardIndex + 1
        If RiskCardIndex = 44 Then RiskCardIndex = 0
    End If
    
    CallTurnComplete
    
    Do
        wPlayer = wPlayer + 1
        If wPlayer = nPlayers Then wPlayer = 0
    Loop While Players(wPlayer).IsPlayerAlive = False
    HighlightActivePlayer
    GamePhase = TurnPlacement
    DoGameAction
End Sub

Private Sub Form_Load()
    RiskBoardVC1.RefreshMap
End Sub

Private Sub Form_QueryUnload(Cancel As Integer, UnloadMode As Integer)
     If UnloadMode = vbFormControlMenu Then 'Or UnloadMode = vbAppWindows Then
        If MyMessageBox("Are you sure you would like to end this RISK game?", vbYesNo, "RISK") = vbNo Then Cancel = True
     End If
End Sub

Private Sub Form_Resize()
    If ScaleWidth > 5000 Then
        RiskBoardVC1.Width = ScaleWidth - 4215
    End If
    
    If ScaleHeight > 885 + MinBoxHeight Then
        If ScaleHeight > 4575 + MinBoxHeight Then
            Frame1.Height = ScaleHeight - 4575
            EndTurnButton.Top = ScaleHeight - 4540
        End If
        Image1.Top = EndTurnButton.Top + 550
        RiskBoardVC1.Height = ScaleHeight - 495
    End If
End Sub


Public Sub DoGameInitialization()
    
    Randomize ' seed random number generator
    
    Delay = 1#
    PromptForNextTurn = True
        
    ' I used this code to verify that the program knows the
    ' card types correctly
    'Dim y As Long
    'Dim e As Long
    'For y = 12 To 42
    '    GetCardType y, e
    '    If e = 1 Then
    '        MsgBox "Soldier"
    '    ElseIf e = 2 Then
    '        MsgBox "Horseman"
    '    ElseIf e = 3 Then
    '        MsgBox "Cannon"
    '    Else
    '        MsgBox "Error, card# " & y & " ctype = " & e
    '    End If
    '    RiskCardForm.ShowFormGetRiskCard 1, y
    'Next y
    
    For wPlayer = 0 To 5
        playerName(wPlayer) = ""
        PlayerDLLName(wPlayer) = ""
        Players(wPlayer).IsPlayerHuman = True
        Players(wPlayer).ArmyCount = 0
        Players(wPlayer).ArmiesToPlace = 0
        Players(wPlayer).CountryCount = 0
        Players(wPlayer).IsPlayerAlive = False
        Players(wPlayer).CardCount = 0
        PlayerColorIndex(wPlayer) = wPlayer
    Next wPlayer
    
    Dim curDirectory As String * 256
    
    GetCurrentDirectory 256, curDirectory
    NewPlayerForm.CommonDialog1.InitDir = curDirectory
    GameOptions.RndSeed.Text = CInt(Rnd * 1000 + 1)
    Sponsors.Show vbModal, Me
    CreateGame.Show vbModal, Me
    
    If CreateGame.result = False Then
        Unload Me
        Exit Sub
    End If
    SetCurrentDirectory curDirectory
    
    Randomize GameOptions.RndSeed.Text
    
    MinBoxHeight = 6135 - (6 - nPlayers) * 975
    
    Dim ACount As Integer
    Select Case nPlayers
    Case 2: ACount = 40
    Case 3: ACount = 35
    Case 4: ACount = 30
    Case 5: ACount = 25
    Case 6: ACount = 20
    End Select
    
    For wPlayer = 0 To 5
        Players(wPlayer).ArmiesToPlace = ACount
    Next wPlayer
    
    Dim nextHole As Integer, nextPlayer As Integer
    
    For nextHole = 0 To 5
        If Players(nextHole).IsPlayerAlive = False Then
            nextPlayer = nextHole
            For nextPlayer = nextHole + 1 To 5
                If Players(nextPlayer).IsPlayerAlive = True Then
                    SwapPlayers nextPlayer, nextHole
                    Exit For
                End If
            Next
        End If
    Next
    
    noHumanPlayers = True
    For nextHole = 0 To nPlayers - 1
        If Players(nextHole).IsPlayerHuman = True Then
            noHumanPlayers = False
            Exit For
        End If
    Next
    
    SetPlayerOrderForm.Show vbModal, Me
    
    For wPlayer = 0 To nPlayers - 1
        PlayerNameLabel(wPlayer).Caption = playerName(wPlayer)
        PlayerNameLabel(wPlayer).Visible = True
        PlayerInfoLabel(wPlayer).Caption = Players(wPlayer).CountryCount & " Countries, 0 Cards"
        PlayerInfoLabel(wPlayer).Visible = True
        ArmyImage(wPlayer) = LoadPicture(GetPlayerPictureFileName(PlayerColorIndex(wPlayer), True))
        ArmyImage(wPlayer).Visible = True
        ArmyCount(wPlayer).Visible = True
        ArmyCount(wPlayer).Caption = Players(wPlayer).ArmyCount
    Next wPlayer
    
    Dim wCard As Integer
    Dim cIndex As Integer

    Dim qcards(1 To 42) As Integer
    For wCard = 1 To 42
        qcards(wCard) = wCard
    Next
    
    wPlayer = 0
    Dim name As String
    Dim doSkip As Boolean
    
    For wCard = 42 To 1 Step -1
        HighlightActivePlayer
        cIndex = Int(Rnd() * wCard) + 1
        ' player wPlayer receives card at cIndex
        name = GetBasicCountryName(qcards(cIndex))
        Players(wPlayer).CountryCount = Players(wPlayer).CountryCount + 1
        Countries(qcards(cIndex)).OwnerID = wPlayer
        PlaceNewArmies wPlayer, qcards(cIndex), 1
        RiskBoardVC1.SetMapFocus qcards(cIndex)
        
        If Not doSkip And noHumanPlayers = False Then
            RiskCardForm.ShowFormDealRiskCard qcards(cIndex), playerName(wPlayer)
            doSkip = RiskCardForm.SkipAll
        End If
        
        qcards(cIndex) = qcards(wCard)
        wPlayer = wPlayer + 1
        If wPlayer = nPlayers Then wPlayer = 0
        RiskCards(wCard) = wCard
    Next wCard
    
    RiskCards(0) = 0   ' place wild cards in the deck
    RiskCards(43) = 0
    
    ' there are 44 risk cards in all, need to shuffle the deck, so to speak
    Dim wSwap As Integer, cardA As Integer, cardB As Integer, tempCard As Integer
    For wSwap = 1 To 1000
        cardA = Int(Rnd() * 44)
        cardB = Int(Rnd() * 44)
        tempCard = RiskCards(cardA)
        RiskCards(cardA) = RiskCards(cardB)
        RiskCards(cardB) = tempCard
    Next wSwap
    
    Dim c As Integer, cType As Long, j As Integer
    
    For wPlayer = 0 To nPlayers - 1
        'For j = 1 To 4
        '    c = RiskCards(RiskCardIndex)
        '    GetCardType c, cType
        '    cards(wPlayer).CardType(Players(wPlayer).CardCount) = cType
        '    cards(wPlayer).wCard(Players(wPlayer).CardCount) = c
        '    Players(wPlayer).CardCount = Players(wPlayer).CardCount + 1
        '    RiskCardIndex = RiskCardIndex + 1
        '    If RiskCardIndex = 44 Then RiskCardIndex = 0
        'Next j
        If Players(wPlayer).IsPlayerHuman = False Then
            SetDLLName wPlayer, PlayerDLLName(wPlayer)
        End If
    Next
    
    RiskBoardVC1.BoardMode = 0
    GamePhase = InitialPlacement
    wPlayer = 0
            
    If (InitializeDLL(Countries(0), wPlayer, nPlayers, Players(0), cards(0), nTradeInsDone, LastMove, 0, 0, 0) = 0) Then
        MyMessageBox "Failed to initialize manager DLL.  Program will terminate."
        End
    Else
        HighlightActivePlayer
        DoGameAction
    End If
End Sub

' used to place new armies on board
Public Sub PlaceNewArmies(ByVal pIndex As Integer, countryID As Integer, nArmies As Integer)
    If Countries(countryID).OwnerID = pIndex Then
        If nArmies < 0 Then
            CheckArmies
        End If
        Players(pIndex).ArmiesToPlace = Players(pIndex).ArmiesToPlace - nArmies
        Players(pIndex).ArmyCount = Players(pIndex).ArmyCount + nArmies
        ArmyCount(pIndex).Caption = Players(pIndex).ArmyCount
        PlayerInfoLabel(pIndex).Caption = Players(pIndex).CountryCount & " Countries, " & Players(pIndex).CardCount & " Cards"
        Countries(countryID).ArmyCount = Countries(countryID).ArmyCount + nArmies
        RiskBoardVC1.SetArmies countryID, PlayerColorIndex(pIndex), Countries(countryID).ArmyCount
    End If
End Sub

Private Function IsCardUsed(wCard As Integer) As Boolean
    IsCardUsed = False
    Dim i As Integer
    For i = 0 To 2
        If cards(wPlayer).wCard(wCard) = TradeInForm.GetTradeInCard(i) Then
            IsCardUsed = True
            Exit Function
        End If
    Next i
End Function

Private Sub RemoveUsedCards()
    Dim pos As Integer, unusedPos As Integer, unusedFound As Boolean
    For pos = 0 To Players(wPlayer).CardCount - 1
        If IsCardUsed(pos) = True Then
            unusedFound = False
            For unusedPos = pos + 1 To Players(wPlayer).CardCount - 1
                If IsCardUsed(unusedPos) = False Then
                    unusedFound = True
                    Exit For
                End If
            Next
            If unusedFound = True Then
                Dim cType As Long, wCard As Long
                cType = cards(wPlayer).CardType(pos)
                wCard = cards(wPlayer).wCard(pos)
                cards(wPlayer).CardType(pos) = cards(wPlayer).CardType(unusedPos)
                cards(wPlayer).wCard(pos) = cards(wPlayer).wCard(unusedPos)
                cards(wPlayer).CardType(unusedPos) = cType
                cards(wPlayer).wCard(unusedPos) = wCard
            End If
        End If
    Next
    Players(wPlayer).CardCount = Players(wPlayer).CardCount - 3
End Sub

Private Sub HandleTradeIn(ByRef ArmiesToPlace As Long)
' determine if player can do a trade in.  if so, present him/her with that option...
    Do While Players(wPlayer).CardCount > 2
        GamePhase = TradeIn
        Dim i As Integer, nCards As Integer
        nCards = 8
        If Players(wPlayer).CardCount < nCards Then nCards = Players(wPlayer).CardCount
        
        For i = 0 To nCards - 1
            TradeInForm.SetCard i, cards(wPlayer).wCard(i)
        Next i
        TradeInForm.ShowForm nCards, Players(wPlayer).IsPlayerHuman
        ' shows the form modally...
        If TradeInForm.result = True Then
            If Players(wPlayer).IsPlayerHuman = False Then
                MyMessageBox playerName(wPlayer) & " has made a trade-in.", , "RISK", 1500
            End If
            RemoveUsedCards
            ArmiesToPlace = ArmiesToPlace + GetNextTradeInValue()
            nTradeInsDone = nTradeInsDone + 1
            If TradeInForm.CountryCardSelected <> 0 Then
                PlaceNewArmies wPlayer, TradeInForm.CountryCardSelected, 2
            End If
        Else
            Exit Do
        End If
    Loop
    
    GamePhase = TurnPlacement
End Sub

Private Sub CompPlaceInitialArmies()
    ' do comp sub
    ' call comp sub to place armies initially
    Dim wCountry, nArmies As Long
    Do While currentArmiesToPlace > 0
        If CallPlaceArmiesAtStart(currentArmiesToPlace, wCountry, nArmies) = False Then
            MyMessageBox "CallPlaceArmiesAtStart returned False"
            ReleaseAndEnd
        End If
        If nArmies > currentArmiesToPlace Then
            nArmies = currentArmiesToPlace
        ElseIf nArmies <= 0 Then
            MyMessageBox "Error, computer decided to place 0 armies"
            nArmies = 0
        ElseIf wCountry < 1 Or wCountry > 42 Then
            MyMessageBox "Error, computer decided to place armies on an invalid country id.  (country=" & wCountry & ")"
        ElseIf Countries(wCountry).OwnerID <> wPlayer Then
            MyMessageBox "Error, computer decided to place armies on a country it does not own."
        End If
        If nArmies < currentArmiesToPlace Then
            AttemptToPlaceArmies wCountry, nArmies
        Else
            AttemptToPlaceArmies wCountry, nArmies
            Exit Do
        End If
    Loop
End Sub

Public Sub DoComputerTurn()
    Dim FromWhere, ToWhere, nArmies, result, wCountry, AttackWhere As Long
    
    If GamePhase = TurnPlacement Then
        Do While currentArmiesToPlace > 0
            If CallPlaceArmies(currentArmiesToPlace, wCountry, nArmies) = False Then
                MyMessageBox "CallPlaceArmies returned False"
                ReleaseAndEnd
            End If
            If nArmies > currentArmiesToPlace Then
                nArmies = currentArmiesToPlace
            ElseIf nArmies <= 0 Then
                MyMessageBox "Error, computer decided to place 0 armies"
                nArmies = 0
            End If
            
            If wCountry < 1 Or wCountry > 42 Then
                MyMessageBox "Error, computer decided to place armies on an invalid country id.  (country=" & wCountry & ")"
            ElseIf Countries(wCountry).OwnerID <> wPlayer Then
                MyMessageBox "Error, computer decided to place armies on a country it does not own."
            Else
                AttemptToPlaceArmies wCountry, nArmies
            End If
        Loop
        GamePhase = attack
        LastMove.LastAction = NoMove
        DoComputerTurn
    ElseIf GamePhase = attack Then
        ' make all attacks
        Do While Players(wPlayer).CountryCount < 42
            
            If CallMakeMove(AttackWhere, FromWhere, nArmies, result) = False Then
                MyMessageBox "CallMakeMove returned False"
                ReleaseAndEnd
                Exit Do
            End If
            
            If result = 0 Then
                GamePhase = Reinforcement
                DoComputerTurn
                Exit Do
            Else
                ' check the validity of the attack
                result = GetAttackError(FromWhere, AttackWhere)
                RiskBoardVC1.SetMapFocus AttackWhere
                If result = 0 Then
                    attackCountry FromWhere, AttackWhere, nArmies
                Else
                    MyMessageBox "Invalid Attack: " + GetRiskErrorDescription(result) + _
                        ", Computer tried to attack " + _
                        GetBasicCountryName(AttackWhere) + " from " + _
                        GetBasicCountryName(FromWhere) + " with " + Str(nArmies) + " armie(s)"
                    GamePhase = Reinforcement
                    DoComputerTurn
                    Exit Do
                End If
            End If
            
        Loop
    ElseIf GamePhase = Reinforcement Then
        If CallDoReinforcement(FromWhere, ToWhere, nArmies, result) = False Then
            MyMessageBox "CallDoReinforcement returned False"
            ReleaseAndEnd
        End If
        
        If result <> 0 Then
            If FromWhere < 1 Or FromWhere > 42 Or ToWhere < 1 Or ToWhere > 42 Then
                MyMessageBox "Error - computer returned an invalid countryID.  FromWhere = " + FromWhere + ", ToWhere = " + ToWhere, vbExclamation, "Error"
            ElseIf Countries(FromWhere).OwnerID <> wPlayer Then
                MyMessageBox "Error - computer tried to make a reinforcement from country " + FromWhere + " (" + GetBasicCountryName(FromWhere) + ") which they do not own.", vbExclamation, "Error"
            ElseIf Countries(ToWhere).OwnerID <> wPlayer Then
                MyMessageBox "Error - computer tried to make a reinforcement to country " + ToWhere + " (" + GetBasicCountryName(ToWhere) + ") which they do not own.", vbExclamation, "Error"
            ElseIf Countries(FromWhere).ArmyCount < 2 Then
                MyMessageBox "Error - computer tried to make a reinforcement from a country with one army.  CountryID = " + FromWhere + " (" + GetBasicCountryName(FromWhere), vbExclamation, "Error"
            ElseIf nArmies < 1 Then
                MyMessageBox "DoReinforcement returned true and computer requested to move " + nArmies + " as a reinforcement.", vbExclamation, "Error"
            ElseIf AreCountriesAdjacent(FromWhere, ToWhere) = 0 Then
                MyMessageBox "Error - computer tried to reinforce armies between non-adjacent countries. (" + GetBasicCountryName(FromWhere) + ", " + GetBasicCountryName(ToWhere), vbExclamation, "Error"
            Else
                If nArmies >= Countries(FromWhere).ArmyCount Then
                    nArmies = Countries(FromWhere).ArmyCount - 1
                End If
                CheckArmies
                DoReinforcement nArmies, FromWhere, ToWhere
                RiskBoardVC1.SetMapFocus (ToWhere)
                MyMessageBox playerName(wPlayer) & " has made a reinforcement to " + GetBasicCountryName(ToWhere), , , 1000
            End If
            
        End If
        AdvanceToNextPlayer
    End If
End Sub

Sub DoPlacement(ArmiesToPlace As Long)
    GamePhase = TurnPlacement
    RiskBoardVC1.BoardMode = 0
    PlaceArmiesForm.SetPlayer wPlayer, playerName(wPlayer)
    currentArmiesToPlace = ArmiesToPlace
    PlaceArmiesForm.SetArmiesRemaining (ArmiesToPlace)
    PlaceArmiesForm.Show vbModeless, Me
    If Not Players(wPlayer).IsPlayerHuman Then
        DoComputerTurn
    End If
End Sub

Sub DoGameAction()

    Dim nArmies As Long, wCountry As Long
    If GamePhase = InitialPlacement Then
        Dim ACount As Integer
        ACount = Players(wPlayer).ArmiesToPlace
        If ACount > 5 Then ACount = 5
        
        If ACount > 0 Then
            PlaceArmiesForm.SetPlayer wPlayer, playerName(wPlayer)
            currentArmiesToPlace = ACount
            PlaceArmiesForm.SetArmiesRemaining (ACount)
            PlaceArmiesForm.Show vbModeless, Me
            If Players(wPlayer).IsPlayerHuman = False Then
                CompPlaceInitialArmies
            End If
        Else
            ContinueInitialPlacement
        End If
    ElseIf GamePhase = TurnPlacement Then
        Dim ArmiesToPlace As Long
        ArmiesToPlace = 0
        CalculateArmiesToPlace wPlayer, ArmiesToPlace
        CountryCaptured = False
        HandleTradeIn ArmiesToPlace
        DoPlacement ArmiesToPlace
    End If
End Sub

Private Sub ContinueInitialPlacement()
    ' check to see if all players have no armies to place
    Dim i As Integer, playerFound As Boolean
    For i = 1 To nPlayers - 1
        If Players((wPlayer + i) Mod nPlayers).ArmiesToPlace > 0 Then
            wPlayer = (wPlayer + i) Mod nPlayers
            HighlightActivePlayer
            playerFound = True
            DoGameAction
        End If
    Next i
    
    If Not playerFound Then
        wPlayer = 0
        HighlightActivePlayer
        GamePhase = TurnPlacement
        PlaceArmiesForm.Hide
        DoGameAction
    End If
End Sub

Private Function AttemptToPlaceArmies(ByVal countryID As Integer, ByVal dArmies As Integer) As Boolean
    ' called during place armies
    If countryID < 1 Or countryID > 42 Then
        MyMessageBox "You may not place armies there.  You do not own this country." ', vbInformation
    ElseIf Countries(countryID).OwnerID <> wPlayer Then
        MyMessageBox "You may not place armies there.  You do not own this country." ', vbInformation
    Else
        If currentArmiesToPlace > 0 Then
            If dArmies > currentArmiesToPlace Then dArmies = currentArmiesToPlace
            PlaceNewArmies wPlayer, countryID, dArmies
            currentArmiesToPlace = currentArmiesToPlace - dArmies
            RiskBoardVC1.RefreshMap
            PlaceArmiesForm.SetArmiesRemaining currentArmiesToPlace
        End If
        
        If Players(wPlayer).IsPlayerHuman = False Then
            If currentArmiesToPlace = 0 Then PlaceArmiesForm.Hide
            RiskBoardVC1.SetMapFocus countryID
            MyMessageBox playerName(wPlayer) & " has placed armies in " & GetBasicCountryName(countryID), , , 1000
        End If
        
        If currentArmiesToPlace = 0 Then
            If GamePhase = InitialPlacement Then
                wPlayer = wPlayer + 1
                If wPlayer = nPlayers Then wPlayer = 0
                HighlightActivePlayer
                PlaceArmiesForm.Hide
                DoGameAction
            ElseIf GamePhase = TurnPlacement Then
                GamePhase = attack
                RiskBoardVC1.BoardMode = 1
                PlaceArmiesForm.Hide
                If Players(wPlayer).IsPlayerHuman Then
                    MyMessageBox "You may now attack countries by dragging from one country to the country you wish to attack"
                Else
                    If Players(wPlayer).IsPlayerHuman = False Then
                        MyMessageBox "I am now preparing to attack...", , , 1000
                    End If
                End If
                EndTurnButton.Enabled = True
            Else
                MyMessageBox "Error, Country_Click called when gamephase <> 0 and gamephase <> 1"
            End If
        End If
    End If
End Function

Private Sub Form_Unload(Cancel As Integer)
    ReleaseAndEnd
End Sub

Private Sub RiskBoardVC1_CountryClick(ByVal countryID As Integer, ByVal ShiftDown As Integer)
    If GamePhase = InitialPlacement Or GamePhase = TurnPlacement And Players(wPlayer).IsPlayerHuman Then
        Dim dArmies As Integer
        If ShiftDown = True Then
            dArmies = 5
        Else
            dArmies = 1
        End If
        
        If dArmies > currentArmiesToPlace Then dArmies = currentArmiesToPlace
        AttemptToPlaceArmies countryID, dArmies
    End If
End Sub

Private Sub attackCountry(ByVal CountryA As Integer, ByVal CountryB As Integer, Optional ByVal nDiceToRoll As Long = 0)
    
    Dim DefenderID As Long
    DefenderID = Countries(CountryB).OwnerID
       
    Dim checkA As Integer, checkD As Integer
    checkA = Countries(CountryA).ArmyCount - 1
    checkD = Countries(CountryB).ArmyCount
    CheckArmies
    
    AttackForm.SetInfo GetBasicCountryName(CountryB), _
        playerName(wPlayer), _
        playerName(DefenderID), _
        PlayerColorIndex(wPlayer), _
        PlayerColorIndex(DefenderID), _
        CountryA, _
        CountryB, _
        nDiceToRoll
        
        'Countries(CountryA),
        'Countries(CountryB),
        'Players(wPlayer),
        'Players(DefenderID),
        'DefenderID,

    AttackForm.Show vbModal, Me
    'CheckArmies
    
    If AttackForm.ACount < 0 Then
        MyMessageBox "AttackForm.ACount < 0", , "Error"
    End If
    'If AttackForm.TotalADead > checkA Then
    '    MyMessageBox "AttackForm.TotalADead > checkA", , "Error"
    'End If
    If AttackForm.DCount < 0 Then
        MyMessageBox "AttackForm.DCount < 0", , "Error"
    End If
    'If AttackForm.TotalDDead > checkD Then
    '    MyMessageBox "AttackForm.TotalDDead > checkD", , "Error"
    'End If
    
    'Players(wPlayer).ArmyCount = Players(wPlayer).ArmyCount - AttackForm.TotalADead
    'Players(DefenderID).ArmyCount = Players(DefenderID).ArmyCount - AttackForm.TotalDDead
    
    If AttackForm.ACount = 0 Then
        ' attacker must have died
        'Countries(CountryA).ArmyCount = 1
        'Countries(CountryB).ArmyCount = Countries(CountryB).ArmyCount - AttackForm.TotalDDead
        CheckArmies
    ElseIf AttackForm.DCount = 0 Then
        ' defender must have died
        Dim menToMove As Integer
        If AttackForm.ACommitted <> AttackForm.ACount Then
            If Players(wPlayer).IsPlayerHuman Then
                MoveArmiesForm.formType = 0
                MoveArmiesForm.minArmies = AttackForm.ACommitted
                MoveArmiesForm.maxArmies = AttackForm.ACount
                
                MoveArmiesForm.CountryName = GetBasicCountryName(CountryB)
                MoveArmiesForm.ShowForm
                menToMove = MoveArmiesForm.ArmiesToMove
            Else
                Dim mMove As Long
                If CallCaptureCountry(CountryA, CountryB, AttackForm.ACommitted, AttackForm.ACount, mMove) = False Then
                    MyMessageBox "CallCaptureCountry returned False"
                    ReleaseAndEnd
                End If
                menToMove = mMove
                ' do some validation
                If menToMove < AttackForm.ACommitted Then
                    menToMove = AttackForm.ACommitted
                ElseIf menToMove > AttackForm.ACount Then
                    menToMove = AttackForm.ACount
                End If
                If menToMove < 1 Then
                    MyMessageBox "menToMove < 1", , "Error"
                End If
            End If
        Else
            menToMove = AttackForm.ACommitted
        End If
        Countries(CountryA).ArmyCount = 1 + AttackForm.ACount - menToMove
        'CheckArmies
        Countries(CountryB).ArmyCount = menToMove
        CheckArmies
        If Countries(CountryA).ArmyCount < 1 Or Countries(CountryB).ArmyCount < 1 Then
            MyMessageBox "Error: Armies in a country < 1"
        End If
        Countries(CountryB).OwnerID = wPlayer
        Players(wPlayer).CountryCount = Players(wPlayer).CountryCount + 1
        Players(DefenderID).CountryCount = Players(DefenderID).CountryCount - 1
        CountryCaptured = True
        If Players(DefenderID).CountryCount = 0 Then
            ' this player has been destroyed... fork over the risk cards
            If Players(wPlayer).IsPlayerHuman = False Then
                MyMessageBox playerName(DefenderID) & " has been destroyed.  " & Players(DefenderID).CardCount & " risk card(s) have been captured.", vbOKOnly, "Victory!", 1000
            Else
                MyMessageBox playerName(DefenderID) & " has been destroyed.  " & Players(DefenderID).CardCount & " risk card(s) have been captured.", vbOKOnly, "Victory!"
            End If
            Dim wCard As Integer
            For wCard = 0 To Players(DefenderID).CardCount - 1
                cards(wPlayer).CardType(Players(wPlayer).CardCount) = cards(DefenderID).CardType(wCard)
                cards(wPlayer).wCard(Players(wPlayer).CardCount) = cards(DefenderID).wCard(wCard)
                Players(wPlayer).CardCount = Players(wPlayer).CardCount + 1
            Next wCard
            ArmyImage(DefenderID).Visible = False
            PlayerNameLabel(DefenderID).FontStrikethru = True
            PlayerInfoLabel(DefenderID).Visible = False
                
            Players(DefenderID).IsPlayerAlive = False
        End If
    Else
        ' player must have retreated
        If AttackForm.ACount < 0 Then
            MyMessageBox "AttackForm.ACount < 0"
        End If
        'Countries(CountryA).ArmyCount = 1 + AttackForm.ACount
        'CheckArmies
        'If Countries(CountryB).ArmyCount - AttackForm.TotalDDead < 1 Then
        '    MyMessageBox "Countries(CountryB).ArmyCount - AttackForm.TotalDDead < 1", , "Error"
        'End If
        'Countries(CountryB).ArmyCount = Countries(CountryB).ArmyCount - AttackForm.TotalDDead
        'CheckArmies
    End If
    
    RiskBoardVC1.SetArmies CountryA, PlayerColorIndex(Countries(CountryA).OwnerID), Countries(CountryA).ArmyCount
    'CheckArmies
    RiskBoardVC1.SetArmies CountryB, PlayerColorIndex(Countries(CountryB).OwnerID), Countries(CountryB).ArmyCount
    'CheckArmies
    RiskBoardVC1.RefreshMap
    PlayerInfoLabel(wPlayer).Caption = Players(wPlayer).CountryCount & " Countries, " & Players(wPlayer).CardCount & " Cards"
    PlayerInfoLabel(DefenderID).Caption = Players(DefenderID).CountryCount & " Countries, " & Players(DefenderID).CardCount & " Cards"
    ArmyCount(wPlayer).Caption = Players(wPlayer).ArmyCount
    ArmyCount(DefenderID).Caption = Players(DefenderID).ArmyCount
    
    If Players(wPlayer).CountryCount = 42 Then
        ' player has just won the game
        DoGameEnd
    Else
        If Players(wPlayer).CardCount > 5 Then
            ' got to do a trade in now
            Dim ArmiesToPlace As Long
            ArmiesToPlace = 0
            Do While Players(wPlayer).CardCount > 4
                HandleTradeIn ArmiesToPlace
            Loop
            DoPlacement ArmiesToPlace
        End If
    End If
        
End Sub

Private Sub DoGameEnd()
    MyMessageBox playerName(wPlayer) & " is the victor!"
    ReleaseAndEnd
End Sub

Private Sub DoReinforcement(ByVal nArmiesToMove, ByVal CountryA As Integer, ByVal CountryB As Integer)
    Countries(CountryA).ArmyCount = Countries(CountryA).ArmyCount - nArmiesToMove
    CheckArmies
    Countries(CountryB).ArmyCount = Countries(CountryB).ArmyCount + nArmiesToMove
    CheckArmies
    RiskBoardVC1.SetArmies CountryA, PlayerColorIndex(wPlayer), Countries(CountryA).ArmyCount
    CheckArmies
    RiskBoardVC1.SetArmies CountryB, PlayerColorIndex(wPlayer), Countries(CountryB).ArmyCount
    CheckArmies
    RiskBoardVC1.RefreshMap
End Sub

Private Sub RiskBoardVC1_DragToCountry(ByVal CountryA As Integer, ByVal CountryB As Integer)
    
    If Players(wPlayer).IsPlayerHuman = False Then Exit Sub
    
    If GamePhase = attack Then
        If Countries(CountryA).OwnerID = wPlayer Then
            If CountryA = CountryB Then
                ' do nothing
            ElseIf (AreCountriesAdjacent(CountryA, CountryB) = 0) Then
                MyMessageBox "You may not attack a country which is not adjacent to the country you are attacking from."
            ElseIf Countries(CountryB).OwnerID = wPlayer Then
                MyMessageBox "You may not attack your own country"
            ElseIf Countries(CountryA).ArmyCount > 1 Then
                attackCountry CountryA, CountryB
                CheckArmies
            Else
                MyMessageBox "You may not attack from a country in which you have only 1 army."
            End If
        End If
    ElseIf GamePhase = Reinforcement Then
        If Countries(CountryA).OwnerID = wPlayer And Countries(CountryA).ArmyCount > 1 Then
            If Countries(CountryB).OwnerID = wPlayer Then
                If AreCountriesAdjacent(CountryA, CountryB) = 0 Then
                    MyMessageBox "You may only make a reinforcement between adjacent countries."
                Else
                    MoveArmiesForm.formType = 1
                    MoveArmiesForm.minArmies = 0
                    MoveArmiesForm.maxArmies = Countries(CountryA).ArmyCount - 1
                    MoveArmiesForm.CountryName = GetBasicCountryName(CountryB)
                    MoveArmiesForm.ShowForm
                    DoReinforcement MoveArmiesForm.ArmiesToMove, CountryA, CountryB
                    AdvanceToNextPlayer
                End If
            Else
                MyMessageBox "You may only make a reinforcement from a country you own with at least two men to any adjacent country you own" ', vbInformation
            End If
        Else
            MyMessageBox "You may only make a reinforcement from a country you own with at least two men to any adjacent country you own" ', vbInformation
        End If
    End If
End Sub

Public Function GetBasicCountryName(ByVal countryID As Integer) As String
    If countryID < 1 Or countryID > 42 Then
        GetBasicCountryName = "[Invalid Country " + Str(countryID) + "]"
        Exit Function
    End If
    Dim cName As String * 100
    GetCountryName countryID, cName
    Dim t As String, p As Integer
    t = cName
    For p = 1 To Len(cName)
        If Mid(t, p, 1) = Chr$(0) Then
            GetBasicCountryName = Mid(t, 1, p - 1)
            Exit Function
        End If
    Next p
    GetBasicCountryName = cName
End Function

Public Sub SetStartPlayerInfo(IsHuman As Boolean, name As String, DLLPath As String, ColorIndex As Integer)
    'Dim i As Integer
    'For i = 49 To 1 Step -1
    '    If Mid$(name, i, 1) <> " " Then
    '        name = Left(name, i) & Chr$(0)
    '        Exit For
    '    End If
    'Next i
            
    Players(ColorIndex).IsPlayerAlive = True
    playerName(ColorIndex) = name
    If IsHuman = False Then
        PlayerDLLName(ColorIndex) = DLLPath
    Else
        PlayerDLLName(ColorIndex) = ""
    End If
    Players(ColorIndex).IsPlayerHuman = IsHuman
End Sub

Public Function IsDLLPathInUse(Path As String) As Boolean
    Dim i As Integer
    For i = 0 To 5
        If Path = PlayerDLLName(i) Then
            IsDLLPathInUse = True
            Exit Function
        End If
    Next i
    IsDLLPathInUse = False
End Function

Public Sub DeleteStartPlayer(ColorIndex As Integer)
    Players(ColorIndex).IsPlayerAlive = False
End Sub

Public Sub SwapPlayers(Player1 As Integer, Player2 As Integer)
    Dim temp As PLAYER_INFO
    temp = Players(Player1)
    Players(Player1) = Players(Player2)
    Players(Player2) = temp
    
    Dim temp1 As Integer
    temp1 = PlayerColorIndex(Player1)
    PlayerColorIndex(Player1) = PlayerColorIndex(Player2)
    PlayerColorIndex(Player2) = temp1
    
    Dim tempString As String
    tempString = playerName(Player1)
    playerName(Player1) = playerName(Player2)
    playerName(Player2) = tempString
    
    tempString = PlayerDLLName(Player1)
    PlayerDLLName(Player1) = PlayerDLLName(Player2)
    PlayerDLLName(Player2) = tempString
    
End Sub

