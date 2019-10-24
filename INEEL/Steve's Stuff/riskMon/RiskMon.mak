# Microsoft Developer Studio Generated NMAKE File, Based on RiskMon.dsp
!IF "$(CFG)" == ""
CFG=RiskMon - Win32 Debug
!MESSAGE No configuration specified. Defaulting to RiskMon - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "RiskMon - Win32 Release" && "$(CFG)" !=\
 "RiskMon - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RiskMon.mak" CFG="RiskMon - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RiskMon - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RiskMon - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "RiskMon - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\RiskMon.dll"

!ELSE 

ALL : "$(OUTDIR)\RiskMon.dll"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\ArrayListLL.obj"
	-@erase "$(INTDIR)\RiskFunctions.obj"
	-@erase "$(INTDIR)\RiskMon.obj"
	-@erase "$(INTDIR)\RiskMon.pch"
	-@erase "$(INTDIR)\RiskMon.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StringLList.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\RiskMon.dll"
	-@erase "$(OUTDIR)\RiskMon.exp"
	-@erase "$(OUTDIR)\RiskMon.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_USRDLL" /Fp"$(INTDIR)\RiskMon.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\RiskMon.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\RiskMon.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\RiskMon.pdb" /machine:I386 /def:".\RiskMon.def"\
 /out:"$(OUTDIR)\RiskMon.dll" /implib:"$(OUTDIR)\RiskMon.lib" 
DEF_FILE= \
	".\RiskMon.def"
LINK32_OBJS= \
	"$(INTDIR)\ArrayListLL.obj" \
	"$(INTDIR)\RiskFunctions.obj" \
	"$(INTDIR)\RiskMon.obj" \
	"$(INTDIR)\RiskMon.res" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\StringLList.obj"

"$(OUTDIR)\RiskMon.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "RiskMon - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "c:\winnt\system32\RiskMon.dll" "$(OUTDIR)\RiskMon.bsc"

!ELSE 

ALL : "c:\winnt\system32\RiskMon.dll" "$(OUTDIR)\RiskMon.bsc"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\ArrayListLL.obj"
	-@erase "$(INTDIR)\ArrayListLL.sbr"
	-@erase "$(INTDIR)\RiskFunctions.obj"
	-@erase "$(INTDIR)\RiskFunctions.sbr"
	-@erase "$(INTDIR)\RiskMon.obj"
	-@erase "$(INTDIR)\RiskMon.pch"
	-@erase "$(INTDIR)\RiskMon.res"
	-@erase "$(INTDIR)\RiskMon.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\StringLList.obj"
	-@erase "$(INTDIR)\StringLList.sbr"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\RiskMon.bsc"
	-@erase "$(OUTDIR)\RiskMon.exp"
	-@erase "$(OUTDIR)\RiskMon.lib"
	-@erase "$(OUTDIR)\RiskMon.pdb"
	-@erase "c:\winnt\system32\RiskMon.dll"
	-@erase "c:\winnt\system32\RiskMon.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\RiskMon.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\RiskMon.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\RiskMon.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ArrayListLL.sbr" \
	"$(INTDIR)\RiskFunctions.sbr" \
	"$(INTDIR)\RiskMon.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\StringLList.sbr"

"$(OUTDIR)\RiskMon.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=winmm.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\RiskMon.pdb" /debug /machine:I386 /def:".\RiskMon.def"\
 /out:"c:\winnt\system32\RiskMon.dll" /implib:"$(OUTDIR)\RiskMon.lib"\
 /pdbtype:sept 
DEF_FILE= \
	".\RiskMon.def"
LINK32_OBJS= \
	"$(INTDIR)\ArrayListLL.obj" \
	"$(INTDIR)\RiskFunctions.obj" \
	"$(INTDIR)\RiskMon.obj" \
	"$(INTDIR)\RiskMon.res" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\StringLList.obj"

"c:\winnt\system32\RiskMon.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "RiskMon - Win32 Release" || "$(CFG)" ==\
 "RiskMon - Win32 Debug"
SOURCE=.\ArrayListLL.cpp

!IF  "$(CFG)" == "RiskMon - Win32 Release"

