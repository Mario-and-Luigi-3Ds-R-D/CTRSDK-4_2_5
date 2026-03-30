#include "nn/os/os_CriticalSection.h"

namespace nn{
namespace os{

void CriticalSection::Initialize() {
    this->mLock.nn::os::SimpleLock::Initialize();
    this->mThreadUniqueValue = 0;
    this->mLockCount = 0;
}

void CriticalSection::Enter(void) {
    int thread;
    __asm {mrc p15, 0, thread, c13, c0, 3} // mrc isnt cpp.. is it?
    if (thread != this->mThreadUniqueValue){ // Cant get cmp r0,r1 mfs always be like cmp r1,r0
        this->mLock.Lock();
        __asm {mrc p15, 0, thread, c13, c0, 3}  // mrc isnt cpp.. is it?
        this->mThreadUniqueValue = thread;
    }
    this->mLockCount += 1;
}

void CriticalSection::Leave() {
    s32 pCount;

    pCount = this->mLockCount - 1;
    this->mLockCount = pCount;
    if (pCount == 0) {
        this->mThreadUniqueValue = 0;
        this->mLock.nn::os::SimpleLock::Unlock();
    }
}

bool CriticalSection::TryEnter(void) {
    register u32 thread;
    __asm {mrc p15, 0, thread, c13, c0, 3}
    if (this->mThreadUniqueValue != thread) { // Fuckin' CMP wont budge! MEIN GOTT!
        if (this->mLock.TryLock() == 0) {
            return 0;
        }
        __asm {mrc p15, 0, thread, c13, c0, 3}
        this->mThreadUniqueValue = thread;
    }
    this->mLockCount = this->mLockCount + 1;
    return 1;
}

} // os
} // nn