#pragma once

#include "nn/applet/applet_Paramaters.h"

namespace nn { 
namespace applet {
namespace CTR {

    void GetAppletType();
    void GetAttribute();
    void GetHomeButtonState();
    void GetId();
    void GetMessageCommand();
    void GetSleepNotificationState();
    void GetTransitionType();

namespace detail{

    void GetDisplayInfo(nn::applet::CTR::AppletDisplayInfo* pInfo);
    void GetInitialParamBuffer();
    void GetOrderToCloseState();
    void GetPowerButtonState();
    void GetSleepSysState();
    
}
namespace{

    u8 isAppletMode;
    u8 isActive;
    u8 sAbsoluteHomeButtonState;
    u8 sSleepSysState;
    u8 sShutdownState;
    u8 sPowerButtonState;
    u8 sOrderToCloseState;
    u8 sIsToCallPowerButtonCallback;
    u8 sIsReceivedWakeupByCancelFlag;
    u8 sPrevTransitionType;

}
}
}
}