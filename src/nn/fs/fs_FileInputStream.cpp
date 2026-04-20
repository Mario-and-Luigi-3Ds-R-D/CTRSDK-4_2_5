#include <nn/fs/fs_FileStream.h>
#include <nn/err/CTR/err_Api.h>

// TODO:: ALL

namespace nn{
namespace fs{

// FileInputStream

FileInputStream::FileInputStream(){}

FileInputStream::~FileInputStream(){}

s32 FileInputStream::Read(void* buffer, size_t size){
    s32 ret;
    NN_ERR_THROW_FATAL_ALL(this->detail::FileBase::TryRead(&ret, buffer, size));
    return ret;
}

Result FileInputStream::TryRead(s32* pOut, void* buffer, size_t size){
    return this->detail::FileBase::TryRead(pOut, buffer, size);
}

void FileInputStream::Seek(s64 position, PositionBase base){
    NN_ERR_THROW_FATAL_ALL(this->detail::FileBase::TrySeek(position, base));
}

Result FileInputStream::TrySeek(s64 position, PositionBase base){
    Result result;

    result = this->nn::fs::detail::FileBase::TrySeek(position,base);
    result.mResult;
}

s64 FileInputStream::GetPosition(){
    s64 ret;
    NN_ERR_THROW_FATAL_ALL(this->detail::FileBase::TryGetPosition(&ret)__current_pc());
    return ret;
}

Result FileInputStream::TryGetPosition(s64* pOut){
    return this->detail::FileBase::TryGetPosition(pOut);
}

void FileInputStream::SetPosition(s64 position){
    NN_ERR_THROW_FATAL_ALL(this->detail::FileBase::TrySetPosition(position)__current_pc());
}

Result FileInputStream::TrySetPosition(s64 position){
    return this->detail::FileBase::TrySetPosition(position);
}

s64 FileInputStream::GetSize(){
    return this->detail::FileBase::GetSize();
}

Result FileInputStream::TryGetSize(s64* pOut){
    Result ret;
    NN_ERR_THROW_FATAL_ALL(this->detail::FileBase::TryGetSize((s64*)&ret)__current_pc());
    return ret;
}


}
}