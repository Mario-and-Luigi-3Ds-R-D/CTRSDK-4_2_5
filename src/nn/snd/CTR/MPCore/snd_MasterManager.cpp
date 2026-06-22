#include <nn/snd/CTR/MPCore/snd_MasterManager.h>
#include <nn/snd/CTR/MPCore/snd_Api.h>
#include <nn/cfg/CTR/cfg_Api.h>
#include <nn/cfg/CTR/cfg_DetailApi.h>
#include <nn/cfg/CTR/cfg_Sound.h>
#include <nn/Assert.h>

namespace nn {
namespace snd {
namespace CTR {
namespace internal{
    CTR::MasterManager sMasterManager;
}

void MasterManager::AuxUserCallback(AuxBusId busId, uptr data){
    NN_TASSERT_((busId != AUX_BUS_A) && (busId != AUX_BUS_B));
    if(this->mInitialized){
        MasterManagerImpl::GetInstance()->AuxUserCallback(busId,data);
    }
}

void MasterManager::ExecuteEffect(AuxBusId busId, uptr data){
    os::CriticalSection::ScopedLock lock(this->mFxCriticalSection);
    AuxBusData auxBusData;
    auxBusData.frontRight = (s32*)data + 0x280;
    auxBusData.rearLeft = (s32*)data + 0x500;
    auxBusData.rearRight = (s32*)data + 0x780;
    auxBusData.frontLeft = (s32*)data;
    if(!this->mFxSet[busId].mpFxDelay){
        if(!this->mFxSet[busId].mpFxReverb){
            this->mFxSet[busId].mpFxReverb->UpdateBuffer((uptr)&auxBusData);
        }
    }
    else{
        this->mFxSet[busId].mpFxDelay->UpdateBuffer((uptr)&auxBusData);
    }
}

void MasterManager::Finalize(){
    if(this->mInitialized){
        MasterManagerImpl::GetInstance()->Finalize();
        this->mFxCriticalSection.Finalize();
        this->mInitialized = false;
    }
}

s32 MasterManager::GetDspCycles(){
    s32 cycle = 0xcd78;
    switch(this->mOutputMode){
    case OUTPUT_MODE_MONO:
        cycle = 0xdf0c;
        break;
    case OUTPUT_MODE_STEREO:
        cycle = 0xd930;
        break;
    case OUTPUT_MODE_3DSURROUND:
        if(GetHeadphoneStatus())
            cycle = 0x30BB0;
        else
            cycle = 0x37140;
        break;
    }
    switch(this->mOutputMode){
    case CLIPPING_MODE_NORMAL:
        cycle += 0x400 + 0x1DC;
        break;
    case CLIPPING_MODE_SOFT:
        cycle += 0x2000 + 0x710;
        break;
    }
    return cycle;
}

void MasterManager::Initialize(){
    cfg::CTR::SoundSettingCfgData cfgData;
    u8 mode;
    Result res;
    if(!this->mInitialized){
        this->mInitialized = true;
        MasterManagerImpl::GetInstance()->Initialize();
        this->mMasterVolume = 1.0f;
        this->mSystemMasterVolume = 1.0f;
        this->mAuxVolume[0] = 1.0f;
        this->mAuxVolume[1] = 1.0f;
        this->mAuxCallback[0] = 0;
        this->mAuxCallback[1] = 0;
        this->mAuxUserData[0] = 0;
        this->mAuxUserData[1] = 0;
        this->mAuxFrontBypass[0] = 0;
        this->mAuxFrontBypass[1] = 0;
        this->mRearRadio = 1.0f;
        this->mSurroundDepth = 1.0f;
        this->mClippingMode = CLIPPING_MODE_SOFT;
        MasterManagerImpl::GetInstance()->InitializeParam();
        cfg::CTR::Initialize();
        res = cfg::CTR::detail::GetConfig(&cfgData,1,0x70001);
        if(res.IsSuccess()){
            mode = cfgData.soundOutputMode != 0;
            if(cfgData.soundOutputMode == 1)
                mode = OUTPUT_MODE_STEREO;
            if(cfgData.soundOutputMode == 2)
                mode = OUTPUT_MODE_3DSURROUND;
        }
        else{
            mode = OUTPUT_MODE_STEREO;
        }
        this->mOutputMode = (OutputMode)mode;
        MasterManagerImpl::GetInstance()->SetSoundOutputMode((OutputMode)mode);
        this->mDroppedFrameCount = 0;
        for(int i = 0; i < 2; i++){
            this->mFxSet[i].mpFxDelay = 0;
            this->mFxSet[i].mpFxReverb = 0;
        }
        this->mFxCriticalSection.Initialize();
    }
}

void MasterManager::SetOutputBufferCount(s32 outputBufferCount){
    return MasterManagerImpl::GetInstance()->SetOutputBufferCount(outputBufferCount);
}

void MasterManager::SetMasterVolume(float fVolume){
    if(this->mInitialized){
        MasterManagerImpl::GetInstance()->SetMasterVolume(fVolume);
    }
}


void MasterManager::SetSurroundSpeakerPosition(SurroundSpeakerPosition pos){
    this->mSpeakerPosition = pos;
    return MasterManagerImpl::GetInstance()->SetSurroundSpeakerPosition(pos);
}
bool MasterManager::SetSurroundDepth(f32 depth){
    this->mSurroundDepth = depth;
    return MasterManagerImpl::GetInstance()->SetSurroundDepth(depth);
}

void MasterManager::SetIsHeadphoneConnected(bool flag){
    this->mIsHeadsetConnected = flag;
    MasterManagerImpl::GetInstance()->SetIsHeadphoneConnected(flag);
}

void MasterManager::UpdateDroppedSoundFrameCount(){
    s32 frameCnt = internal::sDspsnd.GetDroppedFrameCount();
    if(0 <= frameCnt){
        this->mDroppedFrameCount += frameCnt;
    }
}
}
}
}