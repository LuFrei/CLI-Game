#include "Renderer.h"

namespace CLGEngine{
/// @brief Creates a graphical block using an array of characters.
class CharMapRenderer : public Renderer {
private:
    TileMap* charMap; // Type name is more missleading than car name.
public:
    CharMapRenderer(Entity* ent, TileMap& charMap);
    CharMapRenderer(Entity* ent, TileMap& charMap, bool isSquare);

    // TODO: Animations
};
}