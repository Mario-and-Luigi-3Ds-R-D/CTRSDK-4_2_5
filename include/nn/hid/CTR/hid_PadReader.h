#pragma once

#include <nn/Handle.h>
#include <nn/Result.h>
#include <nn/types.h>
#include <nn/hid/CTR/hid_AnalogStickClamper.h>
#include <nn/hid/CTR/hid_Api.h>
#include <nn/hid/CTR/hid_Pad.h>
#include <nn/hid/CTR/hid_DeviceStatus.h>
#include <nn/util/util_NonCopyable.h>

namespace nn{
namespace hid{
namespace CTR{

class PadReader : private nn::util::NonCopyable<PadReader>{
public:
    typedef enum{
        STICK_CLAMP_MODE_CIRCLE = AnalogStickClamper::STICK_CLAMP_MODE_CIRCLE,
        STICK_CLAMP_MODE_CROSS = AnalogStickClamper::STICK_CLAMP_MODE_CROSS,
        STICK_CLAMP_MODE_MINIMUM = AnalogStickClamper::STICK_CLAMP_MODE_MINIMUM
    } StickClampMode;

    PadReader(Pad& pad=GetPad( ));
    ~PadReader() {};
    void Read(PadStatus* pBufs, s32* pReadLen, s32 bufLen);
    bool ReadLatest(PadStatus* pBuf);
    f32 NormalizeStick(short x, short y);

    void SetNormalizeStickScaleSettings(f32 scale, s16 threshold);

    static const s8 MAX_READ_NUM = 7;
    
    static void HideKeyInfo(PadStatus* padStatus){
      padStatus->hold = 0;
      padStatus->release = 0;
      padStatus->trigger = 0;
      padStatus->stick.x = 0;
      padStatus->stick.y = 0;
    }
protected:
    Pad& mPad;
    s32 mIndexOfRead;
    bit32 mLatestHold;
    AnalogStickClamper mStickClamper;
    bool mIsReadLatestFirst;
    s8 rev[3];
    s32 rev2;
    s64 mTickOfRead;

private:
    static AnalogStickClamper::ClampMode  ClamperClampMode(const StickClampMode mode){ return (AnalogStickClamper::ClampMode)mode; }
    static StickClampMode ReaderClampMode(const AnalogStickClamper::ClampMode mode);
public:
    inline void SetStickClampMode(StickClampMode mode){
        this->mStickClamper.SetStickClampMode(ClamperClampMode(mode));
    }
};


namespace{
    bool sIsEnableSelect;
}

}
}
}