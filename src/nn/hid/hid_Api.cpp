// Filename: hid_Api.cpp
//
// Project: Horizon 4_2_5 Decompilation
//
// Remade by user Luigifan27

#include <nn/hid/hid_Api.h>
#include <nn/dbg/dbg_Break.h>

namespace nn{
namespace hid{
namespace CTR{

static HidDevices sDevices;

Result Finalize(){
    sDevices.Finalize();
}

Result Initialize(){
    sDevices.Initialize(CTR::PORT_NAME_USER);
}

Pad& GetPad(){
    #ifdef NN_DEBUG
        if(isInitialized != false){
            nndbgBreakWithTMessage_(NN_DBG_BREAK_REASON_ASSERT,"hid_Api.cpp",20,"%s","isInitialized");
        }
    #endif

    return sDevices.pad;
}

TouchPanel& GetTouchPanel(){
    #ifdef NN_DEBUG
        if(isInitialized != false){
            nndbgBreakWithTMessage_(NN_DBG_BREAK_REASON_ASSERT,"hid_Api.cpp",30,"%s","isInitialized");
        }
    #endif

    return sDevices.touchPanel;
}

Accelerometer& GetAccelerometer(){
    #ifdef NN_DEBUG
        if(isInitialized != false){
            nndbgBreakWithTMessage_(NN_DBG_BREAK_REASON_ASSERT,"hid_Api.cpp",40,"%s","isInitialized");
        }
    #endif

    return sDevices.accelerometer;
}

Gyroscope& GetGyroscope(){
    // get that 0xb3 chamnged
    #ifdef NN_DEBUG
        if(isInitialized != false){
            nndbgBreakWithTMessage_(NN_DBG_BREAK_REASON_ASSERT,"hid_Api.cpp",51,"%s","isInitialized");
        }
    #endif

    return sDevices.gyroscope;
}

}
}
}