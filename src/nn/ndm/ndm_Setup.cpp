#include <nn/ndm/ndm_Setup.h>
#include <nn/ndm/ndm_UserControl.h>
#include <nn/ndm/ndm_Interface.h>
#include <nn/applet/CTR/applet_Info.h>
#include <nn/applet/CTR/applet_Api.h>

namespace nn{
namespace ndm{

void SetupDaemonsDefault(){
    if(nn::applet::CTR::IsInitialized() && !nn::applet::CTR::GetAppletType()){
        Result canInit = nn::ndm::Initialize().IsFailure();
        if(canInit != 0){
            nndbgPanic();
        }
        nn::ndm::CTR::detail::Interface::OverrideDefaultDaemons(0xfu);
        nn::ndm::SuspendDaemons(6u);
    }
}

}
}