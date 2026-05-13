#include "nn/dbg/dbg_Printf.h"

extern "C"{
    void nndbgPrintWarning_ (const char* filename, int lineno, const char* fmt, ...);
    void nndbgTPrintWarning_(const char* filename, int lineno, const char* fmt, ...);
}