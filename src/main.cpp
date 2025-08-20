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

PROCESS_INFORMATION procInfo;
STARTUPINFO startInfo;
HANDLE hJob;
HANDLE hFMO;
/*********************/
/* FOR WHEN IM BACK: */
/*********************/
/*
RPC Say tconnection doesnt exist. 
Look into race conditions when starting RPC/Second process!!!!
*/
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


// TODO!: This will silent fail, need to integrate it with the RpcTryExcept
//          Or vice versa.
Shared::PlayerData* SetupFileMapping(){
    // try {
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
            // return 1; // Will we crash or silent fail?
        }

        return (Shared::PlayerData*)sharedData;
    // } catch (int errCode) {
    //     cleanup();
    //     //TODO: handle errors.
    //     exit(1);
    // }
}

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

int main(int argc, char* argv[]) {

#pragma region File-Mapping
    int simulatedXPos = 10;
    int simulatedYPos = 15;

    struct Shared::PlayerData pData = {simulatedXPos, simulatedYPos};

    Shared::PlayerData* sharedData = SetupFileMapping();



    //Testing FMO data sharing
    *(sharedData) = pData;
    simulatedXPos = 20;

#pragma endregion   //File-Mapping


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
   
   std::this_thread::sleep_for(std::chrono::milliseconds(4000));

#pragma region RPC_Setup
    RPC_STATUS status;
    unsigned char * pszUuid             = NULL;
    unsigned char * pszProtocolSequence = (unsigned char*)"ncacn_np";
    unsigned char * pszNetworkAddress   = NULL;
    unsigned char * pszEndpoint         = (unsigned char*)"\\pipe\\Debugger";
    unsigned char * pszOptions          = NULL;
    unsigned char * pszStringBinding    = NULL;
    unsigned char * pszString           = (unsigned char*)"DEBUGGER ONLINE!";
    unsigned long ulCode;

    status = RpcStringBindingCompose(pszUuid,
                                    pszProtocolSequence,
                                    pszNetworkAddress,
                                    pszEndpoint,
                                    pszOptions,
                                    &pszStringBinding);
    if (status) exit(status);

    status = RpcBindingFromStringBinding(pszStringBinding, &Debugger_IfHandle);

    if (status) exit(status);

    try  
    {
        AddEntry(pszString);
    }
    catch(int err) 
    {
        printf("Runtime reported exception 0x%lx = %ld\n", err, err);
    }


#pragma endregion   //RPC_Setup
   

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