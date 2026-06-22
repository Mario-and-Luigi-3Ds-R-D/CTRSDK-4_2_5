// Filename: hid_Api.cpp
//
// Project: Horizon 4_2_5 Decompilation
//
// Remade by user Luigifan27

#include <nn/hid/CTR/hid_Api.h>
#include <nn/Assert.h>

namespace nn{
namespace hid{
namespace CTR{

static HidDevices sDevices;

void Finalize(){
    sDevices.Finalize();
}

Result Initialize(){
    sDevices.Initialize(CTR::PORT_NAME_USER);
}

Pad& GetPad(){
    NN_TASSERT_(isInitialized);

    return sDevices.pad;
}

DebugPad& GetDebugPad(){
    NN_TASSERT_(isInitialized);

    return sDevices.debugPad;
}

TouchPanel& GetTouchPanel(){
    NN_TASSERT_(isInitialized);

    return sDevices.touchPanel;
}

Accelerometer& GetAccelerometer(){
    NN_TASSERT_(isInitialized);

    return sDevices.accelerometer;
}

Gyroscope& GetGyroscope(){
    NN_TASSERT_(isInitialized);

    return sDevices.gyroscope;
}

}
}
}