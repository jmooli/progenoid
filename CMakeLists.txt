cmake_minimum_required(VERSION 3.28)
project(Progenoid LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(progenoid 
    src/main.cpp
    src/core/resource_manager.cpp
    src/entities/paddle.cpp
    src/entities/ball.cpp
    src/entities/block.cpp
    src/entities/wall.cpp
    src/core/game.cpp
    src/core/scene.cpp
    src/entities/game_object.cpp
)
target_compile_features(progenoid PRIVATE cxx_std_17)
target_link_libraries(progenoid PRIVATE SFML::Graphics)
