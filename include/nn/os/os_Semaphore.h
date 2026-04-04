#pragma once

#include "nn/os/os_Event.h"

namespace nn{
namespace os{
    
    class Semaphore : public nn::os::InterruptEvent{
    public:

        ~Semaphore();
    };
}
}