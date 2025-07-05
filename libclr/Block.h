#pragma once

#include "export.h"
#include <windows.h>
#include "Rect.h"

namespace clr{

/// @brief Represents the 2D data that will be displayed on screen
class LIB_API Block{
private:
    // TODO: Probably remove Z from here.
    // right now we use this z to find what layer to add Block to in Screen.AddToRenderQueue.
    int _z; 
public:
    Rect rect;
    CHAR_INFO* dataArr;

    Block(int width, int height);
    Block(Rect rect);
    ~Block();

    void z(int z){_z = z;}
    int z(){return _z;}

    /// @brief Fills the Block ractangle with a single CHAR_INFO
    /// @param material CHAR_INFO to fill the Block with.
    void Fill(CHAR_INFO material);
    void Resize(int newWidth, int newHeight);
    void SetRect(Rect newRect);
};
}