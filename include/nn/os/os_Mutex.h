#pragma once

#include "nn/types.h"
#include "nn/os/os_Types.h"

namespace nn{
namespace os{
    class Mutex : public nn::os::WaitObject{
    public:
        Mutex::~Mutex() {
            this->Close();
        }
        void Finalize() {
            WaitObject::Finalize(); 
        }

    };

}
}