add_library(CLGEngine Entity.cpp Input.cpp Time.cpp CORE/MainWindow.cpp CORE/Utility.h)

add_subdirectory(Graphics)
target_link_libraries(CLGEngine PUBLIC Graphics)

target_link_directories(CLGEngine PUBLIC 
                        "${PROJECT_SOURCE_DIR}/Graphics")