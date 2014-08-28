# Microsoft Developer Studio Generated NMAKE File, Based on WestWorldWithWomen.dsp
!IF "$(CFG)" == ""
CFG=WestWorldWithWomen - Win32 Debug
!MESSAGE No configuration specified. Defaulting to WestWorldWithWomen - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "WestWorldWithWomen - Win32 Release" && "$(CFG)" != "WestWorldWithWomen - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "WestWorldWithWomen.mak" CFG="WestWorldWithWomen - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WestWorldWithWomen - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "WestWorldWithWomen - Win32 Debug" (based on "Win32 (x86) Console Application")
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

!IF  "$(CFG)" == "WestWorldWithWomen - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\WestWorldWithWomen.exe"


CLEAN :
	-@erase "$(INTDIR)\BaseGameEntity.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\Miner.obj"
	-@erase "$(INTDIR)\MinerOwnedStates.obj"
	-@erase "$(INTDIR)\MinersWife.obj"
	-@erase "$(INTDIR)\MinersWifeOwnedStates.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\WestWorldWithWomen.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GR /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\WestWorldWithWomen.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\WestWorldWithWomen.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\WestWorldWithWomen.pdb" /machine:I386 /out:"$(OUTDIR)\WestWorldWithWomen.exe" 
LINK32_OBJS= \
	"$(INTDIR)\BaseGameEntity.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\Miner.obj" \
	"$(INTDIR)\MinerOwnedStates.obj" \
	"$(INTDIR)\MinersWife.obj" \
	"$(INTDIR)\MinersWifeOwnedStates.obj"

"$(OUTDIR)\WestWorldWithWomen.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "WestWorldWithWomen - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\WestWorldWithWomen.exe"


CLEAN :
	-@erase "$(INTDIR)\BaseGameEntity.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\Miner.obj"
	-@erase "$(INTDIR)\MinerOwnedStates.obj"
	-@erase "$(INTDIR)\MinersWife.obj"
	-@erase "$(INTDIR)\MinersWifeOwnedStates.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\WestWorldWithWomen.exe"
	-@erase "$(OUTDIR)\WestWorldWithWomen.ilk"
	-@erase "$(OUTDIR)\WestWorldWithWomen.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\WestWorldWithWomen.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\WestWorldWithWomen.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\WestWorldWithWomen.pdb" /debug /machine:I386 /out:"$(OUTDIR)\WestWorldWithWomen.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\BaseGameEntity.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\Miner.obj" \
	"$(INTDIR)\MinerOwnedStates.obj" \
	"$(INTDIR)\MinersWife.obj" \
	"$(INTDIR)\MinersWifeOwnedStates.obj"

"$(OUTDIR)\WestWorldWithWomen.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("WestWorldWithWomen.dep")
!INCLUDE "WestWorldWithWomen.dep"
!ELSE 
!MESSAGE Warning: cannot find "WestWorldWithWomen.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "WestWorldWithWomen - Win32 Release" || "$(CFG)" == "WestWorldWithWomen - Win32 Debug"
SOURCE=.\BaseGameEntity.cpp

"$(INTDIR)\BaseGameEntity.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\main.cpp

"$(INTDIR)\main.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Miner.cpp

"$(INTDIR)\Miner.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\MinerOwnedStates.cpp

"$(INTDIR)\MinerOwnedStates.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\MinersWife.cpp

"$(INTDIR)\MinersWife.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\MinersWifeOwnedStates.cpp

"$(INTDIR)\MinersWifeOwnedStates.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

