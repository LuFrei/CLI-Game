#pragma once

#include <forward_list>

#include "../CLGEngine/Entity.h"
#include "../CLGEngine/TileMap.h"
#include "Maps.h"
#include "Entities/Character.h"

class GameManager : public ISubject {
private:
    static GameManager* _gm;
    TileMap* _level;
    int _currLevelIdx;
    Maps* _levels;
    static Character* _player;
public:
    GameManager();
    ~GameManager();
    void SetPlayer(Character* p);
    void SetLevel(int idx);
    TileMap* GetLevelTileMap();
    int GetCurrentLevelIdx() {return _currLevelIdx;};

// ISubject
private:
    std::forward_list<IObserver*> _subscribers;
public:
    virtual void AddSubscriber(IObserver* o);
    virtual void RemoveSubscriber(IObserver* o);
    virtual void Notify();
};