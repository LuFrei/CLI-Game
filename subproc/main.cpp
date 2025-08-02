#include <iostream>
#include <Windows.h>
#include <array>
#include <stdlib.h>

#include "../shared.h"
#include "libclr.h"

#define SCREEN_WIDTH 120
#define SCREEN_HEIGHT 30

/* Checklist
1. Scrolling view
[x] list of blocks
- scrolling blocks
  [x] Move blocks up/down, with last/first blocks rotating
  [ ] Get mouse wheel input
- Data scrolling for scrolling blocks
  [x] Make data set LARGER than lsit size.
  [ ] "viewport" range for history log
2. "Log history" array
[ ] Vector of strings locally.
[ ] TextBlocks: set text as block data.
3. File MApping data transfer
[ ] temp data system
  - App sends string to display in data strucutre
  - Debugger checks if theres any content in data structure
    - if there's data, copy it to Log History, and erase temp data
    - When copying: move head of visible logs down (we want to show the enw data instantly.)
*/



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

#pragma region ScrollingLogScreen
    // // Populating fake data
    // std::vector<std::string> logHistory;
    // logHistory.push_back("Character Loaded.");
    // logHistory.push_back("");

    std::vector<WCHAR> fakeValues = {
        L'A', L'B', L'C', L'D', L'E', L'F', L'G', L'H', L'I', L'J', L'K', L'L', L'M',
        L'N', L'O', L'P', L'Q', L'R', L'S', L'T', L'U', L'V', L'W', L'X', L'Y', L'Z',
        L'a', L'b', L'c', L'd', L'e', L'f', L'g', L'h', L'i', L'j', L'k', L'l', L'm',
        L'n', L'o', L'p', L'q', L'r', L's', L't', L'u', L'v', L'w', L'x', L'y', L'z',
        L'0', L'1', L'2', L'3', L'4', L'5', L'6', L'7', L'8', L'9'
    };
    // View port size
    int viewportSize = SCREEN_HEIGHT;
    int bottom = fakeValues.size();
    int top = bottom - SCREEN_HEIGHT;
    
    std::array<clr::Block, SCREEN_HEIGHT> textLines;

    for(int i = 0; i < SCREEN_HEIGHT; i++){
        textLines[i].Resize(SCREEN_WIDTH/2, 1);
        textLines[i].y = i;
        textLines[i].Fill({fakeValues[i+top],WHITE});
        screen->AddToRenderQueue(&textLines[i]);
    }


#pragma endregion // Scrolling log screen
    

    while(true){

#pragma region ScrollTesting
/* NOTES: 
Simple solution is to iterate the array and update each 
block and check for bottom/top most if they exceed the limits.

Maybe something better would be to have them grouped together
where one change would move them all at once, And when one went out of bounds, it would self correct with an offset.

Starting with straight forward approach.
*/

        // Scrolling down
        if(GetKeyState(VK_UP) & 0x8000 && top > 0){
            bottom--;
            top--;
            for(clr::Block& block : textLines){
                block.y++;
                if(block.y >= SCREEN_HEIGHT) {
                    block.y = 0;
                    block.Fill({fakeValues[top], WHITE});
                }
            }

            Sleep(50);
        }

        // Scrolling Up
        if(GetKeyState(VK_DOWN) & 0x8000 && bottom < fakeValues.size() - 1){
            bottom++;
            top++;
            for(clr::Block& block : textLines){
                block.y--;
                if(block.y < 0) {
                    block.y = SCREEN_HEIGHT - 1;
                    block.Fill({fakeValues[bottom], WHITE});
                }
            }

            Sleep(50);
        }
        

#pragma endregion
    
        screen->Draw(); 
    }

    CloseHandle(hFMO);
    delete screen;
    return 0;
}