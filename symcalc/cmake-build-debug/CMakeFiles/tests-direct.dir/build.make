# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/minimumtanaku/Documents/GitHub/C_projects/symcalc

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/minimumtanaku/Documents/GitHub/C_projects/symcalc/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/tests-direct.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tests-direct.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tests-direct.dir/flags.make

CMakeFiles/tests-direct.dir/tokenizer.cpp.o: CMakeFiles/tests-direct.dir/flags.make
CMakeFiles/tests-direct.dir/tokenizer.cpp.o: ../tokenizer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/minimumtanaku/Documents/GitHub/C_projects/symcalc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/tests-direct.dir/tokenizer.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tests-direct.dir/tokenizer.cpp.o -c /Users/minimumtanaku/Documents/GitHub/C_projects/symcalc/tokenizer.cpp

CMakeFiles/tests-direct.dir/tokenizer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tests-direct.dir/tokenizer.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/minimumtanaku/Documents/GitHub/C_projects/symcalc/tokenizer.cpp > CMakeFiles/tests-direct.dir/tokenizer.cpp.i

CMakeFiles/tests-direct.dir/tokenizer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tests-direct.dir/tokenizer.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/minimumtanaku/Documents/GitHub/C_projects/symcalc/tokenizer.cpp -o CMakeFiles/tests-direct.dir/tokenizer.cpp.s

CMakeFiles/tests-direct.dir/cmdline.cpp.o: CMakeFiles/tests-direct.dir/flags.make
CMakeFiles/tests-direct.dir/cmdline.cpp.o: ../cmdline.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/minimumtanaku/Documents/GitHub/C_projects/symcalc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/tests-direct.dir/cmdline.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tests-direct.dir/cmdline.cpp.o -c /Users/minimumtanaku/Documents/GitHub/C_projects/symcalc/cmdline.cpp

CMakeFiles/tests-direct.dir/cmdline.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tests-direct.dir/cmdline.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/minimumtanaku/Documents/GitHub/C_projects/symcalc/cmdline.cpp > CMakeFiles/tests-direct.dir/cmdline.cpp.i

CMakeFiles/tests-direct.dir/cmdline.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tests-direct.dir/cmdline.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/minimumtanaku/Documents/GitHub/C_projects/symcalc/cmdline.cpp -o CMakeFiles/tests-direct.dir/cmdline.cpp.s

CMakeFiles/tests-direct.dir/expr.cpp.o: CMakeFiles/tests-direct.dir/flags.make
CMakeFiles/tests-direct.dir/expr.cpp.o: ../expr.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/minimumtanaku/Documents/GitHub/C_projects/symcalc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/tests-direct.dir/expr.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tests-direct.dir/expr.cpp.o -c /Users/minimumtanaku/Documents/GitHub/C_projects/symcalc/expr.cpp

CMakeFiles/tests-direct.dir/expr.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tests-direct.dir/expr.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/minimumtanaku/Documents/GitHub/C_projects/symcalc/expr.cpp > CMakeFiles/tests-direct.dir/expr.cpp.i

CMakeFiles/tests-direct.dir/expr.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tests-direct.dir/expr.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/minimumtanaku/Documents/GitHub/C_projects/symcalc/expr.cpp -o CMakeFiles/tests-direct.dir/expr.cpp.s

CMakeFiles/tests-direct.dir/expr_impl.cpp.o: CMakeFiles/tests-direct.dir/flags.make
CMakeFiles/tests-direct.dir/expr_impl.cpp.o: ../expr_impl.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/minimumtanaku/Documents/GitHub/C_projects/symcalc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/tests-direct.dir/expr_impl.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tests-direct.dir/expr_impl.cpp.o -c /Users/minimumtanaku/Documents/GitHub/C_projects/symcalc/expr_impl.cpp

CMakeFiles/tests-direct.dir/expr_impl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tests-direct.dir/expr_impl.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/minimumtanaku/Documents/GitHub/C_projects/symcalc/expr_impl.cpp > CMakeFiles/tests-direct.dir/expr_impl.cpp.i

CMakeFiles/tests-direct.dir/expr_impl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tests-direct.dir/expr_impl.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/minimumtanaku/Documents/GitHub/C_projects/symcalc/expr_impl.cpp -o CMakeFiles/tests-direct.dir/expr_impl.cpp.s

CMakeFiles/tests-direct.dir/app.cpp.o: CMakeFiles/tests-direct.dir/flags.make
CMakeFiles/tests-direct.dir/app.cpp.o: ../app.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/minimumtanaku/Documents/GitHub/C_projects/symcalc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/tests-direct.dir/app.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tests-direct.dir/app.cpp.o -c /Users/minimumtanaku/Documents/GitHub/C_projects/symcalc/app.cpp

