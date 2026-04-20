#include <nn/os/os_Initialize.h>
#include <nn/os/os_Thread.h>
#include <nn/os/os_WaitableCounter.h>
#include <nn/os/os_SharedMemory.h>
#include <nn/os/os_StackMemory.h>

namespace nn{
namespace os{
void Initialize(){
    nn::os::WaitableCounter::Initialize();
    nn::os::detail::SaveThreadLocalRegionAddress();
    nn::os::detail::InitializeSharedMemory();
    nn::os::detail::InitializeStackMemory();
    //nn::os::detail::InitializeThreadEnvrionment();
}

}
}