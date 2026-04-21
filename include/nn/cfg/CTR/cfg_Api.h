#pragma once

#include "nn/types.h"

namespace nn {
namespace cfg {
namespace CTR {
    const char PORT_NAME_USER[] = "cfg:u";
    const char PORT_NAME_SYSTEM[] = "cfg:s";
    const char PORT_NAME_IPC[] = "cfg:i";
    
    void Initialize();
    u8 GetFsLatencyEmulationParam();
    bool IsDebugMode();

} // namespace CTR
} // namespace cfg
} // namespace nn