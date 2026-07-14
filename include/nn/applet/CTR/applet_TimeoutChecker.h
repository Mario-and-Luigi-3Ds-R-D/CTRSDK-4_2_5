#pragma once

#include <nn/os/os_Tick.h>
#include <nn/applet/CTR/applet_Paramaters.h>

namespace nn{
namespace applet{
namespace CTR{
namespace detail{

class TimeoutChecker{
    const fnd::TimeSpan mTimeout;
    os::Tick mStart;
public:
    TimeoutChecker(fnd::TimeSpan timeout):
        mTimeout(timeout){
        if (timeout == CTR::NO_WAIT || timeout == CTR::WAIT_INFINITE) {
            mStart = os::Tick();
        } 
        else {
            mStart = os::Tick::GetSystemCurrent();
        }
    }
    ~TimeoutChecker(){ }
    bool Check(){
        if (mTimeout == CTR::NO_WAIT){
            return true;
        }
        if (mTimeout == CTR::WAIT_INFINITE){
            return false;
        }
        if (mTimeout < nn::fnd::TimeSpan(nn::os::Tick::GetSystemCurrent() - this->mStart)){
            return true;
        }
    }
};

}
}
}
}
