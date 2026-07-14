#pragma once

#include <nn/hidlow/hidlow_LifoRing.h>
#include <nn/hidlow/CTR/hidlow_AnalogStick.h>
#include <nn/hid/CTR/hid_ExtraPadStatus.h>

namespace nn{
namespace hidlow{
namespace CTR{

struct IExtraPadStatus{
    fnd::InterlockedVariable<s32> hold;
    fnd::InterlockedVariable<s32> trigger;
    fnd::InterlockedVariable<s32> release;
    fnd::InterlockedVariable<s8> voltage;
    fnd::InterlockedVariable<s8> isConnected;
    short rev;
    IAnalogStickStatus stick;
    IAnalogStickStatus extraStick;

    IExtraPadStatus();
};

class ExtraPadLifoRing : public LifoRing{
public:
    void ReadData(hid::CTR::ExtraPadStatus* pBuffers, s32 bufferNum,s32 *pReadCount,s64 *pTick,s32 *pIndex);
};

}
}
}