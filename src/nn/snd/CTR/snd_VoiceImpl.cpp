#include <nn/snd/CTR/MPCore/snd_Voice.h>
#include <nn/snd/CTR/MPCore/snd_OperateMaster.h>

namespace nn{
namespace snd{
namespace CTR{
namespace{
WaveBuffer* SearchPlayingBuffer(ushort currentBufferId, ushort lastBufferId, WaveBuffer* pWaveBuffer, short* sentBufferCount){

}

}

void VoiceImpl::AppendWaveBuffer(WaveBuffer* buffer){
    NN_TASSERT_(buffer->status == WaveBuffer::STATUS_FREE);
    NN_NULL_TASSERT_(buffer->bufferAddress);

}

void VoiceImpl::CalculateDspCycle(){
    this->mModifiedParamFlag = -1;
    this->UpdateParams();
}

void VoiceImpl::ForceUpdateParams(){
    this->mModifiedParamFlag = 0xffff;
    this->UpdateParams();
}

void VoiceImpl::Initialize(){
    this->mState = Voice::STATE_PAUSE;
    this->mPlaying = false;
    this->mPlayPosition = 0;
    this->mIsFirstWaveBufferForAdpcm = false;
    this->mWaveBufferModifiedFlag = 0;

    this->mSampleInfo &= 0xfffc | 1;
    this->mSampleInfo &= 0xfff3 | 4;
    this->mSampleInfo &= 0xffef;
    this->mSampleInfo &= 0xffdf;
    this->mSampleInfo &= 0xffbf;

    this->SetVolume(1.0);
    MixParam mixParam;
    this->SetMixParam(mixParam);
    this->SetSampleRate(0x7fd8);
    this->SetPitch(1.0);
    this->SetInterpolationType(INTERPOLATION_TYPE_POLYPHASE);
    this->SetFilterType(FILTER_TYPE_NONE);
    memset(&this->mMonoFilterCoeffs,0,4);
    memset(&this->mBiquadFilterCoeffs,0,10);
    this->mDspCycles = 0;
    this->mpWaveBuffer = 0;
    this->mSentBufferCount = 0;
    this->mNextBufferIndex = 0;
    this->mBufferId = 0;
}

void VoiceImpl::ReleaseWaveBuffer(){
    os::CriticalSection::ScopedLock lock(this->mCriticalSection);
    for(WaveBuffer* p = this->mpWaveBuffer; p != 0; p = p->next){
        //memcpy(&p->status,this->) what goes here..?
    }
    this->mpWaveBuffer = 0;
    this->mSentBufferCount = 0;
    this->mNextBufferIndex = 0;
    lock.~ScopedLock();
    this->mSyncCount++;
    this->mModifiedParamFlag |= 0x8000;
}

void VoiceImpl::SendWaveBuffer(){
    // TODO
}

void VoiceImpl::SetMixVolume(){
    MixParam mix;
    memcpy(&mix,&this->mMixParam,0x30);
    for(int i = 0; i < 4; i++){
        (&mix)[-1].mainBus[i] = mix.mainBus[i] * this->mVolume;
        mix.mainBus[i += -8] = mix.auxBusA[i] * this->mVolume;
        mix.mainBus[i += -4] = mix.auxBusB[i] * this->mVolume;
    }
    for(int j = 0; j < 4; j++){
        mix.mainBus[j] = (&mix)[-1].mainBus[j];
        mix.auxBusA[j] = mix.mainBus[j += -8];
        mix.auxBusB[j] = mix.mainBus[j += -8];
    }
    internal::sDspsnd.SetChannelMix(this->mId,&mix);
}

void VoiceImpl::SetState(Voice::State state){
    NN_TASSERT_(state == Voice::STATE_PLAY || state == Voice::STATE_STOP || state == Voice::STATE_PAUSE);
    this->mState = state;
    if(state != Voice::STATE_PLAY){
        if(state == Voice::STATE_STOP)
            this->Stop();
        else if(state == Voice::STATE_PAUSE)
            this->Pause();
    }
}

void VoiceImpl::SetSyncCount(){
    if(this->mModifiedParamFlag & 0x8000){
        internal::sDspsnd.SetChannelSyncCount(this->mId, this->mSyncCount);
        this->mModifiedParamFlag &= 0x7fff;
    }
}

void VoiceImpl::Start(){
    internal::sDspsnd.SetChannelPlayStart(this->mId);
    this->mPlaying = true;
}

void VoiceImpl::Stop(){
    internal::sDspsnd.SetChannelPlayStop(this->mId);
    this->mPlaying = false;
    internal::sDspsnd.InitializeChannelParameters(this->mId);
}

void VoiceImpl::UpdateParams(){
    if(this->mModifiedParamFlag & 1)
        this->SetMixVolume();
    if(this->mModifiedParamFlag & 2)
        this->SetTimer();
    if(this->mModifiedParamFlag & 4)
        internal::sDspsnd.SetChannelIiRFilterType(this->mId,this->mFilterType);
    if(this->mModifiedParamFlag & 8)
        internal::sDspsnd.SetChannelIIRFilter_Mono(this->mId,this->mMonoFilterCoeffs.n0,this->mMonoFilterCoeffs.d1);
    if(this->mModifiedParamFlag & 0x10)
        internal::sDspsnd.SetChannelIIRFilter_Biquad(
            this->mId,
            this->mBiquadFilterCoeffs.n0,
            this->mBiquadFilterCoeffs.n1,
            this->mBiquadFilterCoeffs.n2,
            this->mBiquadFilterCoeffs.d1,
            this->mBiquadFilterCoeffs.d2);
    if(this->mModifiedParamFlag & 0x20)
        this->UpdateInterpolationType();
    if(this->mModifiedParamFlag & (1 | 2 | 4 | 0x20))
        this->CalculateDspCycle();
    this->mModifiedParamFlag &= 0x8000;
}

void VoiceImpl::UpdateStatus(){
    // TODO
}

void VoiceImpl::UpdateWaveBufferList(){
    if(this->mState == Voice::STATE_PLAY)
        this->SendWaveBuffer();
}

void VoiceImpl::UpdateWaveBufferStatus(ushort currentBufferId, ushort lastBufferId){
    os::CriticalSection::ScopedLock lock(this->mCriticalSection);
    if(!this->mpWaveBuffer){
        lock.~ScopedLock();
    }
    else{

    }
    // todo if needed
}

void VoiceImpl::Pause(){
    internal::sDspsnd.SetChannelPlayStop(this->mId);
}

ushort VoiceImpl::SelectCoefficient(){
    if(this->mSampleRateRatio == 1.3333334 || this->mSampleRateRatio < 1.3333334 != (this->mSampleRateRatio)){
        if(this->mSampleRateRatio <= 1.0)
            return 2;
    }
    else
        return 0;
}

void VoiceImpl::SetInterpolationType(InterpolationType type){
    NN_TASSERT_(type == INTERPOLATION_TYPE_POLYPHASE || type == INTERPOLATION_TYPE_LINEAR || type ==  INTERPOLATION_TYPE_NONE);
    this->mInterpolationType = type;
    this->mModifiedParamFlag |= 0x20;
}

void VoiceImpl::SetMixParam(const MixParam& mixParam){
    memcpy(&this->mMixParam, &mixParam, 0x30);
    this->mModifiedParamFlag |= 1;
}

void VoiceImpl::SetPitch(f32 pitch){
    NN_TASSERT_(0.0f <= pitch);
    this->mPitch = math::max(pitch,0.0);
    this->mModifiedParamFlag |= 2;
}

void VoiceImpl::SetSampleFormat(SampleFormat format){
    NN_TASSERT_(format == SAMPLE_FORMAT_PCM16 || format == SAMPLE_FORMAT_PCM8 || format == SAMPLE_FORMAT_ADPCM);
    this->mSampleInfo &= 0xfff3 | (format & 3) << 2;
}

void VoiceImpl::SetSampleRate(s32 sampleRate){
    NN_TASSERT_(0 <= sampleRate);
    this->mSampleRate = math::max(sampleRate, 0);
    this->mModifiedParamFlag |= 2;
}

void VoiceImpl::SetVolume(f32 volume){
    this->mVolume = volume;
    this->mModifiedParamFlag |= 1;
}

void VoiceImpl::SetTimer(){
    this->mSampleRateRatio = this->CalcFsRatio();
    internal::sDspsnd.SetChannelTimer(this->mId, this->mSampleRateRatio);
    if(this->mInterpolationType == INTERPOLATION_TYPE_POLYPHASE)
        this->mModifiedParamFlag |= 0x20;
}

void VoiceImpl::UpdateInterpolationType(){
    DSPWord method;
    ushort coefSelect;
    if(this->mInterpolationType == INTERPOLATION_TYPE_POLYPHASE){
        method = 0;
        coefSelect = this->SelectCoefficient();
    }
    else if(this->mInterpolationType == INTERPOLATION_TYPE_LINEAR)
        method = 1;
    internal::sDspsnd.SetChannelRIM(this->mId,method,coefSelect);
}

}
}
}