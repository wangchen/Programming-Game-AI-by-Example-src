# Microsoft Developer Studio Generated NMAKE File, Based on SimpleSoccer.dsp
!IF "$(CFG)" == ""
CFG=SimpleSoccer - Win32 Debug
!MESSAGE No configuration specified. Defaulting to SimpleSoccer - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "SimpleSoccer - Win32 Release" && "$(CFG)" != "SimpleSoccer - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SimpleSoccer.mak" CFG="SimpleSoccer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SimpleSoccer - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SimpleSoccer - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "SimpleSoccer - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\SimpleSoccer.exe" "$(OUTDIR)\SimpleSoccer.bsc"


CLEAN :
	-@erase "$(INTDIR)\BaseGameEntity.obj"
	-@erase "$(INTDIR)\BaseGameEntity.sbr"
	-@erase "$(INTDIR)\DebugConsole.obj"
	-@erase "$(INTDIR)\DebugConsole.sbr"
	-@erase "$(INTDIR)\Cgdi.obj"
	-@erase "$(INTDIR)\Cgdi.sbr"
	-@erase "$(INTDIR)\EntityManager.obj"
	-@erase "$(INTDIR)\EntityManager.sbr"
	-@erase "$(INTDIR)\FieldPlayer.obj"
	-@erase "$(INTDIR)\FieldPlayer.sbr"
	-@erase "$(INTDIR)\FieldPlayerStates.obj"
	-@erase "$(INTDIR)\FieldPlayerStates.sbr"
	-@erase "$(INTDIR)\FrameCounter.obj"
	-@erase "$(INTDIR)\FrameCounter.sbr"
	-@erase "$(INTDIR)\Goalkeeper.obj"
	-@erase "$(INTDIR)\Goalkeeper.sbr"
	-@erase "$(INTDIR)\GoalKeeperStates.obj"
	-@erase "$(INTDIR)\GoalKeeperStates.sbr"
	-@erase "$(INTDIR)\iniFileLoaderBase.obj"
	-@erase "$(INTDIR)\iniFileLoaderBase.sbr"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\main.sbr"
	-@erase "$(INTDIR)\MessageDispatcher.obj"
	-@erase "$(INTDIR)\MessageDispatcher.sbr"
	-@erase "$(INTDIR)\ParamLoader.obj"
	-@erase "$(INTDIR)\ParamLoader.sbr"
	-@erase "$(INTDIR)\PlayerBase.obj"
	-@erase "$(INTDIR)\PlayerBase.sbr"
	-@erase "$(INTDIR)\PrecisionTimer.obj"
	-@erase "$(INTDIR)\PrecisionTimer.sbr"
	-@erase "$(INTDIR)\Script1.res"
	-@erase "$(INTDIR)\SoccerBall.obj"
	-@erase "$(INTDIR)\SoccerBall.sbr"
	-@erase "$(INTDIR)\SoccerPitch.obj"
	-@erase "$(INTDIR)\SoccerPitch.sbr"
	-@erase "$(INTDIR)\SoccerTeam.obj"
	-@erase "$(INTDIR)\SoccerTeam.sbr"
	-@erase "$(INTDIR)\SteeringBehaviors.obj"
	-@erase "$(INTDIR)\SteeringBehaviors.sbr"
	-@erase "$(INTDIR)\SupportSpotCalculator.obj"
	-@erase "$(INTDIR)\SupportSpotCalculator.sbr"
	-@erase "$(INTDIR)\TeamStates.obj"
	-@erase "$(INTDIR)\TeamStates.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\WindowUtils.obj"
	-@erase "$(INTDIR)\WindowUtils.sbr"
	-@erase "$(OUTDIR)\SimpleSoccer.bsc"
	-@erase "$(OUTDIR)\SimpleSoccer.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GR /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\SimpleSoccer.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\Script1.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SimpleSoccer.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\main.sbr" \
	"$(INTDIR)\ParamLoader.sbr" \
	"$(INTDIR)\SoccerPitch.sbr" \
	"$(INTDIR)\SoccerTeam.sbr" \
	"$(INTDIR)\SteeringBehaviors.sbr" \
	"$(INTDIR)\SupportSpotCalculator.sbr" \
	"$(INTDIR)\FieldPlayerStates.sbr" \
	"$(INTDIR)\GoalKeeperStates.sbr" \
	"$(INTDIR)\TeamStates.sbr" \
	"$(INTDIR)\MessageDispatcher.sbr" \
	"$(INTDIR)\BaseGameEntity.sbr" \
	"$(INTDIR)\EntityManager.sbr" \
	"$(INTDIR)\FieldPlayer.sbr" \
	"$(INTDIR)\Goalkeeper.sbr" \
	"$(INTDIR)\PlayerBase.sbr" \
	"$(INTDIR)\SoccerBall.sbr" \
	"$(INTDIR)\DebugConsole.sbr" \
	"$(INTDIR)\Cgdi.sbr" \
	"$(INTDIR)\FrameCounter.sbr" \
	"$(INTDIR)\iniFileLoaderBase.sbr" \
	"$(INTDIR)\PrecisionTimer.sbr" \
	"$(INTDIR)\WindowUtils.sbr"

