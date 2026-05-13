#include <nn/applet/CTR/applet_Connect.h>

namespace nn{
namespace applet{
namespace CTR{
namespace detail{
namespace{
    static os::Mutex sMutex;
}

void LockAndConnect(){
    // TODO
}

void DisconnectAndUnlock(){
    // TODO
}

void GetDisplayInfo(AppletDisplayInfo* pInfo){
    // TODO
}

void InitializeMutex(nn::Handle handle){
    sMutex.mHandle = handle.mHandle;
}

}
}
}
}