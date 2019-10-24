# Microsoft Developer Studio Project File - Name="ScheduleX" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ScheduleX - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ScheduleX.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ScheduleX.mak" CFG="ScheduleX - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ScheduleX - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ScheduleX - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ScheduleX - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "ScheduleX - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "ScheduleX - Win32 Release"
# Name "ScheduleX - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\font.cpp
# End Source File
# Begin Source File

SOURCE=.\picture.cpp
# End Source File
# Begin Source File

SOURCE=.\pvalarm.cpp
# End Source File
# Begin Source File

SOURCE=.\pvappointment.cpp
# End Source File
# Begin Source File

SOURCE=.\pvappointmentset.cpp
# End Source File
# Begin Source File

SOURCE=.\pvcalendar.cpp
# End Source File
# Begin Source File

SOURCE=.\pvdayview.cpp
# End Source File
# Begin Source File

SOURCE=.\pvtaskitem.cpp
# End Source File
# Begin Source File

SOURCE=.\pvtaskpad.cpp
# End Source File
# Begin Source File

SOURCE=.\ScheduleX.cpp
# End Source File
# Begin Source File

SOURCE=.\ScheduleX.rc
# End Source File
# Begin Source File

SOURCE=.\ScheduleXDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\font.h
# End Source File
# Begin Source File

SOURCE=.\picture.h
# End Source File
# Begin Source File

SOURCE=.\pvalarm.h
# End Source File
# Begin Source File

SOURCE=.\pvappointment.h
# End Source File
# Begin Source File

SOURCE=.\pvappointmentset.h
# End Source File
# Begin Source File

SOURCE=.\pvcalendar.h
# End Source File
# Begin Source File

SOURCE=.\pvdayview.h
# End Source File
# Begin Source File

SOURCE=.\pvtaskitem.h
# End Source File
# Begin Source File

SOURCE=.\pvtaskpad.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ScheduleX.h
# End Source File
# Begin Source File

SOURCE=.\ScheduleXDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\ScheduleX.ico
# End Source File
# Begin Source File

SOURCE=.\res\ScheduleX.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section ScheduleX : {8FFC5773-EE23-11D3-9DC0-00A0CC3A1AD6}
# 	2:5:Class:CPVAppointment
# 	2:10:HeaderFile:pvappointment.h
# 	2:8:ImplFile:pvappointment.cpp
# End Section
# Section ScheduleX : {C2125ADD-D187-11D2-9C0D-00A0CC3A1AD6}
# 	2:5:Class:CPVTaskPad
# 	2:10:HeaderFile:pvtaskpad.h
# 	2:8:ImplFile:pvtaskpad.cpp
# End Section
# Section ScheduleX : {A1117B93-D7C4-11D2-9C17-00A0CC3A1AD6}
# 	2:5:Class:CPVTaskItem
# 	2:10:HeaderFile:pvtaskitem.h
# 	2:8:ImplFile:pvtaskitem.cpp
# End Section
# Section ScheduleX : {154DEBDD-A401-11D2-9BC2-00400561D975}
# 	2:5:Class:CPVDay
# 	2:10:HeaderFile:pvday.h
# 	2:8:ImplFile:pvday.cpp
# End Section
# Section ScheduleX : {7BF80981-BF32-101A-8BBB-00AA00300CAB}
# 	2:5:Class:CPicture
# 	2:10:HeaderFile:picture.h
# 	2:8:ImplFile:picture.cpp
# End Section
# Section ScheduleX : {8FFC5772-EE23-11D3-9DC0-00A0CC3A1AD6}
# 	2:5:Class:CPVAlarm
# 	2:10:HeaderFile:pvalarm.h
# 	2:8:ImplFile:pvalarm.cpp
# End Section
# Section ScheduleX : {69CD5E88-EE24-11D3-9DC0-00A0CC3A1AD6}
# 	2:21:DefaultSinkHeaderFile:pvdayview.h
# 	2:16:DefaultSinkClass:CPVDayView
# End Section
# Section ScheduleX : {45395181-EE24-11D3-9DC0-00A0CC3A1AD6}
# 	2:5:Class:CPVAppointmentSet
# 	2:10:HeaderFile:pvappointmentset.h
# 	2:8:ImplFile:pvappointmentset.cpp
# End Section
# Section ScheduleX : {22ACD16F-99EB-11D2-9BB3-00400561D975}
# 	2:21:DefaultSinkHeaderFile:pvcalendar.h
# 	2:16:DefaultSinkClass:CPVCalendar
# End Section
# Section ScheduleX : {E56F52B0-D0AD-11D2-9C0A-00A0CC3A1AD6}
# 	2:21:DefaultSinkHeaderFile:pvtaskpad.h
# 	2:16:DefaultSinkClass:CPVTaskPad
# End Section
# Section ScheduleX : {819CA2E1-E2BE-11D2-9C27-00A0CC3A1AD6}
# 	2:5:Class:CPVDayAppointment
# 	2:10:HeaderFile:pvdayappointment.h
# 	2:8:ImplFile:pvdayappointment.cpp
# End Section
# Section ScheduleX : {22ACD16E-99EB-11D2-9BB3-00400561D975}
# 	2:5:Class:CPVCalendar
# 	2:10:HeaderFile:pvcalendar.h
# 	2:8:ImplFile:pvcalendar.cpp
# End Section
# Section ScheduleX : {154DEBEA-A401-11D2-9BC2-00400561D975}
# 	2:5:Class:CPVDayAlarm
# 	2:10:HeaderFile:pvdayalarm.h
# 	2:8:ImplFile:pvdayalarm.cpp
# End Section
# Section ScheduleX : {819CA2E5-E2BE-11D2-9C27-00A0CC3A1AD6}
# 	2:5:Class:CPVDayAppointmentSet
# 	2:10:HeaderFile:pvdayappointmentset.h
# 	2:8:ImplFile:pvdayappointmentset.cpp
# End Section
# Section ScheduleX : {154DEBDE-A401-11D2-9BC2-00400561D975}
# 	2:21:DefaultSinkHeaderFile:pvday.h
# 	2:16:DefaultSinkClass:CPVDay
# End Section
# Section ScheduleX : {69CD5E81-EE24-11D3-9DC0-00A0CC3A1AD6}
# 	2:5:Class:CPVDayView
# 	2:10:HeaderFile:pvdayview.h
# 	2:8:ImplFile:pvdayview.cpp
# End Section
# Section ScheduleX : {BEF6E003-A874-101A-8BBA-00AA00300CAB}
# 	2:5:Class:COleFont
# 	2:10:HeaderFile:font.h
# 	2:8:ImplFile:font.cpp
# End Section
