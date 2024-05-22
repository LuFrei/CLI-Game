#include "Wall.h"

Wall::Wall():
    Entity(40, 9, 2, 8){
        rend = new Graphics::Renderer(position.x, position.y, size.x, size.y);
}

Wall::~Wall(){
    delete rend;
}

void Wall::Update(){

}
