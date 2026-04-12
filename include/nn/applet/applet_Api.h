#pragma once

#include "nn/applet/applet_Paramaters.h"
#include "nn/fnd/fnd_TimeSpan.h"
#include "nn/os/os_TransferMemoryBlock.h"
#include "nn/Result.h"
#include "nn/Handle.h"

// Mostly the detail ones, so yeah.

namespace nn { 
namespace applet {
namespace CTR {
namespace detail{
    // Main Applet
    void Enable(bool isSleepEnabled);
    void CallUtility(u32 utilityId, u8* pInParam, size_t inParamSize, u8* outParam, size_t outParamSize, s32* readSize);
    bool WaitForRegister(AppletId appletId,nn::fnd::TimeSpan span);
    Result CloseApplication(u8 *pParam,size_t paramSize,nn::Handle handle);

    // GPU Rights
    //
    // #AppletGPURightsMatter
    bool IsGpuRightGiven();
    void AssignGpuRight(bool flag);

    void AttachTransferMemoryHandle(os::TransferMemoryBlock* transferMemory, nn::Handle handle, size_t size, bit32 otherPermission);

    // Cancel
    Result CancelLibraryApplet(bool isApplicationEnd);
    Result CancelLibraryAppletIfRegistered(bool isApplicationEnd, nn::applet::CTR::AppletWakeupState *pWakeupState);
    bool CancelParamater();

    void UnlockTransition(u32 action);
    void SleepIfShellClosed();

}
}
}
}