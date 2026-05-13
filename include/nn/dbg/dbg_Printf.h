#include <nn/types.h>
#include <cstdarg>

namespace nn{
namespace dbg{
namespace detail{
    void Printf(const char* fmt, ...);
    void TPrintf(const char* fmt, ...);
    void VPrintf(const char* fmt, ::std::va_list arg);
    void TVPrintf(const char* fmt, ::std::va_list arg);
    void PutString(const char* text, s32 length);
    void PutString(const char* text);
}
}
}