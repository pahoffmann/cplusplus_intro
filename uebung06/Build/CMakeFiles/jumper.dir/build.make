# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/patrick/UniOsnabrück/c++/C06/uebung06

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/patrick/UniOsnabrück/c++/C06/uebung06/Build

# Include any dependencies generated for this target.
include CMakeFiles/jumper.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/jumper.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/jumper.dir/flags.make

CMakeFiles/jumper.dir/src/MainWindow.cc.o: CMakeFiles/jumper.dir/flags.make
CMakeFiles/jumper.dir/src/MainWindow.cc.o: ../src/MainWindow.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/patrick/UniOsnabrück/c++/C06/uebung06/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/jumper.dir/src/MainWindow.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/jumper.dir/src/MainWindow.cc.o -c /home/patrick/UniOsnabrück/c++/C06/uebung06/src/MainWindow.cc

CMakeFiles/jumper.dir/src/MainWindow.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jumper.dir/src/MainWindow.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/patrick/UniOsnabrück/c++/C06/uebung06/src/MainWindow.cc > CMakeFiles/jumper.dir/src/MainWindow.cc.i

CMakeFiles/jumper.dir/src/MainWindow.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jumper.dir/src/MainWindow.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/patrick/UniOsnabrück/c++/C06/uebung06/src/MainWindow.cc -o CMakeFiles/jumper.dir/src/MainWindow.cc.s

CMakeFiles/jumper.dir/src/MainWindow.cc.o.requires:

.PHONY : CMakeFiles/jumper.dir/src/MainWindow.cc.o.requires

CMakeFiles/jumper.dir/src/MainWindow.cc.o.provides: CMakeFiles/jumper.dir/src/MainWindow.cc.o.requires
	$(MAKE) -f CMakeFiles/jumper.dir/build.make CMakeFiles/jumper.dir/src/MainWindow.cc.o.provides.build
.PHONY : CMakeFiles/jumper.dir/src/MainWindow.cc.o.provides

CMakeFiles/jumper.dir/src/MainWindow.cc.o.provides.build: CMakeFiles/jumper.dir/src/MainWindow.cc.o


CMakeFiles/jumper.dir/src/Main.cpp.o: CMakeFiles/jumper.dir/flags.make
CMakeFiles/jumper.dir/src/Main.cpp.o: ../src/Main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/patrick/UniOsnabrück/c++/C06/uebung06/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/jumper.dir/src/Main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/jumper.dir/src/Main.cpp.o -c /home/patrick/UniOsnabrück/c++/C06/uebung06/src/Main.cpp

CMakeFiles/jumper.dir/src/Main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jumper.dir/src/Main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/patrick/UniOsnabrück/c++/C06/uebung06/src/Main.cpp > CMakeFiles/jumper.dir/src/Main.cpp.i

CMakeFiles/jumper.dir/src/Main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jumper.dir/src/Main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/patrick/UniOsnabrück/c++/C06/uebung06/src/Main.cpp -o CMakeFiles/jumper.dir/src/Main.cpp.s

CMakeFiles/jumper.dir/src/Main.cpp.o.requires:

.PHONY : CMakeFiles/jumper.dir/src/Main.cpp.o.requires

CMakeFiles/jumper.dir/src/Main.cpp.o.provides: CMakeFiles/jumper.dir/src/Main.cpp.o.requires
	$(MAKE) -f CMakeFiles/jumper.dir/build.make CMakeFiles/jumper.dir/src/Main.cpp.o.provides.build
.PHONY : CMakeFiles/jumper.dir/src/Main.cpp.o.provides

CMakeFiles/jumper.dir/src/Main.cpp.o.provides.build: CMakeFiles/jumper.dir/src/Main.cpp.o


CMakeFiles/jumper.dir/src/Level.cc.o: CMakeFiles/jumper.dir/flags.make
CMakeFiles/jumper.dir/src/Level.cc.o: ../src/Level.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/patrick/UniOsnabrück/c++/C06/uebung06/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/jumper.dir/src/Level.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/jumper.dir/src/Level.cc.o -c /home/patrick/UniOsnabrück/c++/C06/uebung06/src/Level.cc

CMakeFiles/jumper.dir/src/Level.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jumper.dir/src/Level.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/patrick/UniOsnabrück/c++/C06/uebung06/src/Level.cc > CMakeFiles/jumper.dir/src/Level.cc.i

CMakeFiles/jumper.dir/src/Level.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jumper.dir/src/Level.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/patrick/UniOsnabrück/c++/C06/uebung06/src/Level.cc -o CMakeFiles/jumper.dir/src/Level.cc.s

CMakeFiles/jumper.dir/src/Level.cc.o.requires:

.PHONY : CMakeFiles/jumper.dir/src/Level.cc.o.requires

