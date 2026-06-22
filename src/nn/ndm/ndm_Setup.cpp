#include <nn/ndm/ndm_Setup.h>
#include <nn/ndm/ndm_UserControl.h>
#include <nn/ndm/ndm_Interface.h>
#include <nn/applet/CTR/applet_Info.h>
#include <nn/applet/CTR/applet_Api.h>

#include <nn/dbg/dbg_DebugString.h>
namespace nn{
namespace ndm{

void SetupDaemonsDefault(){
    if(applet::CTR::IsInitialized() && !applet::CTR::GetAppletType()){
        Result canInit; 
        if(ndm::Initialize().IsFailure()){
            nndbgPanic();
        }
        canInit = nn::ndm::CTR::detail::Interface::OverrideDefaultDaemons(0xfu);
        #ifdef NN_DEBUG
            if(canInit.IsFailure()){
                dbg::detail::TPrintf("Failed to override default daemons. (SDK version mismatch?)\n");
                dbg::detail::PrintResult(canInit);
            }
        #endif
        canInit = nn::ndm::SuspendDaemons(6u);
        #ifdef NN_DEBUG
            if(canInit.IsFailure()){
                dbg::detail::TPrintf("Failed to suspend boss daemon.\n");
                dbg::detail::PrintResult(canInit);
            }
        #endif
    }
}

}
}