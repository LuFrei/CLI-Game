#pragma once

#include <forward_list>

#include "../CLGEngine/Entity.h"
#include "../CLGEngine/TileMap.h"
#include "../CLGEngine/CORE/Vector2.h"
#include "../CLGEngine/CORE/ISubject.h"
#include "Maps.h"
#include "../CLGEngine/Components/Renderers/CharMapRenderer.h"


class GameManager 
: public CLGEngine::Entity
, public CLGEngine::ISubject {
// Core
private:
    static GameManager* _instance;
public:
    GameManager();
    ~GameManager();

// Entity
private:
    CLGEngine::CharMapRenderer* _levelRenderer;
public:
    void Update() {}

// Level
private:

    Maps* _levels; // We need this because this our soliution to store every map data in the game..
                    // TODO: Find a better way to do that..
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