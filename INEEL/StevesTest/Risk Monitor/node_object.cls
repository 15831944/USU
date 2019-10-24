VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "node_object"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Public nodeKey As String
Public StartTime As String
Public EndTime As String
Public nodeName As String
'0=taskprofile 1= task, 2=procedure, 3=mode
Public nodetype As Integer
'Public nodeBranch As PVBranch
'Public parentBranch As PVBranch
Public parentNode As Integer
Public TaskAutoID As Integer
Public GroupAutoID As Integer
Public NodeState As Integer '0 = open 1 = Closed
Public DataRow As Integer 'ID number for tree view
Public Identification As Integer
'true = expanded false = colapsed
Public ExpandColapse As Boolean



