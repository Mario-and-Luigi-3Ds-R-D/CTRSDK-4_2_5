#include <nn/applet/applet_Api.h>
#include <nn/applet/applet_Paramaters.h>

const nn::Handle nn::applet::CTR::HANDLE_NONE = (nn::Handle)0;

namespace nn{
namespace applet{
namespace CTR{
namespace detail{

void Enable(bool isEnable){
    // TODO
}

Result CloseApplication(u8 *pParam,size_t paramSize,nn::Handle handle){
    // TODO
}

void CallUtility(u32 utilityId, u8* pInParam, size_t inParamSize, u8* pOutParam, size_t outParamSize, s32* pReadSize){
    // TODO
}

void UnlockTransition(u32 action){
    // TODO
}

void SleepIfShellClosed(){
    // TODO
}

}
}
}
}