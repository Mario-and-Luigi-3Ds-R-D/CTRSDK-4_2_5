#pragma once

#include "nn/snd/CTR/MPCore/snd_System.h"
#include "nn/snd/CTR/Common/snd_Types.h"

namespace nn{
namespace snd{
namespace CTR{

class MasterManager{
public:
    struct FxSet{
    //    FxDelay
    };

    bool mInitialized;
    s8 buf;
    ClippingMode mClippingMode;
    OutputMode mOutputMode;
    f32 mMasterVolume;
    f32 mSystemMasterVolume;
    f32 mAuxVolume[2];
    uptr mAuxUserData[2];
    bool mAuxFrontBypass[2];
    SurroundSpeakerPosition mSpeakerPosition;
    f32 mSurroundDepth;
    f32 mRearRadio;
    s32 mDroppedFrameCount;
    FxSet mFxSet[2];
    os::CriticalSection mFxCriticalSection;

    static MasterManager* GetInstance();
};

namespace internal{
    CTR::MasterManager sMasterManager;
}

    inline MasterManager* MasterManager::GetInstance(){
        return &internal::sMasterManager;
    }
}
}
}