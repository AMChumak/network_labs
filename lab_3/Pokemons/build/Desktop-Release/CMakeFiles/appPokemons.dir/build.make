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
CMAKE_SOURCE_DIR = /home/anton/Documents/Networks/course3/lab_3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release

# Include any dependencies generated for this target.
include CMakeFiles/appPokemons.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/appPokemons.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/appPokemons.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/appPokemons.dir/flags.make

meta_types/qt6apppokemons_release_metatypes.json.gen: /usr/lib/qt6/libexec/moc
meta_types/qt6apppokemons_release_metatypes.json.gen: meta_types/appPokemons_json_file_list.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Running moc --collect-json for target appPokemons"
	/usr/lib/qt6/libexec/moc -o /home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/meta_types/qt6apppokemons_release_metatypes.json.gen --collect-json @/home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/meta_types/appPokemons_json_file_list.txt
	/usr/bin/cmake -E copy_if_different /home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/meta_types/qt6apppokemons_release_metatypes.json.gen /home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/meta_types/qt6apppokemons_release_metatypes.json

meta_types/qt6apppokemons_release_metatypes.json: meta_types/qt6apppokemons_release_metatypes.json.gen
	@$(CMAKE_COMMAND) -E touch_nocreate meta_types/qt6apppokemons_release_metatypes.json

apppokemons_qmltyperegistrations.cpp: qmltypes/appPokemons_foreign_types.txt
apppokemons_qmltyperegistrations.cpp: meta_types/qt6apppokemons_release_metatypes.json
apppokemons_qmltyperegistrations.cpp: /usr/lib/qt6/libexec/qmltyperegistrar
apppokemons_qmltyperegistrations.cpp: /usr/lib/x86_64-linux-gnu/metatypes/qt6core_none_metatypes.json
apppokemons_qmltyperegistrations.cpp: /usr/lib/x86_64-linux-gnu/metatypes/qt6qml_none_metatypes.json
apppokemons_qmltyperegistrations.cpp: /usr/lib/x86_64-linux-gnu/metatypes/qt6network_none_metatypes.json
apppokemons_qmltyperegistrations.cpp: /usr/lib/x86_64-linux-gnu/metatypes/qt6quick_none_metatypes.json
apppokemons_qmltyperegistrations.cpp: /usr/lib/x86_64-linux-gnu/metatypes/qt6gui_none_metatypes.json
apppokemons_qmltyperegistrations.cpp: /usr/lib/x86_64-linux-gnu/metatypes/qt6qmlmodels_none_metatypes.json
apppokemons_qmltyperegistrations.cpp: /usr/lib/x86_64-linux-gnu/metatypes/qt6opengl_none_metatypes.json
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Automatic QML type registration for target appPokemons"
	/usr/lib/qt6/libexec/qmltyperegistrar --generate-qmltypes=/home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/Pokemons/appPokemons.qmltypes --import-name=Pokemons --major-version=1 --minor-version=0 @/home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/qmltypes/appPokemons_foreign_types.txt -o /home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/apppokemons_qmltyperegistrations.cpp /home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/meta_types/qt6apppokemons_release_metatypes.json
	/usr/bin/cmake -E make_directory /home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/.generated
	/usr/bin/cmake -E touch /home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/.generated/appPokemons.qmltypes

Pokemons/appPokemons.qmltypes: apppokemons_qmltyperegistrations.cpp
	@$(CMAKE_COMMAND) -E touch_nocreate Pokemons/appPokemons.qmltypes

.rcc/qrc_qmake_Pokemons.cpp: Pokemons/qmldir
.rcc/qrc_qmake_Pokemons.cpp: .rcc/qmake_Pokemons.qrc
.rcc/qrc_qmake_Pokemons.cpp: /usr/lib/qt6/libexec/rcc
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Running rcc for resource qmake_Pokemons"
	/usr/lib/qt6/libexec/rcc --output /home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/.rcc/qrc_qmake_Pokemons.cpp --name qmake_Pokemons /home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/.rcc/qmake_Pokemons.qrc

