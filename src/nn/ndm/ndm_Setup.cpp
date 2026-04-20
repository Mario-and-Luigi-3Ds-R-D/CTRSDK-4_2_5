#include <nn/ndm/ndm_Setup.h>
#include <nn/ndm/ndm_UserControl.h>
#include <nn/ndm/ndm_Interface.h>
#include <nn/applet/CTR/applet_Info.h>
#include <nn/applet/CTR/applet_Api.h>

namespace nn{
namespace ndm{

// nasty ass butt hack used -O2 (smiley face)
void SetupDaemonsDefault(){
    if(nn::applet::CTR::IsInitialized() && !nn::applet::CTR::GetAppletType()){
        if(nn::ndm::Initialize().IsFailure()){
            nndbgPanic();
        }
        nn::ndm::CTR::detail::Interface::OverrideDefaultDaemons(0xfu);
        nn::ndm::SuspendDaemons(6u);
    }
}

}
}