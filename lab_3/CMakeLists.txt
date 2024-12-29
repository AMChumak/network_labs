cmake_minimum_required(VERSION 3.16)

project(Pokemons VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)
find_package(Qt6 6.4 REQUIRED COMPONENTS Network)

# Directories where Qt Creator can find QML files.
# (Not needed for builds, but makes Qt Creator code completion happy.)
list(APPEND QML_IMPORT_PATH "/usr/lib/x86_64linux-gnu/qt6/qml/QtQuick")


# Prevent adding duplicate values at each run of CMake.
list(REMOVE_DUPLICATES QML_IMPORT_PATH)

# The variable is cached in ${BUILD_DIR}/CMakeCache.txt. We need FORCE to
# change it there immediately. Also, add a comment to the cache file.
set(QML_IMPORT_PATH ${QML_IMPORT_PATH}
    CACHE STRING "Qt Creator 4.1 extra qml import paths"
    FORCE
)


qt_standard_project_setup()

qt_add_executable(appPokemons
    main.cpp
)

qt_add_qml_module(appPokemons
    URI Pokemons
    VERSION 1.0
    QML_FILES
        Main.qml
        RESOURCES images/pikachu.gif
        RESOURCES images/search.svg
        RESOURCES images/question.gif
        SOURCES searchbtnmodel.h searchbtnmodel.cpp
        SOURCES tablemodel.h tablemodel.cpp
        SOURCES imagemodel.h imagemodel.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appPokemons PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appPokemons
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appPokemons
    PRIVATE Qt6::Quick
)
target_link_libraries(appPokemons
    PRIVATE Qt6::Network
)

include(GNUInstallDirs)
install(TARGETS appPokemons
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
