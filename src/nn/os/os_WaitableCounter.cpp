#include "nn/os/os_WaitableCounter.h"
#include "nn/svc/svc_Api.h"

namespace nn{
namespace os{
    
    void WaitableCounter::Initialize(void) {
    s32 pHandle;

    if (nn::os::WaitableCounter::sHandle == 0) {
        pHandle = 0;
        if ((s32)(nn::svc::CreateAddressArbiter((nn::Handle*)&pHandle) & 0x80000000) >= 0) {
            nn::os::WaitableCounter::sHandle = pHandle;
        }
    }
}

}
}