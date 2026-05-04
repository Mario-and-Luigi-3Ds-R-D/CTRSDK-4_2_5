#pragma once

#include "nn/fs/fs_IStream.h"
#include "nn/fs/fs_Paramaters.h"
#include "nn/fs/fs_FileBase.h"
#include "nn/err/CTR/err_Api.h"
#include "nn/util/util_NonCopyable.h"
#include "nn/Result.h"

namespace nn{
namespace fs{

    class FileStream : public IStream, public detail::FileBase{ // public FileBase as well
    public:
        FileStream() { }
        virtual ~FileStream() { } // 0x0 - 0x4

        virtual Result TrySeek(s64 position, PositionBase base){ // 0x8
            this->detail::FileBase::TrySeek(position, base);
        }

        virtual void Seek(s64 position, PositionBase base){ // 0xC
            NN_ERR_THROW_FATAL_ALL(this->detail::FileBase::TrySeek(position, base));
        }

        virtual Result TryGetPosition(s64* pOut){ // 0x10
            return this->detail::FileBase::TryGetPosition(pOut);
        }

        virtual s64 GetPosition(){ // 0x14
            s64 ret;
            NN_ERR_THROW_FATAL_ALL(this->detail::FileBase::TryGetPosition(&ret));
            return ret;
        }

        virtual Result TrySetPosition(s64 position){ // 0x18
            return this->detail::FileBase::TrySetPosition(position);
        }

        virtual void SetPosition(s64 position){ // 0x1C
            NN_ERR_THROW_FATAL_ALL(this->detail::FileBase::TrySetPosition(position)__current_pc());
        }


        virtual Result TryGetSize(s64* pOut) const{ // 0x20
            Result ret;
            NN_ERR_THROW_FATAL_ALL(this->detail::FileBase::TryGetSize((s64*)&ret)__current_pc());
            return ret;
        }

        virtual s64 GetSize() const{ // 0x24
            s64 ret;
            NN_ERR_THROW_FATAL_ALL(this->detail::FileBase::TryGetSize(&ret));
            return ret;
        }

        virtual Result TryRead(s32* pOut, void* buffer, size_t size){ // 0x28
            this->detail::FileBase::TryRead(pOut,buffer,size);
        }

        virtual int Read(void*, size_t){ // 0x2C
            s32 ret;
            NN_ERR_THROW_FATAL_ALL(this->detail::FileBase::TryRead(&ret, buffer, size));
            return ret;
        }

        virtual s32 Write(const void* buffer, size_t size, bool flush){ // 0x30
            s32 ret;
            NN_ERR_THROW_FATAL_ALL(this->detail::FileBase::TryWrite(&ret, buffer, size, flush));
            return ret;
        }

        virtual Result TryWrite(s32* pOut, const void* buffer, size_t size, bool flush){ // 0x34
            Result result;
            u32 isError;

            result = this->nn::fs::detail::FileBase::TryWrite(pOut, buffer, size, flush);
            result.mResult;
        }

        virtual void SetSize(s64 size){ // 0x38
            NN_ERR_THROW_FATAL_ALL(this->detail::FileBase::TrySetSize(size));
        }


        virtual Result TrySetSize(s64 size){ // 0x3C
            return this->detail::FileBase::TrySetSize(size);
        }

        virtual void Flush(){ // 0x40
            this->detail::FileBase::TryFlush();
        }

        virtual Result TryFlush(){ // 0x44
            return this->detail::FileBase::TryFlush();
        }
    };

    class FileInputStream : public nn::fs::IInputStream, public nn::fs::detail::FileBase, private nn::util::NonCopyable<FileInputStream>{
    public:
        FileInputStream(){ }
        virtual ~FileInputStream(){ } // 0x0 / 0x4

        virtual Result TrySeek(s64 position, PositionBase base){ // 0x8
            this->detail::FileBase::TrySeek(position, base);
        }

        virtual void Seek(s64 position, PositionBase base){ // 0xC
            NN_ERR_THROW_FATAL_ALL(this->detail::FileBase::TrySeek(position, base));
        }

        virtual Result TryGetPosition(s64* pOut) const{ // 0x10
            return this->detail::FileBase::TryGetPosition(pOut);
        }

        virtual s64 GetPosition() const{ // 0x14
            s64 pos;
            
            pos = this->mPosition.lo;
            pos = this->mPosition.hi;
            return pos;
        }

        virtual Result TrySetPosition(s64 position){ // 0x18
            return this->detail::FileBase::TrySetPosition(position);
        }

        virtual void SetPosition(s64 position){ // 0x1C
            NN_ERR_THROW_FATAL_ALL(this->detail::FileBase::TrySetPosition(position)__current_pc());
        }

        virtual Result TryGetSize(s64* pOut) const{ // 0x20
            Result ret;
            NN_ERR_THROW_FATAL_ALL(this->detail::FileBase::TryGetSize((s64*)&ret)__current_pc());
            return ret;
        }

        virtual s64 GetSize() const{ // 0x24
            s64 ret;
            NN_ERR_THROW_FATAL_ALL(this->detail::FileBase::TryGetSize(&ret));
            return ret;
        }

        virtual Result TryRead(s32* pOut, void* buffer, size_t size){ // 0x28
            this->detail::FileBase::TryRead(pOut,buffer,size);
        }

        virtual int Read(void*, size_t){ // 0x2C
            s32 ret;
            NN_ERR_THROW_FATAL_ALL(this->detail::FileBase::TryRead(&ret, buffer, size));
            return ret;
        }

    };

} // fs
} // nn