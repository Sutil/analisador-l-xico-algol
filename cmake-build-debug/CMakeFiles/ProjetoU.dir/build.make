# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
CMAKE_COMMAND = /home/sutil/CLion/clion-2016.3.1/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/sutil/CLion/clion-2016.3.1/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sutil/ClionProjects/ProjetoU

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sutil/ClionProjects/ProjetoU/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ProjetoU.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ProjetoU.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ProjetoU.dir/flags.make

CMakeFiles/ProjetoU.dir/main.cpp.o: CMakeFiles/ProjetoU.dir/flags.make
CMakeFiles/ProjetoU.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sutil/ClionProjects/ProjetoU/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ProjetoU.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ProjetoU.dir/main.cpp.o -c /home/sutil/ClionProjects/ProjetoU/main.cpp

CMakeFiles/ProjetoU.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ProjetoU.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sutil/ClionProjects/ProjetoU/main.cpp > CMakeFiles/ProjetoU.dir/main.cpp.i

CMakeFiles/ProjetoU.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ProjetoU.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sutil/ClionProjects/ProjetoU/main.cpp -o CMakeFiles/ProjetoU.dir/main.cpp.s

CMakeFiles/ProjetoU.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/ProjetoU.dir/main.cpp.o.requires

CMakeFiles/ProjetoU.dir/main.cpp.o.provides: CMakeFiles/ProjetoU.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/ProjetoU.dir/build.make CMakeFiles/ProjetoU.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/ProjetoU.dir/main.cpp.o.provides

CMakeFiles/ProjetoU.dir/main.cpp.o.provides.build: CMakeFiles/ProjetoU.dir/main.cpp.o


CMakeFiles/ProjetoU.dir/tests/separadorTest.cpp.o: CMakeFiles/ProjetoU.dir/flags.make
CMakeFiles/ProjetoU.dir/tests/separadorTest.cpp.o: ../tests/separadorTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sutil/ClionProjects/ProjetoU/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ProjetoU.dir/tests/separadorTest.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ProjetoU.dir/tests/separadorTest.cpp.o -c /home/sutil/ClionProjects/ProjetoU/tests/separadorTest.cpp

CMakeFiles/ProjetoU.dir/tests/separadorTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ProjetoU.dir/tests/separadorTest.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sutil/ClionProjects/ProjetoU/tests/separadorTest.cpp > CMakeFiles/ProjetoU.dir/tests/separadorTest.cpp.i

CMakeFiles/ProjetoU.dir/tests/separadorTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ProjetoU.dir/tests/separadorTest.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sutil/ClionProjects/ProjetoU/tests/separadorTest.cpp -o CMakeFiles/ProjetoU.dir/tests/separadorTest.cpp.s

CMakeFiles/ProjetoU.dir/tests/separadorTest.cpp.o.requires:

.PHONY : CMakeFiles/ProjetoU.dir/tests/separadorTest.cpp.o.requires

CMakeFiles/ProjetoU.dir/tests/separadorTest.cpp.o.provides: CMakeFiles/ProjetoU.dir/tests/separadorTest.cpp.o.requires
	$(MAKE) -f CMakeFiles/ProjetoU.dir/build.make CMakeFiles/ProjetoU.dir/tests/separadorTest.cpp.o.provides.build
.PHONY : CMakeFiles/ProjetoU.dir/tests/separadorTest.cpp.o.provides

CMakeFiles/ProjetoU.dir/tests/separadorTest.cpp.o.provides.build: CMakeFiles/ProjetoU.dir/tests/separadorTest.cpp.o


CMakeFiles/ProjetoU.dir/sintatico/AnalisadorSintaticoMain.cpp.o: CMakeFiles/ProjetoU.dir/flags.make
CMakeFiles/ProjetoU.dir/sintatico/AnalisadorSintaticoMain.cpp.o: ../sintatico/AnalisadorSintaticoMain.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sutil/ClionProjects/ProjetoU/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/ProjetoU.dir/sintatico/AnalisadorSintaticoMain.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ProjetoU.dir/sintatico/AnalisadorSintaticoMain.cpp.o -c /home/sutil/ClionProjects/ProjetoU/sintatico/AnalisadorSintaticoMain.cpp

