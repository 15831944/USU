VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "Workspace"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit
' database id used to store this workspace and
' all data related to this workspace
Public workspaceId As Integer
' user id of workspace creator
Public creatorId As Integer
' start time of workspace
Public StartTime As Date
' end time of workspace
Public EndTime As Date
' time workspace last modified
Public dateLastModified As Date
' date the workspace was created
Public dateCreated As Date
' workspace name
Public WorkspaceName As String
' workspace description
Public WorkspaceDescription As String
' mode that is active at workspace start time
Public InitialModeID As Integer
' stores data for items in the tree
Public ChildNodes As New Collection
' data object tab control associated with workspace
Public tabCtrl As MSComctlLib.Tab


