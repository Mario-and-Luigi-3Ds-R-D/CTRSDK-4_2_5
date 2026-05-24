#pragma once

#include "nn/types.h"

namespace nn{
namespace drivers{ 
namespace ro{

class RegistrationListHeader{
public:
    u8 rev[0x14];
    void* IsDebugMode;
};

}
}
}