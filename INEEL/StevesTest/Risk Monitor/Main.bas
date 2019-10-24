Attribute VB_Name = "Module1"
Option Explicit
Public ActiveMovieFile As String
Public BrowserManualFile As String
Public red As Integer
Public green As Integer
Public blue As Integer
Public redflag As Integer
Public greenflag As Integer
Public blueflag As Integer
Public dbEnvironment As rdoEnvironment
Public dbConnection As rdoConnection
Public MDIMain As frmMain
Public userID As Integer
Public workingDirectory As String
Public pidDirectory As String
Public databaseName As String
Public pManager As ProcessManager
Public NewLine As String
Public Const NameMaxFieldLength As Integer = 50
Public compHierarchy As ComponentHierarchyClass
Public connectionType As String
Public ModeList As Collection
Public ModeCount As Integer
Public IsAccessDatabase As Boolean
Public DateDelimitor As String
Public DLLActive As Boolean
'color of users high medium and low risk values
Public DangerColor As Long
Public CautionColor As Long
Public OKColor As Long
Public TaskColor As Long
Public ProcColor As Long
Public CompColor As Long
Public UserType As EnumUserType
Public InterfaceType As InterfaceTypeEnum
'**************************************************************
' constants used in drawing risk chart
' set GraphHeight equal to an arbitrary max value,
' with PixelH being the height of the high level risk bar and PixelM
' and PixelB being the height of the medium level risk bar and baseline
' risk bar relative to the bottom of the graph
Public Const GraphHeight = 100
Public Const PixelH = 90
Public Const PixelM = 50
Public Const PixelB = 10

Enum EnumUserType
    NormalUser = 0
    Administrator = 1
End Enum

Enum InterfaceTypeEnum
    Regular = 0
    NASA = 1
End Enum

'Function/Subroutine:
'Purpose:
Public Function DBConnect(name As String) As Boolean
    
    On Error GoTo checkError
    Set dbEnvironment = rdoEngine.rdoEnvironments(0)
    dbEnvironment.CursorDriver = rdUseOdbc
    dbEnvironment.LoginTimeout = 8
    
    ',"RiskMonitorSQLServer"
    Set dbConnection = dbEnvironment.OpenConnection(dsname:=name, _
        Prompt:=rdDriverNoPrompt, _
        Connect:="UID=;PWD=;", _
        Options:=rdAsyncEnable)
   
    While Module1.dbConnection.StillConnecting
        DoEvents
    Wend
    
    DBConnect = True
    databaseName = name
    If InStr(1, databaseName, "SQL", vbTextCompare) > 0 Then
        DateDelimitor = "'"
        IsAccessDatabase = False
    Else
        DateDelimitor = "#"
        IsAccessDatabase = True
    End If
    
    Exit Function
    
checkError:
    DBConnect = False
    
End Function

