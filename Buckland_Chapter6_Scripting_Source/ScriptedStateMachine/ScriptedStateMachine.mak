# Microsoft Developer Studio Generated NMAKE File, Based on ScriptedStateMachine.dsp
!IF "$(CFG)" == ""
CFG=ScriptedStateMachine - Win32 Debug
!MESSAGE No configuration specified. Defaulting to ScriptedStateMachine - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "ScriptedStateMachine - Win32 Release" && "$(CFG)" != "ScriptedStateMachine - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ScriptedStateMachine.mak" CFG="ScriptedStateMachine - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ScriptedStateMachine - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "ScriptedStateMachine - Win32 Debug" (based on "Win32 (x86) Console Application")
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

!IF  "$(CFG)" == "ScriptedStateMachine - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\ScriptedStateMachine.exe"


CLEAN :
	-@erase "$(INTDIR)\class_rep.obj"
	-@erase "$(INTDIR)\create_class.obj"
	-@erase "$(INTDIR)\find_best_match.obj"
	-@erase "$(INTDIR)\function.obj"
	-@erase "$(INTDIR)\implicit_cast.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\Miner.obj"
	-@erase "$(INTDIR)\object.obj"
	-@erase "$(INTDIR)\open.obj"
	-@erase "$(INTDIR)\stack_content_by_name.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ScriptedStateMachine.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\ScriptedStateMachine.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ScriptedStateMachine.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\ScriptedStateMachine.pdb" /machine:I386 /nodefaultlib:"libcmt" /out:"$(OUTDIR)\ScriptedStateMachine.exe" 
LINK32_OBJS= \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\Miner.obj" \
	"$(INTDIR)\class_rep.obj" \
	"$(INTDIR)\create_class.obj" \
	"$(INTDIR)\find_best_match.obj" \
	"$(INTDIR)\function.obj" \
	"$(INTDIR)\implicit_cast.obj" \
	"$(INTDIR)\object.obj" \
	"$(INTDIR)\open.obj" \
	"$(INTDIR)\stack_content_by_name.obj"

"$(OUTDIR)\ScriptedStateMachine.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ScriptedStateMachine - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\ScriptedStateMachine.exe" "$(OUTDIR)\ScriptedStateMachine.bsc"


CLEAN :
	-@erase "$(INTDIR)\class_rep.obj"
	-@erase "$(INTDIR)\class_rep.sbr"
	-@erase "$(INTDIR)\create_class.obj"
	-@erase "$(INTDIR)\create_class.sbr"
	-@erase "$(INTDIR)\find_best_match.obj"
	-@erase "$(INTDIR)\find_best_match.sbr"
	-@erase "$(INTDIR)\function.obj"
	-@erase "$(INTDIR)\function.sbr"
	-@erase "$(INTDIR)\implicit_cast.obj"
	-@erase "$(INTDIR)\implicit_cast.sbr"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\main.sbr"
	-@erase "$(INTDIR)\Miner.obj"
	-@erase "$(INTDIR)\Miner.sbr"
	-@erase "$(INTDIR)\object.obj"
	-@erase "$(INTDIR)\object.sbr"
	-@erase "$(INTDIR)\open.obj"
	-@erase "$(INTDIR)\open.sbr"
	-@erase "$(INTDIR)\stack_content_by_name.obj"
	-@erase "$(INTDIR)\stack_content_by_name.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\ScriptedStateMachine.bsc"
	-@erase "$(OUTDIR)\ScriptedStateMachine.exe"
	-@erase "$(OUTDIR)\ScriptedStateMachine.ilk"
	-@erase "$(OUTDIR)\ScriptedStateMachine.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\ScriptedStateMachine.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ScriptedStateMachine.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\main.sbr" \
	"$(INTDIR)\Miner.sbr" \
	"$(INTDIR)\class_rep.sbr" \
	"$(INTDIR)\create_class.sbr" \
	"$(INTDIR)\find_best_match.sbr" \
	"$(INTDIR)\function.sbr" \
	"$(INTDIR)\implicit_cast.sbr" \
	"$(INTDIR)\object.sbr" \
	"$(INTDIR)\open.sbr" \
	"$(INTDIR)\stack_content_by_name.sbr"

