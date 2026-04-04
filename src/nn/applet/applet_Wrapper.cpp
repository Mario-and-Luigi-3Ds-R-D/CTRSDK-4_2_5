#include <nn/applet/applet_Api.h>
#include <nn/applet/applet_Wrapper.h>

namespace nn{
namespace applet{
namespace CTR{

void ClearHomeButtonState(void) {
    nn::applet::CTR::SetHomeButtonState(HOME_BUTTON_NONE);
    nn::applet::CTR::detail::UnlockTransition(1);
    nn::applet::CTR::detail::SleepIfShellClosed();
}

}
}
}