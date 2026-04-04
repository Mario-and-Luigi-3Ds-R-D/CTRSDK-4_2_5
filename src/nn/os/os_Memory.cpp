#include "nn/os/os_Memory.h"

namespace nn{
namespace os{

uptr GetMemoryAddress(){
    return sDeviceMemoryAddress;
}

uptr GetAppMemorySize(){
    return sDeviceMemorySize;
}

size_t GetDeviceMemorySize(){
    return sDeviceMemorySize;
}

Result SetDeviceMemorySize(size_t pSize){

}

void SetupHeapForMemoryBlock(){
    
}

size_t GetHeapSoze(){
    return sDeviceHeapSize;
}

int GetCodeRegionAddress(){
    return 0x10000;
}

int GetCodeRegionSize(){
    return 0x53cb98;
}

}
}