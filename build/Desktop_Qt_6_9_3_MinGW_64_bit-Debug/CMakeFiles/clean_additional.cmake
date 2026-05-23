# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\WhiteBoard_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\WhiteBoard_autogen.dir\\ParseCache.txt"
  "WhiteBoard_autogen"
  )
endif()
