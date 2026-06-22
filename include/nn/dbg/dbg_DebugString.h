#include "nn/Result.h"
#include "nn/types.h"
#include <cstdarg>

#ifdef NN_DEBUG

#define NN_SLOG_( ... ) (void)nn::dbg::detail::Printf(__VA_ARGS__)
#define NN_TLOG_( ... ) (void)nn::dbg::detail::TPrintf(__VA_ARGS__)

#else

#define NN_SLOG_(void)
#define NN_TLOG_(void)

#endif

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

