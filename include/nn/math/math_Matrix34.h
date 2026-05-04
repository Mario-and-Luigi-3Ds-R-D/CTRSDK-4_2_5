#pragma once

#include "nn/types.h"

namespace nn{
namespace math{

class MTX34{ // i would name it Matrix34_f32, but I cant static.crs which sucks but fuck it
protected:
    float matrix[3][4];
public:
    static const int ROW_COUNT = 3; //
    static const int COLUMN_COUNT = 4; //
    MTX34() {}
    MTX34(f32 x00, f32 x01, f32 x02, f32 x03,f32 x10, f32 x11, f32 x12, f32 x13,f32 x20, f32 x21, f32 x22, f32 x23);
    static const MTX34& Identity(){
        static const MTX34 identity(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,0.0f, 0.0f, 1.0f, 0.0f);
        return identity;
    }
};

}
}