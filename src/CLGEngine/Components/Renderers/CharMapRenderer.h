#include "Renderer.h"

#include <map>
#include <array>

namespace CLGEngine{
/// @brief Creates a graphical block using an array of characters.
class  CharMapRenderer : public Renderer {
private:
    TileMap* _charMap; // Type name is more missleading than car name.
public:
    // Can we do this BEFORE feeding the chardata to the renderer...?
    bool usingMaterialMap;
    std::map<char, CHAR_INFO> matMap;
    short* colorMapArr;

    CharMapRenderer(Entity* ent, TileMap& charMap);
    CharMapRenderer(Entity* ent, TileMap& charMap, bool isSquare);

    // TODO: Animations
    void SetCharMap(TileMap& charMap);
};
}