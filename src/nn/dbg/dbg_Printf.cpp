#include <nn/dbg/dbg_Printf.h>
#include <nn/nstd/nstd_Printf.h>
#include <nn/util/detail/util_Symbol.h>
#include <nn/svc/svc_Api.h>

#include <string.h>
#include <cstdio>
#include <cstdarg>
#include <cstring>

#define NN_DBG_PRINTF_BUFFER_LENGTH     256
#define NN_DBG_TPRINTF_BUFFER_LENGTH 128

namespace nn{
namespace dbg{
namespace detail{
    void PutString(const char* text, s32 length){
        //NN_UTIL_REFER_SYMBOL(nullptr);
        nn::svc::OutputDebugString(text, length);
    }

    void PutString(const char* text){
        PutString(text, strlen(text));
    }

    void TVPrintf(const char* fmt, ::std::va_list arg){
        char buf[NN_DBG_TPRINTF_BUFFER_LENGTH];
        int length = nstd::TVSNPrintf(buf, sizeof(buf), fmt, arg);
        if (length >= NN_DBG_TPRINTF_BUFFER_LENGTH){
            length = NN_DBG_TPRINTF_BUFFER_LENGTH - 1;
        }
        detail::PutString(buf, length);
    }

    void TPrintf(const char* fmt, ...){
        va_list vlist;

        va_start(vlist, fmt);
        nn::dbg::detail::TVPrintf(fmt, vlist);
        va_end(vlist);
    }

    __weak void VPrintf(const char* fmt, ::std::va_list arg){
        char buf[NN_DBG_PRINTF_BUFFER_LENGTH];
        int length = ::std::vsnprintf(buf, sizeof(buf), fmt, arg);
        if (length >= NN_DBG_PRINTF_BUFFER_LENGTH){
            length = NN_DBG_PRINTF_BUFFER_LENGTH - 1;
        }
        PutString(buf, length);
    }

    void PrintResult(Result result){
        Result res_local = result;
        TPrintf("Result (%08x)\n", res_local.GetPrintableBits());
        TPrintf("  Level:       (%4d) %s\n", res_local.GetLevel());
        TPrintf("  Summary:     (%4d) %s\n",res_local.GetSummary()); // GetSummaryString());
        TPrintf("  Module:      (%4d) %s\n",res_local.GetModule()); // GetModuleString());
        TPrintf("  Description: (%4d) %s\n",res_local.GetDescription()); // GetDescriptionString());
    }

}
}
}