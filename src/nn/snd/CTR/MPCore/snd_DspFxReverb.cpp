#include "nn/snd/CTR/MPCore/snd_DspFxReverb.h"

namespace nn {
namespace snd {
namespace CTR {

DspFxReverb::FilterSize DspFxReverb::sDefaultFilterSize;

DspFxReverb::Param::Param() {

}

DspFxReverb::DspFxReverb() {

}

DspFxReverb::~DspFxReverb() {

}

size_t DspFxReverb::GetRequiredMemorySize(const DspFxReverb::Param& param) {

}

bool DspFxReverb::Initialize(uptr buffer, size_t size) {

}

void DspFxReverb::Finalize() {

}

bool DspFxReverb::Attach(AuxBusId id) {

}

void DspFxReverb::Detach() {

}

bool DspFxReverb::SetParam(const DspFxReverb::Param& param) {

}

bool DspFxReverb::Enable(bool enable) {

}

bool DspFxReverb::IsBufferInUse() {

}

bool DspFxReverb::AssignWorkBuffer(uptr buffer, size_t size) {

}

void DspFxReverb::ReleaseWorkBuffer() {

}

} // namespace CTR
} // namespace snd
} // namespace nn