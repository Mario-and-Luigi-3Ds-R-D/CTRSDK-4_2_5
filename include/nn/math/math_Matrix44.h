#pragma once

#include "nn/types.h"
#include "nn/math/math_Vec3.h"

namespace nn{
namespace math{

    enum PivotDirection{
        PIVOT_NONE,
        PIVOT_UPSIDE_TO_TOP,
        PIVOT_UPSIDE_TO_RIGHT,
        PIVOT_UPSIDE_TO_BOTTOM,
        PIVOT_UPSIDE_TO_LEFT,
        PIVOT_NUM
    };

class MTX44{
public:
    float matrix[4][4];

    static const int ROW_COUNT = 4; //
    static const int COLUMN_COUNT = 4; //
    MTX44() {}
    MTX44(f32 x00, f32 x01, f32 x02, f32 x03,f32 x10, f32 x11, f32 x12, f32 x13,f32 x20, f32 x21, f32 x22, f32 x23,f32 x30, f32 x31, f32 x32, f32 x33);
    static const MTX44& Identity(){
        static const MTX44 identity(1.0f, 0.0f, 0.0f, 0.0f,0.0f, 1.0f, 0.0f, 0.0f,0.0f, 0.0f, 1.0f, 0.0f,0.0f, 0.0f, 0.0f, 1.0f);
        return identity;
    }
};

}
}