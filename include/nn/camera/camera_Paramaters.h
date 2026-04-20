#pragma once

#include "nn/types.h"
#include "nn/Handle.h"
#include "nn/Result.h"

namespace nn{
namespace camera{
namespace CTR{
namespace detail{
    enum CameraSelect {
        SELECT_NONE=0,
        SELECT_OUT1=1,
        SELECT_IN1=2,
        SELECT_IN1_OUT1=3,
        SELECT_OUT2=4,
        SELECT_OUT1_OUT2=5,
        SELECT_IN1_OUT2=6,
        SELECT_ALL=7
    };

}
}
}
}