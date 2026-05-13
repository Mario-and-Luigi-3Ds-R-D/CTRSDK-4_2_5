#include <nn/applet/CTR/applet_Wrapper.h>
#include <nn/applet/CTR/applet_Connect.h>
#include <nn/applet/CTR/applet_Info.h>
#include <nn/applet/CTR/applet_ClientThread.h>
#include <nn/applet/CTR/applet_Api.h>
#include <nn/os/os_CriticalSection.h>

namespace nn{
namespace applet{
namespace CTR{
namespace{
    bool sleepEnable;
    SysSleepAcceptedCallbackInfo* spHead;
    SysSleepAcceptedCallbackInfo* spTail;
    int homeButtonCallback;
    int requestMemoryCallback;
    int receiveMessageCallback;
    int dspSleepCallback;
    int dspWakeUpCallback;
    int sleepQueryCallback;
    int sleepCanceledCallback;
    int sleepAcceptedCallback;
    int awakeCallback;
    int shutdownCallback;
    int powerButtonCallback;
    int transitionCallback;
    int closeCallback;
    int releaseMemoryCallback;
    int closeAppletCallback;
    int commandCallback;
    int homeButtonCallbackArg;
    int requestMemoryCallbackArg;
    int receiveMessageCallbackArg;
    int dspSleepCallbackArg;
    int dspWakeUpCallbackArg;
    int sleepQueryCallbackArg;
    int sleepCanceledCallbackArg;
    int sleepAcceptedCallbackArg;
    int awakeCallbackArg;
    int shutdownCallbackArg;
    int powerButtonCallbackArg;
    int transitionCallbackArg;
    int closeCallbackArg;
    int releaseMemoryCallbackArg;
    int closeAppletCallbackArg;
    int commandCallbackArg;

}
namespace{
    static os::CriticalSection sSleepAcceptedCriticalSection;
}

void InitializeWrapper(){
    detail::SetReceiveCallback(ReceiveCallbackForCommands,0);
    homeButtonCallback = 0;
    homeButtonCallbackArg = 0;
    requestMemoryCallback = 0;
    requestMemoryCallbackArg = 0;
    receiveMessageCallback = 0;
    receiveMessageCallbackArg = 0;
    dspSleepCallback = 0;
    dspSleepCallbackArg = 0;
    dspWakeUpCallback = 0;
    dspWakeUpCallbackArg = 0;
    sleepQueryCallback = 0;
    sleepQueryCallbackArg = 0;
    sleepCanceledCallback = 0;
    sleepCanceledCallbackArg = 0;
    sleepAcceptedCallback = 0;
    sleepAcceptedCallbackArg = 0;
    awakeCallback = 0;
    awakeCallbackArg = 0;
    shutdownCallback = 0;
    shutdownCallbackArg = 0;
    powerButtonCallback = 0;
    powerButtonCallbackArg = 0;
    transitionCallback = 0;
    transitionCallbackArg = 0;
    closeCallback = 0;
    closeCallbackArg = 0;
    commandCallback = 0;
    commandCallbackArg = 0;
}

void ClearHomeButtonState(void) {
    nn::applet::CTR::SetHomeButtonState(HOME_BUTTON_NONE);
    nn::applet::CTR::detail::UnlockTransition(1);
    nn::applet::CTR::detail::SleepIfShellClosed();
}

void SetSleepQueryCallback(nn::applet::CTR::AppletSleepQueryCallback callback,uptr arg){
    *(AppletSleepQueryCallback*)sleepQueryCallback = callback;
    sleepQueryCallbackArg = arg;
}

void SetAwakeCallback(AppletAwakeCallback callback,uptr arg){
    *(AppletAwakeCallback*)awakeCallback = callback;
    awakeCallbackArg = arg;
}

bool ProcessPowerButton(){
    // TODO
}

bool ReceiveCallbackForCommands(uptr callback){
    // TODO
}

bool ProcessHomeButton(){
    // TODO
}

void DisableSleep(bool isReplyReject){
    if(!isReplyReject){
        return;
    }
    SetSleepNotificationState(NOTIFY_SLEEP_REJECT);
    detail::ReplySleepQueryToManager(REPLY_REJECT);
}

void EnableSleep(bool isSleepCheck){
    sleepEnable = 1;
    if(isSleepCheck){
        detail::SleepIfShellClosed();
        return;
    }
    return;
}

bool IsExpectedToProcessHomeButton(){
    bool Homemenu = IsExpectedToJumpToHomeMenu();
    HomeButtonState hbState;
    if((Homemenu != 0) || (hbState = GetHomeButtonState(), hbState != HOME_BUTTON_NONE)){
        hbState = HOME_BUTTON_SINGLE_PRESSED;
    }
    return hbState;
}

void CloseAppletHook(){
    if (releaseMemoryCallback != 0){
        reinterpret_cast<void(*)(int)>(releaseMemoryCallback)(releaseMemoryCallbackArg);
    }

    if (closeAppletCallback == 0)
        return;

    reinterpret_cast<void(*)(int)>(closeAppletCallback)(closeAppletCallbackArg);
}

//
// SysSleepAcceptedCallbackInfo 
//

void SysSleepAcceptedCallbackInfo::Unregister(){

}

void SysSleepAcceptedCallbackInfo::Register(){

}

}
}
}