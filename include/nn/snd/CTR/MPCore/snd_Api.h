#pragma once

#include <nn/Result.h>
#include <nn/snd/CTR/Common/snd_Types.h>
#include <nn/snd/CTR/MPCore/snd_Voice.h>
#include <nn/os/os_LightEvent.h>

namespace nn {
namespace snd {
namespace CTR {
    static const s32 NN_SND_DSP_MAXIMUM_CYCLES = 622535;

    Result Initialize();
    Result Finalize();
    void WaitForDspSync();
    void SendParameterToDsp();
    void Sleep();
    void WakeUp();
    void OrderToWaitForFinalize();
    bool GetHeadphoneStatus();
 
} // namespace CTR
} // namespace snd
} // namespace nn