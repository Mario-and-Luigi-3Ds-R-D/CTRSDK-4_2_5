#pragma once

#include "nn/hid/CTR/hid_HidBase.h"
#include "nn/hid/CTR/hid_AnalogStick.h"

namespace nn{
namespace hid{
namespace CTR{

struct ExtraPadStatus{
    AnalogStickStatus stick;
    AnalogStickStatus extraStick;
    bit32 hold;
    bit32 trigger;
    bit32 release;
    u8 batteryLevel;
    bool isConnected;
    short rev;
};

class ExtraPad{
public:
    bool IsSampling();
};

}
}
}