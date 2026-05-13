#pragma once

#include "nn/applet/CTR/applet_Paramaters.h"

namespace nn{
namespace applet{ 
namespace CTR { 
namespace detail { 
namespace APPLET{ 
    Result AppletUtility(u32 id,u8 *pInParam,size_t inParamSize,u8 *pOutParam,size_t outParamSize,s32 *pReadLen);
    Result CancelLibraryApplet(bool isApplicationEnd);    
    Result CancelParamater(bool isSenderCheck, AppletId senderId, bool isReceiverCheck, AppletId receiverId, bool* pIsCanceled);
    Result CloseApplication(u8 *pParam,size_t paramSize,Handle handle);
    Result Enable(AppletAttr appletAttr);
    Result GetAppletManInfo(AppletPos appletPos,AppletPos *currentPos,AppletId *requestedAppletId,AppletId *homeMenuAppletId,AppletId *currentAppletId);
    Result GetLockHandle(Handle *pMutexHandle,AppletAttr appletAttr,AppletAttr *pAttrDecided,bit32 *pMiscState);
    Result GlanceParameter(AppletId *pSenderId,AppletId receiverId,u32 *pCommand,u8 *pParam,size_t paramSize,s32 *pReadLen,Handle *pHandle);
    Result Initialize(AppletId appletId,AppletAttr appletAttr,Handle *pEventHandle_mesg,Handle *pEventHandle_cont);
    Result InquireNotification(AppletId appletId,AppletNotification *notification);
    Result IsRegistered(AppletId appletId,bool *pRegistered);
    Result JumpToHomeMenu(u8 *pParam,size_t paramSize,Handle handle);
    Result NotifyToWait(AppletId id);
    Result PrepareToCloseApplication(bool isJumpToHome); // idk if dt has this
    Result PrepareToJumpToHomeMenu();
    Result PrepareToStartSystemApplet(AppletId id);
    Result ReceiveParameter(AppletId *pSenderId,AppletId receiverId,u32 *pCommand,u8 *pParam,size_t paramSize,s32 *pReadLen,Handle *pHandle);
    Result ReplySleepNotificationComplete();
    Result ReplySleepQuery(AppletId id,AppletQueryReply reply);
    Result SendCaptureBufferInfo(u8 *pParam,size_t paramSize);
    Result SendParameter(AppletId senderId,AppletId receiverId,u32 command,u8 *pParam,size_t paramSize,Handle pHandle);
    Result SleepSystem(bit64 awakeReason);
    Result StartSystemApplet(AppletId id,u8 *pParam,size_t paramSize,Handle handle);

    extern const nn::Handle sSession;
}
}
}
}
}