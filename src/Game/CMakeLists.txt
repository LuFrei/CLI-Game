add_library(Game GameManager.cpp Level.cpp Maps.cpp)

add_subdirectory(Entities)
target_link_libraries(Game PUBLIC Entities)