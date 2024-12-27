#include "GameManager.h"

GameManager* GameManager::_instance = nullptr;
GameManager::GameManager()
: CLGEngine::Entity(0,0,0,0)
, _levels(new Maps())
, _currLevelIdx(0){
    try{
        if(_instance != nullptr){
            throw "a GameManager already exists.";
        }
    } catch(std::string) 
    { }

    _instance = this;
    _level = new TileMap(Maps::list[_currLevelIdx]);
    _levelRenderer = new CLGEngine::CharMapRenderer(this, *_level, true);
}

GameManager::~GameManager(){
    delete _level;
    delete _levels;
    delete _levelRenderer;
    _instance = nullptr;
}

void GameManager::SetLevel(int idx){
    CLGEngine::Vector2<int> lastEnd = _level->offset + _level->endPos;

    _currLevelIdx = idx;
    _level->SetMap(Maps::list[_currLevelIdx]);

    _level->offset = lastEnd - _level->startPos; // maybe this can part of SetMap?
}

TileMap* GameManager::GetLevelTileMap(){
    return _level;
}

int GameManager::GetCurrentLevelIdx(){
    return _currLevelIdx;
}


void GameManager::AddSubscriber(CLGEngine::IObserver* o){
    _subscribers.emplace_front(o);
}

void GameManager::RemoveSubscriber(CLGEngine::IObserver* o){
    _subscribers.remove(o);
}

void GameManager::Notify(){
    for(CLGEngine::IObserver* o : _subscribers){
        o->OnNotify();
    }
}