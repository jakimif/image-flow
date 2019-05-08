cmake_minimum_required(VERSION 3.0)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)


FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.13.0
)

FetchContent_MakeAvailable(googletest)

add_executable(TestArgumentParser 
  argumentParser.cpp
  "${CMAKE_SOURCE_DIR}/argumentParser.cpp"
  "${CMAKE_SOURCE_DIR}/utils.cpp"
)

target_include_directories(TestArgumentParser PRIVATE "${CMAKE_SOURCE_DIR}")
target_link_libraries(TestArgumentParser PRIVATE gtest_main)



