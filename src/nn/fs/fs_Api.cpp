#include <nn/fs/fs_Api.h>
#include <nn/fs/fs_Paramaters.h>
#include <nn/err/CTR/err_Api.h>
#include <nn/cfg/CTR/cfg_Api.h>
#include <nn/srv/srv_Api.h>

namespace nn{
namespace fs{
// hacky but it matches kinda
#ifdef NONMATCHING_STRBNE
#endif

void InitializeLatencyEmulation(void) {
    u8 getFsLatency  = nn::cfg::CTR::GetFsLatencyEmulationParam();
    s32 scaled = getFsLatency * 10;
    s64 latency = static_cast<s64>(scaled);

    pLatencyState.mLatencyParamLo = static_cast<s32>(latency);
    pLatencyState.mLatencyParamHi = static_cast<s32>(latency >> 32);

    if (nn::cfg::CTR::IsDebugMode() != 0) {
        pLatencyState.mIsEmulationEndurance = 1;
    }

    if (pLatencyState.mIsDebugMode != 0 ||
        (pLatencyState.mLatencyParamHi | pLatencyState.mLatencyParamLo) != 0) {
        pLatencyState.mIsLatencyEmuEnabled = 1;
    }
}

// Not Finished
void Initialize(){
    Result servHandle;
    Result isInit = IsInitialized();
    if(isInit == 0){
        isInit = srv::Initialize();
        if(isInit != 0x8a067f9){
            NN_ERR_THROW_FATAL_ALL(isInit);
        }
        //servHandle = srv::GetServiceHandle(&sFileServerSession, detail::FILE_SERVER_NAME);
        //NN_ERR_THROW_FATAL_ALL(servHandle);
    }
}

}
}