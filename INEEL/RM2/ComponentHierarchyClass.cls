VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "ComponentHierarchyClass"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Private LStrings(0 To 9) As String
Public nLevels As Integer
Public nLevelsInUse As Integer
Private Icons(0 To 9) As IPictureDisp
Private IconFName(0 To 9) As String
Private baseC As IPictureDisp
Public BaseName As String
Public BaseIconFileName As String
Public smallIcons As ImageList

Public Function LevelStrings(wIndex As Integer) As String
    LevelStrings = LStrings(wIndex)
End Function

Public Sub SetLevelString(wIndex As Integer, text As String)
    LStrings(wIndex) = text
End Sub

Public Function IconFileName(wIndex As Integer) As String
    IconFileName = IconFName(wIndex)
End Function

Public Function Icon(wIndex As Integer) As IPictureDisp
    Set Icon = Icons(wIndex)
End Function

Public Sub SetIcon(wIndex As Integer, FileName As String)
    'newIcon As IPictureDisp)
    IconFName(wIndex) = FileName
    If (FileName <> "" And FileName <> "(none)") Then
        ' could do error checking... check to see if this file exists
        Set Icons(wIndex) = LoadPicture(workingDirectory & "icons\" & FileName)
        smallIcons.ListImages.Remove (wIndex + 1)
        smallIcons.ListImages.Add wIndex + 1, , Icons(wIndex)
    End If
End Sub

Public Function BaseIcon() As IPictureDisp
    Set BaseIcon = baseC
End Function

Public Sub SetBaseIcon(FileName As String)
    'newIcon As IPictureDisp)
    BaseIconFileName = FileName
    If FileName <> "" And FileName <> "(none)" Then
        Set baseC = LoadPicture(workingDirectory & "icons\" & FileName)
        smallIcons.ListImages.Remove (11)
        smallIcons.ListImages.Add 11, , baseC
    End If
End Sub

Public Sub ConstructObject()
    Dim rArray As Variant, i As Integer
    
    Dim mySQLString As String, dataMissing As Boolean, text As String
    
    mySQLString = "SELECT nLevels, nLevelsInUse FROM CompHLevels"
    Dim resultSet As rdoResultset
    Set resultSet = dbConnection.OpenResultset(mySQLString)
    
    If Not resultSet.EOF Then
        rArray = resultSet.GetRows(1)
        nLevels = rArray(0, 0)
        nLevelsInUse = rArray(1, 0)
    Else
        dataMissing = True
    End If
    
    Set smallIcons = MDIMain.hForm.hImages
    
    smallIcons.ListImages.Add , , LoadPicture(workingDirectory & "icons\H10.bmp")
    smallIcons.ListImages.Add , , LoadPicture(workingDirectory & "icons\H10.bmp")
    smallIcons.ListImages.Add , , LoadPicture(workingDirectory & "icons\H10.bmp")
    smallIcons.ListImages.Add , , LoadPicture(workingDirectory & "icons\H10.bmp")
    smallIcons.ListImages.Add , , LoadPicture(workingDirectory & "icons\H10.bmp")
    smallIcons.ListImages.Add , , LoadPicture(workingDirectory & "icons\H10.bmp")
    smallIcons.ListImages.Add , , LoadPicture(workingDirectory & "icons\H10.bmp")
    smallIcons.ListImages.Add , , LoadPicture(workingDirectory & "icons\H10.bmp")
    smallIcons.ListImages.Add , , LoadPicture(workingDirectory & "icons\H10.bmp")
    smallIcons.ListImages.Add , , LoadPicture(workingDirectory & "icons\H10.bmp")
    smallIcons.ListImages.Add , , LoadPicture(workingDirectory & "icons\H10.bmp")
    
    If Not dataMissing Then
        mySQLString = "SELECT Name, IconFileName FROM CompHData WHERE hLevel = 10"
        Set resultSet = dbConnection.OpenResultset(mySQLString)
    
        If Not resultSet.EOF Then
            rArray = resultSet.GetRows(1)
            BaseName = rArray(0, 0)
            text = rArray(1, 0)
            SetBaseIcon text
            For i = 0 To nLevels - 1
                mySQLString = "SELECT Name, IconFileName FROM CompHData WHERE hLevel = " & i
                Set resultSet = dbConnection.OpenResultset(mySQLString)
        
                If Not resultSet.EOF Then
                    rArray = resultSet.GetRows(1)
                    text = rArray(0, 0)
                    SetLevelString i, text
                    text = rArray(1, 0)
                    SetIcon i, text
                Else
                    dataMissing = True
                    Exit For
                End If
            Next i
        Else
            dataMissing = True
        End If
    End If
    
    If dataMissing Then
        SetLevelString 0, "Function"
        SetLevelString 1, "System"
        SetLevelString 2, "Sub-System"
        SetLevelString 3, "Train"
        SetLevelString 4, "Component"
        SetIcon 0, "H10.bmp"
        SetIcon 1, "H1.bmp"
        SetIcon 2, "H2.bmp"
        SetIcon 3, "H3.bmp"
        SetIcon 4, "H4.bmp"
        BaseName = "Object"
        SetBaseIcon "H5.bmp"
        nLevels = 5
    End If
    
End Sub

