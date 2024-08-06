cmake_minimum_required(VERSION 3.29)
project(Cli-Game VERSION 0.0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(CLI-Game src/main.cpp src/Game/Character.cpp src/Game/Wall.cpp src/Game/TileMap.cpp src/Game/TileMapChecker.cpp)
add_subdirectory(src/CLGEngine)
target_link_libraries(CLI-Game PUBLIC CLGEngine)