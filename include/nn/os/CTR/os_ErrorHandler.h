#pragma once

#include "nn/types.h"
#include "nn/Result.h"

namespace nn{
namespace os{
namespace CTR{
namespace detail{


    void SetInternalErrorHandlingMode(bool preferFatal);
    void HandleInternalError(Result result);


namespace{
    u8 sPreferFatal;
} // _annoymous_
} // detail
} // CTR
} // os
} // nn