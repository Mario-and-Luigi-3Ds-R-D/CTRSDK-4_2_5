// Filename: os_CriticalSection.cpp
//
// Project: Horizon 4_2_5 Decompilation
//
// Remade by user Luigifan27

#include <nn/os/os_CriticalSection.h>
#include <nn/dbg/dbg_Break.h>
#include <nn/Assert.h>

namespace nn{
namespace os{
// Initializes Thread CriticalSection

void CriticalSection::Initialize() {
    this->mLock.Initialize();
    this->mThreadUniqueValue = this->GetInvalidThreadUniqueValue();
    this->mLockCount = 0;
}

// Enters Thread CriticalSection

void CriticalSection::Enter(void) {
    NN_TASSERT_(this->IsInitialized());
    if(!this->LockedByCurrentThread()){
        this->mLock.Lock();
        this->OnLocked();
    }
    this->mLockCount++;
}

// Leaves Thread CriticalSection

void CriticalSection::Leave() {
    NN_TASSERT_(this->IsInitialized());
    NN_TASSERTMSG_(LockedByCurrentThread() && this->mLockCount > 0, "CriticalSection is not entered on the current thread.");
    if (--this->mLockCount == 0) {
        NN_TASSERTMSG_(this->mLock.IsLocked(), "CriticalSection is not entered.");
        this->mThreadUniqueValue = 0;
        this->mLock.nn::os::SimpleLock::Unlock();
    }
}

// Trys to enter Thread CriticalSection, if cant TryLock. If so, add to the count and proceed.

bool CriticalSection::TryEnter(void) {
    NN_TASSERT_(this->IsInitialized());
    if(!this->LockedByCurrentThread() ){
        if(!this->mLock.TryLock() ){
            return false;
        }
        OnLocked();
    }
    this->mLockCount++;
    return true;
}

} // os
} // nn