CMakeFiles/jumper.dir/src/Level.cc.o.provides: CMakeFiles/jumper.dir/src/Level.cc.o.requires
	$(MAKE) -f CMakeFiles/jumper.dir/build.make CMakeFiles/jumper.dir/src/Level.cc.o.provides.build
.PHONY : CMakeFiles/jumper.dir/src/Level.cc.o.provides

CMakeFiles/jumper.dir/src/Level.cc.o.provides.build: CMakeFiles/jumper.dir/src/Level.cc.o


CMakeFiles/jumper.dir/src/Camera.cc.o: CMakeFiles/jumper.dir/flags.make
CMakeFiles/jumper.dir/src/Camera.cc.o: ../src/Camera.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/patrick/UniOsnabrück/c++/C06/uebung06/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/jumper.dir/src/Camera.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/jumper.dir/src/Camera.cc.o -c /home/patrick/UniOsnabrück/c++/C06/uebung06/src/Camera.cc

CMakeFiles/jumper.dir/src/Camera.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jumper.dir/src/Camera.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/patrick/UniOsnabrück/c++/C06/uebung06/src/Camera.cc > CMakeFiles/jumper.dir/src/Camera.cc.i

CMakeFiles/jumper.dir/src/Camera.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jumper.dir/src/Camera.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/patrick/UniOsnabrück/c++/C06/uebung06/src/Camera.cc -o CMakeFiles/jumper.dir/src/Camera.cc.s

CMakeFiles/jumper.dir/src/Camera.cc.o.requires:

.PHONY : CMakeFiles/jumper.dir/src/Camera.cc.o.requires

CMakeFiles/jumper.dir/src/Camera.cc.o.provides: CMakeFiles/jumper.dir/src/Camera.cc.o.requires
	$(MAKE) -f CMakeFiles/jumper.dir/build.make CMakeFiles/jumper.dir/src/Camera.cc.o.provides.build
.PHONY : CMakeFiles/jumper.dir/src/Camera.cc.o.provides

CMakeFiles/jumper.dir/src/Camera.cc.o.provides.build: CMakeFiles/jumper.dir/src/Camera.cc.o


# Object files for target jumper
jumper_OBJECTS = \
"CMakeFiles/jumper.dir/src/MainWindow.cc.o" \
"CMakeFiles/jumper.dir/src/Main.cpp.o" \
"CMakeFiles/jumper.dir/src/Level.cc.o" \
"CMakeFiles/jumper.dir/src/Camera.cc.o"

# External object files for target jumper
jumper_EXTERNAL_OBJECTS =

jumper: CMakeFiles/jumper.dir/src/MainWindow.cc.o
jumper: CMakeFiles/jumper.dir/src/Main.cpp.o
jumper: CMakeFiles/jumper.dir/src/Level.cc.o
jumper: CMakeFiles/jumper.dir/src/Camera.cc.o
jumper: CMakeFiles/jumper.dir/build.make
jumper: /usr/lib/x86_64-linux-gnu/libSDL2main.a
jumper: /usr/lib/x86_64-linux-gnu/libSDL2.so
jumper: /usr/lib/x86_64-linux-gnu/libSDL2_image.so
jumper: /usr/lib/x86_64-linux-gnu/libSDL2_image.so
jumper: CMakeFiles/jumper.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/patrick/UniOsnabrück/c++/C06/uebung06/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable jumper"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/jumper.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/jumper.dir/build: jumper

.PHONY : CMakeFiles/jumper.dir/build

CMakeFiles/jumper.dir/requires: CMakeFiles/jumper.dir/src/MainWindow.cc.o.requires
CMakeFiles/jumper.dir/requires: CMakeFiles/jumper.dir/src/Main.cpp.o.requires
CMakeFiles/jumper.dir/requires: CMakeFiles/jumper.dir/src/Level.cc.o.requires
CMakeFiles/jumper.dir/requires: CMakeFiles/jumper.dir/src/Camera.cc.o.requires

.PHONY : CMakeFiles/jumper.dir/requires

CMakeFiles/jumper.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/jumper.dir/cmake_clean.cmake
.PHONY : CMakeFiles/jumper.dir/clean

CMakeFiles/jumper.dir/depend:
	cd /home/patrick/UniOsnabrück/c++/C06/uebung06/Build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/patrick/UniOsnabrück/c++/C06/uebung06 /home/patrick/UniOsnabrück/c++/C06/uebung06 /home/patrick/UniOsnabrück/c++/C06/uebung06/Build /home/patrick/UniOsnabrück/c++/C06/uebung06/Build /home/patrick/UniOsnabrück/c++/C06/uebung06/Build/CMakeFiles/jumper.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/jumper.dir/depend

