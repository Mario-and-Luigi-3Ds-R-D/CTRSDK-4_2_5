#include <cstdarg>
#include <nn/dbg/dbg_Break.h>
#include <nn/svc/svc_Api.h>
#include <cstdarg>

namespace{
static nn::dbg::BreakHandler s_pBreakHandler = NULL;

// Things needed for nn::dbg::Break, ignore these.

void CallBreakHandler(nn::dbg::BreakReason reason, Result* pResult, const char* filename, int lineno, const char* fmt, std::va_list args){
    nn::dbg::BreakHandler pBreakHandler = s_pBreakHandler;

    if (pBreakHandler != NULL){
        s_pBreakHandler = NULL;
        pBreakHandler(reason, pResult, filename, lineno, fmt, args);
    }
}

void CallBreakHandler(nndbgBreakReason reason, nnResult result, const char* filename, int lineno, const char* fmt, std::va_list args){
    Result resultCpp = result;
    CallBreakHandler(static_cast<nn::dbg::BreakReason>(reason), &resultCpp, filename, lineno, fmt, args);
}

void CallBreakHandler(nndbgBreakReason reason, const char* filename, int lineno, const char* fmt, std::va_list args){
    CallBreakHandler(static_cast<nn::dbg::BreakReason>(reason), NULL, filename, lineno, fmt, args);
}

void CallBreakHandler(nn::dbg::BreakReason reason){
    std::va_list args;
    CallBreakHandler(reason, NULL, NULL, 0, NULL, args);
}

}
namespace nn{
namespace dbg{
nn::dbg::BreakHandler s_pBreakHandler = 0;

__attribute__((noinline)) Result Break(BreakReason reason){
    CallBreakHandler(reason);
    return nn::svc::Break(reason, NULL, 0);
}

void Panic(){
    Break(BREAK_REASON_PANIC);
}

namespace detail{

Result NotifyDllLoadedToDebugger(const void* pDllInfo, size_t size){
    return nn::svc::Break(BREAK_REASON_UNLOAD_RO, pDllInfo, size);
}

}

}
}

// Panic. 

extern "C" {
void nndbgPanic(){
    nn::dbg::Panic();
}

Result nndbgBreak(nn::dbg::BreakReason pReason){
    nn::dbg::Break(pReason);
}

}