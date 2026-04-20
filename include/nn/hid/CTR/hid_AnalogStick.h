#pragma once

#include "nn/hid/CTR/hid_HidBase.h"

namespace nn{
namespace hid{
namespace CTR{

struct AnalogStickStatus{
    short x;
    short y;
};

class AnalogStickClamper{
protected:
    short mMinOfStickClampCircle;
    short mMinOfStickClampCross;
    short mMinOfStickClampMinimum;
    short mMaxOfStickClampCircle;
    short mMaxOfStickClampCross;
    short mMaxOfStickClampMinimum;
    s8 mStickClampMode;
    s8 rev;
    short mThreshold;
    f32 mScale;
    f32 mStroke;
    f32 mStrokeVelocity;
    f32 mLastLength;
    f32 mLastDiff;
public:

AnalogStickClamper();
void ClampCore(short* pOutX, short* pOutY,  s32 x, s32 y);
void ClampValueOfClamp();
f32 NormalizeStick(short x, short y);

};
}
}
}