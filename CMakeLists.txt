cmake_minimum_required(VERSION 3.29)
project(CLI-Game VERSION 0.0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# global library
link_directories(./libclr/build/Debug)

add_executable(${PROJECT_NAME} src/main.cpp)
add_executable(SecondScreen subproc/main.cpp)

include_directories(PUBLIC ./libclr)
add_subdirectory(src/CLGEngine)
add_subdirectory(src/Game)
include_directories(${CMAKE_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC CLGEngine Game libclr)
target_link_libraries(SecondScreen PUBLIC libclr)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND cp -u ${PROJECT_SOURCE_DIR}/libclr/build/Debug/libclr.dll ${CMAKE_BINARY_DIR}/Debug
)