#pragma once

#include "nn/types.h"
#include "nn/os/os_WaitableCounter.h"
#include "nn/os/os_Types.h"

namespace nn{ 
namespace os{
    class SimpleLock{
        WaitableCounter mCounter;
    public:
        void Initialize(void);
        void Lock(void);
        void LockImpl(void);
        bool TryLock(void);
        void Unlock(void);
    };
}
};