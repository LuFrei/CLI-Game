#pragma once

#include <windows.h>
#include "../CORE/Rect.h"

namespace CLGEngine{

/// @brief Represents the 2D data that will be displayed on screen
class Block{
private:
public:
    Rect rect;
    int z;
    CHAR_INFO* dataArr;

    Block(Vector2<int> size);
    Block(Rect rect);
    ~Block();

    /// @brief Fills the Block ractangle with a single CHAR_INFO
    /// @param material CHAR_INFO to fill the Block with.
    void Fill(CHAR_INFO material);
    void Resize(Vector2<int> size);
    void SetRect(Rect newRect);
    void SetLayer(int layer);
};
}