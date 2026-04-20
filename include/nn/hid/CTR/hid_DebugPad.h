#pragma once

#include "nn/hid/CTR/hid_HidBase.h"

namespace nn{
namespace hid{
namespace CTR{

class DebugPadReader{
public:
    DebugPad* mDebugPad;
    s32 mIndexOfRead;
    bit16 mLatestHold;
    bool mIsReadLatestFirst;
    s8 mStickClampMode;
    s32 rev;
    s64 mTickOfRead;
};

}
}
}