CMakeFiles/tests-direct.dir/app.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tests-direct.dir/app.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/minimumtanaku/Documents/GitHub/C_projects/symcalc/app.cpp > CMakeFiles/tests-direct.dir/app.cpp.i

CMakeFiles/tests-direct.dir/app.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tests-direct.dir/app.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/minimumtanaku/Documents/GitHub/C_projects/symcalc/app.cpp -o CMakeFiles/tests-direct.dir/app.cpp.s

CMakeFiles/tests-direct.dir/tests/tests-main.cpp.o: CMakeFiles/tests-direct.dir/flags.make
CMakeFiles/tests-direct.dir/tests/tests-main.cpp.o: ../tests/tests-main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/minimumtanaku/Documents/GitHub/C_projects/symcalc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/tests-direct.dir/tests/tests-main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tests-direct.dir/tests/tests-main.cpp.o -c /Users/minimumtanaku/Documents/GitHub/C_projects/symcalc/tests/tests-main.cpp

CMakeFiles/tests-direct.dir/tests/tests-main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tests-direct.dir/tests/tests-main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/minimumtanaku/Documents/GitHub/C_projects/symcalc/tests/tests-main.cpp > CMakeFiles/tests-direct.dir/tests/tests-main.cpp.i

CMakeFiles/tests-direct.dir/tests/tests-main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tests-direct.dir/tests/tests-main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/minimumtanaku/Documents/GitHub/C_projects/symcalc/tests/tests-main.cpp -o CMakeFiles/tests-direct.dir/tests/tests-main.cpp.s

CMakeFiles/tests-direct.dir/tests/tests-tokenizer.cpp.o: CMakeFiles/tests-direct.dir/flags.make
CMakeFiles/tests-direct.dir/tests/tests-tokenizer.cpp.o: ../tests/tests-tokenizer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/minimumtanaku/Documents/GitHub/C_projects/symcalc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/tests-direct.dir/tests/tests-tokenizer.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tests-direct.dir/tests/tests-tokenizer.cpp.o -c /Users/minimumtanaku/Documents/GitHub/C_projects/symcalc/tests/tests-tokenizer.cpp

CMakeFiles/tests-direct.dir/tests/tests-tokenizer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tests-direct.dir/tests/tests-tokenizer.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/minimumtanaku/Documents/GitHub/C_projects/symcalc/tests/tests-tokenizer.cpp > CMakeFiles/tests-direct.dir/tests/tests-tokenizer.cpp.i

CMakeFiles/tests-direct.dir/tests/tests-tokenizer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tests-direct.dir/tests/tests-tokenizer.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/minimumtanaku/Documents/GitHub/C_projects/symcalc/tests/tests-tokenizer.cpp -o CMakeFiles/tests-direct.dir/tests/tests-tokenizer.cpp.s

CMakeFiles/tests-direct.dir/tests/tests-cmdline.cpp.o: CMakeFiles/tests-direct.dir/flags.make
CMakeFiles/tests-direct.dir/tests/tests-cmdline.cpp.o: ../tests/tests-cmdline.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/minimumtanaku/Documents/GitHub/C_projects/symcalc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/tests-direct.dir/tests/tests-cmdline.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tests-direct.dir/tests/tests-cmdline.cpp.o -c /Users/minimumtanaku/Documents/GitHub/C_projects/symcalc/tests/tests-cmdline.cpp

CMakeFiles/tests-direct.dir/tests/tests-cmdline.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tests-direct.dir/tests/tests-cmdline.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/minimumtanaku/Documents/GitHub/C_projects/symcalc/tests/tests-cmdline.cpp > CMakeFiles/tests-direct.dir/tests/tests-cmdline.cpp.i

CMakeFiles/tests-direct.dir/tests/tests-cmdline.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tests-direct.dir/tests/tests-cmdline.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/minimumtanaku/Documents/GitHub/C_projects/symcalc/tests/tests-cmdline.cpp -o CMakeFiles/tests-direct.dir/tests/tests-cmdline.cpp.s

CMakeFiles/tests-direct.dir/tests/tests-expr.cpp.o: CMakeFiles/tests-direct.dir/flags.make
CMakeFiles/tests-direct.dir/tests/tests-expr.cpp.o: ../tests/tests-expr.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/minimumtanaku/Documents/GitHub/C_projects/symcalc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/tests-direct.dir/tests/tests-expr.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tests-direct.dir/tests/tests-expr.cpp.o -c /Users/minimumtanaku/Documents/GitHub/C_projects/symcalc/tests/tests-expr.cpp

