#include "LevelTrigger.h"

#include "../GameManager.h"
#include "../Maps.h"

CHAR_INFO material = {' ', BACKGROUND_GREEN | BACKGROUND_RED};

LevelTrigger::LevelTrigger(CLGEngine::CORE::Vector2<int> position, std::string levelName)
: Entity(position.x, position.y, 1, 1)
, _col(new CLGEngine::Collider(this))
, _rend(new CLGEngine::Renderer(this, material)) { 
    _col->isSolid = false;
}

LevelTrigger::~LevelTrigger(){
    delete _col;
    delete _rend;
}

void LevelTrigger::Update(){
    if(CLGEngine::Collider* hit = _col->GetHit()){
        if(hit->entity->name == "player"){ 
            gm->SetLevel(gm->GetCurrentLevelIdx() + 1);
        }
    }

    _col->ClearHit(); //TODO: really need to make this automatic...
}