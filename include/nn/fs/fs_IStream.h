#pragma once

#include "nn/Result.h"
#include "nn/fs/fs_IPositionable.h"

namespace nn{
namespace fs{

class IInputStream : public virtual nn::fs::IPositionable{
public:
    virtual ~IInputStream() { }
    virtual Result TryRead(s32* pOut, void* buffer, size_t size) = 0;
    virtual s32 Read(void* buffer, size_t size) = 0;
};

class IOutputStream : public virtual nn::fs::IPositionable{
public:
    virtual ~IOutputStream() { }
    virtual Result TryWrite(s32* pOut, const void* buffer, size_t size, bool flush) = 0;
    virtual s32 Write(const void* buffer, size_t size, bool flush) = 0;
    virtual Result TrySetSize(s64 size) = 0;
    virtual void SetSize(s64 size) = 0;
};

class IStream : public nn::fs::IInputStream, public nn::fs::IOutputStream{
public:
    virtual ~IStream() { }
};

} // fs
} // nn