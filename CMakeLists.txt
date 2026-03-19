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

set(SOURCES 
"src/main.cpp"
 "src/Game.cpp"
 "src/Player.cpp"
 "src/Human.cpp"
 "src/AI.cpp"
)

add_executable(FoolCardGame ${SOURCES})
target_include_directories(FoolCardGame
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

add_custom_target(copy_assets
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_LIST_DIR}/copy_assets.cmake
)
add_dependencies(FoolCardGame copy_assets)

target_compile_features(FoolCardGame PRIVATE cxx_std_17)
target_link_libraries(FoolCardGame PRIVATE SFML::Graphics)
