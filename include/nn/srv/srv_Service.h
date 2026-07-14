#pragma once

#include <nn/Handle.h>
#include <nn/Result.h>

namespace nn{
namespace srv{
namespace detail{
    
class Service{
public:
    static nn::Handle sSession;

    static Result EnableNotication(nn::Handle* pSemaphore); 
    static Result GetServiceHandle(nn::Handle* pOut, const char* name, s32 nameLen, u32 flags);
    static Result ReceiveNotification(bit32 *pOut);
    static Result RegisterClient(void);
};

}
}
}