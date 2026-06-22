#include <nn/applet/CTR/applet_Connect.h>
#include <nn/applet/CTR/detail/applet_Ipc.h>
#include <nn/srv/srv_Api.h>
#include <nn/err/CTR/err_Api.h>
#include <nn/gxlow/gxlow_SystemUse.h>

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
    } 
    else{
        nameLen = strlen(sPortName);
        res = srv::GetServiceHandle(pSession,sPortName,nameLen,0);
    }
}

inline Result FinalizePort(Handle* pSession){
    Result res;
    if(pSession->IsValid()){
        res.mResult = svc::CloseHandle(*pSession).mResult;
        *pSession = INVALID_HANDLE_VALUE;
    } 
    else{
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
    if(!pInfo){
        return;
    }
    gxlow::CTR::DisplayCaptureInfo infoTmp;
    return gxlow::CTR::ImportDisplayCaptureInfo(&infoTmp);

}

void InitializeMutex(nn::Handle handle){
    sMutex.mHandle = handle.mHandle;
}

}
}
}
}