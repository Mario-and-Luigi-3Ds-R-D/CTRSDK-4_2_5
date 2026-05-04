#pragma once

#include "nn/hid/CTR/hid_Gyroscope.h"

namespace nn{
namespace hid{
namespace CTR{
namespace detail{
namespace Ipc{
    Result EnableAccelerometer();
    Result DisableAccelerometer();
    Result EnableGyroscopeLow();
    Result DisableGyroscopeLow();
    Result GetGyroscopeLowCalibrateParam(GyroscopeLowCalibrateParam *);
    Result GetGyroscopeLowRawToDpsCoefficient();
    Result GetIPCHandles(Handle *pSharedMemoryHandle,Handle *pPadEvent,Handle *pTouchPanelEvent,Handle *pAccelerometerEvent,Handle *pGyroscopeLowEvent,Handle *pDebugPadEvent);

extern nn::Handle sSession;
}
}
}
}
}