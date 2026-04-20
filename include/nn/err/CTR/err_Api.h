#ifndef NN_ERR_CTR_ERR_API_H_
#define NN_ERR_CTR_ERR_API_H_

#include <nn/types.h>
#include <nn/Result.h>
#include <nn/util/util_Result.h>
#include <nn/err/CTR/err_FatalErr.h>

#ifdef __cplusplus
// err Macros
namespace nn{
namespace err{
namespace CTR{
namespace detail{
    template <bool(*IsTarget)(Result), void(*TargetFunc)(Result, uptr)>
    inline void CallIf(Result r, uptr pc){
        if (IsTarget(r)){
            TargetFunc(r, pc);
        }
    }

    template <bool(*IsTarget)(Result), void(*TargetFunc)(Result, const char*, int, uptr)>
    inline void CallIf(Result r, const char* fileName, int lineno, uptr pc){
        if (IsTarget(r)){
            TargetFunc(r, fileName, lineno, pc);
        }
    }

    inline bool IsResultFailure(Result r) {return r.IsFailure(); }
    inline bool IsResultFatal  (Result r) {return r.GetLevel() == ::Result::LEVEL_FATAL; }

}
} 
}
}


#ifndef NN_HARDWARE_CTR_LEGACY

    #ifdef NN_PROCESSOR_ARM11MPCORE

        #define NN_ERR_CTR_ERR_API_H_CALL_IF(result, test, f)      \
            ::nn::err::CTR::detail::CallIf                         \
                < ::nn::err::CTR::detail::test,                    \
                  ::nn::err::CTR::f >(result, __current_pc())

        #define NN_ERR_CTR_ERR_API_H_CALL_IF2(result, test, f)     \
            ::nn::err::CTR::detail::CallIf                         \
                < ::nn::err::CTR::detail::test,                    \
                  ::nn::err::CTR::f >(result, NN_FILE_NAME, __LINE__, __current_pc())

        #define NN_ERR_THROW_FATAL_IF_FATAL_ONLY(result) \
            NN_ERR_CTR_ERR_API_H_CALL_IF(result, IsResultFatal, ThrowFatalErrAll)

        #define NN_ERR_THROW_FATAL(result) \
            NN_ERR_CTR_ERR_API_H_CALL_IF(result, IsResultFailure, ThrowFatalErr)

        #define NN_ERR_THROW_FATAL_ALL(result) \
            NN_ERR_CTR_ERR_API_H_CALL_IF(result, IsResultFailure, ThrowFatalErrAll)

        #ifndef NN_SWITCH_DISABLE_DEBUG_PRINT
            #define NN_ERR_LOG_AND_PANIC_IF_FAILED(result) \
                NN_ERR_CTR_ERR_API_H_CALL_IF2(result, IsResultFailure, LogAndPanic)
        #else
            #define NN_ERR_LOG_AND_PANIC_IF_FAILED(result) \
                NN_ERR_CTR_ERR_API_H_CALL_IF(result, IsResultFailure, LogAndPanic)
        #endif

    #else

        #define NN_ERR_THROW_FATAL_IF_FATAL_ONLY(result)    NN_UTIL_PANIC_IF_FAILED(result)
        #define NN_ERR_THROW_FATAL(result)                  NN_UTIL_PANIC_IF_FAILED(result)
        #define NN_ERR_THROW_FATAL_ALL(result)              NN_UTIL_PANIC_IF_FAILED(result)
        #define NN_ERR_LOG_AND_PANIC_IF_FAILED(result)      NN_UTIL_PANIC_IF_FAILED(result)

    #endif

#else

    #define NN_ERR_THROW_FATAL_IF_FATAL_ONLY(result)    ((void)(result))
    #define NN_ERR_THROW_FATAL(result)                  ((void)(result))
    #define NN_ERR_THROW_FATAL_ALL(result)              ((void)(result))
    #define NN_ERR_LOG_AND_PANIC_IF_FAILED(result)      ((void)(result))

#endif

#endif

#endif
