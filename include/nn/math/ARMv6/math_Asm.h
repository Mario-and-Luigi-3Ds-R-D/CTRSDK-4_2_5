#pragma once

#include "nn/math/math_Matrix33.h"
#include "nn/math/math_Matrix34.h"
#include "nn/math/math_Matrix44.h"
#include "nn/math/math_Vec3.h"

namespace nn{
namespace math{
namespace ARMv6{

    void VEC3TransformAsm(nn::math::VEC3*, nn::math::MTX33 const*, nn::math::VEC3 const*);
    void VEC3TransformAsm(nn::math::VEC3*, nn::math::MTX34 const*, nn::math::VEC3 const*);

    void MTX34CopyAsm(nn::math::MTX34 *,nn::math::MTX34 const*);
    void MTX34MultAsm(nn::math::MTX34 *,nn::math::MTX34 const*,math::MTX34 const*);
    void MTX34MultAsm(nn::math::MTX34 *,nn::math::MTX34 const*,float);
    void MTX34AddAsm(nn::math::MTX34 *,nn::math::MTX34 const*,nn::math::MTX34 const*);
    void MTX34MultScaleAsm(nn::math::MTX34 *,nn::math::MTX34 const*,nn::math::VEC3 const*);
    void MTX34InverseAsm(nn::math::MTX34 *,nn::math::MTX34 const*);
    void MTX34InvTransposeAsm(nn::math::MTX34 *,nn::math::MTX34 const*);
    void MTX34MultTranslateAsm(nn::math::MTX34 *,nn::math::VEC3 const*,nn::math::MTX34 const*);
    void MTX34MultTranslateAsm(nn::math::MTX34 *,nn::math::MTX34 const*,nn::math::VEC3 const*);
    void MTX34TransposeAsm(nn::math::MTX34 *,nn::math::MTX34 const*);
    void MTX34ToMTX33Asm(nn::math::MTX33 *,nn::math::MTX34 const*);

    
    void MTX44CopyAsm(nn::math::MTX44 *,nn::math::MTX44 const*);
    void MTX44MultAsm(nn::math::MTX44 *,nn::math::MTX44 const*,nn::math::MTX44 const*);
    void MTX44MultScaleAsm(nn::math::MTX44 *,nn::math::MTX44 const*,nn::math::VEC3 const*);
    void MTX44MultTranslateAsm(nn::math::MTX44 *,nn::math::VEC3 const*,nn::math::MTX44 const*);

}
}
}