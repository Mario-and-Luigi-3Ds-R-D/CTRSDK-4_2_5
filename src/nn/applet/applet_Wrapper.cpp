#include <nn/applet/CTR/applet_Wrapper.h>
#include <nn/applet/CTR/applet_Connect.h>
#include <nn/applet/CTR/applet_Info.h>
#include <nn/applet/CTR/applet_Api.h>

namespace nn{
namespace applet{
namespace CTR{

void InitializeWrapper(){
    // TODO
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

void CloseAppletHook(){
    if (releaseMemoryCallback != 0){
        reinterpret_cast<void(*)(int)>(releaseMemoryCallback)(releaseMemoryCallbackArg);
    }

    if (closeAppletCallback == 0)
        return;

    reinterpret_cast<void(*)(int)>(closeAppletCallback)(closeAppletCallbackArg);
}

}
}
}