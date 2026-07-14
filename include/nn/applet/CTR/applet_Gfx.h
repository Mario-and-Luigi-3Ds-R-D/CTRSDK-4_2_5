#pragma once

#include <nn/applet/CTR/applet_Ipc.h>
#include <nn/applet/CTR/applet_Api.h>
#include <nn/applet/CTR/applet_Paramaters.h>

namespace nn{
namespace applet{
namespace CTR{
namespace detail{

    void GetDisplayInfo(AppletDisplayInfo* pInfo);
    void CalcCaptureBufferInfo(CaptureBufferInfo *cInfo);
}
}
}
}