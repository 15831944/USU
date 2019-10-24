VERSION 5.00
Begin VB.Form SetPlayerOrderForm 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Set Player Order"
   ClientHeight    =   4695
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   3840
   ControlBox      =   0   'False
   BeginProperty Font 
      Name            =   "Arial"
      Size            =   15.75
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4695
   ScaleWidth      =   3840
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin VB.Timer Timer1 
      Enabled         =   0   'False
      Interval        =   1500
      Left            =   3240
      Top             =   3960
   End
   Begin VB.CommandButton RollButton 
      Caption         =   "Roll"
      Height          =   495
      Index           =   5
      Left            =   2400
      TabIndex        =   18
      Top             =   3240
      Width           =   1095
   End
   Begin VB.CommandButton RollButton 
      Caption         =   "Roll"
      Height          =   495
      Index           =   4
      Left            =   2400
      TabIndex        =   17
      Top             =   2640
      Width           =   1095
   End
   Begin VB.CommandButton RollButton 
      Caption         =   "Roll"
      Height          =   495
      Index           =   3
      Left            =   2400
      TabIndex        =   16
      Top             =   2040
      Width           =   1095
   End
   Begin VB.CommandButton RollButton 
      Caption         =   "Roll"
      Height          =   495
      Index           =   2
      Left            =   2400
      TabIndex        =   15
      Top             =   1440
      Width           =   1095
   End
   Begin VB.CommandButton RollButton 
      Caption         =   "Roll"
      Height          =   495
      Index           =   1
      Left            =   2400
      TabIndex        =   14
      Top             =   840
      Width           =   1095
   End
   Begin VB.CommandButton RollButton 
      Caption         =   "Roll"
      Height          =   495
      Index           =   0
      Left            =   2400
      TabIndex        =   13
      Top             =   240
      Width           =   1095
   End
   Begin VB.TextBox DiceText 
      BackColor       =   &H80000004&
      Height          =   495
      Index           =   5
      Left            =   2400
      Locked          =   -1  'True
      TabIndex        =   12
      Top             =   3240
      Visible         =   0   'False
      Width           =   1095
   End
   Begin VB.TextBox DiceText 
      BackColor       =   &H80000004&
      Height          =   495
      Index           =   4
      Left            =   2400
      Locked          =   -1  'True
      TabIndex        =   11
      Top             =   2640
      Visible         =   0   'False
      Width           =   1095
   End
   Begin VB.TextBox DiceText 
      BackColor       =   &H80000004&
      Height          =   495
      Index           =   3
      Left            =   2400
      Locked          =   -1  'True
      TabIndex        =   10
      Top             =   2040
      Visible         =   0   'False
      Width           =   1095
   End
   Begin VB.TextBox DiceText 
      BackColor       =   &H80000004&
      Height          =   495
      Index           =   2
      Left            =   2400
      Locked          =   -1  'True
      TabIndex        =   9
      Top             =   1440
      Visible         =   0   'False
      Width           =   1095
   End
   Begin VB.TextBox DiceText 
      BackColor       =   &H80000004&
      Height          =   495
      Index           =   1
      Left            =   2400
      Locked          =   -1  'True
      TabIndex        =   8
      Top             =   840
      Visible         =   0   'False
      Width           =   1095
   End
   Begin VB.TextBox DiceText 
      BackColor       =   &H80000004&
      Height          =   495
      Index           =   0
      Left            =   2400
      Locked          =   -1  'True
      TabIndex        =   7
      Top             =   240
      Visible         =   0   'False
      Width           =   1095
   End
   Begin VB.CommandButton PlayGameButton 
      Caption         =   "Play Game"
      Enabled         =   0   'False
      Height          =   495
      Left            =   720
      TabIndex        =   6
      Top             =   3960
      Width           =   2295
   End
   Begin VB.Label NameLabel 
      Caption         =   "Label1"
      Height          =   375
      Index           =   5
      Left            =   240
      TabIndex        =   5
      Top             =   3240
      Width           =   1935
   End
   Begin VB.Label NameLabel 
      Caption         =   "Label1"
      Height          =   375
      Index           =   4
      Left            =   240
      TabIndex        =   4
      Top             =   2640
      Width           =   1935
   End
   Begin VB.Label NameLabel 
      Caption         =   "Label1"
      Height          =   375
      Index           =   3
      Left            =   240
      TabIndex        =   3
      Top             =   2040
      Width           =   1935
   End
   Begin VB.Label NameLabel 
      Caption         =   "Label1"
      Height          =   375
      Index           =   2
      Left            =   240
      TabIndex        =   2
      Top             =   1440
      Width           =   1935
   End
   Begin VB.Label NameLabel 
      Caption         =   "Label1"
      Height          =   375
      Index           =   1
      Left            =   240
      TabIndex        =   1
      Top             =   840
      Width           =   1935
   End
   Begin VB.Label NameLabel 
      Caption         =   "Label1"
      Height          =   375
      Index           =   0
      Left            =   240
      TabIndex        =   0
      Top             =   240
      Width           =   1935
   End
