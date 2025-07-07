#define LIB_EXPORTS
#include "Block.h"
#include "ASCII.h"

namespace clr{

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
    dataArr = new CHAR_INFO[width * height];
}

Block::~Block(){
    delete dataArr;
}

void Block::Fill(CHAR_INFO material){
    for(int i = 0; i < (_width * _height); i++){
        dataArr[i] = material;
    }
}

// NOTE: Make new empty one w/ new size. Fill with Defalu,mat, and have Each Renderer handle howt o refill arr.
// Some RendererTypes may have their own Resize, some may not need it. If they do, thye should call this Resize FIRST
void Block::Resize(int newWidth, int newHeight){ // If we are to make this multipurpose for CLRendering and GL Rendering, we should turn this into a float
    _width = newWidth;
    _height = newHeight;

    delete dataArr; // This shouldn't be null, but check here if ther's an error.
    dataArr = new CHAR_INFO[_width * _height];
}

void Block::Reposition(int newX, int newY){
    this->x = newX;
    this->y = newY;
}
}
