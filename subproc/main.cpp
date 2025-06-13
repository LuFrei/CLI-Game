#include <iostream>
#include <Windows.h>

#include "../shared.h"

int main(int argc, char* argv[]){
    
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
    // extracting to avoid doing ((Shared::PlayerData*)sharedData) 20000 times
    Shared::PlayerData* pData = (Shared::PlayerData*)sharedData;

    while(true){
        printf("Player X Position: %d\nPlayer Y Position: %d", 
            pData->xPlayerPos, 
            pData->yPlayerPos
        );
    }


    CloseHandle(hFMO);
    return 0;
}