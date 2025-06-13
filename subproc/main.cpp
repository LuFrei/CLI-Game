#include <iostream>
#include <Windows.h>

#include "../shared.h"

int main(int argc, char* argv[]){
    std::cout << "Second window works!" << std::endl;
    std::cout << "Command Line: " << GetCommandLine() << std::endl;
    
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



    CloseHandle(hFMO);
    return 0;
}