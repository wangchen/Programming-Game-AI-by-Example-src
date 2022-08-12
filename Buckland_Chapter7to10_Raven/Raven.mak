# Microsoft Developer Studio Generated NMAKE File, Based on Raven.dsp
!IF "$(CFG)" == ""
CFG=Raven - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Raven - Win32 Debug.
!ENDIF

!IF "$(CFG)" != "Raven - Win32 Release" && "$(CFG)" != "Raven - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE
!MESSAGE NMAKE /f "Raven.mak" CFG="Raven - Win32 Debug"
!MESSAGE
!MESSAGE Possible choices for configuration are:
!MESSAGE
!MESSAGE "Raven - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Raven - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "Raven - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\Raven.exe" "$(OUTDIR)\Raven.bsc"


CLEAN :
	-@erase "$(INTDIR)\BaseGameEntity.obj"
	-@erase "$(INTDIR)\BaseGameEntity.sbr"
	-@erase "$(INTDIR)\DebugConsole.obj"
	-@erase "$(INTDIR)\DebugConsole.sbr"
	-@erase "$(INTDIR)\Cgdi.obj"
	-@erase "$(INTDIR)\Cgdi.sbr"
	-@erase "$(INTDIR)\CrudeTimer.obj"
	-@erase "$(INTDIR)\CrudeTimer.sbr"
	-@erase "$(INTDIR)\EntityManager.obj"
	-@erase "$(INTDIR)\EntityManager.sbr"
	-@erase "$(INTDIR)\ExploreGoal_Evaluator.obj"
	-@erase "$(INTDIR)\ExploreGoal_Evaluator.sbr"
	-@erase "$(INTDIR)\FrameCounter.obj"
	-@erase "$(INTDIR)\FrameCounter.sbr"
	-@erase "$(INTDIR)\FuzzyModule.obj"
	-@erase "$(INTDIR)\FuzzyModule.sbr"
	-@erase "$(INTDIR)\FuzzyOperators.obj"
	-@erase "$(INTDIR)\FuzzyOperators.sbr"
	-@erase "$(INTDIR)\FuzzySet_LeftShoulder.obj"
	-@erase "$(INTDIR)\FuzzySet_LeftShoulder.sbr"
	-@erase "$(INTDIR)\FuzzySet_RightShoulder.obj"
	-@erase "$(INTDIR)\FuzzySet_RightShoulder.sbr"
	-@erase "$(INTDIR)\FuzzySet_Singleton.obj"
	-@erase "$(INTDIR)\FuzzySet_Singleton.sbr"
	-@erase "$(INTDIR)\FuzzySet_Triangle.obj"
	-@erase "$(INTDIR)\FuzzySet_Triangle.sbr"
	-@erase "$(INTDIR)\FuzzyVariable.obj"
	-@erase "$(INTDIR)\FuzzyVariable.sbr"
	-@erase "$(INTDIR)\GetHealthGoal_Evaluator.obj"
	-@erase "$(INTDIR)\GetHealthGoal_Evaluator.sbr"
	-@erase "$(INTDIR)\GetWeaponGoal_Evaluator.obj"
	-@erase "$(INTDIR)\GetWeaponGoal_Evaluator.sbr"
	-@erase "$(INTDIR)\Goal_Explore.obj"
	-@erase "$(INTDIR)\Goal_Explore.sbr"
	-@erase "$(INTDIR)\Goal_FollowPath.obj"
	-@erase "$(INTDIR)\Goal_FollowPath.sbr"
	-@erase "$(INTDIR)\Goal_GetItem.obj"
	-@erase "$(INTDIR)\Goal_GetItem.sbr"
	-@erase "$(INTDIR)\Goal_MoveToPosition.obj"
	-@erase "$(INTDIR)\Goal_MoveToPosition.sbr"
	-@erase "$(INTDIR)\Goal_NegotiateDoor.obj"
	-@erase "$(INTDIR)\Goal_NegotiateDoor.sbr"
	-@erase "$(INTDIR)\Goal_SeekToPosition.obj"
	-@erase "$(INTDIR)\Goal_SeekToPosition.sbr"
	-@erase "$(INTDIR)\Goal_TraverseEdge.obj"
	-@erase "$(INTDIR)\Goal_TraverseEdge.sbr"
	-@erase "$(INTDIR)\Goal_Wander.obj"
	-@erase "$(INTDIR)\Goal_Wander.sbr"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\main.sbr"
	-@erase "$(INTDIR)\MessageDispatcher.obj"
	-@erase "$(INTDIR)\MessageDispatcher.sbr"
	-@erase "$(INTDIR)\Obstacle.obj"
	-@erase "$(INTDIR)\Obstacle.sbr"
	-@erase "$(INTDIR)\PrecisionTimer.obj"
	-@erase "$(INTDIR)\PrecisionTimer.sbr"
	-@erase "$(INTDIR)\Projectile_Rocket.obj"
	-@erase "$(INTDIR)\Projectile_Rocket.sbr"
	-@erase "$(INTDIR)\Projectile_Shell.obj"
	-@erase "$(INTDIR)\Projectile_Shell.sbr"
	-@erase "$(INTDIR)\Projectile_Slug.obj"
	-@erase "$(INTDIR)\Projectile_Slug.sbr"
	-@erase "$(INTDIR)\Raven_Bot.obj"
	-@erase "$(INTDIR)\Raven_Bot.sbr"
	-@erase "$(INTDIR)\Raven_Door.obj"
	-@erase "$(INTDIR)\Raven_Door.sbr"
	-@erase "$(INTDIR)\Raven_Game.obj"
	-@erase "$(INTDIR)\Raven_Game.sbr"
	-@erase "$(INTDIR)\Raven_Goal_Types.obj"
	-@erase "$(INTDIR)\Raven_Goal_Types.sbr"
	-@erase "$(INTDIR)\Raven_GoalArbitrator.obj"
	-@erase "$(INTDIR)\Raven_GoalArbitrator.sbr"
	-@erase "$(INTDIR)\Raven_GoalQ.obj"
	-@erase "$(INTDIR)\Raven_GoalQ.sbr"
	-@erase "$(INTDIR)\Raven_Map.obj"
	-@erase "$(INTDIR)\Raven_Map.sbr"
	-@erase "$(INTDIR)\Raven_PathPlanner.obj"
	-@erase "$(INTDIR)\Raven_PathPlanner.sbr"
	-@erase "$(INTDIR)\Raven_Scriptor.obj"
	-@erase "$(INTDIR)\Raven_Scriptor.sbr"
	-@erase "$(INTDIR)\Raven_SteeringBehaviors.obj"
	-@erase "$(INTDIR)\Raven_SteeringBehaviors.sbr"
	-@erase "$(INTDIR)\Raven_TargetingSystem.obj"
	-@erase "$(INTDIR)\Raven_TargetingSystem.sbr"
	-@erase "$(INTDIR)\Raven_UserOptions.obj"
	-@erase "$(INTDIR)\Raven_UserOptions.sbr"
	-@erase "$(INTDIR)\Raven_Weapon.obj"
	-@erase "$(INTDIR)\Raven_Weapon.sbr"
	-@erase "$(INTDIR)\Script1.res"
	-@erase "$(INTDIR)\Trigger_HealthGiver.obj"
	-@erase "$(INTDIR)\Trigger_HealthGiver.sbr"
	-@erase "$(INTDIR)\Trigger_WeaponGiver.obj"
	-@erase "$(INTDIR)\Trigger_WeaponGiver.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\Weapon_Knife.obj"
	-@erase "$(INTDIR)\Weapon_Knife.sbr"
	-@erase "$(INTDIR)\Weapon_RailGun.obj"
	-@erase "$(INTDIR)\Weapon_RailGun.sbr"
	-@erase "$(INTDIR)\Weapon_RocketLauncher.obj"
	-@erase "$(INTDIR)\Weapon_RocketLauncher.sbr"
	-@erase "$(INTDIR)\Weapon_ShotGun.obj"
	-@erase "$(INTDIR)\Weapon_ShotGun.sbr"
	-@erase "$(INTDIR)\WindowUtils.obj"
	-@erase "$(INTDIR)\WindowUtils.sbr"
	-@erase "$(OUTDIR)\Raven.bsc"
	-@erase "$(OUTDIR)\Raven.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Raven.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /Zm200 /c
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\Script1.res" /d "NDEBUG"
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Raven.bsc"
BSC32_SBRS= \
	"$(INTDIR)\main.sbr" \
	"$(INTDIR)\Raven_Game.sbr" \
	"$(INTDIR)\Raven_Map.sbr" \
	"$(INTDIR)\Raven_UserOptions.sbr" \
	"$(INTDIR)\Projectile_Rocket.sbr" \
	"$(INTDIR)\Projectile_Shell.sbr" \
	"$(INTDIR)\Projectile_Slug.sbr" \
	"$(INTDIR)\Raven_Weapon.sbr" \
	"$(INTDIR)\Weapon_Knife.sbr" \
	"$(INTDIR)\Weapon_RailGun.sbr" \
	"$(INTDIR)\Weapon_RocketLauncher.sbr" \
	"$(INTDIR)\Weapon_ShotGun.sbr" \
	"$(INTDIR)\BaseGameEntity.sbr" \
	"$(INTDIR)\EntityManager.sbr" \
	"$(INTDIR)\Raven_Bot.sbr" \
	"$(INTDIR)\Raven_Door.sbr" \
	"$(INTDIR)\Goal_Explore.sbr" \
	"$(INTDIR)\Goal_FollowPath.sbr" \
	"$(INTDIR)\Goal_GetItem.sbr" \
	"$(INTDIR)\Goal_MoveToPosition.sbr" \
	"$(INTDIR)\Goal_NegotiateDoor.sbr" \
	"$(INTDIR)\Goal_SeekToPosition.sbr" \
	"$(INTDIR)\Goal_TraverseEdge.sbr" \
	"$(INTDIR)\Goal_Wander.sbr" \
	"$(INTDIR)\ExploreGoal_Evaluator.sbr" \
	"$(INTDIR)\GetHealthGoal_Evaluator.sbr" \
	"$(INTDIR)\GetWeaponGoal_Evaluator.sbr" \
	"$(INTDIR)\Raven_GoalArbitrator.sbr" \
	"$(INTDIR)\Raven_Goal_Types.sbr" \
	"$(INTDIR)\Raven_GoalQ.sbr" \
	"$(INTDIR)\FuzzySet_LeftShoulder.sbr" \
	"$(INTDIR)\FuzzySet_RightShoulder.sbr" \
	"$(INTDIR)\FuzzySet_Singleton.sbr" \
	"$(INTDIR)\FuzzySet_Triangle.sbr" \
	"$(INTDIR)\FuzzyModule.sbr" \
	"$(INTDIR)\FuzzyOperators.sbr" \
	"$(INTDIR)\FuzzyVariable.sbr" \
	"$(INTDIR)\Raven_PathPlanner.sbr" \
	"$(INTDIR)\Raven_SteeringBehaviors.sbr" \
	"$(INTDIR)\MessageDispatcher.sbr" \
	"$(INTDIR)\Raven_TargetingSystem.sbr" \
	"$(INTDIR)\Trigger_HealthGiver.sbr" \
	"$(INTDIR)\Trigger_WeaponGiver.sbr" \
	"$(INTDIR)\Raven_Scriptor.sbr" \
	"$(INTDIR)\DebugConsole.sbr" \
	"$(INTDIR)\Cgdi.sbr" \
	"$(INTDIR)\CrudeTimer.sbr" \
	"$(INTDIR)\FrameCounter.sbr" \
	"$(INTDIR)\Obstacle.sbr" \
	"$(INTDIR)\PrecisionTimer.sbr" \
	"$(INTDIR)\WindowUtils.sbr"

