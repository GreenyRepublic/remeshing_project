# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2018.1.2\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2018.1.2\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = S:\Benfclark\Documents\GitHub\remeshing_project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = S:\Benfclark\Documents\GitHub\remeshing_project\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles\Remesher.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\Remesher.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\Remesher.dir\flags.make

CMakeFiles\Remesher.dir\src\main.cpp.obj: CMakeFiles\Remesher.dir\flags.make
CMakeFiles\Remesher.dir\src\main.cpp.obj: ..\src\main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=S:\Benfclark\Documents\GitHub\remeshing_project\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Remesher.dir/src/main.cpp.obj"
	C:\PROGRA~2\MIB055~1\2017\COMMUN~1\VC\Tools\MSVC\1414~1.264\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Remesher.dir\src\main.cpp.obj /FdCMakeFiles\Remesher.dir\ /FS -c S:\Benfclark\Documents\GitHub\remeshing_project\src\main.cpp
<<

CMakeFiles\Remesher.dir\src\main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Remesher.dir/src/main.cpp.i"
	C:\PROGRA~2\MIB055~1\2017\COMMUN~1\VC\Tools\MSVC\1414~1.264\bin\Hostx86\x86\cl.exe > CMakeFiles\Remesher.dir\src\main.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E S:\Benfclark\Documents\GitHub\remeshing_project\src\main.cpp
<<

CMakeFiles\Remesher.dir\src\main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Remesher.dir/src/main.cpp.s"
	C:\PROGRA~2\MIB055~1\2017\COMMUN~1\VC\Tools\MSVC\1414~1.264\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Remesher.dir\src\main.cpp.s /c S:\Benfclark\Documents\GitHub\remeshing_project\src\main.cpp
<<

CMakeFiles\Remesher.dir\src\main.cpp.obj.requires:

.PHONY : CMakeFiles\Remesher.dir\src\main.cpp.obj.requires

CMakeFiles\Remesher.dir\src\main.cpp.obj.provides: CMakeFiles\Remesher.dir\src\main.cpp.obj.requires
	$(MAKE) -f CMakeFiles\Remesher.dir\build.make /nologo -$(MAKEFLAGS) CMakeFiles\Remesher.dir\src\main.cpp.obj.provides.build
.PHONY : CMakeFiles\Remesher.dir\src\main.cpp.obj.provides

CMakeFiles\Remesher.dir\src\main.cpp.obj.provides.build: CMakeFiles\Remesher.dir\src\main.cpp.obj


CMakeFiles\Remesher.dir\external\halfedge\trimesh.cpp.obj: CMakeFiles\Remesher.dir\flags.make
CMakeFiles\Remesher.dir\external\halfedge\trimesh.cpp.obj: ..\external\halfedge\trimesh.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=S:\Benfclark\Documents\GitHub\remeshing_project\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Remesher.dir/external/halfedge/trimesh.cpp.obj"
	C:\PROGRA~2\MIB055~1\2017\COMMUN~1\VC\Tools\MSVC\1414~1.264\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Remesher.dir\external\halfedge\trimesh.cpp.obj /FdCMakeFiles\Remesher.dir\ /FS -c S:\Benfclark\Documents\GitHub\remeshing_project\external\halfedge\trimesh.cpp
<<

CMakeFiles\Remesher.dir\external\halfedge\trimesh.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Remesher.dir/external/halfedge/trimesh.cpp.i"
	C:\PROGRA~2\MIB055~1\2017\COMMUN~1\VC\Tools\MSVC\1414~1.264\bin\Hostx86\x86\cl.exe > CMakeFiles\Remesher.dir\external\halfedge\trimesh.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E S:\Benfclark\Documents\GitHub\remeshing_project\external\halfedge\trimesh.cpp
<<

CMakeFiles\Remesher.dir\external\halfedge\trimesh.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Remesher.dir/external/halfedge/trimesh.cpp.s"
	C:\PROGRA~2\MIB055~1\2017\COMMUN~1\VC\Tools\MSVC\1414~1.264\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Remesher.dir\external\halfedge\trimesh.cpp.s /c S:\Benfclark\Documents\GitHub\remeshing_project\external\halfedge\trimesh.cpp
<<

CMakeFiles\Remesher.dir\external\halfedge\trimesh.cpp.obj.requires:

.PHONY : CMakeFiles\Remesher.dir\external\halfedge\trimesh.cpp.obj.requires

CMakeFiles\Remesher.dir\external\halfedge\trimesh.cpp.obj.provides: CMakeFiles\Remesher.dir\external\halfedge\trimesh.cpp.obj.requires
	$(MAKE) -f CMakeFiles\Remesher.dir\build.make /nologo -$(MAKEFLAGS) CMakeFiles\Remesher.dir\external\halfedge\trimesh.cpp.obj.provides.build
.PHONY : CMakeFiles\Remesher.dir\external\halfedge\trimesh.cpp.obj.provides

CMakeFiles\Remesher.dir\external\halfedge\trimesh.cpp.obj.provides.build: CMakeFiles\Remesher.dir\external\halfedge\trimesh.cpp.obj