CMakeFiles/ProjetoU.dir/sintatico/AnalisadorSintaticoMain.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ProjetoU.dir/sintatico/AnalisadorSintaticoMain.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sutil/ClionProjects/ProjetoU/sintatico/AnalisadorSintaticoMain.cpp > CMakeFiles/ProjetoU.dir/sintatico/AnalisadorSintaticoMain.cpp.i

CMakeFiles/ProjetoU.dir/sintatico/AnalisadorSintaticoMain.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ProjetoU.dir/sintatico/AnalisadorSintaticoMain.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sutil/ClionProjects/ProjetoU/sintatico/AnalisadorSintaticoMain.cpp -o CMakeFiles/ProjetoU.dir/sintatico/AnalisadorSintaticoMain.cpp.s

CMakeFiles/ProjetoU.dir/sintatico/AnalisadorSintaticoMain.cpp.o.requires:

.PHONY : CMakeFiles/ProjetoU.dir/sintatico/AnalisadorSintaticoMain.cpp.o.requires

CMakeFiles/ProjetoU.dir/sintatico/AnalisadorSintaticoMain.cpp.o.provides: CMakeFiles/ProjetoU.dir/sintatico/AnalisadorSintaticoMain.cpp.o.requires
	$(MAKE) -f CMakeFiles/ProjetoU.dir/build.make CMakeFiles/ProjetoU.dir/sintatico/AnalisadorSintaticoMain.cpp.o.provides.build
.PHONY : CMakeFiles/ProjetoU.dir/sintatico/AnalisadorSintaticoMain.cpp.o.provides

CMakeFiles/ProjetoU.dir/sintatico/AnalisadorSintaticoMain.cpp.o.provides.build: CMakeFiles/ProjetoU.dir/sintatico/AnalisadorSintaticoMain.cpp.o


CMakeFiles/ProjetoU.dir/lexico/AnalisadorLexico.cpp.o: CMakeFiles/ProjetoU.dir/flags.make
CMakeFiles/ProjetoU.dir/lexico/AnalisadorLexico.cpp.o: ../lexico/AnalisadorLexico.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sutil/ClionProjects/ProjetoU/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/ProjetoU.dir/lexico/AnalisadorLexico.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ProjetoU.dir/lexico/AnalisadorLexico.cpp.o -c /home/sutil/ClionProjects/ProjetoU/lexico/AnalisadorLexico.cpp

CMakeFiles/ProjetoU.dir/lexico/AnalisadorLexico.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ProjetoU.dir/lexico/AnalisadorLexico.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sutil/ClionProjects/ProjetoU/lexico/AnalisadorLexico.cpp > CMakeFiles/ProjetoU.dir/lexico/AnalisadorLexico.cpp.i

CMakeFiles/ProjetoU.dir/lexico/AnalisadorLexico.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ProjetoU.dir/lexico/AnalisadorLexico.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sutil/ClionProjects/ProjetoU/lexico/AnalisadorLexico.cpp -o CMakeFiles/ProjetoU.dir/lexico/AnalisadorLexico.cpp.s

CMakeFiles/ProjetoU.dir/lexico/AnalisadorLexico.cpp.o.requires:

.PHONY : CMakeFiles/ProjetoU.dir/lexico/AnalisadorLexico.cpp.o.requires

CMakeFiles/ProjetoU.dir/lexico/AnalisadorLexico.cpp.o.provides: CMakeFiles/ProjetoU.dir/lexico/AnalisadorLexico.cpp.o.requires
	$(MAKE) -f CMakeFiles/ProjetoU.dir/build.make CMakeFiles/ProjetoU.dir/lexico/AnalisadorLexico.cpp.o.provides.build
.PHONY : CMakeFiles/ProjetoU.dir/lexico/AnalisadorLexico.cpp.o.provides

CMakeFiles/ProjetoU.dir/lexico/AnalisadorLexico.cpp.o.provides.build: CMakeFiles/ProjetoU.dir/lexico/AnalisadorLexico.cpp.o


