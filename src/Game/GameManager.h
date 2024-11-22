#pragma once

#include <forward_list>

#include "../CLGEngine/Entity.h"
#include "../CLGEngine/TileMap.h"
#include "../CLGEngine/CORE/Vector2.h"
#include "../CLGEngine/CORE/ISubject.h"
#include "Maps.h"

class GameManager : public CLGEngine::ISubject {
// Core
private:
    static GameManager* _instance;
public:
    GameManager();
    ~GameManager();

// Level
private:
    Maps* _levels;
    int _currLevelIdx;
    TileMap* _level;
public:
    void SetLevel(int idx);
    TileMap* GetLevelTileMap();
    int GetCurrentLevelIdx();


// ISubject
private:
    std::forward_list<CLGEngine::IObserver*> _subscribers;
public:
    virtual void AddSubscriber(CLGEngine::IObserver* o);
    virtual void RemoveSubscriber(CLGEngine::IObserver* o);
    virtual void Notify();
};