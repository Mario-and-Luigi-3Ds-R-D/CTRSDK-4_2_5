#pragma once

#include "nn/types.h"
#include "nn/Handle.h"

namespace nn{
namespace os{

    enum ArbitrationType{
        ARBITRATION_TYPE_SIGNAL = 0,
        ARBITRATION_TYPE_WAIT_IF_LESS_THAN = 1,
        ARBITRATION_TYPE_DECREMENT_AND_WAIT_IF_LESS_THAN = 2, // lonh ahh names
        ARBITRATION_TYPE_WAIT_IF_LESS_THAN_WITH_TIMEOUT = 3,
        ARBITRATION_TYPE_DECREMENT_AND_WAIT_IF_LESS_THAN_WITH_TIMEOUT = 4,
        ARBITRATION_TYPE_MAX_BIT = 0x80000000,
    };

    enum ResetType{
        RESET_TYPE_ONESHOT = 0,
        RESET_TYPE_STICKY = 1,
        RESET_TYPE_PULSE = 2,
        RESET_TYPE_MAX_BIT = 0x80000000,
    };

    struct PageInfo{
        bit32 mFlags;
    };

    enum HandleInfoType{
        HANDLE_INFO_TYPE_CREATION_TIME = 0,
        HANDLE_INFO_TYPE_REFERENCE_COUNT = 1,
        HANDLE_INFO_TYPE_PARENT_PROCESS_ID = 2,
        HANDLE_INFO_TYPE_MAX_BIT = 0x80000000,
    };

    enum MemoryState{
        MEMORY_STATE_FREE = 0,
        MEMORY_STATE_RESERVED = 1,
        MEMORY_STATE_IO = 2,
        MEMORY_STATE_STATIC = 3,
        MEMORY_STATE_CODE = 4,
        MEMORY_STATE_PRIVATE = 5,
        MEMORY_STATE_SHARED = 6,
        MEMORY_STATE_CONTINUOUS = 7,
        MEMORY_STATE_ALIASED = 8,
        MEMORY_STATE_ALIAS = 9,
        MEMORY_STATE_ALIAS_CODE = 10,
        MEMORY_STATE_LOCKED = 11,
        MEMORY_STATE_MAX_BITS = 0x80000000,
    };

    enum LimitableResource{
        LIMITABLE_RESOURCE_MAX_PRIORITY = 0,
        LIMITABLE_RESOURCE_MAX_COMMIT = 1,
        LIMITABLE_RESOURCE_MAX_THREAD = 2,
        LIMITABLE_RESOURCE_MAX_EVENT = 3,
        LIMITABLE_RESOURCE_MAX_MUTEX = 4,
        LIMITABLE_RESOURCE_MAX_SEMAPHORE = 5,
        LIMITABLE_RESOURCE_MAX_TIMER = 6, // NOT USED HERE
        LIMITABLE_RESOURCE_MAX_SHAREDMEMORY = 7,
        LIMITABLE_RESOURCE_MAX_ADDRESSARBITER = 8,
        LIMITABLE_RESOURCE_MAX_CPUTIME = 9,
        LIMITABLE_RESOURCE_END = 10,
        LIMITABLE_RESOURCE_MAX_BIT = 0x80000000,
    };

    struct MemoryInfo{
        uptr mBaseAddress;
        size_t mSize;
        bit32 mPermission;
        nn::os::MemoryState mState;
    };

    struct HandleManager{
    };

    struct ValueType{
        s32 mValueType; /* os_Api.h */
    };

    struct Tick{
        s64 mTick;
    };

    struct RtcSwcInfo{
        s64 mBaseMilliSeconds;
        nn::os::Tick mOsTick;
        s64 mTicksPerSecond;
        s64 mDiffMilliSeconds;
    };

    class HandleObj{
    public:
        nn::Handle mHandle;
    };

    class WaitObject : public HandleObj{
    };

    struct NonCopyable{
    };
}
}