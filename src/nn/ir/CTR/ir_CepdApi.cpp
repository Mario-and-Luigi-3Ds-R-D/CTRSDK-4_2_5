// Filename: ir_CepdApi.cpp
//
// Project: Horizon CTRSDK

#include <nn/ir/CTR/ir_CepdApi.h>
#include <nn/hidlow.h>
#include <nn/srv.h>
#include <nn/math.h>
#include <nn/os.h>

namespace nn{
namespace ir{
namespace CTR{

nn::os::Thread cepdThread;
nn::hidlow::CTR::ExtraPadLifoRing extraPadLifoRing;

nn::srv::LightEventNotificationHandler notificationConnectionHandler;
nn::srv::LightEventNotificationHandler notificationSamplingHandler;

const nn::fnd::TimeSpan PACKET_LOSS_CALC_TIME = nn::fnd::TimeSpan::FromMilliSeconds(1000);

const nn::fnd::TimeSpan TIMEOUT_TO_READ_DATA = nn::fnd::TimeSpan::FromMilliSeconds(20);

const nn::fnd::TimeSpan TIMEOUT_TO_WRITE_DATA = nn::fnd::TimeSpan::FromMilliSeconds(450);

const nn::fnd::TimeSpan TIMEOUT_TO_ERASE_DATA = nn::fnd::TimeSpan::FromMilliSeconds(2000);

const nn::fnd::TimeSpan TIMEOUT_TO_GET_FIRM_VERSION =  nn::fnd::TimeSpan::FromMilliSeconds(100);

const s32 sTangent = static_cast<s32>(nn::math::TanDeg(60.0) );

CepdStatus CepdGetStatus(){
    return cepdStatus;
}

}
}
}