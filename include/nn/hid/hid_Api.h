#pragma once

#include "nn/hid/CTR/hid_HidBase.h"

namespace nn{
namespace hid{
namespace CTR{

Result Initialize();
Result Finalize();

Pad& GetPad();
TouchPanel& GetTouchPanel();
Accelerometer& GetAccelerometer();
Gyroscope& GetGyroscope();

extern HidDevices sDevices;

namespace{
    const char const PORT_NAME_USER[] = "hid:USER";
    const char const PORT_NAME_SERVER[] = "hid:SPVR";
}

}
}
}