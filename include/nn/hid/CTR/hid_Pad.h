#pragma once

#include "nn/hid/CTR/hid_HidBase.h"
#include "nn/hid/CTR/hid_AnalogStick.h"

namespace nn{
namespace hid{
namespace CTR{

struct PadStatus{
    bit32 hold;
    bit32 trigger;
    bit32 release;
    AnalogStickStatus stick;
};

class PadReader{
protected:
    Pad* mPad;
    s32 mIndexOfRead;
    bit32 mLatestHold;
    AnalogStickClamper mStickClamper;
    bool mIsReadLatestFirst;
    s8 rev[3];
    s32 rev2;
    s64 mTickOfRead;
public:
    f32 NormalizeStick(short x, short y);
    PadReader(Pad* pad);
    bool ReadLatest(PadStatus* status);
};

namespace{
    bool sIsEnableSelect;
}

}
}
}