"$(OUTDIR)\SimpleSoccer.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\SimpleSoccer.pdb" /machine:I386 /out:"$(OUTDIR)\SimpleSoccer.exe" 
LINK32_OBJS= \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\ParamLoader.obj" \
	"$(INTDIR)\SoccerPitch.obj" \
	"$(INTDIR)\SoccerTeam.obj" \
	"$(INTDIR)\SteeringBehaviors.obj" \
	"$(INTDIR)\SupportSpotCalculator.obj" \
	"$(INTDIR)\FieldPlayerStates.obj" \
	"$(INTDIR)\GoalKeeperStates.obj" \
	"$(INTDIR)\TeamStates.obj" \
	"$(INTDIR)\MessageDispatcher.obj" \
	"$(INTDIR)\BaseGameEntity.obj" \
	"$(INTDIR)\EntityManager.obj" \
	"$(INTDIR)\FieldPlayer.obj" \
	"$(INTDIR)\Goalkeeper.obj" \
	"$(INTDIR)\PlayerBase.obj" \
	"$(INTDIR)\SoccerBall.obj" \
	"$(INTDIR)\DebugConsole.obj" \
	"$(INTDIR)\Cgdi.obj" \
	"$(INTDIR)\FrameCounter.obj" \
	"$(INTDIR)\iniFileLoaderBase.obj" \
	"$(INTDIR)\PrecisionTimer.obj" \
	"$(INTDIR)\WindowUtils.obj" \
	"$(INTDIR)\Script1.res"

"$(OUTDIR)\SimpleSoccer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SimpleSoccer - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\SimpleSoccer.exe" "$(OUTDIR)\SimpleSoccer.bsc"


