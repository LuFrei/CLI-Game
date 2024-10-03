#pragma once

#include <forward_list>

#include "../CLGEngine/Entity.h"
#include "../CLGEngine/TileMap.h"
#include "Maps.h"

class GameManager : public ISubject {
private:
    static GameManager* _instance;
    TileMap* _level;
    int _currLevelIdx;
    Maps* _levels;
public:
    GameManager();
    ~GameManager();
    void SetLevel(int idx);
    TileMap* GetLevelTileMap();
    int GetCurrentLevelIdx();

// ISubject
private:
    std::forward_list<IObserver*> _subscribers;
public:
    virtual void AddSubscriber(IObserver* o);
    virtual void RemoveSubscriber(IObserver* o);
    virtual void Notify();
};