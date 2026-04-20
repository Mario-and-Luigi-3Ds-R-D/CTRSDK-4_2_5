#include <nn/fs/detail/fs_FileBase.h>
#include <nn/fs/fs_Paramaters.h>
#include <nn/Result.h>

// TODO:: ALL

namespace nn{
namespace fs{
namespace detail{

FileBase::FileBase(){
    
}

FileBase::~FileBase(){
    
}

Result FileBase::TryRead(int* pReadOut, void* pBuffer, size_t pSize){
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
}

Result FileBase::TrySetSize(s64 pSize){
}

Result FileBase::TryFlush(){
}

s32 FileBase::Read(void* pBuffer, size_t pSize){
}

void FileBase::Seek(s64 pSeekOut, nn::fs::PositionBase pPosBase){
}

s64 FileBase::GetPosition(){
}

s64 FileBase::GetSize(){
}

s32 FileBase::Write(const void * pBuffer, size_t pSize, bool pFlush){
}

void FileBase::SetSize(s64 size){

}

void FileBase::Flush(){

}

} // detail
} // fs
} // nn