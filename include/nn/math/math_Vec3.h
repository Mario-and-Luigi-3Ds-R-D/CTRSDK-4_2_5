#pragma once

//#include "nn/math/math_Matrix33.h"
#include "nn/math/math_Matrix34.h"

namespace nn {
namespace math {
    
    struct VEC3{
        float x;
        float y;
        float z;
    };
/*namespace ARMv6{
    VEC3TransformAsm(nn::math::VEC3*, nn::math::MTX33 const*, nn::math::VEC3 const*);
    VEC3TransformAsm(nn::math::VEC3*, nn::math::MTX34 const*, nn::math::VEC3 const*);
}*/

}
}