#pragma once

#include "nn/applet/CTR/applet_Paramaters.h"
#include "nn/fnd/fnd_TimeSpan.h"
#include "nn/os/os_TransferMemoryBlock.h"

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

    // Main Applet
    void Enable(bool isSleepEnabled);
    void Initialize();
    void CallUtility(u32 utilityId, u8* pInParam, size_t inParamSize, u8* outParam, size_t outParamSize, s32* readSize);
    bool WaitForRegister(AppletId appletId,nn::fnd::TimeSpan span);
    Result CloseApplication(u8 *pParam,size_t paramSize,nn::Handle handle);

    Result InitializeConnect(AppletId appletId, AppletAttr attr, s32 threadPriority);
    Result Connect();
    void Disconnect();

    void AssignGpuRight(bool flag);
    void AssignCameraRight(bool flag);
    void AssignDspRight(bool flag);

    Result CancelLibraryAppletIfRegistered(bool isApplicationEnd, nn::applet::CTR::AppletWakeupState *pWakeupState);
    bool CancelParamater(bool isSenderCheck, AppletId senderId, bool isReceiverCheck, AppletId receiverId);
    Result JumpToHomeMenu(u8 *pParam,size_t paramSize,Handle handle);
    Result PrepareToJumpToHomeMenu();
    void GetAppletManInfo(AppletPos requestPos,AppletPos *pCurrentPos,AppletId *pRequestedId,AppletId *pHomeMenuId,AppletId *pCurrentId);
    void UnlockTransition(u32 action);
    void LockTransition(u32 action,bool isForced);
    void SleepIfShellClosed(); // ASM
    void ReplySleepQueryToManager(QueryReply);
    Result Glance(AppletId *pSenderId,u32 *pCommand,u8 *pParam,size_t paramSize,s32 *pReadLen,Handle *pHandle);

    struct LockTransitionParam{
        u32 action;
        bool isForced;
        s8 rev[3];
    };
}
}
}
}