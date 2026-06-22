#pragma once

#include "nn/os/os_Synchronization.h"

namespace nn{
namespace os{
    class Mutex : public nn::os::WaitObject{
    public:
        Mutex::~Mutex() { this->Close(); }
        void Finalize() { this->WaitObject::Finalize(); }
        void Lock() { this->WaitObject::WaitOne(); }
        inline void Mutex::Unlock(){
            NN_OS_ERROR_IF_FAILED(nn::svc::ReleaseMutex(GetHandle()));
        }
    };

}
}