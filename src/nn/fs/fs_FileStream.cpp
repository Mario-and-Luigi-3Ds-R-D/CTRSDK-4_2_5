#include <nn/fs/fs_FileStream.h>

// TODO:: ALL

namespace nn{
namespace fs{
        // FileStream
FileStream::FileStream(){

}

FileStream::~FileStream(){

}

int FileStream::Read(void* pBuffer, size_t size){
    detail::FileBase::Read(pBuffer, size);
}

Result FileStream::TryRead(s32* pOut, void* buffer, size_t size){

}

s32 FileStream::Write(const void* buffer, size_t size, bool flush){

}
Result FileStream::TryWrite(s32* pOut, const void* buffer, size_t size, bool flush){
    this->mPosition.lo;
}

void FileStream::Seek(s64 position, PositionBase base){
    this->detail::FileBase::Seek(position, base);
}

Result FileStream::TrySeek(s64 position, PositionBase base){

}

s64 FileStream::GetPosition(){
    this->detail::FileBase::GetPosition();
}

Result FileStream::TryGetPosition(s64* pOut){

}

void FileStream::SetPosition(s64 position){

}

Result FileStream::TrySetPosition(s64 position){

}

s64 FileStream::GetSize(){

}

Result FileStream::TryGetSize(s64* pOut){

}

void FileStream::SetSize(s64 size){

}

Result FileStream::TrySetSize(s64 size){

}

void FileStream::Flush(){

}

Result FileStream::TryFlush(){

}

// FileInputStream

FileInputStream::FileInputStream(){

}

FileInputStream::~FileInputStream(){

}

s32 FileInputStream::Read(void* buffer, size_t size){

}

Result FileInputStream::TryRead(s32* pOut, void* buffer, size_t size){

}

void FileInputStream::Seek(s64 position, PositionBase base){

}

Result FileInputStream::TrySeek(s64 position, PositionBase base){

}

s64 FileInputStream::GetPosition(){

}

Result FileInputStream::TryGetPosition(s64* pOut){

}

void FileInputStream::SetPosition(s64 position){

}

Result FileInputStream::TrySetPosition(s64 position){

}

s64 FileInputStream::GetSize(){

}

Result FileInputStream::TryGetSize(s64* pOut){

}


}
}