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
CMAKE_COMMAND = "D:\clion\CLion 2023.2.2\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "D:\clion\CLion 2023.2.2\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "D:\FEUP\2 ano\Algoritmos e Estruturas de Dados\Projeto 1\AED"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "D:\FEUP\2 ano\Algoritmos e Estruturas de Dados\Projeto 1\AED\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/TrabalhoAED.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/TrabalhoAED.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/TrabalhoAED.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TrabalhoAED.dir/flags.make

CMakeFiles/TrabalhoAED.dir/library.cpp.obj: CMakeFiles/TrabalhoAED.dir/flags.make
CMakeFiles/TrabalhoAED.dir/library.cpp.obj: D:/FEUP/2\ ano/Algoritmos\ e\ Estruturas\ de\ Dados/Projeto\ 1/AED/library.cpp
CMakeFiles/TrabalhoAED.dir/library.cpp.obj: CMakeFiles/TrabalhoAED.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\FEUP\2 ano\Algoritmos e Estruturas de Dados\Projeto 1\AED\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TrabalhoAED.dir/library.cpp.obj"
	"D:\clion\CLion 2023.2.2\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TrabalhoAED.dir/library.cpp.obj -MF CMakeFiles\TrabalhoAED.dir\library.cpp.obj.d -o CMakeFiles\TrabalhoAED.dir\library.cpp.obj -c "D:\FEUP\2 ano\Algoritmos e Estruturas de Dados\Projeto 1\AED\library.cpp"

CMakeFiles/TrabalhoAED.dir/library.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TrabalhoAED.dir/library.cpp.i"
	"D:\clion\CLion 2023.2.2\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\FEUP\2 ano\Algoritmos e Estruturas de Dados\Projeto 1\AED\library.cpp" > CMakeFiles\TrabalhoAED.dir\library.cpp.i

CMakeFiles/TrabalhoAED.dir/library.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TrabalhoAED.dir/library.cpp.s"
	"D:\clion\CLion 2023.2.2\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "D:\FEUP\2 ano\Algoritmos e Estruturas de Dados\Projeto 1\AED\library.cpp" -o CMakeFiles\TrabalhoAED.dir\library.cpp.s

CMakeFiles/TrabalhoAED.dir/student.cpp.obj: CMakeFiles/TrabalhoAED.dir/flags.make
CMakeFiles/TrabalhoAED.dir/student.cpp.obj: D:/FEUP/2\ ano/Algoritmos\ e\ Estruturas\ de\ Dados/Projeto\ 1/AED/student.cpp
CMakeFiles/TrabalhoAED.dir/student.cpp.obj: CMakeFiles/TrabalhoAED.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\FEUP\2 ano\Algoritmos e Estruturas de Dados\Projeto 1\AED\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/TrabalhoAED.dir/student.cpp.obj"
	"D:\clion\CLion 2023.2.2\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TrabalhoAED.dir/student.cpp.obj -MF CMakeFiles\TrabalhoAED.dir\student.cpp.obj.d -o CMakeFiles\TrabalhoAED.dir\student.cpp.obj -c "D:\FEUP\2 ano\Algoritmos e Estruturas de Dados\Projeto 1\AED\student.cpp"

CMakeFiles/TrabalhoAED.dir/student.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TrabalhoAED.dir/student.cpp.i"
	"D:\clion\CLion 2023.2.2\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\FEUP\2 ano\Algoritmos e Estruturas de Dados\Projeto 1\AED\student.cpp" > CMakeFiles\TrabalhoAED.dir\student.cpp.i

CMakeFiles/TrabalhoAED.dir/student.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TrabalhoAED.dir/student.cpp.s"
	"D:\clion\CLion 2023.2.2\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "D:\FEUP\2 ano\Algoritmos e Estruturas de Dados\Projeto 1\AED\student.cpp" -o CMakeFiles\TrabalhoAED.dir\student.cpp.s

CMakeFiles/TrabalhoAED.dir/course.cpp.obj: CMakeFiles/TrabalhoAED.dir/flags.make
CMakeFiles/TrabalhoAED.dir/course.cpp.obj: D:/FEUP/2\ ano/Algoritmos\ e\ Estruturas\ de\ Dados/Projeto\ 1/AED/course.cpp
CMakeFiles/TrabalhoAED.dir/course.cpp.obj: CMakeFiles/TrabalhoAED.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\FEUP\2 ano\Algoritmos e Estruturas de Dados\Projeto 1\AED\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/TrabalhoAED.dir/course.cpp.obj"
	"D:\clion\CLion 2023.2.2\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TrabalhoAED.dir/course.cpp.obj -MF CMakeFiles\TrabalhoAED.dir\course.cpp.obj.d -o CMakeFiles\TrabalhoAED.dir\course.cpp.obj -c "D:\FEUP\2 ano\Algoritmos e Estruturas de Dados\Projeto 1\AED\course.cpp"

