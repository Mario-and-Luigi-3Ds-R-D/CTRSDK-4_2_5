#include <nn/Handle.h>
#include <nn/fs/CTR/MPCore/fs_UserFileSystem.h>
#include <nn/dbg/dbg_Break.h>
#include <nn/Assert.h>

namespace nn{
namespace fs{
namespace detail{

class FileSystemBaseImpl : public CTR::MPCore::detail::UserFileSystem{

};

class FileSystemBase{
protected:
    FileSystemBaseImpl* mpImpl;
public:
    FileSystemBase() : mpImpl(NULL){}
    void Initialize(FileSystemBaseImpl& impl){
        NN_TASSERT_(!mpImpl);
        *mpImpl = impl;
    }
};

void RegisterGlobalFileSystemBase(detail::FileSystemBase& base);
extern detail::FileSystemBase* spGlobalFileSystemBase;

}
}
}