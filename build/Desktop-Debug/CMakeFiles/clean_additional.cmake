# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/lucilena_final_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/lucilena_final_autogen.dir/ParseCache.txt"
  "lucilena_final_autogen"
  )
endif()
