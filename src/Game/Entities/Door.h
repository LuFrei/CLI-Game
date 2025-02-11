#pragma once

// #include <CLGEngineCORE>  <-- Make this happen! 2025!
#include "../../CLGEngine/Entity.h"
#include "../../CLGEngine/Components/Collider.h"
#include "../../CLGEngine/Components/Renderers/BlockRenderer.h"

enum DoorCode {
    Red, Blue, Green, Purple, Cyan
};

class Door 
: public CLGEngine::Entity{
private:
    int _code;
    CLGEngine::Collider* _col;
    CLGEngine::BlockRenderer* _blocRend;
    bool _isOpen;
public:
    int code(){return _code;}
    int isOpen(){return _isOpen;}

    /* @brief Doors for the game.

    @param rect: Shape and position of the door.
    @param code: *Must be 0-4.* The switch & key code this door will respond to. 
    @param isOpen: Whether the door starts opened or closed.
    */
    Door(CLGEngine::Rect rect, DoorCode code, bool isOpen);
    Door(CLGEngine::Rect rect, DoorCode code);
    ~Door();

    void Update() {};

    void Open();
    void Close();
};