#pragma once

#include "nn/applet/CTR/applet_Paramaters.h"
#include "nn/os/os_Mutex.h"

namespace nn{
namespace applet{
namespace CTR{
namespace detail{
namespace{
    extern os::Mutex sMutex;
}
namespace{
    const char PORT_NAME_SYSTEM[] = "APT:S";
    const char PORT_NAME_USER[] = "APT:U";
}
    void DisconnectAndUnlock();
    void LockAndConnect();
    void GetDisplayInfo(AppletDisplayInfo* pInfo);
    void InitializeMutex(Handle handle);

}
}
}
}