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

using namespace CLGEngine;

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

    // Window* newWindow = new Window();

    PROCESS_INFORMATION ProcInfo;
    STARTUPINFO StartInfo;

    // This is needed
    ZeroMemory(&StartInfo, sizeof(StartInfo));
    StartInfo.cb = sizeof(StartInfo);
    ZeroMemory(&ProcInfo, sizeof(ProcInfo));

    LPSTR CmdLine = GetCommandLine();

    /* Setting up window class */

    const wchar_t CLASS_NAME[] = L"Pop-out Debug Display";

    WNDCLASS wndClass = {};

    // Window Procedure written above, before main

    // hInstance
    HINSTANCE hInstance = GetModuleHandle(NULL);

    wndClass.lpfnWndProc = WindowProc;  // forward dclr??
    wndClass.hInstance = hInstance;     // wWinMain.hInstance????????
    wndClass.lpszClassName = (LPCSTR)CLASS_NAME;

    RegisterClass(&wndClass);

    HWND newWindow = CreateWindowEx(    
        /* ExStyle */       0,
        /* ClassName */     (LPCSTR)CLASS_NAME,                  
        /* Window Name */   (LPCSTR)L"Debugger",
        /* Style */         WS_OVERLAPPEDWINDOW,
        /* x */             CW_USEDEFAULT,
        /* y */             CW_USEDEFAULT,
        /* w */             CW_USEDEFAULT,
        /* h */             CW_USEDEFAULT,
        /* WndParent */     NULL,
        /* Menu */          NULL,
        /* Instance */      hInstance, // IS this same as before? wWinMain.hInstance??
        /* Param */         NULL
    );
    if(newWindow == NULL){
        printf("Window creation failed: (%d).\n", GetLastError());
        return 1;
    }

    ShowWindow(newWindow, SW_SHOWNORMAL);

    GameManager* gm = new GameManager();

    Character* player = new Character({25, 21});
    player->gm = gm;
    player->AddTileMap(gm->GetLevelTileMap()); // Make this internal. No need if we reference gm in Player.

    ScreenText* instructionalText = new ScreenText({0, 29});
    ScreenText* mapNameText = new ScreenText({20, 0});
    instructionalText->SetText("[SpaceBar]  [<][>]");

    game.Play();
    
    // TODO: Make an auto Entitiy cleaner.
    delete newWindow;
    delete player;
    delete instructionalText;
    delete mapNameText;
    delete gm;

    CloseHandle(ProcInfo.hProcess);
    CloseHandle(ProcInfo.hThread);
    
}


// Need to know "what" to instantiate and the positions.