#include <nn/Handle.h>
#include <nn/fs/CTR/MPCore/fs_UserFileSystem.h>
#include <nn/dbg/dbg_Break.h>

namespace nn{
namespace fs{
namespace detail{

class FileSystemBaseImpl : public CTR::MPCore::detail::UserFileSystem{

};

class FileSystemBase{
protected:
    FileSystemBaseImpl* mpImpl;
public:
    void Initialize(FileSystemBaseImpl* impl){
        #ifdef NN_DEBUG
            if(!this->mpImpl){
                nndbgBreakWithTMessage_(NN_DBG_BREAK_REASON_ASSERT,"fs_FileSystemBase.h",19,"%s","!this->mpImpl");
            }
        #endif
        this->mpImpl = impl;
    }
};

}

namespace detail{
    void RegisterGlobalFileSystemBase(detail::FileSystemBase* base);
    static detail::FileSystemBase* spGlobalFileSystemBase;
}
}
}