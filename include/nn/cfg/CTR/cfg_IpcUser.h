#pragma once

#include "nn/Handle.h"
#include "nn/Result.h"
#include "nn/types.h"
#include "nn/cfg/CTR/cfg_RegionCode.h"

namespace nn {
namespace cfg {
namespace CTR {
namespace detail {

class IpcUser{
private:
        Handle s_Session;

public:
        Result GetConfig (void* pData, size_t size, bit32 key) const;
        Result GetRegion (CfgRegionCode*) const;
        Result GetTransferableId (bit32, bit64*);
        Result IsCoppacsSupported (bool*);
};

} // namespace detail
} // namespace CTR
} // namespace cfg
} // namespace nn