#include <nn/hid/CTR/hid_HidBase.h>


namespace nn{
namespace hid{
namespace CTR{

HidDevices::~HidDevices(){
    this->mSharedMemoryBlock.Finalize();
    if(this->mSharedMemoryBlock.mHandle != 0){
        __asm{swi 0x23}
        this->mSharedMemoryBlock.mHandle = 0;
    }
    if(this->debugPad.mHandle != 0){
        __asm{swi 0x23}
        this->debugPad.mHandle = 0;
    }
    if(this->gyroscope.mHandle != 0){
        __asm{swi 0x23}
        this->gyroscope.mHandle = 0;
    }
    if(this->accelerometer.mHandle != 0){
        __asm{swi 0x23}
        this->accelerometer.mHandle = 0;
    }
    if(this->touchPanel.mHandle != 0){
        __asm{swi 0x23}
        this->touchPanel.mHandle = 0;
    }
    this->pad.Close(); // fix and do this for others.
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