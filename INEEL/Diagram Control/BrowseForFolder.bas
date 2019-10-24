Attribute VB_Name = "BrowseForFolderModule"
Option Explicit

Private Const BIF_RETURNONLYFSDIRS = 1
Private Const BIF_DONTGOBELOWDOMAIN = 2
Private Const MAX_PATH = 260

Private Declare Function SHBrowseForFolder Lib _
"shell32" (lpbi As BrowseInfo) As Long

Private Declare Function SHGetPathFromIDList Lib _
"shell32" (ByVal pidList As Long, ByVal lpBuffer _
As String) As Long

Public Declare Function lstrcat Lib "kernel32" Alias "lstrcatA" (ByVal lpString1 As String, ByVal lpString2 As String) As Long

Private Declare Function GlobalAlloc Lib "kernel32" (ByVal wFlags As Long, ByVal dwBytes As Long) As Long
Private Declare Function GlobalLock Lib "kernel32" (ByVal hMem As Long) As Long
Private Declare Sub MoveMemory Lib "kernel32" Alias "RtlMoveMemory" _
    (ByVal dest As Any, ByVal src As Any, ByVal length As Long)
Private Declare Function GlobalFree Lib "kernel32" (ByVal hMem As Long) As Long
Private Declare Function GlobalUnlock Lib "kernel32" (ByVal hMem As Long) As Long

Const GMEM_MOVEABLE = &H2

Private Type BrowseInfo
   hWndOwner As Long
   pIDLRoot As Long
   pszDisplayName As Long
   lpszTitle As Long
   ulFlags As Long
   lpfnCallback As Long
   lParam As Long
   iImage As Long
End Type


Public Function BrowseForFolder(title As String) As String
    ' all this to make a null terminated string in memory
    Dim maxTitle As String * 100, handle As Long, pointer As Long, nullchar As String * 1
    nullchar = Chr$(0)
    maxTitle = title
    handle = GlobalAlloc(GMEM_MOVEABLE, 100)
    pointer = GlobalLock(handle)
    MoveMemory pointer, maxTitle, Len(title)
    MoveMemory pointer + Len(title), nullchar, 1
    
    'Opens a Browse Folders Dialog Box that displays the
    'directories in your computer
    Dim lpIDList As Long 'Declare Varibles
     
    Dim tBrowseInfo As BrowseInfo
      
    With tBrowseInfo
       .lpszTitle = pointer 'lstrcat(title, title)
       .ulFlags = BIF_RETURNONLYFSDIRS + BIF_DONTGOBELOWDOMAIN
    End With
    
    lpIDList = SHBrowseForFolder(tBrowseInfo)
    
    GlobalUnlock (pointer)
    GlobalFree (handle)
    
    If (lpIDList) Then
        BrowseForFolder = Space(MAX_PATH)
        SHGetPathFromIDList lpIDList, BrowseForFolder
        BrowseForFolder = Left(BrowseForFolder, InStr(BrowseForFolder, vbNullChar) - 1)
    Else
        BrowseForFolder = ""
    End If

End Function


