#pragma once

#include "nn/types.h"

namespace nn{
namespace math{

    struct MTX34{ // i would name it Matrix34_f32, but I cant static.crs which sucks but fuck it
    protected:
        float matrix[3][4];
    };

}
}