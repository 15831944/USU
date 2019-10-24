VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "ModeClass"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Public ObjectInUse As Boolean
Public ModeName As String
Public ModeDescription As String
Public ProjectPath As String
Public BaselineRisk As Double
Public MediumRisk As Double
Public HighRisk As Double
Public ModeColor As Long
Public IsMapped As Boolean
'*******| m & b constants used in graphing, not stored in database |*********
Public Mh As Double
Public Bh As Double
Public Ml As Double
Public Bl As Double

Public Sub CalculateMBConstants()
    Mh = (PixelH - PixelM) / (Log(HighRisk) / Log(10) - Log(MediumRisk) / Log(10))
    Bh = PixelH - Mh * (Log(HighRisk) / Log(MediumRisk))
    Ml = (PixelM - PixelB) / (Log(MediumRisk) / Log(10) - Log(BaselineRisk) / Log(10))
    Bl = PixelM - Ml * (Log(MediumRisk) / Log(BaselineRisk))
End Sub

Public Sub CreateNewMode()
    ObjectInUse = False
    ModeName = "New Mode"
    ModeDescription = "New Mode Description"
    ProjectPath = "(none)"
    BaselineRisk = 0.00000001   ' 1e-8
    MediumRisk = 0.00001        ' 1e-5
    HighRisk = 0.001            ' 1e-3
    ModeColor = RGB(255, 0, 0)
    IsMapped = False
End Sub

Public Sub SetMode(Optional name As Variant, Optional Description As Variant, Optional Path As Variant, Optional Baseline As Variant, Optional Medium As Variant, Optional High As Variant, Optional Color As Variant, Optional Mapped As Variant)
    If Not IsMissing(name) And Not IsNull(name) Then ModeName = name
    If Not IsMissing(Description) And Not IsNull(Description) Then ModeDescription = Description
    If Not IsMissing(Path) And Not IsNull(Path) Then ProjectPath = Path
    If Not IsMissing(Baseline) And Not IsNull(Baseline) Then BaselineRisk = Baseline
    If Not IsMissing(Medium) And Not IsNull(Medium) Then MediumRisk = Medium
    If Not IsMissing(High) And Not IsNull(High) Then HighRisk = High
    If Not IsMissing(Color) And Not IsNull(Color) Then ModeColor = Color
    If Not IsMissing(Mapped) And Not IsNull(IsMapped) Then IsMapped = Mapped
End Sub

Public Sub CopyMode(Source As ModeClass)
    BaselineRisk = Source.BaselineRisk
    HighRisk = Source.HighRisk
    MediumRisk = Source.MediumRisk
    ModeColor = Source.ModeColor
    ModeDescription = Source.ModeDescription
    ModeName = Source.ModeName
    ObjectInUse = Source.ObjectInUse
    ProjectPath = Source.ProjectPath
    IsMapped = Source.IsMapped
End Sub

Public Function addmode(NewModeID As Integer) As Boolean
    ' let's search to see if there are any modes in the mode list which
    ' are not in use, if not, we'll make a new mode to add to the list
    Dim NewMode As ModeClass, frmMode As ModeProperties, holeFound As Boolean
    Set frmMode = New ModeProperties
    
    Dim modeID As Integer
    
    Dim i As Integer
    For i = 1 To ModeList.Count
        If ModeList.Item(i).ObjectInUse = False Then
            Set NewMode = ModeList.Item(i)
            holeFound = True
            modeID = i
            Exit For
        End If
    Next i
    
    If Not holeFound Then
        Set NewMode = New ModeClass
        ModeList.Add NewMode
        modeID = ModeList.Count
    End If
    
    NewMode.CreateNewMode
    Dim ModeColor As Integer, r As Integer, b As Integer, g As Integer
    ModeColor = modeID Mod 25
           
    If ModeColor Mod 3 = 0 Then
        r = 250 - (ModeColor / 3) * 10
        b = (ModeColor / 3) * 4
        g = (ModeColor / 3) * 4
    ElseIf ModeColor Mod 2 = 0 Then
        r = (ModeColor / 2) * 4
        b = 250 - (ModeColor / 2) * 10
        g = (ModeColor / 2) * 4
    Else
        g = 250 - (ModeColor) * 10
        r = (ModeColor) * 4
        b = (ModeColor) * 4
    End If
            
    NewMode.ModeColor = RGB(r, g, b)
    Set frmMode.ModeObject = NewMode
    frmMode.ModeIndex = modeID
    frmMode.Show 1
    
    If frmMode.Result = True Then
        NewMode.ObjectInUse = True
        ' add it to the database now
        Dim mySQLStatement As String, resultSet As rdoResultset
        
        mySQLStatement = "INSERT INTO [Mode] (ModeID, ModeName, ModeDesc, SaphireProjPath, BaselineRisk, MediumRisk, HighRisk, ModeColor, Mapped) " & _
            "VALUES (" & modeID & ", '" & NewMode.ModeName & "', '" & NewMode.ModeDescription & "', '" & NewMode.ProjectPath & "', " & _
            NewMode.BaselineRisk & ", " & NewMode.MediumRisk & ", " & NewMode.HighRisk & ", " & NewMode.ModeColor & "," & NewMode.IsMapped & ")"
        dbConnection.Execute (mySQLStatement)
        ModeCount = ModeCount + 1
        NewModeID = modeID
        addmode = True
        Exit Function
    End If
    addmode = False
End Function
