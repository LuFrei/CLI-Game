cmake_minimum_required(VERSION 4.2) # 4.2 minimun req for VS 2026 support.
project(CLI-Game VERSION 0.0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# global library
link_directories(./libclr/build/Debug)
include_directories(PUBLIC ./libclr)
include_directories(${CMAKE_SOURCE_DIR})

add_executable(${PROJECT_NAME} src/main.cpp)
add_subdirectory(src/CLGEngine)
add_subdirectory(src/Game)
target_link_libraries(${PROJECT_NAME} PUBLIC CLGEngine Game libclr Rpcrt4)

add_executable(SecondScreen 
    subproc/main.cpp 
    subproc/ScrollableTextView.cpp 
    subproc/globals.cpp
)
add_subdirectory(subproc/Logger)
add_subdirectory(subproc/WatchList)
target_include_directories(SecondScreen PUBLIC subproc)
target_link_libraries(SecondScreen PUBLIC Logger WatchList libclr Rpcrt4)


add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND cp -u ${PROJECT_SOURCE_DIR}/libclr/build/Debug/libclr.dll ${CMAKE_BINARY_DIR}/Debug
)