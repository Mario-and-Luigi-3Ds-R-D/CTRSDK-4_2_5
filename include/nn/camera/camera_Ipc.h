#pragma once

#include "nn/types.h"
#include "nn/Result.h"
#include "nn/camera/camera_Paramaters.h"

namespace nn{
namespace camera{
namespace CTR{
namespace detail{
namespace Camera{
extern nn::Handle sSession;

    Result Activate(u8 camera);
    Result GetActivatedCamera(u8* camera);
    Result GetSleepCamera(u8* canmera);
    Result SetSleepCamera(u8 camera);

}
}
}
}
}