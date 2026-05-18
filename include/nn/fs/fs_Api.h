#pragma once

#include "nn/Result.h"
#include "nn/Handle.h"
#include "nn/fs/fs_Paramaters.h"
#include "nn/fs/fs_IpcFile.h"

namespace nn{
namespace fs{
namespace detail{
    const char PORT_NAME_LOADER[] = "fs:LDR";
    const char PORT_NAME_USER[] = "fs:USER";

} // detail
    extern nn::Handle sFileServerSession; // 0x0

    /* FileServer Things Here*/

    void Initialize();
    Result GetPriortity(int pOut);
    void InitializeLatencyEmulation();

    /* Inlines */
    inline bool IsInitialized(){
        return sFileServerSession.IsValid();
    }

    inline Result SetPriority(s32 pri){
        ipc::FileSystem sys = detail::GetIpcFileSystem();
        Result res = sys.SetPriority(pri);
    }

}
}