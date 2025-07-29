#pragma once

#include "export.h"
#include <vector>
#include <windows.h>

#include "Color.h"

namespace clr{

/// @brief Represents the 2D data that will be displayed on screen
class LIB_API Block{
protected:
    int _width, _height;
    // TODO: Probably remove Z from here.
    // right now we use this z to find what layer to add Block to in Screen.AddToRenderQueue.
    int _z; 
public:
    int x, y;
    std::vector<CHAR_INFO> dataArr; // SET Up Profiler to test Arr vs Vector

    Block();
    Block(int width, int height);
    Block(int x, int y, int width, int height);
    ~Block();

    int width() {return _width;}
    int height() {return _height;}

    void z(int z){_z = z;}
    int z(){return _z;}


    void SetData(std::vector<CHAR_INFO> newData);
    /// @brief Fills the Block ractangle with a single CHAR_INFO
    /// @param material CHAR_INFO to fill the Block with.
    void Fill(CHAR_INFO material);
    void Resize(int newWidth, int newHeight);
    // is this even necessary?
    void Reposition(int newX, int newY);
};
}