"$(OUTDIR)\Raven.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\Raven.pdb" /machine:I386 /nodefaultlib:"libcmt" /out:"$(OUTDIR)\Raven.exe"
LINK32_OBJS= \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\Raven_Game.obj" \
	"$(INTDIR)\Raven_Map.obj" \
	"$(INTDIR)\Raven_UserOptions.obj" \
	"$(INTDIR)\Projectile_Rocket.obj" \
	"$(INTDIR)\Projectile_Shell.obj" \
	"$(INTDIR)\Projectile_Slug.obj" \
	"$(INTDIR)\Raven_Weapon.obj" \
	"$(INTDIR)\Weapon_Knife.obj" \
	"$(INTDIR)\Weapon_RailGun.obj" \
	"$(INTDIR)\Weapon_RocketLauncher.obj" \
	"$(INTDIR)\Weapon_ShotGun.obj" \
	"$(INTDIR)\BaseGameEntity.obj" \
	"$(INTDIR)\EntityManager.obj" \
	"$(INTDIR)\Raven_Bot.obj" \
	"$(INTDIR)\Raven_Door.obj" \
	"$(INTDIR)\Goal_Explore.obj" \
	"$(INTDIR)\Goal_FollowPath.obj" \
	"$(INTDIR)\Goal_GetItem.obj" \
	"$(INTDIR)\Goal_MoveToPosition.obj" \
	"$(INTDIR)\Goal_NegotiateDoor.obj" \
	"$(INTDIR)\Goal_SeekToPosition.obj" \
	"$(INTDIR)\Goal_TraverseEdge.obj" \
	"$(INTDIR)\Goal_Wander.obj" \
	"$(INTDIR)\ExploreGoal_Evaluator.obj" \
	"$(INTDIR)\GetHealthGoal_Evaluator.obj" \
	"$(INTDIR)\GetWeaponGoal_Evaluator.obj" \
	"$(INTDIR)\Raven_GoalArbitrator.obj" \
	"$(INTDIR)\Raven_Goal_Types.obj" \
	"$(INTDIR)\Raven_GoalQ.obj" \
	"$(INTDIR)\FuzzySet_LeftShoulder.obj" \
	"$(INTDIR)\FuzzySet_RightShoulder.obj" \
	"$(INTDIR)\FuzzySet_Singleton.obj" \
	"$(INTDIR)\FuzzySet_Triangle.obj" \
	"$(INTDIR)\FuzzyModule.obj" \
	"$(INTDIR)\FuzzyOperators.obj" \
	"$(INTDIR)\FuzzyVariable.obj" \
	"$(INTDIR)\Raven_PathPlanner.obj" \
	"$(INTDIR)\Raven_SteeringBehaviors.obj" \
	"$(INTDIR)\MessageDispatcher.obj" \
	"$(INTDIR)\Raven_TargetingSystem.obj" \
	"$(INTDIR)\Trigger_HealthGiver.obj" \
	"$(INTDIR)\Trigger_WeaponGiver.obj" \
	"$(INTDIR)\Raven_Scriptor.obj" \
	"$(INTDIR)\DebugConsole.obj" \
	"$(INTDIR)\Cgdi.obj" \
	"$(INTDIR)\CrudeTimer.obj" \
	"$(INTDIR)\FrameCounter.obj" \
	"$(INTDIR)\Obstacle.obj" \
	"$(INTDIR)\PrecisionTimer.obj" \
	"$(INTDIR)\WindowUtils.obj" \
	"$(INTDIR)\Script1.res"

