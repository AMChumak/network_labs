# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/appguiApp_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/appguiApp_autogen.dir/ParseCache.txt"
  "appguiApp_autogen"
  )
endif()
