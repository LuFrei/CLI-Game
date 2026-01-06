#include "Logger.h"

#include <thread>

#include "../globals.h"
#include "libclr.h"
#include "DebugLogger.h"


ScrollableTextView* logView;

HANDLE hEventRPC = OpenEventA(
  EVENT_MODIFY_STATE,   // dwDesiredAccess
  FALSE,                // bInheritHandle
  "RPCSetupFinished"  // lpName
); 

void InitLogger(){
    logView = new ScrollableTextView(screen, SCREEN_WIDTH/2, SCREEN_HEIGHT, 0, 0);
}

void ExitLogger(){
    delete logView;
    CloseHandle(hEventRPC);
}

void StartRpcServer(){
    
    logView->AddEntry("Setting up RPC...");
    RPC_STATUS status;
    unsigned char * pszProtocolSequence = (unsigned char*)"ncacn_np";
    unsigned char * pszSecurity         = NULL; 
    unsigned char * pszEndpoint         = (unsigned char*)"\\pipe\\DebugLogger";
    unsigned int    cMinCalls = 1;
    unsigned int    fDontWait = FALSE;

    logView->AddEntry("RPC Server Use Protseq...");
    status = RpcServerUseProtseqEp(pszProtocolSequence,
                                   RPC_C_LISTEN_MAX_CALLS_DEFAULT,
                                   pszEndpoint,
                                   pszSecurity); 
 
    if (status) exit(status);

    logView->AddEntry("Done.");
    logView->AddEntry("RPC Server Register If...");

    status = RpcServerRegisterIf(DebugLogger_v1_0_s_ifspec,  
                                 NULL,   
                                 NULL); 

    if (status) exit(status);

    logView->AddEntry("Done.");
    logView->AddEntry("RPC Server Listening...");

    if(!SetEvent(hEventRPC)){ //Maybe becuase it's create in client, it doesnt reset.
        printf("Error: Event Set failed.\n");
        exit(39);
    }

    status = RpcServerListen(cMinCalls,
                             RPC_C_LISTEN_MAX_CALLS_DEFAULT,
                             fDontWait);

    if (status) 
        exit(status);

    logView->AddEntry("Done.");
    logView->AddEntry("RPC setup DONE!");

}

void RunLogger(){
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
}

void Log(std::string log){
    logView->AddEntry(log);
}

void AddEntry( 
    /* [string][in] */ const unsigned char *text
){
    const char* sText = reinterpret_cast<const char*>(text);
    logView->AddEntry(sText);
}

void Shutdown(void)
{
    RPC_STATUS status;
 
    status = RpcMgmtStopServerListening(NULL);
 
    if (status) 
    {
       exit(status);
    }
 
    status = RpcServerUnregisterIf(NULL, NULL, FALSE);
 
    if (status) 
    {
       exit(status);
    }

    ExitLogger();
} //end Shutdown

void __RPC_FAR * __RPC_USER midl_user_allocate(size_t len)
{
    return(malloc(len));
}
 
void __RPC_USER midl_user_free(void __RPC_FAR * ptr)
{
    free(ptr);
}