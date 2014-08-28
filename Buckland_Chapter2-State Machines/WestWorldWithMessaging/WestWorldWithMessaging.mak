# Microsoft Developer Studio Generated NMAKE File, Based on WestWorldWithMessaging.dsp
!IF "$(CFG)" == ""
CFG=WestWorldWithMessaging - Win32 Debug
!MESSAGE No configuration specified. Defaulting to WestWorldWithMessaging - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "WestWorldWithMessaging - Win32 Release" && "$(CFG)" != "WestWorldWithMessaging - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
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
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "WestWorldWithMessaging - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\WestWorldWithMessaging.exe" "$(OUTDIR)\WestWorldWithMessaging.bsc"


CLEAN :
	-@erase "$(INTDIR)\BaseGameEntity.obj"
	-@erase "$(INTDIR)\BaseGameEntity.sbr"
	-@erase "$(INTDIR)\CrudeTimer.obj"
	-@erase "$(INTDIR)\CrudeTimer.sbr"
	-@erase "$(INTDIR)\EntityManager.obj"
	-@erase "$(INTDIR)\EntityManager.sbr"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\main.sbr"
	-@erase "$(INTDIR)\MessageDispatcher.obj"
	-@erase "$(INTDIR)\MessageDispatcher.sbr"
	-@erase "$(INTDIR)\Miner.obj"
	-@erase "$(INTDIR)\Miner.sbr"
	-@erase "$(INTDIR)\MinerOwnedStates.obj"
	-@erase "$(INTDIR)\MinerOwnedStates.sbr"
	-@erase "$(INTDIR)\MinersWife.obj"
	-@erase "$(INTDIR)\MinersWife.sbr"
	-@erase "$(INTDIR)\MinersWifeOwnedStates.obj"
	-@erase "$(INTDIR)\MinersWifeOwnedStates.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\WestWorldWithMessaging.bsc"
	-@erase "$(OUTDIR)\WestWorldWithMessaging.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GR /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\WestWorldWithMessaging.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\WestWorldWithMessaging.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\BaseGameEntity.sbr" \
	"$(INTDIR)\EntityManager.sbr" \
	"$(INTDIR)\main.sbr" \
	"$(INTDIR)\MessageDispatcher.sbr" \
	"$(INTDIR)\MinerOwnedStates.sbr" \
	"$(INTDIR)\MinersWifeOwnedStates.sbr" \
	"$(INTDIR)\CrudeTimer.sbr" \
	"$(INTDIR)\Miner.sbr" \
	"$(INTDIR)\MinersWife.sbr"

"$(OUTDIR)\WestWorldWithMessaging.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\WestWorldWithMessaging.pdb" /machine:I386 /out:"$(OUTDIR)\WestWorldWithMessaging.exe" 
LINK32_OBJS= \
	"$(INTDIR)\BaseGameEntity.obj" \
	"$(INTDIR)\EntityManager.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\MessageDispatcher.obj" \
	"$(INTDIR)\MinerOwnedStates.obj" \
	"$(INTDIR)\MinersWifeOwnedStates.obj" \
	"$(INTDIR)\CrudeTimer.obj" \
	"$(INTDIR)\Miner.obj" \
	"$(INTDIR)\MinersWife.obj"

"$(OUTDIR)\WestWorldWithMessaging.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "WestWorldWithMessaging - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\WestWorldWithMessaging.exe" "$(OUTDIR)\WestWorldWithMessaging.bsc"


CLEAN :
	-@erase "$(INTDIR)\BaseGameEntity.obj"
	-@erase "$(INTDIR)\BaseGameEntity.sbr"
	-@erase "$(INTDIR)\CrudeTimer.obj"
	-@erase "$(INTDIR)\CrudeTimer.sbr"
	-@erase "$(INTDIR)\EntityManager.obj"
	-@erase "$(INTDIR)\EntityManager.sbr"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\main.sbr"
	-@erase "$(INTDIR)\MessageDispatcher.obj"
	-@erase "$(INTDIR)\MessageDispatcher.sbr"
	-@erase "$(INTDIR)\Miner.obj"
	-@erase "$(INTDIR)\Miner.sbr"
	-@erase "$(INTDIR)\MinerOwnedStates.obj"
	-@erase "$(INTDIR)\MinerOwnedStates.sbr"
	-@erase "$(INTDIR)\MinersWife.obj"
	-@erase "$(INTDIR)\MinersWife.sbr"
	-@erase "$(INTDIR)\MinersWifeOwnedStates.obj"
	-@erase "$(INTDIR)\MinersWifeOwnedStates.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\WestWorldWithMessaging.bsc"
	-@erase "$(OUTDIR)\WestWorldWithMessaging.exe"
	-@erase "$(OUTDIR)\WestWorldWithMessaging.ilk"
	-@erase "$(OUTDIR)\WestWorldWithMessaging.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\WestWorldWithMessaging.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\WestWorldWithMessaging.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\BaseGameEntity.sbr" \
	"$(INTDIR)\EntityManager.sbr" \
	"$(INTDIR)\main.sbr" \
	"$(INTDIR)\MessageDispatcher.sbr" \
	"$(INTDIR)\MinerOwnedStates.sbr" \
	"$(INTDIR)\MinersWifeOwnedStates.sbr" \
	"$(INTDIR)\CrudeTimer.sbr" \
	"$(INTDIR)\Miner.sbr" \
	"$(INTDIR)\MinersWife.sbr"

"$(OUTDIR)\WestWorldWithMessaging.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\WestWorldWithMessaging.pdb" /debug /machine:I386 /out:"$(OUTDIR)\WestWorldWithMessaging.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\BaseGameEntity.obj" \
	"$(INTDIR)\EntityManager.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\MessageDispatcher.obj" \
	"$(INTDIR)\MinerOwnedStates.obj" \
	"$(INTDIR)\MinersWifeOwnedStates.obj" \
	"$(INTDIR)\CrudeTimer.obj" \
	"$(INTDIR)\Miner.obj" \
	"$(INTDIR)\MinersWife.obj"

"$(OUTDIR)\WestWorldWithMessaging.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("WestWorldWithMessaging.dep")
!INCLUDE "WestWorldWithMessaging.dep"
!ELSE 
!MESSAGE Warning: cannot find "WestWorldWithMessaging.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "WestWorldWithMessaging - Win32 Release" || "$(CFG)" == "WestWorldWithMessaging - Win32 Debug"
SOURCE=.\BaseGameEntity.cpp

"$(INTDIR)\BaseGameEntity.obj"	"$(INTDIR)\BaseGameEntity.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\EntityManager.cpp

"$(INTDIR)\EntityManager.obj"	"$(INTDIR)\EntityManager.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\main.cpp

"$(INTDIR)\main.obj"	"$(INTDIR)\main.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\MessageDispatcher.cpp

"$(INTDIR)\MessageDispatcher.obj"	"$(INTDIR)\MessageDispatcher.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Miner.cpp

"$(INTDIR)\Miner.obj"	"$(INTDIR)\Miner.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\MinerOwnedStates.cpp

"$(INTDIR)\MinerOwnedStates.obj"	"$(INTDIR)\MinerOwnedStates.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\MinersWife.cpp

"$(INTDIR)\MinersWife.obj"	"$(INTDIR)\MinersWife.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\MinersWifeOwnedStates.cpp

"$(INTDIR)\MinersWifeOwnedStates.obj"	"$(INTDIR)\MinersWifeOwnedStates.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=..\..\Common\Time\CrudeTimer.cpp

"$(INTDIR)\CrudeTimer.obj"	"$(INTDIR)\CrudeTimer.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

