#include <nn/fs/fs_FileSystemBase.h>

namespace nn{
namespace fs{
namespace detail{
void RegisterGlobalFileSystemBase(detail::FileSystemBase* base){
    spGlobalFileSystemBase = base;
}
}
}
}