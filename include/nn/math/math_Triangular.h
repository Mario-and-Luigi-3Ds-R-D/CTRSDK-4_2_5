#pragma once

#include "nn/math/math_Arithmetic.h"

namespace nn{
namespace math{
namespace internal{
struct SinCosSample{
    f32 sin_val;
    f32 cos_val;
    f32 sin_delta;
    f32 cos_delta;
};

}

    void SinCosFIdx(f32* pSin, f32* pCos, f32 fidx);
    f32 SinFIdx(f32 fidx);
    f32 CosFIdx(f32 fidx);
    f32 AtanFIdx(f32 x);
    ushort Atan2Idx(f32 y, f32 x);
    f32 Atan2FIdx(f32 y, f32 x);
    
}
}