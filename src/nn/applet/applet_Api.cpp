#include <nn/applet/CTR/applet_Api.h>
#include <nn/applet/CTR/applet_Connect.h>
#include <nn/applet/CTR/applet_Info.h>
#include <nn/applet/CTR/applet_ClientThread.h>
#include <nn/applet/CTR/applet_Wrapper.h>
#include <nn/applet/CTR/applet_InitialParamaters.h>
#include <nn/applet/CTR/detail/applet_Ipc.h>
#include <nn/camera/camera_Api.h>
#include <nn/srv/srv_Api.h>
#include <nn/os/os_Thread.h>
#include <nn/err/CTR/err_Api.h>

// Legitimate Clusterfuck.

namespace nn{
namespace applet{
namespace CTR{
namespace detail{

/* ---- INLINES ---- */

inline bool IsRegistered(AppletId id){
    bool isRegistered; Result res;

    LockAndConnect();
    res = APPLET::IsRegistered(id, &isRegistered);
    NN_ERR_THROW_FATAL(res);
    DisconnectAndUnlock();
    return isRegistered;
}

inline Result CallUtility(u32 utilityId, u8* pInParam, size_t inParamSize){
    return CallUtility(utilityId, pInParam, inParamSize, 0,0,0);
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

#ifdef NONMATCHING
#endif

inline AppletId GetHomeMenuAppletId(){
    Result res; AppletId id2; AppletId id3; AppletId id1; AppletPos pos;

    LockAndConnect();
    res = APPLET::GetAppletManInfo(POS_NONE,&pos,&id1,&id2,&id3);
    NN_ERR_THROW_FATAL(res);
    DisconnectAndUnlock();
    return id2;
}

inline void WaitBySleep(int msecs){
    fnd::TimeSpan span = fnd::TimeSpan::FromMilliSeconds(msecs);
    os::Thread::Sleep(span);
}


} // detail
} // CTR
} // applet
} // nn

/* ---- FUNCTIONS ---- */

namespace nn{
namespace applet{
namespace CTR{

const nn::Handle HANDLE_NONE = 0;

namespace detail{
namespace{
    bool isApplication;
}
namespace{
    srv::NotificationHandler sHandler;
}

/* Initialize */

Result Initialize(AppletAttr appletAttr) {
    if (!detail::IsAppletMode()) {
        sIsGpuRightGiven = true;
        appletAttr = AppletAttr(appletAttr & ~7);
        nn::srv::RegisterNotificationHandler(&sHandler, 0x100);
        Result result = detail::InitializeConnect(0x300, appletAttr, 0xF);
        if (result.IsFailure())
            return result;
    }
    return ResultSuccess();
}

/* Enable */

void Enable(bool isSleepEnable){
    bool applicationCheck; 
    AppletWakeupState state; 
    AppletAttr attr; 
    u8* pParam; 
    AppletId id;
    s32 size;
    Result result;
    if(isSleepEnable){
        EnableSleep(0);
    }
    nn::applet::CTR::detail::LockAndConnect();
    attr = nn::applet::CTR::GetAttribute();
    result = nn::applet::CTR::detail::APPLET::Enable(attr);
    NN_ERR_THROW_FATAL(result);
    nn::applet::CTR::detail::DisconnectAndUnlock();
    applicationCheck = nn::applet::CTR::IsApplication();
    if((applicationCheck) && (attr = nn::applet::CTR::GetAttribute(), (attr & 0x20) == 0)){
        nn::applet::CTR::SetTransitionType(TRANSITION_ENABLE_APPLET);
        pParam = nn::applet::CTR::detail::GetInitialParamBuffer();
        state = nn::applet::CTR::detail::WaitForStarting(&id,pParam,0x1000,&size,(Handle *)0x0,CTR::WAIT_INFINITE);
        nn::applet::CTR::detail::SetInitialParamSenderId(id);
        nn::applet::CTR::detail::SetInitialParamSenderSize(size);
        nn::applet::CTR::detail::SetInitialParamValid();
        nn::applet::CTR::detail::SetInitialWakeupState(state);
    }
}

/* WaitForRegister */

bool WaitForRegister(AppletId appletId,nn::fnd::TimeSpan span){
    // TODO
}

/* CancelLibraryAppletIfRegistered */

Result CancelLibraryAppletIfRegistered(bool isApplicationEnd, nn::applet::CTR::AppletWakeupState *pWakeupState){
    // TODO
}

/* NotifyToWait */

void NotifyToWait(){
    AppletId id;
    Result res;
    LockAndConnect();
    id = GetId();
    res = APPLET::NotifyToWait(id);
    NN_ERR_THROW_FATAL(res);
    DisconnectAndUnlock();
}

/* CallUtility */

Result CallUtility(u32 utilityId, u8* pInParam, size_t inParamSize, u8* pOutParam, size_t outParamSize, s32* pReadSize){
    // TODO
}

/* CloseApplication */

Result CloseApplication(u8 *pParam,size_t paramSize,nn::Handle handle){
    // TODO
}

/* #AppletRightsMatter */

/* AssignGpuRight */

void AssignGpuRight(bool flag){
    // TODO
}

/* PrepareToStartSystemApplet */

Result PrepareToStartSystemApplet(AppletId id){
    // TODO
}

/* StartSystemApplet */

Result StartSystemApplet(AppletId id, u8* pParam, size_t size, nn::Handle handle){
    // TODO
}

/* AssignDspRight */

void AssignDspRight(bool flag){
/*
    if(flag){
        if(isDspSleeping != false){
            dsp::CTR::WakeUp();
            isDspSleeping = false;
        }
    }
    else{
        if(dsp::CTR::IsComponentLoaded()){
            dsp::CTR::Sleep();
            isDspSleeping = true;
        }
    }
*/
}

/* AssignCameraRight */
/* Finished */

void AssignCameraRight(bool flag){
    if(flag == 0){
        camera::CTR::detail::LeaveApplication();
    }
    camera::CTR::detail::ArriveApplication();
}

/* CancelParamater */

bool CancelParameter(bool isSenderCheck, nn::applet::CTR::AppletId senderId, bool isReceiverCheck, nn::applet::CTR::AppletId receiverId){
    bool isCanceled;
    LockAndConnect();
    Result res = APPLET::CancelParamater(isSenderCheck, senderId, isReceiverCheck, receiverId, &isCanceled);
    NN_ERR_THROW_FATAL(res);
    DisconnectAndUnlock();
    return (s8)isCanceled;
}

/* JumpToHomeMenu */
/* Not Finished */

Result JumpToHomeMenu(u8 *pParam,size_t paramSize,Handle handle){
    /*AppletId appletId; AppletId homemenuId; 
    Result res; 
    Handle hand_local;
    appletId = GetHomeMenuAppletId();
    bool appletCheck = IsApplication();
    if(appletCheck){
        while(!IsRegistered(appletId)){
            WaitBySleep(10);
        }
        sIsVramSaved = true;
        gxlow::CTR::SaveVramSysArea();
        res = CaptureScreenForSystemApplet(appletId);
    }
    if(dsp::CTR::IsComponentLoaded()){
        dsp::CTR::Sleep();
        sIsDspSleeping = true;
    }
    AssignGpuRight(false);
    camera::CTR::LeaveApplication();
    LockAndConnect();
    res = APPLET::JumpToHomeMenu(pParam, paramSize, handle);
    NN_ERR_THROW_FATAL(res);
    DisconnectAndUnlock();
    SetInactive();
    return res;*/
}

/* PrepareToJumpToHomeMenu*/
/* Finished */

Result PrepareToJumpToHomeMenu(){
    SetTransitionType(TRANSITION_JUMP_HOME);
        
    const Result ERROR_A(0xc8a0cff0);
    const Result ERROR_B(0xe0a0cc08);
    const Result ERROR_C(0xc8a0cc02);
        
    Result res;
    while(true){
        LockAndConnect();
        res = APPLET::PrepareToJumpToHomeMenu();
        DisconnectAndUnlock();
        if (res != ERROR_A && res != ERROR_B && res != ERROR_C) break;
            WaitBySleep(10);
    }
    return res;
}

/* GetAppletManInfo */
/* Finished */

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

/* Glance */

Result Glance(AppletId *pSenderId,u32 *pCommand,u8 *pParam,size_t paramSize,s32 *pReadLen,Handle *pHandle){
    // TODO
}

/* --Transitions-- */

/* UnlockTransition */

void UnlockTransition(u32 action){
    // TODO
}

/* LockTransition */

void LockTransition(u32 action,bool isForced){
    // TODO
}

// I love this hack

/* SleepIfShellClosed */
/* Finished */
#pragma O2
void SleepIfShellClosed() {
    u32 flags = 0;
    u32 callId = 4;
    CallUtility(callId, (u8*)flags, flags, (u8*)flags, flags, (s32*)flags);
}
#pragma O3

/* -- SLEEPMANAGERS -- */

/* ReplyToSleepQueryToManager */

void ReplySleepQueryToManager(QueryReply reply){
    AppletId id;
    Result res;
    LockAndConnect();
    id = GetId();
    res = APPLET::ReplySleepQuery(id,reply);
    NN_ERR_THROW_FATAL(res);
    DisconnectAndUnlock();
}

/* ReplySleepNotificationCompleteToManager */

void ReplySleepNotificationCompleteToManager(){
    AppletId id;
    Result res;
    LockAndConnect();
    id = GetId();
    res = APPLET::ReplySleepNotificationComplete();
    NN_ERR_THROW_FATAL(res);
    DisconnectAndUnlock();
}

} // detail

/* IsInitialized */

bool IsInitialized(){
    return CTR::detail::sIsInitialized;
}
}
}
}