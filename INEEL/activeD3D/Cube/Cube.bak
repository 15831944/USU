# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Cube - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Cube - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Cube - Win32 Release" && "$(CFG)" != "Cube - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Cube.mak" CFG="Cube - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Cube - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Cube - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "Cube - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "Cube - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\Cube.exe"

CLEAN : 
	-@erase "$(INTDIR)\Cube.res"
	-@erase "$(INTDIR)\CubeApp.obj"
	-@erase "$(INTDIR)\CubeWin.obj"
	-@erase "$(INTDIR)\HelpDialog.obj"
	-@erase "$(INTDIR)\RMapp.obj"
	-@erase "$(INTDIR)\RMwin.obj"
	-@erase "$(INTDIR)\Text.obj"
	-@erase "$(OUTDIR)\Cube.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
# ADD CPP /nologo /MT /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MT /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_MBCS" /Fp"$(INTDIR)/Cube.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Cube.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Cube.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/Cube.pdb" /machine:I386 /out:"$(OUTDIR)/Cube.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Cube.res" \
	"$(INTDIR)\CubeApp.obj" \
	"$(INTDIR)\CubeWin.obj" \
	"$(INTDIR)\HelpDialog.obj" \
	"$(INTDIR)\RMapp.obj" \
	"$(INTDIR)\RMwin.obj" \
	"$(INTDIR)\Text.obj"

"$(OUTDIR)\Cube.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Cube - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\Cube.exe"

CLEAN : 
	-@erase "$(INTDIR)\Cube.res"
	-@erase "$(INTDIR)\CubeApp.obj"
	-@erase "$(INTDIR)\CubeWin.obj"
	-@erase "$(INTDIR)\HelpDialog.obj"
	-@erase "$(INTDIR)\RMapp.obj"
	-@erase "$(INTDIR)\RMwin.obj"
	-@erase "$(INTDIR)\Text.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Cube.exe"
	-@erase "$(OUTDIR)\Cube.ilk"
	-@erase "$(OUTDIR)\Cube.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Cube.pch" /YX /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Cube.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Cube.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/Cube.pdb" /debug /machine:I386 /out:"$(OUTDIR)/Cube.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Cube.res" \
	"$(INTDIR)\CubeApp.obj" \
	"$(INTDIR)\CubeWin.obj" \
	"$(INTDIR)\HelpDialog.obj" \
	"$(INTDIR)\RMapp.obj" \
	"$(INTDIR)\RMwin.obj" \
	"$(INTDIR)\Text.obj"

"$(OUTDIR)\Cube.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "Cube - Win32 Release"
# Name "Cube - Win32 Debug"

!IF  "$(CFG)" == "Cube - Win32 Release"

!ELSEIF  "$(CFG)" == "Cube - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Cube.rc
DEP_RSC_CUBE_=\
	".\icon1.ico"\
	".\win95.ppm"\
	

"$(INTDIR)\Cube.res" : $(SOURCE) $(DEP_RSC_CUBE_) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\CubeApp.cpp
DEP_CPP_CUBEA=\
	"..\..\..\dxsdk\sdk\inc\d3dcaps.h"\
	"..\..\..\dxsdk\sdk\inc\d3drmdef.h"\
	"..\..\..\dxsdk\sdk\inc\d3drmobj.h"\
	"..\..\..\dxsdk\sdk\inc\d3dtypes.h"\
	".\CubeApp.h"\
	".\CubeWin.h"\
	".\RMApp.h"\
	".\RMWin.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	
NODEP_CPP_CUBEA=\
	"..\..\..\dxsdk\sdk\inc\d3dcom.h"\
	"..\..\..\dxsdk\sdk\inc\subwtype.h"\
	

"$(INTDIR)\CubeApp.obj" : $(SOURCE) $(DEP_CPP_CUBEA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\CubeWin.cpp
DEP_CPP_CUBEW=\
	"..\..\..\dxsdk\sdk\inc\d3dcaps.h"\
	"..\..\..\dxsdk\sdk\inc\d3drmdef.h"\
	"..\..\..\dxsdk\sdk\inc\d3drmobj.h"\
	"..\..\..\dxsdk\sdk\inc\d3dtypes.h"\
	".\CubeWin.h"\
	".\HelpDialog.h"\
	".\RMWin.h"\
	".\Text.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	
NODEP_CPP_CUBEW=\
	"..\..\..\dxsdk\sdk\inc\d3dcom.h"\
	"..\..\..\dxsdk\sdk\inc\subwtype.h"\
	

"$(INTDIR)\CubeWin.obj" : $(SOURCE) $(DEP_CPP_CUBEW) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\RMwin.cpp
DEP_CPP_RMWIN=\
	"..\..\..\dxsdk\sdk\inc\d3dcaps.h"\
	"..\..\..\dxsdk\sdk\inc\d3drmdef.h"\
	"..\..\..\dxsdk\sdk\inc\d3drmobj.h"\
	"..\..\..\dxsdk\sdk\inc\d3dtypes.h"\
	".\RMApp.h"\
	".\RMWin.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	
NODEP_CPP_RMWIN=\
	"..\..\..\dxsdk\sdk\inc\d3dcom.h"\
	"..\..\..\dxsdk\sdk\inc\subwtype.h"\
	

"$(INTDIR)\RMwin.obj" : $(SOURCE) $(DEP_CPP_RMWIN) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\RMapp.cpp
DEP_CPP_RMAPP=\
	"..\..\..\dxsdk\sdk\inc\d3dcaps.h"\
	"..\..\..\dxsdk\sdk\inc\d3drmdef.h"\
	"..\..\..\dxsdk\sdk\inc\d3drmobj.h"\
	"..\..\..\dxsdk\sdk\inc\d3dtypes.h"\
	".\RMApp.h"\
	".\RMWin.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	
NODEP_CPP_RMAPP=\
	"..\..\..\dxsdk\sdk\inc\d3dcom.h"\
	"..\..\..\dxsdk\sdk\inc\subwtype.h"\
	

"$(INTDIR)\RMapp.obj" : $(SOURCE) $(DEP_CPP_RMAPP) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\HelpDialog.cpp
DEP_CPP_HELPD=\
	".\HelpDialog.h"\
	".\Text.h"\
	

"$(INTDIR)\HelpDialog.obj" : $(SOURCE) $(DEP_CPP_HELPD) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Text.cpp
DEP_CPP_TEXT_=\
	".\Text.h"\
	

"$(INTDIR)\Text.obj" : $(SOURCE) $(DEP_CPP_TEXT_) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
