#include <nn/applet/applet_All.h>

namespace nn{
namespace applet{
namespace CTR{
namespace detail{
namespace{
    static os::Mutex* sMutex = 0;
}

void LockAndConnect(){
    // TODO
}

void InitializeConnect(AppletId appletId, AppletAttr attr, s32 threadPriority){
    // TODO
}

void DisconnectAndUnlock(){
    // TODO
}

void Disconnect(){
    // TODO
}

void GetDisplayInfo(AppletDisplayInfo* pInfo){
    // TODO
}

void InitializeMutex(nn::Handle handle){
    sMutex = (os::Mutex*)handle.mHandle;
}

}
}
}
}