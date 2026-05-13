#pragma once

#include "nn/types.h"
#include "nn/fnd/fnd_TimeSpan.h"
#include "nn/os/os_SimpleLock.h"
#include "nn/os/os_WaitableCounter.h"

namespace nn{
namespace os{
    class LightEvent{
    public:
        nn::os::WaitableCounter mCounter;
        nn::os::SimpleLock mLock;

        static const s32 NOT_RESETED_MANUAL = -2;
        static const s32 NOT_RESETED_AUTO = -1;
        static const s32 RESETED_AUTO = 0; // 
        static const s32 RESETED_MANUAL = 1;

        void Initialize(bool);
        void Finalize();
        void ClearSignal();
        void Wait();
        void Signal();
        bool TryWait(fnd::TimeSpan timeout);
        ~LightEvent(){
        };

    }; // CriticalSection
} // os
}; // nn