#pragma once

#include "nn/types.h"

namespace nn{
struct Handle {
public:
    Handle() : mHandle(0) {
    }

    explicit Handle(u32 handle) : mHandle(handle) {
    }

    bool IsValid() const {
        return mHandle != 0;
    }
private:
    u32 mHandle;
};
};