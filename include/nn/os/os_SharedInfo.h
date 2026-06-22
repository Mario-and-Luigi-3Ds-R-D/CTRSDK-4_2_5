#pragma once

#include "nn/os/os_Tick.h"

namespace nn{
namespace os{

struct RtcSwcInfo{
    s64 rtcBaseMilliSeconds;
    Tick rtcBaseTicks;
    s64 rtcTicksPerSeconds;
    s64 rtcDiffMilliSeconds;
};

struct WritableSharedInfo {
    s32 rtcValidNumber;
    u8 targetHardware;
    u8 mcuTargetInfo;
    u8 mcuInfoRegisters_10;
    u8 reserved_0x007[25];
    RtcSwcInfo rtcSwcInfo[2];
    u8 wirelessInfo[16];
    u8 reserved_0x070[16];
    f32 svr2Volume;
    bool displayModeLockFlag;
    u8 batteryState;
    bit8 writeFlags;
    u8 reserved_0x088[25];

};

inline WritableSharedInfo* GetWritableSharedInfo(){
    return (WritableSharedInfo*)0x1ff81000;
}

}
}