DEP_CPP_ARRAY=\
	".\ArrayListLL.h"\
	".\RiskMon.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\ArrayListLL.obj" : $(SOURCE) $(DEP_CPP_ARRAY) "$(INTDIR)"\
 "$(INTDIR)\RiskMon.pch"


!ELSEIF  "$(CFG)" == "RiskMon - Win32 Debug"

DEP_CPP_ARRAY=\
	".\ArrayListLL.h"\
	".\RiskMon.h"\
	

"$(INTDIR)\ArrayListLL.obj"	"$(INTDIR)\ArrayListLL.sbr" : $(SOURCE)\
 $(DEP_CPP_ARRAY) "$(INTDIR)" "$(INTDIR)\RiskMon.pch"


!ENDIF 

SOURCE=.\RiskFunctions.cpp

!IF  "$(CFG)" == "RiskMon - Win32 Release"

DEP_CPP_RISKF=\
	".\Node.h"\
	".\RiskFunctions.h"\
	".\StdAfx.h"\
	".\StringLList.h"\
	

"$(INTDIR)\RiskFunctions.obj" : $(SOURCE) $(DEP_CPP_RISKF) "$(INTDIR)"\
 "$(INTDIR)\RiskMon.pch"


!ELSEIF  "$(CFG)" == "RiskMon - Win32 Debug"

DEP_CPP_RISKF=\
	".\Node.h"\
	".\RiskFunctions.h"\
	".\StringLList.h"\
	

"$(INTDIR)\RiskFunctions.obj"	"$(INTDIR)\RiskFunctions.sbr" : $(SOURCE)\
 $(DEP_CPP_RISKF) "$(INTDIR)" "$(INTDIR)\RiskMon.pch"


!ENDIF 

SOURCE=.\RiskMon.cpp

!IF  "$(CFG)" == "RiskMon - Win32 Release"

DEP_CPP_RISKM=\
	".\ArrayListLL.h"\
	".\Node.h"\
	".\RiskFunctions.h"\
	".\RiskMon.h"\
	".\StdAfx.h"\
	".\StringLList.h"\
	

"$(INTDIR)\RiskMon.obj" : $(SOURCE) $(DEP_CPP_RISKM) "$(INTDIR)"\
 "$(INTDIR)\RiskMon.pch"


!ELSEIF  "$(CFG)" == "RiskMon - Win32 Debug"

DEP_CPP_RISKM=\
	".\ArrayListLL.h"\
	".\Node.h"\
	".\RiskFunctions.h"\
	".\RiskMon.h"\
	".\StringLList.h"\
	

"$(INTDIR)\RiskMon.obj"	"$(INTDIR)\RiskMon.sbr" : $(SOURCE) $(DEP_CPP_RISKM)\
 "$(INTDIR)" "$(INTDIR)\RiskMon.pch"


!ENDIF 

SOURCE=.\RiskMon.rc
DEP_RSC_RISKMO=\
	".\res\RiskMon.rc2"\
	

"$(INTDIR)\RiskMon.res" : $(SOURCE) $(DEP_RSC_RISKMO) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "RiskMon - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_USRDLL" /Fp"$(INTDIR)\RiskMon.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\RiskMon.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RiskMon - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_WINDLL" /D "_USRDLL" /FR"$(INTDIR)\\"\
 /Fp"$(INTDIR)\RiskMon.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\RiskMon.pch" : \
$(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\StringLList.cpp

!IF  "$(CFG)" == "RiskMon - Win32 Release"

DEP_CPP_STRIN=\
	".\Node.h"\
	".\StdAfx.h"\
	".\StringLList.h"\
	

"$(INTDIR)\StringLList.obj" : $(SOURCE) $(DEP_CPP_STRIN) "$(INTDIR)"\
 "$(INTDIR)\RiskMon.pch"


!ELSEIF  "$(CFG)" == "RiskMon - Win32 Debug"

DEP_CPP_STRIN=\
	".\Node.h"\
	".\StringLList.h"\
	

"$(INTDIR)\StringLList.obj"	"$(INTDIR)\StringLList.sbr" : $(SOURCE)\
 $(DEP_CPP_STRIN) "$(INTDIR)" "$(INTDIR)\RiskMon.pch"


!ENDIF 


!ENDIF 

