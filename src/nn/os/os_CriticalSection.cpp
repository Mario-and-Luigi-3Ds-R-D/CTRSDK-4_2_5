#include <nn/os/os_CriticalSection.h>

namespace nn{
namespace os{
// Initializes Thread CriticalSection

void CriticalSection::Initialize() {
    this->mLock.nn::os::SimpleLock::Initialize();
    this->mThreadUniqueValue = 0;
    this->mLockCount = 0;
}

// Enters Thread CriticalSection

void CriticalSection::Enter(void) {
    if(!this->LockedByCurrentThread()){
        this->mLock.Lock();
        this->OnLocked();
    }
    this->mLockCount += 1;
}

// Leaves Thread CriticalSection

void CriticalSection::Leave() {
    s32 pCount;

    pCount = this->mLockCount - 1;
    this->mLockCount = pCount;
    if (pCount == 0) {
        this->mThreadUniqueValue = 0;
        this->mLock.nn::os::SimpleLock::Unlock();
    }
}

// Trys to enter Thread CriticalSection, if cant TryLock. If so, add to the count and proceed.

bool CriticalSection::TryEnter(void) {
    if(!this->LockedByCurrentThread() ){
        if(!this->mLock.TryLock() ){
            return false;
        }
        OnLocked();
    }
    this->mLockCount = this->mLockCount + 1;
    return true;
}

} // os
} // nn