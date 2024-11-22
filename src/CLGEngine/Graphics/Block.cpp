#include "Block.h"
#include "ASCII.h"

namespace CLGEngine{
CHAR_INFO defaultMaterial = {
	ASCII_SHADE1,
	BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED
};

Block::Block(Vector2<int> size) {
    rect = {{0,0}, {(float)size.x, (float)size.y}}; //TODO: Some pooint find out how to add custom explicit/ implicit converstions.
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
}
