#pragma once

#include "nn/Handle.h"
#include "nn/Result.h"
#include "nn/math/math_Vec3.h"
#include "nn/os/os_Event.h"
#include "nn/os/os_SharedMemory.h"

namespace nn{
namespace hid{
namespace CTR{

class HidBase : public nn::os::EventBase{
public:
    uptr mResourcePtr;
};

class Pad : public HidBase{
};

class TouchPanel : public HidBase{
};

class Accelerometer : public HidBase{
};

class Gyroscope : public HidBase{
public:
    virtual ~Gyroscope();
};

class DebugPad : public HidBase{
};

class HidDevices{
public:
    Pad pad;
    TouchPanel touchPanel;
    Accelerometer accelerometer;
    Gyroscope gyroscope;
    DebugPad debugPad;
    nn::os::SharedMemoryBlock mSharedMemoryBlock;
    
    void Finalize();
    Result Initialize(const char* portName);
    ~HidDevices();
};

struct Direction{
    math::VEC3 x;
    math::VEC3 y;
    math::VEC3 z;
};

namespace{
    
    bool isInitialized; // 0x0
}

}
}
}