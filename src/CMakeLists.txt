cmake_minimum_required ( VERSION 2.8 )
project (zenmon)
set (zenmon_VERSION_MAJOR 0)
set (zenmon_VERSION_MINOR 1)
set (CMAKE_CXX_FLAGS "-O2" )

include_directories( 
"${PROJECT_BINARY_DIR}"
)

add_library( zenmon SHARED 
  zenmon.cpp
  process.cpp
  common.cpp
  loader.cpp
  cpu.cpp
)  
  
target_link_libraries( zenmon
  pthread
)