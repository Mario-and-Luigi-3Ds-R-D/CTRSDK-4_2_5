#pragma once

// Rename 2 os_Types.h

#include "nn/types.h"
#include "nn/Result.h"
#include "nn/Handle.h"

namespace nn{
namespace os{

    /* os_Api Funcs */

    void Initialize(void);
    int GetCodeRegionAddress(); // nn::ro uses!
    int GetCodeRegionSize(); // nn::ro uses!
}
}