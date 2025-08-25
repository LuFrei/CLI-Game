#include <rpc.h>
#include <rpcndr.h>
#include <iostream> // May not need this anymore
#include <windows.h>
#include <array>
#include <stdlib.h>

#include "../shared.h"
#include "Logger/Logger.h"
#include "WatchList/WatchList.h"
#include "globals.h"
#include "libclr.h"

#include <thread>

int main(int argc, char* argv[]){
    screen = new clr::Screen(SCREEN_WIDTH, SCREEN_HEIGHT);
    
    InitLogger();
    std::thread RpcServer(StartRpcServer);

    InitWatchList();
    SetupFileMap();

    while(true){
        RunLogger();
        PrintWatchListItems();
        screen->Draw(); 
    }
    
    CloseFileMap();
    ExitLogger();

    delete screen;
    return 0;
}




