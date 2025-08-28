#include "Debugger.h"

// Temp, for testing
#include <thread>
#include <chrono>

// #include <pair>
#include <filesystem>
#include <iostream>

#include <Windows.h>

#include "DebugLogger.h"
#include "../../../shared.h"

PROCESS_INFORMATION procInfo;
STARTUPINFO startInfo;

/* RPC Glob Vars*/
RPC_STATUS status;
unsigned char * pszUuid             = NULL;
unsigned char * pszProtocolSequence = (unsigned char*)"ncacn_np";
unsigned char * pszNetworkAddress   = NULL;
unsigned char * pszEndpoint         = (unsigned char*)"\\pipe\\DebugLogger";
unsigned char * pszOptions          = NULL;
unsigned char * pszStringBinding    = NULL;
unsigned char * pszString           = (unsigned char*)"LOGGER ONLINE!";
unsigned long ulCode;
// ---------

HANDLE hFMO;

std::vector<std::string> Debugger::_logHistory = {};

//FileMApping
struct Shared::Data Debugger::pData = {};
Shared::Data* Debugger::sharedData;
std::vector<void*> Debugger::watchedData; //val*, type name
std::vector<std::pair<void*, std::string>> Debugger::testing_watchedData; //val*, type name


inline void MakeNewWindow(){
    TCHAR modFileNameOut[MAX_PATH] = {0}; 
        
    GetModuleFileName(NULL, modFileNameOut, MAX_PATH);

    std::filesystem::path exePath = modFileNameOut;

    // TODO: Need to move SecondScreen.exe to Debugger Directory.
    std::filesystem::path appPath = exePath.parent_path();
    appPath /= "SecondScreen.exe";

    ZeroMemory(&startInfo, sizeof(startInfo));
    startInfo.cb = sizeof(startInfo);
    ZeroMemory(&procInfo, sizeof(procInfo));

    if( !CreateProcess( NULL,                       // No module name (use command line)
        (LPSTR)appPath.string().c_str(),            // Command line
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
Shared::Data* SetupFileMapping(){
    try {
        int sharedSize = sizeof(struct Shared::Data);

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

        return (Shared::Data*)sharedData;
    } catch (int errCode) {
        //TODO: handle errors.
        exit(1);
    }
}

Debugger::Debugger(){
    sharedData = SetupFileMapping();

    // Create Window
    MakeNewWindow();
   
    // Wait for process to boot up.
    std::this_thread::sleep_for(std::chrono::milliseconds(4000));

#pragma region RPC_Setup


    status = RpcStringBindingCompose(pszUuid,
                                    pszProtocolSequence,
                                    pszNetworkAddress,
                                    pszEndpoint,
                                    pszOptions,
                                    &pszStringBinding);
    if (status) exit(status);

    status = RpcBindingFromStringBinding(pszStringBinding, &DebugLogger_IfHandle);

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

Debugger::~Debugger(){
    status = RpcStringFree(&pszStringBinding); 
    if (status) exit(status);

    status = RpcBindingFree(&DebugLogger_IfHandle);
    if (status) exit(status);

    CloseHandle(procInfo.hProcess);
    CloseHandle(procInfo.hThread);
    CloseHandle(hFMO);
}

// TODO: Make sure logger is up before using RPC
//      And cache logs if it's not.
void Debugger::Log(std::string text){
    //if Dbgr is NOT live:
    //    _logHistory.push_back(text);

    //if Dbgr is live
    AddEntry(reinterpret_cast<const unsigned char*>(text.c_str()));
    // (unsigned char*)
}

// template<typename T>
void Debugger::AddToWatchList(std::string name, void* value){
    if(watchedData.size() >= CAPACITY){
        Log("! Watch List at capacity !");
        return;
    }

    watchedData.push_back(value);
    pData.AddData(name + ": ", (int)*(float*)value);
    sharedData->AddData(name + ": ", (int)*(float*)value);
    *(sharedData) = pData;
}

void Debugger::UpdateWatchList(){
    for(int i = 0; i < watchedData.size(); i++){
        pData.Data[i] = (int)*(float*)watchedData[i];
        sharedData->Data[i] = (int)*(float*)watchedData[i];
        *(sharedData) = pData;
    }
}

void __RPC_FAR * __RPC_USER midl_user_allocate(size_t len)
{
    return(malloc(len));
}
 
void __RPC_USER midl_user_free(void __RPC_FAR * ptr)
{
    free(ptr);
}