CMakeFiles/TrabalhoAED.dir/course.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TrabalhoAED.dir/course.cpp.i"
	"D:\clion\CLion 2023.2.2\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\FEUP\2 ano\Algoritmos e Estruturas de Dados\Projeto 1\AED\course.cpp" > CMakeFiles\TrabalhoAED.dir\course.cpp.i

CMakeFiles/TrabalhoAED.dir/course.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TrabalhoAED.dir/course.cpp.s"
	"D:\clion\CLion 2023.2.2\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "D:\FEUP\2 ano\Algoritmos e Estruturas de Dados\Projeto 1\AED\course.cpp" -o CMakeFiles\TrabalhoAED.dir\course.cpp.s

CMakeFiles/TrabalhoAED.dir/class1.cpp.obj: CMakeFiles/TrabalhoAED.dir/flags.make
CMakeFiles/TrabalhoAED.dir/class1.cpp.obj: D:/FEUP/2\ ano/Algoritmos\ e\ Estruturas\ de\ Dados/Projeto\ 1/AED/class1.cpp
CMakeFiles/TrabalhoAED.dir/class1.cpp.obj: CMakeFiles/TrabalhoAED.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\FEUP\2 ano\Algoritmos e Estruturas de Dados\Projeto 1\AED\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/TrabalhoAED.dir/class1.cpp.obj"
	"D:\clion\CLion 2023.2.2\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TrabalhoAED.dir/class1.cpp.obj -MF CMakeFiles\TrabalhoAED.dir\class1.cpp.obj.d -o CMakeFiles\TrabalhoAED.dir\class1.cpp.obj -c "D:\FEUP\2 ano\Algoritmos e Estruturas de Dados\Projeto 1\AED\class1.cpp"

CMakeFiles/TrabalhoAED.dir/class1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TrabalhoAED.dir/class1.cpp.i"
	"D:\clion\CLion 2023.2.2\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\FEUP\2 ano\Algoritmos e Estruturas de Dados\Projeto 1\AED\class1.cpp" > CMakeFiles\TrabalhoAED.dir\class1.cpp.i

CMakeFiles/TrabalhoAED.dir/class1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TrabalhoAED.dir/class1.cpp.s"
	"D:\clion\CLion 2023.2.2\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "D:\FEUP\2 ano\Algoritmos e Estruturas de Dados\Projeto 1\AED\class1.cpp" -o CMakeFiles\TrabalhoAED.dir\class1.cpp.s

# Object files for target TrabalhoAED
TrabalhoAED_OBJECTS = \
"CMakeFiles/TrabalhoAED.dir/library.cpp.obj" \
"CMakeFiles/TrabalhoAED.dir/student.cpp.obj" \
"CMakeFiles/TrabalhoAED.dir/course.cpp.obj" \
"CMakeFiles/TrabalhoAED.dir/class1.cpp.obj"

# External object files for target TrabalhoAED
TrabalhoAED_EXTERNAL_OBJECTS =

libTrabalhoAED.a: CMakeFiles/TrabalhoAED.dir/library.cpp.obj
libTrabalhoAED.a: CMakeFiles/TrabalhoAED.dir/student.cpp.obj
libTrabalhoAED.a: CMakeFiles/TrabalhoAED.dir/course.cpp.obj
libTrabalhoAED.a: CMakeFiles/TrabalhoAED.dir/class1.cpp.obj
libTrabalhoAED.a: CMakeFiles/TrabalhoAED.dir/build.make
libTrabalhoAED.a: CMakeFiles/TrabalhoAED.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="D:\FEUP\2 ano\Algoritmos e Estruturas de Dados\Projeto 1\AED\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX static library libTrabalhoAED.a"
	$(CMAKE_COMMAND) -P CMakeFiles\TrabalhoAED.dir\cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\TrabalhoAED.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TrabalhoAED.dir/build: libTrabalhoAED.a
.PHONY : CMakeFiles/TrabalhoAED.dir/build

CMakeFiles/TrabalhoAED.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\TrabalhoAED.dir\cmake_clean.cmake
.PHONY : CMakeFiles/TrabalhoAED.dir/clean

CMakeFiles/TrabalhoAED.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "D:\FEUP\2 ano\Algoritmos e Estruturas de Dados\Projeto 1\AED" "D:\FEUP\2 ano\Algoritmos e Estruturas de Dados\Projeto 1\AED" "D:\FEUP\2 ano\Algoritmos e Estruturas de Dados\Projeto 1\AED\cmake-build-debug" "D:\FEUP\2 ano\Algoritmos e Estruturas de Dados\Projeto 1\AED\cmake-build-debug" "D:\FEUP\2 ano\Algoritmos e Estruturas de Dados\Projeto 1\AED\cmake-build-debug\CMakeFiles\TrabalhoAED.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/TrabalhoAED.dir/depend
