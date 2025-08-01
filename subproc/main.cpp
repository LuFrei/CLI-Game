#include <iostream>
#include <Windows.h>
#include <array>

#include "../shared.h"
#include "libclr.h"

#define SCREEN_WIDTH 120
#define SCREEN_HEIGHT 30

int main(int argc, char* argv[]){
    clr::Screen* screen = new clr::Screen(SCREEN_WIDTH, SCREEN_HEIGHT);

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

    std::array<clr::Block, SCREEN_HEIGHT> textLines;

    WCHAR characters[4] = {'A', 'B', 'C', 'D'};

    for(int i = 0; i < SCREEN_HEIGHT; i++){
        textLines[i] = clr::Block(5, 1);
        textLines[i].y = i;
        textLines[i].Fill({characters[i%4], WHITE});
        screen->AddToRenderQueue(&textLines[i]);
    }
    // clr::Block* testSquare = new clr::Block(2, 4);
    // testSquare->Fill({'A', WHITE});
    // screen->AddToRenderQueue(testSquare);
    screen->Draw();

    while(true){
        screen->Draw();
    }

    CloseHandle(hFMO);
    delete screen;
    return 0;
}