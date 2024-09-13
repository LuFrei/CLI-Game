#include "LevelTrigger.h"

#include "GameManager.h"
#include "Maps.h"

CHAR_INFO material = {' ', BACKGROUND_GREEN | BACKGROUND_RED};

LevelTrigger::LevelTrigger(CLGEngine::CORE::Vector2<int> position, std::string levelName)
: Entity(position.x, position.y, 1, 1)
, _col(new CLGEngine::Collider(this))
, _rend(new Graphics::Renderer(this, material))
, levelTo(levelName) { 
    _col->isSolid = false;
}

LevelTrigger::~LevelTrigger(){
    delete _col;
    delete _rend;
}

void LevelTrigger::Update(){
    if(Collider* hit = _col->GetHit()){
        if(hit->entity->name == "player"){ 
            GameManager::tileMap->SetMap(Maps::GetMap(levelTo));
        }
    }

    _col->ClearHit(); //TODO: really need to make this automatic...
}