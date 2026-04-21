#include <nn/hid/CTR/hid_HidBase.h>


namespace nn{
namespace hid{
namespace CTR{

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
    // TODO
}

void HidDevices::Finalize(){
    // TODO
}

}
}
}