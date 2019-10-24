VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form EditTask 
   Caption         =   "Edit Task"
   ClientHeight    =   5295
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   9870
   BeginProperty Font 
      Name            =   "Arial"
      Size            =   9.75
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   Icon            =   "EditTask.frx":0000
   LinkTopic       =   "Form1"
   MinButton       =   0   'False
   ScaleHeight     =   5295
   ScaleWidth      =   9870
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Cancel 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   8520
      TabIndex        =   10
      Top             =   4800
      Width           =   1335
   End
   Begin VB.CommandButton Add 
      Caption         =   "<- Add"
      Height          =   375
      Left            =   5760
      TabIndex        =   9
      Top             =   4800
      Width           =   1215
   End
   Begin VB.CommandButton Remove 
      Caption         =   "Remove"
      Height          =   375
      Left            =   3720
      TabIndex        =   8
      Top             =   4800
      Width           =   975
   End
   Begin MSComctlLib.ListView AvailableProcedures 
      Height          =   3735
      Left            =   5760
      TabIndex        =   7
      Top             =   960
      Width           =   4095
      _ExtentX        =   7223
      _ExtentY        =   6588
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
   Begin MSComctlLib.ListView CurrentProcedures 
      Height          =   3735
      Left            =   0
      TabIndex        =   6
      Top             =   960
      Width           =   5775
      _ExtentX        =   10186
      _ExtentY        =   6588
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
   Begin VB.CommandButton EditDur 
      Caption         =   "Change Duration"
      Height          =   375
      Left            =   1920
      TabIndex        =   2
      Top             =   4800
      Width           =   1695
   End
   Begin VB.CommandButton EditOffset 
      Caption         =   "Change Offset"
      Height          =   375
      Left            =   120
      TabIndex        =   1
      Top             =   4800
      Width           =   1695
   End
   Begin VB.CommandButton ok 
      Caption         =   "OK"
      Height          =   375
      Left            =   7080
      TabIndex        =   0
      Top             =   4800
      Width           =   1335
   End
   Begin VB.Label Label3 
      Caption         =   "Label3"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   240
      TabIndex        =   5
      Top             =   120
      Width           =   8055
   End
   Begin VB.Label Label2 
      Caption         =   "Avaliable Procedures "
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Index           =   1
      Left            =   5760
      TabIndex        =   4
      Top             =   600
      Width           =   2655
   End
   Begin VB.Label Label1 
      Caption         =   "Current Procedures"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Index           =   0
      Left            =   120
      TabIndex        =   3
      Top             =   600
      Width           =   2295
   End
End
Attribute VB_Name = "EditTask"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Public TaskID As Integer
Public nameString As String ' used by other forms
Public TaskName As String

'Function/Subroutine:Add_Click
'Purpose: add a procedure to a task - button click
Private Sub Add_Click()
    Dim DuplicateFound As Boolean, lItem As ListItem, haveOffDur As Boolean
    Dim i As Integer, j As Integer, ProcOffset As String, ProcDuration As String
    
    For i = 1 To AvailableProcedures.ListItems.Count
        If AvailableProcedures.ListItems(i).Selected Then
            ' user wants to add this item.  check to see if it is
            ' already included in the current procedures
            DuplicateFound = False
            For j = 1 To CurrentProcedures.ListItems.Count
                ' compare tags because they are the unique identifier
                If CurrentProcedures.ListItems(j).tag = AvailableProcedures.ListItems(i).tag Then
                    DuplicateFound = True
                    Exit For
                End If
            Next j
            
            If Not DuplicateFound Then
                If Not haveOffDur Then
                    ' show the form to ask the user the offset and duration
                    OffsetDuration.ObjectLabel = TaskName
                    OffsetDuration.Show vbModal, Me
                    If OffsetDuration.CancelClick = True Then Exit Sub
                    ProcOffset = OffsetDuration.Text1.text
                    ProcDuration = OffsetDuration.Text2.text
                    haveOffDur = True
                End If
                nameString = AvailableProcedures.ListItems(i).text
                Set lItem = CurrentProcedures.ListItems.Add(, , nameString)
                lItem.ToolTipText = nameString
                lItem.tag = AvailableProcedures.ListItems(i).tag
                lItem.ListSubItems.Add , , AvailableProcedures.ListItems(i).ListSubItems(1).text, , AvailableProcedures.ListItems(i).ListSubItems(1).text
                lItem.ListSubItems.Add , , ProcOffset, , ProcOffset
                lItem.ListSubItems.Add , , ProcDuration, , ProcDuration
            End If
        End If
    Next i
    
End Sub

Private Sub AvailableProcedures_DblClick()
    Add_Click
