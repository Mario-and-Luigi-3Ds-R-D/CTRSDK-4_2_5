#pragma once

#include "nn/types.h"

namespace nn{
namespace math{

    void SinCosFIdx(f32* pSin, f32* pCos, f32 fidx);
    f32 SinFIdx(f32 fidx);
    f32 CosFIdx(f32 fidx);
    f32 AtanFIdx(f32 x);
    ushort Atan2Idx(f32 y, f32 x);
    ushort Atan2FIdx(f32 y, f32 x);
    
}
}