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
#include "../shared.h"

#include <filesystem>
#include <iostream>

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

PROCESS_INFORMATION procInfo;
STARTUPINFO startInfo;
HANDLE hJob;
HANDLE hFMO;


inline void cleanup(){
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

inline void MakeNewWindow(){
    TCHAR modFileNameOut[MAX_PATH] = {0}; 
        
    GetModuleFileName(NULL, modFileNameOut, MAX_PATH);

    std::filesystem::path exePath = modFileNameOut;

    std::filesystem::path appPath = exePath.parent_path();
    appPath /= "SecondScreen.exe";

    ZeroMemory(&startInfo, sizeof(startInfo));
    startInfo.cb = sizeof(startInfo);
    ZeroMemory(&procInfo, sizeof(procInfo));

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
        throw 1;
    }
}

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

int main(int argc, char* argv[])
{
    try {
        
        //Setting up File MApping
        struct Shared::PlayerData pData = {10, 13} ;

        int sharedSize = sizeof(struct Shared::PlayerData);

        hFMO = CreateFileMapping(
            INVALID_HANDLE_VALUE,
            NULL,
            PAGE_READWRITE,
            0,
            sharedSize,
            "clgSharedData"
        );

        SYSTEM_INFO sysInfo;
        GetSystemInfo(&sysInfo);

        void* sharedData = MapViewOfFile(
            hFMO,
            FILE_MAP_ALL_ACCESS,
            0,
            0,
            sharedSize
        );

        if(sharedData == nullptr){
            printf( "View File mapping failed (%d).\n", GetLastError() );
            return 1; 
        }

        //End File Mapping Setup

        //Testing FMO data sharing
        *((Shared::PlayerData*)sharedData) = pData;
        ((Shared::PlayerData*)sharedData)->xPlayerPos = 20;
        //End Testing FMO data sharing

        SetConsoleCtrlHandler(ConsoleHandler, TRUE);

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

        
        MakeNewWindow();


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

        cleanup();

        return 0;
    } catch (int errCode) {
        cleanup();
        //TODO: handle errors.
        return errCode;
    }
}


// Need to know "what" to instantiate and the positions.