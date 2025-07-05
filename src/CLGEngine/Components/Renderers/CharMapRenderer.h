#pragma once

#include "Renderer.h"

#include <map>
#include <array>
#include "../../TileMap.h"

namespace CLGEngine{
/// @brief Creates a graphical block using an array of characters.
class  CharMapRenderer : public Renderer {
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