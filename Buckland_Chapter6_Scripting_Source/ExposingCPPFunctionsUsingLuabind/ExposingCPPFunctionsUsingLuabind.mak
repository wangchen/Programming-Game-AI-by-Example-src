# Microsoft Developer Studio Generated NMAKE File, Based on ExposingCPPFunctionsUsingLuabind.dsp
!IF "$(CFG)" == ""
CFG=ExposingCPPFunctionsUsingLuabind - Win32 Debug
!MESSAGE No configuration specified. Defaulting to ExposingCPPFunctionsUsingLuabind - Win32 Debug.
!ENDIF

!IF "$(CFG)" != "ExposingCPPFunctionsUsingLuabind - Win32 Release" && "$(CFG)" != "ExposingCPPFunctionsUsingLuabind - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE
!MESSAGE NMAKE /f "ExposingCPPFunctionsUsingLuabind.mak" CFG="ExposingCPPFunctionsUsingLuabind - Win32 Debug"
!MESSAGE
!MESSAGE Possible choices for configuration are:
!MESSAGE
!MESSAGE "ExposingCPPFunctionsUsingLuabind - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "ExposingCPPFunctionsUsingLuabind - Win32 Debug" (based on "Win32 (x86) Console Application")
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

!IF  "$(CFG)" == "ExposingCPPFunctionsUsingLuabind - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\ExposingCPPFunctionsUsingLuabind.exe"


CLEAN :
	-@erase "$(INTDIR)\class_rep.obj"
	-@erase "$(INTDIR)\create_class.obj"
	-@erase "$(INTDIR)\find_best_match.obj"
	-@erase "$(INTDIR)\function.obj"
	-@erase "$(INTDIR)\implicit_cast.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\object.obj"
	-@erase "$(INTDIR)\open.obj"
	-@erase "$(INTDIR)\stack_content_by_name.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ExposingCPPFunctionsUsingLuabind.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\ExposingCPPFunctionsUsingLuabind.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ExposingCPPFunctionsUsingLuabind.bsc"
BSC32_SBRS= \

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\ExposingCPPFunctionsUsingLuabind.pdb" /machine:I386 /out:"$(OUTDIR)\ExposingCPPFunctionsUsingLuabind.exe"
LINK32_OBJS= \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\stack_content_by_name.obj" \
	"$(INTDIR)\class_rep.obj" \
	"$(INTDIR)\create_class.obj" \
	"$(INTDIR)\find_best_match.obj" \
	"$(INTDIR)\function.obj" \
	"$(INTDIR)\implicit_cast.obj" \
	"$(INTDIR)\object.obj" \
	"$(INTDIR)\open.obj"

"$(OUTDIR)\ExposingCPPFunctionsUsingLuabind.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ExposingCPPFunctionsUsingLuabind - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\ExposingCPPFunctionsUsingLuabind.exe"


CLEAN :
	-@erase "$(INTDIR)\class_rep.obj"
	-@erase "$(INTDIR)\create_class.obj"
	-@erase "$(INTDIR)\find_best_match.obj"
	-@erase "$(INTDIR)\function.obj"
	-@erase "$(INTDIR)\implicit_cast.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\object.obj"
	-@erase "$(INTDIR)\open.obj"
	-@erase "$(INTDIR)\stack_content_by_name.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\ExposingCPPFunctionsUsingLuabind.exe"
	-@erase "$(OUTDIR)\ExposingCPPFunctionsUsingLuabind.ilk"
	-@erase "$(OUTDIR)\ExposingCPPFunctionsUsingLuabind.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\ExposingCPPFunctionsUsingLuabind.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ExposingCPPFunctionsUsingLuabind.bsc"
BSC32_SBRS= \

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\ExposingCPPFunctionsUsingLuabind.pdb" /debug /machine:I386 /out:"$(OUTDIR)\ExposingCPPFunctionsUsingLuabind.exe" /pdbtype:sept
LINK32_OBJS= \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\stack_content_by_name.obj" \
	"$(INTDIR)\class_rep.obj" \
	"$(INTDIR)\create_class.obj" \
	"$(INTDIR)\find_best_match.obj" \
	"$(INTDIR)\function.obj" \
	"$(INTDIR)\implicit_cast.obj" \
	"$(INTDIR)\object.obj" \
	"$(INTDIR)\open.obj"

"$(OUTDIR)\ExposingCPPFunctionsUsingLuabind.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("ExposingCPPFunctionsUsingLuabind.dep")
!INCLUDE "ExposingCPPFunctionsUsingLuabind.dep"
!ELSE
!MESSAGE Warning: cannot find "ExposingCPPFunctionsUsingLuabind.dep"
!ENDIF
!ENDIF


!IF "$(CFG)" == "ExposingCPPFunctionsUsingLuabind - Win32 Release" || "$(CFG)" == "ExposingCPPFunctionsUsingLuabind - Win32 Debug"
SOURCE=.\main.cpp

"$(INTDIR)\main.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=..\..\Common\luabind\src\class_rep.cpp

"$(INTDIR)\class_rep.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\Common\luabind\src\create_class.cpp

"$(INTDIR)\create_class.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\Common\luabind\src\find_best_match.cpp

"$(INTDIR)\find_best_match.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\Common\luabind\src\function.cpp

"$(INTDIR)\function.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\Common\luabind\src\implicit_cast.cpp

"$(INTDIR)\implicit_cast.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\Common\luabind\src\object.cpp

"$(INTDIR)\object.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\Common\luabind\src\open.cpp

"$(INTDIR)\open.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\Common\luabind\src\stack_content_by_name.cpp

"$(INTDIR)\stack_content_by_name.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF
