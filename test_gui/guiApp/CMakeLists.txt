cmake_minimum_required(VERSION 3.16)

project(guiApp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup()

qt_add_executable(appguiApp
        main.cpp
)

qt_add_qml_module(appguiApp
        URI guiApp
        VERSION 1.0
        QML_FILES
        Main.qml
        SessionPage.qml
        RESOURCES images/enemy_snake_body.png
        RESOURCES images/enemy_snake_head.png
        RESOURCES images/gift.png
        RESOURCES images/my_snake_body.png
        RESOURCES images/my_snake_head.png
        RESOURCES images/snakes_game_title.png
        RESOURCES images/snow_tilemap.png
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appguiApp PROPERTIES
        #    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appguiApp
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
)

target_link_libraries(appguiApp
        PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appguiApp
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
