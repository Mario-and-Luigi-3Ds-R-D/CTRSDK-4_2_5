#pragma once

#include "nn/types.h"
#include "nn/os/os_SimpleLock.h"
#include "nn/os/os_WaitableCounter.h"

namespace nn{
namespace os{
    class LightEvent{
    public:
        nn::os::WaitableCounter mCounter;
        nn::os::SimpleLock mLock;

        static const s32 RESET_MANUAL = -2;
        static const s32 RESET_AUTO   = -1;
        static const s32 RESET_UNK0   = 0;
        static const s32 RESET_UNK1   = 1;

        void Initialize(bool);
        void Finalize();
        void ClearSignal(void);
        void Wait(void);
        void Signal(void);
        bool TryWait(void);
        ~LightEvent(){
        };

    }; // CriticalSection
} // os
}; // nn