#include "Door.h"

#include <array>
#include "../../CLGEngine/Graphics/ASCII.h"

const std::array<short, 5> CODE_COLORS= {
    FOREGROUND_RED,
    FOREGROUND_BLUE,
    FOREGROUND_GREEN,
    FOREGROUND_BLUE | FOREGROUND_RED,
    FOREGROUND_BLUE | FOREGROUND_GREEN
};

#define CLOSED_TEXTURE      ASCII_SHADE4
#define OPEN_TEXTURE        ASCII_SHADE1
#define CLOSED_INTENSITY    FOREGROUND_INTENSITY
#define OPEN_INTENSITY      0


Door::Door(CLGEngine::Rect rect, DoorCode code, bool isOpen)
: Entity(
    rect.position.x, 
    rect.position.y, 
    rect.size.x, 
    rect.size.y
  )
, _col(new CLGEngine::Collider(this))
, _code(code)
, _isOpen(isOpen){
    // !!! If failing check if DoorCode reduces to an int here or above!
    short intensity = isOpen ? OPEN_INTENSITY : CLOSED_INTENSITY;
    CHAR_INFO doorGfxData = {
        isOpen ? OPEN_TEXTURE : CLOSED_TEXTURE,
        CODE_COLORS[code] | intensity
    };


    _col->SetActive(!isOpen);
    _blocRend = new CLGEngine::BlockRenderer(this, doorGfxData, true);
    _blocRend->z(0);
}

Door::Door(CLGEngine::Rect rect, DoorCode code)
: Door(rect, code, false) {}

void Door::Open(){
    _isOpen = true;
    // Investigate: Worth keeping a persistent CHAR_INFO and only changing color & texture?
    CHAR_INFO doorGfxData = {
        OPEN_TEXTURE,
        CODE_COLORS[_code] | OPEN_INTENSITY 
    };
    // TODO(2): Add functionality to change material in BlockRenderer
    _col->SetActive(false);
}

void Door::Close(){
    _isOpen = false;
    // Investigate: Worth keeping a persistent CHAR_INFO and only changing color & texture?
    CHAR_INFO doorGfxData = {
        CLOSED_TEXTURE,
        CODE_COLORS[_code] | CLOSED_INTENSITY 
    };
    // TODO(2)
    _col->SetActive(true);
}