cmake_minimum_required ( VERSION 2.8 )
project (proctreemon)
set (proctreemon_VERSION_MAJOR 0)
set (proctreemon_VERSION_MINOR 1)
set (CMAKE_CXX_FLAGS "-O2" )

include_directories(
"${PROJECT_BINARY_DIR}"
)

add_library( proctreemon SHARED
  proctreemon.cpp
  process.cpp
  common.cpp
  loader.cpp
  cpu.cpp
)

target_link_libraries( proctreemon
  pthread
)
