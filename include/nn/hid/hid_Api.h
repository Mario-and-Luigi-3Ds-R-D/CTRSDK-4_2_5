#pragma once

#include "nn/hid/CTR/hid_HidBase.h"

namespace nn{
namespace hid{
namespace CTR{

Result Initialize();
Result Finalize();

Pad* GetPad();
TouchPanel* GetTouchPanel();
Accelerometer* GetAccelerometer();
Gyroscope* GetGyroscope();

extern HidDevices sDevices;

namespace{
    const char* const HID_PORT_USER = "hid:USER";
}

}
}
}