CMakeFiles/ProjetoU.dir/lexico/separador.cpp.o: CMakeFiles/ProjetoU.dir/flags.make
CMakeFiles/ProjetoU.dir/lexico/separador.cpp.o: ../lexico/separador.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sutil/ClionProjects/ProjetoU/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/ProjetoU.dir/lexico/separador.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ProjetoU.dir/lexico/separador.cpp.o -c /home/sutil/ClionProjects/ProjetoU/lexico/separador.cpp

CMakeFiles/ProjetoU.dir/lexico/separador.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ProjetoU.dir/lexico/separador.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sutil/ClionProjects/ProjetoU/lexico/separador.cpp > CMakeFiles/ProjetoU.dir/lexico/separador.cpp.i

CMakeFiles/ProjetoU.dir/lexico/separador.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ProjetoU.dir/lexico/separador.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sutil/ClionProjects/ProjetoU/lexico/separador.cpp -o CMakeFiles/ProjetoU.dir/lexico/separador.cpp.s

CMakeFiles/ProjetoU.dir/lexico/separador.cpp.o.requires:

.PHONY : CMakeFiles/ProjetoU.dir/lexico/separador.cpp.o.requires

CMakeFiles/ProjetoU.dir/lexico/separador.cpp.o.provides: CMakeFiles/ProjetoU.dir/lexico/separador.cpp.o.requires
	$(MAKE) -f CMakeFiles/ProjetoU.dir/build.make CMakeFiles/ProjetoU.dir/lexico/separador.cpp.o.provides.build
.PHONY : CMakeFiles/ProjetoU.dir/lexico/separador.cpp.o.provides

CMakeFiles/ProjetoU.dir/lexico/separador.cpp.o.provides.build: CMakeFiles/ProjetoU.dir/lexico/separador.cpp.o


CMakeFiles/ProjetoU.dir/tests/lexico/lexicoTest.cpp.o: CMakeFiles/ProjetoU.dir/flags.make
CMakeFiles/ProjetoU.dir/tests/lexico/lexicoTest.cpp.o: ../tests/lexico/lexicoTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sutil/ClionProjects/ProjetoU/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/ProjetoU.dir/tests/lexico/lexicoTest.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ProjetoU.dir/tests/lexico/lexicoTest.cpp.o -c /home/sutil/ClionProjects/ProjetoU/tests/lexico/lexicoTest.cpp

CMakeFiles/ProjetoU.dir/tests/lexico/lexicoTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ProjetoU.dir/tests/lexico/lexicoTest.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sutil/ClionProjects/ProjetoU/tests/lexico/lexicoTest.cpp > CMakeFiles/ProjetoU.dir/tests/lexico/lexicoTest.cpp.i

CMakeFiles/ProjetoU.dir/tests/lexico/lexicoTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ProjetoU.dir/tests/lexico/lexicoTest.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sutil/ClionProjects/ProjetoU/tests/lexico/lexicoTest.cpp -o CMakeFiles/ProjetoU.dir/tests/lexico/lexicoTest.cpp.s

CMakeFiles/ProjetoU.dir/tests/lexico/lexicoTest.cpp.o.requires:

.PHONY : CMakeFiles/ProjetoU.dir/tests/lexico/lexicoTest.cpp.o.requires

CMakeFiles/ProjetoU.dir/tests/lexico/lexicoTest.cpp.o.provides: CMakeFiles/ProjetoU.dir/tests/lexico/lexicoTest.cpp.o.requires
	$(MAKE) -f CMakeFiles/ProjetoU.dir/build.make CMakeFiles/ProjetoU.dir/tests/lexico/lexicoTest.cpp.o.provides.build
.PHONY : CMakeFiles/ProjetoU.dir/tests/lexico/lexicoTest.cpp.o.provides

CMakeFiles/ProjetoU.dir/tests/lexico/lexicoTest.cpp.o.provides.build: CMakeFiles/ProjetoU.dir/tests/lexico/lexicoTest.cpp.o