"$(OUTDIR)\Raven.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Raven - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\Raven.exe" "$(OUTDIR)\Raven.bsc"


CLEAN :
	-@erase "$(INTDIR)\BaseGameEntity.obj"
	-@erase "$(INTDIR)\BaseGameEntity.sbr"
	-@erase "$(INTDIR)\DebugConsole.obj"
	-@erase "$(INTDIR)\DebugConsole.sbr"
	-@erase "$(INTDIR)\Cgdi.obj"
	-@erase "$(INTDIR)\Cgdi.sbr"
	-@erase "$(INTDIR)\CrudeTimer.obj"
	-@erase "$(INTDIR)\CrudeTimer.sbr"
	-@erase "$(INTDIR)\EntityManager.obj"
	-@erase "$(INTDIR)\EntityManager.sbr"
	-@erase "$(INTDIR)\ExploreGoal_Evaluator.obj"
	-@erase "$(INTDIR)\ExploreGoal_Evaluator.sbr"
	-@erase "$(INTDIR)\FrameCounter.obj"
	-@erase "$(INTDIR)\FrameCounter.sbr"
	-@erase "$(INTDIR)\FuzzyModule.obj"
	-@erase "$(INTDIR)\FuzzyModule.sbr"
	-@erase "$(INTDIR)\FuzzyOperators.obj"
	-@erase "$(INTDIR)\FuzzyOperators.sbr"
	-@erase "$(INTDIR)\FuzzySet_LeftShoulder.obj"
	-@erase "$(INTDIR)\FuzzySet_LeftShoulder.sbr"
	-@erase "$(INTDIR)\FuzzySet_RightShoulder.obj"
	-@erase "$(INTDIR)\FuzzySet_RightShoulder.sbr"
	-@erase "$(INTDIR)\FuzzySet_Singleton.obj"
	-@erase "$(INTDIR)\FuzzySet_Singleton.sbr"
	-@erase "$(INTDIR)\FuzzySet_Triangle.obj"
	-@erase "$(INTDIR)\FuzzySet_Triangle.sbr"
	-@erase "$(INTDIR)\FuzzyVariable.obj"
	-@erase "$(INTDIR)\FuzzyVariable.sbr"
	-@erase "$(INTDIR)\GetHealthGoal_Evaluator.obj"
	-@erase "$(INTDIR)\GetHealthGoal_Evaluator.sbr"
	-@erase "$(INTDIR)\GetWeaponGoal_Evaluator.obj"
	-@erase "$(INTDIR)\GetWeaponGoal_Evaluator.sbr"
	-@erase "$(INTDIR)\Goal_Explore.obj"
	-@erase "$(INTDIR)\Goal_Explore.sbr"
	-@erase "$(INTDIR)\Goal_FollowPath.obj"
	-@erase "$(INTDIR)\Goal_FollowPath.sbr"
	-@erase "$(INTDIR)\Goal_GetItem.obj"
	-@erase "$(INTDIR)\Goal_GetItem.sbr"
	-@erase "$(INTDIR)\Goal_MoveToPosition.obj"
	-@erase "$(INTDIR)\Goal_MoveToPosition.sbr"
	-@erase "$(INTDIR)\Goal_NegotiateDoor.obj"
	-@erase "$(INTDIR)\Goal_NegotiateDoor.sbr"
	-@erase "$(INTDIR)\Goal_SeekToPosition.obj"
	-@erase "$(INTDIR)\Goal_SeekToPosition.sbr"
	-@erase "$(INTDIR)\Goal_TraverseEdge.obj"
	-@erase "$(INTDIR)\Goal_TraverseEdge.sbr"
	-@erase "$(INTDIR)\Goal_Wander.obj"
	-@erase "$(INTDIR)\Goal_Wander.sbr"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\main.sbr"
	-@erase "$(INTDIR)\MessageDispatcher.obj"
	-@erase "$(INTDIR)\MessageDispatcher.sbr"
	-@erase "$(INTDIR)\Obstacle.obj"
	-@erase "$(INTDIR)\Obstacle.sbr"
	-@erase "$(INTDIR)\PrecisionTimer.obj"
	-@erase "$(INTDIR)\PrecisionTimer.sbr"
	-@erase "$(INTDIR)\Projectile_Rocket.obj"
	-@erase "$(INTDIR)\Projectile_Rocket.sbr"
	-@erase "$(INTDIR)\Projectile_Shell.obj"
	-@erase "$(INTDIR)\Projectile_Shell.sbr"
	-@erase "$(INTDIR)\Projectile_Slug.obj"
	-@erase "$(INTDIR)\Projectile_Slug.sbr"
	-@erase "$(INTDIR)\Raven_Bot.obj"
	-@erase "$(INTDIR)\Raven_Bot.sbr"
	-@erase "$(INTDIR)\Raven_Door.obj"
	-@erase "$(INTDIR)\Raven_Door.sbr"
	-@erase "$(INTDIR)\Raven_Game.obj"
	-@erase "$(INTDIR)\Raven_Game.sbr"
	-@erase "$(INTDIR)\Raven_Goal_Types.obj"
	-@erase "$(INTDIR)\Raven_Goal_Types.sbr"
	-@erase "$(INTDIR)\Raven_GoalArbitrator.obj"
	-@erase "$(INTDIR)\Raven_GoalArbitrator.sbr"
	-@erase "$(INTDIR)\Raven_GoalQ.obj"
	-@erase "$(INTDIR)\Raven_GoalQ.sbr"
	-@erase "$(INTDIR)\Raven_Map.obj"
	-@erase "$(INTDIR)\Raven_Map.sbr"
	-@erase "$(INTDIR)\Raven_PathPlanner.obj"
	-@erase "$(INTDIR)\Raven_PathPlanner.sbr"
	-@erase "$(INTDIR)\Raven_Scriptor.obj"
	-@erase "$(INTDIR)\Raven_Scriptor.sbr"
	-@erase "$(INTDIR)\Raven_SteeringBehaviors.obj"
	-@erase "$(INTDIR)\Raven_SteeringBehaviors.sbr"
	-@erase "$(INTDIR)\Raven_TargetingSystem.obj"
	-@erase "$(INTDIR)\Raven_TargetingSystem.sbr"
	-@erase "$(INTDIR)\Raven_UserOptions.obj"
	-@erase "$(INTDIR)\Raven_UserOptions.sbr"
	-@erase "$(INTDIR)\Raven_Weapon.obj"
	-@erase "$(INTDIR)\Raven_Weapon.sbr"
	-@erase "$(INTDIR)\Script1.res"
	-@erase "$(INTDIR)\Trigger_HealthGiver.obj"
	-@erase "$(INTDIR)\Trigger_HealthGiver.sbr"
	-@erase "$(INTDIR)\Trigger_WeaponGiver.obj"
	-@erase "$(INTDIR)\Trigger_WeaponGiver.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\Weapon_Knife.obj"
	-@erase "$(INTDIR)\Weapon_Knife.sbr"
	-@erase "$(INTDIR)\Weapon_RailGun.obj"
	-@erase "$(INTDIR)\Weapon_RailGun.sbr"
	-@erase "$(INTDIR)\Weapon_RocketLauncher.obj"
	-@erase "$(INTDIR)\Weapon_RocketLauncher.sbr"
	-@erase "$(INTDIR)\Weapon_ShotGun.obj"
	-@erase "$(INTDIR)\Weapon_ShotGun.sbr"
	-@erase "$(INTDIR)\WindowUtils.obj"
	-@erase "$(INTDIR)\WindowUtils.sbr"
	-@erase "$(OUTDIR)\Raven.bsc"
	-@erase "$(OUTDIR)\Raven.exe"
	-@erase "$(OUTDIR)\Raven.ilk"
	-@erase "$(OUTDIR)\Raven.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GR /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FAs /Fa"$(INTDIR)\\" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Raven.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /Zm200 /c
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\Script1.res" /d "_DEBUG"
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Raven.bsc"
BSC32_SBRS= \
	"$(INTDIR)\main.sbr" \
	"$(INTDIR)\Raven_Game.sbr" \
	"$(INTDIR)\Raven_Map.sbr" \
	"$(INTDIR)\Raven_UserOptions.sbr" \
	"$(INTDIR)\Projectile_Rocket.sbr" \
	"$(INTDIR)\Projectile_Shell.sbr" \
	"$(INTDIR)\Projectile_Slug.sbr" \
	"$(INTDIR)\Raven_Weapon.sbr" \
	"$(INTDIR)\Weapon_Knife.sbr" \
	"$(INTDIR)\Weapon_RailGun.sbr" \
	"$(INTDIR)\Weapon_RocketLauncher.sbr" \
	"$(INTDIR)\Weapon_ShotGun.sbr" \
	"$(INTDIR)\BaseGameEntity.sbr" \
	"$(INTDIR)\EntityManager.sbr" \
	"$(INTDIR)\Raven_Bot.sbr" \
	"$(INTDIR)\Raven_Door.sbr" \
	"$(INTDIR)\Goal_Explore.sbr" \
	"$(INTDIR)\Goal_FollowPath.sbr" \
	"$(INTDIR)\Goal_GetItem.sbr" \
	"$(INTDIR)\Goal_MoveToPosition.sbr" \
	"$(INTDIR)\Goal_NegotiateDoor.sbr" \
	"$(INTDIR)\Goal_SeekToPosition.sbr" \
	"$(INTDIR)\Goal_TraverseEdge.sbr" \
	"$(INTDIR)\Goal_Wander.sbr" \
	"$(INTDIR)\ExploreGoal_Evaluator.sbr" \
	"$(INTDIR)\GetHealthGoal_Evaluator.sbr" \
	"$(INTDIR)\GetWeaponGoal_Evaluator.sbr" \
	"$(INTDIR)\Raven_GoalArbitrator.sbr" \
	"$(INTDIR)\Raven_Goal_Types.sbr" \
	"$(INTDIR)\Raven_GoalQ.sbr" \
	"$(INTDIR)\FuzzySet_LeftShoulder.sbr" \
	"$(INTDIR)\FuzzySet_RightShoulder.sbr" \
	"$(INTDIR)\FuzzySet_Singleton.sbr" \
	"$(INTDIR)\FuzzySet_Triangle.sbr" \
	"$(INTDIR)\FuzzyModule.sbr" \
	"$(INTDIR)\FuzzyOperators.sbr" \
	"$(INTDIR)\FuzzyVariable.sbr" \
	"$(INTDIR)\Raven_PathPlanner.sbr" \
	"$(INTDIR)\Raven_SteeringBehaviors.sbr" \
	"$(INTDIR)\MessageDispatcher.sbr" \
	"$(INTDIR)\Raven_TargetingSystem.sbr" \
	"$(INTDIR)\Trigger_HealthGiver.sbr" \
	"$(INTDIR)\Trigger_WeaponGiver.sbr" \
	"$(INTDIR)\Raven_Scriptor.sbr" \
	"$(INTDIR)\DebugConsole.sbr" \
	"$(INTDIR)\Cgdi.sbr" \
	"$(INTDIR)\CrudeTimer.sbr" \
	"$(INTDIR)\FrameCounter.sbr" \
	"$(INTDIR)\Obstacle.sbr" \
	"$(INTDIR)\PrecisionTimer.sbr" \
	"$(INTDIR)\WindowUtils.sbr"

