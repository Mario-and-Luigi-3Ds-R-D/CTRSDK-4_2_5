#pragma once

#include <nn/types.h>

extern "C" {
    uptr nngxGetPhysicalAddr(uptr virtualAddr);
    void nngxUpdateBuffer(const void* pBuffer, size_t size);
}

namespace nn {
namespace gx {
namespace CTR {

    inline uptr GetPhysicalAddr(uptr virtualAddr) {
        return nngxGetPhysicalAddr(virtualAddr);
    }

    inline void UpdateBuffer(const void* pBuffer, size_t size) {
        nngxUpdateBuffer(pBuffer, size);
    }

}
}
}