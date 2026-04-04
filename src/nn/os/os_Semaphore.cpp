#include <nn/os/os_Semaphore.h>

namespace nn{
namespace os{

Semaphore::~Semaphore(){
    if (this->mHandle != 0) {
        __asm{swi 0x23}
        this->mHandle = 0;
    }
}

}
}