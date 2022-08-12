# Microsoft Developer Studio Project File - Name="Raven" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Raven - Win32 boundschecker
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Raven.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Raven.mak" CFG="Raven - Win32 boundschecker"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Raven - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Raven - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "Raven - Win32 boundschecker" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Raven - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /YX /FD /Zm200 /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"libcmt"

!ELSEIF  "$(CFG)" == "Raven - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GR /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FAs /FR /YX /FD /GZ /Zm200 /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"libcmt" /pdbtype:sept

!ELSEIF  "$(CFG)" == "Raven - Win32 boundschecker"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Raven___Win32_boundschecker"
# PROP BASE Intermediate_Dir "Raven___Win32_boundschecker"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Raven___Win32_boundschecker"
# PROP Intermediate_Dir "Raven___Win32_boundschecker"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GR /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FAs /FR /YX /FD /GZ /Zm200 /c
# ADD CPP /nologo /W3 /Gm /GR /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FAs /FR /YX /FD /GZ /Zm200 /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"libcmt" /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"libcmt" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Raven - Win32 Release"
# Name "Raven - Win32 Debug"
# Name "Raven - Win32 boundschecker"
# Begin Group "Game"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "weapons & projectiles"

# PROP Default_Filter ""
# Begin Group "weapons"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\armory\Raven_Weapon.cpp
# End Source File
# Begin Source File

SOURCE=.\armory\Raven_Weapon.h
# End Source File
# Begin Source File

SOURCE=.\armory\Weapon_Blaster.cpp
# End Source File
# Begin Source File

SOURCE=.\armory\Weapon_Blaster.h
# End Source File
# Begin Source File

SOURCE=.\armory\Weapon_RailGun.cpp
# End Source File
# Begin Source File

SOURCE=.\armory\Weapon_RailGun.h
# End Source File
# Begin Source File

SOURCE=.\armory\Weapon_RocketLauncher.cpp
# End Source File
# Begin Source File

SOURCE=.\armory\Weapon_RocketLauncher.h
# End Source File
# Begin Source File

SOURCE=.\armory\Weapon_ShotGun.cpp
# End Source File
# Begin Source File

SOURCE=.\armory\Weapon_ShotGun.h
# End Source File
# End Group
# Begin Group "projectiles"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\armory\Projectile_Bolt.cpp
# End Source File
# Begin Source File

SOURCE=.\armory\Projectile_Bolt.h
# End Source File
# Begin Source File

SOURCE=.\armory\Projectile_Pellet.cpp
# End Source File
# Begin Source File

SOURCE=.\armory\Projectile_Pellet.h
# End Source File
# Begin Source File

SOURCE=.\armory\Projectile_Rocket.cpp
# End Source File
# Begin Source File

SOURCE=.\armory\Projectile_Rocket.h
# End Source File
# Begin Source File

SOURCE=.\armory\Projectile_Slug.cpp
# End Source File
# Begin Source File

SOURCE=.\armory\Projectile_Slug.h
# End Source File
# Begin Source File

SOURCE=.\armory\Raven_Projectile.cpp
# End Source File
# Begin Source File

SOURCE=.\armory\Raven_Projectile.h
# End Source File
# End Group
# End Group
# Begin Group "Base entity classes"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Common\Game\BaseGameEntity.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\Game\BaseGameEntity.h
# End Source File
# Begin Source File

SOURCE=..\Common\Game\EntityFunctionTemplates.h
# End Source File
# Begin Source File

SOURCE=..\Common\Game\MovingEntity.h
# End Source File
# End Group
# Begin Group "Script related"

# PROP Default_Filter ""
# Begin Group "general"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\lua\Raven_Scriptor.cpp
# End Source File
# Begin Source File

SOURCE=.\lua\Raven_Scriptor.h
# End Source File
# Begin Source File

SOURCE=..\Common\script\Scriptor.h
# End Source File
# End Group
# Begin Group "lua headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\Common\lua-5.0\include\lauxlib.h"
# End Source File
# Begin Source File

SOURCE="..\Common\lua-5.0\include\lua.h"
# End Source File
# Begin Source File

SOURCE="..\Common\lua-5.0\include\LuaHelperFunctions.h"
# End Source File
# Begin Source File

SOURCE="..\Common\lua-5.0\include\lualib.h"
# End Source File
# End Group
# Begin Source File

SOURCE=.\Params.lua
# End Source File
# End Group
# Begin Group "misc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\constants.h
# End Source File
# Begin Source File

