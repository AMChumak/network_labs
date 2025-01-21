cmake_minimum_required(VERSION 3.16)

project(snake_gui VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Multimedia)

qt_standard_project_setup(REQUIRES 6.8)



qt_add_executable(appsnake_gui
        main.cpp
)

qt_add_resources(QRC_FILES resources.qrc)
target_sources(appsnake_gui PRIVATE ${QRC_FILES})

qt_add_qml_module(appsnake_gui
        URI snake_gui
        VERSION 1.0
        QML_FILES Main.qml
        QML_FILES HomePage/HomePage.qml
        RESOURCES images/background.png
        RESOURCES images/my_snake_body.png
        RESOURCES images/my_snake_head.png
        RESOURCES images/enemy_snake_body.png
        RESOURCES images/enemy_snake_head.png
        RESOURCES images/snakes_logo.png
        RESOURCES images/food.png
        RESOURCES fonts/retro.ttf
        RESOURCES images/UI-01.png
        RESOURCES images/UI-02.png
        RESOURCES images/UI-03.png
        RESOURCES images/UI-04.png
        RESOURCES images/UI-05.png
        RESOURCES images/UI-06.png
        RESOURCES images/UI-7.png
        RESOURCES images/UI-8.png
        RESOURCES images/UI-18.png
        RESOURCES images/UI-19.png
        RESOURCES images/UI-58.png
        RESOURCES images/UI-104.png
        RESOURCES images/UI-105.png
        RESOURCES sounds/button.mp3
        RESOURCES sounds/song.mp3
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appsnake_gui PROPERTIES
        #    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appsnake_gui
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
)

target_link_libraries(appsnake_gui
        PRIVATE Qt6::Quick Qt6::Multimedia
)

include(GNUInstallDirs)
install(TARGETS appsnake_gui
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
