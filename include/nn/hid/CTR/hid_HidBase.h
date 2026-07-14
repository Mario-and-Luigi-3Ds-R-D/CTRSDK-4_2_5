#pragma once

#include <nn/Handle.h>
#include <nn/Result.h>
#include <nn/types.h>
#include <nn/fnd/fnd_Timespan.h>
#include <nn/os/os_Synchronization.h>
#include <nn/os/os_Event.h>

namespace nn{
namespace hid{
namespace CTR{

class HidBase : public nn::os::EventBase{
protected:
    HidBase() : nn::os::EventBase() {}
    ~HidBase() {}
public:
    uptr mResourcePtr;

    uptr GetResource();
    void SetResource(uptr);
};

inline uptr HidBase::GetResource(){
    return mResourcePtr;
}

inline void HidBase::SetResource(uptr ptr){
    this->mResourcePtr = ptr;
}

}
}
}