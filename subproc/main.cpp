#include <rpc.h>
#include <rpcndr.h>
#include <iostream> // May not need this anymore
#include <array>
#include <stdlib.h>

#include "../shared.h"
#include "Logger/Logger.h"
#include "WatchList/WatchList.h"
#include "globals.h"
#include "libclr.h"

#include <thread>

int main(int argc, char* argv[]){
    std::thread RpcServer(StartRpcServer);
    
    screen = new clr::Screen(SCREEN_WIDTH, SCREEN_HEIGHT);
    InitLogger();

    InitWatchList();
    SetupFileMap();

    while(true){
        RunLogger();
        PrintWatchListItems();
        screen->Draw(); 
    }
    
    // TODO: These never run. Should handle program exits from Alt-F4 and 'X'
    CloseFileMap();
    ExitLogger();

    delete screen;
    return 0;
}




