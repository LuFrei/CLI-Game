add_library(Game GameManager.cpp Maps.cpp TileMapChecker.cpp)

add_subdirectory(Entities)
target_link_libraries(Game PUBLIC Entities)