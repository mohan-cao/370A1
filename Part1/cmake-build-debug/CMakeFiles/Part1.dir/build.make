# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/newbee/Desktop/370A1/Part1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/newbee/Desktop/370A1/Part1/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Part1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Part1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Part1.dir/flags.make

CMakeFiles/Part1.dir/OSA1.1.c.o: CMakeFiles/Part1.dir/flags.make
CMakeFiles/Part1.dir/OSA1.1.c.o: ../OSA1.1.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/newbee/Desktop/370A1/Part1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Part1.dir/OSA1.1.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Part1.dir/OSA1.1.c.o   -c /Users/newbee/Desktop/370A1/Part1/OSA1.1.c

CMakeFiles/Part1.dir/OSA1.1.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Part1.dir/OSA1.1.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/newbee/Desktop/370A1/Part1/OSA1.1.c > CMakeFiles/Part1.dir/OSA1.1.c.i

CMakeFiles/Part1.dir/OSA1.1.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Part1.dir/OSA1.1.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/newbee/Desktop/370A1/Part1/OSA1.1.c -o CMakeFiles/Part1.dir/OSA1.1.c.s

CMakeFiles/Part1.dir/OSA1.1.c.o.requires:

.PHONY : CMakeFiles/Part1.dir/OSA1.1.c.o.requires

CMakeFiles/Part1.dir/OSA1.1.c.o.provides: CMakeFiles/Part1.dir/OSA1.1.c.o.requires
	$(MAKE) -f CMakeFiles/Part1.dir/build.make CMakeFiles/Part1.dir/OSA1.1.c.o.provides.build
.PHONY : CMakeFiles/Part1.dir/OSA1.1.c.o.provides

CMakeFiles/Part1.dir/OSA1.1.c.o.provides.build: CMakeFiles/Part1.dir/OSA1.1.c.o


# Object files for target Part1
Part1_OBJECTS = \
"CMakeFiles/Part1.dir/OSA1.1.c.o"

# External object files for target Part1
Part1_EXTERNAL_OBJECTS =

Part1: CMakeFiles/Part1.dir/OSA1.1.c.o
Part1: CMakeFiles/Part1.dir/build.make
Part1: CMakeFiles/Part1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/newbee/Desktop/370A1/Part1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Part1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Part1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Part1.dir/build: Part1

.PHONY : CMakeFiles/Part1.dir/build

CMakeFiles/Part1.dir/requires: CMakeFiles/Part1.dir/OSA1.1.c.o.requires

.PHONY : CMakeFiles/Part1.dir/requires

CMakeFiles/Part1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Part1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Part1.dir/clean

CMakeFiles/Part1.dir/depend:
	cd /Users/newbee/Desktop/370A1/Part1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/newbee/Desktop/370A1/Part1 /Users/newbee/Desktop/370A1/Part1 /Users/newbee/Desktop/370A1/Part1/cmake-build-debug /Users/newbee/Desktop/370A1/Part1/cmake-build-debug /Users/newbee/Desktop/370A1/Part1/cmake-build-debug/CMakeFiles/Part1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Part1.dir/depend
