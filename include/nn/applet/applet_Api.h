#pragma once

#include "nn/applet/applet_Paramaters.h"

// Mostly the detail ones, so yeah.

namespace nn { 
namespace applet {
namespace CTR {
namespace detail{

// all stubs
    void UnlockTransition(u32 action) {}
    void SleepIfShellClosed(){} // stub
    void CallUtility(u32 utilityId, u8* pInParam, size_t inParamSize, u8* pOutParam, size_t outParamSize, s32* pReadSize) {}
}
}
}
}