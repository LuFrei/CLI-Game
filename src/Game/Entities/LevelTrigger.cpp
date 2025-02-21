#include "LevelTrigger.h"

#include "../GameManager.h"
#include "../Maps.h"

CHAR_INFO material = {' ', BACKGROUND_GREEN | BACKGROUND_RED};

LevelTrigger::LevelTrigger(CLGEngine::Vector2<int> position, std::string levelName)
: Entity(position.x, position.y, 1, 1)
, _col(new CLGEngine::Collider(this))
, _rend(new CLGEngine::BlockRenderer(this, material)) { 
    _col->isSolid = false;
}

LevelTrigger::~LevelTrigger(){
    delete _col;
    delete _rend;
}

void LevelTrigger::OnCollision(CLGEngine::Entity* hit){
    if(hit->name == "player"){ 
        gm->SetLevel(gm->GetCurrentLevelIdx() + 1);
    }
}