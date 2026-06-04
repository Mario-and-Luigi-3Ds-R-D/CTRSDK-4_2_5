#pragma once

#include "nn/Handle.h"
#include "nn/Result.h"
#include "nn/os/os_CriticalSection.h"
#include "nn/fnd/fnd_Intrusive.h"

namespace nn {
namespace srv {
class NotificationHandler;

struct NotificationHandler : public fnd::IntrusiveLinkedList<NotificationHandler>::Item{
    bit32 mAttachedMessage;

    NotificationHandler() { }
};


Result Initialize();
Result StartNotification();
Result RegisterNotificationHandler(NotificationHandler* pHandler, bit32 message);
Result GetServiceHandle(nn::Handle* pOut, const char* pName, s32 nameLen, bit32 flags);

namespace detail {

Result Connect(const char* pName);

class HandlerManager{
public:
    nn::fnd::IntrusiveLinkedList<NotificationHandler> mHandler;

    ~HandlerManager();
    Result Register(NotificationHandler* pHandler, u32 message);
};

} // namespace detail

namespace {
    extern const char PORT_NAME_SERVICE;
} // namespace

} // namespace srv
} // namespace nn
