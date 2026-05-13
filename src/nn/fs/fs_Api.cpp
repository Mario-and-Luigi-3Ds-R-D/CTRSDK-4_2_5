#include <nn/fs/fs_Api.h>
#include <nn/fs/fs_Paramaters.h>
//#include <nn/fs/detail/fs_IpcFileSystem.h>
#include <nn/fs/CTR/MPCore/fs_UserFileSystem.h>
#include <nn/fs/fs_FileSystemBase.h>
#include <nn/err/CTR/err_Api.h>
#include <nn/cfg/CTR/cfg_Api.h>
#include <nn/srv/srv_Api.h>
#include <string.h>

namespace nn{
namespace fs{
namespace{
    nn::Handle sFileServerSession; // 0x0
}
namespace{
//    detail::FileSystemBase sFileSystemBase;
}
namespace{
//    detail::FileSystemBase sFileSystemBaseImpl;
}
namespace detail{
    /*nn::Handle GetIpcFileSystem(){
        Result res;
        if(fs::sFileServerSession.mHandle != 0){
            NN_ERR_THROW_FATAL_ALL(res);
        }
        return fs::sFileServerSession.mHandle;
    }*/
}

void InitializeLatencyEmulation(void) {

}

static detail::FileSystemBase* spGlobalFileSystemBase;
void RegisterGlobalFileSystemBase(detail::FileSystemBase* base){
//    spGlobalFileSystemBase = base;
}



// Not Finished
void Initialize(){
    /*size_t nameLen;
    if(sFileServerSession != 0){
        return;
    }

    Result res; res = srv::Initialize();
    if(res.mResult != 0x8a067f9){
        NN_ERR_THROW_FATAL_ALL(res);
    }

    nameLen = strlen(detail::PORT_NAME_USER);
    res = srv::GetServiceHandle(&sFileServerSession, detail::PORT_NAME_USER, nameLen, 0);
    NN_ERR_THROW_FATAL_ALL(res);

    CTR::MPCore::detail::UserFileSystem::Initialize(sFileServerSession);
    #ifdef NN_DEBUG
        nndbgBreakWithTMessage_(NN_DBG_BREAK_REASON_ASSERT,"fs_FileSystemBase.h",0x79,"%s");
    #endif
    sFileSystemBase = sFileSystemBaseImpl;
    RegisterGlobalFileSystemBase(&sFileSystemBase);
    Handle hand; hand = detail::GetIpcFileSystem();
    Result res; res = ipc::FileSystem::SetPriority(&hand,0);
    NN_ERR_THROW_FATAL_ALL(res);*/
}

}
}