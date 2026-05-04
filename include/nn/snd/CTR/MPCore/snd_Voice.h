#pragma once

#include "nn/Result.h"
#include "nn/snd/CTR/Common/snd_Types.h"

namespace nn {
namespace snd {
namespace CTR {

typedef void (*VoiceDropCallbackFunc)(class Voice*, uptr userArg);

class VoiceImpl;
class VoiceManager;

class Voice {
    friend class VoiceManager;

public:
    enum State {
        STATE_PLAY,
        STATE_STOP,
        STATE_PAUSE
    };

private:
    const s32 mId;
    s8 mState;
    s8 mInterpolationType;
    s8 rev;
    s8 mFilterType;
    MonoFilterCoefficients mMonoFilterCoeffs;
    BiquadFilterCoefficients mBiquadFilterCoeffs;
    s8 rev2[2];
    s32 mSampleRate;
    f32 mPitch;
    s32 mPriority;
    Voice* mPriorVoice;
    Voice* mInferiorVoice;
    VoiceDropCallbackFunc mCallback;
    uptr mUserArg;
    MixParam mMixParam;
    f32 mVolume;
    VoiceImpl* mpImpl;

    void Initialize();
    void UpdateStatus(const void* pVars);
    void UpdateWaveBufferList();
    s32 GetId() const { return mId; }
    VoiceImpl* GetImpl() const { return mpImpl; }

    explicit Voice(s32 id);
    ~Voice();

public:
    void AppendWaveBuffer(WaveBuffer* pBuffer);
    void DeleteWaveBuffer(WaveBuffer* pBuffer);
    void UpdateWaveBuffer(WaveBuffer* pBuffer);

    void SetChannelCount(s32 channelCount);
    void SetSampleFormat(SampleFormat format);
    void SetFrontBypassFlag(bool flag);
    void Set3dSurroundPreprocessed(bool flag);
    void SetStartFrameFadeInFlag(bool flag);
    void SetSampleRate(s32 sampleRate);
    void SetPitch(f32 pitch);
    void SetAdpcmParam(const AdpcmParam& param);
    void SetPriority(s32 priority);
    void SetState(State state);
    void SetMixParam(const MixParam& mixParam);
    void SetVolume(f32 volume);
    void SetInterpolationType(InterpolationType type);
    void SetFilterType(FilterType type);
    void EnableMonoFilter(bool enable);
    void SetMonoFilterCoefficients(const MonoFilterCoefficients* pCoeff);
    void SetMonoFilterCoefficients(const MonoFilterCoefficients& coeff);
    void SetMonoFilterCoefficients(u16 cutoff);
    void EnableBiquadFilter(bool enable);
    void SetBiquadFilterCoefficients(const BiquadFilterCoefficients* pCoeff);
    void SetBiquadFilterCoefficients(const BiquadFilterCoefficients& coeff);

    void GetMonoFilterCoefficients(MonoFilterCoefficients* pCoeff);
    void GetMonoFilterCoefficients(MonoFilterCoefficients& coeff);
    void GetBiquadFilterCoefficients(BiquadFilterCoefficients* pCoeff);
    void GetBiquadFilterCoefficients(BiquadFilterCoefficients& coeff);

    s32  GetPlayPosition() const;
    bool IsPlaying() const;

    bool SetupBcwav(uptr addrBcwav, WaveBuffer* pWaveBuffer0, WaveBuffer* pWaveBuffer1, Bcwav::ChannelIndex channelIndex = Bcwav::CHANNEL_INDEX_L);
};

Voice* AllocVoice(s32 priority, VoiceDropCallbackFunc callback, uptr userArg);
void   FreeVoice(Voice* pVoice);

enum VoiceDropMode {
    VOICE_DROP_MODE_DEFAULT   = 0,
    VOICE_DROP_MODE_REAL_TIME = 1
};

void SetVoiceDropMode(VoiceDropMode mode);

} // namespace CTR
} // namespace snd
} // namespace nn