// Filename: hid_HidBase.cpp
//
// Project: Horizon 4_2_5 Decompilation
//
// Remade by user Luigifan27

#include <nn/hid/CTR/hid_Api.h>
#include <nn/hid/CTR/hid_IpcClient.h>
#include <nn/srv/srv_Api.h>
#include <string.h>


namespace nn{
namespace hid{
namespace CTR{
    bool isInitialized;

HidDevices::~HidDevices(){
    this->mSharedMemoryBlock.Finalize();
    this->mSharedMemoryBlock.Close();
    this->debugPad.Close();
    this->gyroscope.Close();
    this->accelerometer.Close();
    this->touchPanel.Close();
    this->pad.Close();
}

Result HidDevices::Initialize(const char* portName){

}

void HidDevices::Finalize(){

}

}
}
}