#pragma once

#include "nn/types.h"

namespace nn {
namespace nstd {

s32 TVSNPrintf (char* dst, size_t len, const char* fmt, va_list vlist);
s32 TSNPrintf (char* dst, size_t len, const char* fmt, ...);
s32 TSPrintf (char* dst, const char* fmt, ...);

} // namespace nstd
} // namespace nn