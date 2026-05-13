#include <nn/snd/CTR/MPCore/snd_DspFxDelay.h>

namespace nn{
namespace snd{
namespace CTR{
DspFxDelay::DspFxDelay(){
    this->mBuffer = 0;
    this->mBufferPhysical = 0;
    this->mBufferSize = 0;
    this->mIsInitialized = false;
    this->mAuxBusId = -1;
    this->mIsEnabled = false;
    this->mProcessCount = 0;
}

size_t DspFxDelay::GetRequiredMemorySize(const DspFxDelay::Param& param) {
    size_t memSize = (param.mDelayTime * 1000) / 0x1318;
    size_t memSizeNew;
    if(memSize == 0){
        memSize = 1;
    } 
    if(param.mIsEnableSurround != false){
        memSizeNew = 4;
    } else{
        memSizeNew = 2;
    } return memSizeNew * memSize * 0x280;
}

void DspFxDelay::Finalize() {

}

bool DspFxDelay::Attach(AuxBusId id) {

}

void DspFxDelay::Detach() {

}

bool DspFxDelay::SetParam(const DspFxDelay::Param& param) {

}

bool DspFxDelay::Enable(bool enable) {

}


}
}
}