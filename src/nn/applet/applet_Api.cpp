#include <nn/applet/applet_All.h>
//#include <nn/gxlow/gxlow_SystemUse.h>
#include <nn/err/CTR/err_Api.h>

const nn::Handle nn::applet::CTR::HANDLE_NONE = (nn::Handle)0;

namespace nn{
namespace applet{
namespace CTR{
namespace detail{

bool sIsApplet;
bool sIsVramSaved;
bool sIsInitialized;
bool sIsGpuRightGiven;
bool sIsDspSleeping;

void Enable(bool isSleepEnable){
    
}

/*void Enable(bool isSleepEnable){
    nn::fnd::TimeSpan timeout;
    bool applicationCheck;
    AppletWakeupState state;
    AppletAttr attr;
    Result result;
    u8* pParam;
    AppletId id;
    s32 size;

    if(isSleepEnable != 0){
        EnableSleep(0);
    }
    nn::applet::CTR::detail::LockAndConnect();
    attr = nn::applet::CTR::GetAttribute();
    result = nn::applet::CTR::detail::APPLET::Enable(attr).IsFailure();
    if(result != 0){
        NN_ERR_THROW_FATAL(result);
    }
    nn::applet::CTR::detail::DisconnectAndUnlock();
    applicationCheck = nn::applet::CTR::IsApplication();
    if((applicationCheck) && (attr = nn::applet::CTR::GetAttribute(), (attr & 0x20) == 0)){
        nn::applet::CTR::SetTransitionType(TRANSITION_ENABLE_APPLET);
        pParam = nn::applet::CTR::detail::GetInitialParamBuffer();
        //timeout.mNanoSeconds = *(fnd::TimeSpan*)CTR::WAIT_INFINITE;
        state = nn::applet::CTR::detail::WaitForStarting(&id,pParam,0x1000,&size,(Handle *)0x0,timeout);
        nn::applet::CTR::detail::SetInitialParamSenderId(id);
        nn::applet::CTR::detail::SetInitialParamSenderSize(size);
        nn::applet::CTR::detail::SetInitialParamValid();
        nn::applet::CTR::detail::SetInitialWakeupState(state);
    }
}*/

void CallUtility(u32 utilityId, u8* pInParam, size_t inParamSize, u8* pOutParam, size_t outParamSize, s32* pReadSize){
    // TODO
}

bool WaitForRegister(AppletId appletId,nn::fnd::TimeSpan span){
    // TODO
}

Result CloseApplication(u8 *pParam,size_t paramSize,nn::Handle handle){
    // TODO
}

void AssignGpuRight(bool flag){
    // TODO
}

void AssignDspRight(bool flag){
    // TODO
}

Result CancelLibraryAppletIfRegistered(bool isApplicationEnd, nn::applet::CTR::AppletWakeupState *pWakeupState){
    // TODO
}

bool CancelParamater(bool isSenderCheck, nn::applet::CTR::AppletId senderId, bool isReceiverCheck, nn::applet::CTR::AppletId receiverId){
    bool isCanceled;
    LockAndConnect();
    Result res = APPLET::CancelParamater(isSenderCheck, senderId, isReceiverCheck, receiverId, &isCanceled);
    NN_ERR_THROW_FATAL(res); // how the fuck to call this shit..?
    DisconnectAndUnlock();
    return (s8)isCanceled;
}

Result JumpToHomeMenu(u8 *pParam,size_t paramSize,Handle handle){
    // TODO
}

void PrepareToJumpToHomeMenu(){
    // TODO
}

void GetAppletManInfo(AppletPos requestPos,AppletPos *pCurrentPos,AppletId *pRequestedId,AppletId *pHomeMenuId,AppletId *pCurrentId){
    // TODO
}

// nonmatch
void UnlockTransition(u32 action){
    u32 actionLocal = action;
    CallUtility(7,(u8*)&actionLocal,4,0,0,0);
}

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

void ReplySleepQueryToManager(QueryReply reply){
    // TODO
}

} // detail

bool IsInitialized(){
    return CTR::detail::sIsInitialized;
}
}
}
}