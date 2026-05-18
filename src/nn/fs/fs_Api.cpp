#include <nn/fs/fs_Api.h>
#include <nn/fs/fs_Paramaters.h>
#include <nn/fs/CTR/MPCore/fs_UserFileSystem.h>
#include <nn/fs/fs_FileSystemBase.h>
#include <nn/err/CTR/err_Api.h>
#include <nn/cfg/CTR/cfg_Api.h>
#include <nn/srv/srv_Api.h>

#include <string.h>

namespace nn{
namespace fs{
    nn::Handle sFileServerSession; // 0x0
namespace{
    detail::FileSystemBase sFileSystemBase;
}
namespace{
    detail::FileSystemBaseImpl sFileSystemBaseImpl;
}

void InitializeLatencyEmulation(void) {

}

void Initialize(){
    size_t nameLen;
    if(!IsInitialized()){
        Result res; res = srv::Initialize();
        if(res.mResult != 0x8a067f9){
            NN_ERR_THROW_FATAL_ALL(res);
        }

        nameLen = strlen(detail::PORT_NAME_USER);
        res = srv::GetServiceHandle(&sFileServerSession, detail::PORT_NAME_USER, nameLen, 0);
        NN_ERR_THROW_FATAL_ALL(res);
        CTR::MPCore::detail::UserFileSystem::Initialize(sFileServerSession);
        sFileSystemBase.Initialize(&sFileSystemBaseImpl);
        detail::RegisterGlobalFileSystemBase(&sFileSystemBase);
        res = SetPriority(0);
        NN_ERR_THROW_FATAL_ALL(res);
    }
}

}
}