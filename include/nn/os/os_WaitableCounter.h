#pragma once

#include "nn/types.h"
#include "nn/os/os_Api.h"

namespace nn{ 
namespace os{
    class WaitableCounter{
    public:
        ValueType mValue;
        static nn::Handle sHandle;

        void Initialize();
    };
}
}