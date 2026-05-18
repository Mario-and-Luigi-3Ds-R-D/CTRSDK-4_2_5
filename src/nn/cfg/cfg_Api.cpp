#include <nn/cfg/CTR/cfg_Api.h>
#include <nn/cfg/CTR/cfg_DetailApi.h>
#include <nn/cfg/CTR/cfg_IpcUser.h>
#include <nn/Result.h>
#include <nn/err/CTR/err_Api.h>

namespace nn {
namespace cfg {
namespace CTR {

LanguageCfgData LANGUAGE_CFG_DEFAULT;

void Initialize(){
    Result res; res = detail::Initialize();
    NN_ERR_THROW_FATAL_ALL(res);
}

void Finalize(){
    detail::Finalize();
}

CfgLanguageCode GetLanguage(){
    LanguageCfgData languageCode; Result res;
    languageCode.code = LANGUAGE_CFG_DEFAULT.code;
    res = detail::IpcUser::GetConfig(&languageCode,1,0xa0002);
    NN_ERR_THROW_FATAL_ALL(res);
    return (CfgLanguageCode)languageCode.code;
}

u8 GetFsLatencyEmulationParam(){
    Result res;
    DebugParamCfgData debugParam;
    detail::_IPCPortType portType;

    if (*(u8*)0x1FF80014 & 1) {
        return 0U;
    }

    res = detail::InitializeProperPort(&portType);
    if (res.IsFailure()) {
        NN_ERR_THROW_FATAL_ALL(res);
    }

    void* pData = &debugParam;
    res = detail::IpcUser::GetConfig(pData, 4, 0x130000);
    NN_ERR_THROW_FATAL_ALL(res);

    detail::_IPCPortType pt = portType;
    detail::FinalizeProperPort(pt);

    return debugParam.fsLatencyParam;
}

bool IsDebugMode(){
    Result res;
    DebugParamCfgData debugParam;
    detail::_IPCPortType portType;

    if (*(u8*)0x1FF80014 & 1) {
        return 0U;
    }

    res = detail::InitializeProperPort(&portType);
    if (res.IsFailure()) {
        NN_ERR_THROW_FATAL_ALL(res);
    }

    void* pData = &debugParam;
    res = detail::IpcUser::GetConfig(pData, 4, 0x130000);
    NN_ERR_THROW_FATAL_ALL(res);

    detail::_IPCPortType pt = portType;
    detail::FinalizeProperPort(pt);
    bool isMode;
    if((debugParam.param.flags1 & 1) == 0){
        return isMode = false;
    } else{
        return isMode = true;
    }
}

} // namespace CTR
} // namespace cfg
} // namespace nn