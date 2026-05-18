// Filename: os_CriticalSection.cpp
//
// Project: Horizon 4_2_5 Decompilation
//
// Remade by user Luigifan27

#include <nn/os/os_CriticalSection.h>
#include <nn/dbg/dbg_Break.h>

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
    #ifdef NN_DEBUG
        if(this->mLockCount < 0){
            nndbgBreakWithTMessage_(NN_DBG_BREAK_REASON_ASSERT,"os_CriticalSection.cpp",23,"%s","this->mLockCount < 0");
        }
    #endif
    if(!this->LockedByCurrentThread()){
        this->mLock.Lock();
        #ifdef NN_DEBUG
            if(this->mLockCount == 0){
                nndbgBreakWithTMessage_(NN_DBG_BREAK_REASON_ASSERT,"os_CriticalSection.cpp",31,"%s","this->mLockCount == 0");
            }
        #endif
        this->OnLocked();
    }
    this->mLockCount += 1;
}

// Leaves Thread CriticalSection

void CriticalSection::Leave() {
    s32 pCount;
    #ifdef NN_DEBUG
        if(this->mLockCount < 0){
            nndbgBreakWithTMessage_(NN_DBG_BREAK_REASON_ASSERT,"os_CriticalSection.cpp",45,"%s","this->mLockCount < 0");
        }
    #endif
    pCount = this->mLockCount - 1;
    this->mLockCount = pCount;
    if (pCount == 0) {
        this->mThreadUniqueValue = 0;
        this->mLock.nn::os::SimpleLock::Unlock();
    }
}

// Trys to enter Thread CriticalSection, if cant TryLock. If so, add to the count and proceed.

bool CriticalSection::TryEnter(void) {
    #ifdef NN_DEBUG
        if(this->mLockCount < 0){
            nndbgBreakWithTMessage_(NN_DBG_BREAK_REASON_ASSERT,"os_CriticalSection.cpp",61,"%s","this->mLockCount < 0");
        }
    #endif

    if(!this->LockedByCurrentThread() ){
        if(!this->mLock.TryLock() ){
            return false;
        }
        #ifdef NN_DEBUG
            if(this->mLockCount == 0){
                nndbgBreakWithTMessage_(NN_DBG_BREAK_REASON_ASSERT,"os_CriticalSection.cpp",71,"%s","this->mLockCount == 0");
            }
        #endif
        OnLocked();
    }
    this->mLockCount = this->mLockCount + 1;
    return true;
}

} // os
} // nn