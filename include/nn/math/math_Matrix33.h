#pragma once

#include "nn/types.h"

#pragma push
#pragma Otime

namespace nn{
namespace math{

class MTX33{
protected:
    float matrix[3][3];
public:
    MTX33() {}
    MTX33(f32 x00, f32 x01, f32 x02,f32 x10, f32 x11, f32 x12,f32 x20, f32 x21, f32 x22){ }
    static const int ROW_COUNT = 3;
    static const int COLUMN_COUNT = 3;
    
    static const MTX33& Identity(){
        static const MTX33 identity(1.0f, 0.0f, 0.0f,0.0f, 1.0f, 0.0f,0.0f, 0.0f, 1.0f);
        return identity;
    }
};

}
}