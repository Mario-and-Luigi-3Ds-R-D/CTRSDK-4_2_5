#pragma once

#include <nn/Handle.h>
#include <nn/Result.h>
#include <nn/types.h>
#include <nn/ro/ro_Types.h>

namespace nn {
namespace ro {
namespace detail {

class DynamicLoader{
public:
    DynamicLoader() {}

    static Handle sSession;

    static nn::Result Startup( nn::Handle process, uptr staticInfo, size_t staticInfoSize, uptr locateAddr);
    static nn::Result RegisterList( nn::Handle process, uptr rr, size_t rrSize);
    static nn::Result UnregisterList( nn::Handle process, uptr rr);
    static nn::Result Load(size_t* pFixedSize, nn::Handle process, uptr ro, uptr roRelocate, size_t roSize, uptr dataAddr, uptr dataRelocate, size_t dataSize, uptr bssAddr, uptr bssSize, bool doRegister, nn::ro::FixLevel fixLevel, uptr rr);
    static nn::Result Unload(nn::Handle process, uptr roModule, size_t roSize, uptr originalAddr);
    static nn::Result Link(nn::Handle process, uptr roModule);
    static nn::Result Unlink(nn::Handle process, uptr roModule);
    static nn::Result Cleanup(nn::Handle process, uptr originalAddr);
};

}
}
}