SOURCE=..\Common\Game\EntityManager.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\Game\EntityManager.h
# End Source File
# Begin Source File

SOURCE=.\GraveMarkers.cpp
# End Source File
# Begin Source File

SOURCE=.\GraveMarkers.h
# End Source File
# Begin Source File

SOURCE=.\Raven_Door.cpp
# End Source File
# Begin Source File

SOURCE=.\Raven_Door.h
# End Source File
# Begin Source File

SOURCE=.\Raven_ObjectEnumerations.h
# End Source File
# Begin Source File

SOURCE=.\Raven_UserOptions.cpp
# End Source File
# Begin Source File

SOURCE=.\Raven_UserOptions.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# Begin Source File

SOURCE=.\Raven_Bot.cpp
# End Source File
# Begin Source File

SOURCE=.\Raven_Bot.h
# End Source File
# Begin Source File

SOURCE=.\Raven_Game.cpp
# End Source File
# Begin Source File

SOURCE=.\Raven_Game.h
# End Source File
# Begin Source File

SOURCE=.\Raven_Map.cpp
# End Source File
# Begin Source File

SOURCE=.\Raven_Map.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter ""
# Begin Group "maps"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\maps\Raven_DM1.map
# End Source File
# Begin Source File

SOURCE=.\maps\Raven_DM1_Doors.map
# End Source File
# End Group
# Begin Source File

SOURCE=.\note.txt
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\Script1.rc
# End Source File
# End Group
# Begin Group "AI"

# PROP Default_Filter ""
# Begin Group "goals"

# PROP Default_Filter ""
# Begin Group "composite"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\goals\Goal_AdjustRange.cpp
# End Source File
# Begin Source File

SOURCE=.\goals\Goal_AdjustRange.h
# End Source File
# Begin Source File

SOURCE=.\goals\Goal_AttackTarget.cpp
# End Source File
# Begin Source File

SOURCE=.\goals\Goal_AttackTarget.h
# End Source File
# Begin Source File

SOURCE=..\Common\Goals\Goal_Composite.h
# End Source File
# Begin Source File

SOURCE=.\goals\Goal_Explore.cpp
# End Source File
# Begin Source File

SOURCE=.\goals\Goal_Explore.h
# End Source File
# Begin Source File

SOURCE=.\goals\Goal_FollowPath.cpp
# End Source File
# Begin Source File

SOURCE=.\goals\Goal_FollowPath.h
# End Source File
# Begin Source File

SOURCE=.\goals\Goal_GetItem.cpp
# End Source File
# Begin Source File

SOURCE=.\goals\Goal_GetItem.h
# End Source File
# Begin Source File

SOURCE=.\goals\Goal_HuntTarget.cpp
# End Source File
# Begin Source File

SOURCE=.\goals\Goal_HuntTarget.h
# End Source File
# Begin Source File

SOURCE=.\goals\Goal_MoveToPosition.cpp
# End Source File
# Begin Source File

SOURCE=.\goals\Goal_MoveToPosition.h
# End Source File
# Begin Source File

SOURCE=.\goals\Goal_NegotiateDoor.cpp
# End Source File
# Begin Source File

SOURCE=.\goals\Goal_NegotiateDoor.h
# End Source File
# Begin Source File

SOURCE=.\goals\Goal_Think.cpp
# End Source File
# Begin Source File

SOURCE=.\goals\Goal_Think.h
# End Source File
# End Group
# Begin Group "goal evaluation"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\goals\AttackTargetGoal_Evaluator.cpp
# End Source File
# Begin Source File

SOURCE=.\goals\AttackTargetGoal_Evaluator.h
# End Source File
# Begin Source File

SOURCE=.\goals\ExploreGoal_Evaluator.cpp
# End Source File
# Begin Source File

SOURCE=.\goals\ExploreGoal_Evaluator.h
# End Source File
# Begin Source File

SOURCE=.\goals\GetHealthGoal_Evaluator.cpp
# End Source File
# Begin Source File

SOURCE=.\goals\GetHealthGoal_Evaluator.h
# End Source File
# Begin Source File

SOURCE=.\goals\GetWeaponGoal_Evaluator.cpp
# End Source File
# Begin Source File

SOURCE=.\goals\GetWeaponGoal_Evaluator.h
# End Source File
# Begin Source File

SOURCE=.\goals\Goal_Evaluator.h
# End Source File
# Begin Source File

