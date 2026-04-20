#pragma once

#include "nn/Result.h"
#include "nn/fs/fs_IPositionable.h"

namespace nn{
namespace fs{

class IInputStream : public virtual nn::fs::IPositionable{
public:
    virtual ~IInputStream() {}
};

class IOutputStream : public virtual nn::fs::IPositionable{
public:
    virtual ~IOutputStream() {}
};

class IStream : public nn::fs::IInputStream, public nn::fs::IOutputStream{
public:
    virtual ~IStream() {}
};

} // fs
} // nn