#pragma once

#include "nn/types.h"
#include "nn/Handle.h"
#include "nn/Result.h"

namespace nn{
namespace ndm{
namespace CTR{
namespace detail{
namespace Interface{

extern const nn::Handle sSession;

Result OverrideDefaultDaemons(uint);
}
}
}
}
}