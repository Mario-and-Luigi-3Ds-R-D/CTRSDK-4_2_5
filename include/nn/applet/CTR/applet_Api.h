#pragma once

#include "nn/applet/CTR/applet_Paramaters.h"
#include "nn/applet/CTR/applet_Result.h"
#include "nn/fnd/fnd_TimeSpan.h"
#include "nn/os/os_TransferMemoryBlock.h"
#include "nn/os/os_Thread.h"

// Mostly the detail ones, so yeah.

namespace nn { 
namespace applet {
namespace CTR {
bool IsInitialized();

    extern const nn::Handle HANDLE_NONE;

namespace detail{
namespace{
    bool sIsApplet;
    bool sIsVramSaved;
    bool sIsInitialized;
    bool sIsGpuRightGiven;
    bool sIsDspSleeping;
}

    /* Main Applet */

    /// @param in AppletAttr appletAttr
    ///
    /// @brief Initializes the Application, used by init_Default
    Result Initialize(AppletAttr applerAttr);

    /// @param in bool isSleepEnaled = true
    ///
    /// @brief Enable
    void Enable(bool isSleepEnabled = true);

    bool IsRegistered(AppletId appletId);

    /// @param in AppletId appletId, nn::fnd::TimeSpan span
    ///
    /// @brief Uses a Tick Checker to Wait on a Register.
    bool WaitForRegister(AppletId appletId, nn::fnd::TimeSpan span);

    Result CancelLibraryApplet( bool isApplicationEnd = false ); // inline
    Result CancelLibraryAppletIfRegistered(bool isApplicationEnd = false, AppletWakeupState *pWakeupState=NULL);

    Result PrepareToCloseApplication(bool isCancelPreload = false);
    Result CloseApplication(u8 *pParam,size_t paramSize,nn::Handle handle);

    Result CallUtility(u32 utilityId, u8* pInParam, size_t inParamSize, u8* outParam, size_t outParamSize, s32* readSize);

    void AssignGpuRight(bool flag);
    void AssignCameraRight(bool flag);
    void AssignDspRight(bool flag);

    Result JumpToHomeMenu(u8 *pParam,size_t paramSize,Handle handle);
    Result PrepareToJumpToHomeMenu();

    void UnlockTransition(u32 action);
    void LockTransition(u32 action,bool isForced);

    bool CancelParemater(bool isSenderCheck, AppletId senderId, bool isReceiverCheck, AppletId receiverId);

    void GetAppletManInfo(AppletPos requestPos,AppletPos *pCurrentPos,AppletId *pRequestedId,AppletId *pHomeMenuId,AppletId *pCurrentId);

    void SleepIfShellClosed();

    Result InitializeConnect(AppletId appletId, AppletAttr attr, s32 threadPriority);

    void SetActive();

    void ReplySleepQueryToManager(QueryReply);
    void ReplySleepNotificationCompleteToManager();

    Result PrepareToStartSystemApplet(AppletId id);
    Result StartSystemApplet(AppletId id, u8* pParam, size_t size, nn::Handle handle);
    
    Result Glance(AppletId *pSenderId,u32 *pCommand,u8 *pParam,size_t paramSize,s32 *pReadLen,Handle *pHandle);

    void NotifyToWait();

    Result Receive(AppletId *pSenderId,u32 *pCommand,u8 *pParam,size_t paramSize,s32 *pReadLen,Handle *pHandle,fnd::TimeSpan timeout);

    struct LockTransitionParam{
        u32 action;
        bool isForced;
        s8 rev[3];
    };

    inline void WaitBySleep(int msecs){
        fnd::TimeSpan span = fnd::TimeSpan::FromMilliSeconds(msecs);
        os::Thread::Sleep(span);
    }
}
}
}
}