# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/appPokemons_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/appPokemons_autogen.dir/ParseCache.txt"
  "appPokemons_autogen"
  )
endif()
