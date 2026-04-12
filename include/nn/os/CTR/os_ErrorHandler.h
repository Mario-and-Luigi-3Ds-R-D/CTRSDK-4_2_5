#pragma once

#include "nn/types.h"
#include "nn/Result.h"

namespace nn{
namespace os{
namespace CTR{
namespace detail{


    void SetInternalErrorHandlingMode(bool preferFatal);
    void HandleInternalError(Result result);

    static s8 sPreferFatal;

} // detail
} // CTR
} // os
} // nn