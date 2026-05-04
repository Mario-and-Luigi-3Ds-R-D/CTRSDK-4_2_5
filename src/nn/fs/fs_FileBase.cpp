#include <nn/fs/fs_FileBase.h>
#include <nn/fs/fs_Paramaters.h>
#include <nn/Result.h>

// TODO:: ALL

namespace nn{
namespace fs{
namespace detail{

Result FileBase::TryRead(int* pReadOut, void* pBuffer, size_t pSize){
    // TODO
}

Result FileBase::TryWrite(int* pReadOut, const void* pBuffer, size_t pSize, bool pFlush=true){
}

Result FileBase::TrySeek(s64 pSeekOut, nn::fs::PositionBase pPosBase){
}

Result FileBase::TryGetPosition(s64* pPosOut)const {
}

Result FileBase::TrySetPosition(s64 pPosSet){
}

Result FileBase::TryGetSize(s64* pOutSize) const{
//    this->detail::FileBaseImpl::TryGetSize(pOutSize);
}

Result FileBase::TrySetSize(s64 size){
\
}

Result FileBase::TryFlush(){
}

} // detail
} // fs
} // nn