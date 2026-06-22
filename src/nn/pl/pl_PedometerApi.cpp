// Filename: pl_PedometerApi.cpp
//
// Project: Horizon 4_2_5 Decompilation
//
// Remade by user Luigifan27

#include <nn/pl/CTR/pl_PedometerApi.h>
#include "nn/ptm/CTR/detail/ptm_PtmIpc.h"
#include "nn/dbg/dbg_Break.h"

namespace nn {
namespace pl {
namespace CTR {

void GetStepHistory(ushort pStepCounts, s32 numHours, nn::fnd::DateTime start){
    Result result;

    if(nn::ptm::CTR::detail::PtmIpc::GetStepHistory().IsFailure()){
        nndbgBreak((nn::dbg::BreakReason)result.mResult);
    }
    return;
}

}
}
}