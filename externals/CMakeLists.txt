cmake_minimum_required(VERSION 3.0)

FetchContent_Declare(
  stbcontents
  GIT_REPOSITORY https://github.com/nothings/stb.git
)

FetchContent_MakeAvailable(stbcontents)

FetchContent_GetProperties(stbcontents SOURCE_DIR _stbSourceDir)

add_library(stb INTERFACE)
target_include_directories(stb INTERFACE ${_stbSourceDir})


# FetchContent_Declare(
#   nlohmann_json
#   GIT_REPOSITORY https://github.com/nlohmann/json.git
#   GIT_TAG master
# )

# FetchContent_MakeAvailable(nlohmann_json)

# FetchContent_GetProperties(nlohmann_json SOURCE_DIR _nlohmann_jsonSourceDir)
# target_include_directories(nlohmann_json INTERFACE ${_nlohmann_jsonSourceDir})

