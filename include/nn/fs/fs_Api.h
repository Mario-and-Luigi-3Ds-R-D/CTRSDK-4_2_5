#pragma once

#include "nn/Result.h"
#include "nn/Handle.h"
#include "nn/fs/fs_Paramaters.h"

namespace nn{
namespace fs{
    /* FileServer Things Here*/
    void Initialize();
    bool IsInitialized(void);
    Result SetPriority(int pPritority);
    Result GetPriotity(int pOut);

namespace{
    nn::Handle sFileServerSession; // 0x0
}

namespace detail{
        const char FILE_SERVER_NAME[] = "fs:USER";
}
};
}