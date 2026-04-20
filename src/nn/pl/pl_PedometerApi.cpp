#include <nn/pl/CTR/pl_PedometerApi.h>
#include "nn/ptm/CTR/detail/ptm_PtmIpc.h"
#include "nn/dbg/dbg_Break.h"

namespace nn {
namespace pl {
namespace CTR {

void GetStepHistory(ushort pStepCounts, s32 numHours, nn::fnd::DateTime start){
    Result result;

    result.mResult = nn::ptm::CTR::detail::PtmIpc::GetStepHistory().IsFailure();
    if(result != 0){
        nndbgBreak((nn::dbg::BreakReason)result.IsFailure());
    }
    return;
}

}
}
}