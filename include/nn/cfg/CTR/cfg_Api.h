#pragma once

#include "nn/types.h"
#include "nn/cfg/CTR/cfg_LanguageCode.h"

namespace nn {
namespace cfg {
namespace CTR {
    const char PORT_NAME_USER[] = "cfg:u";
    const char PORT_NAME_SYSTEM[] = "cfg:s";
    const char PORT_NAME_IPC[] = "cfg:i";
    
    void Initialize();
    void Finalize();
    CfgLanguageCode GetLanguage();
    
    u8 GetFsLatencyEmulationParam();
    bool IsDebugMode();

    struct LanguageCfgData{
        u8 code;
    };

    extern LanguageCfgData LANGUAGE_CFG_DEFAULT;

} // namespace CTR
} // namespace cfg
} // namespace nn