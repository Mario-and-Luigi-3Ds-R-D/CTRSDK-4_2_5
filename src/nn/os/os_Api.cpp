#include "nn/os/os_Api.h"
#include "nn/os/os_WaitableCounter.h"
#include "nn/os/os_SharedMemory.h"
#include "nn/os/os_StackMemory.h"

namespace nn{
namespace os{

void Initialize(){
    nn::os::WaitableCounter::Initialize();
}

}
}