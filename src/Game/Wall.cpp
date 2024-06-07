#include "Wall.h"

Wall::Wall()
    : Entity(20, 9, 2, 8){
        AddRenderer();
        AddCollider();
}

Wall::~Wall(){
}

void Wall::Update(){

}
