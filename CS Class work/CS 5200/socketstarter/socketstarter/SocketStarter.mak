# Microsoft Developer Studio Generated NMAKE File, Format Version 40001
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=SocketStarter - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to SocketStarter - Win32\
 Debug.
!ENDIF 

!IF "$(CFG)" != "SocketStarter - Win32 Release" && "$(CFG)" !=\
 "SocketStarter - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "SocketStarter.mak" CFG="SocketStarter - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SocketStarter - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SocketStarter - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "SocketStarter - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "SocketStarter - Win32 Release"

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
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\SocketStarter.exe"

CLEAN : 
	-@erase ".\Release\SocketStarter.exe"
	-@erase ".\Release\PassiveStreamDlg.obj"
	-@erase ".\Release\SocketStarter.pch"
	-@erase ".\Release\DatagramDlg.obj"
	-@erase ".\Release\SocketStarterDlg.obj"
	-@erase ".\Release\ActiveStreamDlg.obj"
	-@erase ".\Release\DatagramSocket.obj"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\WatchDlg.obj"
	-@erase ".\Release\StreamSocket.obj"
	-@erase ".\Release\SocketStarter.obj"
	-@erase ".\Release\SocketStarter.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/SocketStarter.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/SocketStarter.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SocketStarter.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/SocketStarter.pdb" /machine:I386\
 /out:"$(OUTDIR)/SocketStarter.exe" 
LINK32_OBJS= \
	"$(INTDIR)/PassiveStreamDlg.obj" \
	"$(INTDIR)/DatagramDlg.obj" \
	"$(INTDIR)/SocketStarterDlg.obj" \
	"$(INTDIR)/ActiveStreamDlg.obj" \
	"$(INTDIR)/DatagramSocket.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/WatchDlg.obj" \
	"$(INTDIR)/StreamSocket.obj" \
	"$(INTDIR)/SocketStarter.obj" \
	"$(INTDIR)/SocketStarter.res"

"$(OUTDIR)\SocketStarter.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SocketStarter - Win32 Debug"

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
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\SocketStarter.exe"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\SocketStarter.pch"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\SocketStarter.exe"
	-@erase ".\Debug\SocketStarterDlg.obj"
	-@erase ".\Debug\DatagramSocket.obj"
	-@erase ".\Debug\WatchDlg.obj"
	-@erase ".\Debug\StreamSocket.obj"
	-@erase ".\Debug\ActiveStreamDlg.obj"
	-@erase ".\Debug\PassiveStreamDlg.obj"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\DatagramDlg.obj"
	-@erase ".\Debug\SocketStarter.obj"
	-@erase ".\Debug\SocketStarter.res"
	-@erase ".\Debug\SocketStarter.ilk"
	-@erase ".\Debug\SocketStarter.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/SocketStarter.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/SocketStarter.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SocketStarter.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/SocketStarter.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/SocketStarter.exe" 
LINK32_OBJS= \
	"$(INTDIR)/SocketStarterDlg.obj" \
	"$(INTDIR)/DatagramSocket.obj" \
	"$(INTDIR)/WatchDlg.obj" \
	"$(INTDIR)/StreamSocket.obj" \
	"$(INTDIR)/ActiveStreamDlg.obj" \
	"$(INTDIR)/PassiveStreamDlg.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/DatagramDlg.obj" \
	"$(INTDIR)/SocketStarter.obj" \
	"$(INTDIR)/SocketStarter.res"

"$(OUTDIR)\SocketStarter.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "SocketStarter - Win32 Release"
# Name "SocketStarter - Win32 Debug"

!IF  "$(CFG)" == "SocketStarter - Win32 Release"

!ELSEIF  "$(CFG)" == "SocketStarter - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "SocketStarter - Win32 Release"

!ELSEIF  "$(CFG)" == "SocketStarter - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SocketStarter.cpp
DEP_CPP_SOCKE=\
	".\StdAfx.h"\
	".\SocketStarter.h"\
	".\SocketStarterDlg.h"\
	".\WatchDlg.h"\
	".\StreamSocket.h"\
	".\ActiveStreamDlg.h"\
	".\PassiveStreamDlg.h"\
	".\DatagramDlg.h"\
	

"$(INTDIR)\SocketStarter.obj" : $(SOURCE) $(DEP_CPP_SOCKE) "$(INTDIR)"\
 "$(INTDIR)\SocketStarter.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\SocketStarterDlg.cpp
DEP_CPP_SOCKET=\
	".\StdAfx.h"\
	".\SocketStarter.h"\
	".\SocketStarterDlg.h"\
	".\WatchDlg.h"\
	".\StreamSocket.h"\
	".\ActiveStreamDlg.h"\
	".\PassiveStreamDlg.h"\
	".\DatagramDlg.h"\
	

