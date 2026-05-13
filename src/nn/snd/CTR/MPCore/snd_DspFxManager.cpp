#include "nn/snd/CTR/MPCore/snd_DspFxManager.h"

namespace nn {
namespace snd {
namespace CTR {

void DspFxManager::Initialize() {
    this->mIsAttached[0][0] = false;
    this->mIsEnabled[0][0] = false;
    this->mChannelNum[0][0] = 0;
    this->mIsAttached[1][0] = false;
    this->mIsEnabled[1][0] = false;
    this->mChannelNum[1][0] = 0;
    this->mIsAttached[0][1] = false;
    this->mIsEnabled[0][1] = false;
    this->mChannelNum[0][1] = 0;
    this->mIsAttached[1][1] = false;
    this->mIsEnabled[1][1] = false;
    this->mChannelNum[1][1] = 0;
    GetInstance()->Initialize();
}



DspFxManagerImpl* DspFxManager::Finalize(){
    return DspFxManagerImpl::GetInstance()->Finalize();
}

DspFxManager* DspFxManager::GetInstance() {
    return sInstance;
}

bool DspFxManager::Detach(s32 a, s8 b) {
    this->mIsAttached[a][b] = false;
    return true;
}

bool DspFxManager::Attach(s8 a, s8 b, s8 c) {

}

s32 DspFxManager::GetDspCycles() {

}

//
// DspManagerImpl
//

void DspFxManagerImpl::Initialize() {

}

DspFxManagerImpl* DspFxManagerImpl::Finalize(){ }

void DspFxManagerImpl::ForceUpdateParams() {
    for(int i = 0; i < 2; i++){
        int index; i = index;
        this->mDspFxDelayParams[index].mDelayTime = 0xffff;
        //internal::sDspsnd.SetDspDelayEffect(index, &this->mDspFxDelayParams[index].mDelayTime);
        this->mDspFxReverbParams[index].mEarlyReflectionTime = 0xffff;
        //internal::sDspsnd.SetDspReverbEffect(index, &this->mDspFxReverbParams[index].mEarlyReflectionTime);
    }
}

DspFxManagerImpl* DspFxManagerImpl::GetInstance() {
    return sInstance;
}

void DspFxManagerImpl::SetDspDelayEffect() {

}

void DspFxManagerImpl::SetDspReverbEffect() {

}

} // namespace CTR
} // namespace snd
} // namespace nn