#pragma once

#include "nn/Result.h"
#include "nn/applet/CTR/applet_Paramaters.h"
#include "nn/os/os_CriticalSection.h"
#include "nn/fnd/fnd_TimeSpan.h"

namespace nn { 
namespace applet {
namespace CTR {
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
    bool IsExpectedToProcessHomeButton();
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

namespace detail{
    Result CaptureScreenForSystemApplet(AppletId id);
    Result WaitToCaptureScreen(AppletId id, Handle* pHandle);
    bool ReceiveCallbackForCommands(uptr ptr);
    AppletWakeupState WaitForStarting(AppletId* pSenderId,  u8* pParam, size_t paramSize, s32* pReadLen, Handle* pHandle, fnd::TimeSpan* timout);

}
}
}
}