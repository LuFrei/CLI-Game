#include "CLGEngine/Entity.h"
#include "CLGEngine/Game.h"
#include "CLGEngine/TileMap.h"

#include "Game/Entities/Character.h"
#include "Game/Entities/ScreenText.h"
#include "Game/Entities/Wall.h"
#include "Game/Entities/Door.h"
#include "Game/Entities/Button.h"
#include "Game/Maps.h"
#include "Game/Entities/LevelTrigger.h"
#include "Game/GameManager.h"

using namespace CLGEngine;

int main()
{
    Game game = Game();
//TODO: REMINDER! Lets write everything in main 
// - as simple as posisble. THEN, we move into modularization
    GameManager* gm = new GameManager();

    Character* player = new Character({25, 21});
    player->gm = gm;
    player->AddTileMap(gm->GetLevelTileMap()); // MAke this internal. No need if we reference gm in Player.

    ScreenText* instructionalText = new ScreenText({0, 29});
    ScreenText* mapNameText = new ScreenText({20, 0});
    instructionalText->SetText("[SpaceBar]  [<][>]");

    Door* door = new Door(
        {
            {29, 21}, // pos
            {1, 2}  // size
        },
        DoorCode::Blue
    );
    Door* door1 = new Door(
        {
            {31, 21}, // pos
            {1, 2}  // size
        },
        DoorCode::Blue,
        true
    );
    Door* door2 = new Door(
        {
            {33, 21}, // pos
            {1, 2}  // size
        },
        DoorCode::Red,
        false
    );
    Door* door3 = new Door(
        {
            {35, 21}, // pos
            {1, 2}  // size
        },
        DoorCode::Red,
        true
    );

    Button* blueSwitch = new Button({door, door1});
    Button* redSwitch = new Button({door2, door3});

    blueSwitch->SetPosition({27, 22});
    redSwitch->SetPosition({23, 22});

    game.Play();
    
    // TODO: Make an auto Entitiy cleaner.
    delete redSwitch;
    delete blueSwitch;
    delete door;
    delete door1;
    delete door2;
    delete door3;
    delete player;
    delete instructionalText;
    delete mapNameText;
    delete gm;
}


// Need to know "what" to instantiate and the positions.