#include <nn/camera/camera_Api.h>
#include <nn/camera/camera_Ipc.h>

namespace nn{
namespace camera{
namespace CTR{
namespace detail{
namespace{
    bool isInitialized;
    bool leaveApplication;

}

Result ArriveApplication(){
    Result ipc;
    if((isInitialized != 0) && (ipc = Camera::Activate(leaveApplication), ipc.mResult == 0xC9405001)){
        Camera::SetSleepCamera(leaveApplication);
    }
}

Result LeaveApplication(){

}

}
}
}
}