SOURCE=.\goals\Raven_Feature.cpp
# End Source File
# Begin Source File

SOURCE=.\goals\Raven_Feature.h
# End Source File
# End Group
# Begin Group "atomic"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Common\Goals\Goal.h
# End Source File
# Begin Source File

SOURCE=.\goals\Goal_DodgeSideToSide.cpp
# End Source File
# Begin Source File

SOURCE=.\goals\Goal_DodgeSideToSide.h
# End Source File
# Begin Source File

SOURCE=.\goals\Goal_SayPhrase.cpp
# End Source File
# Begin Source File

SOURCE=.\goals\Goal_SayPhrase.h
# End Source File
# Begin Source File

SOURCE=.\goals\Goal_SeekToPosition.cpp
# End Source File
# Begin Source File

SOURCE=.\goals\Goal_SeekToPosition.h
# End Source File
# Begin Source File

SOURCE=.\goals\Goal_TraverseEdge.cpp
# End Source File
# Begin Source File

SOURCE=.\goals\Goal_TraverseEdge.h
# End Source File
# Begin Source File

SOURCE=.\goals\Goal_Wander.cpp
# End Source File
# Begin Source File

SOURCE=.\goals\Goal_Wander.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\goals\Raven_Goal_Types.cpp
# End Source File
# Begin Source File

SOURCE=.\goals\Raven_Goal_Types.h
# End Source File
# End Group
# Begin Group "fuzzy logic"

# PROP Default_Filter ""
# Begin Group "fuzzy set types"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Common\fuzzy\FuzzySet.h
# End Source File
# Begin Source File

SOURCE=..\Common\fuzzy\FuzzySet_LeftShoulder.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\fuzzy\FuzzySet_LeftShoulder.h
# End Source File
# Begin Source File

SOURCE=..\Common\fuzzy\FuzzySet_RightShoulder.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\fuzzy\FuzzySet_RightShoulder.h
# End Source File
# Begin Source File

SOURCE=..\Common\fuzzy\FuzzySet_Shoulder.h
# End Source File
# Begin Source File

SOURCE=..\Common\fuzzy\FuzzySet_Singleton.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\fuzzy\FuzzySet_Singleton.h
# End Source File
# Begin Source File

SOURCE=..\Common\fuzzy\FuzzySet_Triangle.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\fuzzy\FuzzySet_Triangle.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\Common\fuzzy\FuzzyHedges.h
# End Source File
# Begin Source File

SOURCE=..\Common\fuzzy\FuzzyModule.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\fuzzy\FuzzyModule.h
# End Source File
# Begin Source File

SOURCE=..\Common\fuzzy\FuzzyOperators.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\fuzzy\FuzzyOperators.h
# End Source File
# Begin Source File

SOURCE=..\Common\fuzzy\FuzzyRule.h
# End Source File
# Begin Source File

SOURCE=..\Common\fuzzy\FuzzyTerm.h
# End Source File
# Begin Source File

SOURCE=..\Common\fuzzy\FuzzyVariable.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\fuzzy\FuzzyVariable.h
# End Source File
# Begin Source File

SOURCE=..\Common\fuzzy\FzSet.h
# End Source File
# End Group
# Begin Group "Movement & Navigation"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Common\Graph\AStarHeuristicPolicies.h
# End Source File
# Begin Source File

SOURCE=..\Common\misc\CellSpacePartition.h
# End Source File
# Begin Source File

SOURCE=..\Common\Graph\GraphAlgorithms.h
# End Source File
# Begin Source File

SOURCE=..\Common\Graph\GraphEdgeTypes.h
# End Source File
# Begin Source File

SOURCE=..\Common\Graph\GraphNodeTypes.h
# End Source File
# Begin Source File

SOURCE=..\Common\Graph\HandyGraphFunctions.h
# End Source File
# Begin Source File

SOURCE=..\Common\Graph\NodeTypeEnumerations.h
# End Source File
# Begin Source File

SOURCE=.\navigation\PathEdge.h
# End Source File
# Begin Source File

SOURCE=.\navigation\PathManager.h
# End Source File
# Begin Source File

SOURCE=.\navigation\Raven_PathPlanner.cpp
# End Source File
# Begin Source File

SOURCE=.\navigation\Raven_PathPlanner.h
# End Source File
# Begin Source File

SOURCE=.\Raven_SteeringBehaviors.cpp
# End Source File
# Begin Source File

SOURCE=.\Raven_SteeringBehaviors.h
# End Source File
# Begin Source File

