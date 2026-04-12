#pragma once

#include "nn/Result.h"
#include "nn/applet/applet_Paramaters.h"

namespace nn{
namespace applet{
namespace CTR{
namespace detail{

    void LockAndConnect(); // applet_Connect.h
    void DisconnectAndUnlock();
    void GetDisplayInfo(AppletDisplayInfo* pInfo);

}
}
}
}