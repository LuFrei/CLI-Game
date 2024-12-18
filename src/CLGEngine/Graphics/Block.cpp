#include "Block.h"
#include "ASCII.h"

namespace CLGEngine{
CHAR_INFO defaultMaterial = {
	ASCII_SHADE1,
	BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED
};

Block::Block(Vector2<int> size) {
    rect = {{0,0}, (Vector2<float>)size}; //TODO: Some pooint find out how to add custom explicit/ implicit converstions.
    dataArr = new CHAR_INFO[size.x * size.y];
    Fill(defaultMaterial);
}

Block::Block(Rect rect) {
    this->rect = rect;
    dataArr = new CHAR_INFO[rect.size.x * rect.size.y];
    Fill(defaultMaterial);
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
void Block::Resize(Vector2<int> size){
    rect.size = (Vector2<float>)size;

    delete dataArr; // This shouldn't be null, but check here if ther's an error.
    dataArr = new CHAR_INFO[size.x * size.y];
    Fill(defaultMaterial); // Do we want this here??
}
}