'Function/Subroutine:
'Purpose:
Sub Main()

    InterfaceType = NASA
    
    NewLine = Chr$(13)
    Dim fs As Object 'FileSystemObject
    Set fs = CreateObject("Scripting.FileSystemObject")
    
    'set flags
    redflag = 0
    greenflag = 0
    blueflag = 0
    
    workingDirectory = GetSetting("RiskMonitor", "STARTUP", "Working_Directory", "")
    If (workingDirectory = "") Then
        MsgBox "The registry key for the working directory is missing." & NewLine & _
               "Please select the directory to which Risk Monitor was installed (Ex: C:\Program Files\RiskMonitor)", vbInformation
        workingDirectory = BrowseForFolder("Select Risk Monitor Directory")
        If workingDirectory = "" Then Exit Sub
        workingDirectory = workingDirectory & "\"
    End If
    
    Do While Not fs.FolderExists(workingDirectory & "icons")
        If (MsgBox("No icons folder was found in " & workingDirectory & NewLine & _
            "Would you like to try a different directory?", vbYesNo + vbQuestion) = vbNo) Then
            Exit Sub
        End If
        workingDirectory = BrowseForFolder("Select Risk Monitor Directory")
        workingDirectory = workingDirectory & "\"
    Loop
    
    ' if working directory is none, then ask the user where the risk monitor
    ' directory is
    ' if it does not contain an icons folder and .exe, then ask the user
    ' where it is
    
    pidDirectory = GetSetting("RiskMonitor", "STARTUP", "PID_Directory", "")
    ' if it does not contain a PID folder, then ask the user where the PID folder is
    If (pidDirectory = "") Then
        MsgBox "The registry key for the P&ID directory is missing." & NewLine & _
               "Please select the directory in which P&ID diagrams are stored (Ex: C:\Program Files\RiskMonitor\PID)", vbInformation
        pidDirectory = BrowseForFolder("Select P&ID Directory")
        If pidDirectory <> "" Then
            pidDirectory = pidDirectory & "\"
        End If
    End If
    
    
    
    SaveSetting "RiskMonitor", "STARTUP", "Working_Directory", workingDirectory
    SaveSetting "RiskMonitor", "STARTUP", "PID_Directory", pidDirectory
    'workingDirectory = "" '"D:\SFXTree Risk Monitor\"
    Set pManager = New ProcessManager
    
    'determine if database has been previously opened
    databaseName = GetSetting("RiskMonitor", "STARTUP", "Database_Name", "")
    
    Do
        Splash.Show (1)
        'frmODBCLogon.Show (1)
        'DBConnect
        frmLogin.Show (1)
        If frmLogin.OK Then Exit Do
    Loop
    
    SaveSetting "RiskMonitor", "STARTUP", "Database_Name", databaseName
    Unload Splash
    Unload frmLogin

    
    Set MDIMain = New frmMain

    Load MDIMain
    SelectMainViewFrm.Show vbModal
    
    If InterfaceType = NASA Then
        If SelectMainViewFrm.OptionSelected = 2 Then
            Unload MDIMain
            End
        Else
            MDIMain.Show
            If SelectMainViewFrm.OptionSelected = 1 Then MDIMain.mnuViewRiskMeter_Click
            
        End If
    Else
        MDIMain.Show
    End If
    'ChartDialog.Show
    
End Sub

'Function/Subroutine:
'Purpose:
Public Sub ColowWindowWhite(FormToChange As Form)
    FormToChange.BackColor = RGB(255, 255, 255)
End Sub
'Function/Subroutine:
'Purpose:
Sub LoadResStrings(frm As Form)
    On Error Resume Next
    
    Dim ctl As Control
    Dim obj As Object
    Dim fnt As Object
    Dim sCtlType As String
    Dim nVal As Integer


    'set the form's caption
    frm.Caption = LoadResString(CInt(frm.tag))
    

    'set the font
    Set fnt = frm.Font
    fnt.name = LoadResString(20)
    fnt.Size = CInt(LoadResString(21))
    

    'set the controls' captions using the caption
    'property for menu items and the Tag property
    'for all other controls
    For Each ctl In frm.Controls
        Set ctl.Font = fnt
        sCtlType = TypeName(ctl)
        If sCtlType = "Label" Then
            ctl.Caption = LoadResString(CInt(ctl.tag))
        ElseIf sCtlType = "Menu" Then
            ctl.Caption = LoadResString(CInt(ctl.Caption))
        ElseIf sCtlType = "TabStrip" Then
            For Each obj In ctl.Tabs
                obj.Caption = LoadResString(CInt(obj.tag))
                obj.ToolTipText = LoadResString(CInt(obj.ToolTipText))
            Next
        ElseIf sCtlType = "Toolbar" Then
            For Each obj In ctl.Buttons
                obj.ToolTipText = LoadResString(CInt(obj.ToolTipText))
            Next
        ElseIf sCtlType = "ListView" Then
            For Each obj In ctl.ColumnHeaders
                obj.Text = LoadResString(CInt(obj.tag))
            Next
        Else
            nVal = 0
            nVal = Val(ctl.tag)
            If nVal > 0 Then ctl.Caption = LoadResString(nVal)
            nVal = 0
            nVal = Val(ctl.ToolTipText)
            If nVal > 0 Then ctl.ToolTipText = LoadResString(nVal)
        End If
    Next


End Sub

Public Function getDataDelimitor() As String

    If InStr(1, databaseName, "SQL", vbTextCompare) > 0 Then
        getDataDelimitor = "'"
    Else
        getDataDelimitor = "#"
    End If
    
End Function

Public Function SQLDate(DateText As Variant) As String
    SQLDate = DateDelimitor & Format$(DateText, "m/d/yyyy h:mm:ss AM/PM") & DateDelimitor
End Function

