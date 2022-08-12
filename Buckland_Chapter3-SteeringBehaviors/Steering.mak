# Microsoft Developer Studio Generated NMAKE File, Based on Steering.dsp
!IF "$(CFG)" == ""
CFG=Steering - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Steering - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Steering - Win32 Release" && "$(CFG)" != "Steering - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Steering.mak" CFG="Steering - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Steering - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Steering - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "Steering - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\Steering.exe" "$(OUTDIR)\Steering.bsc"


CLEAN :
	-@erase "$(INTDIR)\Cgdi.obj"
	-@erase "$(INTDIR)\Cgdi.sbr"
	-@erase "$(INTDIR)\GameWorld.obj"
	-@erase "$(INTDIR)\GameWorld.sbr"
	-@erase "$(INTDIR)\iniFileLoaderBase.obj"
	-@erase "$(INTDIR)\iniFileLoaderBase.sbr"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\main.sbr"
	-@erase "$(INTDIR)\Obstacle.obj"
	-@erase "$(INTDIR)\Obstacle.sbr"
	-@erase "$(INTDIR)\ParamLoader.obj"
	-@erase "$(INTDIR)\ParamLoader.sbr"
	-@erase "$(INTDIR)\Path.obj"
	-@erase "$(INTDIR)\Path.sbr"
	-@erase "$(INTDIR)\PrecisionTimer.obj"
	-@erase "$(INTDIR)\PrecisionTimer.sbr"
	-@erase "$(INTDIR)\Script1.res"
	-@erase "$(INTDIR)\SteeringBehaviors.obj"
	-@erase "$(INTDIR)\SteeringBehaviors.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\Vehicle.obj"
	-@erase "$(INTDIR)\Vehicle.sbr"
	-@erase "$(INTDIR)\WindowUtils.obj"
	-@erase "$(INTDIR)\WindowUtils.sbr"
	-@erase "$(OUTDIR)\Steering.bsc"
	-@erase "$(OUTDIR)\Steering.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GR /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Steering.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\Script1.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Steering.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\GameWorld.sbr" \
	"$(INTDIR)\main.sbr" \
	"$(INTDIR)\SteeringBehaviors.sbr" \
	"$(INTDIR)\Vehicle.sbr" \
	"$(INTDIR)\ParamLoader.sbr" \
	"$(INTDIR)\Path.sbr" \
	"$(INTDIR)\WindowUtils.sbr" \
	"$(INTDIR)\Cgdi.sbr" \
	"$(INTDIR)\iniFileLoaderBase.sbr" \
	"$(INTDIR)\PrecisionTimer.sbr" \
	"$(INTDIR)\Obstacle.sbr"

"$(OUTDIR)\Steering.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\Steering.pdb" /machine:I386 /out:"$(OUTDIR)\Steering.exe" 
LINK32_OBJS= \
	"$(INTDIR)\GameWorld.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\SteeringBehaviors.obj" \
	"$(INTDIR)\Vehicle.obj" \
	"$(INTDIR)\ParamLoader.obj" \
	"$(INTDIR)\Path.obj" \
	"$(INTDIR)\Script1.res" \
	"$(INTDIR)\WindowUtils.obj" \
	"$(INTDIR)\Cgdi.obj" \
	"$(INTDIR)\iniFileLoaderBase.obj" \
	"$(INTDIR)\PrecisionTimer.obj" \
	"$(INTDIR)\Obstacle.obj"

"$(OUTDIR)\Steering.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Steering - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\Steering.exe" "$(OUTDIR)\Steering.bsc"


