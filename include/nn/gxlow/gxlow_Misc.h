#pragma once

#include "nn/types.h"

#ifdef __cplusplus
extern "C"{
#endif

void nngxlowFlushDataCache(const void* pData, size_t size);
uptr nngxlowGetPhysicalAddr(uptr virtualAddr);

#ifdef __cplusplus
}
#endif

namespace nn{
namespace gxlow{
namespace CTR{

void FlushDataCache(const void* pData, size_t size);
uptr GetPhysicalAddr(uptr virtualAddr);


}
}
}