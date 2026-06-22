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
#include <nn/gxlow/gxlow_SystemUse.h>
#include <nn/dsp/CTR/MPCore/dsp_Api.h>

#include <nn/dbg/dbg_DebugString.h>

#include <nn/gx/CTR/gx_CTR.h>

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

#ifdef NONMATCHING
#endif

inline AppletId GetHomeMenuAppletId(){
    Result res;
    AppletPos pos;
    AppletId id1; 
    AppletId id2; 
    AppletId id3; 
    LockAndConnect();
    res = APPLET::GetAppletManInfo(POS_NONE, &pos, &id1, &id2, &id3);
    NN_ERR_THROW_FATAL(res);
    DisconnectAndUnlock();
    return id2;
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

inline bool IsRetryRequired(Result result){
    bool ret = true;
    if(result == nn::applet::CTR::ResultBusy())
        return ret;
    if(result == nn::applet::CTR::ResultTransitionBusy())
        return ret;
    if(result == nn::applet::CTR::ResultNotEmpty())
        return ret;
    return false;
}

bool DisableSleepForTransition(){
    bool isSleep = CTR::IsEnableSleep();
    if(isSleep) DisableSleep(true);
    return isSleep;
}
bool EnableSleepForTransition(){
    bool isSleep = CTR::IsEnableSleep();
    if(!isSleep) EnableSleep(true);
    return isSleep;
}

void RestoreSleepForTransition(bool e){
    if(e)
        EnableSleepForTransition();
    else
        DisableSleepForTransition();
}


inline Result SaveVramSysArea(){
    sIsVramSaved = true;
    return gxlow::CTR::SaveVramSysArea();
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

inline Result CancelLibraryApplet(bool isApplicationEnd){
    Result res;
    SetTransitionType(TRANSITION_CANCEL_APPLIB);
    while(true){
        LockAndConnect();
        res = APPLET::CancelLibraryApplet(isApplicationEnd);
        DisconnectAndUnlock();
        if(!IsRetryRequired(res)) break;
        WaitBySleep(10);
    }
    return res;
}

Result CancelLibraryAppletIfRegistered(bool isApplicationEnd, AppletWakeupState* pWakeupState){
    Result res = ResultSuccess();
    if(pWakeupState){
        *pWakeupState = WAKEUP_SKIP;
    }
    if((!IsApplication() || IsRegistered(0x400)) &&
       (!IsSystemApplet() || IsRegistered(0x200))){
        res = CancelLibraryApplet(isApplicationEnd);
        if(res == ResultSuccess()){
            AppletWakeupState wakeup;
            wakeup = WaitForStarting(NULL,NULL,0,NULL,NULL,CTR::WAIT_INFINITE);
            if(pWakeupState)
                *pWakeupState = wakeup;
            
        }
    }
    return res;
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

inline Result PrepareToCloseApplication(bool isCancelPreload){
    CancelLibraryAppletIfRegistered(false);
    SetTransitionType(TRANSITION_CLOSE_APP);
    Result res;
    while(true){
        LockAndConnect();
        res = APPLET::PrepareToCloseApplication(!isCancelPreload);
        DisconnectAndUnlock();
        if(!IsRetryRequired(res)) break;
        WaitBySleep(10);
    }
    NN_ERR_THROW_FATAL(res);
    return res;
}

Result CloseApplication(u8* pParam, size_t paramSize, Handle handle){
    if(GetTransitionType() != TRANSITION_CLOSE_APP){
        PrepareToCloseApplication(false);
    }
    CloseAppletHook();
    AssignGpuRight(false);
    Result res;
    while(true){
        LockAndConnect();
        res = APPLET::CloseApplication(pParam, paramSize, handle);
        DisconnectAndUnlock();
        if(!IsRetryRequired(res)) break;
        WaitBySleep(10);
    }
    NN_ERR_THROW_FATAL(res);
    SetInactive();
    svc::ExitProcess();
    return res;
}

/* #AppletRightsMatter */

/* AssignGpuRight */

void AssignGpuRight(bool flag){
    Result res;
    if(flag){
        sIsGpuRightGiven = true;
        res = gxlow::CTR::AcquireGpuRight();
        NN_ERR_THROW_FATAL(res);
    }
    else if(sIsGpuRightGiven){
        sIsGpuRightGiven = false;
        res = gxlow::CTR::ReleaseGpuRight();
        if(res == Result(0xd8a02a05)){
            if(res == Result(0xd9001bf7)){
                NN_TLOG_("applet_API: Warning: Release GPU right despite no gx init.\n");
            }
            else{
                NN_ERR_THROW_FATAL(res);
            }
        }
    }
}

/* PrepareToStartSystemApplet */

Result PrepareToStartSystemApplet(AppletId id){
    Result res;
    nngxGetIsRunning();
    CancelLibraryAppletIfRegistered(false);
    SetTransitionType(TRANSITION_START_SYS);
    bool sleep = DisableSleepForTransition();
    while(true){
        LockAndConnect();
        res = APPLET::PrepareToStartSystemApplet(id);
        DisconnectAndUnlock();
        if(!IsRetryRequired(res)) break;
        WaitBySleep(10);
    }
    RestoreSleepForTransition(sleep);
    if(IsApplication()){
        if(res == Result(0xc8a0cffc)){
            res = ResultSuccess();
        }
    }
    return res;
}

/* StartSystemApplet */

Result StartSystemApplet(AppletId id,u8* pParam,size_t paramSize,Handle h){
    Result res;

    if (!IsApplication() && !IsSystemApplet())
        return Result(0xC8A0CC04);

    if (IsSystemApplet()){
        AssignGpuRight(false);
    }
    else if (IsApplication()){
        SaveVramSysArea();

        AssignDspRight(false);
        AssignGpuRight(false);
        AssignCameraRight(false);
    }

    bool sleepEnabled = IsEnableSleep();

    if (sleepEnabled)
        DisableSleep(true);

    while (true){
        LockAndConnect();
        res = APPLET::StartSystemApplet(id,pParam,paramSize,h);
        DisconnectAndUnlock();
        if (!IsRetryRequired(res)) break;
        WaitBySleep(10);
    }

    if (sleepEnabled){
        if (!IsEnableSleep())
            EnableSleep(true);
    }
    else{
        if (IsEnableSleep())
            DisableSleep(true);
    }

    NN_ERR_THROW_FATAL_ALL(res);
    SetInactive();
    if (IsApplication())
        res = CaptureScreenForSystemApplet(id);

    if (IsSystemApplet())
        svc::ExitProcess();

    return res;
}

/* AssignDspRight */

void AssignDspRight(bool flag){
    /*if(flag){
        if(sIsDspSleeping){
            dsp::CTR::WakeUp();
            sIsDspSleeping = false;
        }
    }
    else{
        if(dsp::CTR::IsComponentLoaded()){
            dsp::CTR::Sleep();
            sIsDspSleeping = true;
        }
    }*/
}

/* AssignCameraRight */

void AssignCameraRight(bool flag){
    if(flag){
        camera::CTR::detail::LeaveApplication();
    }
    else{
        camera::CTR::detail::ArriveApplication();
    }
}

/* CancelParamater */

bool CancelParameter(bool isSenderCheck, nn::applet::CTR::AppletId senderId, bool isReceiverCheck, nn::applet::CTR::AppletId receiverId){
    bool isCanceled;
    LockAndConnect();
    Result res = APPLET::CancelParamater(isSenderCheck, senderId, isReceiverCheck, receiverId, &isCanceled);
    NN_ERR_THROW_FATAL(res);
    DisconnectAndUnlock();
    return isCanceled;
}

/* JumpToHomeMenu */

Result JumpToHomeMenu(u8* pParam, size_t paramSize, Handle handle){
    AppletId appletId; AppletId homemenuId; 
    Result res; 
    Handle hand_local;
    appletId = CTR::detail::GetHomeMenuAppletId();
    if(IsApplication()){
        while(!IsRegistered(appletId)){
            WaitBySleep(10);
        }
        SaveVramSysArea();
        res = CaptureScreenForSystemApplet(appletId);
    }
    AssignDspRight(false);
    AssignGpuRight(false);
    AssignCameraRight(false);
    LockAndConnect();
    res = APPLET::JumpToHomeMenu(pParam, paramSize, handle);
    NN_ERR_THROW_FATAL(res);
    DisconnectAndUnlock();
    SetInactive();
    return res;
}

/* PrepareToJumpToHomeMenu*/

Result PrepareToJumpToHomeMenu(){
    SetTransitionType(TRANSITION_JUMP_HOME);
        
    Result res;
    while(true){
        LockAndConnect();
        res = APPLET::PrepareToJumpToHomeMenu();
        DisconnectAndUnlock();
        if (!IsRetryRequired(res)) break;
            WaitBySleep(10);
    }
    return res;
}

/* GetAppletManInfo */

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

/* UnlockTransition */



void UnlockTransition(u32 action){

}

/* LockTransition */

void LockTransition(u32 action,bool isForced){

}

/* SleepIfShellClosed */

#pragma O2

void SleepIfShellClosed() {
    u32 flags = 0;
    u32 callId = 4;
    CallUtility(callId, (u8*)flags, flags, (u8*)flags, flags, (s32*)flags);
}

#pragma O3

Result InitializeConnect(AppletId appletId, AppletAttr attr, s32 threadPriority){
    // TODO
}

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