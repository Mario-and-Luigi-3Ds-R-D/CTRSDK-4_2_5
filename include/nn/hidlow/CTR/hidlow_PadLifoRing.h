#pragma once

#include "nn/hidlow/hidlow_LifoRing.h"
#include "nn/hidlow/CTR/hidlow_AccelerometerLifoRing.h"
#include "nn/hidlow/CTR/hidlow_AnalogStick.h"
#include "nn/hid/CTR/hid_Pad.h"

namespace nn{
namespace hidlow{
namespace CTR{

struct IPadStatus{
    fnd::InterlockedVariable<s32> hold;
    fnd::InterlockedVariable<s32> trigger;
    fnd::InterlockedVariable<s32> release;
    IAccelerometerStatus stick;
};

class PadLifoRing : public hidlow::LifoRing{
public:
    f32 mSvr2Volume;
    bit32 mRawButtons;
    IAnalogStickStatus mRawAnalogStick;
    s32 rev;
    IPadStatus mBuffers[8];

    void ReadData(hid::CTR::PadStatus *status,s32 bufferNum,s32 *pReadCount,s64 *pTick,s32 *pIndex);
};

}
}
}