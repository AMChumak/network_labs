# CMake generated Testfile for 
# Source directory: /home/anton/Documents/Networks/course3/snake/tests
# Build directory: /home/anton/Documents/Networks/course3/snake/cmake-build-debug/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[snakeGTests]=] "snakeTests")
set_tests_properties([=[snakeGTests]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/anton/Documents/Networks/course3/snake/tests/CMakeLists.txt;31;add_test;/home/anton/Documents/Networks/course3/snake/tests/CMakeLists.txt;0;")
subdirs("../_deps/googletest-build")
