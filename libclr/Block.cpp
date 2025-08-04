#define LIB_EXPORTS
#include "Block.h"
#include "ASCII.h"

namespace clr {

Block::Block():
    Block(0, 0, 1, 1)
{ }
    
Block::Block(int width, int height) :
    Block(0, 0, width, height){
}

Block::Block(int x, int y, int width, int height) {
    this->x = x;
    this->y = y;
    _width = width;
    _height = height;
    dataArr.resize(width * height);
}

Block::~Block(){
    // delete dataArr;
}

// Should cheack to make sure CHAR_INFO is <= sizeLimit
// This does nothing.
void Block::SetData(std::vector<CHAR_INFO> newData){
    int sizeLimit = _width * _height;
    dataArr = newData;
}

void Block::Fill(CHAR_INFO material){
    dataArr.clear();
    dataArr.resize(_width * _height);
    for(int i = 0; i < (_width * _height); i++){
        dataArr[i] = material;
    }
}

// NOTE: Make new empty one w/ new size. Fill with Defalu,mat, and have Each Renderer handle howt o refill arr.
// Some RendererTypes may have their own Resize, some may not need it. If they do, thye should call this Resize FIRST
void Block::Resize(int newWidth, int newHeight){ // If we are to make this multipurpose for CLRendering and GL Rendering, we should turn this into a float
    _width = newWidth;
    _height = newHeight;

    // TODO: Need to reevaluate if this is necessary.
    //      Before vector refctor, we erased the array, so I'm keeping it here for now.
    dataArr.resize(_width * _height);
    // int daSize = dataArr.size();
}

void Block::SetTextData(std::string text){
    // Would it be faster to just fill the empty space in the loop?
    dataArr.clear();
    dataArr.resize(_width * _height);

    for(int i = 0; i < text.size() && i < _width * _height; i++){
        dataArr[i].Char.AsciiChar = text[i];
        dataArr[i].Attributes = WHITE;
    }
}
} // namespace clr