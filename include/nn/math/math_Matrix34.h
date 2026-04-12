#pragma once

#include "nn/types.h"
#include "nn/math/math_Matrix33.h"
#include "nn/math/math_Vec3.h"

namespace nn{
namespace math{

    struct MTX34{ // i would name it Matrix34_f32, but I cant static.crs which sucks but fuck it
    protected:
        float matrix[3][4];
    };

namespace ARMv6{

    void MTX34CopyAsm(nn::math::MTX34 *,nn::math::MTX34 const*);
    void MTX34MultAsm(nn::math::MTX34 *,nn::math::MTX34 const*,nn::math::MTX34 const*);
    void MTX34MultAsm(nn::math::MTX34 *,nn::math::MTX34 const*,float);
    void MTX34AddAsm(nn::math::MTX34 *,nn::math::MTX34 const*,nn::math::MTX34 const*);
    void MTX34MultScaleAsm(nn::math::MTX34 *,nn::math::MTX34 const*,nn::math::VEC3 const*);
    void MTX34InverseAsm(nn::math::MTX34 *,nn::math::MTX34 const*);
    void MTX34InvTransposeAsm(nn::math::MTX34 *,nn::math::MTX34 const*);
    void MTX34MultTranslateAsm(nn::math::MTX34 *,nn::math::VEC3 const*,nn::math::MTX34 const*);
    void MTX34MultTranslateAsm(nn::math::MTX34 *,nn::math::MTX34 const*,nn::math::VEC3 const*);
    void MTX34TransposeAsm(nn::math::MTX34 *,nn::math::MTX34 const*);
    void MTX34ToMTX33Asm(nn::math::MTX33 *,nn::math::MTX34 const*);

}
}
}