CMakeFiles/ProjetoU.dir/lexico/definidorToken.cpp.o: CMakeFiles/ProjetoU.dir/flags.make
CMakeFiles/ProjetoU.dir/lexico/definidorToken.cpp.o: ../lexico/definidorToken.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sutil/ClionProjects/ProjetoU/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/ProjetoU.dir/lexico/definidorToken.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ProjetoU.dir/lexico/definidorToken.cpp.o -c /home/sutil/ClionProjects/ProjetoU/lexico/definidorToken.cpp

CMakeFiles/ProjetoU.dir/lexico/definidorToken.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ProjetoU.dir/lexico/definidorToken.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sutil/ClionProjects/ProjetoU/lexico/definidorToken.cpp > CMakeFiles/ProjetoU.dir/lexico/definidorToken.cpp.i

CMakeFiles/ProjetoU.dir/lexico/definidorToken.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ProjetoU.dir/lexico/definidorToken.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sutil/ClionProjects/ProjetoU/lexico/definidorToken.cpp -o CMakeFiles/ProjetoU.dir/lexico/definidorToken.cpp.s

CMakeFiles/ProjetoU.dir/lexico/definidorToken.cpp.o.requires:

.PHONY : CMakeFiles/ProjetoU.dir/lexico/definidorToken.cpp.o.requires

CMakeFiles/ProjetoU.dir/lexico/definidorToken.cpp.o.provides: CMakeFiles/ProjetoU.dir/lexico/definidorToken.cpp.o.requires
	$(MAKE) -f CMakeFiles/ProjetoU.dir/build.make CMakeFiles/ProjetoU.dir/lexico/definidorToken.cpp.o.provides.build
.PHONY : CMakeFiles/ProjetoU.dir/lexico/definidorToken.cpp.o.provides

CMakeFiles/ProjetoU.dir/lexico/definidorToken.cpp.o.provides.build: CMakeFiles/ProjetoU.dir/lexico/definidorToken.cpp.o


CMakeFiles/ProjetoU.dir/tests/lexico/definidorTokenTest.cpp.o: CMakeFiles/ProjetoU.dir/flags.make
CMakeFiles/ProjetoU.dir/tests/lexico/definidorTokenTest.cpp.o: ../tests/lexico/definidorTokenTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sutil/ClionProjects/ProjetoU/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/ProjetoU.dir/tests/lexico/definidorTokenTest.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ProjetoU.dir/tests/lexico/definidorTokenTest.cpp.o -c /home/sutil/ClionProjects/ProjetoU/tests/lexico/definidorTokenTest.cpp

CMakeFiles/ProjetoU.dir/tests/lexico/definidorTokenTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ProjetoU.dir/tests/lexico/definidorTokenTest.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sutil/ClionProjects/ProjetoU/tests/lexico/definidorTokenTest.cpp > CMakeFiles/ProjetoU.dir/tests/lexico/definidorTokenTest.cpp.i

CMakeFiles/ProjetoU.dir/tests/lexico/definidorTokenTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ProjetoU.dir/tests/lexico/definidorTokenTest.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sutil/ClionProjects/ProjetoU/tests/lexico/definidorTokenTest.cpp -o CMakeFiles/ProjetoU.dir/tests/lexico/definidorTokenTest.cpp.s

CMakeFiles/ProjetoU.dir/tests/lexico/definidorTokenTest.cpp.o.requires:

.PHONY : CMakeFiles/ProjetoU.dir/tests/lexico/definidorTokenTest.cpp.o.requires

CMakeFiles/ProjetoU.dir/tests/lexico/definidorTokenTest.cpp.o.provides: CMakeFiles/ProjetoU.dir/tests/lexico/definidorTokenTest.cpp.o.requires
	$(MAKE) -f CMakeFiles/ProjetoU.dir/build.make CMakeFiles/ProjetoU.dir/tests/lexico/definidorTokenTest.cpp.o.provides.build
.PHONY : CMakeFiles/ProjetoU.dir/tests/lexico/definidorTokenTest.cpp.o.provides

CMakeFiles/ProjetoU.dir/tests/lexico/definidorTokenTest.cpp.o.provides.build: CMakeFiles/ProjetoU.dir/tests/lexico/definidorTokenTest.cpp.o


