#pragma once

#include "nn/types.h"
#include "nn/Handle.h"
#include "nn/Result.h"
#include "nn/cfg/CTR/cfg_RegionCode.h"

namespace nn {
namespace cfg {
namespace CTR {
namespace detail {
namespace IpcUser{
namespace{
        extern nn::Handle sSession;
}
        Result GetConfig (void* pData, size_t size, bit32 key);
        Result GetRegion (CfgRegionCode*);
        Result GetTransferableId (bit32, bit64*);
        Result IsCoppacsSupported (bool*);
                
};

} // namespace detail
} // namespace CTR
} // namespace cfg
} // namespace nn