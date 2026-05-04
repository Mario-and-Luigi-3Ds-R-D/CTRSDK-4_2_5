#pragma once

#include <nn/Handle.h>
#include <nn/dbg/dbg_Break.h>

#define NN_POINTER_ASSERT(p)

#define NN_ASSERT_SDK(cond)
#define NN_ASSERT_SDK_MSG(cond, ...)
#define NN_ASSERT_SDK_MIN(var, min)
#define NN_ASSERT_SDK_MAX(var, max)
#define NN_ASSERT_SDK_RESULT(cond, result)

#define NN_PANIC_SDK(...) nndbgPanic();
#define NN_PANIC_IF_FAILED(result)

#define NN_TASSERT_(exp) NN_TASSERTMSG_((exp), "%s", #exp) // DateTime uses this..? 

#define NN_ASSERT_WITH_RESULT(exp, result)
