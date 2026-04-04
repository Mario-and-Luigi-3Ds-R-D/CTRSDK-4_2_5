#pragma once

#include "nn/types.h"

namespace nn{
namespace applet{
namespace CTR{

    enum AppJumpType{
        JUMP_OTHER = 0,
        JUMP_CALLER = 1,
        JUMP_SELF = 2,
    };

    enum AppletPos{
        POS_NONE = -1,
        POS_APP = 0,
        POS_APPLIB = 1,
        POS_SYS = 2,
        POS_SYSLIB = 3,
        POS_RESIDENT = 4,
        POS_MAX = 5,
    };

    enum AppletPreperationState{
        NO_PREP = 0,
        PREP_TO_LAUNCH_APP = 1,
        PREP_TO_CLOSE_APP = 2,
        PREP_TO_FORCE_CLOSE_APP = 3,
        PREP_TO_PRELOAD_APPLIB = 4,
        PREP_TO_LAUNCH_APPLIB = 5,
        PREP_TO_CLOSE_APPLIB = 6,
        PREP_TO_LAUNCH_SYS = 7,
        PREP_TO_CLOSE_SYS = 8,
        PREP_TO_PRELOAD_SYSLIB = 9,
        PREP_TO_LAUNCH_SYSLIB = 10,
        PREP_TO_CLOSE_SYSLIB = 11,
        PREP_TO_LAUNCH_RESIDENT = 12,
        PREP_TO_LEAVE_RESIDENT = 13,
        PREP_TO_DO_HOMEMENU = 14,
        PREP_TO_LEAVE_HOMEMENU = 15,
        PREP_TO_START_RESIDENT = 16,
        PREP_TO_DO_APP_JUMP = 17,
        PREP_TO_FORCE_CLOSE_SYS = 18,
        PREP_TO_LAUNCH_OTHER_SYS = 19,
        PREP_TO_JUMP_TO_APP = 20,
    };

    enum Command{
        CMD_NONE = 0,
        CMD_WAKEUP = 1,
        CMD_REQUEST = 2,
        CMD_RESPONSE = 3,
        CMD_EXIT = 4,
        CMD_MESSAGE = 5,
        CMD_HOME_BTN_SINGLE = 6,
        CMD_HOME_BTN_DOUBLE = 7,
        CMD_DSP_SLEEP = 8,
        CMD_DSP_WAKEUP = 9,
        CMD_WAKEUP_BY_EXIT = 10,
        CMD_WAKEUP_BY_PAUSE = 11,
        CMD_WAKEUP_BY_CANCEL = 12,
        CMD_WAKEUP_BY_CANCELALL = 13,
        CMD_WAKEUP_BY_POWER_BUTTON_CLICK = 14,
        CMD_WAKEUP_TO_JUMP_HOME = 15,
        CMD_REQUEST_FOR_SYS_APPLET = 16,
        CMD_WAKEUP_TO_LAUNCH_APPLICATION = 17,
        CMD_WAKEUP_BY_TERMINATION_APPLICATION = 0x40,
        CMD_WAKEUP_BY_TERMINATION_SYS_APPLICATION = 0x41,
        CMD_ACTION_MASK = 0xffff,
        CMD_FINALIZE = 0x10000,
    };

    // Will this get used..? 
    //
    // Speaking of DataManagementScene

    enum DataManagementScene{
        DATA_TOP = 0,
        DATA_STREETPASS = 1,
    };

    enum DisplayBufferMode{
        FORMAT_R8G8B8A8 = 0,
        FORMAT_R8G8B8 = 1,
        FORMAT_R5G6B5 = 2,
        FORMAT_R5G5B5A1 = 3,
        FORMAT_R4G4B4A4 = 4,
        FORMAT_UNIMPORTABLE = 0xFFFFFFFFF
    };

    enum HomeButtonState{
        HOME_BUTTON_NONE = 0,
        HOME_BUTTON_SINGLE_PRESSED = 1,
        HOME_BUTTON_DOUBLE_PRESSED = 2,
    };

    struct AppletDisplayInfo{
        uptr mAddr;
        uptr mAddrB;

    };
}
}
}