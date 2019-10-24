# Microsoft Developer Studio Project File - Name="TestPackage" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=TestPackage - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TestPackage.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TestPackage.mak" CFG="TestPackage - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TestPackage - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "TestPackage - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TestPackage - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
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
# ADD LINK32 winmm.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "TestPackage - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "TESTING" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 winmm.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "TestPackage - Win32 Release"
# Name "TestPackage - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\common\Building.cpp
# End Source File
# Begin Source File

SOURCE=..\common\Calendar.cpp
# End Source File
# Begin Source File

SOURCE=..\common\CalendarDate.cpp
# End Source File
# Begin Source File

SOURCE=..\client\ClientComChannel.cpp
# End Source File
# Begin Source File

SOURCE=..\common\ComChannel.cpp
# End Source File
# Begin Source File

SOURCE=..\common\Configuration.cpp
# End Source File
# Begin Source File

SOURCE=..\common\DString.cpp
# End Source File
# Begin Source File

SOURCE=..\common\Event.cpp
# End Source File
# Begin Source File

SOURCE=..\common\Location.cpp
# End Source File
# Begin Source File

SOURCE=..\common\LogicalClock.cpp
# End Source File
# Begin Source File

SOURCE=..\common\Marshall.cpp
# End Source File
# Begin Source File

SOURCE=..\common\MeetingPreference.cpp
# End Source File
# Begin Source File

SOURCE=..\common\Message.cpp
# End Source File
# Begin Source File

SOURCE=..\common\PersistentObjectSet.cpp
# End Source File
# Begin Source File

SOURCE=..\common\Reply.cpp
# End Source File
# Begin Source File

SOURCE=..\common\Request.cpp
# End Source File
# Begin Source File

SOURCE=..\common\RequestReply.cpp
# End Source File
# Begin Source File

SOURCE=..\common\ReservedTime.cpp
# End Source File
# Begin Source File

SOURCE=..\server\ServerComChannel.cpp
# End Source File
# Begin Source File

SOURCE=..\common\SockAddr.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\common\strdup.cpp
# End Source File
# Begin Source File

SOURCE=.\TestPackage.cpp
# End Source File
# Begin Source File

SOURCE=.\TestPackage.rc
# End Source File
# Begin Source File

SOURCE=.\TestPackageDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\common\TimeBlock.cpp
# End Source File
# Begin Source File

SOURCE=..\common\TimeOfDay.cpp
# End Source File
# Begin Source File

SOURCE=..\common\User.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\common\Building.h
# End Source File
# Begin Source File

SOURCE=..\common\Calendar.h
# End Source File
# Begin Source File

SOURCE=..\common\CalendarDate.h
# End Source File
# Begin Source File

SOURCE=..\client\ClientComChannel.h
# End Source File
# Begin Source File

SOURCE=..\common\ComChannel.h
# End Source File
# Begin Source File

SOURCE=..\common\DString.h
# End Source File
# Begin Source File

SOURCE=..\common\DTime.h
# End Source File
# Begin Source File

SOURCE=..\common\Event.h
# End Source File
# Begin Source File

SOURCE=..\common\Location.h
# End Source File
# Begin Source File

SOURCE=..\common\LogicalClock.h
# End Source File
# Begin Source File

SOURCE=..\common\Marshall.h
# End Source File
# Begin Source File

SOURCE=..\common\MeetingPreference.h
# End Source File
# Begin Source File

SOURCE=..\common\Message.h
# End Source File
# Begin Source File

SOURCE=..\common\PersistentObject.h
# End Source File
# Begin Source File

SOURCE=..\common\PersistentObjectSet.h
# End Source File
# Begin Source File

SOURCE=..\common\Reply.h
# End Source File
# Begin Source File

SOURCE=..\common\Request.h
# End Source File
# Begin Source File

SOURCE=..\common\RequestReply.h
# End Source File
# Begin Source File

SOURCE=..\common\ReservedTime.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=..\server\ServerComChannel.h
# End Source File
# Begin Source File

SOURCE=..\common\SockAddr.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TestPackage.h
# End Source File
# Begin Source File

SOURCE=.\TestPackageDlg.h
# End Source File
# Begin Source File

SOURCE=..\common\TimeBlock.h
# End Source File
# Begin Source File

SOURCE=..\common\TimeOfDay.h
# End Source File
# Begin Source File

SOURCE=..\common\User.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\TestPackage.ico
# End Source File
# Begin Source File

SOURCE=.\res\TestPackage.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
