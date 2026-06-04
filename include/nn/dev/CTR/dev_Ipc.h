#pragma once

#include "nn/Handle.h"
#include "string.h"

namespace nn{
namespace dev{
namespace CTR{
class Dev{
public:
    Handle mSession;

    Dev(Handle session){
        Handle ses_local = session;
        memcpy(this,&ses_local,4);
    }
};
}
}
}