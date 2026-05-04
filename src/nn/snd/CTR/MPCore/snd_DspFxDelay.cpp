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

DspFxDelay::~DspFxDelay() {

}

size_t DspFxDelay::GetRequiredMemorySize(const DspFxDelay::Param& param) {

}

bool DspFxDelay::Initialize(uptr buffer, size_t size) {

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

bool DspFxDelay::IsBufferInUse() {

}

bool DspFxDelay::AssignWorkBuffer(uptr buffer, size_t size) {

}

void DspFxDelay::ReleaseWorkBuffer() {

}
}
}
}