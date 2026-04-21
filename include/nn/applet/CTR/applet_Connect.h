#pragma once

#include "nn/applet/CTR/applet_Paramaters.h"
#include "nn/os/os_Mutex.h"

namespace nn{
namespace applet{
namespace CTR{
namespace detail{
namespace{
    extern os::Mutex* sMutex;
} 
    void LockAndConnect();
    void InitializeConnect(AppletId appletId, AppletAttr attr, s32 threadPriority);
    void DisconnectAndUnlock();
    void Disconnect();
    void GetDisplayInfo(AppletDisplayInfo* pInfo);
    void InitializeMutex(Handle handle);

}
}
}
}