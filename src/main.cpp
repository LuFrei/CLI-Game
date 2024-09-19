#include "CLGEngine/Entity.h"
#include "CLGEngine/Game.h"
#include "CLGEngine/TileMap.h"

#include "Game/Entities/Character.h"
#include "Game/ScreenText.h"
#include "Game/Entities/Wall.h"
#include "Game/Maps.h"
#include "Game/GameManager.h"
#include "Game/LevelTrigger.h"

using namespace CLGEngine;

int main()
{
    Game game = Game();

    Maps* maps = new Maps();

    Character* player = new Character({2, 0});
    TileMap* level = new TileMap(Maps::GetMap("demoMap"));
    GameManager* gM = new GameManager();
    GameManager::player = player;
    GameManager::tileMap = level;

    LevelTrigger* levelEnd = new LevelTrigger({28, 2}, "map01");
    ScreenText* instructionalText = new ScreenText({35, 10});
    ScreenText* wrappingText = new ScreenText({35, 15});
    ScreenText* thinWrappingText = new ScreenText({47, 15});
    thinWrappingText->_text->charPerLine = 1; // TODO: expose _text a little bit better..
    instructionalText->SetText("[SpaceBar]  [<][>]");
    wrappingText->SetText("12345678901234567890The text should wrap around after 20 characters by default. But you can change this by changing maxCharsPerLine property!");
    thinWrappingText->SetText("Like this!");
    
    GameManager::player = player;
    GameManager::tileMap = level;
    player->AddTileMap(level); 
    game.mainWindow.screen->SetTileMap(level); // TODO: TileMap Renderer
    game.Play();
    
    // TODO: Make an auto Entitiy cleaner.
    delete gM;
    delete maps;
    delete level;
    delete player;
    delete levelEnd;
    delete instructionalText;
    delete wrappingText;
    delete thinWrappingText;
}
