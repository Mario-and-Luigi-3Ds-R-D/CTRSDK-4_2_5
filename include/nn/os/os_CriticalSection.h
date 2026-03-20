#pragma once

#include "nn/types.h"

namespace nn{

namespace os{

namespace CriticalSection{

    void Enter(int);
    void Leave(int);


} // CriticalSection
} // os
}; // nn