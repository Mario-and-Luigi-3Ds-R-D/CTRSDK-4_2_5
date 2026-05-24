#pragma once

#include "nn/Result.h"
#include "nn/applet/CTR/applet_Paramaters.h"
#include "nn/os/os_CriticalSection.h"
#include "nn/fnd/fnd_TimeSpan.h"

namespace nn { 
namespace applet {
namespace CTR {
    void InitializeWrapper();

    void EnableSleep(bool isSleepCheck);
    void SetSleepQueryCallback(AppletSleepQueryCallback callback,uptr arg);
    void DisableSleep(bool isReplyReject);
    void SetAwakeCallback(AppletAwakeCallback callback,uptr arg);
    //void SetSleepCanceledCallback(AppletSleepCanceledCallback callback, uptr arg);

    bool ReceiveCallbackForCommands(uptr callback);

    bool ProcessPowerButton();
    bool ProcessHomeButton();
    void ClearHomeButtonState();
    bool IsExpectedToProcessHomeButton();
    void ReplySleepQuery(QueryReply reply);
    SleepNotificationState IsExpectedToReplySleepQuery();

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

    AppletWakeupState WaitForStarting(AppletId* pSenderId,  u8* pParam, size_t paramSize, s32* pReadLen, Handle* pHandle, fnd::TimeSpan timeout);

    bool IsEnableSleep();

}
}
}
}