#include <nn/fs/fs_FileStream.h>

namespace nn{
namespace fs{
        // FileStream
        FileStream::FileStream(){}

        FileStream::~FileStream(){}

        Result FileStream::TrySeek(s64 pSeekOut, nn::fs::PositionBase pPosBase){
            return detail::FileBase::TrySeek(pSeekOut, pPosBase);
        }
        void FileStream::Seek(s64 pSeekOut, nn::fs::PositionBase pPosBase){
            detail::FileBase::Seek(pSeekOut, pPosBase);
        }
        int FileStream::FUN_005e0480(){}

        FileStream* FileStream::FUN_005e0478(){}

        s64 FileStream::FUN_00128140(){}

        void FileStream::SetPosition(s64 pPosOut){
            detail::FileBase::SetPosition(pPosOut);
        }
        Result FileStream::TryGetSize(s64* pSizeOut){
            return detail::FileBase::TryGetSize(pSizeOut);
        }
        s64 FileStream::GetSize(){
            return detail::FileBase::GetSize();
        }
        Result FileStream::TryRead(int* pReadOut, void* pBuffer, size_t pSize){
            return detail::FileBase::TryRead(pReadOut, pBuffer, pSize);
        }
        int FileStream::Read(void* pBuffer, size_t pSize){
            return detail::FileBase::Read(pBuffer, pSize);
        }
        int FileStream::Write(const void* pBuffer, size_t pSize, bool pFlush){
            return detail::FileBase::Write(pBuffer, pSize, pFlush);
        }
        Result FileStream::TryWrite(int* pOut, const void* pBuffer, size_t pSize, bool pFlush){
            return  detail::FileBase::TryWrite(pOut, pBuffer, pSize, pFlush);
        }
        void FileStream::FUN_0045c5dc(){}

        void FileStream::FUN_0045e9e8(){}

        void FileStream::FUN_0045c57c(){}

        void FileStream::FUN_0045ea3c(){}

        // FileInputStream

        FileInputStream::~FileInputStream(){
        }
        Result FileInputStream::TrySeek(s64 pSeekOut, nn::fs::PositionBase pPosBase){
            return detail::FileBase::TrySeek(pSeekOut, pPosBase);
        }
        void FileInputStream::Seek(s64 pSeekOut, nn::fs::PositionBase pPosBase){
            detail::FileBase::Seek(pSeekOut, pPosBase);
        }
        int FileInputStream::FUN_005f5784(){}

        s64 FileInputStream::FUN_005f57b8(){} // (param_1 + -0x1c) + 8 thiscall

        Result FileInputStream::TrySetPosition(s64 pPosPos){
            return detail::FileBase::TrySetPosition(pPosPos);
        }
        void FileInputStream::SetPosition(s64 pPosPos){
            detail::FileBase::SetPosition(pPosPos);
        }
        Result FileInputStream::TryGetSize(s64* pSizeOut){
            return detail::FileBase::TryGetSize(pSizeOut);
        }
        s64 FileInputStream::GetSize(){
            return detail::FileBase::GetSize();
        }
        Result FileInputStream::TryRead(int* pReadOut, void* pBuffer, size_t pSize){
            return detail::FileBase::TryRead(pReadOut, pBuffer, pSize);
        }
        int FileInputStream::Read(void* pBuffer, size_t pSize){
            return detail::FileBase::Read(pBuffer, pSize);
        }

        // FileOutputStream
}
}