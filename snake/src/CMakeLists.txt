cmake_minimum_required(VERSION 3.30)
project(game)

add_subdirectory(proto)
add_subdirectory(engine)


add_executable(game main.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC engine)