#include <nn/snd/CTR/MPCore/snd_MasterManager.h>
#include <nn/dsp/CTR/MPCore/dsp_Api.h>
#include <nn/Assert.h>

namespace nn {
namespace snd {
namespace CTR {
namespace internal{
    CTR::MasterManagerImpl sMasterManagerImpl;
}
// flagged
void MasterManagerImpl::AuxUserCallback(AuxBusId busId, uptr data){
    NN_TASSERT_((busId != AUX_BUS_A) && (busId != AUX_BUS_B));
    AuxBusData auxBusData;
    if(this->mInitialized){
        os::CriticalSection::ScopedLock lock(this->mCriticalSection);
        if(this->mAuxCallback[busId] != 0){
            auxBusData.frontRight = (s32*)data + 0x280;
            auxBusData.rearLeft = (s32*)data + 0x500;
            auxBusData.rearRight = (s32*)data + 0x780;
            auxBusData.frontLeft = (s32*)data;
            (*this->mAuxCallback[busId])(&auxBusData,0xa0,this->mAuxUserData[busId]);
        }
        return;
    }
}

void MasterManagerImpl::Finalize(){
    if(this->mInitialized){
        this->mCriticalSection.Finalize();
        this->mInitialized = false;
    }
}

void MasterManagerImpl::ForceUpdateParams(){
    AuxBusId id;
    bool flag;
    OutputMode outmode;
    ClippingMode clippingmode;
    SurroundSpeakerPosition pos;
    SyncMode syncmode;
    internal::sDspsnd.SetMasterVolume(this->mMasterVolume * this->mSystemMasterVolume);
    for(int i = 0; i < 2; i++){
        internal::sDspsnd.SetAuxReturnVolume(id,this->mAuxVolume[id]);
        if((!this->mAuxCallback[id]) && (!this->mFxEnabled[id])){
            flag = false;
        }
        else{
            flag = true;
        }
        internal::sDspsnd.EnableAuxBus(id,flag);
        internal::sDspsnd.SetAuxFrontBypass(id,this->mAuxFrontBypass[id]);
    }
    outmode = this->mOutputMode;
    internal::sDspsnd.SetSoundOutputMode(outmode);

    clippingmode = this->mClippingMode;
    internal::sDspsnd.SetClippingMode(clippingmode);

    internal::sDspsnd.SetSurroundDepth(this->mSurroundDepth);

    pos = this->mSpeakerPosition;
    internal::sDspsnd.SetSurroundSpeakerPosition(pos);

    internal::sDspsnd.SetRearRatio(this->mRearRatio);
    internal::sDspsnd.SetOutputBufferCount(this->mOutputBufferCount);
    this->mDroppedFrameCount = 0;

    syncmode = this->mSyncMode;
    internal::sDspsnd.SetSyncMode(syncmode);
}

void MasterManagerImpl::Initialize(){
    if(!this->mInitialized){
        this->mCriticalSection.Initialize();
        this->mInitialized = true;
    }
}

void MasterManagerImpl::InitializeParam(){
    this->SetMasterVolume(1.0);
    this->SetSystemMasterVolume(1.0);
    this->SetAuxReturnVolume(AUX_BUS_A,1.0);
    this->SetAuxReturnVolume(AUX_BUS_B,1.0);
    this->ClearAuxCallback(AUX_BUS_A);
    this->ClearAuxCallback(AUX_BUS_B);
    this->SetAuxFrontBypass(AUX_BUS_A,false);
    this->SetAuxFrontBypass(AUX_BUS_B,false);
    this->SetRearRatio(1.0);
    this->SetSurroundDepth(1.0);
    this->SetClippingMode(CLIPPING_MODE_SOFT);
    for(int i = 0; i < 2; i++)
        this->mFxEnabled[i] = false;
    this->SetOutputBufferCount(2);
    this->SetSyncMode(SYNC_MODE_STRICT);
}

void MasterManagerImpl::RegisterAuxCallback(AuxBusId busId, AuxCallback callback, uptr userData){
    NN_TASSERT_(busId == AUX_BUS_A || busId == AUX_BUS_B);
    os::CriticalSection::ScopedLock lock(this->mCriticalSection);
    this->mAuxCallback[busId] = callback;
    this->mAuxUserData[busId] = userData;
    if(!callback){
        internal::sDspsnd.EnableAuxBus(busId,this->mFxEnabled[busId]);
    }
    else{
        internal::sDspsnd.EnableAuxBus(busId,true);
    }
}

void MasterManagerImpl::SetAuxReturnVolume(AuxBusId busId, f32 fVolume){
    NN_TASSERT_(busId == AUX_BUS_A || busId == AUX_BUS_B);
    if(this->mInitialized){
        this->mAuxVolume[busId] = fVolume;
        internal::sDspsnd.SetAuxReturnVolume(busId,fVolume);
    }
}

void MasterManagerImpl::SetSurroundSpeakerPosition(SurroundSpeakerPosition pos){
    if(pos < 2){
        this->mSpeakerPosition = pos;
        internal::sDspsnd.SetSurroundSpeakerPosition(pos);
    }
}

bool MasterManagerImpl::SetClippingMode(ClippingMode mode){
    if(dsp::CTR::IsComponentLoaded()){
        NN_TASSERT_(mode == CLIPPING_MODE_NORMAL || mode == CLIPPING_MODE_SOFT);
        memcpy(&this->mClippingMode,&mode,1);
        internal::sDspsnd.SetClippingMode(mode);
    }
    else{
        return false;
    }
}

void MasterManagerImpl::SetMasterVolume(f32 fVolume){
    if(this->mInitialized){
        this->mMasterVolume = fVolume;
        internal::sDspsnd.SetMasterVolume(this->mMasterVolume * this->mSystemMasterVolume);
    }
}

void MasterManagerImpl::SetOutputBufferCount(s32 outputBufferCount){
    int newCnt = math::max(outputBufferCount,2);
    newCnt = math::min(newCnt, 3);
    this->mOutputBufferCount = newCnt;
    internal::sDspsnd.SetOutputBufferCount(newCnt);
}

bool MasterManagerImpl::SetRearRatio(f32 ratio){
    this->mRearRatio = ((0.0 < ratio * 32768.0) * (ratio * 32768.0));
    return internal::sDspsnd.SetRearRatio(this->mRearRatio);
}

bool MasterManagerImpl::SetSoundOutputMode(OutputMode mode){
    if(dsp::CTR::IsComponentLoaded()){
        NN_TASSERT_(mode == OUTPUT_MODE_MONO || mode == OUTPUT_MODE_STEREO || mode == OUTPUT_MODE_3DSURROUND);
        memcpy(&this->mOutputMode, &mode, 1);
        internal::sDspsnd.SetSoundOutputMode(mode);
    }
    else{
        return false;
    }
}

bool MasterManagerImpl::SetSurroundDepth(f32 depth){
    if(depth < 0.0)
        depth = 0.0;
    if(depth != 1.0 && depth < 1.0 == (depth))
        depth = 1.0;
    this->mSurroundDepth = (0.0 < depth * 32767.0) * (depth * 32767.0);
    return internal::sDspsnd.SetSurroundDepth(this->mSurroundDepth);
}

void MasterManagerImpl::SetSyncMode(SyncMode mode){
    memcpy(&this->mSyncMode, &mode, 1);
    return internal::sDspsnd.SetSyncMode(mode);
}

void MasterManagerImpl::SetSystemMasterVolume(f32 volume){
    if(this->mInitialized){
        this->mSystemMasterVolume = volume;
        internal::sDspsnd.SetMasterVolume(this->mMasterVolume * this->mSystemMasterVolume);
    }
}

}
}
}