End Sub

Private Sub Cancel_Click()
    Me.Hide
End Sub

Private Sub CurrentProcedures_Click()
    EditDur.Enabled = True
    EditOffset.Enabled = True
    Remove.Enabled = True
End Sub

Private Sub CurrentProcedures_DblClick()
    Remove_Click
End Sub

Private Sub CurrentProcedures_KeyPress(KeyAscii As Integer)
    If KeyAscii = 13 Then
        Remove_Click
    End If
End Sub

'Function/Subroutine:EditDur_Click
'Purpose: change the duration of a procedure within a task
Private Sub EditDur_Click()
    Dim i As Integer, getTime As Boolean
    For i = 1 To CurrentProcedures.ListItems.Count
        If CurrentProcedures.ListItems(i).Selected Then
            ' user wants to change this item.
            ' show the form to ask the user the duration
            If Not getTime Then
                Offset.ObjectLabel = CurrentProcedures.ListItems(i).text
                Offset.Show vbModal, Me
                If Offset.CancelClick = True Then Exit Sub
                getTime = True
            End If
            CurrentProcedures.ListItems(i).ListSubItems(3).text = Offset.Text1
            CurrentProcedures.ListItems(i).ListSubItems(3).ToolTipText = Offset.Text1
        End If
    Next i
    If getTime Then Unload Offset
End Sub
'Function/Subroutine:EditOffset_Click
'Purpose: edit the offset of a procedure in a task
Private Sub EditOffset_Click()
    Dim i As Integer, getTime As Boolean
    For i = 1 To CurrentProcedures.ListItems.Count
        If CurrentProcedures.ListItems(i).Selected Then
            ' user wants to change this item.
            ' show the form to ask the user the duration
            If Not getTime Then
                Offset.ObjectLabel = CurrentProcedures.ListItems(i).text
                Offset.Show vbModal, Me
                If Offset.CancelClick = True Then Exit Sub
                getTime = True
            End If
            CurrentProcedures.ListItems(i).ListSubItems(2).text = Offset.Text1
            CurrentProcedures.ListItems(i).ListSubItems(2).ToolTipText = Offset.Text1
        End If
    Next i
    If getTime Then Unload Offset
End Sub
'Function/Subroutine:Form_Load
'Purpose: initialize variables and set up arrays of database info so
'database dosent have to be accessed too often
Private Sub Form_Load()
    Dim mySQLStatement As String, resultSet As rdoResultset, rarray As Variant
    Dim ProcName As String, procDescription As String, lItem As ListItem
    Dim ProcDur As String, ProcOff As String
    'Get Task ID from Task Name
    mySQLStatement = "SELECT TaskID FROM [Task] WHERE TaskName = '" & TaskName & "'"
    Set resultSet = dbConnection.OpenResultset(mySQLStatement)
    ' Run time error 40071 will be generated if no connection is present by this statement
    
    CurrentProcedures.ColumnHeaders.Add , , "Procedure Name", (CurrentProcedures.Width - 80) * 1 / 3
    CurrentProcedures.ColumnHeaders.Add , , "Procedure Description", (CurrentProcedures.Width - 80) * 1 / 3
    CurrentProcedures.ColumnHeaders.Add , , "Offset from Start (hrs)", (CurrentProcedures.Width - 80) * 1 / 6
    CurrentProcedures.ColumnHeaders.Add , , "Duration (hrs)", (CurrentProcedures.Width - 80) * 1 / 6
    
    AvailableProcedures.ColumnHeaders.Add , , "Procedure Name", (AvailableProcedures.Width - 80) * 1 / 2
    AvailableProcedures.ColumnHeaders.Add , , "Procedure Description", (AvailableProcedures.Width - 80) * 1 / 2
    
    ' check to make sure result was returned
    If (resultSet.EOF) Then
        MsgBox "No Task Found, Program Error", vbInformation
        Me.Hide
        Exit Sub
    Else
        rarray = resultSet.GetRows(1)
        TaskID = rarray(0, 0)
        ' we should not get the task by the task name, since it could be a duplicate, but for now, it will do
        mySQLStatement = "SELECT TaskProc.ProcedureID, Procedure.ProcedureName, Procedure.ProcedureDesc, TaskProc.TimeOffset, TaskProc.Duration FROM [TaskProc], [Procedure] WHERE TaskID = " & TaskID & " AND TaskProc.ProcedureID = Procedure.ProcedureID"
        Set resultSet = dbConnection.OpenResultset(mySQLStatement, rdOpenKeyset)
        If (resultSet.EOF) Then
            EditDur.Enabled = False
            EditOffset.Enabled = False
            Remove.Enabled = False
        Else
            'Display Current Procedure names in a list view
            While Not resultSet.EOF
                rarray = resultSet.GetRows(1)
                ProcName = rarray(1, 0)
                procDescription = rarray(2, 0)
                ProcOff = rarray(3, 0)
                ProcDur = rarray(4, 0)
                Set lItem = CurrentProcedures.ListItems.Add(, , ProcName)
                lItem.ToolTipText = ProcName
                lItem.ListSubItems.Add , , procDescription, , procDescription
                lItem.ListSubItems.Add , , ProcOff, , ProcOff
                lItem.ListSubItems.Add , , ProcDur, , ProcDur
                ' we can store the procedure id in the list item tag
                lItem.tag = rarray(0, 0)
            Wend
        End If
    End If

    'populate available procedure list view
    mySQLStatement = "SELECT ProcedureID, ProcedureName, ProcedureDesc From [Procedure]"
    Set resultSet = dbConnection.OpenResultset(mySQLStatement)
    
    If resultSet.EOF Then
        MsgBox "No Procedures Found", vbInformation
    Else
        While Not resultSet.EOF
            rarray = resultSet.GetRows(1)
            ProcName = rarray(1, 0)
            procDescription = rarray(2, 0)
            Set lItem = AvailableProcedures.ListItems.Add(, , ProcName)
            lItem.ToolTipText = ProcName
            lItem.ListSubItems.Add , , procDescription, , procDescription
            ' we can store the procedure id in the list item tag
            lItem.tag = rarray(0, 0)
        Wend
    End If
    
    Label3.Caption = TaskName
