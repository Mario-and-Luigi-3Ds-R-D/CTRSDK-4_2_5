#pragma once

#include "nn/Result.h"
#include "nn/types.h"
#include "nn/os/ARM/os_Exception.h"

namespace nn{
namespace err{
namespace CTR{

    struct Exception{
        u8 mInfo[24];
        nn::os::ARM::ExceptionContext mExContext;
    };

    struct Failure{
        char mMessage[96];
    };

    union Data{
        nn::err::CTR::Exception mException;
        nn::err::CTR::Failure mFailure;
    };

    struct FatalErrInfo{
        bit8 mType;
        u8 mRevisionHi;
        ushort mRevisionLo;
        Result mResult;
        uptr mPc;
        bit32 mProcessId;
        bit64 mTitleId;
        bit64 mAppTitleId;
        nn::err::CTR::Data mData;
    };

    class FatalErr{
    public:
        Result Throw();
    };
    void ThrowFatalErr(Result pResult);
namespace{
    

    void Throw(nn::err::CTR::FatalErrInfo* pInfo);
} // __annoymous__
} // CTR
} // err
} // nn