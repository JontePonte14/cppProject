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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/EDAF50/cppProject/clientserver

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/EDAF50/cppProject/clientserver/build

# Include any dependencies generated for this target.
include example/CMakeFiles/myserver.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include example/CMakeFiles/myserver.dir/compiler_depend.make

# Include the progress variables for this target.
include example/CMakeFiles/myserver.dir/progress.make

# Include the compile flags for this target's objects.
include example/CMakeFiles/myserver.dir/flags.make

example/CMakeFiles/myserver.dir/myserver.cc.o: example/CMakeFiles/myserver.dir/flags.make
example/CMakeFiles/myserver.dir/myserver.cc.o: /root/EDAF50/cppProject/clientserver/example/myserver.cc
example/CMakeFiles/myserver.dir/myserver.cc.o: example/CMakeFiles/myserver.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/root/EDAF50/cppProject/clientserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object example/CMakeFiles/myserver.dir/myserver.cc.o"
	cd /root/EDAF50/cppProject/clientserver/build/example && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT example/CMakeFiles/myserver.dir/myserver.cc.o -MF CMakeFiles/myserver.dir/myserver.cc.o.d -o CMakeFiles/myserver.dir/myserver.cc.o -c /root/EDAF50/cppProject/clientserver/example/myserver.cc

example/CMakeFiles/myserver.dir/myserver.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/myserver.dir/myserver.cc.i"
	cd /root/EDAF50/cppProject/clientserver/build/example && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/EDAF50/cppProject/clientserver/example/myserver.cc > CMakeFiles/myserver.dir/myserver.cc.i

example/CMakeFiles/myserver.dir/myserver.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/myserver.dir/myserver.cc.s"
	cd /root/EDAF50/cppProject/clientserver/build/example && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/EDAF50/cppProject/clientserver/example/myserver.cc -o CMakeFiles/myserver.dir/myserver.cc.s

# Object files for target myserver
myserver_OBJECTS = \
"CMakeFiles/myserver.dir/myserver.cc.o"

# External object files for target myserver
myserver_EXTERNAL_OBJECTS =

example/myserver: example/CMakeFiles/myserver.dir/myserver.cc.o
example/myserver: example/CMakeFiles/myserver.dir/build.make
example/myserver: libclientserver.a
example/myserver: example/CMakeFiles/myserver.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/root/EDAF50/cppProject/clientserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable myserver"
	cd /root/EDAF50/cppProject/clientserver/build/example && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/myserver.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
example/CMakeFiles/myserver.dir/build: example/myserver
.PHONY : example/CMakeFiles/myserver.dir/build

example/CMakeFiles/myserver.dir/clean:
	cd /root/EDAF50/cppProject/clientserver/build/example && $(CMAKE_COMMAND) -P CMakeFiles/myserver.dir/cmake_clean.cmake
.PHONY : example/CMakeFiles/myserver.dir/clean

example/CMakeFiles/myserver.dir/depend:
	cd /root/EDAF50/cppProject/clientserver/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/EDAF50/cppProject/clientserver /root/EDAF50/cppProject/clientserver/example /root/EDAF50/cppProject/clientserver/build /root/EDAF50/cppProject/clientserver/build/example /root/EDAF50/cppProject/clientserver/build/example/CMakeFiles/myserver.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : example/CMakeFiles/myserver.dir/depend