SOURCE=.\navigation\SearchTerminationPolicies.h
# End Source File
# Begin Source File

SOURCE=..\Common\Graph\SparseGraph.h
# End Source File
# Begin Source File

SOURCE=.\navigation\TimeSlicedGraphAlgorithms.h
# End Source File
# End Group
# Begin Group "Messaging"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Common\Messaging\MessageDispatcher.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\Messaging\MessageDispatcher.h
# End Source File
# Begin Source File

SOURCE=.\Raven_Messages.h
# End Source File
# Begin Source File

SOURCE=..\Common\Messaging\Telegram.h
# End Source File
# End Group
# Begin Group "Sensory Memory"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Raven_SensoryMemory.cpp
# End Source File
# Begin Source File

SOURCE=.\Raven_SensoryMemory.h
# End Source File
# End Group
# Begin Group "Triggers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Common\Triggers\Trigger.h
# End Source File
# Begin Source File

SOURCE=.\triggers\Trigger_HealthGiver.cpp
# End Source File
# Begin Source File

SOURCE=.\triggers\Trigger_HealthGiver.h
# End Source File
# Begin Source File

SOURCE=..\Common\Triggers\Trigger_LimitedLifeTime.h
# End Source File
# Begin Source File

SOURCE=.\triggers\Trigger_OnButtonSendMsg.h
# End Source File
# Begin Source File

SOURCE=..\Common\Triggers\Trigger_ReSpawning.h
# End Source File
# Begin Source File

SOURCE=.\triggers\Trigger_SoundNotify.cpp
# End Source File
# Begin Source File

SOURCE=.\triggers\Trigger_SoundNotify.h
# End Source File
# Begin Source File

SOURCE=.\triggers\Trigger_WeaponGiver.cpp
# End Source File
# Begin Source File

SOURCE=.\triggers\Trigger_WeaponGiver.h
# End Source File
# Begin Source File

SOURCE=..\Common\Triggers\TriggerRegion.h
# End Source File
# Begin Source File

SOURCE=..\Common\Triggers\TriggerSystem.h
# End Source File
# End Group
# Begin Group "Weapon Handling"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Raven_WeaponSystem.cpp
# End Source File
# Begin Source File

SOURCE=.\Raven_WeaponSystem.h
# End Source File
# End Group
# Begin Group "Target Selection"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Raven_TargetingSystem.cpp
# End Source File
# Begin Source File

SOURCE=.\Raven_TargetingSystem.h
# End Source File
# End Group
# End Group
# Begin Group "Common"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Common\2D\C2DMatrix.h
# End Source File
# Begin Source File

SOURCE=..\Common\misc\Cgdi.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\misc\Cgdi.h
# End Source File
# Begin Source File

SOURCE=..\Common\Time\CrudeTimer.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\Time\CrudeTimer.h
# End Source File
# Begin Source File

SOURCE=..\Common\Debug\DebugConsole.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\Debug\DebugConsole.h
# End Source File
# Begin Source File

SOURCE=..\Common\misc\FrameCounter.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\misc\FrameCounter.h
# End Source File
# Begin Source File

SOURCE=..\Common\2D\geometry.h
# End Source File
# Begin Source File

SOURCE=..\Common\2D\InvertedAABBox2D.h
# End Source File
# Begin Source File

SOURCE=..\Common\Time\PrecisionTimer.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\Time\PrecisionTimer.h
# End Source File
# Begin Source File

SOURCE=..\Common\misc\PriorityQueue.h
# End Source File
# Begin Source File

SOURCE=..\Common\PriorityQueue.h
# End Source File
# Begin Source File

SOURCE=..\Common\Time\Regulator.h
# End Source File
# Begin Source File

SOURCE=..\Common\misc\Stream_Utility_Functions.h
# End Source File
# Begin Source File

SOURCE=..\Common\2D\Transformations.h
# End Source File
# Begin Source File

SOURCE=..\Common\misc\utils.h
# End Source File
# Begin Source File

SOURCE=..\Common\2D\Vector2d.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\2D\Vector2D.h
# End Source File
# Begin Source File

SOURCE=..\Common\2D\Wall2D.h
# End Source File
# Begin Source File

SOURCE=..\Common\2D\WallIntersectionTests.h
# End Source File
# Begin Source File

SOURCE=..\Common\misc\WindowUtils.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\misc\WindowUtils.h
# End Source File
# End Group
# End Target
# End Project
