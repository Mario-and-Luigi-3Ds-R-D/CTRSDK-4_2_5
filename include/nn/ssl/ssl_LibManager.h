#pragma once

#include "nn/Handle.h"
#include "nn/os/os_CriticalSection.h"

namespace nn{
namespace ssl{
namespace detail{

class LibManager{
protected:
    int flag_0x4;
    os::CriticalSection* mCriticalSection;
    int flag_0xc;
    int flag_0x10;
    os::HandleObj mHandleObj;
public:
    virtual ~LibManager();
};

extern LibManager gLibManager;
}
}
}