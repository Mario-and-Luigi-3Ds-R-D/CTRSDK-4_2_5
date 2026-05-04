#pragma once

#include "nn/types.h"
#include "nn/util/util_NonCopyable.h"
#include "nn/os/os_WaitableCounter.h"
#include "nn/os/os_Types.h"

namespace nn{ 
namespace os{
    class SimpleLock : private nn::util::NonCopyable<SimpleLock>{
    private:
        WaitableCounter mCounter;
    public:
        SimpleLock()  {}
        ~SimpleLock() {}
        
        void Initialize(void);
        void Lock(void);
        void LockImpl(void);
        bool TryLock(void);
        void Unlock(void);
    };
}
};