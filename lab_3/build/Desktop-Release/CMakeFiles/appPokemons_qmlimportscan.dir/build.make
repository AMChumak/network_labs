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
CMAKE_SOURCE_DIR = /home/anton/Documents/Networks/course3/lab_3/Pokemons

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release

# Utility rule file for appPokemons_qmlimportscan.

# Include any custom commands dependencies for this target.
include CMakeFiles/appPokemons_qmlimportscan.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/appPokemons_qmlimportscan.dir/progress.make

CMakeFiles/appPokemons_qmlimportscan: .qt_plugins/Qt6_QmlPlugins_Imports_appPokemons.cmake

.qt_plugins/Qt6_QmlPlugins_Imports_appPokemons.cmake: /usr/lib/qt6/libexec/qmlimportscanner
.qt_plugins/Qt6_QmlPlugins_Imports_appPokemons.cmake: .rcc/qmake_Pokemons.qrc
.qt_plugins/Qt6_QmlPlugins_Imports_appPokemons.cmake: .rcc/appPokemons_raw_qml_0.qrc
.qt_plugins/Qt6_QmlPlugins_Imports_appPokemons.cmake: /home/anton/Documents/Networks/course3/lab_3/Pokemons/Main.qml
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Running qmlimportscanner for appPokemons"
	cd /home/anton/Documents/Networks/course3/lab_3/Pokemons && /usr/lib/qt6/libexec/qmlimportscanner @/home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/.qt_plugins/Qt6_QmlPlugins_Imports_appPokemons.rsp

appPokemons_qmlimportscan: .qt_plugins/Qt6_QmlPlugins_Imports_appPokemons.cmake
appPokemons_qmlimportscan: CMakeFiles/appPokemons_qmlimportscan
appPokemons_qmlimportscan: CMakeFiles/appPokemons_qmlimportscan.dir/build.make
.PHONY : appPokemons_qmlimportscan

# Rule to build all files generated by this target.
CMakeFiles/appPokemons_qmlimportscan.dir/build: appPokemons_qmlimportscan
.PHONY : CMakeFiles/appPokemons_qmlimportscan.dir/build

CMakeFiles/appPokemons_qmlimportscan.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/appPokemons_qmlimportscan.dir/cmake_clean.cmake
.PHONY : CMakeFiles/appPokemons_qmlimportscan.dir/clean

CMakeFiles/appPokemons_qmlimportscan.dir/depend:
	cd /home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/anton/Documents/Networks/course3/lab_3/Pokemons /home/anton/Documents/Networks/course3/lab_3/Pokemons /home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release /home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release /home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/CMakeFiles/appPokemons_qmlimportscan.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/appPokemons_qmlimportscan.dir/depend

