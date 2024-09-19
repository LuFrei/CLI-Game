add_library(Game GameManager.cpp LevelTrigger.cpp Maps.cpp ScreenText.cpp TileMapChecker.cpp)

add_subdirectory(Entities)
target_link_libraries(Game PUBLIC Entities)