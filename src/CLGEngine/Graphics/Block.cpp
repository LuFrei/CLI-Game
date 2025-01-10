#include "Block.h"
#include "ASCII.h"

namespace CLGEngine{

Block::Block(Vector2<int> size) {
    rect = {{0,0}, (Vector2<float>)size}; //TODO: Some pooint find out how to add custom explicit/ implicit converstions.
    dataArr = new CHAR_INFO[size.x * size.y];
}

Block::Block(Rect rect) {
    this->rect = rect;
    dataArr = new CHAR_INFO[rect.size.x * rect.size.y];
}

Block::~Block(){
    delete dataArr;
}

void Block::Fill(CHAR_INFO material){
    for(int i = 0; i < (rect.size.x * rect.size.y); i++){
        dataArr[i] = material;
    }
}

// NOTE: Make new empty one w/ new size. Fill with Defalu,mat, and have Each Renderer handle howt o refill arr.
// Some RendererTypes may have their own Resize, some may not need it. If they do, thye should call this Resize FIRST
void Block::Resize(Vector2<int> size){ // If we are to make this multipurpose for CLRendering and GL Rendering, we should turn this into a float
    rect.size = (Vector2<float>)size;

    delete dataArr; // This shouldn't be null, but check here if ther's an error.
    dataArr = new CHAR_INFO[size.x * size.y];
}

void Block::SetRect(Rect newRect){
    Resize((Vector2<int>)newRect.size);
    rect.position = newRect.position;
}

void Block::SetLayer(int layer){
    z = layer;
}
}