.rcc/qmlcache/appPokemons_qmlcache_loader.cpp: /usr/lib/qt6/libexec/qmlcachegen
.rcc/qmlcache/appPokemons_qmlcache_loader.cpp: .rcc/qmlcache/appPokemons_qml_loader_file_list.rsp
.rcc/qmlcache/appPokemons_qmlcache_loader.cpp: .rcc/qmake_Pokemons.qrc
.rcc/qmlcache/appPokemons_qmlcache_loader.cpp: .rcc/appPokemons_raw_qml_0.qrc
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Generating .rcc/qmlcache/appPokemons_qmlcache_loader.cpp"
	/usr/lib/qt6/libexec/qmlcachegen --resource-name qmlcache_appPokemons --resource /home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/.rcc/qmake_Pokemons.qrc --resource /home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/.rcc/appPokemons_raw_qml_0.qrc -o /home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/.rcc/qmlcache/appPokemons_qmlcache_loader.cpp @/home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/.rcc/qmlcache/appPokemons_qml_loader_file_list.rsp

.rcc/qmlcache/appPokemons_Main_qml.cpp: /usr/lib/qt6/libexec/qmlcachegen
.rcc/qmlcache/appPokemons_Main_qml.cpp: /home/anton/Documents/Networks/course3/lab_3/Main.qml
.rcc/qmlcache/appPokemons_Main_qml.cpp: .rcc/qmake_Pokemons.qrc
.rcc/qmlcache/appPokemons_Main_qml.cpp: .rcc/appPokemons_raw_qml_0.qrc
.rcc/qmlcache/appPokemons_Main_qml.cpp: Pokemons/appPokemons.qmltypes
.rcc/qmlcache/appPokemons_Main_qml.cpp: Pokemons/qmldir
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Generating .rcc/qmlcache/appPokemons_Main_qml.cpp"
	/usr/bin/cmake -E make_directory /home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/.rcc/qmlcache
	/usr/lib/qt6/libexec/qmlcachegen --bare --resource-path /Pokemons/Main.qml -I /home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release -I /usr/lib/x86_64-linux-gnu/qt6/qml -i /home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/Pokemons/qmldir --resource /home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/.rcc/qmake_Pokemons.qrc --resource /home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/.rcc/appPokemons_raw_qml_0.qrc -o /home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/.rcc/qmlcache/appPokemons_Main_qml.cpp /home/anton/Documents/Networks/course3/lab_3/Main.qml

.rcc/qrc_appPokemons_raw_qml_0.cpp: /home/anton/Documents/Networks/course3/lab_3/Main.qml
.rcc/qrc_appPokemons_raw_qml_0.cpp: /home/anton/Documents/Networks/course3/lab_3/images/pikachu.png
.rcc/qrc_appPokemons_raw_qml_0.cpp: /home/anton/Documents/Networks/course3/lab_3/images/pikachu.gif
.rcc/qrc_appPokemons_raw_qml_0.cpp: /home/anton/Documents/Networks/course3/lab_3/images/search.svg
.rcc/qrc_appPokemons_raw_qml_0.cpp: /home/anton/Documents/Networks/course3/lab_3/images/faq.gif
.rcc/qrc_appPokemons_raw_qml_0.cpp: /home/anton/Documents/Networks/course3/lab_3/images/question.gif
.rcc/qrc_appPokemons_raw_qml_0.cpp: .rcc/appPokemons_raw_qml_0.qrc
.rcc/qrc_appPokemons_raw_qml_0.cpp: /usr/lib/qt6/libexec/rcc
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Running rcc for resource appPokemons_raw_qml_0"
	/usr/lib/qt6/libexec/rcc --output /home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/.rcc/qrc_appPokemons_raw_qml_0.cpp --name appPokemons_raw_qml_0 /home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/.rcc/appPokemons_raw_qml_0.qrc

appPokemons_autogen/timestamp: /usr/lib/qt6/libexec/moc
appPokemons_autogen/timestamp: CMakeFiles/appPokemons.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Automatic MOC and UIC for target appPokemons"
	/usr/bin/cmake -E cmake_autogen /home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/CMakeFiles/appPokemons_autogen.dir/AutogenInfo.json Release
	/usr/bin/cmake -E touch /home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/appPokemons_autogen/timestamp

