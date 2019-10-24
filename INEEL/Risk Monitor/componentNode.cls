VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "componentNode"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Public nodetype As componentNodeType
Public hLevel As Integer
Public ID As Integer
'Public parentID As Integer
Public name As String
Public diagramPath As String
Public totalBaseComponents As Integer
Public IsSelected As Boolean

Private iBaseComponents As Collection

Public Sub createBaseCompCollection()
    Set iBaseComponents = New Collection
End Sub

Public Function BaseComponentCount() As Integer
    BaseComponentCount = iBaseComponents.Count
End Function

Public Function GetBaseComponent(Index As Integer) As baseCompClass
    Set GetBaseComponent = iBaseComponents.Item(Index)
End Function

Public Sub SetBaseComponent(Index As Integer, GroupName As String, name As String, ID As Integer, nBEs As Integer)
    iBaseComponents.Item(Index).GroupName = GroupName
    iBaseComponents.Item(Index).name = name
    iBaseComponents.Item(Index).ID = ID
    iBaseComponents.Item(Index).nBEs = nBEs
End Sub

Public Sub AddBaseComponent(GroupName As String, name As String, ID As Integer, nBEs As Integer)
    Dim b As baseCompClass
    Set b = New baseCompClass
    b.GroupName = GroupName
    b.name = name
    b.ID = ID
    b.nBEs = nBEs
    iBaseComponents.Add b
End Sub

Public Sub DeleteBaseComponent(Index As Integer)
    iBaseComponents.Remove (Index)
End Sub

Public Sub ClearBaseComponents()
    Dim i As Integer
    For i = iBaseComponents.Count To 1 Step -1
        iBaseComponents.Remove (i)
    Next i
End Sub




