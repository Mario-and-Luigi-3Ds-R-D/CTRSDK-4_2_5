#include <nn/dbg/dbg_Printf.h>
#include <nn/nstd/nstd_Printf.h>
#include <nn/util/detail/util_Symbol.h>
#include <nn/svc/svc_Api.h>
#include <string.h>

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
            length = NN_DBG_TPRINTF_BUFFER_LENGTH - 1;   // need not count \0 of tail end
        }
        detail::PutString(buf, length);
    }

}
}
}