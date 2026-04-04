#pragma once

#include "nn/os/os_Types.h"

namespace nn{
namespace os{
    class InterruptEvent : public nn::os::WaitObject{
    };

    class EventBase : public nn::os::InterruptEvent{
    };

    class Event : public nn::os::EventBase{ // most pointless heiharchy
    public:
    
        Event::Event(){
            this->mHandle = 0;
        }

        Event::~Event(){
            if(this->mHandle != 0) {
                __asm{swi 0x23}
                this->mHandle = 0;
            }
        }

    };
}
}