VERSION 5.00
Begin VB.Form TradeInForm 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Risk Cards"
   ClientHeight    =   5205
   ClientLeft      =   150
   ClientTop       =   495
   ClientWidth     =   13050
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
   ScaleHeight     =   5205
   ScaleWidth      =   13050
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin VB.Timer Timer2 
      Enabled         =   0   'False
      Interval        =   2000
      Left            =   720
      Top             =   4680
   End
   Begin VB.Timer Timer1 
      Enabled         =   0   'False
      Interval        =   1000
      Left            =   240
      Top             =   4680
   End
   Begin VB.CommandButton Command2 
      Caption         =   "No Trade In"
      Enabled         =   0   'False
      Height          =   495
      Left            =   5040
      TabIndex        =   1
      Top             =   4560
      Width           =   2295
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Do Trade In"
      Enabled         =   0   'False
      Height          =   495
      Left            =   2640
      TabIndex        =   0
      Top             =   4560
      Width           =   2175
   End
   Begin VB.Image CardImage 
      Height          =   2430
      Index           =   6
      Left            =   9960
      Stretch         =   -1  'True
      Top             =   1920
      Width           =   1215
   End
   Begin VB.Image CardImage 
      Height          =   2430
      Index           =   7
      Left            =   11595
      Stretch         =   -1  'True
      Top             =   1920
      Width           =   1215
   End
   Begin VB.Shape CardHighlight 
      BorderColor     =   &H0000FFFF&
      Height          =   2655
      Index           =   6
      Left            =   9840
      Top             =   1800
      Width           =   1455
   End
   Begin VB.Shape CardHighlight 
      BorderColor     =   &H0000FFFF&
      Height          =   2655
      Index           =   7
      Left            =   11475
      Top             =   1800
      Width           =   1455
   End
   Begin VB.Shape CardHighlight 
      BorderColor     =   &H0000FFFF&
      Height          =   2655
      Index           =   5
      Left            =   8280
      Top             =   1800
      Width           =   1455
   End
   Begin VB.Shape CardHighlight 
      BorderColor     =   &H0000FFFF&
      Height          =   2655
      Index           =   4
      Left            =   6648
      Top             =   1800
      Width           =   1455
   End
   Begin VB.Shape CardHighlight 
      BorderColor     =   &H0000FFFF&
      Height          =   2655
      Index           =   3
      Left            =   5016
      Top             =   1800
      Width           =   1455
   End
   Begin VB.Shape CardHighlight 
      BorderColor     =   &H0000FFFF&
      Height          =   2655
      Index           =   2
      Left            =   3384
      Top             =   1800
      Width           =   1455
   End
   Begin VB.Shape CardHighlight 
      BorderColor     =   &H0000FFFF&
      Height          =   2655
      Index           =   1
      Left            =   1752
      Top             =   1800
      Width           =   1455
   End
   Begin VB.Shape CardHighlight 
      BorderColor     =   &H0000FFFF&
      Height          =   2655
      Index           =   0
      Left            =   120
      Top             =   1800
      Width           =   1455
   End
   Begin VB.Label Label1 
      Caption         =   "Click on the cards you wish to use for a trade in if you can make a trade in.  This trade in is worth x armies."
      Height          =   1455
      Left            =   120
      TabIndex        =   2
      Top             =   120
      Width           =   4695
   End
   Begin VB.Image CardImage 
      Height          =   2430
      Index           =   5
      Left            =   8400
      Stretch         =   -1  'True
      Top             =   1920
      Width           =   1215
   End
   Begin VB.Image CardImage 
      Height          =   2430
      Index           =   4
      Left            =   6765
      Stretch         =   -1  'True
      Top             =   1920
      Width           =   1215
   End
   Begin VB.Image CardImage 
      Height          =   2430
      Index           =   3
      Left            =   5130
      Stretch         =   -1  'True
      Top             =   1920
      Width           =   1215
   End
   Begin VB.Image CardImage 
      Height          =   2430
      Index           =   2
      Left            =   3510
      Stretch         =   -1  'True
      Top             =   1920
      Width           =   1215
   End
   Begin VB.Image CardImage 
      Height          =   2430
      Index           =   1
      Left            =   1875
      Stretch         =   -1  'True
      Top             =   1920
      Width           =   1215
   End
   Begin VB.Image CardImage 
      Height          =   2430
      Index           =   0
      Left            =   240
      Stretch         =   -1  'True
      Top             =   1920
      Width           =   1215
   End
End
Attribute VB_Name = "TradeInForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private cardsSelected As Integer
Private nCards As Integer
Private cards As CARD_DATA
Private Declare Function GetCardType Lib "ManagerDLL" (ByVal wCard As Long, ByRef CardType As Long) As Long
Private Declare Function GetCountryInfo Lib "ManagerDLL" (ByVal wCountry As Long, ByRef InfoStruct As COUNTRY_INFO) As Long
Private Declare Function CallDoTradeIn Lib "ManagerDLL" (ByVal CardCount As Long, ByRef wCards As Long, ByVal IsMandatory As Long, ByRef result As Long) As Boolean
Private Declare Function GetNextTradeInValue Lib "ManagerDLL" () As Long

Private cardsToTradeIn(0 To 2) As Long
Private CompDoTradeIn As Long

Private cset As CARD_DATA
Public result As Boolean
Public CountryCardSelected As Integer
Private inCSelectMode As Boolean
Private IsHuman As Boolean

Public Sub SetCard(index As Integer, ByVal wCard As Integer)
    cards.wCard(index) = wCard
    Dim cType As Long
    GetCardType wCard, cType
    cards.CardType(index) = cType
    CardImage(index).Picture = LoadPicture("cards\Image" & wCard & ".jpg")
