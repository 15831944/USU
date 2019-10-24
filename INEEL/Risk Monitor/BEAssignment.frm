VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form BEAssignment 
   Caption         =   "Assign Basic Events to Base Component"
   ClientHeight    =   6090
   ClientLeft      =   2775
   ClientTop       =   3765
   ClientWidth     =   10035
   BeginProperty Font 
      Name            =   "Arial"
      Size            =   9.75
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   Icon            =   "BEAssignment.frx":0000
   LinkTopic       =   "Form1"
   MinButton       =   0   'False
   ScaleHeight     =   6090
   ScaleWidth      =   10035
   Begin MSComctlLib.ListView SelectedBasicEventsList 
      Height          =   3495
      Left            =   7080
      TabIndex        =   12
      Top             =   2040
      Width           =   2775
      _ExtentX        =   4895
      _ExtentY        =   6165
      View            =   3
      LabelEdit       =   1
      MultiSelect     =   -1  'True
      LabelWrap       =   -1  'True
      HideSelection   =   -1  'True
      FullRowSelect   =   -1  'True
      GridLines       =   -1  'True
      _Version        =   393217
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      BorderStyle     =   1
      Appearance      =   1
      NumItems        =   0
   End
   Begin VB.TextBox ModeName 
      BackColor       =   &H80000000&
      Height          =   375
      Left            =   2760
      Locked          =   -1  'True
      TabIndex        =   11
      Text            =   "Text1"
      Top             =   840
      Width           =   2055
   End
   Begin MSComctlLib.ListView AssociatedEventsList 
      Height          =   3495
      Left            =   3600
      TabIndex        =   9
      Top             =   2040
      Width           =   3495
      _ExtentX        =   6165
      _ExtentY        =   6165
      View            =   3
      LabelEdit       =   1
      MultiSelect     =   -1  'True
      LabelWrap       =   -1  'True
      HideSelection   =   -1  'True
      FullRowSelect   =   -1  'True
      GridLines       =   -1  'True
      _Version        =   393217
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      BorderStyle     =   1
      Appearance      =   1
      NumItems        =   0
   End
   Begin MSComctlLib.ListView SystemsList 
      Height          =   3495
      Left            =   120
      TabIndex        =   8
      Top             =   2040
      Width           =   3480
      _ExtentX        =   6138
      _ExtentY        =   6165
      View            =   3
      LabelEdit       =   1
      LabelWrap       =   -1  'True
      HideSelection   =   -1  'True
      FullRowSelect   =   -1  'True
      GridLines       =   -1  'True
      _Version        =   393217
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      BorderStyle     =   1
      Appearance      =   1
      NumItems        =   0
   End
   Begin VB.CommandButton CancelButton 
      Caption         =   "Cancel"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   8640
      TabIndex        =   7
      Top             =   240
      Width           =   1215
   End
   Begin VB.CommandButton RemoveBasicEvents 
      Caption         =   "Remove"
      Height          =   375
      Left            =   8400
      TabIndex        =   6
      Top             =   5640
      Width           =   1455
   End
   Begin VB.CommandButton AddBasicEvents 
      Caption         =   "Add->"
      Height          =   375
      Left            =   5640
      TabIndex        =   5
      Top             =   5640
      Width           =   1455
   End
   Begin VB.TextBox BaseComponentName 
      BackColor       =   &H80000000&
      Height          =   375
      Left            =   2760
      Locked          =   -1  'True
      TabIndex        =   2
      Text            =   "Text1"
      Top             =   360
      Width           =   2055
   End
   Begin VB.CommandButton OKButton 
      Caption         =   "OK"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   7200
      TabIndex        =   0
      Top             =   240
      Width           =   1215
   End
   Begin VB.Label SystemLabel 
      Caption         =   "[no system selected]"
      Height          =   255
      Left            =   3600
      TabIndex        =   13
      Top             =   1560
      Width           =   3375
   End
   Begin VB.Label Label5 
      Caption         =   "Active Mode"
      Height          =   255
      Left            =   240
      TabIndex        =   10
      Top             =   840
      Width           =   2295
   End
   Begin VB.Label Label4 
      Caption         =   "Selected Basic Events"
      Height          =   255
      Left            =   7080
      TabIndex        =   4
      Top             =   1560
      Width           =   2775
   End
   Begin VB.Label Label2 
      Caption         =   "Systems List"
      Height          =   255
      Left            =   120
      TabIndex        =   3
      Top             =   1560
      Width           =   3375
   End
   Begin VB.Label Label1 
      Caption         =   "Editing Base Component"
      Height          =   255
      Left            =   240
      TabIndex        =   1
      Top             =   360
      Width           =   2415
   End
End
Attribute VB_Name = "BEAssignment"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Option Explicit
Public result As Boolean
Public ActiveModeID As Integer

'****************| Steve's DLL Support |**********************************
Private Declare Function SystemCount Lib "riskMon" () As Long
Private Declare Function GetSystemName Lib "riskMon" (ByVal Index As Long, ByRef name As String, ByRef Description As String) As Long
Private Declare Function GetNumOfBE Lib "riskMon" (ByVal sysName As String) As Long
Private Declare Function GetBEName Lib "riskMon" (ByVal sysName As String, ByVal Index As Long, ByRef beName As String, ByRef beDescription As String) As Long
'*************************************************************************

