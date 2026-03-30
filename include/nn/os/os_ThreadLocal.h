#pragma once

#include "nn/types.h"

namespace nn{
namespace os{
namespace CTR{

    class ThreadLocalRegion{
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

    class ThreadLocalStorage{
    public:
        int mIndex;

        void ClearAllSlots(void);
        ~ThreadLocalStorage();
    };

}
}