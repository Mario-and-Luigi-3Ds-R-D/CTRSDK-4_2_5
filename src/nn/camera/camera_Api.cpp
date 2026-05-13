#include <nn/camera/camera_Api.h>
#include <nn/camera/camera_Ipc.h>

namespace nn{
namespace camera{
namespace CTR{
namespace detail{
namespace{
    u8 isInitialized;
    u8 leaveApplication;

}

Result ArriveApplication(){
    Result ipc;
    if((detail::isInitialized != 0) && (ipc = Camera::Activate(detail::leaveApplication), ipc.mResult == 0xC9405001)){
        Camera::SetSleepCamera(detail::leaveApplication);
    }
}

Result LeaveApplication(){

}

}
}
}
}