#pragma once

#include "nn/Handle.h"
#include "nn/Result.h"

namespace nn{
namespace srv{
namespace detail{
namespace Service{
    extern nn::Handle sSession;

    Result EnableNotication(nn::Handle* pSemaphore); 
    Result GetServiceHandle(nn::Handle* pOut, const char* pService, s32 nameLen, u32 flags);
    Result ReceiveNotification(bit32 *pOut);
    Result RegisterClient(void);
};
    Result Connect(const char*);
}
}
}