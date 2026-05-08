#include "nn/snd/CTR/MPCore/snd_DspFxManager.h"

namespace nn {
namespace snd {
namespace CTR {

void DspFxManager::Initialize() {
    DspFxManagerImpl* pFxManagerImpl;
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
    pFxManagerImpl->GetInstance();
    pFxManagerImpl->Initialize();
}

DspFxManager* sInstance;

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

DspFxManagerImpl* DspFxManagerImpl::Finalize() {

}

void DspFxManagerImpl::ForceUpdateParams() {

}

DspFxManagerImpl* DspFxManagerImpl::GetInstance() {

}

void DspFxManagerImpl::SetDspDelayEffect() {

}

void DspFxManagerImpl::SetDspReverbEffect() {

}

} // namespace CTR
} // namespace snd
} // namespace nn