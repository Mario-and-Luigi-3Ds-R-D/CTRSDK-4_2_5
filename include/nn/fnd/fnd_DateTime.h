#pragma once

#include "nn/types.h"
#include "nn/fnd/fnd_TimeSpan.h"

namespace nn{
namespace fnd{
class DateTime{
public:
    s64 mMilliSeconds;

    static const s32 MILLISECONDS_DAY = 1000 * 60 * 60 * 24;

    // Funni macro hack
    inline s32 MilliSecondsOnDay(s64 milliSeconds){
        s64 ms = milliSeconds + (730119LL * MILLISECONDS_DAY);
        return ms % MILLISECONDS_DAY;
    }

    DateTime FromParamaters(s32,s32,s32,s32,s32,s32,s32);
    s32 GetSecond(); // 100%
    s32 GetMilliSecond(); // 100%
    DateTime GetNow(); // ASM
    DateTime(s32 year, s32 month, s32 day, s32 hour, s32 minute, s32 second, s32 millisecond) :mMilliSeconds(DateTime::FromParamaters(year,month,day,hour,minute,second,millisecond).mMilliSeconds){ }
    s32 DateToDays(s32,s32,s32); // ASM
    DateTime& operator+=(const TimeSpan& rhs);

    static const DateTime MIN_DATETIME;
};
}
}

extern nn::fnd::DateTime gDt;