CLEAN :
	-@erase "$(INTDIR)\BaseGameEntity.obj"
	-@erase "$(INTDIR)\BaseGameEntity.sbr"
	-@erase "$(INTDIR)\DebugConsole.obj"
	-@erase "$(INTDIR)\DebugConsole.sbr"
	-@erase "$(INTDIR)\Cgdi.obj"
	-@erase "$(INTDIR)\Cgdi.sbr"
	-@erase "$(INTDIR)\EntityManager.obj"
	-@erase "$(INTDIR)\EntityManager.sbr"
	-@erase "$(INTDIR)\FieldPlayer.obj"
	-@erase "$(INTDIR)\FieldPlayer.sbr"
	-@erase "$(INTDIR)\FieldPlayerStates.obj"
	-@erase "$(INTDIR)\FieldPlayerStates.sbr"
	-@erase "$(INTDIR)\FrameCounter.obj"
	-@erase "$(INTDIR)\FrameCounter.sbr"
	-@erase "$(INTDIR)\Goalkeeper.obj"
	-@erase "$(INTDIR)\Goalkeeper.sbr"
	-@erase "$(INTDIR)\GoalKeeperStates.obj"
	-@erase "$(INTDIR)\GoalKeeperStates.sbr"
	-@erase "$(INTDIR)\iniFileLoaderBase.obj"
	-@erase "$(INTDIR)\iniFileLoaderBase.sbr"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\main.sbr"
	-@erase "$(INTDIR)\MessageDispatcher.obj"
	-@erase "$(INTDIR)\MessageDispatcher.sbr"
	-@erase "$(INTDIR)\ParamLoader.obj"
	-@erase "$(INTDIR)\ParamLoader.sbr"
	-@erase "$(INTDIR)\PlayerBase.obj"
	-@erase "$(INTDIR)\PlayerBase.sbr"
	-@erase "$(INTDIR)\PrecisionTimer.obj"
	-@erase "$(INTDIR)\PrecisionTimer.sbr"
	-@erase "$(INTDIR)\Script1.res"
	-@erase "$(INTDIR)\SoccerBall.obj"
	-@erase "$(INTDIR)\SoccerBall.sbr"
	-@erase "$(INTDIR)\SoccerPitch.obj"
	-@erase "$(INTDIR)\SoccerPitch.sbr"
	-@erase "$(INTDIR)\SoccerTeam.obj"
	-@erase "$(INTDIR)\SoccerTeam.sbr"
	-@erase "$(INTDIR)\SteeringBehaviors.obj"
	-@erase "$(INTDIR)\SteeringBehaviors.sbr"
	-@erase "$(INTDIR)\SupportSpotCalculator.obj"
	-@erase "$(INTDIR)\SupportSpotCalculator.sbr"
	-@erase "$(INTDIR)\TeamStates.obj"
	-@erase "$(INTDIR)\TeamStates.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\WindowUtils.obj"
	-@erase "$(INTDIR)\WindowUtils.sbr"
	-@erase "$(OUTDIR)\SimpleSoccer.bsc"
	-@erase "$(OUTDIR)\SimpleSoccer.exe"
	-@erase "$(OUTDIR)\SimpleSoccer.ilk"
	-@erase "$(OUTDIR)\SimpleSoccer.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\SimpleSoccer.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\Script1.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SimpleSoccer.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\main.sbr" \
	"$(INTDIR)\ParamLoader.sbr" \
	"$(INTDIR)\SoccerPitch.sbr" \
	"$(INTDIR)\SoccerTeam.sbr" \
	"$(INTDIR)\SteeringBehaviors.sbr" \
	"$(INTDIR)\SupportSpotCalculator.sbr" \
	"$(INTDIR)\FieldPlayerStates.sbr" \
	"$(INTDIR)\GoalKeeperStates.sbr" \
	"$(INTDIR)\TeamStates.sbr" \
	"$(INTDIR)\MessageDispatcher.sbr" \
	"$(INTDIR)\BaseGameEntity.sbr" \
	"$(INTDIR)\EntityManager.sbr" \
	"$(INTDIR)\FieldPlayer.sbr" \
	"$(INTDIR)\Goalkeeper.sbr" \
	"$(INTDIR)\PlayerBase.sbr" \
	"$(INTDIR)\SoccerBall.sbr" \
	"$(INTDIR)\DebugConsole.sbr" \
	"$(INTDIR)\Cgdi.sbr" \
	"$(INTDIR)\FrameCounter.sbr" \
	"$(INTDIR)\iniFileLoaderBase.sbr" \
	"$(INTDIR)\PrecisionTimer.sbr" \
	"$(INTDIR)\WindowUtils.sbr"

"$(OUTDIR)\SimpleSoccer.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\SimpleSoccer.pdb" /debug /machine:I386 /out:"$(OUTDIR)\SimpleSoccer.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\ParamLoader.obj" \
	"$(INTDIR)\SoccerPitch.obj" \
	"$(INTDIR)\SoccerTeam.obj" \
	"$(INTDIR)\SteeringBehaviors.obj" \
	"$(INTDIR)\SupportSpotCalculator.obj" \
	"$(INTDIR)\FieldPlayerStates.obj" \
	"$(INTDIR)\GoalKeeperStates.obj" \
	"$(INTDIR)\TeamStates.obj" \
	"$(INTDIR)\MessageDispatcher.obj" \
	"$(INTDIR)\BaseGameEntity.obj" \
	"$(INTDIR)\EntityManager.obj" \
	"$(INTDIR)\FieldPlayer.obj" \
	"$(INTDIR)\Goalkeeper.obj" \
	"$(INTDIR)\PlayerBase.obj" \
	"$(INTDIR)\SoccerBall.obj" \
	"$(INTDIR)\DebugConsole.obj" \
	"$(INTDIR)\Cgdi.obj" \
	"$(INTDIR)\FrameCounter.obj" \
	"$(INTDIR)\iniFileLoaderBase.obj" \
	"$(INTDIR)\PrecisionTimer.obj" \
	"$(INTDIR)\WindowUtils.obj" \
	"$(INTDIR)\Script1.res"

