#pragma once

#include "nn/types.h"
#include "nn/os/os_SimpleLock.h"
#include "nn/os/os_Types.h"

namespace nn { 
namespace os {
    class CriticalSection {
    public:
        SimpleLock mLock;
        u32 mThreadUniqueValue;
        s32 mLockCount;

        void Initialize(void);
        void Enter(void);
        void Leave(void);
        bool TryEnter(void);
        ~CriticalSection() {
        }
            struct ScopedLock {
                nn::os::CriticalSection* mReference;
                ScopedLock(nn::os::CriticalSection& cs) : mReference(&cs) {mReference->Enter();}

                ~ScopedLock(){mReference->Leave();}
    
            };
        };
    }
};