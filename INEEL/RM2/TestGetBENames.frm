VERSION 5.00
Begin VB.Form TestGetBENames 
   Caption         =   "Test"
   ClientHeight    =   3195
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   Icon            =   "TestGetBENames.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   3195
   ScaleWidth      =   4680
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton GetCritComp 
      Caption         =   "GetCritComp"
      Height          =   495
      Left            =   3120
      TabIndex        =   6
      Top             =   2520
      Width           =   1095
   End
   Begin VB.CommandButton LoadCritComp 
      Caption         =   "Load CritComps"
      Height          =   495
      Left            =   1680
      TabIndex        =   5
      Top             =   2520
      Width           =   1095
   End
   Begin VB.CommandButton LoadSys 
      Caption         =   "getNumOfBe"
      Height          =   495
      Left            =   360
      TabIndex        =   4
      Top             =   2520
      Width           =   975
   End
   Begin VB.CommandButton GetBe 
      Caption         =   "   Get Basic          Event"
      Height          =   735
      Left            =   3120
      TabIndex        =   3
      Top             =   1560
      Width           =   1095
   End
   Begin VB.CommandButton NumTrees 
      Caption         =   "Num  Systems"
      Height          =   735
      Left            =   360
      TabIndex        =   2
      Top             =   1560
      Width           =   855
   End
   Begin VB.CommandButton GetName 
      Caption         =   "Get Name"
      Height          =   735
      Left            =   1560
      TabIndex        =   1
      Top             =   1560
      Width           =   1215
   End
   Begin VB.ListBox MyScreen 
      Height          =   840
      Left            =   360
      TabIndex        =   0
      Top             =   360
      Width           =   3015
   End
End
Attribute VB_Name = "TestGetBENames"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Declare Function SystemCount Lib "riskMon" () As Long
'starts from 1 to SystemCount
Private Declare Function GetSystemName Lib "riskMon" (ByVal funcIndex As Long, ByRef funcSysName As String, ByRef funkSysDesc As String) As Long
Private Declare Function GetBEName Lib "riskMon" (ByVal funcSysName As String, ByVal funcIndex2 As Long, ByRef funkBEName As String, ByRef funkBEDesc As String) As Long
Private Declare Function GetNumOfBE Lib "riskMon" (ByVal funcSysName As String) As Long

'pass time in this format "20yr-mo-dy hr:mn:sc" (military hours)
Private Declare Function LoadCritBE Lib "riskMon" (ByVal funcTime As String) As Long
Private Declare Function GetNextCritBE Lib "riskMon" (ByRef funcBeName As String) As Long


Private sysName As String * 25
Private sysDesc As String * 61
Private beDesc As String * 61
Private NumOfSystems As Long
Private beName As String * 25
Private numOfBE As Long
Private CritBEName As String * 25
Private time As String * 25

Private Sub GetBe_Click()
    Dim num As Long
    sysName = "CCS"
    Dim Index As Long
    Index = 0
    num = GetBEName(sysName, Index, beName, beDesc)
    
    MyScreen.AddItem beName
    MyScreen.AddItem beDesc
    MyScreen.Refresh
End Sub

Private Sub GetCritComp_Click()
    Dim num As Long
    
    num = GetNextCritBE(CritBEName)
    MyScreen.AddItem CritBEName
    MyScreen.Refresh
End Sub

Private Sub GetName_Click()
    Dim num As Long
    
    num = GetSystemName(1, sysName, sysDesc)
    MyScreen.AddItem sysName
    MyScreen.AddItem sysDesc
    MyScreen.Refresh
End Sub



Private Sub LoadCritComp_Click()
    Dim num As Long
    time = "2001-07-18 13:00:00 PM" ' =7/18/01 1:00:00 PM"
    num = LoadCritBE(time)
    
    
End Sub

Private Sub LoadSys_Click()
    sysName = "CCS"
    numOfBE = GetNumOfBE(sysName)
End Sub

Private Sub NumTrees_Click()
    NumOfSystems = SystemCount
    MyScreen.AddItem NomOfSystems
    MyScreen.Refresh
    
End Sub
