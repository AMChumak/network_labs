cmake_minimum_required(VERSION 3.23)
project(client)

set(CMAKE_CXX_STANDARD 14)

add_executable(client
        ConnectManager.h
        ConnectManager.cpp
        FileReader.h
        FileReader.cpp
        Client.cpp
        Client.h
        clientMain.cpp
        ProtocolStrategy.h
        FTProtocolStrategy.h
        FTProtocolStrategy.cpp)


#выключает copy elision
add_compile_options(-fno-elide-constructors)
