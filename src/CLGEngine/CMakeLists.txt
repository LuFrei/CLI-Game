add_library(CLGEngine Entity.cpp Input.cpp Time.cpp Game.cpp EntityManager.cpp Collider.cpp)

add_subdirectory(Graphics)
add_subdirectory(CORE)
target_link_libraries(CLGEngine PUBLIC CORE Graphics)