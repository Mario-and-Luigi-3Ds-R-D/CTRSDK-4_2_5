#pragma once

#include "nn/types.h"
#include "nn/Handle.h"
#include "nn/Result.h"

namespace nn{
namespace ndm{
namespace CTR{
namespace detail{
namespace Interface{

extern nn::Handle sSession;

Result OverrideDefaultDaemons(uint);
}
}
}
}
}