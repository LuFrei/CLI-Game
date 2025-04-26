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
#include "CLGEngine/CORE/MainWindow.h"
#include "CLGEngine/CORE/Window.h"

#include <filesystem>

using namespace CLGEngine;

#define SUB_PROCESS_PATH "SecondScreen.exe "

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
    // Let's keep it empty for now.
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
};

int main(int argc, char* argv[])
{

    if(argc != 1){
        printf("Usage: %s [cmdline]\n", argv[0]);
        return 1;
    }
    Game game = Game();

    /*Level Setup
    * Have levels in a folder.
    * Load levels from directory into Level queue
    
    LevelManager.AddLevelToQueue(<path/to/levels>);

    * LevelManager should have direct access to entity manager to create and destroy
    
    * TileMap will be 1 value in each level.
    */

    TCHAR modFileNameOut[MAX_PATH] = {0};
    
    GetModuleFileName(NULL, modFileNameOut, MAX_PATH);

    std::filesystem::path exePath = modFileNameOut;

    std::filesystem::path appPath = exePath.parent_path();
    appPath /= "SecondScreen.exe";


    PROCESS_INFORMATION procInfo;
    STARTUPINFO startInfo;

    // This is needed
    ZeroMemory(&startInfo, sizeof(startInfo));
    startInfo.cb = sizeof(startInfo);
    ZeroMemory(&procInfo, sizeof(procInfo));
    

    // LPSTR argY = argv[0];
    // LPSTR scndApp = L"SecondScreen.exe ";
    // std::string lpCmdLn = "SecondScreen.exe " + argZ;

    // LPSTR secondScreenApp = (LPSTR)"SecondScreen"; //!! name the other app this
    // std::string appDir = strcat(SUB_PROCESS_PATH, argv[0]);

    if( !CreateProcess( NULL,                       // No module name (use command line)
        (LPSTR)appPath.string().c_str(),        // Command line
        NULL,                                       // Process handle not inheritable
        NULL,                                       // Thread handle not inheritable
        FALSE,                                      // Set handle inheritance to FALSE
        CREATE_NEW_CONSOLE,                                          // No creation flags
        NULL,                                       // Environment
        NULL,                                       // Use parent's starting directory 
        &startInfo,                                 // Pointer to STARTUPINFO structure
        &procInfo )                                 // Pointer to PROCESS_INFORMATION structure
    )
    {
        printf( "CreateProcess failed (%d).\n", GetLastError() );
        return 1;
    }


    GameManager* gm = new GameManager();

    Character* player = new Character({25, 21});
    player->gm = gm;
    player->AddTileMap(gm->GetLevelTileMap()); // Make this internal. No need if we reference gm in Player.

    ScreenText* instructionalText = new ScreenText({0, 29});
    ScreenText* mapNameText = new ScreenText({40, 0});
    instructionalText->SetText("[SpaceBar]  [<][>]");
    // TODO: Just testing, remove later
    mapNameText->SetText(std::string(GetCommandLine()));

    game.Play();
    
    // TODO: Make an auto Entitiy cleaner.
    // delete newWindow;
    delete player;
    delete instructionalText;
    delete mapNameText;
    delete gm;

    CloseHandle(procInfo.hProcess);
    CloseHandle(procInfo.hThread);
    
    return 0;
}


// Need to know "what" to instantiate and the positions.