#include "CLGEngine/Entity.h"
#include "CLGEngine/Game.h"
#include "CLGEngine/TileMap.h"

#include "Game/Entities/Character.h"
#include "Game/Entities/ScreenText.h"
#include "Game/Entities/Wall.h"
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

    Character* player = new Character({2, 0});

    gm->SetPlayer(player);

    ScreenText* instructionalText = new ScreenText({35, 10});
    ScreenText* wrappingText = new ScreenText({35, 15});
    ScreenText* thinWrappingText = new ScreenText({47, 15});
    thinWrappingText->_text->charPerLine = 1; // TODO: expose _text a little bit better..
    instructionalText->SetText("[SpaceBar]  [<][>]");
    
    
    game.mainWindow.screen->SetTileMap(gm->GetLevelTileMap()); // TODO: TileMap Renderer

    game.Play();
    
    // TODO: Make an auto Entitiy cleaner.
    delete player;
    delete instructionalText;
    delete wrappingText;
    delete thinWrappingText;
    delete gm;
}


// Need to know "what" to instantiate and the positions.