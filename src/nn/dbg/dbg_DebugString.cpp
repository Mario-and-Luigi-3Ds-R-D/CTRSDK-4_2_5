#include <nn/dbg/dbg_DebugString.h>

extern "C"{
    void nndbgPrintWarning_ (const char* filename, int lineno, const char* fmt, ...){
        va_list vlist;

        va_start(vlist, fmt);
        nn::dbg::detail::TPrintf("%s:%d [WARN] ", filename, lineno);
        nn::dbg::detail::VPrintf(fmt, vlist);
        nn::dbg::detail::TPrintf("\n");
        va_end(vlist);
    }
    void nndbgTPrintWarning_(const char* filename, int lineno, const char* fmt, ...){
        va_list vlist;

        va_start(vlist, fmt);
        nn::dbg::detail::TPrintf("%s:%d [WARN] ", filename, lineno);
        nn::dbg::detail::TVPrintf(fmt, vlist);
        nn::dbg::detail::TPrintf("\n");
        va_end(vlist);
    }
}