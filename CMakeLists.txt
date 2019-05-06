cmake_minimum_required(VERSION 3.0)
project(ImageBatch VERSION 1.0)

# set(CMAKE_CXX_STANDARD 14)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-std=c++17)


add_executable(ImageBatch main.cpp utils.cpp argumentParser.cpp mode.cpp renamemode.cpp convertmode.cpp)

set_target_properties(ImageBatch PROPERTIES CXX_STANDARD 17)

file(COPY ${CMAKE_SOURCE_DIR}/help.txt DESTINATION ${CMAKE_BINARY_DIR})

set(FETCHCONTENT_QUIET OFF CACHE BOOL "disabled quiet mode to fetch content" FORCE)
include(FetchContent)

add_subdirectory(externals)
# add_subdirectory(test)

target_link_libraries(ImageBatch PRIVATE stb)


