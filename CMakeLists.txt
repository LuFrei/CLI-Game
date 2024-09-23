cmake_minimum_required(VERSION 3.29)
project(Cli-Game VERSION 0.0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(CLI-Game src/main.cpp)
add_subdirectory(src/CLGEngine)
add_subdirectory(src/Game)
target_link_libraries(CLI-Game PUBLIC CLGEngine Game)