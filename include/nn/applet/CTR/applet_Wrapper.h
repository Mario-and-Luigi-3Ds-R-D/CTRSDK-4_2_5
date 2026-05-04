#pragma once

#include "nn/Result.h"
#include "nn/applet/CTR/applet_Paramaters.h"
#include "nn/os/os_CriticalSection.h"
#include "nn/fnd/fnd_TimeSpan.h"

namespace nn { 
namespace applet {
namespace CTR {
namespace{
    extern os::CriticalSection* sSleepAcceptedCriticalSection;

}
    void InitializeWrapper();
    void ClearHomeButtonState();
    void SetSleepQueryCallback(AppletSleepQueryCallback callback,uptr arg);
    void DisableSleep(bool isReplyReject);
    void EnableSleep(bool isSleepCheck);
    bool ReceiveCallbackForCommands(uptr callback);
    void SetAwakeCallback(AppletAwakeCallback callback,uptr arg);
    bool ProcessPowerButton();
    bool ProcessHomeButton();
    //void SetSleepCanceledCallback(AppletSleepCanceledCallback callback, uptr arg);
    void CloseAppletHook();


    class SysSleepAcceptedCallbackInfo{
    public:
        SysSleepAcceptedCallbackInfo* mPrev;
        SysSleepAcceptedCallbackInfo* mNext;
        AppletSysSleepAcceptedCallback mCallback;
        uptr mParamater;
        int mPriority;

        void Register();
        void Unregister();
    };
namespace{
    bool sleepEnable;
    SysSleepAcceptedCallbackInfo* spHead;
    SysSleepAcceptedCallbackInfo* spTail;
    int homeButtonCallback;
    int requestMemoryCallback;
    int receiveMessageCallback;
    int dspSleepCallback;
    int dspWakeUpCallback;
    int sleepQueryCallback;
    int sleepCanceledCallback;
    int sleepAcceptedCallback;
    int awakeCallback;
    int shutdownCallback;
    int powerButtonCallback;
    int transitionCallback;
    int closeCallback;
    int releaseMemoryCallback;
    int closeAppletCallback;
    int commandCallback;
    int homeButtonCallbackArg;
    int requestMemoryCallbackArg;
    int receiveMessageCallbackArg;
    int dspSleepCallbackArg;
    int dspWakeUpCallbackArg;
    int sleepQueryCallbackArg;
    int sleepCanceledCallbackArg;
    int sleepAcceptedCallbackArg;
    int awakeCallbackArg;
    int shutdownCallbackArg;
    int powerButtonCallbackArg;
    int transitionCallbackArg;
    int closeCallbackArg;
    int releaseMemoryCallbackArg;
    int closeAppletCallbackArg;
    int commandCallbackArg;

}

namespace detail{
    Result CaptureScreenForSystemApplet(AppletId id);
    Result WaitToCaptureScreen(AppletId id, Handle* pHandle);
    bool ReceiveCallbackForCommands(uptr ptr);
    AppletWakeupState WaitForStarting(AppletId* pSenderId,  u8* pParam, size_t paramSize, s32* pReadLen, Handle* pHandle, fnd::TimeSpan* timout);

}
}
}
}