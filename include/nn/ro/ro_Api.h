#pragma once

#include "nn/types.h"
#include "nn/ro/ro_RegistrationList.h"

namespace nn{
namespace ro{
    class SizeInfo{

    };

    class Module{ // Module OFfsets

    };

    struct FixLevel{

    };
    void Initialize(uint);
    void Finalize();
    uint FindModule(const char* pModule);
    uint GetAddress(const char* pAddress);
    void GetSizeInfo(nn::ro::SizeInfo* pSizeInfo,void* pBuffer);
    uint CalculateRequiredBufferSize(void* pBuffer);
    nn::ro::Module* LoadModule(nn::ro::Module* pOffset, int, void*, uint, bool, nn::ro::FixLevel pLevel); // last is const RegistrationList*
}
namespace{
    void* sStatic;
}

}