CMakeFiles/appPokemons.dir/appPokemons_autogen/mocs_compilation.cpp.o: CMakeFiles/appPokemons.dir/flags.make
CMakeFiles/appPokemons.dir/appPokemons_autogen/mocs_compilation.cpp.o: appPokemons_autogen/mocs_compilation.cpp
CMakeFiles/appPokemons.dir/appPokemons_autogen/mocs_compilation.cpp.o: CMakeFiles/appPokemons.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/appPokemons.dir/appPokemons_autogen/mocs_compilation.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/appPokemons.dir/appPokemons_autogen/mocs_compilation.cpp.o -MF CMakeFiles/appPokemons.dir/appPokemons_autogen/mocs_compilation.cpp.o.d -o CMakeFiles/appPokemons.dir/appPokemons_autogen/mocs_compilation.cpp.o -c /home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/appPokemons_autogen/mocs_compilation.cpp

CMakeFiles/appPokemons.dir/appPokemons_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/appPokemons.dir/appPokemons_autogen/mocs_compilation.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/appPokemons_autogen/mocs_compilation.cpp > CMakeFiles/appPokemons.dir/appPokemons_autogen/mocs_compilation.cpp.i

CMakeFiles/appPokemons.dir/appPokemons_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/appPokemons.dir/appPokemons_autogen/mocs_compilation.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/appPokemons_autogen/mocs_compilation.cpp -o CMakeFiles/appPokemons.dir/appPokemons_autogen/mocs_compilation.cpp.s

CMakeFiles/appPokemons.dir/main.cpp.o: CMakeFiles/appPokemons.dir/flags.make
CMakeFiles/appPokemons.dir/main.cpp.o: /home/anton/Documents/Networks/course3/lab_3/main.cpp
CMakeFiles/appPokemons.dir/main.cpp.o: CMakeFiles/appPokemons.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/appPokemons.dir/main.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/appPokemons.dir/main.cpp.o -MF CMakeFiles/appPokemons.dir/main.cpp.o.d -o CMakeFiles/appPokemons.dir/main.cpp.o -c /home/anton/Documents/Networks/course3/lab_3/main.cpp

CMakeFiles/appPokemons.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/appPokemons.dir/main.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/anton/Documents/Networks/course3/lab_3/main.cpp > CMakeFiles/appPokemons.dir/main.cpp.i

CMakeFiles/appPokemons.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/appPokemons.dir/main.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/anton/Documents/Networks/course3/lab_3/main.cpp -o CMakeFiles/appPokemons.dir/main.cpp.s

CMakeFiles/appPokemons.dir/apppokemons_qmltyperegistrations.cpp.o: CMakeFiles/appPokemons.dir/flags.make
CMakeFiles/appPokemons.dir/apppokemons_qmltyperegistrations.cpp.o: apppokemons_qmltyperegistrations.cpp
CMakeFiles/appPokemons.dir/apppokemons_qmltyperegistrations.cpp.o: CMakeFiles/appPokemons.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/appPokemons.dir/apppokemons_qmltyperegistrations.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/appPokemons.dir/apppokemons_qmltyperegistrations.cpp.o -MF CMakeFiles/appPokemons.dir/apppokemons_qmltyperegistrations.cpp.o.d -o CMakeFiles/appPokemons.dir/apppokemons_qmltyperegistrations.cpp.o -c /home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/apppokemons_qmltyperegistrations.cpp

CMakeFiles/appPokemons.dir/apppokemons_qmltyperegistrations.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/appPokemons.dir/apppokemons_qmltyperegistrations.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/apppokemons_qmltyperegistrations.cpp > CMakeFiles/appPokemons.dir/apppokemons_qmltyperegistrations.cpp.i

CMakeFiles/appPokemons.dir/apppokemons_qmltyperegistrations.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/appPokemons.dir/apppokemons_qmltyperegistrations.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/apppokemons_qmltyperegistrations.cpp -o CMakeFiles/appPokemons.dir/apppokemons_qmltyperegistrations.cpp.s

CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qrc_qmake_Pokemons.cpp.o: CMakeFiles/appPokemons.dir/flags.make
CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qrc_qmake_Pokemons.cpp.o: .rcc/qrc_qmake_Pokemons.cpp
CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qrc_qmake_Pokemons.cpp.o: CMakeFiles/appPokemons.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qrc_qmake_Pokemons.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qrc_qmake_Pokemons.cpp.o -MF CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qrc_qmake_Pokemons.cpp.o.d -o CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qrc_qmake_Pokemons.cpp.o -c /home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/.rcc/qrc_qmake_Pokemons.cpp

CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qrc_qmake_Pokemons.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qrc_qmake_Pokemons.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/.rcc/qrc_qmake_Pokemons.cpp > CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qrc_qmake_Pokemons.cpp.i

CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qrc_qmake_Pokemons.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qrc_qmake_Pokemons.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/.rcc/qrc_qmake_Pokemons.cpp -o CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qrc_qmake_Pokemons.cpp.s

CMakeFiles/appPokemons.dir/searchbtnmodel.cpp.o: CMakeFiles/appPokemons.dir/flags.make
CMakeFiles/appPokemons.dir/searchbtnmodel.cpp.o: /home/anton/Documents/Networks/course3/lab_3/searchbtnmodel.cpp
CMakeFiles/appPokemons.dir/searchbtnmodel.cpp.o: CMakeFiles/appPokemons.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/appPokemons.dir/searchbtnmodel.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/appPokemons.dir/searchbtnmodel.cpp.o -MF CMakeFiles/appPokemons.dir/searchbtnmodel.cpp.o.d -o CMakeFiles/appPokemons.dir/searchbtnmodel.cpp.o -c /home/anton/Documents/Networks/course3/lab_3/searchbtnmodel.cpp

CMakeFiles/appPokemons.dir/searchbtnmodel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/appPokemons.dir/searchbtnmodel.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/anton/Documents/Networks/course3/lab_3/searchbtnmodel.cpp > CMakeFiles/appPokemons.dir/searchbtnmodel.cpp.i

CMakeFiles/appPokemons.dir/searchbtnmodel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/appPokemons.dir/searchbtnmodel.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/anton/Documents/Networks/course3/lab_3/searchbtnmodel.cpp -o CMakeFiles/appPokemons.dir/searchbtnmodel.cpp.s

CMakeFiles/appPokemons.dir/tablemodel.cpp.o: CMakeFiles/appPokemons.dir/flags.make
CMakeFiles/appPokemons.dir/tablemodel.cpp.o: /home/anton/Documents/Networks/course3/lab_3/tablemodel.cpp
CMakeFiles/appPokemons.dir/tablemodel.cpp.o: CMakeFiles/appPokemons.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/appPokemons.dir/tablemodel.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/appPokemons.dir/tablemodel.cpp.o -MF CMakeFiles/appPokemons.dir/tablemodel.cpp.o.d -o CMakeFiles/appPokemons.dir/tablemodel.cpp.o -c /home/anton/Documents/Networks/course3/lab_3/tablemodel.cpp

CMakeFiles/appPokemons.dir/tablemodel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/appPokemons.dir/tablemodel.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/anton/Documents/Networks/course3/lab_3/tablemodel.cpp > CMakeFiles/appPokemons.dir/tablemodel.cpp.i

CMakeFiles/appPokemons.dir/tablemodel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/appPokemons.dir/tablemodel.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/anton/Documents/Networks/course3/lab_3/tablemodel.cpp -o CMakeFiles/appPokemons.dir/tablemodel.cpp.s

CMakeFiles/appPokemons.dir/imagemodel.cpp.o: CMakeFiles/appPokemons.dir/flags.make
CMakeFiles/appPokemons.dir/imagemodel.cpp.o: /home/anton/Documents/Networks/course3/lab_3/imagemodel.cpp
CMakeFiles/appPokemons.dir/imagemodel.cpp.o: CMakeFiles/appPokemons.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/appPokemons.dir/imagemodel.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/appPokemons.dir/imagemodel.cpp.o -MF CMakeFiles/appPokemons.dir/imagemodel.cpp.o.d -o CMakeFiles/appPokemons.dir/imagemodel.cpp.o -c /home/anton/Documents/Networks/course3/lab_3/imagemodel.cpp

CMakeFiles/appPokemons.dir/imagemodel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/appPokemons.dir/imagemodel.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/anton/Documents/Networks/course3/lab_3/imagemodel.cpp > CMakeFiles/appPokemons.dir/imagemodel.cpp.i

