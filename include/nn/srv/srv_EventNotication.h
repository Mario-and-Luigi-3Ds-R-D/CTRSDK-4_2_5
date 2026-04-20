#pragma once

#include "nn/types.h"
#include "nn/Handle.h"
#include "nn/Result.h"
#include "nn/srv/srv_Api.h"
#include "nn/fnd/fnd_Intrusive.h"
#include "nn/os/os_LightEvent.h"

namespace nn{
namespace srv{
    class EventNotificationHandlerBase : public NotificationHandler{
    public:
        os::LightEvent* mLightEvent;

        void HandleNotification(bit32 mMessage){
            this->mLightEvent->Signal();
        }
    };
}
}