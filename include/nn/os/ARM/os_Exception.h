#pragma once

#include "nn/types.h"

namespace nn{
namespace os{

class ARM{
    void SpinWaiyCpuCycles();
    void SetUserExceptionHandler(); // userexceptionhandler pHandler, uptr pStackBottom

    struct ExceptionBuffer{
    };

    struct ExceptionContext{
        bit32 mResult[16];
        bit32 mCpsr;
    };

    struct ExceptionInfo{
        s8 mType;
        s8 unk[3];
        bit32 fsr;
        bit32 far;
        bit32 fpexc;
        bit32 fpinst;
        bit32 fpinst2;
    };

    enum ExceptionType{
        TYPE_PABT = 0,
        TYPE_DABT = 1,
        TYPE_UNDEF = 2,
        TYPE_VFP = 3,
        TYPE_MAX_BIT = 80,
    };

}; // class ARM
}
}