#pragma once

#include "nn/Result.h"
#include "nn/fs/fs_IPositionable.h"

namespace nn{
namespace fs{

class IInputStream : public IPositionable{
public:
    int flag1; // IPositionable

    virtual ~IInputStream(){}
};

class IOutputStream : public IPositionable{
public:
    int flag1; // IPositionable

    virtual ~IOutputStream(){}
};

class IStream : public IInputStream, public IOutputStream{
public:
    virtual ~IStream(){}
};

} // fs
} // nn