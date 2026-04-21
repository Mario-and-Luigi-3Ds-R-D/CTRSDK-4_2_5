#pragma once

#include "nn/Result.h"
#include "nn/Handle.h"
#include "nn/fs/fs_Paramaters.h"

namespace nn{
namespace fs{
namespace detail{
        const char PORT_NAME_USER[] = "fs:USER";
        const char PORT_NAME_LOADER[] = "fs:LDR";
} // detail
namespace{
    nn::Handle sFileServerSession; // 0x0
}
    /* FileServer Things Here*/
    void Initialize();
    Result GetPriotity(int pOut);

    /* FileSevrer Inlines*/

    inline Result IsInitialized(){
        return sFileServerSession != 0;
    }

    }
}