"$(OUTDIR)\ScriptedStateMachine.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\ScriptedStateMachine.pdb" /debug /machine:I386 /nodefaultlib:"libcmt" /out:"$(OUTDIR)\ScriptedStateMachine.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\Miner.obj" \
	"$(INTDIR)\class_rep.obj" \
	"$(INTDIR)\create_class.obj" \
	"$(INTDIR)\find_best_match.obj" \
	"$(INTDIR)\function.obj" \
	"$(INTDIR)\implicit_cast.obj" \
	"$(INTDIR)\object.obj" \
	"$(INTDIR)\open.obj" \
	"$(INTDIR)\stack_content_by_name.obj"

"$(OUTDIR)\ScriptedStateMachine.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("ScriptedStateMachine.dep")
!INCLUDE "ScriptedStateMachine.dep"
!ELSE 
!MESSAGE Warning: cannot find "ScriptedStateMachine.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ScriptedStateMachine - Win32 Release" || "$(CFG)" == "ScriptedStateMachine - Win32 Debug"
SOURCE=.\main.cpp

!IF  "$(CFG)" == "ScriptedStateMachine - Win32 Release"


"$(INTDIR)\main.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "ScriptedStateMachine - Win32 Debug"


"$(INTDIR)\main.obj"	"$(INTDIR)\main.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Miner.cpp

!IF  "$(CFG)" == "ScriptedStateMachine - Win32 Release"


"$(INTDIR)\Miner.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "ScriptedStateMachine - Win32 Debug"


"$(INTDIR)\Miner.obj"	"$(INTDIR)\Miner.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=..\..\Common\luabind\src\class_rep.cpp

!IF  "$(CFG)" == "ScriptedStateMachine - Win32 Release"


"$(INTDIR)\class_rep.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ScriptedStateMachine - Win32 Debug"


"$(INTDIR)\class_rep.obj"	"$(INTDIR)\class_rep.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\Common\luabind\src\create_class.cpp

!IF  "$(CFG)" == "ScriptedStateMachine - Win32 Release"


"$(INTDIR)\create_class.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ScriptedStateMachine - Win32 Debug"


"$(INTDIR)\create_class.obj"	"$(INTDIR)\create_class.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\Common\luabind\src\find_best_match.cpp

!IF  "$(CFG)" == "ScriptedStateMachine - Win32 Release"


"$(INTDIR)\find_best_match.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ScriptedStateMachine - Win32 Debug"


"$(INTDIR)\find_best_match.obj"	"$(INTDIR)\find_best_match.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\Common\luabind\src\function.cpp

!IF  "$(CFG)" == "ScriptedStateMachine - Win32 Release"


"$(INTDIR)\function.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ScriptedStateMachine - Win32 Debug"


"$(INTDIR)\function.obj"	"$(INTDIR)\function.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\Common\luabind\src\implicit_cast.cpp

!IF  "$(CFG)" == "ScriptedStateMachine - Win32 Release"


"$(INTDIR)\implicit_cast.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ScriptedStateMachine - Win32 Debug"


"$(INTDIR)\implicit_cast.obj"	"$(INTDIR)\implicit_cast.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\Common\luabind\src\object.cpp

!IF  "$(CFG)" == "ScriptedStateMachine - Win32 Release"


"$(INTDIR)\object.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ScriptedStateMachine - Win32 Debug"


"$(INTDIR)\object.obj"	"$(INTDIR)\object.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\Common\luabind\src\open.cpp

!IF  "$(CFG)" == "ScriptedStateMachine - Win32 Release"


"$(INTDIR)\open.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ScriptedStateMachine - Win32 Debug"


"$(INTDIR)\open.obj"	"$(INTDIR)\open.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\Common\luabind\src\stack_content_by_name.cpp

!IF  "$(CFG)" == "ScriptedStateMachine - Win32 Release"


"$(INTDIR)\stack_content_by_name.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ScriptedStateMachine - Win32 Debug"


"$(INTDIR)\stack_content_by_name.obj"	"$(INTDIR)\stack_content_by_name.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 


!ENDIF 

