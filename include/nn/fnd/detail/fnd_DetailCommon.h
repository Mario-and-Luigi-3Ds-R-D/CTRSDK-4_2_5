#include "nn/types.h"

typedef s32 NNSiIntPtr;     // signed integer type mutually convertible with void* pointer
typedef u32 NNSiUIntPtr;    // unsigned integer type mutually convertible with void* pointer

namespace nn{ 
namespace fnd { 
namespace detail {

#define  NNSi_FndGetBitValue(data, st, bits) \
    (((data) >>(st)) & ((1 <<(bits)) -1))

inline NNSiUIntPtr NNSiGetUIntPtr(const void* ptr){
    return (NNSiUIntPtr)ptr;
}

inline void* AddU32ToPtr(void* ptr, u32 val){
    return (void*)( NNSiGetUIntPtr(ptr) + val );
}

inline void* SubU32ToPtr(void* ptr, u32 val){
    return (void*)( NNSiGetUIntPtr(ptr) - val );
}

inline u32 GetOffsetFromPtr(const void* start, const void* end){
    return NNSiGetUIntPtr(end) - NNSiGetUIntPtr(start);
}

}
}
}