#pragma once

#include "nn/types.h"
#include "nn/Result.h"

class ChannelManager{
public:
    ushort mCh;
    ushort rev;

public:
    ChannelManager(ushort ch){ this->mCh = ch; }
    Result CheckAddress();
    Result CheckSIOStatus();
    Result Close();
};

class FioChannelManager : public ChannelManager{

};