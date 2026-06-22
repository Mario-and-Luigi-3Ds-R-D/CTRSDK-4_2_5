#pragma once

#include "nn/fnd/fnd_TimeSpan.h"

namespace nn{
namespace svc{
    s64 GetSystemTick();
}
namespace os{

class Tick{
public:
    s64 mTick;

    explicit Tick(s64 tick = 0) : mTick(tick) {}
    Tick(nn::fnd::TimeSpan span);
    static Tick GetSystemCurrent();

    operator s64() const { return mTick; }
    operator nn::fnd::TimeSpan() const;
    nn::fnd::TimeSpan ToTimeSpan() const;
};

inline Tick Tick::GetSystemCurrent(){
    return Tick(nn::svc::GetSystemTick());
}

}
}