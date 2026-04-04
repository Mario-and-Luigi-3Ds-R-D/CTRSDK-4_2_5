#pragma once

#include "nn/types.h"
#include "nn/os/os_Types.h"

namespace nn{
namespace os{

    class Mutex : public nn::os::WaitObject{
    public:
        Mutex::~Mutex() {
            if (this->mHandle != 0) {
                __asm{swi 0x23}
                this->mHandle = 0;
            }
        }

    };

}
}