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

    bool operator==(int other) const {
        return mHandle == (u32)other;
    }
    bool operator!=(int other) const {
        return mHandle != (u32)other;
    }
    Handle& operator=(int other) {
        mHandle = (u32)other;
        return *this;
    }
    Handle& operator=(u32 other) {
        mHandle = other;
        return *this;
    }
    Handle& operator=(nn::Handle* other) {
        mHandle = (u32)other;
        return *this;
    }
private:
    u32 mHandle;
};
}