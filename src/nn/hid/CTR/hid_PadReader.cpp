// Filename: hid_PadReader.cpp
//
// Project: Horizon 4_2_5 Decompilation
//
// Remade by user Luigifan27

#include <nn/hid/CTR/hid_Pad.h>
#include <nn/hid/CTR/hid_ExtraPad.h>
#include <nn/hidlow/CTR/hidlow_PadLifoRing.h>
#include <nn/hidlow/hidlow_Api.h>
#include <nn/applet/CTR/applet_Api.h>
#include <nn/applet/CTR/applet_Info.h>

#include <nn/dbg/dbg_Break.h>

namespace nn{
namespace hid{
namespace CTR{

PadReader::PadReader(Pad& pad) : 
    mPad(pad), 
    mIndexOfRead(-1), 
    mIsReadLatestFirst(true), 
    mTickOfRead(-1){
}

#ifdef NONMATCHING
#endif
// the part is that ring-> and that ADD 2 early
bool PadReader::ReadLatest(PadStatus* pBuf){
    s64 tick = -1LL;
    s32 index = -1;
    s32 readLen;
    uint newHold;
    bool isAppletInitialized;

    bool IsSampling = nn::hid::CTR::ExtraPad::IsSampling();
    if(!IsSampling){
        this->mStickClamper.ClampValueOfClamp();
        hidlow::CTR::PadLifoRing* ring = (hidlow::CTR::PadLifoRing*)this->mPad.GetResource();
        ring->hidlow::CTR::PadLifoRing::ReadData(pBuf, 1, &readLen, &tick, &index);
        if(0 < readLen){
            this->mStickClamper.ClampCore(&pBuf->stick.x,&pBuf->stick.y,pBuf->stick.x,pBuf->stick.y);
            if(this->mIsReadLatestFirst != false){
                this->mLatestHold = pBuf->hold;
                this->mIsReadLatestFirst = false;
            }
            newHold = pBuf->hold & 0xffffdfff;
            pBuf->hold = newHold;
            uint mLatestHold = this->mLatestHold;
            pBuf->trigger = (newHold ^ mLatestHold) & ~mLatestHold;
            pBuf->release = this->mLatestHold & ~newHold;
            isAppletInitialized = applet::CTR::IsInitialized();
            if((isAppletInitialized) && (isAppletInitialized = applet::CTR::detail::IsActive(), !isAppletInitialized)){
                pBuf->hold = 0;
                pBuf->release = 0;
                pBuf->trigger = 0;
                pBuf->stick.x = 0;
                pBuf->stick.y = 0;
            }
            this->mLatestHold = pBuf->hold;
            if(sIsEnableSelect == false){
                hidlow::GatherStartAndSelect(pBuf);
            }
            return true;
        }
    }
    return false;
}

f32 PadReader::NormalizeStick(short x, short y){
    return this->mStickClamper.NormalizeStick(x,y);
}

}
}
}