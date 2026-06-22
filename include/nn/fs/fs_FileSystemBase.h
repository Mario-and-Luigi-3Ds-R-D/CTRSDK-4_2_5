#include <nn/Handle.h>
#include <nn/fs/CTR/MPCore/fs_UserFileSystem.h>
#include <nn/dbg/dbg_Break.h>
#include "nn/Assert.h"

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
        NN_TASSERT_(!mpImpl);
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