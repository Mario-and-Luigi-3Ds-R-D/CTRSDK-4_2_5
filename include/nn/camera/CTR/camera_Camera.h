#pragma once

#include <nn/camera/CTR/camera_Paramaters.h>
#include <nn/Handle.h>
#include <nn/Result.h>

namespace nn{
namespace camera{
namespace CTR{
namespace detail{

class Camera{
public:
    static Result Activate(u8 camera);
    static Result GetActivatedCamera(u8* camera);
    static Result GetSleepCamera(u8* canmera);
    static Result SetSleepCamera(u8 camera);

    static nn::Handle sSession;
};

}
}
}
}