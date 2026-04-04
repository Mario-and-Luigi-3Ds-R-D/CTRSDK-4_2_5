#include "nn/os/os_WaitableCounter.h"
#include "nn/svc/svc_Api.h"

namespace nn{
namespace os{
    
void WaitableCounter::Initialize(void) {
    nn::Handle* pHandle;

    if (nn::os::WaitableCounter::sHandle == 0) {
        pHandle = 0;
        if ((s32)(nn::svc::CreateAddressArbiter((nn::Handle*)&pHandle) & 0x80000000) >= 0) { // If Result is 1 or higher then we gucci
            nn::os::WaitableCounter::sHandle = pHandle;
        }
    }
}

} // os
} // nn