"$(INTDIR)\SocketStarterDlg.obj" : $(SOURCE) $(DEP_CPP_SOCKET) "$(INTDIR)"\
 "$(INTDIR)\SocketStarter.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "SocketStarter - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/SocketStarter.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\SocketStarter.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "SocketStarter - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/SocketStarter.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\SocketStarter.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SocketStarter.rc
DEP_RSC_SOCKETS=\
	".\res\SocketStarter.ico"\
	".\res\SocketStarter.rc2"\
	

"$(INTDIR)\SocketStarter.res" : $(SOURCE) $(DEP_RSC_SOCKETS) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ActiveStreamDlg.cpp
DEP_CPP_ACTIV=\
	".\StdAfx.h"\
	".\SocketStarter.h"\
	".\SocketStarterDlg.h"\
	".\ActiveStreamDlg.h"\
	".\WatchDlg.h"\
	".\StreamSocket.h"\
	".\PassiveStreamDlg.h"\
	".\DatagramDlg.h"\
	

"$(INTDIR)\ActiveStreamDlg.obj" : $(SOURCE) $(DEP_CPP_ACTIV) "$(INTDIR)"\
 "$(INTDIR)\SocketStarter.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\PassiveStreamDlg.cpp
DEP_CPP_PASSI=\
	".\StdAfx.h"\
	".\SocketStarter.h"\
	".\SocketStarterDlg.h"\
	".\PassiveStreamDlg.h"\
	".\StreamSocket.h"\
	".\WatchDlg.h"\
	".\ActiveStreamDlg.h"\
	".\DatagramDlg.h"\
	

"$(INTDIR)\PassiveStreamDlg.obj" : $(SOURCE) $(DEP_CPP_PASSI) "$(INTDIR)"\
 "$(INTDIR)\SocketStarter.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DatagramDlg.cpp

!IF  "$(CFG)" == "SocketStarter - Win32 Release"

DEP_CPP_DATAG=\
	".\StdAfx.h"\
	".\SocketStarter.h"\
	".\SocketStarterDlg.h"\
	".\DatagramDlg.h"\
	".\DatagramSocket.h"\
	".\WatchDlg.h"\
	".\StreamSocket.h"\
	".\ActiveStreamDlg.h"\
	".\PassiveStreamDlg.h"\
	
NODEP_CPP_DATAG=\
	".\datagram_sock"\
	

"$(INTDIR)\DatagramDlg.obj" : $(SOURCE) $(DEP_CPP_DATAG) "$(INTDIR)"\
 "$(INTDIR)\SocketStarter.pch"


!ELSEIF  "$(CFG)" == "SocketStarter - Win32 Debug"

DEP_CPP_DATAG=\
	".\StdAfx.h"\
	".\SocketStarter.h"\
	".\SocketStarterDlg.h"\
	".\DatagramDlg.h"\
	".\DatagramSocket.h"\
	".\WatchDlg.h"\
	".\StreamSocket.h"\
	".\ActiveStreamDlg.h"\
	".\PassiveStreamDlg.h"\
	

"$(INTDIR)\DatagramDlg.obj" : $(SOURCE) $(DEP_CPP_DATAG) "$(INTDIR)"\
 "$(INTDIR)\SocketStarter.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\WatchDlg.cpp
DEP_CPP_WATCH=\
	".\StdAfx.h"\
	".\SocketStarter.h"\
	".\WatchDlg.h"\
	".\StreamSocket.h"\
	

"$(INTDIR)\WatchDlg.obj" : $(SOURCE) $(DEP_CPP_WATCH) "$(INTDIR)"\
 "$(INTDIR)\SocketStarter.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StreamSocket.cpp
DEP_CPP_STREA=\
	".\StdAfx.h"\
	".\SocketStarter.h"\
	".\StreamSocket.h"\
	".\ActiveStreamDlg.h"\
	".\WatchDlg.h"\
	

"$(INTDIR)\StreamSocket.obj" : $(SOURCE) $(DEP_CPP_STREA) "$(INTDIR)"\
 "$(INTDIR)\SocketStarter.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DatagramSocket.cpp
DEP_CPP_DATAGR=\
	".\StdAfx.h"\
	".\SocketStarter.h"\
	".\DatagramSocket.h"\
	".\DatagramDlg.h"\
	".\WatchDlg.h"\
	".\StreamSocket.h"\
	

"$(INTDIR)\DatagramSocket.obj" : $(SOURCE) $(DEP_CPP_DATAGR) "$(INTDIR)"\
 "$(INTDIR)\SocketStarter.pch"


# End Source File
# End Target
# End Project
################################################################################
