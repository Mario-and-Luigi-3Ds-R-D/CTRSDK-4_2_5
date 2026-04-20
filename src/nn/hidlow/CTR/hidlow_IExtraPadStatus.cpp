#include <nn/hidlow/CTR/hidlow_IExtraPadStatus.h>

namespace nn{
namespace hidlow{
namespace CTR{

IExtraPadStatus::IExtraPadStatus(){
    this->hold  = 0;
    this->trigger  = 0;
    this->release  = 0;
    this->voltage = 0;
    this->isConnected = 0;
    this->stick.x = 0;
    this->stick.y = 0;
    this->extraStick.x = 0;
    this->extraStick.y = 0;
}

}
}
}