// Filename: srv_Api.cpp
//
// Project: Horizon Decompilation

#include <nn/srv/srv_API.h>
#include <nn/srv/srv_Service.h>

#include <nn/os/os_Thread.h>
#include <nn/os/os_Semaphore.h>

#include <nn/util/util_Result.h>

#include <nn/dbg/dbg_DebugString.h>
#include <nn/dbg/dbg_Break.h>

#define NN_NOTIFICATION_PRIORITY 1359598848

namespace nn {
namespace srv {

    int sInitializeCount;
    os::CriticalSection sInitializeLock;
    const char PORT_NAME_SERVICE[] = "srv:";

namespace detail {
    
class HandlerManager{
public:
    nn::fnd::IntrusiveLinkedList<NotificationHandler> mHandler;

    Result Register(NotificationHandler* pHandler, u32 message) {
        NN_POINTER_TASSERT_(pHandler);
        NN_TASSERT_(message != 0);
        NN_TASSERT_(!pHandler->mAttachedMessage == 0);

        pHandler->mAttachedMessage = message;
        this->mHandler.PushBack(pHandler);
        return ResultSuccess();
    }
    NotificationHandler* Find(bit32 message){
        nn::srv::NotificationHandler *i
        NN_TASSERT_(message != 0);
        for(i = this->mHandler.GetFront(); (i != 0 && (i->mAttachedMessage != message)); i = this->mHandler.GetNext(i)){
            if(i->mAttachedMessage == message){
                break;
            }
        }
        return i;
    }

};
    static HandlerManager sHandlerManager;

    NN_NOINLINE Result Connect(const char* name) {
        Result res;
        while (true) {
            res = svc::ConnectToPort(&Service::sSession, name);
            if (res.GetLevel()       != Result::LEVEL_PERMANENT   ||
                res.GetSummary()     != Result::SUMMARY_NOT_FOUND ||
                res.GetDescription() != 1018) break;
            os::Thread::Sleep(fnd::TimeSpan::FromNanoSeconds(1000 * 500));
        }
        if (res.IsSuccess()) {
            res = Service::RegisterClient();
            sInitializeCount++;
        }
        return res;
    }
}
namespace {
    os::Semaphore sNotificationSemaphore;
    os::Thread sNotificationDispatcher;

    void DispatcherThread() {
        Result result;
        for(;;){
            sNotificationSemaphore.Acquire();
            result = DispatchNotification();
            NN_PANIC_IF_FAILED(result);
        }
    }
}

namespace {
    os::StackBuffer<4132> sStack;
}

Result Initialize() {
    os::CriticalSection::ScopedLock lock(sInitializeLock);
    if (srv::sInitializeCount > 0) {
        srv::sInitializeCount++;
        Result res; res.mResult = 0x82067F9;
        return res;
    }
    NN_MIN_TASSERT_(sInitializeCount, 0);
    Result connect = detail::Connect(srv::PORT_NAME_SERVICE);
    return connect;
}

Result StartNotification() {
    Result res = EnableNotification(&sNotificationSemaphore);
    if (res.IsSuccess()) {
        sNotificationDispatcher.Start(&DispatcherThread, sStack, NN_NOTIFICATION_PRIORITY);
    }
}

Result EnableNotification(os::Semaphore* pOut) {
    Result res;
    Handle h;
    res = detail::Service::EnableNotication(&h);
    if (res.IsSuccess())
        pOut->SetHandle(h);
    return res;
}

Result DispatchNotification() {
    bit32 message;
    Result res = detail::Service::ReceiveNotification(&message);
    if(res.IsFailure()){
        return res;
    }
    NotificationHandler* pHandler = detail::sHandlerManager.Find(message);
    if (pHandler != NULL) {
        pHandler->HandleNotification(message);
        return ResultSuccess();
    }
    else
        return ResultSuccess();
}

Result RegisterNotificationHandler(NotificationHandler* pHandler, u32 message) {
    return detail::sHandlerManager.Register(pHandler, message);
}

Result GetServiceHandle(nn::Handle* pOut, const char* pName, s32 nameLen, bit32 flags) {
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