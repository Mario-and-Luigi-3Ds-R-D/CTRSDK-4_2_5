#pragma once

#include "nn/Handle.h"
#include "nn/Result.h"

namespace nn {
namespace cfg {
namespace CTR {
namespace detail {
        typedef enum _IPCPortType{
                PORT_CFG_USER   = 0,
                PORT_CFG_SYS    = 1,
                PORT_CFG_INIT   = 2,
                PORT_CFG_NOR    = 3,
                NUM_OF_IPC_PORT = 4
        } IPCPortType;

        Result Initialize();
        Result InitializeProperPort(IPCPortType* pPortType);

        void Finalize();
        void FinalizeProperPort(IPCPortType portType);

        Result GetConfig(void* pData, size_t size, bit32 key);

} // namespace detail
} // namespace CTR
} // namespace cfg
} // namespace nn