CMakeFiles/tests-direct.dir/tests/tests-expr.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tests-direct.dir/tests/tests-expr.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/minimumtanaku/Documents/GitHub/C_projects/symcalc/tests/tests-expr.cpp > CMakeFiles/tests-direct.dir/tests/tests-expr.cpp.i

CMakeFiles/tests-direct.dir/tests/tests-expr.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tests-direct.dir/tests/tests-expr.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/minimumtanaku/Documents/GitHub/C_projects/symcalc/tests/tests-expr.cpp -o CMakeFiles/tests-direct.dir/tests/tests-expr.cpp.s

CMakeFiles/tests-direct.dir/tests/tests-utils.cpp.o: CMakeFiles/tests-direct.dir/flags.make
CMakeFiles/tests-direct.dir/tests/tests-utils.cpp.o: ../tests/tests-utils.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/minimumtanaku/Documents/GitHub/C_projects/symcalc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/tests-direct.dir/tests/tests-utils.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tests-direct.dir/tests/tests-utils.cpp.o -c /Users/minimumtanaku/Documents/GitHub/C_projects/symcalc/tests/tests-utils.cpp

CMakeFiles/tests-direct.dir/tests/tests-utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tests-direct.dir/tests/tests-utils.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/minimumtanaku/Documents/GitHub/C_projects/symcalc/tests/tests-utils.cpp > CMakeFiles/tests-direct.dir/tests/tests-utils.cpp.i

CMakeFiles/tests-direct.dir/tests/tests-utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tests-direct.dir/tests/tests-utils.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/minimumtanaku/Documents/GitHub/C_projects/symcalc/tests/tests-utils.cpp -o CMakeFiles/tests-direct.dir/tests/tests-utils.cpp.s

# Object files for target tests-direct
tests__direct_OBJECTS = \
"CMakeFiles/tests-direct.dir/tokenizer.cpp.o" \
"CMakeFiles/tests-direct.dir/cmdline.cpp.o" \
"CMakeFiles/tests-direct.dir/expr.cpp.o" \
"CMakeFiles/tests-direct.dir/expr_impl.cpp.o" \
"CMakeFiles/tests-direct.dir/app.cpp.o" \
"CMakeFiles/tests-direct.dir/tests/tests-main.cpp.o" \
"CMakeFiles/tests-direct.dir/tests/tests-tokenizer.cpp.o" \
"CMakeFiles/tests-direct.dir/tests/tests-cmdline.cpp.o" \
"CMakeFiles/tests-direct.dir/tests/tests-expr.cpp.o" \
"CMakeFiles/tests-direct.dir/tests/tests-utils.cpp.o"

# External object files for target tests-direct
tests__direct_EXTERNAL_OBJECTS =

tests-direct: CMakeFiles/tests-direct.dir/tokenizer.cpp.o
tests-direct: CMakeFiles/tests-direct.dir/cmdline.cpp.o
tests-direct: CMakeFiles/tests-direct.dir/expr.cpp.o
tests-direct: CMakeFiles/tests-direct.dir/expr_impl.cpp.o
tests-direct: CMakeFiles/tests-direct.dir/app.cpp.o
tests-direct: CMakeFiles/tests-direct.dir/tests/tests-main.cpp.o
tests-direct: CMakeFiles/tests-direct.dir/tests/tests-tokenizer.cpp.o
tests-direct: CMakeFiles/tests-direct.dir/tests/tests-cmdline.cpp.o
tests-direct: CMakeFiles/tests-direct.dir/tests/tests-expr.cpp.o
tests-direct: CMakeFiles/tests-direct.dir/tests/tests-utils.cpp.o
tests-direct: CMakeFiles/tests-direct.dir/build.make
tests-direct: CMakeFiles/tests-direct.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/minimumtanaku/Documents/GitHub/C_projects/symcalc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX executable tests-direct"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tests-direct.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tests-direct.dir/build: tests-direct

.PHONY : CMakeFiles/tests-direct.dir/build

CMakeFiles/tests-direct.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tests-direct.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tests-direct.dir/clean

CMakeFiles/tests-direct.dir/depend:
	cd /Users/minimumtanaku/Documents/GitHub/C_projects/symcalc/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/minimumtanaku/Documents/GitHub/C_projects/symcalc /Users/minimumtanaku/Documents/GitHub/C_projects/symcalc /Users/minimumtanaku/Documents/GitHub/C_projects/symcalc/cmake-build-debug /Users/minimumtanaku/Documents/GitHub/C_projects/symcalc/cmake-build-debug /Users/minimumtanaku/Documents/GitHub/C_projects/symcalc/cmake-build-debug/CMakeFiles/tests-direct.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tests-direct.dir/depend

