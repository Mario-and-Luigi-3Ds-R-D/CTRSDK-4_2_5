#pragma once

#include "nn/fs/fs_IPositionable.h"

namespace nn{
namespace fs{

class IInputStream{
public:
    int flag1; // IPositionable

    virtual ~IInputStream();
};

class IOutputStream{
public:
    int flag1; // IPositionable

    virtual ~IOutputStream();
};

class IStream{
    IInputStream mInputStream;
    IOutputStream mOutputStream;
public:
    virtual ~IStream();
};

} // fs
} // nn