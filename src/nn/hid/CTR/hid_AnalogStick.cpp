#include <nn/hid/CTR/hid_AnalogStick.h>
#include <nn/hidlow/hidlow_Api.h>

namespace nn{
namespace hid{
namespace CTR{

// nonmatch but does the exact same thing
AnalogStickClamper::AnalogStickClamper(){
    this->mMinOfStickClampCircle = 0x28;
    this->mMinOfStickClampCross = 0x24;
    this->mMinOfStickClampMinimum = 0x28;
    this->mMaxOfStickClampCircle = 0x91;
    this->mMaxOfStickClampCross = 0x91;
    this->mMaxOfStickClampMinimum = 0x91;
    this->mStickClampMode = 0;
    this->mThreshold = 0x8d;
    this->mStrokeVelocity = 0.0;
    this->mLastLength = 0.0;
    this->mLastDiff = 0.0;
    this->mScale = 1.5;
    this->mStroke = 141.0;
}

void AnalogStickClamper::ClampCore(short* pOutX, short* pOutY, s32 x, s32 y){
    bit8 clampMode = this->mStickClampMode;

    if(clampMode == 0){
        hidlow::ClampStickCircle(pOutX,pOutY,x,y,this->mMinOfStickClampCircle,this->mMaxOfStickClampCircle);
        return;
    }

    if(clampMode != 1){
        if(clampMode == 2){
            hidlow::ClampStickMinimum(pOutX,pOutY,x,y,this->mMinOfStickClampMinimum, this->mMaxOfStickClampMinimum);
        }
        return;
    }
    hidlow::ClampStickCross(pOutX,pOutY,x,y,this->mMinOfStickClampCross,this->mMaxOfStickClampCross);
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
    bit8 clampMode = this->mStickClampMode;

    if (y > 0x91) y = 0x91;

    if (clampMode == 0) {
        if (x < 0x28) x = 0x28;
        this->mMinOfStickClampCircle = x;
        this->mMaxOfStickClampCircle = y;
        return;
    }
    if (clampMode != 1) {
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