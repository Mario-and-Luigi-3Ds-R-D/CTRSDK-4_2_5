#pragma once

#include "nn/types.h"

namespace nn{
namespace os{
namespace CTR{
namespace{
    void DefaultTerminateHandler();
    void DefaultUnexpectedHandler();
}

void SetupThreadCppExceptionEnvironment();

}
}
}