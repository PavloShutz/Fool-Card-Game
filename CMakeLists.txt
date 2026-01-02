cmake_minimum_required(VERSION 3.28)
project(FoolCardGame LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

include_directories(include)

add_executable(FoolCardGame
    "src/main.cpp"
    "include/Game.hpp"
    "src/Game.cpp"
    "include/Card.hpp"
)
target_compile_features(FoolCardGame PRIVATE cxx_std_17)
target_link_libraries(FoolCardGame PRIVATE SFML::Graphics)
