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
}
namespace{
    nn::os::StackBuffer<1> sBuffer;
}
    static os::Event sEvent[3];
    static os::Thread sThread;
    static os::LightEvent sControlLight;

void InitializeClientThread(s32 threadPriority, Handle hControl, Handle hMessage){
    sEvent[1].Initialize(false);
    sEvent[1].Finalize();
    sEvent[1].SetHandle(hMessage);
    sEvent[2].Initialize(false);
    sControlLight.Initialize(true);
    sIsThreadEnd = false;
    sThread.Start(ThreadFunc,0,sBuffer,threadPriority);
}

void FinalizeClientThread(){
    sIsThreadEnd = true;
    sEvent[0].Signal();
    sThread.Join();
    sThread.Finalize();
    sControlLight.Finalize();
    for(int i = 0; i < 3; i++){
        sEvent[i].Finalize();
    }
}

void SetReceiveCallback(AppletReceiveCallback callback,uptr parameter){
    sReceiveCallback = callback;
    sReceiveCallbackParam = parameter;
}

void WaitForControlEvent(){
    sControlLight.Wait();
}

bool TryWaitForControlEvent(){
    return sControlLight.TryWait();
}

void ClearControlEvent(){
    sControlLight.ClearSignal();
}

void ThreadFunc(int param){

}

}
}
}
}