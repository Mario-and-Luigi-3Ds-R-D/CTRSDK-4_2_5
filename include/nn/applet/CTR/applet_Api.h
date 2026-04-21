#pragma once

#include "nn/applet/CTR/applet_Paramaters.h"
#include "nn/fnd/fnd_TimeSpan.h"
#include "nn/os/os_TransferMemoryBlock.h"

// Mostly the detail ones, so yeah.

namespace nn { 
namespace applet {
namespace CTR {
bool IsInitialized();

namespace detail{
namespace{
    bool sIsApplet;
    bool sIsVramSaved;
    bool sIsInitialized;
    bool sIsGpuRightGiven;
    bool sIsDspSleeping;
}
    const char PORT_NAME_SYSTEM[] = "APT:S";
    const char PORT_NAME_USER[] = "APT:U";
    // Main Applet
    void Enable(bool isSleepEnabled);
    void CallUtility(u32 utilityId, u8* pInParam, size_t inParamSize, u8* outParam, size_t outParamSize, s32* readSize);
    bool WaitForRegister(AppletId appletId,nn::fnd::TimeSpan span);
    Result CloseApplication(u8 *pParam,size_t paramSize,nn::Handle handle);

    // RIGHTS.
    //
    // #AppletGPURightsMatter
    void AssignGpuRight(bool flag);
    void AssignCameraRight(bool flag);
    void AssignDspRight(bool flag);

    Result CancelLibraryAppletIfRegistered(bool isApplicationEnd, nn::applet::CTR::AppletWakeupState *pWakeupState);
    bool CancelParamater(bool isSenderCheck, AppletId senderId, bool isReceiverCheck, AppletId receiverId);
    Result JumpToHomeMenu(u8 *pParam,size_t paramSize,Handle handle);
    void PrepareToJumpToHomeMenu();
    void GetAppletManInfo(AppletPos requestPos,AppletPos *pCurrentPos,AppletId *pRequestedId,AppletId *pHomeMenuId,AppletId *pCurrentId);
    void UnlockTransition(u32 action);
    void LockTransition(u32 action,bool isForced);
    void SleepIfShellClosed(); // ASM
    void ReplySleepQueryToManager(QueryReply);
}
}
}
}