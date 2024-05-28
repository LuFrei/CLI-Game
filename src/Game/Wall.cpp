#include "Wall.h"

Wall::Wall():
    Entity(40, 9, 2, 8){
        rend = new Graphics::Renderer(position.x, position.y, size.x, size.y);
        col = new Collider(position.x, position.y, size.x, size.y);
}

Wall::~Wall(){
    delete rend;
    delete col;
}

void Wall::Update(){

}
