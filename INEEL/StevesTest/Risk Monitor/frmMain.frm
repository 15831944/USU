VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{22ACD161-99EB-11D2-9BB3-00400561D975}#1.0#0"; "PVCALENDAR.OCX"
Object = "{6ABB9000-48F8-11CF-AC42-0040332ED4E5}#4.0#0"; "SFTTREEX.OCX"
Object = "{82D32468-6EF3-11D5-BD26-0020AFF34773}#47.0#0"; "GANTT CONTROL VER 1.00.OCX"
Begin VB.MDIForm frmMain 
   BackColor       =   &H8000000C&
   Caption         =   "Risk Monitor"
   ClientHeight    =   8745
   ClientLeft      =   165
   ClientTop       =   450
   ClientWidth     =   11445
   Icon            =   "frmMain.frx":0000
   LinkTopic       =   "MDIForm1"
   MousePointer    =   1  'Arrow
   StartUpPosition =   2  'CenterScreen
   Begin VB.PictureBox LeftPane 
      Align           =   3  'Align Left
      AutoRedraw      =   -1  'True
      Height          =   7740
      Left            =   0
      MousePointer    =   1  'Arrow
      ScaleHeight     =   7680
      ScaleWidth      =   10155
      TabIndex        =   1
      Top             =   600
      Width           =   10215
      Begin SftTree.SftTree OOSTree 
         Height          =   2415
         Left            =   240
         TabIndex        =   9
         Top             =   4080
         Width           =   5535
         _Version        =   262144
         _ExtentX        =   9763
         _ExtentY        =   4260
         _StockProps     =   237
         BackColor       =   -2147483643
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderStyle     =   1
         Appearance      =   1
         Appearance      =   1
         BeginProperty ColHeaderFont {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BeginProperty RowHeaderFont {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BeginProperty ItemEditFont {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         GridStyle       =   3
         Columns         =   4
         ColWidth0       =   67
         ColTitle0       =   "Task"
         ColWidth1       =   67
         ColTitle1       =   "Start"
         ColBmp1         =   "frmMain.frx":0442
         ColWidth2       =   67
         ColTitle2       =   "End"
         ColBmp2         =   "frmMain.frx":045E
         ColWidth3       =   67
         ColTitle3       =   "Duration"
         ColBmp3         =   "frmMain.frx":047A
         AutoRespond     =   0   'False
         ColHeaderBackColor=   16760233
         Scrollbars      =   0
         RowColHeaderAppearance=   0
         LeftButtonOnly  =   0   'False
         RowHeaderStyle  =   192
         RowHeaderAppearance=   0
         ColPict1        =   "frmMain.frx":0496
         ColPict2        =   "frmMain.frx":04B2
         ColPict3        =   "frmMain.frx":04CE
         SplitterBar     =   -1  'True
         SplitColumn     =   1
         SplitterOffset  =   178
      End
      Begin SftTree.SftTree Tree 
         Height          =   2775
         Left            =   240
         TabIndex        =   7
         Top             =   1320
         Width           =   5535
         _Version        =   262144
         _ExtentX        =   9763
         _ExtentY        =   4895
         _StockProps     =   237
         BackColor       =   -2147483643
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderStyle     =   1
         Appearance      =   1
         Appearance      =   1
         BeginProperty ColHeaderFont {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BeginProperty RowHeaderFont {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BeginProperty ItemEditFont {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         GridStyle       =   3
         Columns         =   4
         ColWidth0       =   67
         ColTitle0       =   "Task"
         ColWidth1       =   67
         ColTitle1       =   "Start"
         ColBmp1         =   "frmMain.frx":04EA
         ColWidth2       =   67
         ColTitle2       =   "End"
         ColBmp2         =   "frmMain.frx":0506
         ColWidth3       =   67
         ColTitle3       =   "Duration"
         ColBmp3         =   "frmMain.frx":0522
         AutoRespond     =   0   'False
         ColHeaderBackColor=   16760233
         Scrollbars      =   0
         RowColHeaderAppearance=   0
         LeftButtonOnly  =   0   'False
         RowHeaderStyle  =   192
         RowHeaderAppearance=   0
         ColPict1        =   "frmMain.frx":053E
         ColPict2        =   "frmMain.frx":055A
         ColPict3        =   "frmMain.frx":0576
         SplitterBar     =   -1  'True
         SplitColumn     =   1
         SplitterOffset  =   178
      End
      Begin PVATLCALENDARLib.PVCalendar PVCalendar1 
         Height          =   5535
         Left            =   240
         TabIndex        =   15
         Top             =   1080
         Width           =   8175
         _Version        =   524288
         BorderStyle     =   0
         Appearance      =   1
         FirstDay        =   0
         Frame           =   3
         SelectMode      =   1
         DisplayFormat   =   0
         DateOrientation =   0
         CustomTextOrientation=   2
         ImageOrientation=   8
         DOWText0        =   "Sun"
         DOWText1        =   ""
         DOWText2        =   ""
         DOWText3        =   ""
         DOWText4        =   ""
         DOWText5        =   ""
         DOWText6        =   ""
         MonthText0      =   "January"
         MonthText1      =   "February"
         MonthText2      =   "March"
         MonthText3      =   "April"
         MonthText4      =   "May"
         MonthText5      =   "June"
         MonthText6      =   "July"
         MonthText7      =   "August"
         MonthText8      =   "September"
         MonthText9      =   "October"
         MonthText10     =   "November"
         MonthText11     =   "December"
         HeaderBackColor =   12632256
         HeaderForeColor =   0
         DisplayBackColor=   12632256
         DisplayForeColor=   0
         DayBackColor    =   12632256
         DayForeColor    =   0
         SelectedDayForeColor=   16777215
         SelectedDayBackColor=   8388608
         BeginProperty HeaderFont {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BeginProperty DOWFont {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BeginProperty DaysFont {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         MultiLineText   =   -1  'True
         EditMode        =   0
         BeginProperty TextFont {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
      End
      Begin GanttControl.GanttChart GanttChart1 
         Height          =   2175
         Left            =   5880
         TabIndex        =   14
         Top             =   4440
         Width           =   2535
         _ExtentX        =   4471
         _ExtentY        =   3836
         RowHeight       =   315
         TimeResolution  =   3
         HeaderHeight    =   640
         VisibleStartTime=   36526
         PeriodWidth     =   0
         StartTime       =   36526
         EndTime         =   40178
         VScrollVisible  =   0   'False
         HScrollVisible  =   -1  'True
         HeaderColor     =   16760233
         HeaderFontColor =   0
         HeaderGridColor =   0
         ChartBackgroundColor=   16777215
         ChartHorizontalColor=   11842740
         ChartVerticalColor=   15132390
         ChartBarOutlineColor=   0
         NotifyDuringVScroll=   -1  'True
         BeginProperty HeaderFont {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   12
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BeginProperty ganttChartFont {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   12
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ModePeriodBorderStyle=   1
         ModePeriodFillStyle=   0
         ModeBarStyle    =   1
         EnableDoubleClick=   0   'False
      End
      Begin GanttControl.GanttChart GanttChart 
         Height          =   2895
         Left            =   5880
         TabIndex        =   13
         Top             =   1440
         Width           =   2535
         _ExtentX        =   4471
         _ExtentY        =   5106
         RowHeight       =   315
         TimeResolution  =   3
         HeaderHeight    =   640
         VisibleStartTime=   36526
         PeriodWidth     =   0
         StartTime       =   36526
         EndTime         =   40178
         VScrollVisible  =   0   'False
         HScrollVisible  =   -1  'True
         HeaderColor     =   16760233
         HeaderFontColor =   0
         HeaderGridColor =   0
         ChartBackgroundColor=   16777215
         ChartHorizontalColor=   11842740
         ChartVerticalColor=   15132390
         ChartBarOutlineColor=   0
         NotifyDuringVScroll=   -1  'True
         BeginProperty HeaderFont {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   12
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BeginProperty ganttChartFont {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   12
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ModePeriodBorderStyle=   1
         ModePeriodFillStyle=   7
         ModeBarStyle    =   1
         EnableDoubleClick=   0   'False
      End
      Begin VB.CommandButton closeworkspace 
         Caption         =   "x"
         BeginProperty Font 
            Name            =   "Lucida Console"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   8160
         TabIndex        =   12
         ToolTipText     =   "Close Active Workspace"
         Top             =   600
         Width           =   255
      End
      Begin VB.CheckBox oos 
         Caption         =   "Out Of Service"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   9.75
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   3600
         TabIndex        =   11
         Top             =   720
         Width           =   3135
      End
      Begin VB.CheckBox optskmgmt 
         Caption         =   "Operational Task Management"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   9.75
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   360
         TabIndex        =   10
         Top             =   720
         Width           =   3135
      End
      Begin VB.CommandButton ImageSplitter 
         Appearance      =   0  'Flat
         Height          =   5535
         Left            =   5760
         MouseIcon       =   "frmMain.frx":0592
         MousePointer    =   99  'Custom
         TabIndex        =   8
         Top             =   960
         Width           =   135
      End
      Begin VB.TextBox Text4 
         Alignment       =   2  'Center
         BackColor       =   &H00FFBDA9&
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   12
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   285
         Left            =   5880
         MousePointer    =   1  'Arrow
         TabIndex        =   6
         Text            =   "Scheduler"
         Top             =   1080
         Width           =   2415
      End
      Begin VB.TextBox Text3 
         Alignment       =   2  'Center
         BackColor       =   &H00FFBDA9&
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   12
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   285
         Left            =   3000
         MousePointer    =   1  'Arrow
         TabIndex        =   5
         Text            =   "Schedule Manager"
         Top             =   1080
         Width           =   2655
      End
      Begin VB.TextBox Text2 
         Alignment       =   2  'Center
         BackColor       =   &H00FFBDA9&
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   12
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   285
         Left            =   240
         MousePointer    =   1  'Arrow
         TabIndex        =   4
         Text            =   "Task Hierarchy"
         Top             =   1080
         Width           =   2655
      End
      Begin MSComctlLib.TabStrip TabStrip1 
         Height          =   6615
         Left            =   120
         TabIndex        =   2
         Top             =   120
         Width           =   8415
         _ExtentX        =   14843
         _ExtentY        =   11668
         _Version        =   393216
         BeginProperty Tabs {1EFB6598-857C-11D1-B16A-00C0F0283628} 
            NumTabs         =   1
            BeginProperty Tab1 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
               ImageVarType    =   2
            EndProperty
         EndProperty
         MousePointer    =   1
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   12
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
      End
   End
   Begin MSComctlLib.Toolbar Toolbar1 
      Align           =   1  'Align Top
      Height          =   600
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   11445
      _ExtentX        =   20188
      _ExtentY        =   1058
      ButtonWidth     =   1032
      ButtonHeight    =   1005
      Appearance      =   1
      Style           =   1
      ImageList       =   "ImageList1"
      _Version        =   393216
      BeginProperty Buttons {66833FE8-8583-11D1-B16A-00C0F0283628} 
         NumButtons      =   17
         BeginProperty Button1 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "New"
            Object.ToolTipText     =   "New Workspace"
            ImageIndex      =   1
         EndProperty
         BeginProperty Button2 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Open"
            Object.ToolTipText     =   "Open Workspace"
            ImageIndex      =   2
         EndProperty
         BeginProperty Button3 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Save"
            Object.ToolTipText     =   "Copy Workspace"
            ImageIndex      =   3
         EndProperty
         BeginProperty Button4 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Print"
            Object.ToolTipText     =   "Print"
            ImageIndex      =   4
         EndProperty
         BeginProperty Button5 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button6 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Review and Oversight"
            Object.ToolTipText     =   "Review and Oversight"
            ImageIndex      =   5
         EndProperty
         BeginProperty Button7 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Scheduler"
            Object.ToolTipText     =   "Scheduler"
            ImageIndex      =   6
         EndProperty
         BeginProperty Button8 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Risk Meter"
            Object.ToolTipText     =   "Risk Meter"
            ImageIndex      =   7
         EndProperty
         BeginProperty Button9 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button10 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "AddGroup"
            Object.ToolTipText     =   "Insert Task Group"
            ImageIndex      =   8
            Style           =   5
            BeginProperty ButtonMenus {66833FEC-8583-11D1-B16A-00C0F0283628} 
               NumButtonMenus  =   2
               BeginProperty ButtonMenu1 {66833FEE-8583-11D1-B16A-00C0F0283628} 
                  Text            =   "Edit Task Group"
               EndProperty
               BeginProperty ButtonMenu2 {66833FEE-8583-11D1-B16A-00C0F0283628} 
                  Text            =   "Create Task Group"
               EndProperty
            EndProperty
         EndProperty
         BeginProperty Button11 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "AddTask"
            Object.ToolTipText     =   "Insert Task"
            ImageIndex      =   10
            Style           =   5
            BeginProperty ButtonMenus {66833FEC-8583-11D1-B16A-00C0F0283628} 
               NumButtonMenus  =   2
               BeginProperty ButtonMenu1 {66833FEE-8583-11D1-B16A-00C0F0283628} 
                  Text            =   "Edit Task"
               EndProperty
               BeginProperty ButtonMenu2 {66833FEE-8583-11D1-B16A-00C0F0283628} 
                  Text            =   "Create Task"
               EndProperty
            EndProperty
         EndProperty
         BeginProperty Button12 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "EditProc"
            Object.ToolTipText     =   "Edit Procedure"
            ImageIndex      =   9
            Style           =   5
            BeginProperty ButtonMenus {66833FEC-8583-11D1-B16A-00C0F0283628} 
               NumButtonMenus  =   1
               BeginProperty ButtonMenu1 {66833FEE-8583-11D1-B16A-00C0F0283628} 
                  Text            =   "Create Procedure"
               EndProperty
            EndProperty
         EndProperty
         BeginProperty Button13 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "AddMode"
            Object.ToolTipText     =   "Insert Mode"
            ImageIndex      =   11
            Style           =   5
            BeginProperty ButtonMenus {66833FEC-8583-11D1-B16A-00C0F0283628} 
               NumButtonMenus  =   1
               BeginProperty ButtonMenu1 {66833FEE-8583-11D1-B16A-00C0F0283628} 
                  Text            =   "Edit Modes"
               EndProperty
            EndProperty
         EndProperty
         BeginProperty Button14 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button15 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Remove"
            Object.ToolTipText     =   "Remove "
            ImageIndex      =   12
         EndProperty
         BeginProperty Button16 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button17 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Time Scale"
            Object.ToolTipText     =   "Time Scale/ Modify Start-End Time"
            ImageIndex      =   13
            Style           =   5
            BeginProperty ButtonMenus {66833FEC-8583-11D1-B16A-00C0F0283628} 
               NumButtonMenus  =   7
               BeginProperty ButtonMenu1 {66833FEE-8583-11D1-B16A-00C0F0283628} 
                  Key             =   "HourView"
                  Text            =   "  Hour View"
               EndProperty
               BeginProperty ButtonMenu2 {66833FEE-8583-11D1-B16A-00C0F0283628} 
                  Text            =   "  Shift View"
               EndProperty
               BeginProperty ButtonMenu3 {66833FEE-8583-11D1-B16A-00C0F0283628} 
                  Key             =   "DayView"
                  Text            =   "  Day View"
               EndProperty
               BeginProperty ButtonMenu4 {66833FEE-8583-11D1-B16A-00C0F0283628} 
                  Key             =   "WeekView"
                  Text            =   "  Week View"
               EndProperty
               BeginProperty ButtonMenu5 {66833FEE-8583-11D1-B16A-00C0F0283628} 
                  Key             =   "MonthView"
                  Text            =   "  Month View"
               EndProperty
               BeginProperty ButtonMenu6 {66833FEE-8583-11D1-B16A-00C0F0283628} 
                  Key             =   "QuarterView"
                  Text            =   "  Quarter View"
               EndProperty
               BeginProperty ButtonMenu7 {66833FEE-8583-11D1-B16A-00C0F0283628} 
                  Key             =   "YearView"
                  Text            =   "  Year View"
               EndProperty
            EndProperty
         EndProperty
      EndProperty
      MousePointer    =   1
      Begin MSComctlLib.ImageList ImageList1 
         Left            =   3600
         Top             =   -120
         _ExtentX        =   1005
         _ExtentY        =   1005
         BackColor       =   -2147483643
         ImageWidth      =   32
         ImageHeight     =   32
         MaskColor       =   12632256
         _Version        =   393216
         BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
            NumListImages   =   19
            BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
               Picture         =   "frmMain.frx":06E4
               Key             =   ""
            EndProperty
            BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
               Picture         =   "frmMain.frx":0B09
               Key             =   ""
            EndProperty
            BeginProperty ListImage3 {2C247F27-8591-11D1-B16A-00C0F0283628} 
               Picture         =   "frmMain.frx":0F41
               Key             =   ""
            EndProperty
            BeginProperty ListImage4 {2C247F27-8591-11D1-B16A-00C0F0283628} 
               Picture         =   "frmMain.frx":1375
               Key             =   ""
            EndProperty
            BeginProperty ListImage5 {2C247F27-8591-11D1-B16A-00C0F0283628} 
               Picture         =   "frmMain.frx":17A3
               Key             =   ""
            EndProperty
            BeginProperty ListImage6 {2C247F27-8591-11D1-B16A-00C0F0283628} 
               Picture         =   "frmMain.frx":18DB
               Key             =   ""
            EndProperty
            BeginProperty ListImage7 {2C247F27-8591-11D1-B16A-00C0F0283628} 
               Picture         =   "frmMain.frx":212D
               Key             =   ""
            EndProperty
            BeginProperty ListImage8 {2C247F27-8591-11D1-B16A-00C0F0283628} 
               Picture         =   "frmMain.frx":297F
               Key             =   ""
            EndProperty
            BeginProperty ListImage9 {2C247F27-8591-11D1-B16A-00C0F0283628} 
               Picture         =   "frmMain.frx":35D1
               Key             =   ""
            EndProperty
            BeginProperty ListImage10 {2C247F27-8591-11D1-B16A-00C0F0283628} 
               Picture         =   "frmMain.frx":4223
               Key             =   ""
            EndProperty
            BeginProperty ListImage11 {2C247F27-8591-11D1-B16A-00C0F0283628} 
               Picture         =   "frmMain.frx":4E75
               Key             =   ""
            EndProperty
            BeginProperty ListImage12 {2C247F27-8591-11D1-B16A-00C0F0283628} 
               Picture         =   "frmMain.frx":5AC7
               Key             =   ""
            EndProperty
            BeginProperty ListImage13 {2C247F27-8591-11D1-B16A-00C0F0283628} 
               Picture         =   "frmMain.frx":5EF0
               Key             =   ""
            EndProperty
            BeginProperty ListImage14 {2C247F27-8591-11D1-B16A-00C0F0283628} 
               Picture         =   "frmMain.frx":6742
               Key             =   ""
            EndProperty
            BeginProperty ListImage15 {2C247F27-8591-11D1-B16A-00C0F0283628} 
               Picture         =   "frmMain.frx":7478
               Key             =   ""
            EndProperty
            BeginProperty ListImage16 {2C247F27-8591-11D1-B16A-00C0F0283628} 
               Picture         =   "frmMain.frx":78E1
               Key             =   ""
            EndProperty
            BeginProperty ListImage17 {2C247F27-8591-11D1-B16A-00C0F0283628} 
               Picture         =   "frmMain.frx":79FB
               Key             =   ""
            EndProperty
            BeginProperty ListImage18 {2C247F27-8591-11D1-B16A-00C0F0283628} 
               Picture         =   "frmMain.frx":7B1B
               Key             =   ""
            EndProperty
            BeginProperty ListImage19 {2C247F27-8591-11D1-B16A-00C0F0283628} 
               Picture         =   "frmMain.frx":7CB8
               Key             =   ""
            EndProperty
         EndProperty
      End
   End
   Begin MSComctlLib.StatusBar sbStatusBar 
      Align           =   2  'Align Bottom
      Height          =   405
      Left            =   0
      TabIndex        =   3
      Top             =   8340
      Width           =   11445
      _ExtentX        =   20188
      _ExtentY        =   714
      _Version        =   393216
      BeginProperty Panels {8E3867A5-8586-11D1-B16A-00C0F0283628} 
         NumPanels       =   3
         BeginProperty Panel1 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            AutoSize        =   1
            Object.Width           =   14552
            Text            =   "Status"
            TextSave        =   "Status"
         EndProperty
         BeginProperty Panel2 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            Style           =   6
            AutoSize        =   2
            TextSave        =   "11/22/2001"
         EndProperty
         BeginProperty Panel3 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            Style           =   5
            AutoSize        =   2
            TextSave        =   "4:11 PM"
         EndProperty
      EndProperty
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      OLEDropMode     =   1
   End
   Begin VB.Menu mnuFile 
      Caption         =   "File"
      Begin VB.Menu mnuEditUser 
         Caption         =   "Edit User (Password)"
      End
      Begin VB.Menu mnuNewUser 
         Caption         =   "New User"
      End
      Begin VB.Menu separator1 
         Caption         =   "______________"
      End
      Begin VB.Menu mnuNew 
         Caption         =   "&New Workspace"
         Shortcut        =   ^N
      End
      Begin VB.Menu mnuOpen 
         Caption         =   "&Open Workspace"
         Shortcut        =   ^O
      End
      Begin VB.Menu mnuClose 
         Caption         =   "Close Workspace"
      End
      Begin VB.Menu copyworkspace 
         Caption         =   "Copy Workspace"
      End
      Begin VB.Menu deleteworkspace 
         Caption         =   "Delete Workspace"
      End
      Begin VB.Menu separator 
         Caption         =   "______________"
      End
      Begin VB.Menu Exit 
         Caption         =   "E&xit"
      End
   End
   Begin VB.Menu mnuEdit 
      Caption         =   "Edit"
      Begin VB.Menu mnuCut 
         Caption         =   "Cut"
         Shortcut        =   ^X
      End
      Begin VB.Menu mnuCopy 
         Caption         =   "&Copy"
         Shortcut        =   ^C
      End
      Begin VB.Menu mnuPaste 
         Caption         =   "Paste"
         Shortcut        =   ^V
      End
   End
   Begin VB.Menu mnuView 
      Caption         =   "View"
      Begin VB.Menu mnuViewTskMgmt 
         Caption         =   "Task Management View"
      End
      Begin VB.Menu mnuViewRevOvst 
         Caption         =   "Review and Oversight View"
      End
      Begin VB.Menu mnuViewRiskMeter 
         Caption         =   "Risk Meter"
      End
      Begin VB.Menu mnuViewSaphireStats 
         Caption         =   "SAPHIRE Statistics"
      End
   End
   Begin VB.Menu Task 
      Caption         =   "Task"
      Begin VB.Menu agroup 
         Caption         =   "Add Group"
      End
      Begin VB.Menu atask 
         Caption         =   "AddTask"
      End
      Begin VB.Menu amode 
         Caption         =   "Add Mode"
      End
      Begin VB.Menu CSETime 
         Caption         =   "Change Start and End Time"
      End
      Begin VB.Menu removei 
         Caption         =   "Remove Item"
      End
   End
   Begin VB.Menu mnuComponents 
      Caption         =   "Component"
      Begin VB.Menu addComponent 
         Caption         =   "Add OOS Component"
      End
      Begin VB.Menu RemoveComponent 
         Caption         =   "Remove OOS Component"
      End
      Begin VB.Menu ChangeComponent 
         Caption         =   "Change Component Settings"
      End
      Begin VB.Menu mnuComponentMap 
         Caption         =   "Component Map"
      End
      Begin VB.Menu mnuBasicEventMap 
         Caption         =   "Edit Basic Event Map"
      End
   End
   Begin VB.Menu TreeMenu 
      Caption         =   "TreeMenu"
      Visible         =   0   'False
      Begin VB.Menu AddGroup 
         Caption         =   "Add Group"
      End
      Begin VB.Menu AddTask 
         Caption         =   "Add Task"
      End
      Begin VB.Menu addmode 
         Caption         =   "Add Mode"
      End
      Begin VB.Menu StartEnd 
         Caption         =   "Change Start and End Time"
      End
      Begin VB.Menu Ritem 
         Caption         =   "Remove Item"
      End
   End
   Begin VB.Menu OOSTreeMenu 
      Caption         =   "OOSTreeMenu"
      Visible         =   0   'False
      Begin VB.Menu aComponent 
         Caption         =   "Add Component"
      End
      Begin VB.Menu rComponent 
         Caption         =   "Remove Component"
      End
      Begin VB.Menu SETime 
         Caption         =   "Change Start and End Time"
      End
   End
   Begin VB.Menu Risk 
      Caption         =   "Risk"
      Begin VB.Menu Refresh 
         Caption         =   "Refresh Risk Values"
      End
      Begin VB.Menu SetValues 
         Caption         =   "Set Cut Off Values"
      End
   End
   Begin VB.Menu mnuPreferences 
      Caption         =   "Preferences"
      Begin VB.Menu mnuPersonalSettings 
         Caption         =   "Personal Settings"
         Begin VB.Menu mnuColorOptions 
            Caption         =   "Color Options"
            Begin VB.Menu mnuRiskColor 
               Caption         =   "Risk Color"
            End
            Begin VB.Menu mnuBarColor 
               Caption         =   "Bar Color"
            End
            Begin VB.Menu mnuWorkspaceColor 
               Caption         =   "Workspace Color"
            End
         End
         Begin VB.Menu mnuModeOptions 
            Caption         =   "Mode Display"
         End
      End
      Begin VB.Menu mnuProjectSettings 
         Caption         =   "Project Settings"
         Begin VB.Menu mnuModeColor 
            Caption         =   "Mode Color"
         End
      End
      Begin VB.Menu mnuWorkspaceSettings 
         Caption         =   "Workspace Settings"
      End
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Public active As Boolean 'determine if user has existing open workspaces
Public WorkspacesLoaded As Boolean

'Images for tree variables.
Public nodePict1 As IPictureDisp
Public nodePict2 As IPictureDisp
Public nodePict3 As IPictureDisp
Public nodePict4 As IPictureDisp
Public nodePict5 As IPictureDisp
Public nodePict6 As IPictureDisp
Public nodePict7 As IPictureDisp

'cut of values for risk - will be set by user.
Public BaselineRisk As Double
Public MediumRisk As Double
Public HighRisk As Double

'used to determine if a popup menu is currently open
Public popupmenuopen As Boolean

Private Declare Function SendMessage Lib "user32" Alias "SendMessageA" (ByVal hwnd As Long, ByVal wMsg As Long, ByVal wParam As Long, ByVal lParam As Any) As Long
Const EM_UNDO = &HC7
Private Declare Function OSWinHelp% Lib "user32" Alias "WinHelpA" (ByVal hwnd&, ByVal HelpFile$, ByVal wCommand%, dwData As Any)

Private workspaces As Collection
Private activeWorkspace As Workspace
 
'Counter for number of open workspaces
Public activeWorkspaceIndex As Integer
 
Const NAME_COLUMN = 0
Const TYPE_COLUMN = 1
Const SIZE_COLUMN = 2
Const DATE_COLUMN = 3
Public curColorScheme As Integer
Private colors(1 To 16, 0 To 1) As Long
Private colorTable(1 To 11) As Long
' the first dimension of colors refers to a specific color group
' for example, Index 1 is the background color.  this is the color that
' the background of most windows should be, in a control area...
' to create a new color group, when none of the existing groups define
' correctly the area a color should be, one can be created by adding a new
' row to the database...  then this can be used in code.  The user can
' modify this color for a color scheme by going to the options menu

Dim mbMoving As Boolean
Dim InTaskMgmtView As Boolean
Dim NeedUpdateRiskValues As Boolean
' this variable is used in a couple of ways.
' first, it is set to true when the month or year of the calendar is
' changed.  it is set to true when the active workspace changes
' basically, it means that the data in the calendar needs to be updated

'put the component hierarchy form in memory for duration of program...
Public compMap As ComponentMap
Public hForm As hierarchyIconsForm
Private VScreen As VScreen
Public DisplayComponentMapFirst As Boolean

'********************************************************************
' STEVE'S DLL SUPPORT
Public threadActive As Long
Public dataBaseChangesMade As Long
Private Declare Function StartWorkerThread Lib "riskMon" (tActive As Long, cMade As Long, ByVal oName As String, ByVal runningDir As String, ByVal IsAccessDB As Long) As Long
Private Declare Function CloseWorkerThread Lib "riskMon" () As Long
'    Starts the main thread of the program
'tActive:
'cMade:
'    OdbcName: the name of the odbc driver to be used
'    ProjLoc: the location of the saphire project
'    RunningDir: The directory the program is running in or were you want the error logs stored
'
Private Declare Function DoAllUpdates Lib "riskMon" (percent As Long) As Long
'    Percent: the percent of what has been completed so far.
'
Private Declare Function ContinueAllUpdates Lib "riskMon" (percent As Long) As Long
'    Percent: the percent of what has been completed so far.
'
Private Declare Function SetWorkspace Lib "riskMon" (WorkID As Long) As Long
'    WorkID: the workspace ID that is current
Private Declare Function GetAverageUpdateSpeed Lib "riskMon" (totalUpdatesDone As Long) As Long
' returns average speed and total updates done
Private Declare Function SuspendUpdates Lib "riskMon" () As Long

Private Declare Function ResumeUpdates Lib "riskMon" () As Long

'********************************************************************

'Function/Subroutine:Active_Workspace_Add
'Purpose: Add a workspace to the workspace collection
Public Function Active_Workspace_Add(WS As Workspace)
    workspaces.Add WS
End Function

Public Function GetActiveWorkspace() As Workspace
    Set GetActiveWorkspace = activeWorkspace
End Function

'Function/Subroutine:Active_Workspace_Remove
'Purpose:Remove a workspace from the workspace collection
Public Function Active_Workspace_Remove(WS As Workspace)
    
    Dim i As Integer
    
    For i = workspaces.Count To 1 Step -1
        If workspaces.Item(i).workspaceId = WS.workspaceId Then
            workspaces.Remove i
            activeWorkspaceIndex = activeWorkspaceIndex - 1
        End If
    Next i
    
    If activeWorkspaceIndex = 0 Then activeWorkspaceIndex = 1
    Set activeWorkspace = workspaces.Item(activeWorkspaceIndex)
    TabStrip1_Click
    
End Function
'Function/Subroutine:Active_Workspace
'Purpose:adds a new workspace to the worspaces collection.
Public Function Active_Workspace() As Workspace
    
    activeWorkspaceIndex = workspaces.Count + 1
    Set activeWorkspace = New Workspace
    Set Active_Workspace = activeWorkspace
    
End Function
'Function: AddComponent
'Purpose: add a component to the OOS list when the option is selected
'from the popupmenu
Private Sub AddComponent_Click()
    ButtonFunctions.AddOOSComponents activeWorkspace
End Sub
'Function:AddGroup_Click
'Purpose: add a task group to a workspace when the option is selected
'from the popupmenu
Private Sub AddGroup_Click()
'
    ButtonFunctions.AddGroup activeWorkspace
End Sub
'function: addmode_click
'Handles the click of add mode from the popup tree menu
Private Sub addmode_Click()
    ButtonFunctions.addmode activeWorkspace
End Sub

'Function:AddTask_Click
'Purpose:add a task to a workspace when the option is selected
'from the popupmenu
Private Sub AddTask_Click()
    ButtonFunctions.AddTask activeWorkspace
End Sub
'function: agroup_click
'Handles the click of add group from the task menu
Private Sub agroup_Click()
    ButtonFunctions.AddGroup activeWorkspace
End Sub
'function: amode_click
'Handles the click of Add Mode from the task menu
Private Sub amode_Click()
    ButtonFunctions.addmode activeWorkspace
End Sub

'function: atask_click
'Handles the click of Add Task from the task menu
Private Sub atask_Click()
    ButtonFunctions.AddTask activeWorkspace
End Sub

'Function:ChangeComponent_Click
'Purpose:Change the start and end time of a component in the OOS list
Private Sub ChangeComponent_Click()
    ButtonFunctions.ChangeOOSComponents activeWorkspace
End Sub
'Function:closeworkspace_Click
'Purpose: close the active workspace if it is not the last one open.
Private Sub closeworkspace_Click()
    OpenWorkspaces.close_workspace activeWorkspace
End Sub

Private Sub copyworkspace_Click()
    ButtonFunctions.Copy_Workspace activeWorkspace
End Sub

'Function: CSETime_Click
'Purpose: Handles the event when the set time option is selected
'from the task menu
Private Sub CSETime_Click()
    Dim Index As Long
    Index = Tree.ListSelection
    
    sbStatusBar.Panels(1).text = "Updating Data..."
    If Tree.ItemPicture(Index) = nodePict3 Then 'procedure node
            Dim StartDate As Date
            Dim EndDate As Date
            Dim OldEnd As Date
            Dim OldStart As Date
            Dim i As Integer
            Dim WSID As Integer
            Dim itemID As Integer
            Dim taskref As Integer
            Dim group As Integer
            Dim mySQL As String
            
            'Popup window to allow user to select new date and time
            TimeEdit.LabelText = Tree.CellText(Index, 0)
            TimeEdit.StartDate = Tree.CellText(Index, 1)
            TimeEdit.EndDate = Tree.CellText(Index, 2)
            TimeEdit.Show vbModal
            StartDate = TimeEdit.StartDate
            EndDate = TimeEdit.EndDate
            
            'if the user canceled the operation exit function
            If TimeEdit.CancelClick = True Then
                Unload TimeEdit
                Exit Sub
            End If
            
            Unload TimeEdit
            
            'Change node in collection
                For i = 1 To activeWorkspace.ChildNodes.Count
                    If activeWorkspace.ChildNodes.Item(i).DataRow = Index Then
                        OldStart = activeWorkspace.ChildNodes.Item(i).StartTime
                        OldEnd = activeWorkspace.ChildNodes.Item(i).EndTime
                        
                        Exit For
                    End If
                Next i
                
                WSID = activeWorkspace.workspaceId
                itemID = activeWorkspace.ChildNodes.Item(i).Identification
                taskref = activeWorkspace.ChildNodes.Item(i).TaskAutoID
                group = activeWorkspace.ChildNodes.Item(i).GroupAutoID
            
            'change item in database table
            If pManager.ChangeProcedureTime(WSID, itemID, taskref, OldStart, OldEnd, StartDate, EndDate) = False Then
                MsgBox "Can't Change Procedure Time Due to Mode Conflict", vbInformation
            Else
                activeWorkspace.ChildNodes.Item(i).StartTime = StartDate
                activeWorkspace.ChildNodes.Item(i).EndTime = EndDate
            End If
            
            OpenWorkspaces.LoadData activeWorkspace
        
        ElseIf Tree.ItemPicture(Index) = nodePict2 Then 'task node
            
            'let user select new data
            TimeEdit.LabelText = Tree.CellText(Index, 0)
            TimeEdit.StartDate = Tree.CellText(Index, 1)
            TimeEdit.EndDate = Tree.CellText(Index, 2)
            TimeEdit.Show 1
            StartDate = TimeEdit.StartDate
            EndDate = TimeEdit.EndDate
            
            'if the user cancled the action stop the function
            If TimeEdit.CancelClick = True Then
                Unload TimeEdit
                Exit Sub
            End If
            Unload TimeEdit
            
            'Change node in collection
            For i = 1 To activeWorkspace.ChildNodes.Count
                If activeWorkspace.ChildNodes.Item(i).DataRow = Index Then
                    activeWorkspace.ChildNodes.Item(i).StartTime = StartDate
                    activeWorkspace.ChildNodes.Item(i).EndTime = EndDate
                    Exit For
                End If
            Next i
            
            WSID = activeWorkspace.workspaceId
            itemID = activeWorkspace.ChildNodes.Item(i).Identification
            taskref = activeWorkspace.ChildNodes.Item(i).TaskAutoID
            group = activeWorkspace.ChildNodes.Item(i).GroupAutoID
            
            'change item in table
            mySQL = "UPDATE WorkspaceTaskSchedule SET StartTime = " _
                & SQLDate(StartDate) & ", EndTime = " & SQLDate(EndDate) & _
                " WHERE WorkspaceID = " & WSID & " AND TaskId = " _
                & itemID & " AND AutoReference = " & taskref
                
            dbConnection.Execute (mySQL)
            
            'Load changed data into objects.
            OpenWorkspaces.LoadData activeWorkspace
            
        ElseIf Tree.ItemPicture(Index) = nodePict4 Then 'mode node
            Dim RowReturn As Integer
            Dim rarray As Variant
            Dim resultSet As rdoResultset
            
            RowReturn = 0
            'get list of workspace modes
            mySQL = "SELECT ModeID, StartTime, ModeName FROM [WorkspaceMode] WHERE WorkspaceID = " & MDIMain.returnID & " ORDER BY StartTime"
            Set resultSet = dbConnection.OpenResultset(mySQL, rdOpenKeyset)
            
            'If there are no modes
            If resultSet.EOF Then
                MsgBox "No Modes Running", vbInformation
                Exit Sub
            'Otherwise add them to the list
            Else
                While Not resultSet.EOF
                resultSet.MoveNext
                RowReturn = RowReturn + 1
                Wend
                resultSet.MoveFirst
                rarray = resultSet.GetRows(RowReturn)
            End If
        
            'move items to removeMode form
            EditModeTime.rarray = rarray
            EditModeTime.RowReturn = RowReturn
            EditModeTime.aWorkspace = activeWorkspace
            'Implement remove mode form - does actual removal of mode
            EditModeTime.Show 1
            Unload EditModeTime
        End If
        sbStatusBar.Panels(1).text = "Running"
End Sub
'Function:deleteworkspace_click
'Purpose: Delete a workspace that is not in use.
Private Sub deleteworkspace_Click()
    ButtonFunctions.Delete_workspace
End Sub

'Function:Exit_Click
'Purpose:exit the program
Private Sub Exit_Click()
    If DLLActive Then
        If (CloseWorkerThread = 0) Then
            MsgBox "Close worker thread failed"
        End If
    End If
    End
End Sub

'Function GanttChart_ChangeModePeriodRequested
'Purpose: handle drag event on mode bar
Private Sub GanttChart_ChangeModePeriodRequested(modeID As Integer, modeText As String, ArrayIndex As Integer, proposedTime As Date, currentTime As Date)
    'pManager.isModeValid proposedTime, 2, activeWorkspace
    
    ButtonFunctions.ChangeModeTime modeID, modeText, currentTime, proposedTime, activeWorkspace

End Sub

'Function: GanttChart_ChangeRowRequested
'Purpose: Function is use when a bar in the OOS gantt chart is draged
'If the bar corresponds to a procedure a check is made to make sure
'the move is permitted and then the data is updated in the database
Private Sub GanttChart_ChangeRowRequested(rowID As Integer, proposedStartTime As Date, proposedEndTime As Date, currentStartTime As Date, currentEndTime As Date)
    Dim Index As Integer
    
    Index = rowID
    'make sure node is editable
    If Tree.ItemPicture(Index) = nodePict1 Or Tree.ItemPicture(Index) = nodePict5 Or Tree.ItemPicture(Index) = nodePict4 Then
            Exit Sub
        'for procedure
    ElseIf Tree.ItemPicture(Index) = nodePict3 Then
            Dim StartDate As Date
            Dim EndDate As Date
            Dim i As Integer
            Dim WSID As Integer
            Dim itemID As Integer
            Dim taskref As Integer
            Dim group As Integer
            Dim mySQL As String
            
            StartDate = proposedStartTime
            EndDate = proposedEndTime
            
            'Change node in collection - i gets used below so watch it dosent get changed
                For i = 1 To activeWorkspace.ChildNodes.Count
                    If activeWorkspace.ChildNodes.Item(i).DataRow = Index Then
                        Exit For
                    End If
                Next i
                
                WSID = activeWorkspace.workspaceId
                itemID = activeWorkspace.ChildNodes.Item(i).Identification
                taskref = activeWorkspace.ChildNodes.Item(i).TaskAutoID
                group = activeWorkspace.ChildNodes.Item(i).GroupAutoID

            'change item in table
            If pManager.ChangeProcedureTime(WSID, itemID, taskref, currentStartTime, currentEndTime, StartDate, EndDate) = False Then
                MsgBox "Can't Change Procedure Time due to Mode Conflict", vbInformation
            Else
                activeWorkspace.ChildNodes.Item(i).StartTime = StartDate
                activeWorkspace.ChildNodes.Item(i).EndTime = EndDate
                'change item in tree
                'OpenWorkspaces.LoadData activeWorkspace
                Tree.CellText(Index, 1) = StartDate
                Tree.CellText(Index, 2) = EndDate
                Tree.CellText(Index, 3) = DateDiff("h", StartDate, EndDate) & " Hour(s)"
                GanttChart.SetRowStartEndTimes StartDate, EndDate
                'GanttChart.RedrawGanttChart
            End If
            
            
        'for task
        Else
            
            
            StartDate = proposedStartTime
            EndDate = proposedEndTime
            
            
            'Change node in collection
            For i = 1 To activeWorkspace.ChildNodes.Count
                If activeWorkspace.ChildNodes.Item(i).DataRow = Index Then
                    activeWorkspace.ChildNodes.Item(i).StartTime = StartDate
                    activeWorkspace.ChildNodes.Item(i).EndTime = EndDate
                    Exit For
                End If
            Next i
            
            WSID = activeWorkspace.workspaceId
            itemID = activeWorkspace.ChildNodes.Item(i).Identification
            taskref = activeWorkspace.ChildNodes.Item(i).TaskAutoID
            group = activeWorkspace.ChildNodes.Item(i).GroupAutoID
            
            'change item in table
            mySQL = "UPDATE WorkspaceTaskSchedule SET StartTime = " _
                & SQLDate(StartDate) & ", EndTime = " & SQLDate(EndDate) & _
                " WHERE WorkspaceID = " & WSID & " AND TaskId = " _
                & itemID & " AND AutoReference = " & taskref
                
            dbConnection.Execute (mySQL)
            'OpenWorkspaces.LoadData activeWorkspace
            'change item in tree
            'OpenWorkspaces.LoadData activeWorkspace
            Tree.CellText(Index, 1) = StartDate
            Tree.CellText(Index, 2) = EndDate
            Tree.CellText(Index, 3) = DateDiff("h", StartDate, EndDate) & " Hour(s)"
            GanttChart.SetRowStartEndTimes StartDate, EndDate
            'GanttChart.RedrawGanttChart
        End If
End Sub

Private Sub GanttChart_Click(wRow As Integer)
'
    Dim tempInt As Integer
    
    If wRow > 0 Then
        tempInt = GanttChart.GetRowID(wRow)
        
        If tempInt > 0 Then
            Tree.Selected(tempInt) = True
            
            Dim temp As SelectionType
            temp.row = wRow
            temp.sType = HasFocus
            GanttChart.Selection = temp
        End If
    End If
    
End Sub

'Function: GanttChart1_ChangeRowRequested
'Purpose: Function is use when a bar in the OOS gantt chart is draged
'If the bar corresponds to a component a check is made to make sure
'the move is permitted and then the data is updated in the database
Private Sub GanttChart1_ChangeRowRequested(rowID As Integer, proposedStartTime As Date, proposedEndTime As Date, currentStartTime As Date, currentEndTime As Date)
    Dim Index As Integer
    
    Index = rowID
    If OOSTree.ItemPicture(Index) = nodePict5 Or OOSTree.ItemPicture(Index) = nodePict4 Then
            Exit Sub
        'for procedure
    ElseIf OOSTree.ItemPicture(Index) = nodePict6 Then
            Dim OldStart As Date
            Dim OldEnd As Date
            Dim i As Integer
            Dim WSID As Integer
            Dim itemID As Integer
            Dim taskref As Integer
            Dim group As Integer
            Dim mySQL As String
            Dim name As String
            Dim StartDate As Date
            Dim EndDate As Date
            Dim resultSet As rdoResultset
            Dim rarray As Variant
            Dim RowReturn As Integer
            Dim overlap As Boolean
            
            'save the old start and end time for database queries
            OldStart = currentStartTime
            OldEnd = currentEndTime
            
            'dont change if node type is not component
            If Index > 1 Then
    
                name = MDIMain.OOSTree.CellText(Index, 0)
                StartDate = proposedStartTime
                EndDate = proposedEndTime
                
                'Check to see if component is already in the out of service list
                mySQL = "SELECT StartTime, EndTime FROM [OOSList] WHERE ComponentName = '" & name & "' AND WorkspaceID = " & activeWorkspace.workspaceId
                Set resultSet = dbConnection.OpenResultset(mySQL, rdOpenKeyset)
                
                If resultSet.EOF Then
                    pManager.UpdateOOSItem StartDate, EndDate, OldStart, OldEnd, activeWorkspace.workspaceId, name
                    OpenWorkspaces.ooslistControl activeWorkspace
                    MDIMain.GanttChart1.RedrawGanttChart
                Else
                    'Otherwise check to make sure no overlap of
                    'components exists.
                    While Not resultSet.EOF
                        resultSet.MoveNext
                        RowReturn = RowReturn + 1
                    Wend
                    resultSet.MoveFirst
                    rarray = resultSet.GetRows(RowReturn)
                        
                    Dim tempstart As Date
                    Dim tempend As Date
                    Dim startdifference As Double
                    Dim enddifference As Double
                    
                    
                    For i = 0 To RowReturn - 1
                        tempstart = rarray(0, i)
                        tempend = rarray(1, i)
                        startdifference = (OldStart - tempstart)
                        enddifference = (OldEnd - tempend)
                        
                        If startdifference = 0 And enddifference = 0 Then
                            'do nothing - dont check components own record
                        ElseIf (startdifference < (1 ^ -10) And startdifference >= 0) And (enddifference < (1 ^ -10) And enddifference >= 0) Then
                            'do nothing = dont check components won record
                        ElseIf (startdifference > -(1 ^ -10) And startdifference <= 0) And (enddifference > -(1 ^ -10) And enddifference <= 0) Then
                            'Do Nothing - dont check components own record
                        Else
                            If (StartDate > rarray(0, i) And StartDate < rarray(1, i)) Or (StartDate < rarray(0, i) And EndDate > rarray(0, i)) Then
                                MsgBox "Can't Place Component OOS More Than Once During Time Period", vbInformation
                                overlap = True
                            ElseIf (EndDate > rarray(0, i) And EndDate < rarray(1, i)) Or (EndDate < rarray(1, i) And StartDate > rarray(1, i)) Then
                                MsgBox "Can't Place Component OOS More Than Once During Time Period", vbInformation
                                overlap = True
                            End If
                        End If
                    Next i
                    
                    If overlap = False Then
                        pManager.UpdateOOSItem StartDate, EndDate, OldStart, OldEnd, activeWorkspace.workspaceId, name
                        
                        'OpenWorkspaces.ooslistControl activeWorkspace
                        GanttChart1.SetRowStartEndTimes StartDate, EndDate
                        OOSTree.CellText(Index, 1) = StartDate
                        OOSTree.CellText(Index, 2) = EndDate
                        'MDIMain.GanttChart1.RedrawGanttChart
                    End If
                End If
            Else
                MsgBox "No Component Selected", vbInformation
            End If
   End If
End Sub
'Function: GanttChart_VerticalScrollChange
'Purpose: Event raised when the vertical scroll bar is moved. The
'function makes sure the treevew scrolls with the gantt chart by
'setting the top visible rows the same.
Private Sub GanttChart_VerticalScrollChange(TopRow As Integer)
    Dim i As Integer
    Dim topRowID As Integer
    If (TopRow = 1) Then
        Tree.TopIndex = 0
    Else
        'gets the ID number associated with gantt chart row which has
        'been set to the corresponding tree index number
        topRowID = GanttChart.GetRowID(TopRow - 1)
        
        'account for the off by one that appears due to the ganttchart
        'header height.
        For i = topRowID - 1 To 1 Step -1
            If Tree.ItemShown(i) Then
                Tree.TopIndex = i
                Exit For
            End If
        Next i
    End If
    
    
    DoEvents
End Sub

Private Sub GanttChart1_Click(wRow As Integer)
    Dim tempInt As Integer
    
    If wRow > 0 Then
        tempInt = GanttChart1.GetRowID(wRow)
        OOSTree.Selected(tempInt) = True
        
        Dim temp As SelectionType
        temp.row = wRow
        temp.sType = HasFocus
        GanttChart1.Selection = temp
    End If
End Sub

'Function: GanttChart1_VerticalScrollChange
'Purpose: Event raised when the vertical scroll bar is moved. The
'function makes sure the treevew scrolls with the gantt chart by
'setting the top visible rows the same.
Private Sub GanttChart1_VerticalScrollChange(TopRow As Integer)
    Dim i As Integer
    
    Dim topRowID As Integer
        If (TopRow = 1) Then
            OOSTree.TopIndex = 0
        Else
            'gets the ID number associated with gantt chart row which has
            'been set to the corresponding tree index number
            topRowID = GanttChart1.GetRowID(TopRow - 1)
        
            'account for the off by one that appears due to the ganttchart
            'header height.
            For i = topRowID - 1 To 1 Step -1
                If OOSTree.ItemShown(i) Then
                    OOSTree.TopIndex = i
                    Exit For
                End If
            Next i
        End If
        DoEvents
        
End Sub

'Function/Subroutine:LeftPane_Resize
'Purpose: Gets called whenever the main window gets resized. Sets the
'size values of all objects on the main window.
Private Sub LeftPane_Resize()
    Dim pCalendarWidth As Integer, pCalendarHeight As Integer
    Dim pCalendarLeft As Integer, pCalendarTop As Integer
    
    Tree.Visible = False
    GanttChart.Visible = False
    GanttChart1.Visible = False
    OOSTree.Visible = False
    
    LeftPane.Width = Me.Width
    
    If LeftPane.Height > 2000 And LeftPane.Width > 1200 Then
        TabStrip1.Height = LeftPane.Height - 400
        
        Text2.Height = TabStrip1.Top + 280
        Text3.Height = Text2.Height
        Text4.Height = Text2.Height
        
        Tree.Top = Text2.Top + Text2.Height + Screen.TwipsPerPixelY * 3
        GanttChart.Top = Tree.Top + Screen.TwipsPerPixelY
        Tree.Height = TabStrip1.Height - Tree.Top - Screen.TwipsPerPixelY * 2
        GanttChart.Height = Tree.Height - Screen.TwipsPerPixelY * 2
        
        sbStatusBar.Top = Me.Height - sbStatusBar.Height
        
        ImageSplitter.Top = Tree.Top + Screen.TwipsPerPixelY * 2
        ImageSplitter.Height = Tree.Height - Screen.TwipsPerPixelY * 4
        
        pCalendarTop = Text2.Top
        pCalendarHeight = Tree.Height + Tree.Top - Text2.Top
   
        TabStrip1.Left = LeftPane.Left + 100
        TabStrip1.Width = LeftPane.Width - 400
        Tree.Left = TabStrip1.Left + Screen.TwipsPerPixelX * 3
        Tree.Width = (TabStrip1.Width - Screen.TwipsPerPixelX * 9) * 2 / 3 - Screen.TwipsPerPixelX
        GanttChart.Width = (TabStrip1.Width - Screen.TwipsPerPixelX * 9) / 3
        GanttChart.Left = Tree.Left + Tree.Width + Screen.TwipsPerPixelX
        Text2.Left = Tree.Left
        Text2.Width = Tree.SplitterOffset + 75
        Text3.Left = Tree.SplitterOffset + 265
        Text3.Width = Tree.Width - Tree.SplitterOffset - 140
        Text4.Left = GanttChart.Left
        Text4.Width = GanttChart.Width

        ImageSplitter.Left = Tree.Left + Tree.Width - Screen.TwipsPerPixelX * 2
        ImageSplitter.Width = Screen.TwipsPerPixelX * 5

        pCalendarWidth = TabStrip1.Width - Screen.TwipsPerPixelX * 9
        pCalendarLeft = Tree.Left
        
        If (pCalendarWidth / pCalendarHeight > 1.4) Then
            PVCalendar1.Width = pCalendarHeight * 1.4
            PVCalendar1.Height = pCalendarHeight
            PVCalendar1.Left = pCalendarLeft + (pCalendarWidth - PVCalendar1.Width) / 2
            PVCalendar1.Top = pCalendarTop
        Else
            PVCalendar1.Height = pCalendarWidth / 1.4
            PVCalendar1.Width = pCalendarWidth
            PVCalendar1.Top = pCalendarTop + (pCalendarHeight - PVCalendar1.Height) / 2
            PVCalendar1.Left = pCalendarLeft
        End If
        
        closeworkspace.Left = TabStrip1.Left + TabStrip1.Width - 350
    End If
    

    'set oos objects if necessary
    If PVCalendar1.Visible = False Then
        Tree.Visible = True
        GanttChart.Visible = True
        'GanttChart1.Visible = True
        'OOSTree.Visible = True
        
        oos_Click
    End If
    
    'make sure top line of tree and ganttchart are correct after resize
    If GanttChart.VScrollVisible Then
        Dim tempInt As Integer
        Dim i As Integer
        For i = Tree.TopIndex + 2 To Tree.listCount - 1
            If Tree.ItemShown(i) Then
                tempInt = i
                Exit For
            End If
        Next i
        
        tempInt = GanttChart.GetRowFromRowID(tempInt)
        If tempInt > 0 Then
            GanttChart.SetVerticalScrollBar (tempInt)
        End If
    Else
        If Tree.listCount > 0 Then Tree.TopIndex = 1
    End If
    
    'make sure top line of oostree and ganttchart1 are correct after resize
    If GanttChart1.VScrollVisible Then
        For i = OOSTree.TopIndex + 2 To OOSTree.listCount - 1
            If OOSTree.ItemShown(i) Then
                tempInt = i
                Exit For
            End If
        Next i
        
        tempInt = GanttChart1.GetRowFromRowID(tempInt)
        If tempInt > 0 Then
            GanttChart1.SetVerticalScrollBar (tempInt)
        End If
    Else
        If OOSTree.listCount > 0 Then OOSTree.TopIndex = 1
    End If
    
    
    
End Sub

'Function/Subroutine:MDIForm_Initialize
'Purpose: initalizes variables used by all frmMain Windows.
Private Sub MDIForm_Initialize()
    Set workspaces = New Collection
      
    'get user prefrences from database
    LoadColorSchemes
    
    'Initialize flags
    InTaskMgmtView = True
    NeedUpdateRiskValues = True
    
    'Initialize pictures for tree nodes.
    Set nodePict1 = LoadPicture(workingDirectory & "icons\op.bmp")
    Set nodePict2 = LoadPicture(workingDirectory & "icons\task.bmp")
    Set nodePict3 = LoadPicture(workingDirectory & "icons\proc.bmp")
    Set nodePict4 = LoadPicture(workingDirectory & "icons\mode.bmp")
    Set nodePict5 = LoadPicture(workingDirectory & "icons\workspace.bmp")
    Set nodePict6 = LoadPicture(workingDirectory & "icons\cogs.bmp")
    Set nodePict7 = LoadPicture(workingDirectory & "icons\risk.bmp")
      
    'DLL Thread Information
    DLLActive = False
    If DLLActive Then
        Dim odbcName As String
        Dim IsAccessDB As Long
        If IsAccessDatabase Then IsAccessDB = 1 Else IsAccessDB = 0
        
        odbcName = "riskMon"
        
        threadActive = 1
        dataBaseChangesMade = 0
        
        If (StartWorkerThread(threadActive, dataBaseChangesMade, odbcName, workingDirectory, IsAccessDB) = 0) Then
            MsgBox "Failed to initialize risk update DLL", vbInformation
        End If
        
    End If

    Set compHierarchy = New ComponentHierarchyClass
    
End Sub



'Function: MDIForm_terminate
' Purpose: Checks to make sure the DLL thread was closed.
Private Sub MDIForm_Terminate()
    If DLLActive Then
        If (CloseWorkerThread = 0) Then
            MsgBox "Close worker thread failed"
        End If
    End If
'MsgBox "function is getting called"
End Sub

'Function/Subroutine:MDIForm_Load
'Purpose: Initialise frmMain when instance occures.
Private Sub MDIForm_Load()
    'initialize sub forms.
    Set compMap = New ComponentMap
    Set VScreen = New VScreen
    Set hForm = New hierarchyIconsForm
    Set VScreen.cForm = compMap
    'initialize component hierarchy object
    compHierarchy.ConstructObject
    'initialize mode object
    Set ModeList = New Collection
    Dim mySQLstatement As String
    Dim resultSet As rdoResultset
    Dim rarray As Variant
    Dim Mode As ModeClass
    Dim upperModeID As Integer, modeID As Integer
    
    mnuNewUser.Enabled = (UserType = Administrator)
    
    ModeCount = 0
    mySQLstatement = "SELECT ModeID FROM Mode ORDER BY ModeID DESC"
    Set resultSet = dbConnection.OpenResultset(mySQLstatement)
    
    If Not resultSet.EOF Then
        rarray = resultSet.GetRows(1)
        upperModeID = rarray(0, 0)
        Dim i As Integer
        For i = 1 To upperModeID
            Set Mode = New ModeClass
            Mode.CreateNewMode
            ModeList.Add Mode
        Next i
        mySQLstatement = "SELECT ModeID, ModeName, ModeDesc, SaphireProjPath, BaselineRisk, MediumRisk, HighRisk, ModeColor FROM Mode"

        Set resultSet = dbConnection.OpenResultset(mySQLstatement)
        While Not resultSet.EOF
            rarray = resultSet.GetRows(1)
            modeID = rarray(0, 0)
            ModeList.Item(modeID).SetMode rarray(1, 0), rarray(2, 0), rarray(3, 0), rarray(4, 0), rarray(5, 0), rarray(6, 0), rarray(7, 0)
            ModeList.Item(modeID).ObjectInUse = True
            ModeCount = ModeCount + 1
        Wend
    Else
        ' have the user try and create at least one mode now if none exist
        Set Mode = New ModeClass
        Mode.CreateNewMode
        If MsgBox("No modes or associated SAPHIRE projects have been found.  At least one mode must be created before the Risk Monitor can be used.  Would you like to create a mode now?", vbYesNo) = vbYes Then
            If Not Mode.addmode(modeID) Then
                MsgBox "Risk Monitor could not load because no modes or associated SAPHIRE projects were found.", vbExclamation
                Unload Me
            End If
            Do While MsgBox("Would you like to add another mode now?", vbYesNo) = vbYes
                Mode.addmode modeID
            Loop
        Else
            MsgBox "Risk Monitor could not load because no modes or associated SAPHIRE projects were found.", vbExclamation
            Unload Me
        End If
    End If
    
    ' let's find this user's favorite color preferences...
    mySQLstatement = "SELECT ColorScheme, DangerColor, CautionColor, OKColor, TaskColor, ProcColor, CompColor FROM UserPreferences WHERE UserID = " & userID
    Set resultSet = dbConnection.OpenResultset(mySQLstatement)
    rarray = resultSet.GetRows(1)
    curColorScheme = rarray(0, 0)
    
    'set users risk colors
    DangerColor = rarray(1, 0)
    CautionColor = rarray(2, 0)
    OKColor = rarray(3, 0)
    TaskColor = rarray(4, 0)
    ProcColor = rarray(5, 0)
    CompColor = rarray(6, 0)

    SetColorScheme
    
    'set window flags
    active = True
    popupmenuopen = False
    
    'turn off out of service (OOS) items which are not shown at startup
    optskmgmt.Value = 1
    oos.Value = 0
    OOSTree.Visible = False
    GanttChart1.Visible = False
 
    'Set toolbar to start values and set inital size of objects
    Toolbar1.Buttons(17).Image = GanttChart.TimeResolution + 13
    Toolbar1.Buttons(17).ButtonMenus(GanttChart.TimeResolution).text = "» " & Mid(Toolbar1.Buttons(17).ButtonMenus(GanttChart.TimeResolution).text, 3)

    LeftPane_Resize
    
    sbStatusBar.Panels(1).text = "Loading..."
 
    'Determine if user has open workspaces... if so load them up
    OpenWorkspaces.Get_Open_Workspaces
 
    'If user has no open workspaces then...
    If MDIMain.active = False Then
        'Create new or open existing?
        FirstLogin.Show vbModal
        If FirstLogin.Result = False Then
            Unload Me
            Exit Sub
        End If
    Else
        'otehrwise set ooslist objects
        OpenWorkspaces.ooslistControl activeWorkspace
    End If
    
    'Set DLL thread variables
    If DLLActive Then SetWorkspace activeWorkspace.workspaceId
    mnuViewSaphireStats.Enabled = DLLActive
    
    sbStatusBar.Panels(1).text = "Running"
    WorkspacesLoaded = True
    
    'Load initial Items into tree (Initializes image size)
    Tree.ItemPictureExpandable = nodePict1
    Tree.ItemPictureExpanded = nodePict2
    Tree.ItemPictureLeaf = nodePict3
    OOSTree.ItemPictureExpandable = nodePict1
    OOSTree.ItemPictureExpanded = nodePict2
    OOSTree.ItemPictureLeaf = nodePict3

End Sub
'Function/Subroutine:LoadNewWorkspace
'Purpose: for creating a new workspace
Public Function LoadNewWorkspace() As Boolean
'
    Dim RowReturn, i As Integer
    Dim rarray As Variant
    Dim lrArray As Variant
    Dim mySQLstatement As String
    Dim resultSet As rdoResultset
    Dim Time As String
    Dim TimeStart As String
    Dim TimeEnd As String
    Dim WSName As String, WSDescription As String
    Dim CreateDate As String
    Dim Index As Long
    Dim WorkspaceType, InitialMode As Integer
    
    'Set initial time values - can be changed later by user
    Time = DatePart("yyyy", Now)
    WorkspaceProperties.StartDate = "1/1/" & Time
    WorkspaceProperties.EndDate = "12/31/" & Time

    'Query user for new workspace name
    WorkspaceProperties.Show 1
    If WorkspaceProperties.Result = False Then
        LoadNewWorkspace = False
        Exit Function
    End If
    
    WSName = WorkspaceProperties.Text1
    WSDescription = WorkspaceProperties.Text2
    WorkspaceType = WorkspaceProperties.WorkspaceType
    TimeStart = WorkspaceProperties.StartDate
    TimeEnd = WorkspaceProperties.EndDate
    InitialMode = WorkspaceProperties.InitialMode
    Unload WorkspaceProperties

    'Create new workspace in database
    mySQLstatement = "INSERT INTO [Workspace] (WorkspaceName, WorkspaceDesc, UserID, AccessType, StartTime, EndTime, CreateDate, InitialModeID) VALUES ( '" & WSName & "','" & WSDescription & "'," & userID & ", " & WorkspaceType & ", " & SQLDate(TimeStart) & ", " & SQLDate(TimeEnd) & ", " & SQLDate(Now) & "," & InitialMode & ")"
    Set resultSet = dbConnection.OpenResultset(mySQLstatement)

    'Get the worspace Id from the newly created record
    mySQLstatement = "SELECT Workspace.WorkspaceID FROM [Workspace] WHERE WorkspaceName = '" & WSName & "'"
    Set resultSet = dbConnection.OpenResultset(mySQLstatement)
    lrArray = resultSet.GetRows(1)

    'Put workspace in openWorkspaces list
    mySQLstatement = "INSERT INTO [OpenWorkspaces] (WorkspaceID, UserID) VALUES ( " & lrArray(0, 0) & ", " & userID & ")"
    dbConnection.Execute (mySQLstatement)
    ' Add initial mode to workspace mode table
    mySQLstatement = "INSERT INTO [WorkspaceMode] (WorkspaceID, ModeID, StartTime, ModeName) VALUES (" & lrArray(0, 0) & "," & InitialMode & "," & SQLDate(TimeStart) & ",'" & ModeList.Item(InitialMode).ModeName & "')"
    dbConnection.Execute (mySQLstatement)
    'Increment collection variable for maintnence purposes
    activeWorkspaceIndex = workspaces.Count + 1

    'create new collection member
    Set activeWorkspace = New Workspace

    'Clear the tree so new data can be entered
    Tree.Clear

    'Set Workspace variables
    With activeWorkspace
        .workspaceId = lrArray(0, 0)
        '.modifyAccess = True
        .creatorId = userID
        .StartTime = TimeStart
        .EndTime = TimeEnd
        .dateLastModified = Now
        .dateCreated = Now
        .WorkspaceName = WSName
        .WorkspaceDescription = WSDescription
        .InitialModeID = InitialMode
    End With
    
    'Add Item to tree view
    Index = Tree.AddItem(WSName)

    'Add item to collection
    workspaces.Add activeWorkspace

    'Create new tabstrip to represent workspace
    If (workspaces.Count = 1) Then
        Set activeWorkspace.tabCtrl = TabStrip1.Tabs(1)
    Else
        Set activeWorkspace.tabCtrl = TabStrip1.Tabs.Add()
    End If

    activeWorkspace.tabCtrl.Caption = WSName
    activeWorkspace.tabCtrl.Selected = True

    ''Add mode node
    Dim tempNode As node_object
    Set tempNode = New node_object

    tempNode.StartTime = activeWorkspace.StartTime
    tempNode.nodeName = "MODE"
    tempNode.nodetype = 3
    tempNode.NodeState = 0
    tempNode.EndTime = activeWorkspace.EndTime
    tempNode.TaskAutoID = 0
    tempNode.GroupAutoID = 0
    activeWorkspace.ChildNodes.Add tempNode

    Index = Tree.AddItem("MODE")
    Set Tree.ItemPicture(Index) = nodePict4
    Tree.ItemLevel(Index) = 1

    'Display new workspace on screen, set appropriate flags so
    'updates will begin on the new workspace
    OpenWorkspaces.LoadData activeWorkspace
    NeedUpdateRiskValues = True
    If DLLActive Then SetWorkspace activeWorkspace.workspaceId
    ShowWorkspaceView
    OpenWorkspaces.ooslistControl activeWorkspace
    LoadNewWorkspace = True
End Function
'Function:MDIForm_Unload
'Purpose: handles the event when the control box x is clicked.
Private Sub MDIForm_Unload(Cancel As Integer)
    If DLLActive Then
        If (CloseWorkerThread() = 0) Then
            MsgBox "Close worker thread failed"
        End If
    End If
    End
End Sub

Private Sub mnuBarColor_Click()
    BarColor.Show 1
End Sub

Private Sub mnuBasicEventMap_Click()
    Dim cForm As New BaseComponentMap
    'cForm.ShowNumberAssociatedBasicEvents = True
    cForm.FormMode = MapBasicEvents
    If DLLActive Then SuspendUpdates
    cForm.Show 1
    If DLLActive Then ResumeUpdates
End Sub

Private Sub mnuComponentMap_Click()
    compMap.FormMode = Edit
    compMap.CompDiagram.ShowToolboxOnRightClick = True
    compMap.Show 0
End Sub
'Function:mnuClose_Click
'Purpose:Close an open workspace
Private Sub mnuClose_Click()
    OpenWorkspaces.close_workspace activeWorkspace
End Sub

Private Sub mnuModeColor_Click()
    ModeColor.Show 1
End Sub

'Function:mnuNew_Click
'Purpose: Create a new workspace
Private Sub mnuNew_Click()
'
     LoadNewWorkspace
End Sub

'Function:mnuOpen_Click
'Purpose:Open an existing workspace
Private Sub mnuOpen_Click()
    
    WorkspaceList.CantSelectIfOpen = True
    WorkspaceList.Load PublicOrCreatedByUser
    
    If WorkspaceList.WorkspaceCount > 0 Then
        WorkspaceList.Show vbModal
        If WorkspaceList.Result = True Then
            OpenWorkspaces.open_workspace WorkspaceList.WSID
        End If
    Else
        MsgBox "No workspaces exist or you do not have rights to open any existing workspaces.", vbInformation
        Exit Sub
    End If
    Unload WorkspaceList
    
End Sub

Private Sub mnuRiskColor_Click()
    RiskColor.Show 1
End Sub

Public Sub mnuViewRiskMeter_Click()
    If DLLActive Then SuspendUpdates
    VScreen.Show 1, Me
    If DLLActive Then ResumeUpdates
End Sub

'Function: oos_Click
'Purpose: show or hide the out of serviece list depending on if the
'option is checked or not.
Private Sub oos_Click()

    Tree.Height = TabStrip1.Height - Tree.Top - Screen.TwipsPerPixelY * 2
    GanttChart.Height = Tree.Height - Screen.TwipsPerPixelY * 2
        
    'If checkbox is selected
    If oos.Value = 1 Then
        GanttChart1.Visible = True
        OOSTree.Visible = True
        
        OOSTree.Height = TabStrip1.Height - Tree.Top - Screen.TwipsPerPixelY * 2
        GanttChart1.Height = OOSTree.Height - Screen.TwipsPerPixelY * 2
        
      
        'if both operational task management and oos list are visible
        If optskmgmt.Value = 1 Then
            GanttChart.Height = GanttChart.Height / 2
            Tree.Height = Tree.Height / 2
            
            GanttChart1.Visible = True
            OOSTree.Visible = True
            
            GanttChart1.Height = GanttChart.Height
            OOSTree.Height = Tree.Height
            
            GanttChart1.Top = GanttChart.Top + GanttChart.Height + 20 '10
            OOSTree.Top = Tree.Top + Tree.Height + 10
            
            GanttChart1.Left = GanttChart.Left
            OOSTree.Left = Tree.Left
            
            GanttChart1.Width = GanttChart.Width
            OOSTree.Width = Tree.Width
        'otherwise make sure the oos list is 'on'
        Else
            GanttChart.Visible = False
            Tree.Visible = False
            Text2.Visible = False
            Text3.Visible = False
            Text4.Visible = False
        
            GanttChart1.Visible = True
            OOSTree.Visible = True
            oos.Value = 1
        
            GanttChart1.Left = GanttChart.Left
            OOSTree.Left = Tree.Left
        
            GanttChart1.Width = GanttChart.Width
            OOSTree.Width = Tree.Width
        
            GanttChart1.Top = GanttChart.Top
            OOSTree.Top = Tree.Top
            End If
        
    'If it is not selected
    Else
        'Show only operational task management stuff
        GanttChart.Visible = True
        Tree.Visible = True
        Text2.Visible = True
        Text3.Visible = True
        Text4.Visible = True
        
        GanttChart1.Visible = False
        OOSTree.Visible = False
        optskmgmt.Value = 1
        

    End If
End Sub
'Function:OOSTree_ItemClick
'Purpose: When an item in the OOS gantt chart is clicked determine if
'the click was with the right mouse button and if so pop up the
'correct menu
Private Sub OOSTree_ItemClick(ByVal Index As Long, ByVal ColNum As Integer, ByVal AreaType As Integer, ByVal Button As Integer, ByVal Shift As Integer)
    Dim tempInt As Integer
    
    Dim temp As SelectionType
    tempInt = Index
    temp.row = GanttChart1.GetRowFromRowID(tempInt)
    temp.sType = HasFocus
    GanttChart1.Selection = temp
    
    'if button was right
    If Button = 2 Then
        rComponent = True
        SETime = True
        
        If popupmenuopen = False Then
            If Index > 1 Then 'dont select first two nodes
                popupmenuopen = True
                PopupMenu OOSTreeMenu
            Else
                popupmenuopen = True
                rComponent = False
                SETime = False
                PopupMenu OOSTreeMenu
            End If
        Else
            popupmenuopen = False
        End If
    End If
End Sub
'Function:OOSTree_ItemDblClick
'Purpose' handles the double click event from the out of service tree
Private Sub OOSTree_ItemDblClick(ByVal Index As Long, ByVal ColNum As Integer, ByVal AreaType As Integer, ByVal Button As Integer, ByVal Shift As Integer)
    'If statement is for case when column in table is clicked
    '(rather than tree view)
    If AreaType = 9 And ColNum <> 0 Then
        'for uneditable type
        If OOSTree.ItemPicture(Index) = nodePict5 Or OOSTree.ItemPicture(Index) = nodePict4 Then
            Exit Sub
        'for procedure
        ElseIf OOSTree.ItemPicture(Index) = nodePict6 Then
            ButtonFunctions.ChangeOOSComponents activeWorkspace
        End If
    ElseIf AreaType = 9 And ColNum = 0 Then
        'popup component diagram if tree view was clicked
        ComponentDiagram.Show 1
    End If
End Sub
'Function:aComponent_Click
'Purpose: adds a component to the out of service menu when selection
'is made from the tree's popupmenu
Private Sub aComponent_Click()
    ButtonFunctions.AddOOSComponents activeWorkspace
End Sub

Private Sub OOSTree_TopChange(ByVal Index As Long)
    OOSTree.Selected(Index) = True
    If (OOSTree.ItemShown(Index + 1)) Then
        GanttChart1.SetVerticalScrollBar (Index + 1)
    Else
        Dim i As Integer
        For i = 2 To OOSTree.listCount - Index
            If (OOSTree.ItemShown(Index + 1)) Then
                GanttChart1.SetVerticalScrollBar (Index + i)
                Exit For
            End If
        Next i
    End If
    
    Dim tempInt As Integer
    Dim temp As SelectionType
    tempInt = Index
    temp.row = GanttChart.GetRowFromRowID(tempInt)
    temp.sType = HasFocus
    GanttChart1.Selection = temp
End Sub

'Function:optskmgmt_Click
'Purpose: Handles the click from the operational task management
'check box.
Private Sub optskmgmt_Click()
    'If Box is selected
    If optskmgmt.Value = 1 Then
        GanttChart.Visible = True
        Tree.Visible = True
        Text2.Visible = True
        Text3.Visible = True
        Text4.Visible = True
        Tree.Height = TabStrip1.Height - Tree.Top - Screen.TwipsPerPixelY * 2
        GanttChart.Height = Tree.Height - Screen.TwipsPerPixelY * 2
        
        'if both operational task management and oos list are visible
        If oos.Value = 1 Then
            GanttChart.Height = GanttChart.Height / 2
            Tree.Height = Tree.Height / 2
            
            GanttChart1.Visible = True
            OOSTree.Visible = True
            
            GanttChart1.Height = GanttChart.Height
            OOSTree.Height = Tree.Height
            
            GanttChart1.Top = GanttChart.Top + GanttChart.Height + 10
            OOSTree.Top = Tree.Top + Tree.Height + 10
            
            GanttChart1.Left = GanttChart.Left
            OOSTree.Left = Tree.Left
            
            GanttChart1.Width = GanttChart.Width
            OOSTree.Width = Tree.Width
        'otherwise make sure the oos list is 'off'
        Else
            GanttChart1.Visible = False
            OOSTree.Visible = False
        End If
        
    'If Box is not selected
    Else
        'make sure only oos objects are visible - correct height ratio
        GanttChart.Visible = False
        Tree.Visible = False
        Text2.Visible = False
        Text3.Visible = False
        Text4.Visible = False
        
        GanttChart1.Visible = True
        OOSTree.Visible = True
        oos.Value = 1
        
        OOSTree.Height = TabStrip1.Height - Tree.Top - Screen.TwipsPerPixelY * 2
        GanttChart1.Height = OOSTree.Height - Screen.TwipsPerPixelY * 2
        
        GanttChart1.Left = GanttChart.Left
        OOSTree.Left = Tree.Left
        
        GanttChart1.Width = GanttChart.Width
        OOSTree.Width = Tree.Width
        
        GanttChart1.Top = GanttChart.Top
        OOSTree.Top = Tree.Top

    End If
End Sub

'Function:rComponent_Click
'Purpose: removes a component from the out of service menu when
'selection is made from the tree's popupmenu
Private Sub rComponent_Click()
    ButtonFunctions.RemoveOOSComponents activeWorkspace
End Sub
'Function:RemoveComponent_Click
'Purpose: removes a component from the out of service menu when
'selection is made from the tree's menu
Private Sub RemoveComponent_Click()
    ButtonFunctions.RemoveOOSComponents activeWorkspace
End Sub
'function: removei_click
'Handles the click of remove from the task menu
Private Sub removei_Click()
    ButtonFunctions.Remove activeWorkspace
End Sub

'Function:Ritem_Click
'Purpose: removes a component from the out of service menu when
'selection is made from the tree's popupmenu
Private Sub Ritem_Click()
'
    ButtonFunctions.Remove activeWorkspace
End Sub

'Function: SETime_Click
'Purpose: Change the time of a scheduled oos component when option is
'selected from popupmenu
Private Sub SETime_Click()
    ButtonFunctions.ChangeOOSComponents activeWorkspace
End Sub
'Function: SetValues_Click
'Purpose: Allow the user to change the cut off values for high, medium and
'low risk
Private Sub SetValues_Click()
    '
        RiskValues.Show 1
End Sub

'Function: StartEnd_Click
'Purpose: Change the time of a scheduled procedure or task when
'option is selected from toolbar
Private Sub StartEnd_Click()

    Dim Index As Long
    Index = Tree.ListSelection
    
    sbStatusBar.Panels(1).text = "Updating Data..."
    If Tree.ItemPicture(Index) = nodePict3 Then 'procedure node
            Dim StartDate As Date
            Dim EndDate As Date
            Dim OldEnd As Date
            Dim OldStart As Date
            Dim i As Integer
            Dim WSID As Integer
            Dim itemID As Integer
            Dim taskref As Integer
            Dim group As Integer
            Dim mySQL As String
            
            'Popup window to allow user to select new date and time
            TimeEdit.LabelText = Tree.CellText(Index, 0)
            TimeEdit.StartDate = Tree.CellText(Index, 1)
            TimeEdit.EndDate = Tree.CellText(Index, 2)
            TimeEdit.Show 1
            StartDate = TimeEdit.StartDate
            EndDate = TimeEdit.EndDate
            
            'if the user canceled the operation exit function
            If TimeEdit.CancelClick = True Then
                Unload TimeEdit
                Exit Sub
            End If
            
            Unload TimeEdit
            
            'Change node in collection
                For i = 1 To activeWorkspace.ChildNodes.Count
                    If activeWorkspace.ChildNodes.Item(i).DataRow = Index Then
                        OldStart = activeWorkspace.ChildNodes.Item(i).StartTime
                        OldEnd = activeWorkspace.ChildNodes.Item(i).EndTime

                        Exit For
                    End If
                Next i
                
                WSID = activeWorkspace.workspaceId
                itemID = activeWorkspace.ChildNodes.Item(i).Identification
                taskref = activeWorkspace.ChildNodes.Item(i).TaskAutoID
                group = activeWorkspace.ChildNodes.Item(i).GroupAutoID
            
            'change item in database table
            
            If pManager.ChangeProcedureTime(WSID, itemID, taskref, OldStart, OldEnd, StartDate, EndDate) = False Then
                MsgBox "Can't Change Procedure Time due to Mode Conflict", vbInformation
            Else
                activeWorkspace.ChildNodes.Item(i).StartTime = StartDate
                activeWorkspace.ChildNodes.Item(i).EndTime = EndDate
            End If
            
            OpenWorkspaces.LoadData activeWorkspace
        
        ElseIf Tree.ItemPicture(Index) = nodePict2 Then 'task node
            
            'let user select new data
            TimeEdit.LabelText = Tree.CellText(Index, 0)
            TimeEdit.StartDate = Tree.CellText(Index, 1)
            TimeEdit.EndDate = Tree.CellText(Index, 2)
            TimeEdit.Show 1
            StartDate = TimeEdit.StartDate
            EndDate = TimeEdit.EndDate
            
            'if the user cancled the action stop the function
            If TimeEdit.CancelClick = True Then
                Unload TimeEdit
                Exit Sub
            End If
            Unload TimeEdit
            
            'Change node in collection
            For i = 1 To activeWorkspace.ChildNodes.Count
                If activeWorkspace.ChildNodes.Item(i).DataRow = Index Then
                    activeWorkspace.ChildNodes.Item(i).StartTime = StartDate
                    activeWorkspace.ChildNodes.Item(i).EndTime = EndDate
                    Exit For
                End If
            Next i
            
            WSID = activeWorkspace.workspaceId
            itemID = activeWorkspace.ChildNodes.Item(i).Identification
            taskref = activeWorkspace.ChildNodes.Item(i).TaskAutoID
            group = activeWorkspace.ChildNodes.Item(i).GroupAutoID
            
            'change item in table
            mySQL = "UPDATE WorkspaceTaskSchedule SET StartTime = " _
                & SQLDate(StartDate) & ", EndTime = " & SQLDate(EndDate) & _
                " WHERE WorkspaceID = " & WSID & " AND TaskId = " _
                & itemID & " AND AutoReference = " & taskref
                
            dbConnection.Execute (mySQL)
            
            'Load changed data into objects.
            OpenWorkspaces.LoadData activeWorkspace
            
        ElseIf Tree.ItemPicture(Index) = nodePict4 Then 'mode node
            Dim RowReturn As Integer
            Dim resultSet As rdoResultset
            Dim rarray As Variant
            
            RowReturn = 0
            'get list of workspace modes
            mySQL = "SELECT ModeID, StartTime, ModeName FROM [WorkspaceMode] WHERE WorkspaceID = " & MDIMain.returnID & " ORDER BY StartTime"
            Set resultSet = dbConnection.OpenResultset(mySQL, rdOpenKeyset)
            
            'If there are no modes
            If resultSet.EOF Then
                MsgBox "No Modes Running", vbInformation
                Exit Sub
            'Otherwise add them to the list
            Else
                While Not resultSet.EOF
                resultSet.MoveNext
                RowReturn = RowReturn + 1
                Wend
                resultSet.MoveFirst
                rarray = resultSet.GetRows(RowReturn)
            End If
        
            'move items to editMode form
            EditModeTime.rarray = rarray
            EditModeTime.RowReturn = RowReturn
            Set EditModeTime.aWorkspace = activeWorkspace
            'Implement edit mode form
            EditModeTime.Show 1
            Unload EditModeTime
        End If
        sbStatusBar.Panels(1).text = "Running"
End Sub


'Function/Subroutine:TabStrip1_Click
'Purpose: Handles the event when a tabstrip is clicked - changes the
'active workspace to the workspace associated with the clicked tab.
Private Sub TabStrip1_Click()
   Dim tabIndex As Integer
   
   sbStatusBar.Panels(1).text = "Loading Workspace..."
    tabIndex = TabStrip1.SelectedItem.Index
    
    progress.ProgressBar1.Value = 0
    progress.Show
    progress.Refresh
    
    If (tabIndex <> activeWorkspaceIndex) Then
        activeWorkspaceIndex = tabIndex
        Set activeWorkspace = workspaces.Item(activeWorkspaceIndex)
        NeedUpdateRiskValues = True
    End If
    progress.ProgressBar1.Value = 10
    'Load data for the workspace that has just been made active.
    OpenWorkspaces.LoadData activeWorkspace
    OpenWorkspaces.ooslistControl activeWorkspace
    If DLLActive Then SetWorkspace activeWorkspace.workspaceId

    progress.ProgressBar1.Value = 90
    'make sure the correct view is being displayed.
    ShowWorkspaceView
    
    sbStatusBar.Panels(1).text = "Running"
    
    PVCalendar1.GetYearRange DatePart("yyyy", activeWorkspace.StartTime), DatePart("yyyy", activeWorkspace.EndTime)
    
    progress.ProgressBar1.Value = 100
    Unload progress
    
    
End Sub
'Function/Subroutine:ShowWorkspaceView
'Purpose:Display the correct view (operational task management or
'review and oversight) depending on how the flags have been set.
Private Sub ShowWorkspaceView()

    sbStatusBar.Panels(1).text = "Loading View..."
    
    'Set visible property for all objects on tabstrip
    Text2.Visible = InTaskMgmtView
    Text3.Visible = InTaskMgmtView
    Text4.Visible = InTaskMgmtView
    GanttChart.Visible = InTaskMgmtView
    Tree.Visible = InTaskMgmtView
    OOSTree.Visible = InTaskMgmtView
    GanttChart1.Visible = InTaskMgmtView
    oos.Visible = InTaskMgmtView
    optskmgmt.Visible = InTaskMgmtView
    ImageSplitter.Visible = InTaskMgmtView
    PVCalendar1.Visible = Not InTaskMgmtView
    
    'If task management view check to see if oos list if visible
    If (InTaskMgmtView = True) Then
        oos_Click
    End If
    
    
    'do updates if review and oversight view is visible
    If (InTaskMgmtView = False) Then
        
        sbStatusBar.Panels(1).text = "Updating Risk Calculations..."
        
        If DLLActive Then
            Dim percentComplete As Long
            DoAllUpdates percentComplete
            Dim pDlg As ProgressDialog
            Dim progressNeeded As Boolean
            progressNeeded = False
            If (percentComplete < 100) Then
                Set pDlg = New ProgressDialog
                progressNeeded = True
                pDlg.SetCompletion percentComplete
                pDlg.Show 0
            End If
            Do While (percentComplete < 100)
                ' update progress bar
                ContinueAllUpdates percentComplete
                pDlg.SetCompletion percentComplete
                If (pDlg.CancelPressed) Then
                    Exit Do
                End If
            Loop
            If (progressNeeded) Then Unload pDlg
        End If
        
        Dim curDate As Date
        curDate = Now
        PVCalendar1.SetYearRange year(curDate), year(curDate) + 10, year(curDate)
        DisplayRiskValues Now, 1
    End If
    
    sbStatusBar.Panels(1).text = "Running"

                        
End Sub

Private Sub Task_Click()
    If Tree.ListSelection < 1 Then
        removei = False
        CSETime = False
    Else
        removei = True
        CSETime = True
    End If
        
End Sub

'Function/Subroutine:Toolbar1_ButtonClick
'Purpose:Determine which toolbar button was clicked and call
'corresponding function
Private Sub Toolbar1_ButtonClick(ByVal Button As MSComctlLib.Button)

    'On Error Resume Next
    Select Case Button.Key
        Case "New"
            LoadNewWorkspace
        Case "Open"
            mnuOpen_Click
        Case "Save"
            'MsgBox "Method not yet implemented"
            'mnuFileSave_Click
            ButtonFunctions.Copy_Workspace activeWorkspace
        Case "Print"
            'MsgBox "Method not yet implemented"
            'mnuFilePrint_Click
            Tree.Selected(3) = Not Tree.Selected(3)
        Case "Review and Oversight"
            mnuViewRevOvst_Click
        Case "Scheduler"
            mnuViewTskMgmt_Click
        Case "Risk Meter"
            mnuViewRiskMeter_Click
        Case "AddGroup"
            ButtonFunctions.AddGroup activeWorkspace
        Case "AddTask"
            ButtonFunctions.AddTask activeWorkspace
        Case "EditProc"
            frmSelectProc.Show vbModal, Me
            Unload frmSelectProc
        Case "AddMode"
            ButtonFunctions.addmode activeWorkspace
        Case "Remove"
            ButtonFunctions.Remove activeWorkspace
        Case "Time Scale"
            ButtonFunctions.StartEnd activeWorkspace
        
    End Select
   
End Sub
'Function/Subroutine:Toolbar1_ButtonMenuClick
'Purpose:Get the value from the toolbar button menu that was clicked
'and set the time resolution accordingly.
Private Sub Toolbar1_ButtonMenuClick(ByVal ButtonMenu As MSComctlLib.ButtonMenu)
    Dim i As Integer
    Select Case ButtonMenu.Parent.Key
    Case "Time Scale"
        For i = 1 To 7
           If i = ButtonMenu.Index Then
               Toolbar1.Buttons(17).ButtonMenus(i).text = "» " & Mid(Toolbar1.Buttons(17).ButtonMenus(i).text, 3)
           Else
               Toolbar1.Buttons(17).ButtonMenus(i).text = "  " & Mid(Toolbar1.Buttons(17).ButtonMenus(i).text, 3)
           End If
        Next i
        
        Toolbar1.Buttons(17).Image = ButtonMenu.Index + 13
        GanttChart.TimeResolution = ButtonMenu.Index
        GanttChart1.TimeResolution = ButtonMenu.Index
    Case "AddGroup"
        If ButtonMenu.Index = 1 Then
            frmSelectTaskGroup.Show vbModal, Me
            Unload frmSelectTaskGroup
        Else ' = 2
            frmNewGroup.Show vbModal, Me
            If frmNewGroup.Result = True Then
                EditTaskGroup.TaskGroupName = frmNewGroup.TaskGroupName
                EditTaskGroup.Show vbModal, Me
                Unload EditTaskGroup
            End If
            Unload frmNewGroup
        End If
    Case "AddTask"
        If ButtonMenu.Index = 1 Then
            frmSelectTask.Show vbModal, Me
            Unload frmSelectTask
        Else ' = 2
            frmNewTask.Show vbModal, Me
            If frmNewTask.Result = True Then
                EditTask.TaskName = frmNewTask.TaskName
                EditTask.Show vbModal, Me
                Unload EditTask
            End If
            Unload frmNewTask
        End If
    Case "EditProc"
        frmNewProc.Show vbModal, Me
        If frmNewProc.Result = True Then
            EditProc.ProcedureName = frmNewProc.ProcedureName
            EditProc.Show vbModal, Me
            Unload EditProc
        End If
        Unload EditProc
    Case "AddMode"
        MsgBox "Not implemented yet."
    End Select
    'Toolbar1.Buttons(17).ButtonMenus.Item (ButtonMenu.Index).
    
End Sub
'Function/Subroutine:SetColorScheme
'Purpose:Sets the colorscheme from the users preferences
Private Sub SetColorScheme()
    Me.BackColor = colors(16, curColorScheme)
    
    SetCalendarColorScheme
    'WorkspaceTree.BackColor = colors(4, curColorScheme)
End Sub
'Function/Subroutine:mnuViewRvwOvst_Click
'Purpose: Sets the flags so that the review and oversite window will
'be shown and then calls the show function
Private Sub mnuViewRevOvst_Click()
    If (InTaskMgmtView = True) Then
        InTaskMgmtView = False
        ShowWorkspaceView
    End If
End Sub
'Function/Subroutine:mnuViewTskMgmt_Click
'Purpose:Sets the flags so that the operational task management view
'will be shown and then calls the show function.
Private Sub mnuViewTskMgmt_Click()
    If (InTaskMgmtView = False) Then
        InTaskMgmtView = True
        ShowWorkspaceView
    End If
End Sub
'Function:mnuViewSaphireStats_Click
'Purpose: Displays statistics about how long saphire (Through the DLL)
'Is taking to calculate risk.
Private Sub mnuViewSaphireStats_Click()
    If (DLLActive) Then
        Dim sStats As SaphireStats
        Set sStats = New SaphireStats
        Dim TotalUpdates As Long
        sStats.AverageTime.text = GetAverageUpdateSpeed(TotalUpdates)
        sStats.TotalUpdates.text = TotalUpdates
        sStats.Show 1
    End If
End Sub


'Function/Subroutine:GetColor
'Purpose: Gets color according to user preferences.
Public Function GetColor(Index As Integer, scheme As Integer) As Long
    GetColor = colors(Index, scheme)
End Function

'Function/Subroutine:Tree_ItemClick
'Purpose:Capturs a single item click in the tree. expands or colappses
'a node if parent node and mouse click was left or displays popupmenu
'if click was right.
Private Sub Tree_ItemClick(ByVal Index As Long, ByVal ColNum As Integer, ByVal AreaType As Integer, ByVal Button As Integer, ByVal Shift As Integer)
    Dim i As Integer
    Dim tempInt As Integer
    
    'MsgBox AreaType
        
    'if right click...
    If Button = 2 Then
        Ritem = True
        StartEnd = True
        If popupmenuopen = False Then
            If Index > 0 Then 'dont select first two nodes
                popupmenuopen = True
                PopupMenu TreeMenu
            Else
                popupmenuopen = True
                Ritem = False
                StartEnd = False
                PopupMenu TreeMenu
            End If
        Else
            popupmenuopen = False
        End If
        Exit Sub
    End If
    
    'if headder was clicked
    If AreaType = 6 Then
        ButtonFunctions.StartEnd activeWorkspace
        Tree.ColHeaderButton = -1
    End If
    
    'if a expand colapse node was pressed
    If AreaType = 3 Then
    
        'Expand or collapse item as needed
        Tree.ItemExpand(Index) = Not Tree.ItemExpand(Index)
        
        Dim compairnumber As Integer
        Dim j As Integer
        'Set expanded or colapsed property in collection
        For i = 1 To activeWorkspace.ChildNodes.Count
            If activeWorkspace.ChildNodes.Item(i).DataRow = Index Then
                activeWorkspace.ChildNodes.Item(i).ExpandColapse = Not activeWorkspace.ChildNodes.Item(i).ExpandColapse
                If activeWorkspace.ChildNodes.Item(i).GroupAutoID <> 0 Then
                    compairnumber = activeWorkspace.ChildNodes.Item(i).GroupAutoID
                Else
                    compairnumber = activeWorkspace.ChildNodes.Item(i).TaskAutoID
                End If
                
                If activeWorkspace.ChildNodes.Item(i).ExpandColapse = False Then
                    For j = 1 To activeWorkspace.ChildNodes.Count
                        If activeWorkspace.ChildNodes.Item(j).GroupAutoID = compairnumber And activeWorkspace.ChildNodes.Item(i).DataRow > Index Then
                            activeWorkspace.ChildNodes.Item(j).ExpandColapse = False
                        ElseIf activeWorkspace.ChildNodes.Item(j).TaskAutoID = compairnumber And activeWorkspace.ChildNodes.Item(i).DataRow > Index Then
                            activeWorkspace.ChildNodes.Item(j).ExpandColapse = False
                        End If
                    Next j
                End If
            End If
        Next i

        'update gantt chart
        GanttChart.ClearAllRows
        For i = 0 To Tree.listCount - 1
            If Tree.ItemShown(i) Then
                'Place in gant chart
                If Tree.ItemPicture(i) = nodePict2 Then 'task
                    MDIMain.GanttChart.AddRow i, Tree.CellText(i, 1), Tree.CellText(i, 2), TaskColor, , Tree.CellText(i, 0)
                End If
               
                If Tree.ItemPicture(i) = nodePict3 Then 'procedure
                     MDIMain.GanttChart.AddRow i, Tree.CellText(i, 1), Tree.CellText(i, 2), ProcColor, , Tree.CellText(i, 0)
                End If
                
                If Tree.ItemPicture(i) = nodePict1 Then 'group
                     MDIMain.GanttChart.AddBlankRow (i)
                End If
                
            End If
        Next i
        
        
        
        GanttChart.RedrawGanttChart
    End If
    
    Dim temp As SelectionType
    tempInt = Index
    temp.row = GanttChart.GetRowFromRowID(tempInt)
    temp.sType = HasFocus
    GanttChart.Selection = temp
End Sub

'Function/Subroutine:ImageSplitter_MouseDown
'Purpose:Determine if the splitter bar is being moved
Private Sub ImageSplitter_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
    
    mbMoving = True
    
End Sub
'Function/Subroutine:ImageSplitter_MouseMove
'Purpose:If splitter bar has been moved then reset size of affected
'objects
Private Sub ImageSplitter_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
    Dim sglPos As Single
    Dim newPos As Integer
    
    If mbMoving Then
        sglPos = X + ImageSplitter.Left
        If sglPos < Tree.Left + Tree.SplitterOffset + 200 Then
            ImageSplitter.Left = Tree.Left + Tree.SplitterOffset + 200
        ElseIf sglPos > GanttChart.Left + GanttChart.Width - 50 Then
            ImageSplitter.Left = GanttChart.Left + GanttChart.Width - 50
        Else
            ImageSplitter.Left = sglPos
        End If
        
    End If
      
End Sub
'Function/Subroutine:ImageSplitter_MouseUp
'Purpose:If splitter bar has been moved then reset size of affected
'objects
Private Sub ImageSplitter_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
    If (mbMoving) Then

        Tree.Width = ImageSplitter.Left - Tree.Left + Screen.TwipsPerPixelX * 2
        Text3.Width = ImageSplitter.Left - Text3.Left + Screen.TwipsPerPixelX * 2
        
        GanttChart.Left = Tree.Left + Tree.Width + Screen.TwipsPerPixelX
        Text4.Left = GanttChart.Left
        GanttChart.Width = TabStrip1.Width - GanttChart.Left + 10
        Text4.Width = GanttChart.Width
        
        OOSTree.Width = Tree.Width
        GanttChart1.Width = GanttChart.Width
        GanttChart1.Left = GanttChart.Left
      
        mbMoving = False
    End If
End Sub
'Function/Subroutine:SetCalendarColorScheme
'Purpose:Set colors for reveiw and oversite view
Public Sub SetCalendarColorScheme()
    PVCalendar1.HeaderBackColor = GetColor(2, MDIMain.curColorScheme)
    PVCalendar1.DisplayBackColor = GetColor(3, MDIMain.curColorScheme)
    PVCalendar1.DayBackColor = GetColor(4, MDIMain.curColorScheme)
    PVCalendar1.SelectedDayBackColor = GetColor(7, MDIMain.curColorScheme)
    PVCalendar1.SelectedDayForeColor = GetColor(8, MDIMain.curColorScheme)
End Sub
'Function/Subroutine:DaysInMonth
'Purpose:function returns the number of days in a given month and year
Private Function DaysInMonth(year As Integer, Month As Integer) As Integer
    Select Case Month
        Case 1, 3, 5, 7, 8, 10, 12
            DaysInMonth = 31
        Case 4, 6, 9, 11
            DaysInMonth = 30
        Case 2
            If ((year Mod 4 = 0 And year Mod 100 <> 0) Or year Mod 400 = 0) Then
                DaysInMonth = 29
            Else
                DaysInMonth = 28
            End If
    End Select
            
End Function
'Function/Subroutine:UpdateRiskValues
'Purpose:
Private Sub UpdateRiskValues(ByVal NewDate As Date)
    Dim wMonth As Integer, wYear As Integer
    Dim wDayInMonth As Integer
    wMonth = Month(NewDate)
    wYear = year(NewDate)
    Dim EndDate As Date, StartDate As Date, curDate As Date, nextDate As Date
    Dim riskPeriodTime As Date
    Dim mySQLstatement As String
    Dim riskPeriodExists As Boolean
    Dim resultSet As rdoResultset
    Dim rarray As Variant
    
    sbStatusBar.Panels(1).text = "Updating Risk Calculations..."
    StartDate = wMonth & "-1-" & wYear
    RiskCalculator.UpdateRiskValues StartDate, 24, 31, 1
    NeedUpdateRiskValues = False
    sbStatusBar.Panels(1).text = "Running"
End Sub
'Function:
'Purpose:
Sub DisplayRiskValues(ByVal NewDate As Date, wDisplayMode As Integer)
    
    If (NeedUpdateRiskValues) Then
        UpdateRiskValues NewDate
    End If
    
    Select Case wDisplayMode
    Case 1:
        Dim Indicator(1 To 3, 1 To 3) As IPictureDisp
        Set Indicator(1, 1) = LoadPicture(workingDirectory & "icons\Ind11.bmp")
        Set Indicator(1, 2) = LoadPicture(workingDirectory & "icons\Ind12.bmp")
        Set Indicator(1, 3) = LoadPicture(workingDirectory & "icons\Ind13.bmp")
        Set Indicator(2, 1) = LoadPicture(workingDirectory & "icons\Ind21.bmp")
        Set Indicator(2, 2) = LoadPicture(workingDirectory & "icons\Ind22.bmp")
        Set Indicator(2, 3) = LoadPicture(workingDirectory & "icons\Ind23.bmp")
        Set Indicator(3, 1) = LoadPicture(workingDirectory & "icons\Ind31.bmp")
        Set Indicator(3, 2) = LoadPicture(workingDirectory & "icons\Ind32.bmp")
        Set Indicator(3, 3) = LoadPicture(workingDirectory & "icons\Ind33.bmp")
        
        Dim i As Integer
        Dim wDate As String
        Dim num, peak, average As Integer
        Dim invalidModeFound As Boolean
                
        For i = 1 To DaysInMonth(year(NewDate), Month(NewDate))
            wDate = Str(Month(NewDate)) & "-" & Str(i) & "-" & Str(year(NewDate))
            If RiskCalculator.GetRiskPeriod(i).modeID = -1 Then
                invalidModeFound = True
                PVCalendar1.DATEImage(wDate) = Nothing
            Else
                average = RiskCalculator.GetRiskPeriod(i).AverageRiskValue
                peak = RiskCalculator.ClassifyRisk(RiskCalculator.GetRiskPeriod(i).PeakRiskValue, RiskCalculator.GetRiskPeriod(i).modeID)
                If average < 1 Then average = 1
                If peak < 1 Then peak = 1
                PVCalendar1.DATEImage(wDate) = Indicator(average, peak)
            End If
        Next i
        
        
    End Select
End Sub

'Function/Subroutine:PVCalendar1_Change
'Purpose:
Private Sub PVCalendar1_Change(ByVal NewDate As Date)
    If (NeedUpdateRiskValues) Then
        DisplayRiskValues NewDate, 1
    End If
End Sub
'Function/Subroutine:PVCalendar1_DateDblClick
'Purpose:bring up a chart view when a day is selected in the review
'and oversite view - chart contains data for that day
Private Sub PVCalendar1_DateDblClick(ByVal selectedDate As Date)
    Dim chart As ChartDialog
    Set chart = New ChartDialog
    chart.RiskStartTime = selectedDate
    chart.RiskEndTime = DateAdd("d", 1, chart.RiskStartTime)
    chart.Show (1)
    Unload chart
End Sub
'Function/Subroutine:PVCalendar1_NewMonth
'Purpose:
Private Sub PVCalendar1_NewMonth()
    NeedUpdateRiskValues = True
End Sub
'Function/Subroutine:PVCalendar1_NewYear
'Purpose:
Private Sub PVCalendar1_NewYear()
    NeedUpdateRiskValues = True
End Sub
'Function/Subroutine:LoadColorSchemes
'Purpose:Load a users prefered color scheme
Private Sub LoadColorSchemes()
    Dim Index As Integer
    
    colorTable(1) = -2147483633
    colorTable(2) = 12632256
    colorTable(3) = 8421504
    colorTable(4) = 16711680
    colorTable(5) = 16777215
    colorTable(6) = &HFF
    colorTable(7) = 0
    colorTable(8) = &HFFC400
    colorTable(9) = &H80C0FF
    colorTable(10) = &H8080FF
    colorTable(11) = &HFF8080
    
    Dim resultSet As rdoResultset
    Dim mySQLstatement As String
    
    'get colors from database
    mySQLstatement = "SELECT [Primaries], [Pastels] FROM Colors"
    
    Set resultSet = dbConnection.OpenResultset(mySQLstatement)
       
    If (resultSet.EOF) Then 'set defaults
        MsgBox "SQL Failed - Failed to load colors table", vbInformation
        colors(1, 0) = &H8000000F
        colors(2, 0) = &HC0C0C0
        colors(3, 0) = &HFF0000
        colors(4, 0) = &HFFFFFF
        colors(5, 0) = &HFFFFFF
        colors(6, 0) = &HFFFFFF
        colors(7, 0) = &HFF&
        colors(8, 0) = &HFFFFFF
        colors(9, 0) = &HC0C0C0
        colors(10, 0) = &H808080
        colors(11, 0) = &H0&
        colors(12, 0) = &HFF0000
        colors(13, 0) = &HC400&
        colors(14, 0) = &HFFFFFF
        colors(15, 0) = &HFFFFFF
        colors(16, 0) = &H808080
        
        colors(1, 1) = &H8000000F
        colors(2, 1) = &HC0C0C0
        colors(3, 1) = &H80C0FF
        colors(4, 1) = &HFFFFFF
        colors(5, 1) = &HFFFFFF
        colors(6, 1) = &HFFFFFF
        colors(7, 1) = &H8080FF
        colors(8, 1) = &HFFFFFF
        colors(9, 1) = &HC0C0C0
        colors(10, 1) = &H808080
        colors(11, 1) = &H0&
        colors(12, 1) = &H80C0FF
        colors(13, 1) = &HFF8080
        colors(14, 1) = &HFFFFFF
        colors(15, 1) = &HFFFFFF
        colors(16, 1) = &H808080
    Else
       Dim colorsVariant As Variant
       colorsVariant = resultSet.GetRows(16)
       Dim wScheme As Integer
       Dim wGroup As Integer
       For wScheme = 0 To 1
            For wGroup = 1 To 16
                colors(wGroup, wScheme) = colorTable(colorsVariant(wScheme, wGroup - 1))
            Next wGroup
        Next wScheme
        ' all the color schemes should be loaded
    End If
    
End Sub
'Function/Subroutine:Tree_ItemDblClick
'Purpose:Handles the event when an item in the tree is double clicked
Private Sub Tree_ItemDblClick(ByVal Index As Long, ByVal ColNum As Integer, ByVal AreaType As Integer, ByVal Button As Integer, ByVal Shift As Integer)


    'If procedure name was selected
    If AreaType = 9 And ColNum = 0 Then
        Dim TextString As String
        Dim ProcedureID As Integer
        Dim resultSet As rdoResultset
        Dim rarray As Variant
        Dim mySQLstatement As String
        Dim i As Integer
        Dim lrArray As Variant
        Dim RowReturn As Integer
        RowReturn = 0
    
        'Determine node that was selected from tree
        TextString = Tree.CellText(Index, 0)
    
        'If node is procedure get procedure ID
        mySQLstatement = "SELECT ProcedureID FROM [Procedure] WHERE ProcedureName = '" & TextString & "'"
        Set resultSet = dbConnection.OpenResultset(mySQLstatement, rdOpenKeyset)
    
        If Not resultSet.EOF Then
            rarray = resultSet.GetRows(1)
            ProcedureID = rarray(0, 0)
    
            'Get the list of components associated with procedure
            mySQLstatement = "SELECT ComponentID FROM [ProcComp] WHERE ProcedureID = " & ProcedureID
            Set resultSet = dbConnection.OpenResultset(mySQLstatement, rdOpenKeyset)
    
            While Not resultSet.EOF
                resultSet.MoveNext
                RowReturn = RowReturn + 1
            Wend
    
            If RowReturn > 0 Then
                resultSet.MoveFirst
                rarray = resultSet.GetRows(RowReturn)

                'for each component add component name to list
'''''Add p&id information to this.
                 For i = 0 To RowReturn - 1
                    If rarray(0, i) <> 0 Then
                        mySQLstatement = "SELECT ComponentName FROM [Component] WHERE ComponentID = " & rarray(0, i)
                        Set resultSet = dbConnection.OpenResultset(mySQLstatement, rdOpenKeyset)
                    
                        lrArray = resultSet.GetRows(1)
                        ComponentList.List1.AddItem lrArray(0, 0)
                    Else
                        MsgBox "No Components Associated with Selected Procedure.", vbInformation
                        Exit Sub
                    End If
                Next i
            Else
                MsgBox "No Components Associated with Selected Procedure.", vbInformation
                Exit Sub
            End If
            'display component list
             ComponentList.Show 1
        Else
            MsgBox "Not a Procedure.", vbInformation
        End If
    End If
    
    'If statement is for case when column in table is clicked
    '(rather than tree view)
    If AreaType = 9 And ColNum <> 0 Then
        'for uneditable type
        If Tree.ItemPicture(Index) = nodePict1 Or Tree.ItemPicture(Index) = nodePict5 Or Tree.ItemPicture(Index) = nodePict4 Then
            Exit Sub
        'for procedure
        ElseIf Tree.ItemPicture(Index) = nodePict3 Then
            Dim StartDate As Date
            Dim EndDate As Date
            Dim OldEnd As Date
            Dim OldStart As Date
            'Dim i As Integer
            Dim WSID As Integer
            Dim itemID As Integer
            Dim taskref As Integer
            Dim group As Integer
            Dim mySQL As String
            
            TimeEdit.LabelText = Tree.CellText(Index, 0)
            TimeEdit.StartDate = Tree.CellText(Index, 1)
            TimeEdit.EndDate = Tree.CellText(Index, 2)
            TimeEdit.Show 1
            StartDate = TimeEdit.StartDate
            EndDate = TimeEdit.EndDate
            'MsgBox startdate & " " & enddate
            
            If TimeEdit.CancelClick = True Then
                Unload TimeEdit
                Exit Sub
            End If
            
            Unload TimeEdit
            
            'Change node in collection
                For i = 1 To activeWorkspace.ChildNodes.Count
                    If activeWorkspace.ChildNodes.Item(i).DataRow = Index Then
                        OldStart = activeWorkspace.ChildNodes.Item(i).StartTime
                        OldEnd = activeWorkspace.ChildNodes.Item(i).EndTime
                        Exit For
                    End If
                Next i
            
                WSID = activeWorkspace.workspaceId
                itemID = activeWorkspace.ChildNodes.Item(i).Identification
                taskref = activeWorkspace.ChildNodes.Item(i).TaskAutoID
                group = activeWorkspace.ChildNodes.Item(i).GroupAutoID
            
            'change item in table
            
            If pManager.ChangeProcedureTime(WSID, itemID, taskref, OldStart, OldEnd, StartDate, EndDate) = False Then
                MsgBox "Can't Change Procedure Time due to Mode Conflict", vbInformation
            Else
                activeWorkspace.ChildNodes.Item(i).StartTime = StartDate
                activeWorkspace.ChildNodes.Item(i).EndTime = EndDate
            End If
            
            'change item in tree
            OpenWorkspaces.LoadData activeWorkspace
        'for task
        Else
            
            TimeEdit.LabelText = Tree.CellText(Index, 0)
            TimeEdit.StartDate = Tree.CellText(Index, 1)
            TimeEdit.EndDate = Tree.CellText(Index, 2)
            TimeEdit.Show 1
            StartDate = TimeEdit.StartDate
            EndDate = TimeEdit.EndDate
            If TimeEdit.CancelClick = True Then
                Unload TimeEdit
                Exit Sub
            End If
            Unload TimeEdit
            
            'Change node in collection
            For i = 1 To activeWorkspace.ChildNodes.Count
                If activeWorkspace.ChildNodes.Item(i).DataRow = Index Then
                    activeWorkspace.ChildNodes.Item(i).StartTime = StartDate
                    activeWorkspace.ChildNodes.Item(i).EndTime = EndDate
                    Exit For
                End If
            Next i
            
            WSID = activeWorkspace.workspaceId
            itemID = activeWorkspace.ChildNodes.Item(i).Identification
            taskref = activeWorkspace.ChildNodes.Item(i).TaskAutoID
            group = activeWorkspace.ChildNodes.Item(i).GroupAutoID
            
            'change item in table
            mySQL = "UPDATE WorkspaceTaskSchedule SET StartTime = " _
                & SQLDate(StartDate) & ", EndTime = " & SQLDate(EndDate) & _
                " WHERE WorkspaceID = " & WSID & " AND TaskId = " _
                & itemID & " AND AutoReference = " & taskref
                
            dbConnection.Execute (mySQL)
            OpenWorkspaces.LoadData activeWorkspace
        End If
    End If
End Sub


Private Sub Tree_KeyUp(KeyCode As Integer, Shift As Integer)
    Dim tempInt As Integer
    Dim temp As SelectionType
    tempInt = Tree.listIndex
    temp.row = GanttChart.GetRowFromRowID(tempInt)
    temp.sType = HasFocus
    GanttChart.Selection = temp
End Sub
Private Sub OOSTree_KeyUp(KeyCode As Integer, Shift As Integer)
    Dim tempInt As Integer
    Dim temp As SelectionType
    tempInt = OOSTree.listIndex
    temp.row = GanttChart1.GetRowFromRowID(tempInt)
    temp.sType = HasFocus
    GanttChart1.Selection = temp
End Sub
'Function: Tree_MouseUp
'Purpose: resize headder if tree splitter bar has moved
Private Sub Tree_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
    Text2.Left = Tree.Left
    Text2.Width = Tree.SplitterOffset + 75
    Text3.Left = Tree.SplitterOffset + 265
    Text3.Width = Tree.Width - Tree.SplitterOffset - 140
End Sub
'Function: Existing_Workspaces
'Purpose: Determine if there are any existing open workspaces
Public Function Existing_Workspaces() As Integer
    Existing_Workspaces = workspaces.Count
End Function
'Function: returnID
'Purpose: provide calling function with the active workspace id.
Public Function returnID() As Integer
    returnID = activeWorkspace.workspaceId
End Function

'Function: Tree_TopChange
'Purpose: Handles the event when the top item in the list changes.
Private Sub Tree_TopChange(ByVal Index As Long)
    '
    Tree.Selected(Index) = True
    If (Tree.ItemShown(Index + 1)) Then
        GanttChart.SetVerticalScrollBar (Index + 1)
    Else
        Dim i As Integer
        For i = 2 To Tree.listCount - Index
            If (Tree.ItemShown(Index + 1)) Then
                GanttChart.SetVerticalScrollBar (Index + i)
                Exit For
            End If
        Next i
    End If
    
    Dim tempInt As Integer
    Dim temp As SelectionType
    tempInt = Index
    temp.row = GanttChart.GetRowFromRowID(tempInt)
    temp.sType = HasFocus
    GanttChart.Selection = temp
    
End Sub

Public Function RefreshData()
    OpenWorkspaces.LoadData activeWorkspace
    OpenWorkspaces.ooslistControl activeWorkspace
End Function

Private Sub mnuNewUser_Click()
    ' only an administrator should be able to do this... make sure
    If UserType <> Administrator Then
        MsgBox "Program Error.  Only an administrator should be able to create a new user.", vbCritical
        Exit Sub
    End If
    
End Sub
