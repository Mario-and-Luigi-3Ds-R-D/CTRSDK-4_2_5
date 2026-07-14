// Filename: hid_DebugPadReader.cpp
//
// Project: Horizon 4_2_5 Decompilation
//
// Remade by user Luigifan27

#include <nn/hid/CTR/hid_DebugPadReader.h>
#include <nn/hidlow/hidlow_Utils.h>
#include <nn/hidlow/CTR/hidlow_DebugPadRawStatus.h>
#include <nn/hidlow/CTR/hidlow_DebugPadLifoRing.h>

namespace nn{
namespace hid{
namespace CTR{
namespace{
    hidlow::CTR::DebugPadRawStatus sDebugPadRawStatus[9];
}

/* NOT MATCHING */

bool DebugPadReader::ReadLatest(DebugPadStatus* pBuf){
    s64 tick = -1LL;
    s32 index = -1;
    s32 readLen;
    s32 min = 0;
    reinterpret_cast<nn::hidlow::CTR::DebugPadLifoRing*>(this->mDebugPad.GetResource())->ReadData(sDebugPadRawStatus, 1, &readLen, &tick, &index);
    if(STICK_CLAMP_MODE_CIRCLE_WITH_PLAY == this->mStickClampMode) min = 15;
    if(0 < readLen){
        if(this->mIsReadLatestFirst){
            this->mLatestHold = sDebugPadRawStatus[0].hold;
            this->mIsReadLatestFirst = false;
        }
        pBuf->trigger = (sDebugPadRawStatus[0].hold ^ this->mLatestHold) & ~this->mLatestHold;
        pBuf->release = (sDebugPadRawStatus[0].hold ^ this->mLatestHold) & this->mLatestHold;
        bit16 hold = sDebugPadRawStatus[0].hold;
        pBuf->hold = sDebugPadRawStatus[0].hold;
        this->mLatestHold = hold;
        hidlow::ClampStickCrossFloat(&pBuf->leftStickX, &pBuf->leftStickY,sDebugPadRawStatus[0].leftStickX << 2, sDebugPadRawStatus[0].leftStickY << 2, min, 0x4d);
        hidlow::ClampStickCrossFloat(&pBuf->rightStickX, &pBuf->rightStickY,sDebugPadRawStatus[0].rightStickX << 3, sDebugPadRawStatus[0].rightStickY << 3, min, 0x4d);
        return true;
    }
    return false;
}

void DebugPadReader::Read(DebugPadStatus* pBufs, s32* pReadLen, s32 bufLen){
    NN_TASSERT_(NULL != pBufs);
    s32 min = 0;
    if(bufLen > 8) bufLen = 8;

    reinterpret_cast<nn::hidlow::CTR::DebugPadLifoRing*>(this->mDebugPad.GetResource())->ReadData(sDebugPadRawStatus, bufLen, pReadLen, &this->mTickOfRead, &this->mIndexOfRead);
    if(this->mStickClampMode == STICK_CLAMP_MODE_CIRCLE_WITH_PLAY) min = 0xf;

    for(int i = 0; i < *pReadLen; i++){
        pBufs[i].hold = sDebugPadRawStatus[i].hold;
        pBufs[i].release = sDebugPadRawStatus[i].release;
        pBufs[i].trigger = sDebugPadRawStatus[i].trigger;
        hidlow::ClampStickCrossFloat(&pBufs[i].leftStickX, &pBufs[i].leftStickY, sDebugPadRawStatus[i].leftStickX << 2, sDebugPadRawStatus[i].leftStickY << 2, min, 0x4d);
        hidlow::ClampStickCrossFloat(&pBufs[i].rightStickX, &pBufs[i].rightStickY, sDebugPadRawStatus[i].rightStickX << 3, sDebugPadRawStatus[i].rightStickY << 2, min, 0x4d);
    }
}
}
}
}