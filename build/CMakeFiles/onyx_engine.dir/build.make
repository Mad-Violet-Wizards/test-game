# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mateusz/Projects/onyx-engine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mateusz/Projects/onyx-engine/build

# Include any dependencies generated for this target.
include CMakeFiles/onyx_engine.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/onyx_engine.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/onyx_engine.dir/flags.make

CMakeFiles/onyx_engine.dir/src/main.cpp.o: CMakeFiles/onyx_engine.dir/flags.make
CMakeFiles/onyx_engine.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mateusz/Projects/onyx-engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/onyx_engine.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/onyx_engine.dir/src/main.cpp.o -c /home/mateusz/Projects/onyx-engine/src/main.cpp

CMakeFiles/onyx_engine.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/onyx_engine.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mateusz/Projects/onyx-engine/src/main.cpp > CMakeFiles/onyx_engine.dir/src/main.cpp.i

CMakeFiles/onyx_engine.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/onyx_engine.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mateusz/Projects/onyx-engine/src/main.cpp -o CMakeFiles/onyx_engine.dir/src/main.cpp.s

CMakeFiles/onyx_engine.dir/src/Time/DateTime.cpp.o: CMakeFiles/onyx_engine.dir/flags.make
CMakeFiles/onyx_engine.dir/src/Time/DateTime.cpp.o: ../src/Time/DateTime.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mateusz/Projects/onyx-engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/onyx_engine.dir/src/Time/DateTime.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/onyx_engine.dir/src/Time/DateTime.cpp.o -c /home/mateusz/Projects/onyx-engine/src/Time/DateTime.cpp

CMakeFiles/onyx_engine.dir/src/Time/DateTime.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/onyx_engine.dir/src/Time/DateTime.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mateusz/Projects/onyx-engine/src/Time/DateTime.cpp > CMakeFiles/onyx_engine.dir/src/Time/DateTime.cpp.i

CMakeFiles/onyx_engine.dir/src/Time/DateTime.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/onyx_engine.dir/src/Time/DateTime.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mateusz/Projects/onyx-engine/src/Time/DateTime.cpp -o CMakeFiles/onyx_engine.dir/src/Time/DateTime.cpp.s

# Object files for target onyx_engine
onyx_engine_OBJECTS = \
"CMakeFiles/onyx_engine.dir/src/main.cpp.o" \
"CMakeFiles/onyx_engine.dir/src/Time/DateTime.cpp.o"

# External object files for target onyx_engine
onyx_engine_EXTERNAL_OBJECTS =

onyx_engine: CMakeFiles/onyx_engine.dir/src/main.cpp.o
onyx_engine: CMakeFiles/onyx_engine.dir/src/Time/DateTime.cpp.o
onyx_engine: CMakeFiles/onyx_engine.dir/build.make
onyx_engine: ../lib/libsfml-graphics.so.2.5.1
onyx_engine: ../lib/libsfml-audio.so.2.5.1
onyx_engine: ../lib/libsfml-window.so.2.5.1
onyx_engine: ../lib/libsfml-system.so.2.5.1
onyx_engine: CMakeFiles/onyx_engine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mateusz/Projects/onyx-engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable onyx_engine"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/onyx_engine.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/onyx_engine.dir/build: onyx_engine

.PHONY : CMakeFiles/onyx_engine.dir/build

CMakeFiles/onyx_engine.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/onyx_engine.dir/cmake_clean.cmake
.PHONY : CMakeFiles/onyx_engine.dir/clean

CMakeFiles/onyx_engine.dir/depend:
	cd /home/mateusz/Projects/onyx-engine/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mateusz/Projects/onyx-engine /home/mateusz/Projects/onyx-engine /home/mateusz/Projects/onyx-engine/build /home/mateusz/Projects/onyx-engine/build /home/mateusz/Projects/onyx-engine/build/CMakeFiles/onyx_engine.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/onyx_engine.dir/depend

