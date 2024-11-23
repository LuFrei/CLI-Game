add_library(Components Component.h Collider.cpp)

add_subdirectory(Renderers)
target_link_libraries(Components PUBLIC Renderers)