#pragma once

#include "nn/Handle.h"
#include "nn/Result.h"
#include "nn/os/os_CriticalSection.h"
#include "nn/fnd/fnd_Intrusive.h"

namespace nn {
namespace srv {
namespace detail {
Result Connect(const char*);
}
class HandlerManager{
public:
    nn::fnd::IntrusiveLinkedList<HandlerManager> mHandler;
        
    ~HandlerManager();
};

struct NotificationHandler : public fnd::IntrusiveLinkedList<NotificationHandler>::Item{
    bit32 mAttachedMessage;

    NotificationHandler() { }
};

Result Initialize();
Result StartNotification();
Result RegisterNotificationHandler(NotificationHandler* pHandler, bit32 message);
Result GetServiceHandle(nn::Handle *pOut, const char *pName, s32 nameLen, bit32 flags);

namespace{
void DispatcherThread();

extern const char const PORT_NAME_SERVICE;
//static NotificationHandler* sHandlerManager;
}
} // Namespace srv
} // Namespace nn
