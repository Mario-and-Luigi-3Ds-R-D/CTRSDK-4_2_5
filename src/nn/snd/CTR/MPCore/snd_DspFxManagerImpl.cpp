// Filename: snd_DspFxManagerImpl.cpp
//
// Project: Horizon 4_2_5 Decompilation
//
// Remade by user Luigifan27

#include <nn/snd/CTR/MPCore/snd_DspFxManager.h>
#include <nn/snd/CTR/MPCore/snd_OperateMaster.h>

namespace nn {
namespace snd {
namespace CTR {

void DspFxManagerImpl::Initialize() {
    DspFxReverbParams params;

    for(int i = 0; i < 2; i++){
        params.combFrames[1] = 0;
        params.combFrames[0] = 1;
        this->SetDspDelayEffect((AuxBusId)i,(DspFxDelayParams*)&params);
        params.enable = 0;
        params.ctrl = 1;
        this->SetDspReverbEffect((AuxBusId)i,&params);
    }
}

DspFxManagerImpl* DspFxManagerImpl::Finalize(){ }

void DspFxManagerImpl::ForceUpdateParams() {
    for(int i = 0; i < 2; i++){
        AuxBusId busId = (AuxBusId)i;
        this->mDspFxDelayParams[busId].ctrl= 0xffff;
        internal::sDspsnd.SetDspDelayEffect(busId, &this->mDspFxDelayParams[busId]);
        this->mDspFxReverbParams[busId].ctrl = 0xffff;
        internal::sDspsnd.SetDspReverbEffect(busId, &this->mDspFxReverbParams[busId]);
    }
}

DspFxManagerImpl* DspFxManagerImpl::GetInstance() {
    return sInstance;
}

bool DspFxManagerImpl::SetDspDelayEffect(AuxBusId id, DspFxDelayParams* param) {
    if((param->ctrl & 1) != 0){
        this->mDspFxDelayParams[id].enable = param->enable;
    }
    if((param->ctrl & 4) != 0){
        this->mDspFxDelayParams[id].channels = param->channels;
        this->mDspFxDelayParams[id].delayFrames = param->delayFrames;
        this->mDspFxDelayParams[id].delayFeedbackGain = param->delayFeedbackGain;
        for(int i = 0; i < 2; i += 1){
            this->mDspFxDelayParams[id].aLpfCoefs[i] = param->aLpfCoefs[i];
        }
    }
    if((param->ctrl & 2) != 0){
        this->mDspFxDelayParams[id].delayBufferAddress = param->delayBufferAddress;
    }
    return internal::sDspsnd.SetDspDelayEffect(id,param);
}

bool DspFxManagerImpl::SetDspReverbEffect(AuxBusId id, DspFxReverbParams* param) {
    if(param->ctrl & 1 != 0){
        this->mDspFxReverbParams[id].enable = param->enable;
    }
    if(param->ctrl & 4 != 0){
        
    }
}

} // namespace CTR
} // namespace snd
} // namespace nn