CMakeFiles/appPokemons.dir/imagemodel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/appPokemons.dir/imagemodel.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/anton/Documents/Networks/course3/lab_3/imagemodel.cpp -o CMakeFiles/appPokemons.dir/imagemodel.cpp.s

CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qmlcache/appPokemons_qmlcache_loader.cpp.o: CMakeFiles/appPokemons.dir/flags.make
CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qmlcache/appPokemons_qmlcache_loader.cpp.o: .rcc/qmlcache/appPokemons_qmlcache_loader.cpp
CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qmlcache/appPokemons_qmlcache_loader.cpp.o: CMakeFiles/appPokemons.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qmlcache/appPokemons_qmlcache_loader.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qmlcache/appPokemons_qmlcache_loader.cpp.o -MF CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qmlcache/appPokemons_qmlcache_loader.cpp.o.d -o CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qmlcache/appPokemons_qmlcache_loader.cpp.o -c /home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/.rcc/qmlcache/appPokemons_qmlcache_loader.cpp

CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qmlcache/appPokemons_qmlcache_loader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qmlcache/appPokemons_qmlcache_loader.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/.rcc/qmlcache/appPokemons_qmlcache_loader.cpp > CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qmlcache/appPokemons_qmlcache_loader.cpp.i

CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qmlcache/appPokemons_qmlcache_loader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qmlcache/appPokemons_qmlcache_loader.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/.rcc/qmlcache/appPokemons_qmlcache_loader.cpp -o CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qmlcache/appPokemons_qmlcache_loader.cpp.s

CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qmlcache/appPokemons_Main_qml.cpp.o: CMakeFiles/appPokemons.dir/flags.make
CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qmlcache/appPokemons_Main_qml.cpp.o: .rcc/qmlcache/appPokemons_Main_qml.cpp
CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qmlcache/appPokemons_Main_qml.cpp.o: CMakeFiles/appPokemons.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Building CXX object CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qmlcache/appPokemons_Main_qml.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qmlcache/appPokemons_Main_qml.cpp.o -MF CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qmlcache/appPokemons_Main_qml.cpp.o.d -o CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qmlcache/appPokemons_Main_qml.cpp.o -c /home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/.rcc/qmlcache/appPokemons_Main_qml.cpp

CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qmlcache/appPokemons_Main_qml.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qmlcache/appPokemons_Main_qml.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/.rcc/qmlcache/appPokemons_Main_qml.cpp > CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qmlcache/appPokemons_Main_qml.cpp.i

CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qmlcache/appPokemons_Main_qml.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qmlcache/appPokemons_Main_qml.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/.rcc/qmlcache/appPokemons_Main_qml.cpp -o CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qmlcache/appPokemons_Main_qml.cpp.s

CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qrc_appPokemons_raw_qml_0.cpp.o: CMakeFiles/appPokemons.dir/flags.make
CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qrc_appPokemons_raw_qml_0.cpp.o: .rcc/qrc_appPokemons_raw_qml_0.cpp
CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qrc_appPokemons_raw_qml_0.cpp.o: CMakeFiles/appPokemons.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_17) "Building CXX object CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qrc_appPokemons_raw_qml_0.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qrc_appPokemons_raw_qml_0.cpp.o -MF CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qrc_appPokemons_raw_qml_0.cpp.o.d -o CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qrc_appPokemons_raw_qml_0.cpp.o -c /home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/.rcc/qrc_appPokemons_raw_qml_0.cpp

CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qrc_appPokemons_raw_qml_0.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qrc_appPokemons_raw_qml_0.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/.rcc/qrc_appPokemons_raw_qml_0.cpp > CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qrc_appPokemons_raw_qml_0.cpp.i

CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qrc_appPokemons_raw_qml_0.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qrc_appPokemons_raw_qml_0.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/.rcc/qrc_appPokemons_raw_qml_0.cpp -o CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qrc_appPokemons_raw_qml_0.cpp.s

