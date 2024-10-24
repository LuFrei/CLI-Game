add_library(CLGEngine Input.cpp Time.cpp Game.cpp EntityManager.cpp Entity.cpp TileMap.cpp MapData.h)

add_subdirectory(Graphics)
add_subdirectory(CORE)
add_subdirectory(Component)
target_link_libraries(CLGEngine PUBLIC CORE Graphics Component)