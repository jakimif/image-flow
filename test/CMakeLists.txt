cmake_minimum_required(VERSION 3.0)
set(FETCHCONTENT_QUIET OFF CACHE BOOL "disabled quiet mode to fetch content" FORCE)

# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.10.0
)

FetchContent_MakeAvailable(googletest)

add_executable(TestArgumentParser argumentParser.cpp)
target_link_libraries(TestArgumentParser PRIVATE gtest_main)


