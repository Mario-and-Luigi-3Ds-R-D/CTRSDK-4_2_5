#pragma once

#include "nn/types.h"

namespace nn{
namespace applet{

    enum AppJumpType : u8{
        JUMP_OTHER = 0,
        JUMP_CALLER = 1,
        JUMP_SELF = 2,
    };

    enum AppletPos : u8{
        POS_NONE = -1,
        POS_APP = 0,
        POS_APPLIB = 1,
        POS_SYS = 2,
        POS_SYSLIB = 3,
        POS_RESIDENT = 4,
        POS_MAX = 5,
    };

    enum AppletPreperationState : u8{
        NO_PREP = 0,
        PREP_TO_LAUNCH_APP = 1,
    };

    /*struct AppletDisplayInfo{
        uptr mAddr;
        uptr mAddrB;

    };*/
}
}