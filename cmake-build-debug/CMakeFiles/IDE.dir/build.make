# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.26

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2023.2.2\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2023.2.2\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\mario\CLionProjects\IDE

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\mario\CLionProjects\IDE\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/IDE.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/IDE.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/IDE.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/IDE.dir/flags.make

CMakeFiles/IDE.dir/main.c.obj: CMakeFiles/IDE.dir/flags.make
CMakeFiles/IDE.dir/main.c.obj: C:/Users/mario/CLionProjects/IDE/main.c
CMakeFiles/IDE.dir/main.c.obj: CMakeFiles/IDE.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\mario\CLionProjects\IDE\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/IDE.dir/main.c.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/IDE.dir/main.c.obj -MF CMakeFiles\IDE.dir\main.c.obj.d -o CMakeFiles\IDE.dir\main.c.obj -c C:\Users\mario\CLionProjects\IDE\main.c

CMakeFiles/IDE.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/IDE.dir/main.c.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\mario\CLionProjects\IDE\main.c > CMakeFiles\IDE.dir\main.c.i

CMakeFiles/IDE.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/IDE.dir/main.c.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\mario\CLionProjects\IDE\main.c -o CMakeFiles\IDE.dir\main.c.s

# Object files for target IDE
IDE_OBJECTS = \
"CMakeFiles/IDE.dir/main.c.obj"

# External object files for target IDE
IDE_EXTERNAL_OBJECTS =

IDE.exe: CMakeFiles/IDE.dir/main.c.obj
IDE.exe: CMakeFiles/IDE.dir/build.make
IDE.exe: CMakeFiles/IDE.dir/linkLibs.rsp
IDE.exe: CMakeFiles/IDE.dir/objects1.rsp
IDE.exe: CMakeFiles/IDE.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\mario\CLionProjects\IDE\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable IDE.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\IDE.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/IDE.dir/build: IDE.exe
.PHONY : CMakeFiles/IDE.dir/build

CMakeFiles/IDE.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\IDE.dir\cmake_clean.cmake
.PHONY : CMakeFiles/IDE.dir/clean

CMakeFiles/IDE.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\mario\CLionProjects\IDE C:\Users\mario\CLionProjects\IDE C:\Users\mario\CLionProjects\IDE\cmake-build-debug C:\Users\mario\CLionProjects\IDE\cmake-build-debug C:\Users\mario\CLionProjects\IDE\cmake-build-debug\CMakeFiles\IDE.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/IDE.dir/depend

