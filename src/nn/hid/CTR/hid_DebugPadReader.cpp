// Filename: hid_DebugPadReader.cpp
//
// Project: Horizon 4_2_5 Decompilation
//
// Remade by user Luigifan27

#include <nn/hid/CTR/hid_DebugPadReader.h>
#include <nn/hidlow/CTR/hidlow_DebugPadStatusRaw.h>
#include <nn/hidlow/CTR/hidlow_DebugPadLifoRing.h>

namespace nn{
namespace hid{
namespace CTR{
namespace{
    hidlow::CTR::DebugPadRawStatus sDebugPadRawStatus[9];
}

bool DebugPadReader::ReadLatest(DebugPadStatus* pBuf){
    s64 tick = -1LL;
    s32 index = -1;
    s32 readLen;
    s32 min = 0;
    hidlow::CTR::DebugPadLifoRing* ring = (hidlow::CTR::DebugPadLifoRing*)this->mDebugPad.GetResource();
    ring->ReadData(sDebugPadRawStatus, 1, &readLen, &tick, &index);
    if(this->mStickClampMode == STICK_CLAMP_MODE_CIRCLE_WITH_PLAY) min = 0xf;
    if(0 < readLen){
        if(this->mIsReadLatestFirst){
            this->mLatestHold = sDebugPadRawStatus[0].hold;
            this->mIsReadLatestFirst = false;
        }
        // TODO
        return false;
    }
}
}
}
}