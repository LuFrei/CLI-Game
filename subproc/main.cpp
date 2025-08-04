#include <iostream>
#include <Windows.h>
#include <array>
#include <stdlib.h>

#include "../shared.h"
#include "libclr.h"

#include "ScrollableTextView.h"

#define SCREEN_WIDTH 120
#define SCREEN_HEIGHT 30

/* WHEN IM BACK FROM MECHANIC:
- Make CmakeLists file for subproc
- Implement ScrollableTextView in this file.
*/

/* Checklist
1. Scrolling view
[x] list of blocks
- scrolling blocks
  [x] Move blocks up/down, with last/first blocks rotating
  [ ] Get mouse wheel input
- Data scrolling for scrolling blocks
  [x] Make data set LARGER than lsit size.
  [x] "viewport" range for history log
2. "Log history" array
[-] TextBlocks: set text as block data.
  - Half-done - Added set Text to Block. Not sure if should make TextBlock yet.
[x] Vector of strings locally.
[ ] Test to make sure live data additions are displayed properly
  - Data sets < display capcity should be displayed top-to-bottom
  - NEw data should appear below.
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

    std::vector<std::string> mockLogs = {
        "1. Character Loaded.",
        "2. Player spawned at coordinates (100, 200, 300).",
        "3. Inventory updated: Added 'Health Potion'.",
        "4. Quest 'Find the Lost Sword' started.",
        "5. Enemy defeated: Goblin King.",
        "6. Experience gained: 150 XP.",
        "7. Level up! Now at Level 2.",
        "8. New skill learned: Fireball.",
        "9. Player traded with NPC: Merchant Joe.",
        "10. Quest 'Defeat the Dragon' completed.",
        "11. Gold earned: 500.",
        "12. Player logged out.",
        "13. Player logged in.",
        "14. Player equipped 'Iron Sword'.",
        "15. Achievement unlocked: First Blood.",
        "16. Discovered new area: Whispering Woods.",
        "17. Item crafted: Wooden Shield.",
        "18. Player joined party: Alice.",
        "19. Player left party: Bob.",
        "20. Received message from NPC: 'Beware the caves.'",
        "21. Player rested at campfire.",
        "22. Weather changed: Rain started.",
        "23. Trap triggered: Poison Dart.",
        "24. Player revived by teammate.",
        "25. Skill upgraded: Stealth II.",
        "26. Player used item: Mana Potion.",
        "27. Inventory full: Cannot pick up 'Silver Ring'.",
        "28. Player opened treasure chest.",
        "29. Found secret passage.",
        "30. Player tamed a wild horse.",
        "31. Player completed daily quest.",
        "32. Player failed to pick lock.",
        "33. Player learned recipe: Healing Salve.",
        "34. Player took damage: 25 HP.",
        "35. Player healed: 30 HP.",
        "36. Player discovered hidden room.",
        "37. Player solved puzzle: Ancient Runes.",
        "38. Player received mail: 'Welcome Gift'.",
        "39. Player equipped 'Leather Armor'.",
        "40. Player unequipped 'Iron Helmet'.",
        "41. Player upgraded weapon: +1 Damage.",
        "42. Player started fishing.",
        "43. Player caught a 'Golden Carp'.",
        "44. Player cooked 'Grilled Meat'.",
        "45. Player set waypoint: Mountain Peak.",
        "46. Player activated portal.",
        "47. Player entered dungeon: Shadow Crypt.",
        "48. Player found rare item: 'Emerald Amulet'.",
        "49. Player completed achievement: Explorer.",
        "50. Player summoned pet: Wolf.",
        "51. Player dismissed pet.",
        "52. Player used emote: Wave.",
        "53. Player changed appearance: New hairstyle.",
        "54. Player received friend request.",
        "55. Player accepted friend request.",
        "56. Player declined trade offer.",
        "57. Player sent group invite.",
        "58. Player received group invite.",
        "59. Player changed settings: Audio volume.",
        "60. Player reported bug: 'Invisible wall'.",
        "61. Player submitted feedback.",
        "62. Player viewed leaderboard.",
        "63. Player reached checkpoint.",
        "64. Player exited to main menu."
    };
    //Mock Log position Tracker -- for test use
    int i = 0;

    ScrollableTextView* logView = new ScrollableTextView(screen);

#pragma endregion // Scrolling log screen
    

    while(true){

#pragma region ScrollTesting
/* NOTES: 
Simple solution is to iterate the array and update each 
block and check for bottom/top most if they exceed the limits.

Maybe something better would be to have them grouped together
where one change would move them all at once, And when one went 
out of bounds, it would self correct with an offset.

Starting with straight forward approach.
*/

        // Testing adding Mock Logs
        if(GetKeyState('P') & 0x8000 && i < mockLogs.size()){
            logView->AddEntry(mockLogs[i]);
            
            i++;
            Sleep(100);
        }

        // (!)TODO: replace Sleep with a timer.
        //          Debugger may be doing other things like watching live 
        //          values, so we don't want to paud the entire app.
        if(GetKeyState(VK_UP) & 0x8000){
            logView->ScrollUp();
            Sleep(50); // (!)
        }

        if(GetKeyState(VK_DOWN) & 0x8000){
            logView->ScrollDown();
            Sleep(50); // (!)
        }

#pragma endregion

        screen->Draw(); 
    }

    CloseHandle(hFMO);
    
    delete logView;
    delete screen;
    return 0;
}