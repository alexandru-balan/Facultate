# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /home/alexandru-balan/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/191.7141.37/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/alexandru-balan/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/191.7141.37/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/alexandru-balan/CLionProjects/Grafuri

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alexandru-balan/CLionProjects/Grafuri/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Grafuri.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Grafuri.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Grafuri.dir/flags.make

CMakeFiles/Grafuri.dir/main.cpp.o: CMakeFiles/Grafuri.dir/flags.make
CMakeFiles/Grafuri.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alexandru-balan/CLionProjects/Grafuri/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Grafuri.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Grafuri.dir/main.cpp.o -c /home/alexandru-balan/CLionProjects/Grafuri/main.cpp

CMakeFiles/Grafuri.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Grafuri.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alexandru-balan/CLionProjects/Grafuri/main.cpp > CMakeFiles/Grafuri.dir/main.cpp.i

CMakeFiles/Grafuri.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Grafuri.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alexandru-balan/CLionProjects/Grafuri/main.cpp -o CMakeFiles/Grafuri.dir/main.cpp.s

# Object files for target Grafuri
Grafuri_OBJECTS = \
"CMakeFiles/Grafuri.dir/main.cpp.o"

# External object files for target Grafuri
Grafuri_EXTERNAL_OBJECTS =

Grafuri: CMakeFiles/Grafuri.dir/main.cpp.o
Grafuri: CMakeFiles/Grafuri.dir/build.make
Grafuri: CMakeFiles/Grafuri.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alexandru-balan/CLionProjects/Grafuri/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Grafuri"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Grafuri.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Grafuri.dir/build: Grafuri

.PHONY : CMakeFiles/Grafuri.dir/build

CMakeFiles/Grafuri.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Grafuri.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Grafuri.dir/clean

CMakeFiles/Grafuri.dir/depend:
	cd /home/alexandru-balan/CLionProjects/Grafuri/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alexandru-balan/CLionProjects/Grafuri /home/alexandru-balan/CLionProjects/Grafuri /home/alexandru-balan/CLionProjects/Grafuri/cmake-build-debug /home/alexandru-balan/CLionProjects/Grafuri/cmake-build-debug /home/alexandru-balan/CLionProjects/Grafuri/cmake-build-debug/CMakeFiles/Grafuri.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Grafuri.dir/depend

