#pragma once

#include "nn/types.h"
#include "nn/fnd/fnd_InterlockedVariable.h"

namespace nn{
namespace hidlow{

class LifoRing{
    fnd::InterlockedVariable<s64> mTickWriteZero;
    fnd::InterlockedVariable<s64> mOldTickWriteZero;
    fnd::InterlockedVariable<s32> mWritePointer;
    s32 rev;
};

}
}