add_library(CLGEngine 
    Entity.cpp 
    EntityManager.cpp 
    Game.cpp 
    Input.cpp 
    Level.cpp 
    LevelManager.cpp 
    MapData.h 
    Time.cpp 
    TileMap.cpp
)

add_subdirectory(Graphics)
add_subdirectory(CORE)
add_subdirectory(Components)
add_subdirectory(Debugging)
target_link_libraries(CLGEngine PUBLIC 
    CORE 
    Graphics 
    Components 
    Debugging
)