#pragma once

#include "nn/types.h"
// This is literally it, no joke.
namespace nn{
namespace fnd{

class TimeSpan{
public:
    TimeSpan(){};
    s64 mNanoSeconds;
    
    static s64 MultiplyRightShift(const s64 x, const s64 y){
        const u64 x_lo = x & 0xffffffff;
        const s64 x_hi = x >> 32;

        const u64 y_lo = y & 0xffffffff;
        const s64 y_hi = y >> 32;

        const s64 z = x_hi * y_lo + ((x_lo * y_lo) >> 32);
        const s64 z_lo = z & 0xffffffff;
        const s64 z_hi = z >> 32;

        return x_hi * y_hi + z_hi + (static_cast<s64>(x_lo * y_hi + z_lo) >> 32);
    }

    s64 GetNanoSeconds() const{
        return this->mNanoSeconds;
    }

    s64 DivideNanoSeconds(s64 magic, s32 rightShift) const{
        s64 n = MultiplyRightShift(mNanoSeconds, magic);
        if (magic < 0){
            n += mNanoSeconds;
        }
        n >>= rightShift;
        return n + (static_cast<u64>(mNanoSeconds) >> 63);
    } // 100%

    s64 GetMilliSeconds() const{
        return DivideNanoSeconds(0x431bde82d7b634dbLL, 18); 
    }

    /* Macros Needed elsewhere, and makes it easier for DateTime. */

    static TimeSpan FromNanoSeconds(s64 nanoSeconds) { 
        TimeSpan ret; ret.mNanoSeconds = nanoSeconds; 
        return ret; 
    }

    static TimeSpan FromMilliSeconds(s64 milliSeconds) {
        return FromNanoSeconds(milliSeconds * 1000 * 1000); 
    }

struct ZeroOnlyTag{

};
};

}
}