End
Attribute VB_Name = "SetPlayerOrderForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim nRolls As Integer
Dim PositionKnown(0 To 5) As Boolean

Private Sub Form_Load()
    Dim i As Integer
    
    For i = 0 To nPlayers - 1
        NameLabel(i).Caption = MainForm.GetPlayerName(i)
    Next i
    
    For i = i To 5
        NameLabel(i).Visible = False
        RollButton(i).Visible = False
    Next i
    
    ' roll automatically for computer players
    For i = 0 To nPlayers - 1
        If MainForm.GetPlayerIsHuman(i) = False Then
            RollButton_Click (i)
        End If
        PositionKnown(i) = False
    Next i
    If noHumanPlayers = True Then Timer1.Enabled = True
End Sub

Private Sub PlayGameButton_Click()
    Me.Hide
End Sub

Private Sub RollButton_Click(index As Integer)
    RollButton(index).Visible = False
    DiceText(index).Visible = True
    DiceText(index) = Int(Rnd() * 6) + 1
    nRolls = nRolls + 1
    
    ' see if all rolling is complete
    Dim i As Integer, moreRolls As Boolean
    For i = 0 To nPlayers - 1
        If DiceText(i).Visible = False Then
            moreRolls = True
            Exit Sub
        End If
    Next i
    
    Timer1.Enabled = True
    
End Sub

Private Sub RollsComplete()
    ' put the players in order according to highest rolls,
    ' then restore the roll button for any tie rolls
    Dim highestRollIndex As Integer, highestRoll As Integer, p As Integer, i As Integer, moreRolls As Boolean
    
    For p = 0 To nPlayers - 2
        If PositionKnown(p) = False Then
            highestRoll = Val(DiceText(p).Text)
            highestRollIndex = p
            For i = p + 1 To nPlayers - 1
                If PositionKnown(i) = False Then
                    If Val(DiceText(i).Text) > highestRoll Then
                        highestRoll = Val(DiceText(i).Text)
                        highestRollIndex = i
                    End If
                End If
            Next i
            If p <> highestRollIndex Then
                MainForm.SwapPlayers p, highestRollIndex
                Dim value As Integer, namel As String
                value = Val(DiceText(p).Text)
                namel = NameLabel(p)
                DiceText(p) = DiceText(highestRollIndex)
                NameLabel(p) = NameLabel(highestRollIndex)
                DiceText(highestRollIndex) = value
                NameLabel(highestRollIndex) = namel
            End If
        End If
    Next p
    
    If DiceText(0) <> DiceText(1) Then PositionKnown(0) = True
    
    For p = 1 To nPlayers - 1
        If DiceText(p) <> DiceText(p - 1) Then
            If (p < nPlayers - 1) Then
                If DiceText(p + 1) <> DiceText(p) Then
                    PositionKnown(p) = True
                End If
            Else
                PositionKnown(p) = True
            End If
        ElseIf PositionKnown(p) = False And PositionKnown(p - 1) = False Then
            DiceText(p).Visible = False
            RollButton(p).Visible = True
            PositionKnown(p) = False
            moreRolls = True
            DiceText(p - 1).Visible = False
            RollButton(p - 1).Visible = True
            PositionKnown(p - 1) = False
        End If
        
    Next p
    
    If moreRolls = False Then
        PlayGameButton.Enabled = True
        If noHumanPlayers Then
            PlayGameButton_Click
        End If
    End If
    
    ' roll automatically for computer players
    For i = 0 To nPlayers - 1
        If RollButton(i).Visible = True And MainForm.GetPlayerIsHuman(i) = False Then
            RollButton_Click (i)
        End If
    Next i
    
End Sub

Private Sub Timer1_Timer()
    Timer1.Enabled = False
    RollsComplete
End Sub
