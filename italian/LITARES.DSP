# Microsoft Developer Studio Project File - Name="LitaRes" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=LitaRes - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "LITARES.MAK".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "LITARES.MAK" CFG="LitaRes - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LitaRes - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "LitaRes - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "LitaRes - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\release\italian"
# PROP Intermediate_Dir "..\..\Release\italian"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x410 /i "..\mfc" /i "..\mfc\res" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386 /out:"..\..\release\italian/boblang.dll" /NOENTRY
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Copying resources
PostBuild_Cmds=copy   /y    ..\..\debug\italian\boblang.dll     ..\..\game\italian\text\ 
# End Special Build Tool

!ELSEIF  "$(CFG)" == "LitaRes - Win32 Debug"

# PROP Ignore_Export_Lib 0
# ADD CPP /W3 /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR
# ADD BASE RSC /l 0x419
# ADD RSC /l 0x410 /i "..\mfc" /i "..\mfc\res"
BSC32=bscmake.exe
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 /nologo /subsystem:windows /dll /pdb:none /debug /machine:I386 /out:"..\..\debug\italian/boblang.dll" /implib:"..\..\debug\italian/boblang.lib" /NOENTRY
# SUBTRACT LINK32 /map

!ENDIF 

# Begin Target

# Name "LitaRes - Win32 Release"
# Name "LitaRes - Win32 Debug"
# Begin Source File

SOURCE=.\arrow.cur
# End Source File
# Begin Source File

SOURCE=.\arrowcop.cur
# End Source File
# Begin Source File

SOURCE=.\Bob.rc
# End Source File
# Begin Source File

SOURCE=.\res\Grip.bmp
# End Source File
# Begin Source File

SOURCE=.\LitaRes.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\res\MIG.ico
# End Source File
# Begin Source File

SOURCE=.\res\MIGDoc.ico
# End Source File
# Begin Source File

SOURCE=.\nodrop.cur
# End Source File
# End Target
# End Project
