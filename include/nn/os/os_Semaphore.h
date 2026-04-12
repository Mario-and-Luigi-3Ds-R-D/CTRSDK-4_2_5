#pragma once

#include "nn/os/os_Event.h"

namespace nn{
namespace os{
    
    class Semaphore : public nn::os::InterruptEvent{
    public:

        ~Semaphore(){
            if (this->mHandle != 0) {
            __asm{swi 0x23}
            this->mHandle = 0;
        }
    }
    };
}
}