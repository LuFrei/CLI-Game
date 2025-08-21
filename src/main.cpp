#include "CLGEngine/Entity.h"
#include "CLGEngine/Game.h"
#include "CLGEngine/TileMap.h"

#include "CLGEngine/CORE/MainWindow.h"
#include "CLGEngine/CORE/Window.h"
#include "CLGEngine/Debugger.h"

#include "Game/Entities/Character.h"
#include "Game/Entities/ScreenText.h"
#include "Game/Entities/Wall.h"
#include "Game/Entities/Door.h"
#include "Game/Entities/Button.h"
#include "Game/Maps.h"
#include "Game/Entities/LevelTrigger.h"
#include "Game/GameManager.h"
#include "../shared.h"

#include <filesystem>
#include <iostream>

// Temp, for testing
#include <thread>
#include <chrono>

#include "Debugger.h"

using namespace CLGEngine;

#define SUB_PROCESS_PATH "SecondScreen.exe "

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
    // Let's keep it empty for now.
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
};

Game game = Game();

GameManager* gm;
Character* player;
ScreenText* instructionalText;
ScreenText* mapNameText;
Debugger* debugger;

PROCESS_INFORMATION procInfo;
STARTUPINFO startInfo;
HANDLE hJob;
HANDLE hFMO;

inline void cleanup(){
    delete debugger;
    delete instructionalText;
    delete player;
    delete mapNameText;
    delete gm;

    CloseHandle(procInfo.hProcess);
    CloseHandle(procInfo.hThread);
    CloseHandle(hJob);
    CloseHandle(hFMO);
    

    // About to see if there actually hit...
    if(!TerminateJobObject(hJob, 0)){
        printf( "Failed to termiante Job: (%d).\n", GetLastError() );
    } else {
        printf( "Job Terminated");
    }

};

BOOL WINAPI ConsoleHandler(DWORD signal) {
    if (signal == CTRL_CLOSE_EVENT || 
        signal == CTRL_C_EVENT ||
        signal == CTRL_BREAK_EVENT) 
    {    
        
        game.Exit(); // TODO: This is not actually waiting for the loop to exit
        // TODO: make a way for the cleanup to run AFTER the game loop stops.
        //       Be it it here in Main or in Game.
        // cleanup();

        if(!TerminateJobObject(hJob, 0)){
            printf( "Failed to termiante Job: (%d).\n", GetLastError() );
        } else {
            printf( "Job Terminated");
        }

        printf("Exiting... cleaning up.\n");
    }
    return FALSE;
}

int main(int argc, char* argv[]) {

    // Exit strategies
    SetConsoleCtrlHandler(ConsoleHandler, TRUE);

    debugger = new Debugger::Debugger();

    // What was this for?
    hJob = CreateJobObject(NULL, "CLI-Game");
    if( !AssignProcessToJobObject(hJob, GetCurrentProcess()))
    {
        printf( "Failed to assign process to Job: (%d).\n", GetLastError() );
        return 1;
    }


    
    /*Level Setup
    * Have levels in a folder.
    * Load levels from directory into Level queue
    
    LevelManager.AddLevelToQueue(<path/to/levels>);
    
    * LevelManager should have direct access to entity manager to create and destroy
    
    * TileMap will be 1 value in each level.
    */



   

    gm = new GameManager();

    player = new Character({25, 21});
    player->gm = gm;
    player->AddTileMap(gm->GetLevelTileMap()); // Make this internal. No need if we reference gm in Player.

    instructionalText = new ScreenText({0, 29});
    mapNameText = new ScreenText({40, 0});
    instructionalText->SetText("[SpaceBar]  [<][>]");
    // TODO: Just testing, remove later
    mapNameText->SetText(std::string(GetCommandLine()));

    game.Play();
        status = RpcStringFree(&pszStringBinding); 

    if (status) exit(status);

    status = RpcBindingFree(&Debugger_IfHandle);

    if (status) exit(status);
    cleanup();

    return 0;
}

void __RPC_FAR * __RPC_USER midl_user_allocate(size_t len)
{
    return(malloc(len));
}
 
void __RPC_USER midl_user_free(void __RPC_FAR * ptr)
{
    free(ptr);
}

// Need to know "what" to instantiate and the positions.