#pragma once

#include <nn/Result.h>
#include <nn/assert.h>

#define NN_UTIL_RETURN_IF_FAILED_BASE(result, s1, s2, s3, s4, s5) \
    do \
    { \
        ::Result nn_util_return_if_failure_result = (result); \
        if (nn_util_return_if_failure_result.IsFailure()) \
        { \
            s1; s2; s3; s4; s5; \
            return nn_util_return_if_failure_result; \
        } \
    } while(0)

#define NN_UTIL_RETURN_IF_FAILED(result) NN_UTIL_RETURN_IF_FAILED_BASE(result,,,,,)
#define NN_UTIL_PANIC_IF_FAILED(result) NN_PANIC_IF_FAILED(result)