"$(OUTDIR)\Raven.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\Raven.pdb" /debug /machine:I386 /nodefaultlib:"libcmt" /out:"$(OUTDIR)\Raven.exe" /pdbtype:sept
LINK32_OBJS= \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\Raven_Game.obj" \
	"$(INTDIR)\Raven_Map.obj" \
	"$(INTDIR)\Raven_UserOptions.obj" \
	"$(INTDIR)\Projectile_Rocket.obj" \
	"$(INTDIR)\Projectile_Shell.obj" \
	"$(INTDIR)\Projectile_Slug.obj" \
	"$(INTDIR)\Raven_Weapon.obj" \
	"$(INTDIR)\Weapon_Knife.obj" \
	"$(INTDIR)\Weapon_RailGun.obj" \
	"$(INTDIR)\Weapon_RocketLauncher.obj" \
	"$(INTDIR)\Weapon_ShotGun.obj" \
	"$(INTDIR)\BaseGameEntity.obj" \
	"$(INTDIR)\EntityManager.obj" \
	"$(INTDIR)\Raven_Bot.obj" \
	"$(INTDIR)\Raven_Door.obj" \
	"$(INTDIR)\Goal_Explore.obj" \
	"$(INTDIR)\Goal_FollowPath.obj" \
	"$(INTDIR)\Goal_GetItem.obj" \
	"$(INTDIR)\Goal_MoveToPosition.obj" \
	"$(INTDIR)\Goal_NegotiateDoor.obj" \
	"$(INTDIR)\Goal_SeekToPosition.obj" \
	"$(INTDIR)\Goal_TraverseEdge.obj" \
	"$(INTDIR)\Goal_Wander.obj" \
	"$(INTDIR)\ExploreGoal_Evaluator.obj" \
	"$(INTDIR)\GetHealthGoal_Evaluator.obj" \
	"$(INTDIR)\GetWeaponGoal_Evaluator.obj" \
	"$(INTDIR)\Raven_GoalArbitrator.obj" \
	"$(INTDIR)\Raven_Goal_Types.obj" \
	"$(INTDIR)\Raven_GoalQ.obj" \
	"$(INTDIR)\FuzzySet_LeftShoulder.obj" \
	"$(INTDIR)\FuzzySet_RightShoulder.obj" \
	"$(INTDIR)\FuzzySet_Singleton.obj" \
	"$(INTDIR)\FuzzySet_Triangle.obj" \
	"$(INTDIR)\FuzzyModule.obj" \
	"$(INTDIR)\FuzzyOperators.obj" \
	"$(INTDIR)\FuzzyVariable.obj" \
	"$(INTDIR)\Raven_PathPlanner.obj" \
	"$(INTDIR)\Raven_SteeringBehaviors.obj" \
	"$(INTDIR)\MessageDispatcher.obj" \
	"$(INTDIR)\Raven_TargetingSystem.obj" \
	"$(INTDIR)\Trigger_HealthGiver.obj" \
	"$(INTDIR)\Trigger_WeaponGiver.obj" \
	"$(INTDIR)\Raven_Scriptor.obj" \
	"$(INTDIR)\DebugConsole.obj" \
	"$(INTDIR)\Cgdi.obj" \
	"$(INTDIR)\CrudeTimer.obj" \
	"$(INTDIR)\FrameCounter.obj" \
	"$(INTDIR)\Obstacle.obj" \
	"$(INTDIR)\PrecisionTimer.obj" \
	"$(INTDIR)\WindowUtils.obj" \
	"$(INTDIR)\Script1.res"

