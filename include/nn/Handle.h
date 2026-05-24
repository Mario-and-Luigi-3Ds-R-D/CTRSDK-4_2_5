#pragma once

#include "nn/types.h"
#include "nn/Result.h"

typedef struct nnHandle{
    bit32 value;
} nnHandle;


namespace nn{
namespace{
    const nnHandle PSEUDO_HANDLE_CURRENT_THREAD  = {0xFFFF8000};
    const nnHandle PSEUDO_HANDLE_CURRENT_PROCESS = {0xFFFF8001};
    const nnHandle INVALID_HANDLE_VALUE = {0};
}
struct Handle {
public:
    Handle ()
        : mHandle (0)
    {}
    Handle (nnHandle handle)
        : mHandle (handle.value)
    {}
    Handle (bit32 value)
        : mHandle (value)
    {}

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

    bool operator== (const Handle& rhs) const { return this->mHandle == rhs.mHandle; }
    bool operator!= (const Handle& rhs) const { return this->mHandle != rhs.mHandle; }
    operator nnHandle () const{
        nnHandle result = {mHandle};
        return result;
    }

    bit32 mHandle;
};
}