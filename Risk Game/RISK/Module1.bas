Attribute VB_Name = "Module1"
Option Explicit

' If this code works it was written by Mark Salisbury, otherwise it was written by someone else

Private Declare Sub ReleaseDLLs Lib "ManagerDLL" ()

'Public fMainForm As MainForm
Public nPlayers As Long
Public wPlayer As Long
Public nTradeInsDone As Long
Public noHumanPlayers As Boolean
Public currentArmiesToPlace As Integer
Public Delay As Double
Public PromptForNextTurn As Boolean
Public frmMain As MainForm

Public Type COUNTRY_DATA
    OwnerID As Long
    ArmyCount As Long
End Type

Public Type PLAYER_INFO
    IsPlayerHuman As Long
    ArmyCount As Long
    ArmiesToPlace As Long
    CountryCount As Long
    IsPlayerAlive As Long
    CardCount As Long
End Type

Public Type LAST_MOVE_INFO
    LastAction As LastMoveEnum
    FromID As Long
    ToID As Long
End Type

Public Enum LastMoveEnum
    NoMove = 0
    MadeAttack = 1
    Retreat = 2
    CapturedCountry = 3
    Defeat = 4
End Enum

Public Type COUNTRY_INFO
    OwnerID As Long
    ArmyCount As Long
    AdjacentCountries As Long
    EnemyOwnedAdjacentCountries As Long
    ContinentID As Long
End Type

Public Type CARD_DATA
    wCard(0 To 9) As Long
    CardType(0 To 9) As Long ' 0 = wild, 1 = soldier, 2 = horse, 3 = cannon
End Type

Sub Main()
      
    frmSplash.Show vbModal
    Set frmMain = MainForm
    frmMain.Show
    frmMain.DoGameInitialization
    
End Sub

Public Function GetPlayerPictureFileName(index As Integer, hasBox As Boolean) As String
    Select Case index
        Case 0: If hasBox Then GetPlayerPictureFileName = "Soldier Blue 24 bit.bmp" Else GetPlayerPictureFileName = "Soldier 1 Blue 24 bit.bmp"
        Case 1: If hasBox Then GetPlayerPictureFileName = "Soldier Red 24 bit.bmp" Else GetPlayerPictureFileName = "Soldier 1 Red 24 bit.bmp"
        Case 2: If hasBox Then GetPlayerPictureFileName = "Soldier Yellow 24 bit.bmp" Else GetPlayerPictureFileName = "Soldier 1 Yellow 24 bit.bmp"
        Case 3: If hasBox Then GetPlayerPictureFileName = "Soldier Green 24 bit.bmp" Else GetPlayerPictureFileName = "Soldier 1 Green 24 bit.bmp"
        Case 4: If hasBox Then GetPlayerPictureFileName = "Soldier Purple 24 bit.bmp" Else GetPlayerPictureFileName = "Soldier 1 Purple 24 bit.bmp"
        Case 5: If hasBox Then GetPlayerPictureFileName = "Soldier Black 24 bit.bmp" Else GetPlayerPictureFileName = "Soldier 1 Black 24 bit.bmp"
    End Select
End Function

Public Function MyMessageBox(Prompt As String, Optional Buttons As VbMsgBoxStyle = vbOKOnly, Optional Title As Variant, Optional miliseconds As Variant) As VbMsgBoxResult
    If IsMissing(Title) Then Title = "Risk"
    Dim t As String
    t = Title
    MyMessageForm.ShowForm Prompt, t, Buttons, miliseconds
    MyMessageBox = MyMessageForm.result
End Function

Public Function ReleaseAndEnd()
    ReleaseDLLs
    End
End Function

Public Function GetRiskErrorDescription(ByVal errCode As Long) As String
    Select Case errCode
        Case 0:
            GetRiskErrorDescription = "No error"
        Case 1:
            GetRiskErrorDescription = "Out of bounds error."
        Case 2:
            GetRiskErrorDescription = "Can't attack from a country you don't own."
        Case 3:
            GetRiskErrorDescription = "Can't attack a country you do own."
        Case 4:
            GetRiskErrorDescription = "Specified countries are not adjacent."
        Case 5:
            GetRiskErrorDescription = "Cannot place armies there.  You do not own specified country."
        Case 6:
            GetRiskErrorDescription = "Failed to load player DLL"
        Case 7:
            GetRiskErrorDescription = "Failed to load procedure within player DLL"
        Case 8:
            GetRiskErrorDescription = "Attack is not valid because attacker does not have enough armies to attack."
        Case Else
            GetRiskErrorDescription = "Error Number " + Str(errCode)
    End Select
    
End Function