"$(OUTDIR)\SimpleSoccer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("SimpleSoccer.dep")
!INCLUDE "SimpleSoccer.dep"
!ELSE 
!MESSAGE Warning: cannot find "SimpleSoccer.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "SimpleSoccer - Win32 Release" || "$(CFG)" == "SimpleSoccer - Win32 Debug"
SOURCE=.\main.cpp

"$(INTDIR)\main.obj"	"$(INTDIR)\main.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ParamLoader.cpp

"$(INTDIR)\ParamLoader.obj"	"$(INTDIR)\ParamLoader.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\SoccerPitch.cpp

"$(INTDIR)\SoccerPitch.obj"	"$(INTDIR)\SoccerPitch.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\SoccerTeam.cpp

"$(INTDIR)\SoccerTeam.obj"	"$(INTDIR)\SoccerTeam.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\SteeringBehaviors.cpp

"$(INTDIR)\SteeringBehaviors.obj"	"$(INTDIR)\SteeringBehaviors.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\SupportSpotCalculator.cpp

"$(INTDIR)\SupportSpotCalculator.obj"	"$(INTDIR)\SupportSpotCalculator.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Script1.rc

"$(INTDIR)\Script1.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\FieldPlayerStates.cpp

"$(INTDIR)\FieldPlayerStates.obj"	"$(INTDIR)\FieldPlayerStates.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\GoalKeeperStates.cpp

"$(INTDIR)\GoalKeeperStates.obj"	"$(INTDIR)\GoalKeeperStates.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\TeamStates.cpp

"$(INTDIR)\TeamStates.obj"	"$(INTDIR)\TeamStates.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=..\Common\AI\MessageDispatcher.cpp

"$(INTDIR)\MessageDispatcher.obj"	"$(INTDIR)\MessageDispatcher.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Common\Game\BaseGameEntity.cpp

"$(INTDIR)\BaseGameEntity.obj"	"$(INTDIR)\BaseGameEntity.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Common\Game\EntityManager.cpp

"$(INTDIR)\EntityManager.obj"	"$(INTDIR)\EntityManager.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\FieldPlayer.cpp

"$(INTDIR)\FieldPlayer.obj"	"$(INTDIR)\FieldPlayer.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Goalkeeper.cpp

"$(INTDIR)\Goalkeeper.obj"	"$(INTDIR)\Goalkeeper.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\PlayerBase.cpp

"$(INTDIR)\PlayerBase.obj"	"$(INTDIR)\PlayerBase.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\SoccerBall.cpp

"$(INTDIR)\SoccerBall.obj"	"$(INTDIR)\SoccerBall.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=..\Common\Debug\DebugConsole.cpp

"$(INTDIR)\DebugConsole.obj"	"$(INTDIR)\DebugConsole.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Common\misc\Cgdi.cpp

"$(INTDIR)\Cgdi.obj"	"$(INTDIR)\Cgdi.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Common\misc\FrameCounter.cpp

"$(INTDIR)\FrameCounter.obj"	"$(INTDIR)\FrameCounter.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Common\misc\iniFileLoaderBase.cpp

"$(INTDIR)\iniFileLoaderBase.obj"	"$(INTDIR)\iniFileLoaderBase.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Common\Time\PrecisionTimer.cpp

"$(INTDIR)\PrecisionTimer.obj"	"$(INTDIR)\PrecisionTimer.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Common\misc\WindowUtils.cpp

"$(INTDIR)\WindowUtils.obj"	"$(INTDIR)\WindowUtils.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