CMakeFiles\Remesher.dir\src\meshMetrics.cpp.obj: CMakeFiles\Remesher.dir\flags.make
CMakeFiles\Remesher.dir\src\meshMetrics.cpp.obj: ..\src\meshMetrics.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=S:\Benfclark\Documents\GitHub\remeshing_project\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Remesher.dir/src/meshMetrics.cpp.obj"
	C:\PROGRA~2\MIB055~1\2017\COMMUN~1\VC\Tools\MSVC\1414~1.264\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Remesher.dir\src\meshMetrics.cpp.obj /FdCMakeFiles\Remesher.dir\ /FS -c S:\Benfclark\Documents\GitHub\remeshing_project\src\meshMetrics.cpp
<<

CMakeFiles\Remesher.dir\src\meshMetrics.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Remesher.dir/src/meshMetrics.cpp.i"
	C:\PROGRA~2\MIB055~1\2017\COMMUN~1\VC\Tools\MSVC\1414~1.264\bin\Hostx86\x86\cl.exe > CMakeFiles\Remesher.dir\src\meshMetrics.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E S:\Benfclark\Documents\GitHub\remeshing_project\src\meshMetrics.cpp
<<

CMakeFiles\Remesher.dir\src\meshMetrics.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Remesher.dir/src/meshMetrics.cpp.s"
	C:\PROGRA~2\MIB055~1\2017\COMMUN~1\VC\Tools\MSVC\1414~1.264\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Remesher.dir\src\meshMetrics.cpp.s /c S:\Benfclark\Documents\GitHub\remeshing_project\src\meshMetrics.cpp
<<

CMakeFiles\Remesher.dir\src\meshMetrics.cpp.obj.requires:

.PHONY : CMakeFiles\Remesher.dir\src\meshMetrics.cpp.obj.requires

CMakeFiles\Remesher.dir\src\meshMetrics.cpp.obj.provides: CMakeFiles\Remesher.dir\src\meshMetrics.cpp.obj.requires
	$(MAKE) -f CMakeFiles\Remesher.dir\build.make /nologo -$(MAKEFLAGS) CMakeFiles\Remesher.dir\src\meshMetrics.cpp.obj.provides.build
.PHONY : CMakeFiles\Remesher.dir\src\meshMetrics.cpp.obj.provides

CMakeFiles\Remesher.dir\src\meshMetrics.cpp.obj.provides.build: CMakeFiles\Remesher.dir\src\meshMetrics.cpp.obj


# Object files for target Remesher
Remesher_OBJECTS = \
"CMakeFiles\Remesher.dir\src\main.cpp.obj" \
"CMakeFiles\Remesher.dir\external\halfedge\trimesh.cpp.obj" \
"CMakeFiles\Remesher.dir\src\meshMetrics.cpp.obj"

# External object files for target Remesher
Remesher_EXTERNAL_OBJECTS =

Remesher.exe: CMakeFiles\Remesher.dir\src\main.cpp.obj
Remesher.exe: CMakeFiles\Remesher.dir\external\halfedge\trimesh.cpp.obj
Remesher.exe: CMakeFiles\Remesher.dir\src\meshMetrics.cpp.obj
Remesher.exe: CMakeFiles\Remesher.dir\build.make
Remesher.exe: CMakeFiles\Remesher.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=S:\Benfclark\Documents\GitHub\remeshing_project\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable Remesher.exe"
	"C:\Program Files\JetBrains\CLion 2018.1.2\bin\cmake\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\Remesher.dir --manifests  -- C:\PROGRA~2\MIB055~1\2017\COMMUN~1\VC\Tools\MSVC\1414~1.264\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\Remesher.dir\objects1.rsp @<<
 /out:Remesher.exe /implib:Remesher.lib /pdb:S:\Benfclark\Documents\GitHub\remeshing_project\cmake-build-debug\Remesher.pdb /version:0.0  /machine:X86 /debug /INCREMENTAL /subsystem:console ../external/glew_2_1_0/lib/Release/Win32/glew32s.lib ../external/glfw/lib-vc2015/glfw3.lib ../external/openGL/OPENGL32.lib ../external/openGL/glut32.lib ../external/openGL/glu32.lib ../external/CGAL_4_12/lib/CGAL_Core-vc140-mt-4.12.lib kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\Remesher.dir\build: Remesher.exe

.PHONY : CMakeFiles\Remesher.dir\build

CMakeFiles\Remesher.dir\requires: CMakeFiles\Remesher.dir\src\main.cpp.obj.requires
CMakeFiles\Remesher.dir\requires: CMakeFiles\Remesher.dir\external\halfedge\trimesh.cpp.obj.requires
CMakeFiles\Remesher.dir\requires: CMakeFiles\Remesher.dir\src\meshMetrics.cpp.obj.requires

.PHONY : CMakeFiles\Remesher.dir\requires

CMakeFiles\Remesher.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Remesher.dir\cmake_clean.cmake
.PHONY : CMakeFiles\Remesher.dir\clean

CMakeFiles\Remesher.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" S:\Benfclark\Documents\GitHub\remeshing_project S:\Benfclark\Documents\GitHub\remeshing_project S:\Benfclark\Documents\GitHub\remeshing_project\cmake-build-debug S:\Benfclark\Documents\GitHub\remeshing_project\cmake-build-debug S:\Benfclark\Documents\GitHub\remeshing_project\cmake-build-debug\CMakeFiles\Remesher.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\Remesher.dir\depend

