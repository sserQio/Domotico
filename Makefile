# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

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
CMAKE_COMMAND = /opt/homebrew/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/sergio/Documents/Coding/Domotico

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/sergio/Documents/Coding/Domotico

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Running CMake cache editor..."
	/opt/homebrew/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Running CMake to regenerate build system..."
	/opt/homebrew/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/sergio/Documents/Coding/Domotico/CMakeFiles /Users/sergio/Documents/Coding/Domotico//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/sergio/Documents/Coding/Domotico/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named Domotico

# Build rule for target.
Domotico: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 Domotico
.PHONY : Domotico

# fast build rule for target.
Domotico/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Domotico.dir/build.make CMakeFiles/Domotico.dir/build
.PHONY : Domotico/fast

#=============================================================================
# Target rules for targets named main

# Build rule for target.
main: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 main
.PHONY : main

# fast build rule for target.
main/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/build
.PHONY : main/fast

src/cp.o: src/cp.cpp.o
.PHONY : src/cp.o

# target to build an object file
src/cp.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Domotico.dir/build.make CMakeFiles/Domotico.dir/src/cp.cpp.o
.PHONY : src/cp.cpp.o

src/cp.i: src/cp.cpp.i
.PHONY : src/cp.i

# target to preprocess a source file
src/cp.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Domotico.dir/build.make CMakeFiles/Domotico.dir/src/cp.cpp.i
.PHONY : src/cp.cpp.i

src/cp.s: src/cp.cpp.s
.PHONY : src/cp.s

# target to generate assembly for a file
src/cp.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Domotico.dir/build.make CMakeFiles/Domotico.dir/src/cp.cpp.s
.PHONY : src/cp.cpp.s

src/device.o: src/device.cpp.o
.PHONY : src/device.o

# target to build an object file
src/device.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Domotico.dir/build.make CMakeFiles/Domotico.dir/src/device.cpp.o
.PHONY : src/device.cpp.o

src/device.i: src/device.cpp.i
.PHONY : src/device.i

# target to preprocess a source file
src/device.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Domotico.dir/build.make CMakeFiles/Domotico.dir/src/device.cpp.i
.PHONY : src/device.cpp.i

src/device.s: src/device.cpp.s
.PHONY : src/device.s

# target to generate assembly for a file
src/device.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Domotico.dir/build.make CMakeFiles/Domotico.dir/src/device.cpp.s
.PHONY : src/device.cpp.s

src/m.o: src/m.cpp.o
.PHONY : src/m.o

# target to build an object file
src/m.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Domotico.dir/build.make CMakeFiles/Domotico.dir/src/m.cpp.o
.PHONY : src/m.cpp.o

src/m.i: src/m.cpp.i
.PHONY : src/m.i

# target to preprocess a source file
src/m.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Domotico.dir/build.make CMakeFiles/Domotico.dir/src/m.cpp.i
.PHONY : src/m.cpp.i

src/m.s: src/m.cpp.s
.PHONY : src/m.s

# target to generate assembly for a file
src/m.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Domotico.dir/build.make CMakeFiles/Domotico.dir/src/m.cpp.s
.PHONY : src/m.cpp.s

src/main.o: src/main.cpp.o
.PHONY : src/main.o

# target to build an object file
src/main.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/main.cpp.o
.PHONY : src/main.cpp.o

src/main.i: src/main.cpp.i
.PHONY : src/main.i

# target to preprocess a source file
src/main.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/main.cpp.i
.PHONY : src/main.cpp.i

src/main.s: src/main.cpp.s
.PHONY : src/main.s

# target to generate assembly for a file
src/main.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/main.cpp.s
.PHONY : src/main.cpp.s

src/system.o: src/system.cpp.o
.PHONY : src/system.o

# target to build an object file
src/system.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Domotico.dir/build.make CMakeFiles/Domotico.dir/src/system.cpp.o
.PHONY : src/system.cpp.o

src/system.i: src/system.cpp.i
.PHONY : src/system.i

# target to preprocess a source file
src/system.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Domotico.dir/build.make CMakeFiles/Domotico.dir/src/system.cpp.i
.PHONY : src/system.cpp.i

src/system.s: src/system.cpp.s
.PHONY : src/system.s

# target to generate assembly for a file
src/system.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Domotico.dir/build.make CMakeFiles/Domotico.dir/src/system.cpp.s
.PHONY : src/system.cpp.s

src/time.o: src/time.cpp.o
.PHONY : src/time.o

# target to build an object file
src/time.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Domotico.dir/build.make CMakeFiles/Domotico.dir/src/time.cpp.o
.PHONY : src/time.cpp.o

src/time.i: src/time.cpp.i
.PHONY : src/time.i

# target to preprocess a source file
src/time.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Domotico.dir/build.make CMakeFiles/Domotico.dir/src/time.cpp.i
.PHONY : src/time.cpp.i

src/time.s: src/time.cpp.s
.PHONY : src/time.s

# target to generate assembly for a file
src/time.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Domotico.dir/build.make CMakeFiles/Domotico.dir/src/time.cpp.s
.PHONY : src/time.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... Domotico"
	@echo "... main"
	@echo "... src/cp.o"
	@echo "... src/cp.i"
	@echo "... src/cp.s"
	@echo "... src/device.o"
	@echo "... src/device.i"
	@echo "... src/device.s"
	@echo "... src/m.o"
	@echo "... src/m.i"
	@echo "... src/m.s"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
	@echo "... src/system.o"
	@echo "... src/system.i"
	@echo "... src/system.s"
	@echo "... src/time.o"
	@echo "... src/time.i"
	@echo "... src/time.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

