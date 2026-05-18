#include <nn/applet/CTR/applet_Connect.h>
#include <nn/applet/CTR/detail/applet_Ipc.h>
#include <nn/srv/srv_Api.h>
#include <nn/err/CTR/err_Api.h>
#include <nn/gxlow/gxlow_Parameters.h>

#include <string.h>

namespace nn{
namespace applet{
namespace CTR{
namespace detail{
namespace{
    static os::Mutex sMutex;
}
namespace{
    const char* sPortName;
}

inline void SetPortName(const char* name){
    if(sPortName == 0){
        sPortName = name;
    }
}

#ifdef NONAMTCHING
#endif

inline Result InitializePort(Handle* pSession){
    SetPortName(PORT_NAME_USER);
    Result res;
    size_t nameLen;
    if(pSession->IsValid()){
        return (Result)0xE0A0CFF9;
    } else{
        nameLen = strlen(PORT_NAME_USER);
        res = srv::GetServiceHandle(pSession,sPortName,nameLen,0);
    }
}

inline Result FinalizePort(Handle* pSession){
    Result res;
    if(pSession->IsValid()){
        res.mResult = svc::CloseHandle(*pSession).mResult;
        *pSession = INVALID_HANDLE_VALUE;
    } else{
        return (Result)0xe0a0cff8;
    }
    return res;
}

inline void Lock(){
    if(sMutex.IsValid()){
        sMutex.Lock();
    }
}

inline void Unlock(){
    if(sMutex.IsValid()){
        sMutex.Unlock();
    }
}

Result InitializeConnect(AppletId appletId, AppletAttr attr, s32 threadPriority){

}

Result Connect(){
    Result res = InitializePort(&APPLET::sSession);
    NN_ERR_THROW_FATAL(res);
    return res;
}

Result Disconnect(){
    Result res = FinalizePort(&APPLET::sSession);
    NN_ERR_THROW_FATAL(res);
    return res;
}

void LockAndConnect(){
    Lock();
    Connect();
}

void DisconnectAndUnlock(){
    Disconnect();
    Unlock();
}

// REVIEW

void GetDisplayInfo(AppletDisplayInfo* pInfo){
    gxlow::DisplayCaptureInfo infoTmp;
    if(pInfo != 0){
        pInfo->d[0].mAddr = infoTmp.surface[0].mAddr;
        pInfo->d[0].mAddrB = infoTmp.surface[0].mAddrB;
        pInfo->d[1].mAddr = infoTmp.surface[1].mAddr;
        pInfo->d[1].mAddrB = infoTmp.surface[1].mAddrB;
        pInfo->d[0].mode = (DisplayBufferMode)infoTmp.surface[0].mode;
        pInfo->d[1].mode = (DisplayBufferMode)infoTmp.surface[1].mode;
        pInfo->d[0].stride = infoTmp.surface[0].stride;
        pInfo->d[1].stride = infoTmp.surface[1].stride;
    }
}

void InitializeMutex(nn::Handle handle){
    sMutex.mHandle = handle.mHandle;
}

}
}
}
}