// Filename: hid_TouchPanel.cpp
//
// Project: Horizon 4_2_5 Decompilation
//
// Remade by user Luigifan27

#include <nn/hid/CTR/hid_TouchPanel.h>
#include <nn/hidlow/CTR/hidlow_TouchPanelLifoRing.h>
#include <nn/applet/CTR/applet_Api.h>
#include <nn/applet/CTR/applet_Info.h>
#include <nn/dbg/dbg_Break.h>

namespace nn{
namespace hid{
namespace CTR{

bool TouchPanelReader::ReadLatest(TouchPanelStatus *pBuf){
    s32 readLen;
    s64 tick = -1LL;
    s32 index = -1;
    
    #ifdef NN_DEBUG
        if (NULL == pBuf) {
            nndbgBreakWithTMessage_(NN_DBG_BREAK_REASON_ASSERT,"hid_TouchPanelReader.cpp",23,"%s","NULL == pBuf");
        }
    #endif
    
    nn::hidlow::CTR::TouchPanelLifoRing* ring = (nn::hidlow::CTR::TouchPanelLifoRing*)this->mTouchPanel.mResourcePtr;
    ring->ReadData(pBuf, 1, &readLen, &tick, &index);
    bool isAppletInitialized = applet::CTR::IsInitialized();
    if((isAppletInitialized) && (isAppletInitialized = applet::CTR::detail::IsActive(), !isAppletInitialized)){
        pBuf->x = 0;
        pBuf->y = 0;
        pBuf->touch = 0;
    }
    return 0 < readLen;
}

}
}
}