Private Sub AddBasicEvents_Click()
    Dim i As Integer, j As Integer
    Dim itemFound As Boolean
    
    For i = 1 To AssociatedEventsList.ListItems.Count
        If AssociatedEventsList.ListItems.Item(i).Selected Then
            ' search to see if this item is already selected
            itemFound = False
            For j = 1 To SelectedBasicEventsList.ListItems.Count
                If AssociatedEventsList.ListItems.Item(i).text = SelectedBasicEventsList.ListItems.Item(j).text Then
                    itemFound = True
                    Exit For
                End If
            Next j
            
            If Not itemFound Then
                SelectedBasicEventsList.ListItems.Add , , AssociatedEventsList.ListItems(i).text
            End If
        End If
    Next i
    
End Sub


Private Sub AssociatedEventsList_Click()
    AddBasicEvents.Enabled = True 'AssociatedEventsList.SelCount > 0
End Sub

Private Sub CancelButton_Click()
    result = False
    Me.Hide
End Sub

Private Sub Form_Load()
    SystemsList.ColumnHeaders.Add , , "System Name", (SystemsList.Width - 80) / 2
    SystemsList.ColumnHeaders.Add , , "Description", (SystemsList.Width - 80) / 2
    AssociatedEventsList.ColumnHeaders.Add , , "Basic Event Name", (AssociatedEventsList.Width - 80) / 2
    AssociatedEventsList.ColumnHeaders.Add , , "Description", (AssociatedEventsList.Width - 80) / 2
    SelectedBasicEventsList.ColumnHeaders.Add , , "Basic Event Name", SelectedBasicEventsList.Width - 80
    
    If DLLActive Then
        Dim sysCount As Long, i As Long, success As Long
        Dim sysName As String * 25, SysDescription As String * 61
        Dim sys As ListItem
        sysCount = SystemCount
        For i = 1 To sysCount
            success = GetSystemName(i, sysName, SysDescription)
            Set sys = SystemsList.ListItems.Add(, , RTrim(sysName))
            sys.ListSubItems.Add , , RTrim(SysDescription)
        Next
    End If
    RemoveBasicEvents.Enabled = False
    AddBasicEvents.Enabled = False
End Sub

Private Sub Form_Resize()
    If Width > 9000 Then
        SystemsList.Left = 100
        Label2.Left = 100
        SystemsList.Width = (Width - 400) * 8# / 21#
        AssociatedEventsList.Left = SystemsList.Left + SystemsList.Width
        AssociatedEventsList.Width = (Width - 400) * 8# / 21#
        SystemLabel.Left = SystemsList.Left + SystemsList.Width
        SelectedBasicEventsList.Left = AssociatedEventsList.Left + AssociatedEventsList.Width
        SelectedBasicEventsList.Width = (Width - 400) * 5# / 21#
        AddBasicEvents.Left = AssociatedEventsList.Left + AssociatedEventsList.Width - 1455
        RemoveBasicEvents.Left = SelectedBasicEventsList.Left + SelectedBasicEventsList.Width - 1455
        Label4.Left = AssociatedEventsList.Left + AssociatedEventsList.Width
        OKButton.Left = Width - 3300
        CancelButton.Left = Width - 1800
        
        SystemsList.ColumnHeaders.Item(1).Width = (SystemsList.Width - 80) / 2
        SystemsList.ColumnHeaders.Item(2).Width = (SystemsList.Width - 80) / 2
        
        AssociatedEventsList.ColumnHeaders.Item(1).Width = (AssociatedEventsList.Width - 80) / 2
        AssociatedEventsList.ColumnHeaders.Item(2).Width = (AssociatedEventsList.Width - 80) / 2
        
        SelectedBasicEventsList.ColumnHeaders.Item(1).Width = SelectedBasicEventsList.Width - 80
    End If
    
    If Height > 5000 Then
        SystemsList.Height = Height - 3240
        AssociatedEventsList.Height = Height - 3240
        SelectedBasicEventsList.Height = Height - 3240
        AddBasicEvents.Top = Height - 975
        RemoveBasicEvents.Top = Height - 975
    End If
End Sub

Private Sub OKButton_Click()
    result = True
    Me.Hide
End Sub

Private Sub RemoveBasicEvents_Click()
    Dim i As Integer
    For i = SelectedBasicEventsList.ListItems.Count To 1 Step -1
        If SelectedBasicEventsList.ListItems(i).Selected Then
            SelectedBasicEventsList.ListItems.Remove (i)
        End If
    Next i
    RemoveBasicEvents.Enabled = (SelectedBasicEventsList.ListItems.Count > 0)
End Sub

Private Sub SelectedBasicEventsList_Click()
    RemoveBasicEvents.Enabled = True '(SelectedBasicEventsList.SelCount > 0)
End Sub

Private Sub SystemsList_Click()
    Dim BECount As Long, SystemName As String * 25, wBE As Long, success As Long
    Dim beName As String * 25, beDescription As String * 61, be As ListItem
    
    If Not SystemsList.SelectedItem Is Nothing Then
        SystemName = SystemsList.SelectedItem.text
        BECount = GetNumOfBE(SystemName)
        AssociatedEventsList.ListItems.Clear
        For wBE = 0 To BECount - 1
            success = GetBEName(SystemName, wBE, beName, beDescription)
            Set be = AssociatedEventsList.ListItems.Add(, , RTrim(beName))
            be.ListSubItems.Add , , RTrim(beDescription)
        Next
        SystemLabel.Caption = SystemsList.SelectedItem.ListSubItems(1).text
    End If
    
End Sub
