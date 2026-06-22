#pragma once

#include "nn/os/os_Tick.h"
#include "nn/applet/CTR/applet_Paramaters.h"

namespace nn{
namespace applet{
namespace CTR{
namespace detail{

class TimeoutChecker{
    fnd::TimeSpan mTimeout;
    os::Tick mStart;

    TimeoutChecker(fnd::TimeSpan timeout) {
        this->mTimeout = timeout;
        if (timeout == CTR::NO_WAIT || timeout == CTR::WAIT_INFINITE) {
            this->mStart = os::Tick();
        } 
        else {
            this->mStart = os::Tick::GetSystemCurrent();
        }
    }
    ~TimeoutChecker(){ }
    bool Check();
};

inline bool TimeoutChecker::Check(){
    if (this->mTimeout == CTR::NO_WAIT) {
        return true;
    }
    if (this->mTimeout == CTR::WAIT_INFINITE) {
        return false;
    }
    fnd::TimeSpan elapsed = (os::Tick::GetSystemCurrent() - this->mStart).ToTimeSpan();
    return this->mTimeout < elapsed;
}

}
}
}
}