# Object files for target ProjetoU
ProjetoU_OBJECTS = \
"CMakeFiles/ProjetoU.dir/main.cpp.o" \
"CMakeFiles/ProjetoU.dir/tests/separadorTest.cpp.o" \
"CMakeFiles/ProjetoU.dir/sintatico/AnalisadorSintaticoMain.cpp.o" \
"CMakeFiles/ProjetoU.dir/lexico/AnalisadorLexico.cpp.o" \
"CMakeFiles/ProjetoU.dir/lexico/separador.cpp.o" \
"CMakeFiles/ProjetoU.dir/tests/lexico/lexicoTest.cpp.o" \
"CMakeFiles/ProjetoU.dir/lexico/definidorToken.cpp.o" \
"CMakeFiles/ProjetoU.dir/tests/lexico/definidorTokenTest.cpp.o"

# External object files for target ProjetoU
ProjetoU_EXTERNAL_OBJECTS =

ProjetoU: CMakeFiles/ProjetoU.dir/main.cpp.o
ProjetoU: CMakeFiles/ProjetoU.dir/tests/separadorTest.cpp.o
ProjetoU: CMakeFiles/ProjetoU.dir/sintatico/AnalisadorSintaticoMain.cpp.o
ProjetoU: CMakeFiles/ProjetoU.dir/lexico/AnalisadorLexico.cpp.o
ProjetoU: CMakeFiles/ProjetoU.dir/lexico/separador.cpp.o
ProjetoU: CMakeFiles/ProjetoU.dir/tests/lexico/lexicoTest.cpp.o
ProjetoU: CMakeFiles/ProjetoU.dir/lexico/definidorToken.cpp.o
ProjetoU: CMakeFiles/ProjetoU.dir/tests/lexico/definidorTokenTest.cpp.o
ProjetoU: CMakeFiles/ProjetoU.dir/build.make
ProjetoU: googletest-build/googlemock/gtest/libgtest.a
ProjetoU: googletest-build/googlemock/gtest/libgtest_main.a
ProjetoU: googletest-build/googlemock/gtest/libgtest.a
ProjetoU: CMakeFiles/ProjetoU.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sutil/ClionProjects/ProjetoU/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable ProjetoU"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ProjetoU.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ProjetoU.dir/build: ProjetoU

.PHONY : CMakeFiles/ProjetoU.dir/build

CMakeFiles/ProjetoU.dir/requires: CMakeFiles/ProjetoU.dir/main.cpp.o.requires
CMakeFiles/ProjetoU.dir/requires: CMakeFiles/ProjetoU.dir/tests/separadorTest.cpp.o.requires
CMakeFiles/ProjetoU.dir/requires: CMakeFiles/ProjetoU.dir/sintatico/AnalisadorSintaticoMain.cpp.o.requires
CMakeFiles/ProjetoU.dir/requires: CMakeFiles/ProjetoU.dir/lexico/AnalisadorLexico.cpp.o.requires
CMakeFiles/ProjetoU.dir/requires: CMakeFiles/ProjetoU.dir/lexico/separador.cpp.o.requires
CMakeFiles/ProjetoU.dir/requires: CMakeFiles/ProjetoU.dir/tests/lexico/lexicoTest.cpp.o.requires
CMakeFiles/ProjetoU.dir/requires: CMakeFiles/ProjetoU.dir/lexico/definidorToken.cpp.o.requires
CMakeFiles/ProjetoU.dir/requires: CMakeFiles/ProjetoU.dir/tests/lexico/definidorTokenTest.cpp.o.requires

.PHONY : CMakeFiles/ProjetoU.dir/requires

CMakeFiles/ProjetoU.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ProjetoU.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ProjetoU.dir/clean

CMakeFiles/ProjetoU.dir/depend:
	cd /home/sutil/ClionProjects/ProjetoU/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sutil/ClionProjects/ProjetoU /home/sutil/ClionProjects/ProjetoU /home/sutil/ClionProjects/ProjetoU/cmake-build-debug /home/sutil/ClionProjects/ProjetoU/cmake-build-debug /home/sutil/ClionProjects/ProjetoU/cmake-build-debug/CMakeFiles/ProjetoU.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ProjetoU.dir/depend

