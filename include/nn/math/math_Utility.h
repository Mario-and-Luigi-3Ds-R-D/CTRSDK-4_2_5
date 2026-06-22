#pragma once

#include "nn/types.h"

namespace nn { 
namespace math {

template <typename T, typename U, typename S>
inline S Max(T a, U b){
    return (a >= b) ? a: b;
}

template <typename T>
inline T Max(T a, T b){
    return (a >= b) ? a: b;
}

template <typename T, typename U, typename S>
inline S Min(T a, U b){
    return (a <= b) ? a: b;
}

template <typename T>
inline T Min(T a, T b){
    return (a <= b) ? a: b;
}



template <typename T>
inline T RoundUp(T x, u32 base){
    return static_cast<T>( (x + (base - 1)) & ~(base - 1) );
}

}
}