"$(OUTDIR)\Raven.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("Raven.dep")
!INCLUDE "Raven.dep"
!ELSE
!MESSAGE Warning: cannot find "Raven.dep"
!ENDIF
!ENDIF


!IF "$(CFG)" == "Raven - Win32 Release" || "$(CFG)" == "Raven - Win32 Debug"
SOURCE=.\main.cpp

"$(INTDIR)\main.obj"	"$(INTDIR)\main.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Raven_Game.cpp

"$(INTDIR)\Raven_Game.obj"	"$(INTDIR)\Raven_Game.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Raven_Map.cpp

"$(INTDIR)\Raven_Map.obj"	"$(INTDIR)\Raven_Map.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Raven_UserOptions.cpp

"$(INTDIR)\Raven_UserOptions.obj"	"$(INTDIR)\Raven_UserOptions.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\armoury\Projectile_Rocket.cpp

"$(INTDIR)\Projectile_Rocket.obj"	"$(INTDIR)\Projectile_Rocket.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\armoury\Projectile_Shell.cpp

"$(INTDIR)\Projectile_Shell.obj"	"$(INTDIR)\Projectile_Shell.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\armoury\Projectile_Slug.cpp

"$(INTDIR)\Projectile_Slug.obj"	"$(INTDIR)\Projectile_Slug.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\armoury\Raven_Weapon.cpp

