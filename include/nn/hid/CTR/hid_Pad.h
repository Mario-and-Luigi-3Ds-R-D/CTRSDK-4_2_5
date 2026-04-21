#pragma once

#include "nn/hid/CTR/hid_HidBase.h"
#include "nn/hid/hid_Api.h"
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
typedef enum{
    STICK_CLAMP_MODE_CIRCLE = AnalogStickClamper::STICK_CLAMP_MODE_CIRCLE,
    STICK_CLAMP_MODE_CROSS = AnalogStickClamper::STICK_CLAMP_MODE_CROSS,
    STICK_CLAMP_MODE_MINIMUM = AnalogStickClamper::STICK_CLAMP_MODE_MINIMUM
} StickClampMode;

f32 NormalizeStick(short x, short y);
PadReader(Pad* pad = CTR::GetPad());
bool ReadLatest(PadStatus* status);

inline void SetStickClampMode(StickClampMode mode){
    this->mStickClamper.SetStickClampMode(ClamperClampMode(mode));
}

private:
    static AnalogStickClamper::ClampMode  ClamperClampMode(const StickClampMode mode);
    static StickClampMode ReaderClampMode(const AnalogStickClamper::ClampMode mode);
};

namespace{
    bool sIsEnableSelect;
}

}
}
}