#pragma once

#include "nn/types.h"
#include "nn/Result.h"

namespace nn{
namespace os{
namespace CTR{
    struct ThreadLocalRegion{
        uptr mTls[16];
        uptr mHandlerAddress;
        uptr mHandlerStackBottomAddress;
        uptr mExceptionBufferAddress;
        bit8 mPad1[16];
        void* mEhGlobalsAddr;
        bit32 mEhGlobals[8];
        bit32 mMessageBuffer[64];
        bit32 mReceiveBuffer[32];
    };
}; // CTR
namespace detail{
    void InitializeThreadEnvrionment();
}

    class ThreadLocalStorage{
    public:
        int mIndex;

        static Result ClearAllSlots();
        ~ThreadLocalStorage();
        void Thread();
    };

namespace{
    short sTLSMap;
}
}
}