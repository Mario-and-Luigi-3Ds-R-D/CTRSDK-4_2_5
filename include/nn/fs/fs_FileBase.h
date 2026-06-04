#pragma once

#include "nn/types.h"
#include "nn/Result.h"
#include "nn/fs/fs_Paramaters.h"
#include "nn/fs/CTR/MPCore/fs_UserFileSystem.h"
#include "nn/err/CTR/err_Api.h"
#include "nn/util/util_Int64.h"

using namespace nn::fs::CTR::MPCore::detail;

namespace nn{
namespace fs{
namespace detail{

    class FileBaseImpl{
    protected:
        void* mFile;
    private:
        void* GetPtr() const  {
            return reinterpret_cast<void*>(reinterpret_cast<uptr>(this->mFile) & ~static_cast<uptr>(0x1)); 
        }
    public:
        FileBaseImpl() : mFile(0) {}
        
        ~FileBaseImpl(){ this->Finalize(); }
        
        Result TryGetSize(s64* pOut) const {
            return UserFileSystem::TryGetFileSize(pOut, GetPtr()); 
        }
        
        Result TryFlush(){
            DoneFlush();
            return UserFileSystem::TryFlush(GetPtr());
        }
        Result TryReadFile(s32* pOut, s64 offset, void* buf, size_t size){
            size_t size2 = size;
            void* pOutPtr = this->GetPtr();
            return UserFileSystem::TryReadFile(pOut,pOutPtr,offset,buf,size2);
        }

        Result TryOpenImpl(const wchar_t* path, bit32 mode){
            return UserFileSystem::TryOpenFile(&this->mFile, path, mode);
        }

        void Finalize(){
            int ptr = (int)this->mFile;
            if((ptr & ~1) == 0){
                return;
            }
            if(ptr & 1)
                nndbgPanic();

            nn::fs::CTR::MPCore::detail::UserFileSystem::CloseFile(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(this->mFile) & ~1));
            this->mFile = 0;
        }
        void DoneFlush() { mFile = reinterpret_cast<void*>(reinterpret_cast<uptr>(mFile) & ~static_cast<uptr>(0x1)); }
    };

    class FileBase : public FileBaseImpl{
    protected:
        typedef util::Int64<s64> S64;
        S64 mPosition;
        mutable S64 mSize;
    public:
        FileBase() : mPosition(0), mSize(0) {}
        FileBase(const wchar_t* pathName, bit32 mode){ Initialize(pathName, mode); }
        Result TryRead(int*, void*, size_t);
        Result TryWrite(int*, const void*, size_t, bool);
        Result TrySeek(s64, nn::fs::PositionBase);
        Result TrySetPosition(s64);
        Result TryGetSize(s64*) const;
        Result TrySetSize(s64);
        Result TryFlush();
        /* Use these instead of calling it directly! */

        s32 Read(void* buffer, size_t size){
            s32 ret;
            NN_ERR_THROW_FATAL_ALL(TryRead(&ret, buffer, size));
            return ret;
        }

        s32 Write(const void* buffer, size_t size, bool flush){
            s32 ret;
            NN_ERR_THROW_FATAL_ALL(TryWrite(&ret, buffer, size, flush));
            return ret;
        }

        void Seek(s64 position, PositionBase base){
            NN_ERR_THROW_FATAL_ALL(TrySeek(position, base));
        }

        s64 GetPosition() const{
            s64 ret;
            NN_ERR_THROW_FATAL_ALL(TryGetPosition(&ret));
            return ret;
        }

        void SetPosition(s64 position){
            NN_ERR_THROW_FATAL_ALL(TrySetPosition(position));
        }

        s64 GetSize() const{
            s64 ret;
            NN_ERR_THROW_FATAL_ALL(TryGetSize(&ret));
            return ret;
        }

        void SetSize(s64 size){
            NN_ERR_THROW_FATAL_ALL(TrySetSize(size));
        }

        void Flush(){
            NN_ERR_THROW_FATAL_ALL(TryFlush());
        }

        Result TryGetPosition(s64* pOut) const{
            *pOut = mPosition;
            return ResultSuccess();
        }

        inline Result FileBase::TryInitialize(const wchar_t* pathName, bit32 mode){
            this->mPosition = this->mSize = 0;
            return TryOpenImpl(pathName, mode);
        }

        void FileBase::Initialize(const wchar_t* pathName, bit32 mode){
            Result result = TryInitialize(pathName, mode);
            if (result.IsFailure()){
                //NN_SLOG_("file open failed: ");
                //NN_SLOG_("%lls\n", pathName);
                NN_ERR_THROW_FATAL_ALL(result);
            }
        }
    };

} // detail
} // fs
} // nn