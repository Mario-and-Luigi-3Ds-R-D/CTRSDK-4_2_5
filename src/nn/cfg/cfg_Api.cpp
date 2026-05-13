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
    // TODO
}

bool IsDebugMode(){
    // TODO
}

} // namespace CTR
} // namespace cfg
} // namespace nn