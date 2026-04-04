#pragma once

#include "nn/types.h"
#include "nn/Handle.h"
#include "nn/Result.h"
#include "nn/fnd/fnd_Intrusive.h" //rename 2 Intrusive.h
#include "nn/os/os_LightEvent.h"

namespace nn{
namespace srv{
    class NotificationHandler : public nn::fnd::IntrusiveLinkedList::Item{
    public:
        bit32 mAttached;
    };

    class EventNotificationHandlerBase : public nn::srv::NotificationHandler{ // how to <> ..?
    public:
        nn::os::LightEvent* mLightEvent;

        void HandleNotification(bit32 mMessage);
    };

    Result RegisterNotificationHandler(nn::srv::NotificationHandler *pHandler,bit32 pMessage);
}
}