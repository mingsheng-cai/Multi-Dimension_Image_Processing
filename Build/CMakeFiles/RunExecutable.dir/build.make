# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.28.3/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.28.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/mscai/Desktop/advanced-programming-group-radix-sort

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/mscai/Desktop/advanced-programming-group-radix-sort/Build

# Include any dependencies generated for this target.
include CMakeFiles/RunExecutable.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/RunExecutable.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/RunExecutable.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/RunExecutable.dir/flags.make

CMakeFiles/RunExecutable.dir/Source/main.cpp.o: CMakeFiles/RunExecutable.dir/flags.make
CMakeFiles/RunExecutable.dir/Source/main.cpp.o: /Users/mscai/Desktop/advanced-programming-group-radix-sort/Source/main.cpp
CMakeFiles/RunExecutable.dir/Source/main.cpp.o: CMakeFiles/RunExecutable.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/mscai/Desktop/advanced-programming-group-radix-sort/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/RunExecutable.dir/Source/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/RunExecutable.dir/Source/main.cpp.o -MF CMakeFiles/RunExecutable.dir/Source/main.cpp.o.d -o CMakeFiles/RunExecutable.dir/Source/main.cpp.o -c /Users/mscai/Desktop/advanced-programming-group-radix-sort/Source/main.cpp

CMakeFiles/RunExecutable.dir/Source/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/RunExecutable.dir/Source/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mscai/Desktop/advanced-programming-group-radix-sort/Source/main.cpp > CMakeFiles/RunExecutable.dir/Source/main.cpp.i

CMakeFiles/RunExecutable.dir/Source/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/RunExecutable.dir/Source/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mscai/Desktop/advanced-programming-group-radix-sort/Source/main.cpp -o CMakeFiles/RunExecutable.dir/Source/main.cpp.s

# Object files for target RunExecutable
RunExecutable_OBJECTS = \
"CMakeFiles/RunExecutable.dir/Source/main.cpp.o"

# External object files for target RunExecutable
RunExecutable_EXTERNAL_OBJECTS =

RunExecutable: CMakeFiles/RunExecutable.dir/Source/main.cpp.o
RunExecutable: CMakeFiles/RunExecutable.dir/build.make
RunExecutable: Source/libcore_lib.a
RunExecutable: CMakeFiles/RunExecutable.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/mscai/Desktop/advanced-programming-group-radix-sort/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable RunExecutable"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/RunExecutable.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/RunExecutable.dir/build: RunExecutable
.PHONY : CMakeFiles/RunExecutable.dir/build

CMakeFiles/RunExecutable.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/RunExecutable.dir/cmake_clean.cmake
.PHONY : CMakeFiles/RunExecutable.dir/clean

CMakeFiles/RunExecutable.dir/depend:
	cd /Users/mscai/Desktop/advanced-programming-group-radix-sort/Build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/mscai/Desktop/advanced-programming-group-radix-sort /Users/mscai/Desktop/advanced-programming-group-radix-sort /Users/mscai/Desktop/advanced-programming-group-radix-sort/Build /Users/mscai/Desktop/advanced-programming-group-radix-sort/Build /Users/mscai/Desktop/advanced-programming-group-radix-sort/Build/CMakeFiles/RunExecutable.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/RunExecutable.dir/depend
