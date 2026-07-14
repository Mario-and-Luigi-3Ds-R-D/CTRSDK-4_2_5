// Filename: hid_AnalogStickClamper.cpp
//
// Project: Horizon 4_2_5 Decompilation
//
// Remade by user Luigifan27

#include <nn/hid/CTR/hid_AnalogStickClamper.h>
#include <nn/hidlow/hidlow_Utils.h>
#include <nn/math.h>

namespace nn{
namespace hid{
namespace CTR{

AnalogStickClamper::AnalogStickClamper() : 
    mMinOfStickClampCircle(MIN_OF_STICK_CLAMP_MODE_CIRCLE),
    mMinOfStickClampCross(MIN_OF_STICK_CLAMP_MODE_CROSS),
    mMinOfStickClampMinimum(MIN_OF_STICK_CLAMP_MODE_CIRCLE),
    mMaxOfStickClampCircle(LIMIT_OF_STICK_CLAMP_MAX),
    mMaxOfStickClampCross(LIMIT_OF_STICK_CLAMP_MAX),
    mMaxOfStickClampMinimum(LIMIT_OF_STICK_CLAMP_MAX),
    mStickClampMode(STICK_CLAMP_MODE_CIRCLE){
        
    mThreshold = DEFAULT_THRESHOLD_OF_NORMALIZE_STICK;
    mStrokeVelocity = 0.0f;
    mLastLength = 0.0f;
    mLastDiff = 0.0f;
    mScale = DEFAULT_SCALE_OF_NORMALIZE_STICK;
    mStroke = 141.0f;
}

void AnalogStickClamper::SetStickClampFree(s16 min, s16 max){
    if(this->mStickClampMode == STICK_CLAMP_MODE_CIRCLE){
        this->mMinOfStickClampCircle = min;
        this->mMaxOfStickClampCircle = max;
    }

    else if(this->mStickClampMode == STICK_CLAMP_MODE_CROSS){
        this->mMinOfStickClampCross = min;
        this->mMaxOfStickClampCross = max;
    }

    else{
        this->mMaxOfStickClampMinimum = max;
        this->mMinOfStickClampMinimum = min;
    }
}

void AnalogStickClamper::SetNormalizeStickScaleSettings(f32 scale, s16 threshold){
    if(LIMIT_OF_STICK_CLAMP_MAX < threshold) threshold = LIMIT_OF_STICK_CLAMP_MAX;
    mScale = scale;
    mThreshold = threshold;
}

void AnalogStickClamper::ClampCore(short* pOutX, short* pOutY, s32 x, s32 y){
    switch (this->mStickClampMode) {
    case STICK_CLAMP_MODE_CIRCLE:
        hidlow::ClampStickCircle(pOutX, pOutY, x, y, this->mMinOfStickClampCircle, this->mMaxOfStickClampCircle);
        break;
    case STICK_CLAMP_MODE_CROSS:
        hidlow::ClampStickCross(pOutX, pOutY, x, y, this->mMinOfStickClampCross, this->mMaxOfStickClampCross);
        break;
    case STICK_CLAMP_MODE_MINIMUM:
        hidlow::ClampStickMinimum(pOutX, pOutY, x, y, this->mMinOfStickClampMinimum, this->mMaxOfStickClampMinimum);
        break;
    }
}

void AnalogStickClamper::ClampValueOfClamp() {
  if (this->mMinOfStickClampCircle < 40)
    this->mMinOfStickClampCircle = 40;
    
  if (this->mMinOfStickClampCross < 36)
    this->mMinOfStickClampCross = 36;
    
  if (this->mMaxOfStickClampCircle > 145)
    this->mMaxOfStickClampCircle = 145;
    
  if (this->mMaxOfStickClampCross > 145)
    this->mMaxOfStickClampCross = 145;
    
  if (this->mMaxOfStickClampMinimum > 145)
    this->mMaxOfStickClampMinimum = 145;
}

f32 AnalogStickClamper::NormalizeStick(s16 x){
    f32 fx = (f32)x;
    s16 threshold;

    switch (mStickClampMode){
    case STICK_CLAMP_MODE_CIRCLE:
        threshold = mMaxOfStickClampCircle - mMinOfStickClampCircle;
        break;

    case STICK_CLAMP_MODE_CROSS:
        threshold = mMaxOfStickClampCross - mMinOfStickClampCross;
        break;

    case STICK_CLAMP_MODE_MINIMUM:
        threshold = 0x69;
        break;
    }

    if (0 == x)
        return 0.0f;
    else if(threshold <= x)
        return 1.0f;

    return fx / threshold;
}


void AnalogStickClamper::SetStickClamp(short min, short max) {
    NN_TASSERT_(0 <= min);
    NN_TASSERT_(min < max);
    if (max > LIMIT_OF_STICK_CLAMP_MAX) max = LIMIT_OF_STICK_CLAMP_MAX;

    if (this->mStickClampMode == STICK_CLAMP_MODE_CIRCLE) {
        if (min < MIN_OF_STICK_CLAMP_MODE_CIRCLE) min = MIN_OF_STICK_CLAMP_MODE_CIRCLE;
        this->mMinOfStickClampCircle = min;
        this->mMaxOfStickClampCircle = max;
        return;
    }
    
    if (this->mStickClampMode != STICK_CLAMP_MODE_CROSS) {
        this->mMaxOfStickClampMinimum = max;
        return;
    }

    if (min < MIN_OF_STICK_CLAMP_MODE_CIRCLE) min = MIN_OF_STICK_CLAMP_MODE_CIRCLE;
    this->mMinOfStickClampCross = min;
    this->mMaxOfStickClampCross = max;
}

}
}
}