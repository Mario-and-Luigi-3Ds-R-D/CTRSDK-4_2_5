#pragma once

#include "nn/types.h"
#include "nn/util/util_NonCopyable.h"
#include "nn/util/detail/util_ScopeLockImpl.h"
#include "nn/os/os_SimpleLock.h"
#include "nn/os/os_Types.h"

#define HW_INST_MRC(a,b,c,d,e,v)    __asm { mrc a,b,v,c,d,e }
#define HW_GET_CP15_THREAD_ID_USER_READ_ONLY(v) HW_INST_MRC(p15,0,c13,c0,3,v)

namespace nn { 
namespace os {
    class CriticalSection : private nn::util::NonCopyable<CriticalSection>{
    public:
        SimpleLock mLock;
        u32 mThreadUniqueValue;
        s32 mLockCount;

        void Initialize(void);
        void Enter(void);
        void Leave(void);
        bool TryEnter(void);
        ~CriticalSection() { }
        class ScopedLock;

        static uptr GetThreadUniqueValue(){
            uptr v;
            HW_GET_CP15_THREAD_ID_USER_READ_ONLY(v);
            return v;
        }
        void OnLocked(){
            this->mThreadUniqueValue = GetThreadUniqueValue();
        }
        bool LockedByCurrentThread() const{
            return GetThreadUniqueValue() == mThreadUniqueValue;
        }
    };
    
    NN_UTIL_DETAIL_DEFINE_SCOPED_LOCK(CriticalSection, Enter(), Leave());
}
};