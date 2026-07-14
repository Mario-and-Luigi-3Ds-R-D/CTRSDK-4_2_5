#pragma once

#include <nn/hidlow.h>

namespace nn{
namespace hidlow{
namespace CTR{

class LifoRingCollector{
private:
    PadLifoRing mPadLifoRing;
    TouchPanelLifoRing mTouchPanelLifoRing;
    AccelerometerLifoRing mAccelerometerLifoRing;
    GyroscopeLowLifoRing mGyroscopeLowLifoRing;
    DebugPadLifoRing mDebugPadLifoRing;
public:
    PadLifoRing* GetPadLifoRingAddress(){ return &this->mPadLifoRing; }
    TouchPanelLifoRing* GetTouchPanelLifoRingAddress(){ return &this->mTouchPanelLifoRing; }
    AccelerometerLifoRing* GetAccelerometerLifoRingAddress(){ return &this->mAccelerometerLifoRing; }
    GyroscopeLowLifoRing* GetGyroscopeLowLifoRingAddress(){ return &this->mGyroscopeLowLifoRing; }
    DebugPadLifoRing* GetDebugPadLifoRingAddress(){ return &this->mDebugPadLifoRing; }
};
}
}
}