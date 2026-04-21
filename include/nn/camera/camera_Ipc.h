#pragma once

#include "nn/types.h"
#include "nn/Result.h"
#include "nn/camera/camera_Paramaters.h"

namespace nn{
namespace camera{
namespace CTR{
namespace detail{
namespace Camera{
extern const nn::Handle sSession;
    Result Activate(CameraSelect camera);
    Result GetActivatedCamera(CameraSelect* camera);
    Result GetSleepCamera(CameraSelect* camera);
    Result SetSleepCamera(CameraSelect camera);

}
}
}
}
}