#pragma once

#include "nn/types.h"
#include "nn/cfg/CTR/cfg_LanguageCode.h"

namespace nn {
namespace cfg {
namespace CTR {
    const char PORT_NAME_USER[] = "cfg:u";
    const char PORT_NAME_INIT[] = "cfg:i";
    const char PORT_NAME_SYSTEM[] = "cfg:s";
    
    void Initialize();
    void Finalize();
    CfgLanguageCode GetLanguage();
    
    u8 GetFsLatencyEmulationParam();
    bool IsDebugMode();

    struct LanguageCfgData{
        u8 code;
    };

    extern LanguageCfgData LANGUAGE_CFG_DEFAULT;

    struct DebugParamCfgData{
        union debugParam{
            u8 flags1;
            u8 param1;
        };

        bool dlpDebug;
        debugParam param;
        u8 fsLatencyParam;
        u8 rsv;
    };
} // namespace CTR
} // namespace cfg
} // namespace nn