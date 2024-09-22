cmake_minimum_required(VERSION 3.28)
project(lab1_1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -pthread -lboost_thread")
add_executable(lab1_1 main.cpp
        sender.cpp
        sender.h
        receiver.cpp
        receiver.h
)


