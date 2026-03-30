#pragma once

#include "nn/os/os_Api.h"

namespace nn{
namespace os{
    class InterruptEvent : public nn::os::WaitObject{
    };

    class EventBase : public nn::os::InterruptEvent{
    };

    class Event : public nn::os::EventBase{ // most pointless heiharchy
    public:
        Event(){
            this->mHandle = (nn::Handle)0;
        }
        ~Event(){
        }
    };
}
}