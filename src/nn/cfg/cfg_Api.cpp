#include <nn/cfg/CTR/cfg_Api.h>
#include <nn/cfg/CTR/cfg_DetailApi.h>
#include <nn/Result.h>
#include <nn/err/CTR/err_Api.h>

namespace nn {
namespace cfg {
namespace CTR {

void Initialize(){
    Result res = detail::Initialize().IsFailure();

    if(res != 0){
        NN_ERR_THROW_FATAL(res);
    }
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