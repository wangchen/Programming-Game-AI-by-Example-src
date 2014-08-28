# Microsoft Developer Studio Project File - Name="WestWorldWithMessaging" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=WestWorldWithMessaging - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "WestWorldWithMessaging.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "WestWorldWithMessaging.mak" CFG="WestWorldWithMessaging - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WestWorldWithMessaging - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "WestWorldWithMessaging - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "WestWorldWithMessaging - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GR /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /FD /c
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "WestWorldWithMessaging - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "WestWorldWithMessaging - Win32 Release"
# Name "WestWorldWithMessaging - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BaseGameEntity.cpp
# End Source File
# Begin Source File

SOURCE=.\EntityManager.cpp
# End Source File
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# Begin Source File

SOURCE=.\MessageDispatcher.cpp
# End Source File
# Begin Source File

SOURCE=.\Miner.cpp
# End Source File
# Begin Source File

SOURCE=.\MinerOwnedStates.cpp
# End Source File
# Begin Source File

SOURCE=.\MinersWife.cpp
# End Source File
# Begin Source File

SOURCE=.\MinersWifeOwnedStates.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BaseGameEntity.h
# End Source File
# Begin Source File

SOURCE=.\EntityManager.h
# End Source File
# Begin Source File

SOURCE=.\EntityNames.h
# End Source File
# Begin Source File

SOURCE=.\Locations.h
# End Source File
# Begin Source File

SOURCE=.\MessageDispatcher.h
# End Source File
# Begin Source File

SOURCE=.\MessageTypes.h
# End Source File
# Begin Source File

SOURCE=.\Miner.h
# End Source File
# Begin Source File

SOURCE=.\MinerOwnedStates.h
# End Source File
# Begin Source File

SOURCE=.\MinersWife.h
# End Source File
# Begin Source File

SOURCE=.\MinersWifeOwnedStates.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\FSM\State.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\FSM\StateMachine.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\Messaging\Telegram.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "misc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Common\ConsoleUtils.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\misc\ConsoleUtils.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\Time\CrudeTimer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\Time\CrudeTimer.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\2D\SVector2D.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\misc\utils.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\utils.h
# End Source File
# End Group
# End Target
# End Project
