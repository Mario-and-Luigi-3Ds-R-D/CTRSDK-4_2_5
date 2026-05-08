#include <nn/os/os_ThreadLocal.h>
#include <nn/os/os_Thread.h>
#include <nn/os/CTR/os_CppException.h>
#include <rt_fp.h>

extern "C" void _fp_init();

namespace nn{
namespace os{
namespace detail{
void InitializeThreadEnvrionment(){
    Result clear = nn::os::ThreadLocalStorage::ClearAllSlots();
    os::CTR::SetupThreadCppExceptionEnvironment();
    _fp_init();
}

}

ThreadLocalStorage::~ThreadLocalStorage(){
    uint mutex = this->mIndex;
    if(mutex < 0x10){
        if((sTLSMap >> (mutex & 0xff) & 1) != 0){
            sTLSMap = sTLSMap & ~(ushort)(1 << (mutex & 0xff));
        }
    }
}

// Clears the thread before start.

__asm Result ThreadLocalStorage::ClearAllSlots(){
    MRC             p15, 0, R0,c13,c0, 3
    MOV             R1, #0
    STR             R1, [R0]
    STR             R1, [R0,#4]
    STR             R1, [R0,#8]
    STR             R1, [R0,#0xC]
    STR             R1, [R0,#0x10]
    STR             R1, [R0,#0x14]
    STR             R1, [R0,#0x18]
    STR             R1, [R0,#0x1C]
    STR             R1, [R0,#0x20]
    STR             R1, [R0,#0x24]
    STR             R1, [R0,#0x28]
    STR             R1, [R0,#0x2C]
    STR             R1, [R0,#0x30]
    STR             R1, [R0,#0x34]
    STR             R1, [R0,#0x38]
    STR             R1, [R0,#0x3C]
    BX              LR
}

}
}