#pragma once

#include <nn/Handle.h>
#include <nn/fnd/fnd_DateTime.h>

namespace nn{
namespace ptm{
namespace CTR{
namespace detail{
namespace PtmIpc{

extern nn::Handle sSession;

Result GetStepHistory(ushort* pStepCounts, s32 numHours, nn::fnd::DateTime start);

}
}
}
}
}