"$(INTDIR)\Raven_Weapon.obj"	"$(INTDIR)\Raven_Weapon.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\armoury\Weapon_Knife.cpp

"$(INTDIR)\Weapon_Knife.obj"	"$(INTDIR)\Weapon_Knife.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\armoury\Weapon_RailGun.cpp

"$(INTDIR)\Weapon_RailGun.obj"	"$(INTDIR)\Weapon_RailGun.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\armoury\Weapon_RocketLauncher.cpp

"$(INTDIR)\Weapon_RocketLauncher.obj"	"$(INTDIR)\Weapon_RocketLauncher.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\armoury\Weapon_ShotGun.cpp

"$(INTDIR)\Weapon_ShotGun.obj"	"$(INTDIR)\Weapon_ShotGun.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Common\Game\BaseGameEntity.cpp

"$(INTDIR)\BaseGameEntity.obj"	"$(INTDIR)\BaseGameEntity.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Common\Game\EntityManager.cpp

"$(INTDIR)\EntityManager.obj"	"$(INTDIR)\EntityManager.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Raven_Bot.cpp

"$(INTDIR)\Raven_Bot.obj"	"$(INTDIR)\Raven_Bot.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Raven_Door.cpp

"$(INTDIR)\Raven_Door.obj"	"$(INTDIR)\Raven_Door.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Script1.rc

