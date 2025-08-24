#include <rpc.h>
#include <rpcndr.h>
#include <iostream> // May not need this anymore
#include <windows.h>
#include <array>
#include <stdlib.h>

#include "../shared.h"
#include "libclr.h"
#include "Logger/Logger.h"

#include <thread>

#define SCREEN_WIDTH 120
#define SCREEN_HEIGHT 30


int main(int argc, char* argv[]){
    clr::Screen* screen = new clr::Screen(SCREEN_WIDTH, SCREEN_HEIGHT);
    InitLogger(screen);

    Log("Setting up File Mapping...");

    HANDLE hFMO = OpenFileMapping(
        FILE_MAP_READ,
        FALSE,
        "clgSharedData"
    );
    
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);

    void* sharedData = MapViewOfFile(
        hFMO,
        FILE_MAP_READ,
        0,
        0, //sysInfo.dwAllocationGranularity,
        0
    );

    Log("COMPLETE.");

    std::thread RpcServer(StartRpcServer);

    // extracting to avoid doing ((Shared::PlayerData*)sharedData) 20000 times
    Shared::PlayerData* pData = (Shared::PlayerData*)sharedData;

    while(true){
        
        RunLogger();
        screen->Draw(); 
    }
    
    CloseHandle(hFMO);
    
    delete screen;
    return 0;
}




