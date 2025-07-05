#define LIB_EXPORTS
#include "Block.h"
#include "ASCII.h"

namespace clr{

Block::Block(){
    rect = {0,0, 1, 1}; //TODO: Some pooint find out how to add custom explicit/ implicit converstions.
    dataArr = new CHAR_INFO[width * height];
}
    
Block::Block(int width, int height) {
    rect = {0,0, width, height}; //TODO: Some pooint find out how to add custom explicit/ implicit converstions.
    dataArr = new CHAR_INFO[width * height];
}

Block::Block(Rect rect) {
    this->rect = rect;
    dataArr = new CHAR_INFO[rect.width * rect.height];
}

Block::~Block(){
    delete dataArr;
}

void Block::Fill(CHAR_INFO material){
    for(int i = 0; i < (rect.width * rect.height); i++){
        dataArr[i] = material;
    }
}

// NOTE: Make new empty one w/ new size. Fill with Defalu,mat, and have Each Renderer handle howt o refill arr.
// Some RendererTypes may have their own Resize, some may not need it. If they do, thye should call this Resize FIRST
void Block::Resize(int newWidth, int newHeight){ // If we are to make this multipurpose for CLRendering and GL Rendering, we should turn this into a float
    rect.width = newWidth;
    rect.height = newHeight;

    delete dataArr; // This shouldn't be null, but check here if ther's an error.
    dataArr = new CHAR_INFO[rect.width * rect.height];
}

void Block::SetRect(Rect newRect){
    Resize(newRect.width, newRect.height);
    rect.x = newRect.x;
    rect.y = newRect.y;
}
}