End Sub

Private Sub Form_Resize()
    If Height > 5700 Then
        EditOffset.Top = Height - 900
        EditDur.Top = Height - 900
        Remove.Top = Height - 900
        Add.Top = Height - 900
        OK.Top = Height - 900
        Cancel.Top = Height - 900
        CurrentProcedures.Height = Height - 2000
        AvailableProcedures.Height = Height - 2000
    End If
    
    If Width > 9990 Then
        CurrentProcedures.Width = (Width - 100) * 57 / 100
        AvailableProcedures.Left = CurrentProcedures.Left + CurrentProcedures.Width
        AvailableProcedures.Width = (Width - 100) * 43 / 100
        OK.Left = Width - 3000
        Cancel.Left = Width - 1600
        Add.Left = AvailableProcedures.Left
        Label2(1).Left = AvailableProcedures.Left
        
        CurrentProcedures.ColumnHeaders(1).Width = (CurrentProcedures.Width - 80) * 1 / 3
        CurrentProcedures.ColumnHeaders(2).Width = (CurrentProcedures.Width - 80) * 1 / 3
        CurrentProcedures.ColumnHeaders(3).Width = (CurrentProcedures.Width - 80) * 1 / 6
        CurrentProcedures.ColumnHeaders(4).Width = (CurrentProcedures.Width - 80) * 1 / 6
    
        AvailableProcedures.ColumnHeaders(1).Width = (AvailableProcedures.Width - 80) * 1 / 2
        AvailableProcedures.ColumnHeaders(2).Width = (AvailableProcedures.Width - 80) * 1 / 2
    End If
End Sub

'Function/Subroutine:ok_Click
'Purpose: handles enter press - adds item
Private Sub OK_Click()
    ' this is where we save the data
    Dim mySQLStatement As String, i As Integer, ProcID As String, ProcDur As String, ProcOff As String
    
    mySQLStatement = "DELETE FROM [TaskProc] WHERE TaskID = " & TaskID
    dbConnection.Execute (mySQLStatement)
    For i = 1 To CurrentProcedures.ListItems.Count
        ProcID = CurrentProcedures.ListItems(i).tag
        ProcOff = CurrentProcedures.ListItems(i).ListSubItems(2).text
        ProcDur = CurrentProcedures.ListItems(i).ListSubItems(3).text
        
        mySQLStatement = "INSERT INTO [TaskProc] (TaskID, ProcedureID, TimeOffset, Duration) VALUES ( " & TaskID & ", " & ProcID & ", " & ProcOff & ", " & ProcDur & ")"
        dbConnection.Execute (mySQLStatement)
    Next i
    
    Me.Hide
End Sub

'Function/Subroutine:Remove_Click
'Purpose:remove and item from the database and the lists.
Private Sub Remove_Click()
    Dim i As Integer
    For i = CurrentProcedures.ListItems.Count To 1 Step -1
        If CurrentProcedures.ListItems(i).Selected Then
            ' user wants to delete this item.
            CurrentProcedures.ListItems.Remove (i)
        End If
    Next i
End Sub


