#pragma once

#include "nn/Handle.h"
#include "nn/fnd/fnd_TimeSpan.h"

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

    enum PowerButtonState {
        POWER_BUTTON_STATE_NONE=0,
        POWER_BUTTON_STATE_CLICK=1
    };

    enum OrderToCloseState {
        ORDER_TO_CLOSE_STATE_NONE=0,
        ORDER_TO_CLOSE_STATE_RECEIVED=1
    };

    enum Notification {
        NOTIFICATION_NONE=0,
        NOTIFICATION_HOME_BUTTON_1=1,
        NOTIFICATION_HOME_BUTTON_2=2,
        NOTIFICATION_SLEEP_QUERY=3,
        NOTIFICATION_SLEEP_CANCELED_BY_OPEN=4,
        NOTIFICATION_SLEEP_ACCEPTED=5,
        NOTIFICATION_AWAKE=6,
        NOTIFICATION_SHUTDOWN=7,
        NOTIFICATION_POWER_BUTTON_CLICK=8,
        NOTIFICATION_POWER_BUTTON_CLEAR=9,
        NOTIFICATION_TRY_SLEEP=10,
        NOTIFICATION_ORDER_TO_CLOSE=11
    };

    enum WakeupState {
        WAKEUP_BY_TIMEOUT=-1,
        WAKEUP_SKIP=0,
        WAKEUP_TO_START=1,
        WAKEUP_BY_EXIT=2,
        WAKEUP_BY_PAUSE=3,
        WAKEUP_BY_CANCEL=4,
        WAKEUP_BY_CANCELALL=5,
        WAKEUP_BY_POWER_BUTTON_CLICK=6,
        WAKEUP_TO_JUMP_HOME=7,
        WAKEUP_TO_JUMP_APPLICATION=8,
        WAKEUP_TO_LAUNCH_APPLICATION=9,
        WAKEUP_STATE_MAX=63
    };

    enum QueryReply {
        REPLY_REJECT=0,
        REPLY_ACCEPT=1,
        REPLY_LATER=2
    };

    enum SleepNotificationState {
        NOTIFY_NONE=0,
        NOTIFY_SLEEP_QUERY=1,
        NOTIFY_SLEEP_ACCEPT=2,
        NOTIFY_SLEEP_REJECT=3,
        NOTIFY_SLEEP_ACCEPTED=4,
        NOTIFY_AWAKE=5
    };

    enum SleepSysState {
        SLEEP_SYS_STATE_NONE=0,
        SLEEP_SYS_STATE_QUERY=1,
        SLEEP_SYS_STATE_ACCEPTED=2,
        SLEEP_SYS_STATE_AWAKE=3,
        SLEEP_SYS_STATE_CANCELED=4
    };

    enum ShutdownState {
        SHUTDOWN_STATE_NONE=0,
        SHUTDOWN_STATE_RECEIVED=1
    };

    enum TransitionType {
        TRANSITION_NONE = 0,
        TRANSITION_START_APP = 1,
        TRANSITION_PRELOAD_APPLIB = 2,
        TRANSITION_CANCEL_APPLIB = 3,
        TRANSITION_START_APPLIB = 4,
        TRANSITION_START_SYS = 5,
        TRANSITION_START_SYSLIB = 6,
        TRANSITION_PRELOAD_RES = 7,
        TRANSITION_START_RES = 8,
        TRANSITION_CLOSE_APP = 9,
        TRANSITION_ORDER_CLOSE_APP = 10,
        TRANSITION_CLOSE_APPLIB = 11,
        TRANSITION_CLOSE_SYSLIB = 12,
        TRANSITION_PAUSE_APPLIB = 13,
        TRANSITION_JUMP_HOME = 14,
        TRANSITION_LEAVE_HOME = 15,
        TRANSITION_LEAVE_RES = 16,
        TRANSITION_ORDER_CLOSE_SYS = 17,
        TRANSITION_JUMP_APP = 18,
        TRANSITION_ENABLE_APPLET = 98,
        TRANSITION_SKIP = 99
    };

    struct AppletDisplayInfo{
        uptr mAddr;
        uptr mAddrB;

    };
/* Externs To make things work*/

    typedef enum WakeupState AppletWakeupState;
    typedef void (*AppletAwakeCallback)(uptr);
    typedef QueryReply (*AppletSleepQueryCallbackFunc)(uptr);
    typedef void (*AppletAwakeCallback)(uptr);
    typedef int (*AppletSleepQueryCallback)(uptr);
    typedef void (*AppletSysSleepAcceptedCallback)(uptr);
    typedef Notification AppletNotification;
    typedef QueryReply AppletQueryReply;
    typedef bit32 AppletAttr;
    typedef bit32 AppletId;

    extern const nn::Handle HANDLE_NONE;

    const nn::fnd::TimeSpan WAIT_INFINITE = nn::fnd::TimeSpan::FromNanoSeconds((s64)-1);
    const nn::fnd::TimeSpan NO_WAIT = nn::fnd::TimeSpan::FromNanoSeconds(0);
}
}
}