// Filename: snd_FxReverb.cpp
//
// Project: Horizon 4_2_5 Decompilation
//
// Remade by user Luigifan27

#include <nn/snd/CTR/MPCore/snd_FxReverb.h>
#include <nn/Assert.h>

#include "nn/snd/CTR/Common/snd_Types.h"

namespace nn{
namespace math{
    inline int Abs(int x){ if(x < 0) x = -x;  return x;}
}
namespace snd{
namespace CTR{

void FxReverb::UpdateBuffer(uptr data){
    if(!mIsActive) return;

    //.. TODO
}

}
}
}