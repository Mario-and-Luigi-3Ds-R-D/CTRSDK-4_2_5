#pragma once

#include "nn/hidlow/hidlow_LifoRing.h"
#include "nn/hidlow/CTR/hidlow_AccelerometerLifoRing.h"

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
    IAccelerometerStatus stick;
    IAccelerometerStatus extraStick;

    IExtraPadStatus();
};

}
}
}