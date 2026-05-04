#pragma once

#include "nn/hid/CTR/hid_HidBase.h"

namespace nn{
namespace hid{
namespace CTR{

const f32 DEFAULT_SCALE_OF_NORMALIZE_STICK = 1.5f;
const s16 DEFAULT_THRESHOLD_OF_NORMALIZE_STICK = 141;
const s16 MIN_OF_STICK_CLAMP_MODE_CIRCLE = 40;
const s16 MIN_OF_STICK_CLAMP_MODE_CROSS = 36;
const s16 LIMIT_OF_STICK_CLAMP_MAX = 145;

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

enum ClampMode{
    STICK_CLAMP_MODE_CIRCLE = 0,
    STICK_CLAMP_MODE_CROSS,
    STICK_CLAMP_MODE_MINIMUM
};

AnalogStickClamper();
void ClampCore(short* pOutX, short* pOutY,  s32 x, s32 y);
void ClampValueOfClamp();
f32 NormalizeStick(short x, short y);

inline void SetStickClampMode(ClampMode mode){
    this->mStickClampMode = mode;
}

};
}
}
}