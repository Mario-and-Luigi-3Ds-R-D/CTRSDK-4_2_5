// Filename: snd_DspFxDelay.cpp
//
// Project: Horizon 4_2_5 Decompilation
//
// Remade by user Luigifan27

#include <nn/snd/CTR/MPCore/snd_DspFxDelay.h>
#include <nn/snd/CTR/MPCore/snd_DspFxManager.h>
#include <nn/snd/CTR/MPCore/snd_OperateMaster.h>
#include <nn/Assert.h>

namespace nn{
namespace snd{
namespace CTR{
DspFxDelay::DspFxDelay(){
    this->mBuffer = 0;
    this->mBufferPhysical = 0;
    this->mBufferSize = 0;
    this->mIsInitialized = false;
    this->mAuxBusId = (AuxBusId)-1;
    this->mIsEnabled = false;
    this->mProcessCount = 0;
}

size_t DspFxDelay::GetRequiredMemorySize(const DspFxDelay::Param& param) {
    size_t memSize = (param.mDelayTime * 1000) / 0x1318;
    size_t memSizeNew;
    if(memSize == 0)
        memSize = 1;
    if(param.mIsEnableSurround != false)
        memSizeNew = 4;
    else
        memSizeNew = 2;
    return memSizeNew * memSize * 0x280;
}

void DspFxDelay::Finalize() {
    if(this->mIsInitialized){
        this->Detach();
        this->ReleaseWorkBuffer();
        this->mIsInitialized = false;
    }
}

bool DspFxDelay::Attach(AuxBusId id) {
    NN_TASSERTMSG_(!this->mIsInitialized, "DspFxDelay is not initialized\n");
    NN_TASSERTMSG_(!this->mAuxBusId, "DspFxDelay is already attached\n");
    NN_TASSERT_(id == AUX_BUS_A || id == AUX_BUS_B);
    /*if((!this->mIsInitialized) || (this->mAuxBusId != -1) || (0 < id))
        return false;
    else
        if(DspFxManager::GetInstance()->Attach(DspFxManager::DSP_EFFECT_TYPE_DELAY,id))
            return false;
        else{
            this->mBufferPhysical >> 0x10 | this->mBufferPhysical << 0x10;
        }*/
}

void DspFxDelay::Detach() {

}

bool DspFxDelay::SetParam(const DspFxDelay::Param& param) {

}

bool DspFxDelay::Enable(bool enable){
    NN_TASSERTMSG_(!this->mBuffer || this->mBufferSize, "DspFxDelay is not initialized\n");
    if (this->mAuxBusId && this->mAuxBusId != 1)
        return false;
    if(!this->mBuffer || !this->mBufferSize)
        return false;
    DspFxDelayParams params;
    params.enable = enable;
    params.ctrl = 1;
    AuxBusId busId = this->mAuxBusId;
    bool result = DspFxManager::GetInstance()->SetDspDelayEffect(busId,&params);

    if (!enable || result)
        this->mIsEnabled = enable;
    if (!mIsEnabled)
        this->mProcessCount = internal::sDspsnd.mProcessCount;
    return result;
}


}
}
}