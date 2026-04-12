#pragma once

#include "nn/Result.h"

enum nndbgBreakReason{
    NN_DBG_BREAK_REASON_PANIC = 0,
    NN_DBG_BREAK_REASON_ASSERT = 1,
    NN_DBG_BREAK_REASON_USER = 2,
    NN_DBG_BREAK_REASON_MAX_BIT = 1073741824,
};

extern "C"{
Result nndbgBreak(int pReason);
void nndbgPanic();
// Are these in DT? Down Below?
void nndbgBreakWithMessage_(nndbgBreakReason pReason, const char* pFileName, int pLineNo, const char* pFmt);
void nndbgBreakWithTMessage_(nndbgBreakReason pReason, const char* pFileName, int pLineNo, const char* pFmt);
void nndbgBreakWithResultMessage_(nndbgBreakReason pReason, Result pResult,  const char* pFileName, int pLineNo, const char* pFmt);
void nndbgBreakWithResultTMessage_(nndbgBreakReason pReason, Result pResult,  const char* pFileName, int pLineNo, const char* pFmt);
}

namespace nn{
namespace dbg{
    enum BreakReason{
        BREAK_REASON_PANIC = 0,
        BREAK_REASON_ASSERT = 1,
        BREAK_REASON_USER = 2,
        BREAK_REASON_LOAD_RO = 3, // Hey, thats my line!
        BREAK_REASON_UNLOAD_RO = 4,
        BREAK_REASON_MAX_BIT = 0x80000000,
    };

    Result Break(nn::dbg::BreakReason pReason);
    void Panic();
}
}