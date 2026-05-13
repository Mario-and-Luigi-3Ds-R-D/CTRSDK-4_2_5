#pragma once

#include "nn/types.h"
#include "nn/snd/CTR/MPCore/snd_DspFxDelay.h"
#include "nn/snd/CTR/MPCore/snd_DspFxReverb.h"

namespace nn{
namespace snd{
namespace CTR{

class DspFxManagerImpl;

class DspFxManager{
protected:
    bool mIsAttached[2][2];
    bool mIsEnabled[2][2];
    s8 mChannelNum[2][2];

public:
    void Initialize();
    DspFxManagerImpl* Finalize();
    static DspFxManager* GetInstance();
    bool Detach(s32, s8);
    bool Attach(s8, s8, s8);
    s32 GetDspCycles();

    static DspFxManager* sInstance;
};

class DspFxManagerImpl{
protected:
    DspFxDelay::Param mDspFxDelayParams[2];
    DspFxReverb::Param mDspFxReverbParams[2];

public:
    void Initialize();
    DspFxManagerImpl* Finalize();
    void ForceUpdateParams();
    static DspFxManagerImpl* GetInstance();
    void SetDspDelayEffect(); // more params, check AliceP.
    void SetDspReverbEffect(); // more params, check AliceP.

    static DspFxManagerImpl* sInstance;
};
}
}
}

//extern nn::snd::CTR::DspFxManager instance;
//extern nn::snd::CTR::DspFxManagerImpl instance;