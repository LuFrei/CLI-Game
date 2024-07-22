#include "Wall.h"

CHAR_INFO wallMat = {
    ' ', BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY
};

Wall::Wall()
    : Entity(20, 9, 2, 8){
        AddRenderer(wallMat);
        AddCollider();
}

Wall::Wall(int x, int y)
    : Entity(x, y, 2, 8){
        AddRenderer(wallMat);
        AddCollider();
}

Wall::~Wall(){
}

void Wall::Update(){

}
