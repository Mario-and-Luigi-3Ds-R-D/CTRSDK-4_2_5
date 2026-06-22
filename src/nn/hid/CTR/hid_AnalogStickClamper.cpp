// Filename: hid_AnalogStickClamper.cpp
//
// Project: Horizon 4_2_5 Decompilation
//
// Remade by user Luigifan27

#include <nn/hid/CTR/hid_AnalogStickClamper.h>
#include <nn/hidlow/hidlow_Api.h>

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
        
    this->mThreshold = DEFAULT_THRESHOLD_OF_NORMALIZE_STICK;
    this->mStrokeVelocity = 0.0f;
    this->mLastLength = 0.0f;
    this->mLastDiff = 0.0f;
    this->mScale = DEFAULT_SCALE_OF_NORMALIZE_STICK;
    this->mStroke = 141.0f;
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

f32 AnalogStickClamper::NormalizeStick(short x, short y) {
    if (y > 0x91) y = 0x91;

    if (this->mStickClampMode == STICK_CLAMP_MODE_CIRCLE) {
        if (x < 0x28) x = 0x28;
        this->mMinOfStickClampCircle = x;
        this->mMaxOfStickClampCircle = y;
        return;
    }
    if (this->mStickClampMode != STICK_CLAMP_MODE_CROSS) {
        this->mMaxOfStickClampMinimum = y;
        return;
    }
    if (x < 0x24) x = 0x24;
    this->mMinOfStickClampCross = x;
    this->mMaxOfStickClampCross = y;
}

}
}
}