#pragma once

#include "nn/math/math_Vec3.h"

namespace nn{
namespace math{

    struct MTX44{
    protected:
        float matrix[4][4];
    };

namespace ARMv6{

    void MTX44CopyAsm(nn::math::MTX44 *,nn::math::MTX44 const*);
    void MTX44MultAsm(nn::math::MTX44 *,nn::math::MTX44 const*,nn::math::MTX44 const*);
    void MTX44MultScaleAsm(nn::math::MTX44 *,nn::math::MTX44 const*,nn::math::VEC3 const*);
    void MTX44MultTranslateAsm(nn::math::MTX44 *,nn::math::VEC3 const*,nn::math::MTX44 const*);
    
}
}
}