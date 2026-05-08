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
        virtual ~FileStream() { this->Finalize(); } // 0x0 - 0x4

        virtual Result TrySeek(s64 position, PositionBase base){ // 0x8
            return this->detail::FileBase::TrySeek(position, base);
        }

        virtual void Seek(s64 position, PositionBase base){ // 0xC
            this->detail::FileBase::Seek(position, base);
        }

        virtual Result TryGetPosition(s64* pOut){ // 0x10
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
            this->detail::FileBase::SetPosition(position);
        }


        virtual Result TryGetSize(s64* pOut) const{ // 0x20
            return this->detail::FileBase::TryGetSize(pOut);
        }

        virtual s64 GetSize() const{ // 0x24
            this->detail::FileBase::GetSize();
        }

        virtual Result TryRead(s32* pOut, void* buffer, size_t size){ // 0x28
            return this->detail::FileBase::TryRead(pOut,buffer,size);
        }

        virtual int Read(void* buf, size_t size){ // 0x2C
            this->detail::FileBase::Read(buf, size);
        }

        virtual s32 Write(const void* buffer, size_t size, bool flush){ // 0x30
            this->detail::FileBase::Write(buffer, size, flush);
        }

        virtual Result TryWrite(s32* pOut, const void* buffer, size_t size, bool flush){ // 0x34
            return this->nn::fs::detail::FileBase::TryWrite(pOut, buffer, size, flush);
        }

        virtual void SetSize(s64 size){ // 0x38
            this->detail::FileBase::SetSize(size);
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
            return this->detail::FileBase::TrySeek(position, base);
        }

        virtual void Seek(s64 position, PositionBase base){ // 0xC
            this->detail::FileBase::Seek(position, base);
        }

        virtual Result TryGetPosition(s64* pOut){ // 0x10
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
            this->detail::FileBase::SetPosition(position);
        }

        virtual Result TryGetSize(s64* pOut) const{ // 0x20
            return this->detail::FileBase::TryGetSize(pOut);
        }

        virtual s64 GetSize() const{ // 0x24
            this->detail::FileBase::GetSize();
        }

        virtual Result TryRead(s32* pOut, void* buffer, size_t size){ // 0x28
            return this->detail::FileBase::TryRead(pOut,buffer,size);
        }

        virtual int Read(void* buf, size_t size){ // 0x2C
            this->detail::FileBase::Read(buf, size);
        }

    };

} // fs
} // nn