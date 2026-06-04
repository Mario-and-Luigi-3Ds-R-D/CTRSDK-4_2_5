#include <nn/dev/CTR/dev_Api.h>
#include <nn/dev/CTR/dev_Ipc.h>
#include <nn/srv/srv_Api.h>
#include <string.h>

#ifdef NN_DEBUG

namespace nn{
namespace dev{
namespace CTR{
namespace{
    bool sInitialized;
}
namespace{
    Dev sDevHandle;
}
void Initialize(){
    size_t nameLen;
    Result res;

    if(sInitialized == false){
        srv::Initialize();
        nameLen = strlen(pxi::CTR::PORT_NAME_DEV);
        res.mResult = srv::GetServiceHandle(&sDevHandle.mSession, pxi::CTR::PORT_NAME_DEV,nameLen, 0).IsFailure();
        if(res.mResult != 0){
            nndbgBreakWithResultMessage_(NN_DBG_BREAK_REASON_PANIC, res, "dev_Api.cpp", 21, "\"%s\" is Failure.", "srv::GetServiceHandle(&Dev::sDevHandle, pxi::CTR::PORT_NAME_DEV)");
        }
        sInitialized = true;
    }
}

void Finalize(){
    if(sInitialized != false){
        nnResult res;
        res.value = svc::CloseHandle(sDevHandle.mSession).IsFailure();
        if(res.value != 0){
            nndbgBreakWithResultMessage_(NN_DBG_BREAK_REASON_PANIC, res, "dev_Api.cpp", 32, "\"%s\" is Failure.", "svc::CloseHandle(Dev::sDevHandle)");
        }
        sInitialized = false;
    }
}


}
}
}

#endif