cmake_minimum_required(VERSION 3.23)
project(server)

set(CMAKE_CXX_STANDARD 14)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)

add_executable(server
        serverMain.cpp
        ConnectManager.h
        ConnectManager.cpp
        Worker.h
        Worker.cpp
        FileWriter.h
        FileWriter.cpp
        ServerWorkerI.h)


#выключает copy elision
add_compile_options(-fno-elide-constructors)