End Sub

Public Function GetTradeInCard(index As Integer)
    GetTradeInCard = cset.wCard(index)
End Function

Public Sub ShowForm(ByVal cCount As Integer, ByVal IsH As Boolean)
    Command1.Visible = True
    Command2.Visible = True
    nCards = cCount
    Width = 13410 - (8 - nCards) * 1635
    Label1.Width = 12660 - (8 - nCards) * 1635
    Label1.Caption = "Click on the cards you wish to use for a trade in if you can make a trade in.  This trade in is worth " & GetNextTradeInValue() & " armies."
    ClearSelections
    CountryCardSelected = 0
    Dim i As Integer
    For i = 0 To nCards - 1
        CardImage(i).Visible = True
    Next
    inCSelectMode = False
    IsHuman = IsH
    Command2.Enabled = nCards < 5 And IsHuman
    If IsHuman = False Then
        Dim m As Long
        If cCount < 5 Then m = 0 Else m = 1
        If CallDoTradeIn(cCount, cardsToTradeIn(0), m, CompDoTradeIn) = False Then
            MyMessageBox "CallDoTradeIn returned False"
            ReleaseAndEnd
        End If
        Timer1.Interval = 1000 * Delay
        Timer2.Interval = 2000 * Delay
        Timer1.Enabled = True
        Timer2.Enabled = True
    End If
    Me.Show vbModal
End Sub

Private Sub ClearSelections()
    Dim i As Integer
    For i = 0 To 5
        CardHighlight(i).Visible = False
    Next i
    cardsSelected = 0
    Command1.Enabled = False
End Sub

Private Function CheckSelections() As Boolean
    If cardsSelected < 3 Then
        CheckSelections = False
        Exit Function
    End If
    
    'check for a match with currently selected cards
    Dim i As Integer, j As Integer
    j = 0
    For i = 0 To nCards - 1
        If CardHighlight(i).Visible = True Then
            cset.CardType(j) = cards.CardType(i)
            cset.wCard(j) = cards.wCard(i)
            j = j + 1
        End If
    Next
    
    If cset.CardType(0) = 0 Or cset.CardType(1) = 0 Or cset.CardType(2) = 0 Then
        ' player has a wild card
        CheckSelections = True
        Exit Function
    End If
    
    If cset.CardType(0) = cset.CardType(1) And cset.CardType(1) = cset.CardType(2) Then
        ' three of a kind
        CheckSelections = True
        Exit Function
    End If
    
    If cset.CardType(0) <> cset.CardType(1) And cset.CardType(1) <> cset.CardType(2) And cset.CardType(0) <> cset.CardType(2) Then
        ' three that are different
        CheckSelections = True
        Exit Function
    End If
    
    CheckSelections = False
End Function

Private Sub CardImage_Click(index As Integer)
    If IsHuman Then
        SelectCard (index)
    End If
End Sub

Private Sub SelectCard(ByVal index As Integer)
    If inCSelectMode Then
        CountryCardSelected = cards.wCard(index)
        Me.Hide
    Else
        If CardHighlight(index).Visible = False Then
            If cardsSelected = 3 Then ClearSelections
            CardHighlight(index).Visible = True
            cardsSelected = cardsSelected + 1
        Else
            CardHighlight(index).Visible = False
            cardsSelected = cardsSelected - 1
        End If
        Command1.Enabled = CheckSelections() And IsHuman
    End If
End Sub


Private Sub Command1_Click()
    ' do trade in
    Dim i As Integer
    Dim hasCountryCard As Integer
    Dim cInfo As COUNTRY_INFO
    
    hasCountryCard = 0
    CountryCardSelected = 0
    For i = 0 To nCards - 1
        If CardHighlight(i).Visible = True And cards.wCard(i) <> 0 Then
            GetCountryInfo cards.wCard(i), cInfo
            If cInfo.OwnerID = wPlayer Then
                CountryCardSelected = cards.wCard(i)
                hasCountryCard = hasCountryCard + 1
                CardImage(i).Visible = True
            Else
                CardImage(i).Visible = False
            End If
        Else
            CardImage(i).Visible = False
        End If
        CardHighlight(i).Visible = False
    Next i
    result = True
    
    If hasCountryCard < 2 Then
        Me.Hide
    Else
        inCSelectMode = True
        Command1.Visible = False
        Command2.Visible = False
        MyMessageBox "Please choose the country you wish to place 2 additional armies on."
        
    End If
End Sub

Private Sub Command2_Click()
    result = False
    Me.Hide
End Sub

Private Sub Form_Activate()
    Command2.Enabled = nCards < 5 And IsHuman
End Sub

'Private Sub Form_Activate()
'    If MainForm.GetPlayerIsHuman(wPlayer) = False Then
'        ' call comp sub to handle trade in
'    End If
'End Sub

Private Sub Form_Resize()
    Command1.Left = 4320 - (8 - nCards) * 840
    Command2.Left = 6720 - (8 - nCards) * 840
End Sub

Private Sub Timer1_Timer()
    ' time to go...
    Timer1.Enabled = False
    If CompDoTradeIn Then
        ClearSelections
        SelectCard cardsToTradeIn(0)
        SelectCard cardsToTradeIn(1)
        SelectCard cardsToTradeIn(2)
        CountryCardSelected = cardsToTradeIn(0)
    End If
End Sub

Private Sub Timer2_Timer()
    Timer2.Enabled = False
    result = False
    If CompDoTradeIn Then
        result = CheckSelections
    End If
    Me.Hide
End Sub