CLEAN :
	-@erase "$(INTDIR)\Cgdi.obj"
	-@erase "$(INTDIR)\Cgdi.sbr"
	-@erase "$(INTDIR)\GameWorld.obj"
	-@erase "$(INTDIR)\GameWorld.sbr"
	-@erase "$(INTDIR)\iniFileLoaderBase.obj"
	-@erase "$(INTDIR)\iniFileLoaderBase.sbr"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\main.sbr"
	-@erase "$(INTDIR)\Obstacle.obj"
	-@erase "$(INTDIR)\Obstacle.sbr"
	-@erase "$(INTDIR)\ParamLoader.obj"
	-@erase "$(INTDIR)\ParamLoader.sbr"
	-@erase "$(INTDIR)\Path.obj"
	-@erase "$(INTDIR)\Path.sbr"
	-@erase "$(INTDIR)\PrecisionTimer.obj"
	-@erase "$(INTDIR)\PrecisionTimer.sbr"
	-@erase "$(INTDIR)\Script1.res"
	-@erase "$(INTDIR)\SteeringBehaviors.obj"
	-@erase "$(INTDIR)\SteeringBehaviors.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\Vehicle.obj"
	-@erase "$(INTDIR)\Vehicle.sbr"
	-@erase "$(INTDIR)\WindowUtils.obj"
	-@erase "$(INTDIR)\WindowUtils.sbr"
	-@erase "$(OUTDIR)\Steering.bsc"
	-@erase "$(OUTDIR)\Steering.exe"
	-@erase "$(OUTDIR)\Steering.ilk"
	-@erase "$(OUTDIR)\Steering.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Steering.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\Script1.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Steering.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\GameWorld.sbr" \
	"$(INTDIR)\main.sbr" \
	"$(INTDIR)\SteeringBehaviors.sbr" \
	"$(INTDIR)\Vehicle.sbr" \
	"$(INTDIR)\ParamLoader.sbr" \
	"$(INTDIR)\Path.sbr" \
	"$(INTDIR)\WindowUtils.sbr" \
	"$(INTDIR)\Cgdi.sbr" \
	"$(INTDIR)\iniFileLoaderBase.sbr" \
	"$(INTDIR)\PrecisionTimer.sbr" \
	"$(INTDIR)\Obstacle.sbr"

"$(OUTDIR)\Steering.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\Steering.pdb" /debug /machine:I386 /out:"$(OUTDIR)\Steering.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\GameWorld.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\SteeringBehaviors.obj" \
	"$(INTDIR)\Vehicle.obj" \
	"$(INTDIR)\ParamLoader.obj" \
	"$(INTDIR)\Path.obj" \
	"$(INTDIR)\Script1.res" \
	"$(INTDIR)\WindowUtils.obj" \
	"$(INTDIR)\Cgdi.obj" \
	"$(INTDIR)\iniFileLoaderBase.obj" \
	"$(INTDIR)\PrecisionTimer.obj" \
	"$(INTDIR)\Obstacle.obj"

"$(OUTDIR)\Steering.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("Steering.dep")
!INCLUDE "Steering.dep"
!ELSE 
!MESSAGE Warning: cannot find "Steering.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Steering - Win32 Release" || "$(CFG)" == "Steering - Win32 Debug"
SOURCE=.\GameWorld.cpp

"$(INTDIR)\GameWorld.obj"	"$(INTDIR)\GameWorld.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\main.cpp

"$(INTDIR)\main.obj"	"$(INTDIR)\main.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\SteeringBehaviors.cpp

"$(INTDIR)\SteeringBehaviors.obj"	"$(INTDIR)\SteeringBehaviors.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Script1.rc

"$(INTDIR)\Script1.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=..\Common\misc\Cgdi.cpp

"$(INTDIR)\Cgdi.obj"	"$(INTDIR)\Cgdi.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Common\misc\iniFileLoaderBase.cpp

"$(INTDIR)\iniFileLoaderBase.obj"	"$(INTDIR)\iniFileLoaderBase.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Obstacle.cpp

"$(INTDIR)\Obstacle.obj"	"$(INTDIR)\Obstacle.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ParamLoader.cpp

"$(INTDIR)\ParamLoader.obj"	"$(INTDIR)\ParamLoader.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Path.cpp

"$(INTDIR)\Path.obj"	"$(INTDIR)\Path.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=..\Common\Time\PrecisionTimer.cpp

"$(INTDIR)\PrecisionTimer.obj"	"$(INTDIR)\PrecisionTimer.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Common\misc\WindowUtils.cpp

"$(INTDIR)\WindowUtils.obj"	"$(INTDIR)\WindowUtils.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Vehicle.cpp

"$(INTDIR)\Vehicle.obj"	"$(INTDIR)\Vehicle.sbr" : $(SOURCE) "$(INTDIR)"



!ENDIF 

