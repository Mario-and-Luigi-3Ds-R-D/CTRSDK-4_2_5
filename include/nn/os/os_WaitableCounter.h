#pragma once

#include "nn/types.h"
#include "nn/os/os_Types.h"
#include "nn/fnd/fnd_InterlockedVariable.h"
#include "nn/svc/svc_Api.h"

namespace nn{ 
namespace os{
    class WaitableCounter{
    public:
        typedef fnd::InterlockedVariable<s32> ValueType;
        ValueType mValue;

        static s32 sHandle;
    public:

        static void Initialize();
        ValueType&       operator* () {return mValue; }
        const ValueType& operator* () const { return mValue; }
        ValueType*       operator->() { return &mValue; }

        Result ArbitrateAddress (ArbitrationType type, s32 value){
                return svc::ArbitrateAddress (sHandle, (uptr)&mValue, type, value);
        }
        Result WaitIfLessThan (s32 value){
                return ArbitrateAddress(ARBITRATION_TYPE_WAIT_IF_LESS_THAN, value);
        }
        Result WaitIfLessThanWithTimeout (s32 value){
                return ArbitrateAddress(ARBITRATION_TYPE_WAIT_IF_LESS_THAN_WITH_TIMEOUT, value);
        }
        Result DecrementAndWaitIfLessThan (s32 value){
                return ArbitrateAddress(ARBITRATION_TYPE_DECREMENT_AND_WAIT_IF_LESS_THAN, value);
        }
        Result DecrementAndWaitIfLessThanWithTimeout (s32 value){
                return ArbitrateAddress(ARBITRATION_TYPE_DECREMENT_AND_WAIT_IF_LESS_THAN_WITH_TIMEOUT, value);
        }
        Result Signal (s32 value){
                return ArbitrateAddress(ARBITRATION_TYPE_SIGNAL, value);
        }
        Result SignalAll (){
                return Signal (-1);
        }
    };
}
}