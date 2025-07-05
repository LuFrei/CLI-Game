cmake_minimum_required(VERSION 3.29)
project(CLI-Game VERSION 0.0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Shared PROPERTIES LINKER_LANGUAGE CXX)

add_library(Shared STATIC shared.h)
add_executable(${PROJECT_NAME} src/main.cpp)
add_executable(SecondScreen subproc/main.cpp)

include_directories(PUBLIC ./libclr)
add_subdirectory(src/CLGEngine)
add_subdirectory(src/Game)
add_subdirectory(libclr)
target_link_libraries(${PROJECT_NAME} PUBLIC CLGEngine Game libclr)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND cp -u ${PROJECT_SOURCE_DIR}/build/libclr/Debug/libclr.dll ${CMAKE_BINARY_DIR}/Debug
)