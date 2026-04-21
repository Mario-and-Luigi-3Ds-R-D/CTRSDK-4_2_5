#pragma once

#include "nn/applet/CTR/applet_Paramaters.h"

namespace nn{
namespace applet{ 
namespace CTR { 
namespace detail {
namespace {
    //u8* sInitializeParamBuffer[4096];
    extern bool sIsInitializedParamVaild;
    extern u8 sInitialWakeupState;
    extern short rev;
    extern int sSenderId;
    extern int sInitialSize;
}
namespace {
    extern u8* sInitializeParamBuffer[4096];
}
    u8* GetInitialParamBuffer();
    void SetInitialParamSenderId(AppletId id);
    void SetInitialParamSenderSize(s32 size);
    void SetInitialParamValid();
    void SetInitialWakeupState(WakeupState state);

}
}
}
}