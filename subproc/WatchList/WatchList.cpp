#include "WatchList.h"

#include "../globals.h"
#include "../shared.h"
#include "../ScrollableTextView.h"

#include "../Logger/Logger.h"

HANDLE hFMO;

ScrollableTextView* view;
Shared::Data sData;
Shared::Data* sharedData;

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

    sharedData = (Shared::Data*)MapViewOfFile(
        hFMO,
        FILE_MAP_READ,
        0,
        0, //sysInfo.dwAllocationGranularity,
        0
    );
}

/* TODO: 
Vector is going out of bounds
I'm not sure why but it's worth inspecting how GetEntry works,
The lifecycle of new watchlist data,
and how we manage the data.

*/

void PrintWatchListItems(){
    if(sharedData != nullptr){
    sData = *sharedData;
        for(int i = 0; i < sData.size; i++){
            view->UpdateEntry(i, sData.Message[i] + std::to_string(sData.Data[i]));
        }
    }
}


void CloseFileMap(){
    CloseHandle(hFMO);
    delete view;
}