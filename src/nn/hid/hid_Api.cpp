#include <nn/hid/hid_Api.h>

namespace nn{
namespace hid{
namespace CTR{

static HidDevices sDevices;

Result Finalize(){
    sDevices.Finalize();
}

Result Initialize(){
    sDevices.Initialize(CTR::HID_PORT_USER);
}

Pad* GetPad(){
    return &sDevices.pad;
}

TouchPanel* GetTouchPanel(){
    return &sDevices.touchPanel;
}

Accelerometer* GetAccelerometer(){
    return &sDevices.accelerometer;
}

Gyroscope* GetGyroscope(){
    return &sDevices.gyroscope;
}

}
}
}