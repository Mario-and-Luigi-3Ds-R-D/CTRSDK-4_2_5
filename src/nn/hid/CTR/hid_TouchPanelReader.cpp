// Filename: hid_TouchPanelReader.cpp
//
// Project: Horizon 4_2_5 Decompilation
//
// Remade by user Luigifan27

#include <nn/hid/CTR/hid_TouchPanelReader.h>
#include <nn/hidlow/CTR/hidlow_TouchPanelLifoRing.h>
#include <nn/applet/CTR/applet_Api.h>
#include <nn/applet/CTR/applet_Info.h>
#include <nn/Assert.h>

namespace nn{
namespace hid{
namespace CTR{

bool TouchPanelReader::ReadLatest(TouchPanelStatus *pBuf){
    s32 readLen;
    s64 tick = -1LL;
    s32 index = -1;
    
    NN_TASSERT_(NULL != pBuf);
    nn::hidlow::CTR::TouchPanelLifoRing* ring = (nn::hidlow::CTR::TouchPanelLifoRing*)this->mTouchPanel.mResourcePtr;
    ring->ReadData(pBuf, 1, &readLen, &tick, &index);
    if((applet::CTR::IsInitialized()) && (!applet::CTR::detail::IsActive())){
        pBuf->x = 0;
        pBuf->y = 0;
        pBuf->touch = 0;
    }
    return 0 < readLen;
}

void TouchPanelReader::Read(TouchPanelStatus* pBufs, s32* pReadLen, s32 bufLen){
    NN_TASSERT_(NULL != pBufs);
    nn::hidlow::CTR::TouchPanelLifoRing* ring = (nn::hidlow::CTR::TouchPanelLifoRing*)this->mTouchPanel.mResourcePtr;
    ring->ReadData(pBufs, 1, pReadLen, &this->mTickOfRead, &this->mIndexOfRead);
    for(int i = 0; i < *pReadLen; i++){
        if((applet::CTR::IsInitialized()) && (!applet::CTR::detail::IsActive())){
            pBufs[*pReadLen].x = 0;
            pBufs[*pReadLen].y = 0;
            pBufs[*pReadLen].touch = 0;
        }
    }
}

}
}
}