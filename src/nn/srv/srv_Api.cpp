// Filename: util_Symbol.cpp
//
// Project: Horizon 4_2_5 Decompilation
//
// Remade by user Luigifan27

#include <nn/srv/srv_Api.h>
#include <nn/srv/detail/srv_Service.h>
#include <nn/os/os_Thread.h>
#include <nn/os/os_Semaphore.h>

#include <nn/dbg/dbg_DebugString.h>
#include <nn/dbg/dbg_Break.h>

#define NN_NOTIFICATION_PRIORITY 1359598848

namespace nn{
namespace srv{
    int sInitializeCount;
    static os::CriticalSection sInitializeLock;
    const char PORT_NAME_SERVICE[] = "srv:";

namespace detail{
static HandlerManager* sHandlerManager;
Result Connect(const char* name){
    Result res;
    while(true){
        res = svc::ConnectToPort(&Service::sSession,name);
        if(res.GetLevel()       != Result::LEVEL_PERMANENT   ||
           res.GetSummary()     != Result::SUMMARY_NOT_FOUND ||
           res.GetDescription() != 1018) break;
        os::Thread::Sleep(fnd::TimeSpan::FromNanoSeconds(500000));

    }
    if(res.IsSuccess()){
        res = Service::RegisterClient();
        sInitializeCount++;
    }
    return res;
}


#ifdef NONMATCHING
#endif

NN_INLINE Result HandlerManager::Register(NotificationHandler* pHandler, u32 message){
    NN_POINTER_TASSERT_(pHandler);
    NN_TASSERT_(message != 0);
    NN_TASSERT_(!pHandler->mAttachedMessage);
    
    pHandler->mAttachedMessage = message;
    this->mHandler.PushBack(pHandler);
    return ResultSuccess();
}

}

namespace {
os::Semaphore sNotificationSemaphore;
os::Thread sNotificationDispatcher;

void DispatcherThread(){
    Result result;
    while(true){
        do{
            sNotificationSemaphore.Acquire();
        } while(!DispatchNotification().IsFailure());
        NN_PANIC_IF_FAILED(result);
    }
}

}

namespace{
    os::StackBuffer<4132> sStack;
}

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
    Result res = EnableNotification(&sNotificationSemaphore);
    if(res.IsSuccess()){
        sNotificationDispatcher.Start(DispatcherThread, sStack, NN_NOTIFICATION_PRIORITY);
    }
}

Result EnableNotification(os::Semaphore* pOut){
    Result res;
    Handle h;
    res = detail::Service::EnableNotication(&h);
    if(res.IsSuccess())
        pOut->SetHandle(h);
    return res;
}

Result DispatchNotification(){
    bit32 message;
    Result res = detail::Service::ReceiveNotification(&message);
    if(res.IsFailure())
        return res;
    detail::sHandlerManager->Find(message);
    return ResultSuccess();
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
    NN_TWARNING_(pName, "Failed to open service \"%s\"\n");
    return nn::srv::detail::Service::GetServiceHandle(pOut, pName, nameLen, flags);
}


}
}