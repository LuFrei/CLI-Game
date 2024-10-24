#include "GameManager.h"

GameManager* GameManager::_instance = nullptr;
GameManager::GameManager()
: _levels(new Maps())
, _currLevelIdx(0){
    try{
        if(_instance != nullptr){
            throw "a GameManager already exists.";
        }
    } catch(std::string) 
    { }

    _instance = this;
    _level = new TileMap(Maps::list[_currLevelIdx]);
}

GameManager::~GameManager(){
    delete _level;
    delete _levels;
    _instance = nullptr;
}

void GameManager::SetLevel(int idx){
    _currLevelIdx = idx;
    _level->SetMap(Maps::list[_currLevelIdx]);
}

TileMap* GameManager::GetLevelTileMap(){
    return _level;
}

int GameManager::GetCurrentLevelIdx(){
    return _currLevelIdx;
}


void GameManager::AddSubscriber(IObserver* o){
    _subscribers.emplace_front(o);
}

void GameManager::RemoveSubscriber(IObserver* o){
    _subscribers.remove(o);
}

void GameManager::Notify(){
    for(IObserver* o : _subscribers){
        o->OnNotify();
    }
}