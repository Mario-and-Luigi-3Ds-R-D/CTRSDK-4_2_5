// Filename: util_Symbol.cpp
//
// Project: Horizon 4_2_5 Decompilation
//
// Remade by user Luigifan27

#include <nn/srv/srv_Api.h>
#include <nn/srv/detail/srv_Service.h>
#include <nn/os/os_Thread.h>

#include <nn/dbg/dbg_DebugString.h>
#include <nn/dbg/dbg_Break.h>

namespace nn{
namespace srv{
namespace{
void DispatcherThread(){

}

}
namespace detail{
Result Connect(const char*){

}

static HandlerManager* sHandlerManager = 0;

#ifdef NONMATCHING
#endif

NN_INLINE Result HandlerManager::Register(NotificationHandler* pHandler, u32 message){
    #ifdef NN_DEBUG
    if(pHandler){
        nndbgBreakWithTMessage_(NN_DBG_BREAK_REASON_ASSERT,"srv_Api.cpp",36,"%s(=0x%08X) is invalid pointer", "pHandler", pHandler);
    }
    if(message != 0){
        nndbgBreakWithTMessage_(NN_DBG_BREAK_REASON_ASSERT,"srv_Api.cpp",39,"%s","message != 0");
    }
    if(pHandler->mAttachedMessage == 0){
        nndbgBreakWithTMessage_(NN_DBG_BREAK_REASON_ASSERT,"srv_Api.cpp",42,"%s","pHandler->mAttachedMessage == 0");
    }
    #endif
    pHandler->mAttachedMessage = message;
    this->mHandler.PushBack(pHandler);
    return ResultSuccess();
}

}

int sInitializeCount = 0;
static os::CriticalSection sInitializeLock;
const char PORT_NAME_SERVICE[] = "srv:";

Result Initialize(){
    os::CriticalSection& lock = srv::sInitializeLock;
    lock.Enter();
    if(srv::sInitializeCount > 0){
        srv::sInitializeCount++;
        Result res; res.mResult = 0x82067F9;
        lock.Leave();
        return res;
    }
    Result connect = detail::Connect(srv::PORT_NAME_SERVICE);
    lock.Leave();
    return connect;
}

Result StartNotification(){

}

#ifdef NONMATCHING
#endif

Result RegisterNotificationHandler(NotificationHandler* pHandler, u32 message){
    return detail::sHandlerManager->Register(pHandler,message);
}

Result GetServiceHandle(nn::Handle *pOut, const char *pName, s32 nameLen, bit32 flags) {
    if (srv::sInitializeCount <= 0) {
        Result res; res.mResult = 0xD8A067F8;
        return res;
    }
    if (nameLen > 8) {
        Result res; res.mResult = 0xD9006405;
        return res;
    }
    return nn::srv::detail::Service::GetServiceHandle(pOut, pName, nameLen, flags);
    #ifdef NN_DEBUG
        nndbgTPrintWarning_("srv_Api.cpp",92,"Failed to open service \"%s\"\n",pName);
    #endif
}


}
}