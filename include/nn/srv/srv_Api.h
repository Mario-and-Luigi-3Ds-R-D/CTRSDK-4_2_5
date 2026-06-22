#pragma once

#include "nn/Handle.h"
#include "nn/Result.h"
#include "nn/os/os_CriticalSection.h"
#include "nn/fnd/fnd_Intrusive.h"

namespace nn {
namespace os{
class Semaphore;

}
namespace srv {
class NotificationHandler;

struct NotificationHandler : public fnd::IntrusiveLinkedList<NotificationHandler>::Item{
    bit32 mAttachedMessage;

    NotificationHandler() { }
};


Result Initialize();
Result StartNotification();
Result EnableNotification(os::Semaphore*);
Result DispatchNotification();
Result RegisterNotificationHandler(NotificationHandler* pHandler, bit32 message);
Result GetServiceHandle(nn::Handle* pOut, const char* pName, s32 nameLen, bit32 flags);

namespace detail {

Result Connect(const char* pName);

class HandlerManager{
public:
    nn::fnd::IntrusiveLinkedList<NotificationHandler> mHandler;

    ~HandlerManager();
    Result Register(NotificationHandler* pHandler, u32 message);
    NotificationHandler* Find(bit32 message){
        nn::srv::NotificationHandler *i
        NN_TASSERT_(message != 0);
        for(i = this->mHandler.GetFront(); i && i->mAttachedMessage != message; i = this->mHandler.GetNext(i)){
            ;
        }
        return i;
    }
};

} // namespace detail

namespace {
    extern const char PORT_NAME_SERVICE;
} // namespace

} // namespace srv
} // namespace nn