"$(INTDIR)\Script1.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\goals\Goal_Explore.cpp

"$(INTDIR)\Goal_Explore.obj"	"$(INTDIR)\Goal_Explore.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\goals\Goal_FollowPath.cpp

"$(INTDIR)\Goal_FollowPath.obj"	"$(INTDIR)\Goal_FollowPath.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\goals\Goal_GetItem.cpp

"$(INTDIR)\Goal_GetItem.obj"	"$(INTDIR)\Goal_GetItem.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\goals\Goal_MoveToPosition.cpp

"$(INTDIR)\Goal_MoveToPosition.obj"	"$(INTDIR)\Goal_MoveToPosition.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\goals\Goal_NegotiateDoor.cpp

"$(INTDIR)\Goal_NegotiateDoor.obj"	"$(INTDIR)\Goal_NegotiateDoor.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\goals\Goal_SeekToPosition.cpp

"$(INTDIR)\Goal_SeekToPosition.obj"	"$(INTDIR)\Goal_SeekToPosition.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\goals\Goal_TraverseEdge.cpp

"$(INTDIR)\Goal_TraverseEdge.obj"	"$(INTDIR)\Goal_TraverseEdge.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\goals\Goal_Wander.cpp

"$(INTDIR)\Goal_Wander.obj"	"$(INTDIR)\Goal_Wander.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\goals\ExploreGoal_Evaluator.cpp

