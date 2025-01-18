cmake_minimum_required(VERSION 3.30)
project(snake)

set(CMAKE_CXX_STANDARD 20)

enable_testing()

include_directories(src)
add_subdirectory(src)
add_subdirectory(tests)

