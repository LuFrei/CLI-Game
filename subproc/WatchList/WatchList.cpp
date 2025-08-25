#include "WatchList.h"

#include "../globals.h"
#include "../shared.h"
#include "../ScrollableTextView.h"

#include "../Logger/Logger.h"

HANDLE hFMO;

ScrollableTextView* view;
Shared::PlayerData* pData;

void InitWatchList(){
    view = new ScrollableTextView(screen, 
        SCREEN_WIDTH/2, SCREEN_HEIGHT, 
        (SCREEN_WIDTH/2)+1, 0
    );
}

void SetupFileMap(){
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

    pData = (Shared::PlayerData*)sharedData; 
    Log("COMPLETE.");
}

void CloseFileMap(){
    CloseHandle(hFMO);
    delete view;
}