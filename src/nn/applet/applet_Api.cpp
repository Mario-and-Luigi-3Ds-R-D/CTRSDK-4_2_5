#include <nn/applet/CTR/applet_Api.h>
#include <nn/applet/CTR/applet_Connect.h>
#include <nn/applet/CTR/applet_Info.h>
#include <nn/applet/CTR/applet_ClientThread.h>
#include <nn/applet/CTR/applet_Wrapper.h>
#include <nn/applet/CTR/detail/applet_Ipc.h>
//#include <nn/gxlow/gxlow_SystemUse.h>
#include <nn/srv/srv_Api.h>
#include <nn/os/os_Thread.h>
#include <nn/err/CTR/err_Api.h>

namespace nn{
namespace applet{
namespace CTR{

const nn::Handle HANDLE_NONE = 0;

namespace detail{

void Initialize(){

}

void Enable(bool isSleepEnable){
    
}

void CallUtility(u32 utilityId, u8* pInParam, size_t inParamSize, u8* pOutParam, size_t outParamSize, s32* pReadSize){
    // TODO
}

bool WaitForRegister(AppletId appletId,nn::fnd::TimeSpan span){
    // TODO
}

Result CloseApplication(u8 *pParam,size_t paramSize,nn::Handle handle){
    // TODO
}

/* Applet Connect, do shit with Port Names and shit. */

Result InitializeConnect(AppletId appletId, AppletAttr attr, s32 threadPriority){

}

Result Connect(){
    // TODO
}

void Disconnect(){
    // TODO
}

/* #AppletRightsMatter */

void AssignGpuRight(bool flag){
    // TODO
}

void AssignDspRight(bool flag){
    // TODO
}

/* Cancel Things */

Result CancelLibraryAppletIfRegistered(bool isApplicationEnd, nn::applet::CTR::AppletWakeupState *pWakeupState){
    // TODO
}

bool CancelParamater(bool isSenderCheck, nn::applet::CTR::AppletId senderId, bool isReceiverCheck, nn::applet::CTR::AppletId receiverId){
    bool isCanceled;
    LockAndConnect();
    Result res = APPLET::CancelParamater(isSenderCheck, senderId, isReceiverCheck, receiverId, &isCanceled);
    NN_ERR_THROW_FATAL(res);
    DisconnectAndUnlock();
    return (s8)isCanceled;
}

/* HomeMenu things */

static void WaitBySleep(s64 impl){
    nn::os::Thread::SleepImpl(nn::fnd::TimeSpan::FromMilliSeconds(impl));
}

Result JumpToHomeMenu(u8 *pParam,size_t paramSize,Handle handle){
    // TODO
}

#ifdef NON_MATCHING
#endif 

Result PrepareToJumpToHomeMenu(){
    /*CTR::SetTransitionType(TRANSITION_JUMP_HOME);
        
    const Result ERROR_A(0xc8a0cff0);
    const Result ERROR_B(0xe0a0cc08);
    const Result ERROR_C(0xc8a0cc02);
        
    Result res;
    while(true){
        LockAndConnect();
        res = APPLET::PrepareToJumpToHomeMenu();
        DisconnectAndUnlock();
    if (res != ERROR_A && res != ERROR_B && res != ERROR_C) break;
        WaitBySleep(0xa);
    }

    return res;*/
}

void GetAppletManInfo(AppletPos requestPos,AppletPos *pCurrentPos,AppletId *pRequestedId,AppletId *pHomeMenuId,AppletId *pCurrentId){
    AppletPos currentPos; AppletId requestedId; AppletId homeMenuId; AppletId currentId; Result result;
    LockAndConnect();
    result = APPLET::GetAppletManInfo(requestPos, &currentPos, &requestedId, &homeMenuId, &currentId);
    NN_ERR_THROW_FATAL(result);
    DisconnectAndUnlock();
    if (pCurrentPos)  *pCurrentPos  = currentPos;
    if (pRequestedId) *pRequestedId = requestedId;
    if (pHomeMenuId)  *pHomeMenuId  = homeMenuId;
    if (pCurrentId)   *pCurrentId   = currentId;
}

Result Glance(AppletId *pSenderId,u32 *pCommand,u8 *pParam,size_t paramSize,s32 *pReadLen,Handle *pHandle){
    AppletId receiverId; Result res; Handle tmpHandle; AppletId tmpSenderId; u32 tmpCmd; u8 tmpBuf[1]; s32 tmpReadLen;
    LockAndConnect();
    if(pSenderId == 0) pSenderId =&tmpSenderId;
    if(pCommand == 0) pCommand =&tmpCmd;
    
    if(pParam == 0 || paramSize == 0) 
        pParam = tmpBuf; paramSize = 0;

    if(pReadLen == 0) pReadLen =&tmpReadLen;
    if(pHandle == 0) pHandle =&tmpHandle;

    receiverId = GetId();
    res = APPLET::GlanceParameter(pSenderId,receiverId,pCommand,pParam,paramSize,pReadLen,pHandle);
    if(tmpHandle.mHandle != 0){ __asm{ swine 0x23}}
    DisconnectAndUnlock();
    return res;
}


#ifdef NONMATCHING
#endif
/* Transitions */
void UnlockTransition(u32 action){
    u32 actionLocal = action;
    CallUtility(7,(u8*)&actionLocal,4,0,0,0);
}

#ifdef NONMATCHING
#endif
void LockTransition(u32 action,bool isForced){
    LockTransitionParam param;

    param.action = action;
    param.isForced = isForced;
    CallUtility(4,(u8*)&param,8,0,0,0);
}

// I love this hack
#pragma O2
void SleepIfShellClosed() {
    u32 flags = 0;
    u32 callId = 4;
    CallUtility(callId, (u8*)flags, flags, (u8*)flags, flags, (s32*)flags);
}
#pragma O3

/* SLEEPMANAGERS */

void ReplySleepQueryToManager(QueryReply reply){
    AppletId id;
    Result res;

    LockAndConnect();
    id = GetId();
    res = APPLET::ReplySleepQuery(id,reply);
    NN_ERR_THROW_FATAL(res);
    DisconnectAndUnlock();
}

} // detail

bool IsInitialized(){
    return CTR::detail::sIsInitialized;
}
}
}
}