# Object files for target appPokemons
appPokemons_OBJECTS = \
"CMakeFiles/appPokemons.dir/appPokemons_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/appPokemons.dir/main.cpp.o" \
"CMakeFiles/appPokemons.dir/apppokemons_qmltyperegistrations.cpp.o" \
"CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qrc_qmake_Pokemons.cpp.o" \
"CMakeFiles/appPokemons.dir/searchbtnmodel.cpp.o" \
"CMakeFiles/appPokemons.dir/tablemodel.cpp.o" \
"CMakeFiles/appPokemons.dir/imagemodel.cpp.o" \
"CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qmlcache/appPokemons_qmlcache_loader.cpp.o" \
"CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qmlcache/appPokemons_Main_qml.cpp.o" \
"CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qrc_appPokemons_raw_qml_0.cpp.o"

# External object files for target appPokemons
appPokemons_EXTERNAL_OBJECTS =

appPokemons: CMakeFiles/appPokemons.dir/appPokemons_autogen/mocs_compilation.cpp.o
appPokemons: CMakeFiles/appPokemons.dir/main.cpp.o
appPokemons: CMakeFiles/appPokemons.dir/apppokemons_qmltyperegistrations.cpp.o
appPokemons: CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qrc_qmake_Pokemons.cpp.o
appPokemons: CMakeFiles/appPokemons.dir/searchbtnmodel.cpp.o
appPokemons: CMakeFiles/appPokemons.dir/tablemodel.cpp.o
appPokemons: CMakeFiles/appPokemons.dir/imagemodel.cpp.o
appPokemons: CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qmlcache/appPokemons_qmlcache_loader.cpp.o
appPokemons: CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qmlcache/appPokemons_Main_qml.cpp.o
appPokemons: CMakeFiles/appPokemons.dir/Pokemons/build/Desktop-Release/.rcc/qrc_appPokemons_raw_qml_0.cpp.o
appPokemons: CMakeFiles/appPokemons.dir/build.make
appPokemons: /usr/lib/x86_64-linux-gnu/libQt6Quick.so.6.4.2
appPokemons: /usr/lib/x86_64-linux-gnu/libQt6QmlModels.so.6.4.2
appPokemons: /usr/lib/x86_64-linux-gnu/libQt6Qml.so.6.4.2
appPokemons: /usr/lib/x86_64-linux-gnu/libQt6Network.so.6.4.2
appPokemons: /usr/lib/x86_64-linux-gnu/libQt6OpenGL.so.6.4.2
appPokemons: /usr/lib/x86_64-linux-gnu/libQt6Gui.so.6.4.2
appPokemons: /usr/lib/x86_64-linux-gnu/libQt6Core.so.6.4.2
appPokemons: /usr/lib/x86_64-linux-gnu/libGLX.so
appPokemons: /usr/lib/x86_64-linux-gnu/libOpenGL.so
appPokemons: CMakeFiles/appPokemons.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_18) "Linking CXX executable appPokemons"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/appPokemons.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/appPokemons.dir/build: appPokemons
.PHONY : CMakeFiles/appPokemons.dir/build

CMakeFiles/appPokemons.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/appPokemons.dir/cmake_clean.cmake
.PHONY : CMakeFiles/appPokemons.dir/clean

CMakeFiles/appPokemons.dir/depend: .rcc/qmlcache/appPokemons_Main_qml.cpp
CMakeFiles/appPokemons.dir/depend: .rcc/qmlcache/appPokemons_qmlcache_loader.cpp
CMakeFiles/appPokemons.dir/depend: .rcc/qrc_appPokemons_raw_qml_0.cpp
CMakeFiles/appPokemons.dir/depend: .rcc/qrc_qmake_Pokemons.cpp
CMakeFiles/appPokemons.dir/depend: Pokemons/appPokemons.qmltypes
CMakeFiles/appPokemons.dir/depend: appPokemons_autogen/timestamp
CMakeFiles/appPokemons.dir/depend: apppokemons_qmltyperegistrations.cpp
CMakeFiles/appPokemons.dir/depend: meta_types/qt6apppokemons_release_metatypes.json
CMakeFiles/appPokemons.dir/depend: meta_types/qt6apppokemons_release_metatypes.json.gen
	cd /home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/anton/Documents/Networks/course3/lab_3 /home/anton/Documents/Networks/course3/lab_3 /home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release /home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release /home/anton/Documents/Networks/course3/lab_3/Pokemons/build/Desktop-Release/CMakeFiles/appPokemons.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/appPokemons.dir/depend

