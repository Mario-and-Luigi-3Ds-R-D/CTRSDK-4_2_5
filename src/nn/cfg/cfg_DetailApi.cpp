#include <nn/cfg/CTR/cfg_DetailApi.h>
#include <nn/cfg/CTR/cfg_IpcUser.h>
#include <nn/dbg/dbg_Printf.h>
#include <nn/srv/srv_Api.h>

#include <string.h>

namespace nn {
namespace cfg {
namespace CTR {
namespace detail {
namespace{
    static int InitializeCount;
}
namespace{
    static bool sIsInitialized;
}

Result InitializeBase(Handle* pSession, const char* name){
    Result res; res.mResult = srv::Initialize().IsFailure();
    size_t nameLen;
    if(res.mResult != 0){
        nndbgPanic();
    }
    if(pSession->IsValid()){
        return (Result)0xd8a103f9;
    }
    else{
        nameLen = strlen(name);
        res = srv::GetServiceHandle(pSession, name,nameLen,0);
        if(res.IsSuccess() == 0){
            return (Result)0xd92103fb;
        }
    }
    return res;
}


// nm
Result Initialize(){
    Result res;
    if(!InitializeCount){
        res = InitializeBase(&IpcUser::sSession,PORT_NAME_USER);
        if(res.IsSuccess()){
            sIsInitialized = true;
        } else{
            return (Result)0xd92103fb;
        }
    }
    ++InitializeCount;
    return res;
}

Result InitializeProperPort(IPCPortType* pPortType){
    // TODO
}

Result FinalizeBase(nn::Handle* pSession){

}

void Finalize(){
    if(0 < InitializeCount)
        InitializeCount -= 1;
    if((InitializeCount == 0) && (sIsInitialized != false)){
        sIsInitialized = false;
        FinalizeBase(&IpcUser::sSession);
    }
}

void FinalizeProperPort(IPCPortType portType){
    switch(portType){
        case PORT_CFG_USER:
        Finalize(); break;
            
        case PORT_CFG_SYS:
        FinalizeSys();break;

        case PORT_CFG_INIT:
        FinalizeInit(); break;
    }
}

Result GetConfig(void* pData, size_t size, bit32 key){
    Result res;
    #ifdef NN_DEBUG
        if(!IpcUser::sSession.IsValid()){
            dbg::detail::TPrintf("[WARN] nn::cfg is not initialized.\n");
        }
    #endif
    res = IpcUser::GetConfig(pData,size,key);
    return res;
}
}
}
}
}