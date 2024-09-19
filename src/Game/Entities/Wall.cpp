#include "Wall.h"

CHAR_INFO wallMat = {
    ' ', BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY
};

Wall::Wall(int x, int y, int width, int height)
    : Entity(x, y, width, height){
        _rend = new CLGEngine::Renderer(this, wallMat);
        _col = new Collider(this);
}

Wall::~Wall(){
    delete _rend;
    delete _col;
}

void Wall::Update(){
}
