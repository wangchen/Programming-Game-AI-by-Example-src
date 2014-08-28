# Microsoft Developer Studio Generated NMAKE File, Based on Pathfinder.dsp
!IF "$(CFG)" == ""
CFG=Pathfinder - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Pathfinder - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Pathfinder - Win32 Release" && "$(CFG)" != "Pathfinder - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Pathfinder.mak" CFG="Pathfinder - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Pathfinder - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Pathfinder - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Pathfinder - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\Pathfinder.exe" "$(OUTDIR)\Pathfinder.bsc"


CLEAN :
	-@erase "$(INTDIR)\CController.obj"
	-@erase "$(INTDIR)\CController.sbr"
	-@erase "$(INTDIR)\Cgdi.obj"
	-@erase "$(INTDIR)\Cgdi.sbr"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\main.sbr"
	-@erase "$(INTDIR)\PrecisionTimer.obj"
	-@erase "$(INTDIR)\PrecisionTimer.sbr"
	-@erase "$(INTDIR)\toolbar.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\WindowUtils.obj"
	-@erase "$(INTDIR)\WindowUtils.sbr"
	-@erase "$(OUTDIR)\Pathfinder.bsc"
	-@erase "$(OUTDIR)\Pathfinder.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Pathfinder.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\toolbar.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Pathfinder.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\CController.sbr" \
	"$(INTDIR)\main.sbr" \
	"$(INTDIR)\Cgdi.sbr" \
	"$(INTDIR)\PrecisionTimer.sbr" \
	"$(INTDIR)\WindowUtils.sbr"

"$(OUTDIR)\Pathfinder.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\Pathfinder.pdb" /machine:I386 /out:"$(OUTDIR)\Pathfinder.exe" 
LINK32_OBJS= \
	"$(INTDIR)\CController.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\Cgdi.obj" \
	"$(INTDIR)\PrecisionTimer.obj" \
	"$(INTDIR)\WindowUtils.obj" \
	"$(INTDIR)\toolbar.res"

"$(OUTDIR)\Pathfinder.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Pathfinder - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\Pathfinder.exe" "$(OUTDIR)\Pathfinder.bsc"


CLEAN :
	-@erase "$(INTDIR)\CController.obj"
	-@erase "$(INTDIR)\CController.sbr"
	-@erase "$(INTDIR)\Cgdi.obj"
	-@erase "$(INTDIR)\Cgdi.sbr"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\main.sbr"
	-@erase "$(INTDIR)\PrecisionTimer.obj"
	-@erase "$(INTDIR)\PrecisionTimer.sbr"
	-@erase "$(INTDIR)\toolbar.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\WindowUtils.obj"
	-@erase "$(INTDIR)\WindowUtils.sbr"
	-@erase "$(OUTDIR)\Pathfinder.bsc"
	-@erase "$(OUTDIR)\Pathfinder.exe"
	-@erase "$(OUTDIR)\Pathfinder.ilk"
	-@erase "$(OUTDIR)\Pathfinder.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Pathfinder.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\toolbar.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Pathfinder.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\CController.sbr" \
	"$(INTDIR)\main.sbr" \
	"$(INTDIR)\Cgdi.sbr" \
	"$(INTDIR)\PrecisionTimer.sbr" \
	"$(INTDIR)\WindowUtils.sbr"

"$(OUTDIR)\Pathfinder.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\Pathfinder.pdb" /debug /machine:I386 /out:"$(OUTDIR)\Pathfinder.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\CController.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\Cgdi.obj" \
	"$(INTDIR)\PrecisionTimer.obj" \
	"$(INTDIR)\WindowUtils.obj" \
	"$(INTDIR)\toolbar.res"

"$(OUTDIR)\Pathfinder.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("Pathfinder.dep")
!INCLUDE "Pathfinder.dep"
!ELSE 
!MESSAGE Warning: cannot find "Pathfinder.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Pathfinder - Win32 Release" || "$(CFG)" == "Pathfinder - Win32 Debug"
SOURCE=.\CController.cpp

"$(INTDIR)\CController.obj"	"$(INTDIR)\CController.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\main.cpp

"$(INTDIR)\main.obj"	"$(INTDIR)\main.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\toolbar.rc

"$(INTDIR)\toolbar.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=..\Common\misc\Cgdi.cpp

"$(INTDIR)\Cgdi.obj"	"$(INTDIR)\Cgdi.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Common\Time\PrecisionTimer.cpp

"$(INTDIR)\PrecisionTimer.obj"	"$(INTDIR)\PrecisionTimer.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Common\misc\WindowUtils.cpp

"$(INTDIR)\WindowUtils.obj"	"$(INTDIR)\WindowUtils.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

