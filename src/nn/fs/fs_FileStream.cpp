#include <nn/fs/fs_FileStream.h>
#include <nn/err/CTR/err_Api.h>

// TODO:: ALL

namespace nn{
namespace fs{
        // FileStream
FileStream::FileStream(){
}

FileStream::~FileStream(){
}

#ifdef NONMATCHING
#endif

s32 FileStream::Read(void *buffer,size_t size){
    s32 ret;
    NN_ERR_THROW_FATAL_ALL(this->detail::FileBase::TryRead(&ret, buffer, size));
    return ret;
}

Result FileStream::TryRead(s32* pOut, void* buffer, size_t size){
    this->detail::FileBase::TryRead(pOut, buffer, size);
}

s32 FileStream::Write(const void* buffer, size_t size, bool flush){
    s32 ret;
    NN_ERR_THROW_FATAL_ALL(this->detail::FileBase::TryWrite(&ret, buffer, size, flush));
    return ret;
}

Result FileStream::TryWrite(s32* pOut, const void* buffer, size_t size, bool flush) {
    Result result;
    u32 isError;

    result = this->nn::fs::detail::FileBase::TryWrite(pOut, buffer, size, flush);
    result.mResult;
}

void FileStream::Seek(s64 position, PositionBase base){
    NN_ERR_THROW_FATAL_ALL(this->detail::FileBase::TrySeek(position, base));
}

Result FileStream::TrySeek(s64 param_1, nn::fs::PositionBase pos) {
    Result result;

    result = this->nn::fs::detail::FileBase::TrySeek(param_1,pos);
    result.mResult;
}

s64 FileStream::GetPosition(){
    s64 ret;
    NN_ERR_THROW_FATAL_ALL(this->detail::FileBase::TryGetPosition(&ret));
    return ret;
}

Result FileStream::TryGetPosition(s64* pOut){
    return this->detail::FileBase::TryGetPosition(pOut);
}

void FileStream::SetPosition(s64 position){
    NN_ERR_THROW_FATAL_ALL(this->detail::FileBase::TrySetPosition(position));
}

Result FileStream::TrySetPosition(s64 position){
    return this->detail::FileBase::TrySetPosition(position);
}

s64 FileStream::GetSize(){
    //return this->detail::FileBase::TryGetSize();
}

Result FileStream::TryGetSize(s64* pOut){
    Result ret;
    NN_ERR_THROW_FATAL_ALL(this->detail::FileBase::TryGetSize((s64*)&ret));
    return ret;
}

void FileStream::SetSize(s64 size){
    this->detail::FileBase::TrySetSize(size);
}

Result FileStream::TrySetSize(s64 size){
    NN_ERR_THROW_FATAL_ALL(this->detail::FileBase::TrySetSize(size));
}

void FileStream::Flush(){
    this->detail::FileBase::TryFlush();
}

Result FileStream::TryFlush(){
    NN_ERR_THROW_FATAL_ALL(this->detail::FileBase::TryFlush());
}

}
}