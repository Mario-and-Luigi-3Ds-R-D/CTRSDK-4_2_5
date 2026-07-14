#include "nn/Result.h"
#include "nn/types.h"
#include <cstdarg>

namespace nn{
namespace dbg{
namespace detail{
    void Printf(const char* fmt, ...);
    void TPrintf(const char* fmt, ...);
    void VPrintf(const char* fmt, ::std::va_list arg);
    void TVPrintf(const char* fmt, ::std::va_list arg);
    void PrintResult(Result res);
    void PutString(const char* text, s32 length);
    void PutString(const char* text);
}
}
}

extern "C"{
    void nndbgPrintWarning_ (const char* filename, int lineno, const char* fmt, ...);
    void nndbgTPrintWarning_(const char* filename, int lineno, const char* fmt, ...);
}

#ifdef NN_DEBUG

#define NN_SLOG_(exp, ...) (void)nn::dbg::detail::Printf(exp, __VA_ARGS__)
#define NN_TLOG_(exp, ...) (void)nn::dbg::detail::TPrintf(exp, __VA_ARGS__)

#else

#define NN_SLOG_(exp, ...)
#define NN_TLOG_(exp, ...)

#endif