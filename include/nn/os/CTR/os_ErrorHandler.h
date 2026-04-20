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

#define NN_OS_ERROR_IF_FAILED(result)           \
    do                                          \
    {                                           \
        ::Result nn_os_result = (result);   \
        if ( nn_os_result.Failed() )         \
        {                                       \
            ::nn::os::CTR::detail::HandleInternalError(nn_os_result); \
        }                                       \
    } while(0)