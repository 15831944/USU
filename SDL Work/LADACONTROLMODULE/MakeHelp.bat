@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by LADA CONTROL MODULE.HPJ. >"hlp\LADA Control Module.hm"
echo. >>"hlp\LADA Control Module.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\LADA Control Module.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\LADA Control Module.hm"
echo. >>"hlp\LADA Control Module.hm"
echo // Prompts (IDP_*) >>"hlp\LADA Control Module.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\LADA Control Module.hm"
echo. >>"hlp\LADA Control Module.hm"
echo // Resources (IDR_*) >>"hlp\LADA Control Module.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\LADA Control Module.hm"
echo. >>"hlp\LADA Control Module.hm"
echo // Dialogs (IDD_*) >>"hlp\LADA Control Module.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\LADA Control Module.hm"
echo. >>"hlp\LADA Control Module.hm"
echo // Frame Controls (IDW_*) >>"hlp\LADA Control Module.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\LADA Control Module.hm"
REM -- Make help for Project LADA CONTROL MODULE


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\LADA Control Module.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\LADA Control Module.hlp" goto :Error
if not exist "hlp\LADA Control Module.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\LADA Control Module.hlp" Debug
if exist Debug\nul copy "hlp\LADA Control Module.cnt" Debug
if exist Release\nul copy "hlp\LADA Control Module.hlp" Release
if exist Release\nul copy "hlp\LADA Control Module.cnt" Release
echo.
goto :done

:Error
echo hlp\LADA Control Module.hpj(1) : error: Problem encountered creating help file

:done
echo.