"$(INTDIR)\ExploreGoal_Evaluator.obj"	"$(INTDIR)\ExploreGoal_Evaluator.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\goals\GetHealthGoal_Evaluator.cpp

"$(INTDIR)\GetHealthGoal_Evaluator.obj"	"$(INTDIR)\GetHealthGoal_Evaluator.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\goals\GetWeaponGoal_Evaluator.cpp

"$(INTDIR)\GetWeaponGoal_Evaluator.obj"	"$(INTDIR)\GetWeaponGoal_Evaluator.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\goals\Raven_GoalArbitrator.cpp

"$(INTDIR)\Raven_GoalArbitrator.obj"	"$(INTDIR)\Raven_GoalArbitrator.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\goals\Raven_Goal_Types.cpp

"$(INTDIR)\Raven_Goal_Types.obj"	"$(INTDIR)\Raven_Goal_Types.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\goals\Raven_GoalQ.cpp

"$(INTDIR)\Raven_GoalQ.obj"	"$(INTDIR)\Raven_GoalQ.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Common\fuzzy\FuzzySet_LeftShoulder.cpp

"$(INTDIR)\FuzzySet_LeftShoulder.obj"	"$(INTDIR)\FuzzySet_LeftShoulder.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Common\fuzzy\FuzzySet_RightShoulder.cpp

"$(INTDIR)\FuzzySet_RightShoulder.obj"	"$(INTDIR)\FuzzySet_RightShoulder.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Common\fuzzy\FuzzySet_Singleton.cpp

"$(INTDIR)\FuzzySet_Singleton.obj"	"$(INTDIR)\FuzzySet_Singleton.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Common\fuzzy\FuzzySet_Triangle.cpp

"$(INTDIR)\FuzzySet_Triangle.obj"	"$(INTDIR)\FuzzySet_Triangle.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Common\fuzzy\FuzzyModule.cpp

"$(INTDIR)\FuzzyModule.obj"	"$(INTDIR)\FuzzyModule.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Common\fuzzy\FuzzyOperators.cpp

"$(INTDIR)\FuzzyOperators.obj"	"$(INTDIR)\FuzzyOperators.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Common\fuzzy\FuzzyVariable.cpp

"$(INTDIR)\FuzzyVariable.obj"	"$(INTDIR)\FuzzyVariable.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\navigation\Raven_PathPlanner.cpp

"$(INTDIR)\Raven_PathPlanner.obj"	"$(INTDIR)\Raven_PathPlanner.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Raven_SteeringBehaviors.cpp

"$(INTDIR)\Raven_SteeringBehaviors.obj"	"$(INTDIR)\Raven_SteeringBehaviors.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=..\Common\AI\MessageDispatcher.cpp

"$(INTDIR)\MessageDispatcher.obj"	"$(INTDIR)\MessageDispatcher.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Raven_TargetingSystem.cpp

"$(INTDIR)\Raven_TargetingSystem.obj"	"$(INTDIR)\Raven_TargetingSystem.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\triggers\Trigger_HealthGiver.cpp

"$(INTDIR)\Trigger_HealthGiver.obj"	"$(INTDIR)\Trigger_HealthGiver.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\triggers\Trigger_WeaponGiver.cpp

"$(INTDIR)\Trigger_WeaponGiver.obj"	"$(INTDIR)\Trigger_WeaponGiver.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Raven_Scriptor.cpp

"$(INTDIR)\Raven_Scriptor.obj"	"$(INTDIR)\Raven_Scriptor.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=..\Common\Debug\DebugConsole.cpp

"$(INTDIR)\DebugConsole.obj"	"$(INTDIR)\DebugConsole.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Common\misc\Cgdi.cpp

"$(INTDIR)\Cgdi.obj"	"$(INTDIR)\Cgdi.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Common\Time\CrudeTimer.cpp

"$(INTDIR)\CrudeTimer.obj"	"$(INTDIR)\CrudeTimer.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Common\misc\FrameCounter.cpp

"$(INTDIR)\FrameCounter.obj"	"$(INTDIR)\FrameCounter.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Obstacle.cpp

"$(INTDIR)\Obstacle.obj"	"$(INTDIR)\Obstacle.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=..\Common\Time\PrecisionTimer.cpp

"$(INTDIR)\PrecisionTimer.obj"	"$(INTDIR)\PrecisionTimer.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Common\misc\WindowUtils.cpp

"$(INTDIR)\WindowUtils.obj"	"$(INTDIR)\WindowUtils.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF
