# Microsoft Developer Studio Project File - Name="LADA Control Module" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=LADA Control Module - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "LADA Control Module.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "LADA Control Module.mak" CFG="LADA Control Module - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LADA Control Module - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "LADA Control Module - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath "Desktop"
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "LADA Control Module - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 Winmm.lib htmlhelp.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "LADA Control Module - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "c:\program files\html help workshop\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 Winmm.lib Htmlhelp.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "LADA Control Module - Win32 Release"
# Name "LADA Control Module - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CalibrationDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CalibrationDlg2.cpp
# End Source File
# Begin Source File

SOURCE=.\Camera.cpp
# End Source File
# Begin Source File

SOURCE=.\CameraData.cpp
# End Source File
# Begin Source File

SOURCE=.\cameradialogDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CamerasPage.cpp
# End Source File
# Begin Source File

SOURCE=.\CameraStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\ChangeLocationDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Checkout.cpp
# End Source File
# Begin Source File

SOURCE=.\CheckOutDlg1.cpp
# End Source File
# Begin Source File

SOURCE=.\ChooseIcon.cpp
# End Source File
# Begin Source File

SOURCE=.\ChooseLocationsDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorCheckButton.cpp
# End Source File
# Begin Source File

SOURCE=.\CommFunctions.cpp
# End Source File
# Begin Source File

SOURCE=.\CommOperations.cpp
# End Source File
# Begin Source File

SOURCE=.\ControlParameters.cpp
# End Source File
# Begin Source File

SOURCE=.\CR10FinalStorageDebugReport.cpp
# End Source File
# Begin Source File

SOURCE=.\Cr10FunctionsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DataCollectionSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\DataCollectionStatusDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DataTransfer.cpp
# End Source File
# Begin Source File

SOURCE=.\DIB.cpp
# End Source File
# Begin Source File

SOURCE=.\Display.cpp
# End Source File
# Begin Source File

SOURCE=.\FileData.cpp
# End Source File
# Begin Source File

SOURCE=.\FinalStoragePage.cpp
# End Source File
# Begin Source File

SOURCE=.\Flag.cpp
# End Source File
# Begin Source File

SOURCE=.\FSInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphButtonForm.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphCollection.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphDisplayView.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphProperties.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\HISTORYCLASS.CPP
# End Source File
# Begin Source File

SOURCE=.\ILFileDisplayInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\ILGroupProperties.cpp
# End Source File
# Begin Source File

SOURCE=.\ILProperties.cpp
# End Source File
# Begin Source File

SOURCE=.\ImportFSLDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\InputLocationReadTest.cpp
# End Source File
# Begin Source File

SOURCE=.\InputLocationsPage.cpp
# End Source File
# Begin Source File

SOURCE=.\InputLocFileInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\InputRequest.cpp
# End Source File
# Begin Source File

SOURCE=".\LADA Control Module.cpp"
# End Source File
# Begin Source File

SOURCE=".\LADA Control Module.rc"
# End Source File
# Begin Source File

SOURCE=".\LADA Control ModuleDoc.cpp"
# End Source File
# Begin Source File

SOURCE=".\LADA Control ModuleView.cpp"
# End Source File
# Begin Source File

SOURCE=.\LADASetupDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\LadaTest.cpp
# End Source File
# Begin Source File

SOURCE=.\LanguageChanger.cpp
# End Source File
# Begin Source File

SOURCE=.\LString.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ManualControl.cpp
# End Source File
# Begin Source File

SOURCE=.\ManualSample.cpp
# End Source File
# Begin Source File

SOURCE=.\MessageBox.cpp
# End Source File
# Begin Source File

SOURCE=.\MinMax.cpp
# End Source File
# Begin Source File

SOURCE=.\NewProject1.cpp
# End Source File
# Begin Source File

SOURCE=.\NewProject2.cpp
# End Source File
# Begin Source File

SOURCE=.\ParamDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ParamMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\ProgressDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\RenameLocationDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ReplaceGraphDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SetFrequencyDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StartDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Stepinfo.cpp
# End Source File
# Begin Source File

SOURCE=.\SystemDiagDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\TwainCpp.cpp
# End Source File
# Begin Source File

SOURCE=.\Verify.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewHistoryDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\WaitTimerInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\WetupDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\WetupInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\WetupSettingsDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BTCImageData.h
# End Source File
# Begin Source File

SOURCE=.\BTCImageObject.h
# End Source File
# Begin Source File

SOURCE=.\BTCIOStream.h
# End Source File
# Begin Source File

SOURCE=.\BTDefines.h
# End Source File
# Begin Source File

SOURCE=.\BTICodec.h
# End Source File
# Begin Source File

SOURCE=.\BTIProgressNotification.h
# End Source File
# Begin Source File

SOURCE=.\BTNexgenIPL.h
# End Source File
# Begin Source File

SOURCE=.\CalibrationDlg.h
# End Source File
# Begin Source File

SOURCE=.\CalibrationDlg2.h
# End Source File
# Begin Source File

SOURCE=.\Camera.h
# End Source File
# Begin Source File

SOURCE=.\CameraData.h
# End Source File
# Begin Source File

SOURCE=.\cameradialogDlg.h
# End Source File
# Begin Source File

SOURCE=.\CamerasPage.h
# End Source File
# Begin Source File

SOURCE=.\CameraStatus.h
# End Source File
# Begin Source File

SOURCE=.\ChangeLocationDlg.h
# End Source File
# Begin Source File

SOURCE=.\Checkout.h
# End Source File
# Begin Source File

SOURCE=.\CheckOutDlg1.h
# End Source File
# Begin Source File

SOURCE=.\ChooseIcon.h
# End Source File
# Begin Source File

SOURCE=.\ChooseLocationsDialog.h
# End Source File
# Begin Source File

SOURCE=.\ColorCheckButton.h
# End Source File
# Begin Source File

SOURCE=.\CommFunctions.h
# End Source File
# Begin Source File

SOURCE=.\CommOperations.h
# End Source File
# Begin Source File

SOURCE=.\ControlParameters.h
# End Source File
# Begin Source File

SOURCE=.\CR10FinalStorageDebugReport.h
# End Source File
# Begin Source File

SOURCE=.\Cr10FunctionsDlg.h
# End Source File
# Begin Source File

SOURCE=.\DataCollectionSheet.h
# End Source File
# Begin Source File

SOURCE=.\DataCollectionStatusDlg.h
# End Source File
# Begin Source File

SOURCE=.\DataTransfer.h
# End Source File
# Begin Source File

SOURCE=.\DIB.h
# End Source File
# Begin Source File

SOURCE=.\Display.h
# End Source File
# Begin Source File

SOURCE=.\FileData.h
# End Source File
# Begin Source File

SOURCE=.\FinalStoragePage.h
# End Source File
# Begin Source File

SOURCE=.\Flag.h
# End Source File
# Begin Source File

SOURCE=.\FSInfo.h
# End Source File
# Begin Source File

SOURCE=.\GraphButtonForm.h
# End Source File
# Begin Source File

SOURCE=.\GraphCollection.h
# End Source File
# Begin Source File

SOURCE=.\GraphDisplayView.h
# End Source File
# Begin Source File

SOURCE=.\GraphProperties.h
# End Source File
# Begin Source File

SOURCE=.\GraphWindow.h
# End Source File
# Begin Source File

SOURCE=.\HISTORYCLASS.H
# End Source File
# Begin Source File

SOURCE=.\ILFileDisplayInfo.h
# End Source File
# Begin Source File

SOURCE=.\ILGroupProperties.h
# End Source File
# Begin Source File

SOURCE=.\ILProperties.h
# End Source File
# Begin Source File

SOURCE=.\ImportFSLDlg.h
# End Source File
# Begin Source File

SOURCE=.\InputLocationReadTest.h
# End Source File
# Begin Source File

SOURCE=.\inputlocations.h
# End Source File
# Begin Source File

SOURCE=.\InputLocationsPage.h
# End Source File
# Begin Source File

SOURCE=.\InputLocFileInfo.h
# End Source File
# Begin Source File

SOURCE=.\InputRequest.h
# End Source File
# Begin Source File

SOURCE=".\LADA Control Module.h"
# End Source File
# Begin Source File

SOURCE=".\LADA Control ModuleDoc.h"
# End Source File
# Begin Source File

SOURCE=".\LADA Control ModuleView.h"
# End Source File
# Begin Source File

SOURCE=.\LADASetupDlg.h
# End Source File
# Begin Source File

SOURCE=.\Ladastrings.h
# End Source File
# Begin Source File

SOURCE=.\LadaTest.h
# End Source File
# Begin Source File

SOURCE=.\LanguageChanger.h
# End Source File
# Begin Source File

SOURCE=.\List.h
# End Source File
# Begin Source File

SOURCE=.\LString.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\ManualControl.h
# End Source File
# Begin Source File

SOURCE=.\ManualSample.h
# End Source File
# Begin Source File

SOURCE=.\MessageBox.h
# End Source File
# Begin Source File

SOURCE=.\MinMax.h
# End Source File
# Begin Source File

SOURCE=.\NewProject1.h
# End Source File
# Begin Source File

SOURCE=.\NewProject2.h
# End Source File
# Begin Source File

SOURCE=.\ParamDlg.h
# End Source File
# Begin Source File

SOURCE=.\ParamMenu.h
# End Source File
# Begin Source File

SOURCE=.\ProgressDialog.h
# End Source File
# Begin Source File

SOURCE=.\RenameLocationDialog.h
# End Source File
# Begin Source File

SOURCE=.\ReplaceGraphDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SetFrequencyDlg.h
# End Source File
# Begin Source File

SOURCE=.\StartDialog.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Stepinfo.h
# End Source File
# Begin Source File

SOURCE=.\SystemDiagDlg.h
# End Source File
# Begin Source File

SOURCE=.\ToolBar.h
# End Source File
# Begin Source File

SOURCE=.\twain.h
# End Source File
# Begin Source File

SOURCE=.\TwainCpp.h
# End Source File
# Begin Source File

SOURCE=.\Verify.h
# End Source File
# Begin Source File

SOURCE=.\ViewHistoryDialog.h
# End Source File
# Begin Source File

SOURCE=.\WaitTimerInfo.h
# End Source File
# Begin Source File

SOURCE=.\WetupDialog.h
# End Source File
# Begin Source File

SOURCE=.\WetupInfo.h
# End Source File
# Begin Source File

SOURCE=.\WetupSettingsDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\RES\automode.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap5.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap6.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap7.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00004.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00005.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00006.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00007.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00008.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00009.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\bmp00010.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\bmp00011.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\bmp00012.bmp
# End Source File
# Begin Source File

SOURCE=.\res\camera.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cameradead.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Coldtool.bmp
# End Source File
# Begin Source File

SOURCE=.\res\connect.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\connecte.bmp
# End Source File
# Begin Source File

SOURCE=.\res\disconnect.bmp
# End Source File
# Begin Source File

SOURCE=.\res\floppyd.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Hottoolb.bmp
# End Source File
# Begin Source File

SOURCE=".\LADA Control Module.ico"
# End Source File
# Begin Source File

SOURCE=".\res\LADA Control Module.ico"
# End Source File
# Begin Source File

SOURCE=".\res\LADA Control Module.rc2"
# End Source File
# Begin Source File

SOURCE=".\res\LADA Control ModuleDoc.ico"
# End Source File
# Begin Source File

SOURCE=.\RES\manmode.bmp
# End Source File
# Begin Source File

SOURCE=".\res\MIR-NASA (light).bmp"
# End Source File
# Begin Source File

SOURCE=.\res\nosticdead.bmp
# End Source File
# Begin Source File

SOURCE=.\res\nosticlive.bmp
# End Source File
# Begin Source File

SOURCE=.\res\notconne.bmp
# End Source File
# Begin Source File

SOURCE=.\res\sampledead.bmp
# End Source File
# Begin Source File

SOURCE=.\res\samplelive.bmp
# End Source File
# Begin Source File

SOURCE=.\sdi.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Group "Code Documentation"

# PROP Default_Filter ""
# Begin Source File

SOURCE=".\Class Glosary.txt"
# End Source File
# Begin Source File

SOURCE=".\Communication Explanation.doc"
# End Source File
# Begin Source File

SOURCE=.\SaveVariables.txt
# End Source File
# End Group
# Begin Source File

SOURCE=.\calibration.txt
# End Source File
# Begin Source File

SOURCE=".\Data Ranges.txt"
# End Source File
# Begin Source File

SOURCE=".\Explanation of Locations for SMP Moisture Control.txt"
# End Source File
# Begin Source File

SOURCE=".\Explanation of RegularCSI.txt"
# End Source File
# Begin Source File

SOURCE=".\LADA Control Module.reg"
# End Source File
# Begin Source File

SOURCE=.\Ladastrings.str
# End Source File
# Begin Source File

SOURCE=.\Newblue.csi
# End Source File
# Begin Source File

SOURCE=".\Project History File Protocol.txt"
# End Source File
# Begin Source File

SOURCE=".\Questions about Check Out.doc"
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=".\Revision History.rtf"
# End Source File
# Begin Source File

SOURCE=".\Software Test Plan.doc"
# End Source File
# Begin Source File

SOURCE=".\To Test.txt"
# End Source File
# Begin Source File

SOURCE=.\ToDoList.doc
# End Source File
# End Target
# End Project
