#pragma once

#include "nn/types.h"
#include "nn/util/util_NonCopyable.h"
#include "nn/util/detail/util_ScopeLockImpl.h"
#include "nn/os/os_WaitableCounter.h"
#include "nn/os/os_Types.h"

namespace nn{ 
namespace os{
    class SimpleLock : private nn::util::NonCopyable<SimpleLock>{
    public:
        WaitableCounter mCounter;
    public:
        class ScopedLock;

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

NN_UTIL_DETAIL_DEFINE_SCOPED_LOCK(nn::os::SimpleLock, Lock(), Unlock());