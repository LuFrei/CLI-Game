add_library(CLGEngine Input.cpp Time.cpp Game.cpp EntityManager.cpp)

add_subdirectory(Graphics)
add_subdirectory(CORE)
target_link_libraries(CLGEngine PUBLIC CORE Graphics Component)