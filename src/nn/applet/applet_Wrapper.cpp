#include <nn/applet/applet_Wrapper.h>
#include <nn/applet/applet_Info.h>
#include <nn/applet/applet_Api.h>

namespace nn{
namespace applet{
namespace CTR{

void ClearHomeButtonState(void) {
    nn::applet::CTR::SetHomeButtonState(HOME_BUTTON_NONE);
    nn::applet::CTR::detail::UnlockTransition(1);
    nn::applet::CTR::detail::SleepIfShellClosed();
}

void SetSleepQueryCallback(nn::applet::CTR::AppletSleepQueryCallback callback,uptr arg){
    // TODO
}

void SetAwakeCallback(AppletAwakeCallback callback,uptr arg){
    // TODO
}

void DisableSleep(bool isReplyReject){
    // TODO
}


}
}
}