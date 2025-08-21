#include "Debugger.h"

std::vector<std::strinf> Debugger::_logHistory = {};

inline void MakeNewWindow(){
    TCHAR modFileNameOut[MAX_PATH] = {0}; 
        
    GetModuleFileName(NULL, modFileNameOut, MAX_PATH);

    std::filesystem::path exePath = modFileNameOut;

    // TODO: Need to move SecondScreen to Debugger Directory.
    std::filesystem::path appPath = exePath.parent_path();
    appPath /= "SecondScreen.exe";

    ZeroMemory(&startInfo, sizeof(startInfo));
    startInfo.cb = sizeof(startInfo);
    ZeroMemory(&procInfo, sizeof(procInfo));

    if( !CreateProcess( NULL,                       // No module name (use command line)
        (LPSTR)appPath.string().c_str(),        // Command line
        NULL,                                       // Process handle not inheritable
        NULL,                                       // Thread handle not inheritable
        FALSE,                                      // Set handle inheritance to FALSE
        CREATE_NEW_CONSOLE,                                          // No creation flags
        NULL,                                       // Environment
        NULL,                                       // Use parent's starting directory 
        &startInfo,                                 // Pointer to STARTUPINFO structure
        &procInfo )                                 // Pointer to PROCESS_INFORMATION structure
    )
    {
        printf( "CreateProcess failed (%d).\n", GetLastError() );
        throw 1;
    }
}

// TODO!: This will silent fail, need to integrate it with the RpcTryExcept
//          Or vice versa.
Shared::PlayerData* SetupFileMapping(){
    // try {
        int sharedSize = sizeof(struct Shared::PlayerData);

        hFMO = CreateFileMapping(
            INVALID_HANDLE_VALUE,
            NULL,
            PAGE_READWRITE,
            0,
            sharedSize,
            "clgSharedData"
        );
        
        SYSTEM_INFO sysInfo;
        GetSystemInfo(&sysInfo);
        
        void* sharedData = MapViewOfFile(
            hFMO,
            FILE_MAP_ALL_ACCESS,
            0,
            0,
            sharedSize
        );
        
        if(sharedData == nullptr){
            printf( "View File mapping failed (%d).\n", GetLastError() );
            // return 1; // Will we crash or silent fail?
        }

        return (Shared::PlayerData*)sharedData;
    // } catch (int errCode) {
    //     cleanup();
    //     //TODO: handle errors.
    //     exit(1);
    // }
}

Debugger::Debugger(){
    // Most of this is testing data, and needs to be changed.
#pragma region File-Mapping
    int simulatedXPos = 10;
    int simulatedYPos = 15;

    struct Shared::PlayerData pData = {simulatedXPos, simulatedYPos};

    Shared::PlayerData* sharedData = SetupFileMapping();

    //Testing FMO data sharing
    *(sharedData) = pData;
    simulatedXPos = 20;

#pragma endregion   //File-Mapping

    // Create Window
    MakeNewWindow();
   
    // Wait for process to boot up.
    std::this_thread::sleep_for(std::chrono::milliseconds(4000));

#pragma region RPC_Setup
    RPC_STATUS status;
    unsigned char * pszUuid             = NULL;
    unsigned char * pszProtocolSequence = (unsigned char*)"ncacn_np";
    unsigned char * pszNetworkAddress   = NULL;
    unsigned char * pszEndpoint         = (unsigned char*)"\\pipe\\Debugger";
    unsigned char * pszOptions          = NULL;
    unsigned char * pszStringBinding    = NULL;
    unsigned char * pszString           = (unsigned char*)"DEBUGGER ONLINE!";
    unsigned long ulCode;

    status = RpcStringBindingCompose(pszUuid,
                                    pszProtocolSequence,
                                    pszNetworkAddress,
                                    pszEndpoint,
                                    pszOptions,
                                    &pszStringBinding);
    if (status) exit(status);

    status = RpcBindingFromStringBinding(pszStringBinding, &Debugger_IfHandle);

    if (status) exit(status);

    try  
    {
        AddEntry(pszString);
    }
    catch(int err) 
    {
        printf("Runtime reported exception 0x%lx = %ld\n", err, err);
    }
#pragma endregion   //RPC_Setup
}

void Debugger::Log(std::string text){
    _logHistory.push_back(text);

}