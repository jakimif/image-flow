cmake_minimum_required(VERSION 3.0)
project(ImageFlow VERSION 1.0)

add_definitions(-std=c++17)

add_executable(ImageFlow 
  main.cpp 
  threadpool.cpp
  utils.cpp 
  argumentParser.cpp 
  mode.cpp 
  renamemode.cpp 
  convertmode.cpp 
  resizemode.cpp
  scalemode.cpp
  modesfactory.cpp
  image.cpp
)

set_target_properties(ImageFlow PROPERTIES CXX_STANDARD 17)

file(COPY ${CMAKE_SOURCE_DIR}/help.txt DESTINATION ${CMAKE_BINARY_DIR})

set(FETCHCONTENT_QUIET OFF CACHE BOOL "disabled quiet mode to fetch content" FORCE)
include(FetchContent)

add_subdirectory(externals)
add_subdirectory(test)

target_link_libraries(ImageFlow PRIVATE stb)


