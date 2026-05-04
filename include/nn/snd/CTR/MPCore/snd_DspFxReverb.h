#pragma once

#include "nn/snd/CTR/Common/snd_Types.h"
#include "nn/util/util_NonCopyable.h"

namespace nn {
namespace snd {
namespace CTR {

class DspFxReverb : private nn::util::NonCopyable<DspFxReverb> {
public:
    struct FilterSize {
        u32 mComb0;
        u32 mComb1;
        u32 mAllPass;
    };

    struct Param {
        u32         mEarlyReflectionTime;
        u32         mFusedTime;
        u32         mPreDelayTime;
        f32         mColoration;
        f32         mDamping;
        FilterSize* mpFilterSize;
        f32         mEarlyGain;
        f32         mFusedGain;
        bool        mUseHpfDamping;
        s8 rev[3];

        Param();
    };

public:
    DspFxReverb();
    ~DspFxReverb();

    static size_t GetRequiredMemorySize(const DspFxReverb::Param& param);
    bool Initialize(uptr buffer, size_t size);
    void Finalize();
    bool Attach(AuxBusId id);
    void Detach();
    bool SetParam(const DspFxReverb::Param& param);
    bool Enable(bool enable = true);

    bool Disable()   {
        return Enable(false); 
    }
    bool IsEnabled() {
        return mIsEnabled; 
    }

    bool IsBufferInUse();

private:
    bool AssignWorkBuffer(uptr buffer, size_t size);
    void ReleaseWorkBuffer();

    static FilterSize sDefaultFilterSize;

    uptr mBuffer;
    uptr mBufferPhysical;
    size_t mBufferSize;
    bool mIsInitialized;
    s8 mAuxBusId;
    bool mIsEnabled;
    s8 mProcessCount;
};

} // namespace CTR
} // namespace snd
} // namespace nn