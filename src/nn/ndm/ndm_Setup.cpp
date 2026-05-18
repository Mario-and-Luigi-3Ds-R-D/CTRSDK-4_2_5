#include <nn/ndm/ndm_Setup.h>
#include <nn/ndm/ndm_UserControl.h>
#include <nn/ndm/ndm_Interface.h>
#include <nn/applet/CTR/applet_Info.h>
#include <nn/applet/CTR/applet_Api.h>

#include <nn/dbg/dbg_Printf.h>
namespace nn{
namespace ndm{

void SetupDaemonsDefault(){
    if(nn::applet::CTR::IsInitialized() && !nn::applet::CTR::GetAppletType()){
        Result canInit; 
        canInit.mResult = nn::ndm::Initialize().IsFailure();
        if(canInit.mResult != 0){
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