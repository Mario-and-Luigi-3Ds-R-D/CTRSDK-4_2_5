#pragma once

#include "nn/types.h"
#include "nn/Result.h"
#include "nn/fnd/fnd_DateTime.h"

namespace nn{
namespace ptm{
namespace CTR{
namespace{
const char* PORT_NAMES[] = {
    "ptm:s", // SYSTEM
    "ptm:u", // USER
    "ptm:sysm", // SYSTEM MODULE
    "ptm:play", // PLAY
    "ptm:gets", // GETS
};

}
Result Initialize();
Result Finalize();

}
}
}