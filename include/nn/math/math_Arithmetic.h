#pragma once

#include "nn/types.h"

#include <cmath>

namespace nn { 
namespace math {
/* Inlines */

inline f32 FAbs(f32 x){
    f32 ret;
    ret = ::std::fabsf(x);
    return ret;
}

/* U16 */

inline u16 F32ToU16(f32 x){
    return u16(x);
}

inline f32 U16ToF32(u16 x){
    return f32(x);
}

}
}