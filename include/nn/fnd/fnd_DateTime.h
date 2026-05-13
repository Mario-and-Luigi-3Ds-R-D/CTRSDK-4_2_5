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

    DateTime() : mMilliSeconds(0) {}
    DateTime(s32 year, s32 month, s32 day, s32 hour, s32 minute, s32 second, s32 millisecond) :mMilliSeconds(DateTime::FromParamaters(year,month,day,hour,minute,second,millisecond).mMilliSeconds){ }

    DateTime FromParamaters(s32,s32,s32,s32,s32,s32,s32);
    s32 GetSecond() const;
    s32 GetMilliSecond() const;
    static DateTime GetNow();
    s32 DateToDays(s32,s32,s32);
    DateTime& operator+=(const TimeSpan& rhs);

    static s32  IsLeapYear(s32 year);

    static const DateTime MIN_DATETIME;
};
}
}

extern nn::fnd::DateTime gDt;