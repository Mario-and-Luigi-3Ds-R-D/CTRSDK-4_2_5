#include <nn/applet/CTR/applet_ClientThread.h>
#include <nn/os/os_LightEvent.h>
#include <nn/os/os_Thread.h>

namespace nn { 
namespace applet {
namespace CTR {
namespace detail{
namespace{
    static bool sIsThreadEnd;
    static AppletReceiveCallback sReceiveCallback;
    static uptr sReceiveCallbackParam;
    static os::Thread sThread;
    static os::LightEvent sControlLight;

}
    static os::Event sEvent[3];

void SetReceiveCallback(AppletReceiveCallback callback,uptr parameter){
    sReceiveCallback = callback;
    sReceiveCallbackParam = parameter;
}

void WaitForControlEvent(){
    sControlLight.Wait();
}

bool TryWaitForControlEvent(){
//    return sControlLight.TryWait();
}

}
}
}
}