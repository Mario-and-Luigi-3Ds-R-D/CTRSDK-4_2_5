#pragma once

#include "nn/Handle.h"
#include "nn/Result.h"

namespace nn{
namespace srv{
namespace detail{

    class Service{
    public:
        Result EnableNotication(nn::Handle* pSemaphore);
        static Result GetServiceHandle(nn::Handle* pOut, const char* pService, int, uint);
        Result ReceiveNotification(bit32 *pOut);
        Result RegisterClient(void);
    };
}
}
}