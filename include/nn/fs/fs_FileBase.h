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
        
        Result TryGetSize(s64* pOut) const {
            return UserFileSystem::TryGetFileSize(pOut, GetPtr()); 
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
    };

    class FileBase : public FileBaseImpl{
    protected:
        typedef util::Int64<s64> S64;
        S64 mPosition;
        mutable S64 mSize;
    public:
        FileBase() : mPosition(0), mSize(0) {}
        Result TryRead(int*, void*, size_t);
        Result TryWrite(int*, const void*, size_t, bool);
        Result TrySeek(s64, nn::fs::PositionBase);
        Result TryGetPosition(s64*) const;
        Result TrySetPosition(s64);
        Result TryGetSize(s64*) const;
        Result TrySetSize(s64);
        Result TryFlush();

        s64 GetSize() const{
            s64 ret;
            NN_ERR_THROW_FATAL_ALL(TryGetSize(&ret));
            return ret;
        }

        // Sets FileBase, Luigifan27 custom inline.
        void SetPositionFlags(){
            this->mPosition.lo = 0;
            this->mPosition.hi = 0;
        }

        void SetSizeFlags(){
            this->mSize.lo = 0;
            this->mSize.hi = 0;
        }

        void SetFlagsImpl(){
            this->SetPositionFlags();
            this->SetSizeFlags();
        }
    };
} // detail
} // fs
} // nn