// Filename: hid_PadReader.cpp
//
// Project: Horizon 4_2_5 Decompilation
//
// Remade by user Luigifan27

#include <nn/hid/CTR/hid_PadReader.h>
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

    if(!ExtraPad::IsSampling()){
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
            if((applet::CTR::IsInitialized()) && (!applet::CTR::detail::IsActive())){
                this->HideKeyInfo(pBuf);
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

/*void PadReader::Read(PadStatus* pBufs, s32* pReadLen, s32 bufLen){
    NN_TASSERT_(NULL != pBufs);
    this->mStickClamper.ClampValueOfClamp();
    hidlow::CTR::PadLifoRing* ring = (hidlow::CTR::PadLifoRing*)this->mPad.GetResource();
    ring->hidlow::CTR::PadLifoRing::ReadData(pBufs, 1, pReadLen, &this->mTickOfRead, &this->mIndexOfRead);

    if(!ExtraPad::IsSampling){
        for(int i = 0; i < *pReadLen; i++){

        }
    }
}*/

f32 PadReader::NormalizeStick(short x, short y){
    return this->mStickClamper.NormalizeStick(x,y);
}

}
}
}