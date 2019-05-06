cmake_minimum_required(VERSION 3.0)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)



FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.10.0
)

FetchContent_MakeAvailable(googletest)

add_executable(TestArgumentParser 
  argumentParser.cpp
  "${CMAKE_SOURCE_DIR}/argumentParser.cpp"
  "${CMAKE_SOURCE_DIR}/utils.cpp"
)

set_target_properties(ImageBatch PROPERTIES CXX_STANDARD 17)

target_include_directories(TestArgumentParser PRIVATE ${CMAKE_SOURCE_DIR})

target_link_libraries(TestArgumentParser PRIVATE gtest_main)


