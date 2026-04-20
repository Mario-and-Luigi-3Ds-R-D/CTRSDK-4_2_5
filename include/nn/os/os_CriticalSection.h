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

        void Initialize(void); // Initialize Thread Crit. Sect.
        void Enter(void); // Enter Thread Crit. Sect.
        void Leave(void); // Leave Thread Crit. Sect.
        bool TryEnter(void); // Try to enter Thread Crit. Sect.
        ~CriticalSection() { // deconst
        }
            struct ScopedLock {
                nn::os::CriticalSection* mReference;
                ScopedLock(nn::os::CriticalSection& cs) : mReference(&cs) {mReference->Enter();}

                ~ScopedLock(){mReference->Leave();}
    
            };
        };
    }
};